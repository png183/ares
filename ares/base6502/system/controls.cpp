auto System::Controls::load(Node::Object parent) -> void {
  node = parent->append<Node::Object>("Controls");
}
