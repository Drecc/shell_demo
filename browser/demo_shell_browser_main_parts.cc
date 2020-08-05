#include "shell_demo/browser/demo_shell_browser_main_parts.h"

#include "content/public/browser/browser_context.h"
#include "shell_demo/browser/shell.h"
#include "ui/base/material_design/material_design_controller.h"

#if defined(OS_ANDROID)
#include "components/crash/content/browser/child_exit_observer_android.h"
#include "components/crash/content/browser/child_process_crash_observer_android.h"
#include "net/android/network_change_notifier_factory_android.h"
#include "net/base/network_change_notifier.h"
#endif

#if !defined(OS_CHROMEOS) && defined(USE_AURA) && defined(OS_LINUX)
#include "ui/base/ime/init/input_method_initializer.h"
#endif
#if defined(USE_AURA) && defined(USE_X11)
#include "ui/events/devices/x11/touch_factory_x11.h"
#endif

namespace content {

DemoShellBrowserMainParts::DemoShellBrowserMainParts(const MainFunctionParams& params)
    : main_function_params_(params)
    , run_message_loop_(true) {
}

DemoShellBrowserMainParts::~DemoShellBrowserMainParts() {

}

int DemoShellBrowserMainParts::PreEarlyInitialization() {
#if !defined(OS_CHROMEOS) && defined(USE_AURA) && defined(OS_LINUX)
  ui::InitializeInputMethodForTesting();
#endif
#if defined(OS_ANDROID)
  net::NetworkChangeNotifier::SetFactory(
    new net::NetworkChangeNotifierFactoryAndroid());
#endif
  return BrowserMainParts::PreEarlyInitialization();
}

int DemoShellBrowserMainParts::PreCreateThreads() {
  return 0;
}

void DemoShellBrowserMainParts::PreMainMessageLoopStart() {
#if defined(USE_AURA) && defined(USE_X11)
  ui::TouchFactory::SetTouchDeviceListFromCommandLine();
#endif
}

void DemoShellBrowserMainParts::PostMainMessageLoopStart() {
}

void DemoShellBrowserMainParts::InitializeBrowserContexts(){
  browser_context_.reset(new DemoShellBrowserContext(false));
}

void DemoShellBrowserMainParts::InitializeMessageLoopContext(){
  ui::MaterialDesignController::Initialize();
  DemoShell::CreateNewWindow(browser_context_.get(), GURL("http://www.baidu.com"), nullptr,
                        gfx::Size());
}

void DemoShellBrowserMainParts::PreMainMessageLoopRun() {
  InitializeBrowserContexts();
  DemoShell::Initialize();
  InitializeMessageLoopContext();
  if (main_function_params_.ui_task) {
      std::move(*main_function_params_.ui_task).Run();
      delete main_function_params_.ui_task;
      run_message_loop_ = false;
  }
}

bool DemoShellBrowserMainParts::MainMessageLoopRun(int* result_code) {
  return !run_message_loop_;
}

void DemoShellBrowserMainParts::PreDefaultMainMessageLoopRun(base::OnceClosure quit_closure) {
  DemoShell::SetMainMessageLoopQuitClosure(std::move(quit_closure));
}

void DemoShellBrowserMainParts::PostMainMessageLoopRun() {
  browser_context_.reset();
}

void DemoShellBrowserMainParts::PostDestroyThreads() {
}

}