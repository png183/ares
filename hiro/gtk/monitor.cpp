#if defined(Hiro_Monitor)

namespace hiro {

auto pMonitor::count() -> u32 {
  #if HIRO_GTK==2
  return gdk_screen_get_n_monitors(gdk_screen_get_default());
  #elif HIRO_GTK==3
  return gdk_display_get_n_monitors(gdk_display_get_default());
  #endif
}

auto pMonitor::dpi(u32 monitor) -> Position {
  #if HIRO_GTK==2
  //GTK2 does not support either per-monitor or per-axis DPI reporting
  float dpi = round(gdk_screen_get_resolution(gdk_screen_get_default()));
  return {dpi, dpi};
  #elif HIRO_GTK==3
  auto gdkMonitor = gdk_display_get_monitor(gdk_display_get_default(), monitor);
  GdkRectangle rectangle = {};
  gdk_monitor_get_workarea(gdkMonitor, &rectangle);
  return {
    round((float)rectangle.width / (gdk_monitor_get_width_mm(gdkMonitor) / 25.4)),
    round((float)rectangle.height / (gdk_monitor_get_height_mm(gdkMonitor) / 25.4))
  };
  #endif
}

auto pMonitor::geometry(u32 monitor) -> Geometry {
  GdkRectangle rectangle = {};
  #if HIRO_GTK==2
  gdk_screen_get_monitor_geometry(gdk_screen_get_default(), monitor, &rectangle);
  #elif HIRO_GTK==3
  auto gdkMonitor = gdk_display_get_monitor(gdk_display_get_default(), monitor);
  gdk_monitor_get_geometry(gdkMonitor, &rectangle);
  #endif
  return {rectangle.x, rectangle.y, rectangle.width, rectangle.height};
}

auto pMonitor::primary() -> u32 {
  #if HIRO_GTK==2 || 1
  return gdk_screen_get_primary_monitor(gdk_screen_get_default());
  #elif HIRO_GTK==3
  return gdk_display_get_primary_monitor(gdk_display_get_default());
  #endif
}

auto pMonitor::workspace(u32 monitor) -> Geometry {
  #if HIRO_GTK==2
  if(Monitor::count() == 1) {
    return Desktop::workspace();
  } else {
    //it is currently unknown how to get per-monitor workspace areas, use geometry instead
    return Monitor::geometry(monitor);
  }
  #elif HIRO_GTK==3
  auto gdkMonitor = gdk_display_get_monitor(gdk_display_get_default(), monitor);
  GdkRectangle rectangle = {};
  gdk_monitor_get_workarea(gdkMonitor, &rectangle);
  return {rectangle.x, rectangle.y, rectangle.width, rectangle.height};
  #endif
}

}

#endif
