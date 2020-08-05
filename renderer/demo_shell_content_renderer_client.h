#ifndef CONTENT_SHELL_RENDERER_SHELL_CONTENT_RENDERER_CLIENT_H_
#define CONTENT_SHELL_RENDERER_SHELL_CONTENT_RENDERER_CLIENT_H_

#include <memory>
#include <string>

#include "base/compiler_specific.h"
#include "build/build_config.h"
#include "content/public/renderer/content_renderer_client.h"
#include "media/mojo/buildflags.h"

namespace web_cache {
class WebCacheImpl;
}

namespace content {

class DemoShellContentRendererClient : public ContentRendererClient {
public:
  DemoShellContentRendererClient();
  ~DemoShellContentRendererClient() override;

  // ContentRendererClient
  void RenderThreadStarted() override;
  void RenderViewCreated(RenderView* render_view) override;
  bool HasErrorPage(int http_status_code) override;
  void PrepareErrorPage(RenderFrame* render_frame,
                        const blink::WebURLError& error,
                        const std::string& http_method,
                        std::string* error_html) override;
  void PrepareErrorPageForHttpStatusError(content::RenderFrame* render_frame,
                                          const GURL& unreachable_url,
                                          const std::string& http_method,
                                          int http_status,
                                          std::string* error_html) override;
  bool IsPluginAllowedToUseDevChannelAPIs() override;
  void DidInitializeWorkerContextOnWorkerThread(
      v8::Local<v8::Context> context) override;

};

}  // namespace content

#endif  // CONTENT_SHELL_RENDERER_SHELL_CONTENT_RENDERER_CLIENT_H_
