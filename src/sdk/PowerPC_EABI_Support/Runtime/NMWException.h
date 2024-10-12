#ifndef _NMWEXCEPTION
#define _NMWEXCEPTION

#include "__ppc_eabi_linker.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef short vbase_ctor_arg_type;
typedef char local_cond_type;

typedef struct CatchInfo {
	void* location;
	void* typeinfo;
	void* dtor;
	void* sublocation;
	long pointercopy;
	void* stacktop;
} CatchInfo;

extern void	__end__catch(CatchInfo* catchinfo);
extern void __throw(char* throwtype, void* location, void* dtor);
extern char __throw_catch_compare(const char* throwtype, const char* catchtype, long* offset_result);
extern void	__unexpected(CatchInfo* catchinfo);

extern int __register_fragment(struct __eti_init_info* info, char* TOC);
extern void __unregister_fragment(int fragmentID);

#ifdef __cplusplus
}
#endif

#endif // _NMWEXCEPTION
