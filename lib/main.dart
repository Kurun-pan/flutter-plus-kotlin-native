import 'dart:io';
import 'package:flutter/services.dart';
import 'package:flutter/material.dart';
import 'package:flutter/foundation.dart'
    show debugDefaultTargetPlatformOverride;

void _setTargetPlatformForDesktop() {
  // No need to handle macOS, as it has now been added to TargetPlatform.
  if (Platform.isLinux || Platform.isWindows) {
    debugDefaultTargetPlatformOverride = TargetPlatform.fuchsia;
  }
}

void main() {
  _setTargetPlatformForDesktop();
  WidgetsFlutterBinding.ensureInitialized();
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter + Kotlin/Native Sample',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: MyHomePage(title: 'Flutter + Kotlin/Native Sample'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);
  final String title;

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  String _platformMessage;

  static MethodChannel _methodChannel = const MethodChannel(
      'com.kotlin_native_example_plugin.platform_channels/channel');

  static const EventChannel _eventChannel = const EventChannel(
      "com.kotlin_native_example_plugin.platform_channels/event");

  void _callPlatformMethod() async {
    try {
      String result = await _methodChannel
          .invokeMethod('echo', ['message', 'Hello, World!']);
      print('Kotlin/Native echo returned $result');
      setState(() {
        _platformMessage = result;
      });
    } catch (e) {
      print(e.toString());
    }
  }

  void _eventListener(dynamic obj) {
    print('Kotlin/Native Plugin EventChannel Result: ' + obj);
  }

  // Kotlin/Native -> Dart
  @override
  void initState() {
    super.initState();

    _callPlatformMethod();
    // Now, not supported EventChannel in Linux/Windows...
    if (!(Platform.isLinux || Platform.isWindows)) {
      _eventChannel.receiveBroadcastStream().listen(_eventListener);
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Text(
              'Platform Message = $_platformMessage',
            ),
            Text(
              'Event = ',
            ),
          ],
        ),
      ),
    );
  }
}
