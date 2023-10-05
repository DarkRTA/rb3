#include <rb3/arkfile.hpp>

bool ArkFile::Write(const void* a, int b) {
	return 0;
}

unsigned int ArkFile::Seek(int offset, int mode) {
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

unsigned int ArkFile::Tell()
{
	return this->fpos;
}

void ArkFile::Flush(){ }


bool ArkFile::Eof() {
	return (this->filesize - this->fpos) == 0;
}
