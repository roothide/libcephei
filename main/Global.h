#import <UIKit/UIApplication.h>
#import <UIKit/UIApplication+Private.h>

// Are we in the system app? Before iOS 8, the only system app is SpringBoard. With the introduction
// of FrontBoard in iOS 8, other apps (e.g. PineBoard and Carousel) can be the system app.
// +[UIApplication registerAsSystemApp] will tell us if we’re in a system app, and the UIApplication
// subclass should also be the principal class of the bundle.
// Cephei avoids linking UIKit, so we need to be careful to not directly use UIKit symbols here.

// principalClass is a Class object, so inspect its class hierarchy rather than its metaclass.
#define IS_SYSTEM_APP (IS_APP_PROCESS() \
	&& [[NSBundle mainBundle].principalClass isSubclassOfClass:NSClassFromString(@"UIApplication")] \
	&& [[NSBundle mainBundle].principalClass respondsToSelector:@selector(registerAsSystemApp)] \
	&& (BOOL)[[NSBundle mainBundle].principalClass registerAsSystemApp])

//sandbox guard for ios18+
#include <libgen.h>
#include <string.h>
#include <mach-o/dyld.h>
static inline BOOL IS_APP_PROCESS(void)
{
	char executablePath[PATH_MAX] = {0};
	uint32_t size = sizeof(executablePath);
	if (_NSGetExecutablePath(executablePath, &size) != 0) {
		return NO;
	}
	char executableDir[PATH_MAX] = {0};
	dirname_r(executablePath, executableDir);
	size_t dirLength = strlen(executableDir);
	return dirLength >= 4 && memcmp(executableDir + dirLength - 4, ".app", 4) == 0;
}
