#pragma once

class EntityUploader {
public:
    virtual void Init();
    virtual void Poll();
};

extern EntityUploader *TheEntityUploader;
