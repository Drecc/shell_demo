#include "shell_demo/browser/shell.h"

#include <stddef.h>

#include <map>
#include <string>
#include <utility>

#include "base/command_line.h"
#include "base/location.h"
#include "base/macros.h"
#include "base/no_destructor.h"
#include "base/run_loop.h"
#include "base/single_thread_task_runner.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_util.h"
#include "base/strings/stringprintf.h"
#include "base/strings/utf_string_conversions.h"
#include "base/threading/thread_task_runner_handle.h"
#include "build/build_config.h"
#include "content/public/browser/web_contents.h"
#include "content/public/common/content_switches.h"

namespace content {

// Null until/unless the default main message loop is running.
base::NoDestructor<base::OnceClosure> g_quit_main_message_loop;

const int kDefaultTestWindowWidthDip = 800;
const int kDefaultTestWindowHeightDip = 600;

DemoShell::DemoShell(std::unique_ptr<WebContents> web_contents,
             bool should_set_delegate)
    : web_contents_(std::move(web_contents)),
      window_(nullptr) {

}

DemoShell::~DemoShell() {
  PlatformCleanUp();

  // Always destroy WebContents before calling PlatformExit(). WebContents
  // destruction sequence may depend on the resources destroyed in
  // PlatformExit() (e.g. the display::Screen singleton).
  web_contents_->SetDelegate(nullptr);
  web_contents_.reset();


if (*g_quit_main_message_loop)
    std::move(*g_quit_main_message_loop).Run();

}

DemoShell* DemoShell::CreateShell(std::unique_ptr<WebContents> web_contents,
                          const gfx::Size& initial_size,
                          bool should_set_delegate) {
  DemoShell* shell = new DemoShell(std::move(web_contents), should_set_delegate);
  shell->PlatformCreateWindow(initial_size.width(), initial_size.height());
  shell->PlatformSetContents();

  return shell;
}

void DemoShell::SetMainMessageLoopQuitClosure(base::OnceClosure quit_closure) {
  *g_quit_main_message_loop = std::move(quit_closure);
}

void DemoShell::Initialize() {
  PlatformInitialize(GetShellDefaultSize());
}

DemoShell* DemoShell::CreateNewWindow(BrowserContext* browser_context,
                              const GURL& url,
                              const scoped_refptr<SiteInstance>& site_instance,
                              const gfx::Size& initial_size) {
  WebContents::CreateParams create_params(browser_context, site_instance);
  std::unique_ptr<WebContents> web_contents =
      WebContents::Create(create_params);
  DemoShell* shell =
      CreateShell(std::move(web_contents), GetShellDefaultSize(),
                  true /* should_set_delegate */);
  if (!url.is_empty())
    shell->LoadURLForFrame(url, std::string(), ui::PageTransitionFromInt(ui::PAGE_TRANSITION_TYPED | ui::PAGE_TRANSITION_FROM_ADDRESS_BAR));
  return shell;
}

void DemoShell::LoadURLForFrame(const GURL& url,
                            const std::string& frame_name,
                            ui::PageTransition transition_type) {
  NavigationController::LoadURLParams params(url);
  params.frame_name = frame_name;
  params.transition_type = transition_type;
  web_contents_->GetController().LoadURLWithParams(params);
  web_contents_->Focus();
}

gfx::Size DemoShell::GetShellDefaultSize() {
  return gfx::Size(kDefaultTestWindowWidthDip, kDefaultTestWindowHeightDip);
}

}  // namespace content
