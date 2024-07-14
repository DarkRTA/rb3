#ifndef RUNTIME_MWRTTI_H
#define RUNTIME_MWRTTI_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct type_info_struct type_info_struct;

typedef struct type_info_base_list {
	type_info_struct *baseTypeInfo;
	long offset;
}	type_info_base_list;

typedef struct type_info_ambighead {
	void* baseTypeInfo;
	long offset;
	long bases;
}	type_info_ambighead;

struct type_info_struct {
	char* typeName;
	type_info_base_list* baseList;
};

typedef struct RTTIVTableHeader {
	type_info_struct* typeInfo;
	long offset;
}	RTTIVTableHeader;

void* __get_typeid(void*, long);
void* __dynamic_cast(void*, int, type_info_struct*, type_info_struct*, bool);

#ifdef __cplusplus
}
#endif

#endif
