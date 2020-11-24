import 'dart:async';

import 'package:flutter/services.dart';

class WindowsEx_1 {
  static const MethodChannel _channel = const MethodChannel('windows_ex_1');

  static Future<String> get platformVersion async {
    final String version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }

  static Future<String> get batteryStatus async {
    final String strStatus = await _channel.invokeMethod('getBatteryStatus');
    return strStatus;
  }
}
