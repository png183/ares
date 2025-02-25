auto MCD::readExternalIO(n1 upper, n1 lower, n24 address, n16 data) -> n16 {
  if(!MegaCD()) return data;
  address.bit(6,7) = 0;  //a12040-a120ff mirrors a12000-a1203f

  if(address == 0xa12000) {
    data.bit( 0)    = io.run;
    data.bit( 1)    = io.request;
    data.bit( 2, 7) = Unmapped;
    data.bit( 8)    = external.irq.pending;
    data.bit( 9,14) = Unmapped;
    //todo: hardware manual states this bit exists; software manual states that it does not
    data.bit(15)    = external.irq.enable;
  }

  if(address == 0xa12002) {
    data.bit(0)    =!io.wramMode ? !io.wramSwitch : +io.wramSelect;
    data.bit(1)    =!io.wramMode ?  io.wramSwitch :  io.wramSwitchRequest;
    data.bit(2)    = io.wramMode;
    data.bit(3, 5) = Unmapped;
    data.bit(6, 7) = io.pramBank;
    data.bit(8,15) = io.pramProtect;
  }

  if(address == 0xa12004) {
    data.bit( 0, 7) = Unmapped;
    data.bit( 8,10) = cdc.transfer.destination;
    data.bit(11,13) = Unmapped;
    data.bit(14)    = cdc.transfer.ready;
    data.bit(15)    = cdc.transfer.completed;
  }

  if(address == 0xa12006) {
    data.byte(1) = io.vectorLevel4.byte(1);
    data.byte(0) = io.vectorLevel4.byte(0);
  }

  if(address == 0xa12008) {
    debug(unusual, "[MCD::readExternalIO] address=0xa12008");
  }

  if(address == 0xa1200a) {
    debug(unusual, "[MCD::readExternalIO] address=0xa1200a");
  }

  if(address == 0xa1200c) {
    data.bit( 0,11) = cdc.stopwatch;
    data.bit(12,15) = Unmapped;
  }

  if(address == 0xa1200e) {
    data.byte(0) = communication.cfs;
    data.byte(1) = communication.cfm;
  }

  if(address >= 0xa12010 && address <= 0xa1201f) {
    n3 index = address - 0xa12010 >> 1;
    data = communication.command[index];
  }

  if(address >= 0xa12020 && address <= 0xa1202f) {
    n3 index = address - 0xa12020 >> 1;
    data = communication.status[index];
  }

  return data;
}

auto MCD::writeExternalIO(n1 upper, n1 lower, n24 address, n16 data) -> void {
  if(!MegaCD()) return;
  address.bit(6,7) = 0;  //a12040-a120ff mirrors a12000-a1203f

  if(address == 0xa12000) {
    if(lower) {
      // The Mega-CD has a documented method of performing a forced reset
      // on the gate array in software via the following code sequence:
      //   MOVE.W #$FF00, $A12002
      //   MOVE.W #$03, $A12001
      //   MOVE.W #$02, $A12001
      //   MOVE.W #$00, $A12001
      // Try to detect the modal changes caused by executing this sequence. (Is this too strict?)
      if(io.request && !io.run && !data.bit(1,0)
      && io.pramProtect == 0xff && io.pramBank == 0 && io.wramSwitchRequest) {
        // TODO: reset subcpu-controlled gate array registers (needs confirmation)
        // Notice: the subcpu bus is not released at this time.
      } else {
        if(io.run && !data.bit(0)) resetCpu();
        io.run     = data.bit(0);
        io.request = io.run ? data.bit(1) : 1; // asserting reset forces busreq (confirmed by eke)
        io.halt    = io.request;
      }
    }
    if(upper) {
      if(data.bit(8)) external.irq.raise();
    }
  }

  if(address == 0xa12002) {
    if(lower) {
      if(data.bit(1) == 0) io.wramSwitchRequest = 1;
      if(data.bit(1) == 1) io.wramSwitch = 1;
      io.pramBank = data.bit(6,7);
    }
    if(upper) {
      io.pramProtect = data.bit(8,15);
    }
  }

  if(address == 0xa12004) {
    //read-only
  }

  if(address == 0xa12006) {
    if(upper) io.vectorLevel4.byte(1) = data.byte(1);
    if(lower) io.vectorLevel4.byte(0) = data.byte(0);
  }

  if(address == 0xa12008) {
    //read-only
  }

  if(address == 0xa1200a) {
    //reserved
    debug(unusual, "[MCD::writeExternalIO] address=0xa1200a");
  }

  if(address == 0xa1200c) {
    //read-only
  }

  if(address == 0xa1200e) {
    // 8-bit register mapped into 16-bit gate array
    // All writes go to the high byte (special case)
    communication.cfm = data.byte(1);
  }

  if(address >= 0xa12010 && address <= 0xa1201f) {
    n3 index = address - 0xa12010 >> 1;
    if(lower) communication.command[index].byte(0) = data.byte(0);
    if(upper) communication.command[index].byte(1) = data.byte(1);
  }

  if(address >= 0xa12020 && address <= 0xa1202f) {
    //read-only
  }
}
