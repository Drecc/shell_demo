#ifndef CONTENT_DEMO_SHELL_BROWSER_SHELL_BROWSER_MAIN_H_
#define CONTENT_DEMO_SHELL_BROWSER_SHELL_BROWSER_MAIN_H_

#include <memory>

namespace content {
class BrowserMainRunner;
struct MainFunctionParams;
}

int DemoShellBrowserMain(
    const content::MainFunctionParams& parameters,
    const std::unique_ptr<content::BrowserMainRunner>& main_runner);

#endif  // CONTENT_DEMO_SHELL_BROWSER_SHELL_BROWSER_MAIN_H_
