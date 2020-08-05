#include "shell_demo/common/demo_shell_content_client.h"

#include "base/command_line.h"
#include "base/values.h"
#include "content/public/common/content_switches.h"
#include "content/public/common/user_agent.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/resource/resource_bundle.h"

namespace content{

DemoShellContentClient::DemoShellContentClient() = default;

DemoShellContentClient::~DemoShellContentClient() = default;

base::string16 DemoShellContentClient::GetLocalizedString(int message_id) {
  return l10n_util::GetStringUTF16(message_id);
}

base::StringPiece DemoShellContentClient::GetDataResource(
    int resource_id,
    ui::ScaleFactor scale_factor) {
  return ui::ResourceBundle::GetSharedInstance().GetRawDataResourceForScale(
    resource_id, scale_factor);
}

base::RefCountedMemory* DemoShellContentClient::GetDataResourceBytes(
  int resource_id) {
  return ui::ResourceBundle::GetSharedInstance().LoadDataResourceBytes(
    resource_id);
}

gfx::Image& DemoShellContentClient::GetNativeImageNamed(int resource_id){
  return ui::ResourceBundle::GetSharedInstance().GetNativeImageNamed(
    resource_id);
}

base::DictionaryValue DemoShellContentClient::GetNetLogConstants() {
  base::DictionaryValue client_constants;
  client_constants.SetString("name", "demo_shell");
  client_constants.SetString(
      "command_line",
      base::CommandLine::ForCurrentProcess()->GetCommandLineString());
  base::DictionaryValue constants;
  constants.SetKey("clientInfo", std::move(client_constants));
  return constants;
}

blink::OriginTrialPolicy* DemoShellContentClient::GetOriginTrialPolicy(){
  return nullptr;
}

}