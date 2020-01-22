// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "kotlin_native_example_plugin.h"

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar.h>
#include <flutter/standard_method_codec.h>
#include <sys/utsname.h>
#include <memory>
#include <sstream>

#include "KotlinNative_api.h"

namespace {

const char kChannelName[] = "com.kotlin_native_example_plugin.platform_channels/channel";

class KotlinNativeExamplePlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrar *registrar);

  // Creates a plugin that communicates on the given channel.
  KotlinNativeExamplePlugin(
      std::unique_ptr<flutter::MethodChannel<flutter::EncodableValue>> channel);

  virtual ~KotlinNativeExamplePlugin();

 private:
  // Called when a method is called on |channel_|;
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

  // The MethodChannel used for communication with the Flutter engine.
  std::unique_ptr<flutter::MethodChannel<flutter::EncodableValue>> channel_;
};

// static
void KotlinNativeExamplePlugin::RegisterWithRegistrar(flutter::PluginRegistrar *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), kChannelName,
          &flutter::StandardMethodCodec::GetInstance());
  auto *channel_pointer = channel.get();

  auto plugin = std::make_unique<KotlinNativeExamplePlugin>(std::move(channel));

  channel_pointer->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

KotlinNativeExamplePlugin::KotlinNativeExamplePlugin(
    std::unique_ptr<flutter::MethodChannel<flutter::EncodableValue>> channel)
    : channel_(std::move(channel)) {}

KotlinNativeExamplePlugin::~KotlinNativeExamplePlugin(){};

void KotlinNativeExamplePlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  if (method_call.method_name().compare("getPlatformVersion") == 0) {
    struct utsname uname_data = {};
    uname(&uname_data);
    std::ostringstream version_stream;
    version_stream << "Linux " << uname_data.version;
    flutter::EncodableValue response(version_stream.str());
    result->Success(&response);
  }
  else if (method_call.method_name().compare("echo") == 0) {
    KotlinNative_ExportedSymbols* libs = KotlinNative_symbols();
    const flutter::EncodableValue* args = method_call.arguments();

    std::string message = "null";
    if (args != nullptr && args->IsList() && args->ListValue().size() == 2) {
      auto list = args->ListValue();
      //message = list[0].StringValue(); // "message"
      message = list[1].StringValue();
    }

    std::string resultMessage = libs->kotlin.root.KotlinNative.echo(message.c_str());
    flutter::EncodableValue response(resultMessage);

    result->Success(&response);
  }
  else {
    result->NotImplemented();
  }
}

}  // namespace

void KotlinNativeExamplePluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  // The plugin registrar owns the plugin, registered callbacks, etc., so must
  // remain valid for the life of the application.
  static auto *plugin_registrar = new flutter::PluginRegistrar(registrar);

  KotlinNativeExamplePlugin::RegisterWithRegistrar(plugin_registrar);
}
