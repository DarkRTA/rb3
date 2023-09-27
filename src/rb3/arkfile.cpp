#include <rb3/arkfile.hpp>

u32 ArkFile::Seek(u32 offset, u32 mode) {
	if (mode == 0) {
		this->fpos = offset;
	}
	else if (mode == 1) {
		this->fpos = this->fpos + offset;
	}
	else if (mode == 2) {
		this->fpos = this->filesize + offset;
	}
	return this->fpos;
}

u32 ArkFile::FilePos() {
	return this->fpos;
}
