#include "include/windows_ex_1/windows_ex_1_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <map>
#include <memory>
#include <sstream>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.System.Power.h>

using namespace winrt;
using namespace Windows::System::Power;

namespace {

class WindowsEx_1Plugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  WindowsEx_1Plugin();

  virtual ~WindowsEx_1Plugin();

 private:
  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

// static
void WindowsEx_1Plugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "windows_ex_1",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<WindowsEx_1Plugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

WindowsEx_1Plugin::WindowsEx_1Plugin() {}

WindowsEx_1Plugin::~WindowsEx_1Plugin() {}

void WindowsEx_1Plugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  // Replace "getPlatformVersion" check with your plugin's method.
  // See:
  // https://github.com/flutter/engine/tree/master/shell/platform/common/cpp/client_wrapper/include/flutter
  // and
  // https://github.com/flutter/engine/tree/master/shell/platform/glfw/client_wrapper/include/flutter
  // for the relevant Flutter APIs.
  if (method_call.method_name().compare("getPlatformVersion") == 0) {
    std::ostringstream version_stream;
    version_stream << "Windows ";
    if (IsWindows10OrGreater()) {
      version_stream << "10+";
    } else if (IsWindows8OrGreater()) {
      version_stream << "8";
    } else if (IsWindows7OrGreater()) {
      version_stream << "7";
    }
    result->Success(flutter::EncodableValue(version_stream.str()));
  } else {
    if(method_call.method_name().compare("getBatteryStatus"))
    {
      
      auto hellMan = PowerManager{};
      auto batStat = hellMan.BatteryStatus();
      std::ostringstream power_stream;
      if(batStat == BatteryStatus::Charging)
      {
        power_stream << "Charging...";
      } else if(batStat == BatteryStatus::Discharging) {
        power_stream << "Discharging...";  
      } else if(batStat == BatteryStatus::Idle){
        power_stream << "Battery Idle";
      } else 
        power_stream << "Absent";
      result->Success(flutter::EncodableValue(power_stream.str()));    
    }
    else
    result->NotImplemented();
  }
}

}  // namespace

void WindowsEx_1PluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  WindowsEx_1Plugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
