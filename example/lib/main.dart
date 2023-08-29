import 'dart:ffi';

import 'package:flutter/material.dart';
import 'dart:async';

import 'package:native_add/native_add.dart' as native_add;
import 'dart:ffi';
import 'package:ffi/ffi.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  @override
  void initState() {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Native Packages'),
        ),
        floatingActionButton: FloatingActionButton(onPressed: () async {
          print(native_add.sum(1, 2));
          print(native_add.getAge(3, 4));
          print(native_add.getName(3, 4).cast<Utf8>().toDartString());
          print(native_add
              .encryptString(" Plaint Text".toNativeUtf8().cast<Char>())
              .cast<Utf8>()
              .toDartString());
          print(await native_add.sumAsync(3, 4));
        }),
      ),
    );
  }
}
