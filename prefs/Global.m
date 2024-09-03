@import Foundation;

#include <roothide.h>

NSBundle *cepheiGlobalBundle;

__attribute__((constructor))
static void cepheiInit() {
	cepheiGlobalBundle = [NSBundle bundleWithPath:jbroot(@"/Library/PreferenceBundles/Cephei.bundle")];
}
