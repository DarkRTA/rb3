/*
    Compile unit: C:\rockband2\system\src\synth\StreamReceiver.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80591690 -> 0x80592290
*/
class StreamReceiver * (* sFactory)(int, int, unsigned char); // size: 0x4, address: 0x80A54710
// Range: 0x80591690 -> 0x80591720
class StreamReceiver * StreamReceiver::New(int numBuffers /* r29 */, int sampleRate /* r30 */, unsigned char slip /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class StreamReceiver * (* sFactory)(int, int, unsigned char);
}

// Range: 0x80591720 -> 0x80591800
void * StreamReceiver::StreamReceiver(class StreamReceiver * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__14StreamReceiver;
}

// Range: 0x80591800 -> 0x80591840
void * StreamReceiver::~StreamReceiver(class StreamReceiver * const this /* r31 */) {}

// Range: 0x80591840 -> 0x8059184C
int StreamReceiver::BytesWriteable() {}

// Range: 0x8059184C -> 0x80591974
void StreamReceiver::WriteData(class StreamReceiver * const this /* r27 */, void * data /* r28 */, int bytes /* r31 */) {
    // Local variables
    int bytesToEnd; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80591974 -> 0x80591ABC
void StreamReceiver::ClearAtEndData(class StreamReceiver * const this /* r28 */) {
    // Local variables
    int firstWipeSize; // r30
    int secondWipeSize; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80591ABC -> 0x80591AD4
unsigned char StreamReceiver::Ready() {}

// Range: 0x80591AD4 -> 0x80591B88
void StreamReceiver::Play(class StreamReceiver * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80591B88 -> 0x80591C38
void StreamReceiver::Stop(class StreamReceiver * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80591C38 -> 0x805921E0
void StreamReceiver::Poll(class StreamReceiver * const this /* r31 */) {
    // Local variables
    int activeBuf; // r28

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805921E0 -> 0x80592240
void StreamReceiver::EndData(class StreamReceiver * const this /* r31 */) {}

// Range: 0x80592240 -> 0x80592290
int StreamReceiver::GetBytesPlayed() {
    // Local variables
    int bytesSent; // r5
    int bytesPlayed; // r3
}

struct {
    // total size: 0x60
} __vt__14StreamReceiver; // size: 0x60, address: 0x8091FC78

