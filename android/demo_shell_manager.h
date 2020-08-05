#ifndef CONTENT_DEMO_SHELL_ANDROID_SHELL_MANAGER_H_
#define CONTENT_DEMO_SHELL_ANDROID_SHELL_MANAGER_H_

#include <jni.h>

#include "base/android/jni_android.h"
#include "base/android/scoped_java_ref.h"

class DemoShell;

namespace cc {
class Layer;
}

namespace content {

// Creates an Android specific shell view, which is our version of a shell
// window.  This view holds the controls and content views necessary to
// render a shell window.  Returns the java object representing the shell view.
// object.
base::android::ScopedJavaLocalRef<jobject> CreateShellView(DemoShell* shell);

// Removes a previously created shell view.
void RemoveShellView(const base::android::JavaRef<jobject>& shell_view);

void ShellAttachLayer(cc::Layer* layer);
void ShellRemoveLayer(cc::Layer* layer);

// Destroys the ShellManager on app exit. Must not use the above functions
// after this is called.
void DestroyShellManager();

}  // namespace content

#endif  // CONTENT_DEMO_SHELL_ANDROID_SHELL_MANAGER_H_