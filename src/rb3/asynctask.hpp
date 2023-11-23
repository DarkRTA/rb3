#ifndef RB3_ASYNCTASK_HPP
#define RB3_ASYNCTASK_HPP
#include "arkfile.hpp"

class AsyncTask {
public:
	int unk0;
	int unk4;
	int unk8;
	int unkc;
	void* unk10;
	char* unk14;
	ArkFile* unk18;

	AsyncTask(ArkFile*, void*, int, int, int, int, const char*);
	bool FillData();
};

#endif