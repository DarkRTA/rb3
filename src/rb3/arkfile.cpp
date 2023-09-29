#include <rb3/arkfile.hpp>

u32 ArkFile::stub_802E76D8() {
	return 0;
}

u32 ArkFile::Seek(int offset, int mode) {
	switch(mode) {
		case 0:
			this->fpos = offset;
			break;
		case 1:
			this->fpos += offset;
			break;
		case 2:
			this->fpos = this->filesize + offset;
			break;
		default:
			break;
	}
	return this->fpos;
}

u32 ArkFile::FilePos()
{
	return this->fpos;
}


bool ArkFile::EndOfFile() {
	return (this->filesize - this->fpos) == 0;
}
