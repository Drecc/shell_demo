#include "shell_demo/common/demo_shell_switches.h"

#include "base/command_line.h"
#include "base/strings/string_split.h"

namespace switches {

// Makes Content Shell use the given path for its data directory.
const char kContentShellDataPath[] = "data-path";

// The directory breakpad should store minidumps in.
const char kCrashDumpsDir[] = "crash-dumps-dir";

// Exposes the window.internals object to JavaScript for interactive development
// and debugging of web tests that rely on it.
const char kExposeInternalsForTesting[] = "expose-internals-for-testing";

// Registers additional font files on Windows (for fonts outside the usual
// %WINDIR%\Fonts location). Multiple files can be used by separating them
// with a semicolon (;).
const char kRegisterFontFiles[] = "register-font-files";

// Size for the content_shell's host window (i.e. "800x600").
const char kContentShellHostWindowSize[] = "content-shell-host-window-size";

// Hides toolbar from content_shell's host window.
const char kContentShellHideToolbar[] = "content-shell-hide-toolbar";


}  // namespace switches
