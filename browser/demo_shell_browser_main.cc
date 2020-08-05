#include "shell_demo/browser/demo_shell_browser_main.h"

#include <iostream>
#include <memory>

#include "base/logging.h"
#include "build/build_config.h"
#include "content/public/browser/browser_main_runner.h"

int DemoShellBrowserMain(
    const content::MainFunctionParams& parameters,
    const std::unique_ptr<content::BrowserMainRunner>& main_runner) {
  int exit_code = main_runner->Initialize(parameters);
  DCHECK_LT(exit_code, 0)
      << "BrowserMainRunner::Initialize failed in ShellBrowserMain";

  if (exit_code >= 0)
    return exit_code;

#if !defined(OS_ANDROID)
  exit_code = main_runner->Run();

  main_runner->Shutdown();
#endif

  return exit_code;
}
