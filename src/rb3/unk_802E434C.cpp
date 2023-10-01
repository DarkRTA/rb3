#include "file.hpp"

int File::sOpenCount[4];

// fn_802E73DC
File::File(){
	sOpenCount[0]++;
}

// fn_802E738C
File::~File(){
	sOpenCount[0]--;
}