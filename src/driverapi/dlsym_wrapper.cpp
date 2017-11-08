#include <string>
#define __USE_GNU
#include <dlfcn.h>
#include <stdio.h>
extern "C" {
void * __libc_dlopen(const char *filename, int flags);
void *dlopen(const char *filename, int flags) {
	if (filename != NULL) {
		void * ret;
		std::string tmp = std::string((char *)filename);
		ret =  __libc_dlopen(filename, flags);
		fprintf(stderr, "DLOPEN: %s HANDLE: %p\n", filename, ret);
		return ret;
	} else {
		return __libc_dlopen(filename, flags);
	}
}
void * __libc_dlsym(void * handle, const char * symbol);
void * dlsym(void * handle, const char * symbol) {
	if (symbol != NULL) {
		fprintf(stderr, "DLSYMBOL: %s, HANDLE: %p\n", symbol, handle);
	}
	return __libc_dlsym(handle, symbol);
}
}