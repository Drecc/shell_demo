#include "base/android/base_jni_onload.h"
#include "base/android/jni_android.h"
#include "base/logging.h"
#include "content/public/app/content_jni_onload.h"
#include "content/public/app/content_main.h"
#include "shell_demo/app/demo_shell_content_main_delegate.h"

JNI_EXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
  base::android::InitVM(vm);
  if (!base::android::OnJNIOnLoadInit())
    return -1;
  content::SetContentMainDelegate(new content::DemoShellContentMainDelegate());
  LOG(INFO) << "JNI_OnLoad finished";
  return JNI_VERSION_1_4;
}
