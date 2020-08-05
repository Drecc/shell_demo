#ifndef CONTENT_DEMO_SHELL_BROWSER_DEMO_SHELL_BROWSER_CONTEXT_H_
#define CONTENT_DEMO_SHELL_BROWSER_DEMO_SHELL_BROWSER_CONTEXT_H_

#include <memory>

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/content_browser_client.h"
#include "content/public/browser/resource_context.h"
#include "net/url_request/url_request_job_factory.h"
#include "shell_demo/browser/demo_shell_url_request_context_getter.h"

namespace content {

class BackgroundSyncController;
class DemoShellDownloadManagerDelegate;
class DemoShellPermissionManager;
class DownloadManagerDelegate;
class PermissionControllerDelegate;

#if !defined(OS_ANDROID)
class ZoomLevelDelegate;
#endif  // !defined(OS_ANDROID)

class DemoShellBrowserContext : public BrowserContext {
public:
  DemoShellBrowserContext(bool off_the_record,
                      bool delay_services_creation = false);
  ~DemoShellBrowserContext() override;

  // BrowserContext
  base::FilePath GetPath() override;
#if !defined(OS_ANDROID)
  std::unique_ptr<ZoomLevelDelegate> CreateZoomLevelDelegate(
      const base::FilePath& partition_path) override;
#endif  // !defined(OS_ANDROID)
  bool IsOffTheRecord() override;
  DownloadManagerDelegate* GetDownloadManagerDelegate() override;
  ResourceContext* GetResourceContext() override;
  BrowserPluginGuestManager* GetGuestManager() override;
  storage::SpecialStoragePolicy* GetSpecialStoragePolicy() override;
  PushMessagingService* GetPushMessagingService() override;
  StorageNotificationService* GetStorageNotificationService() override;
  SSLHostStateDelegate* GetSSLHostStateDelegate() override;
  PermissionControllerDelegate* GetPermissionControllerDelegate() override;
  ClientHintsControllerDelegate* GetClientHintsControllerDelegate() override;
  BackgroundFetchDelegate* GetBackgroundFetchDelegate() override;
  BackgroundSyncController* GetBackgroundSyncController() override;
  BrowsingDataRemoverDelegate* GetBrowsingDataRemoverDelegate() override;
  ContentIndexProvider* GetContentIndexProvider() override;

protected:
  // Contains URLRequestContextGetter required for resource loading.
  class DemoShellResourceContext : public ResourceContext {
   public:
    DemoShellResourceContext();
    ~DemoShellResourceContext() override;

    DISALLOW_COPY_AND_ASSIGN(DemoShellResourceContext);
  };

  std::unique_ptr<DemoShellResourceContext> resource_context_;
  std::unique_ptr<DemoShellDownloadManagerDelegate> download_manager_delegate_;
  std::unique_ptr<DemoShellPermissionManager> permission_manager_;
  std::unique_ptr<BackgroundSyncController> background_sync_controller_;

private:
  void InitWhileIOAllowed();
  bool off_the_record_;
  base::FilePath path_;
  DISALLOW_COPY_AND_ASSIGN(DemoShellBrowserContext);
};

}  // namespace content

#endif  // CONTENT_DEMO_SHELL_BROWSER_DEMO_SHELL_BROWSER_CONTEXT_H_
