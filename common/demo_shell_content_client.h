#ifndef CONTENT_DEMO_SHELL_COMMON_DEMO_SHELL_CONTENT_CLIENT_H_
#define CONTENT_DEMO_SHELL_COMMON_DEMO_SHELL_CONTENT_CLIENT_H_

#include <string>

#include "base/compiler_specific.h"
#include "content/public/common/content_client.h"

namespace content {

std::string GetDemoShellUserAgent();

class DemoShellContentClient : public content::ContentClient {
public:
  DemoShellContentClient();
  ~DemoShellContentClient() override;

  base::string16 GetLocalizedString(int message_id) override;
  base::StringPiece GetDataResource(
      int resource_id,
      ui::ScaleFactor scale_factor) override;
  base::RefCountedMemory* GetDataResourceBytes(
      int resource_id) override;
  gfx::Image& GetNativeImageNamed(int resource_id) override;
  base::DictionaryValue GetNetLogConstants() override;
  blink::OriginTrialPolicy* GetOriginTrialPolicy() override;
private:

};

}

#endif