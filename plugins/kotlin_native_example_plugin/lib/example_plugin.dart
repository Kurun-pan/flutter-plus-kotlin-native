import 'dart:async';
import 'package:flutter/services.dart';

class ExamplePlugin {
  static const MethodChannel _channel =
      const MethodChannel('kotlin_native_example_plugin');

  static Future<String> get platformVersion async {
    //final String version = await _channel.invokeMethod('getPlatformVersion');
    final String version = await _channel.invokeMethod('echo');
    return version;
  }
}
