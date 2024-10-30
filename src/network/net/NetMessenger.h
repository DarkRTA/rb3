#pragma once

class NetMessenger {
public:
    NetMessenger();
    ~NetMessenger();

    unsigned int mLastSender; // 0x0
};

extern NetMessenger TheNetMessenger;