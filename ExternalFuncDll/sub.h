#include "../Calculater/token.h"

#ifdef SUBDLL
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif

extern ::std::vector<::std::string> FuncNames;

extern"C" {
	FCMarks::FCValue DLL testSub(void* any);
	DLL void giveName(void*);
}