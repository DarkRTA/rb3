#ifndef PLUGINS_EMULATIONDEVICE_H
#define PLUGINS_EMULATIONDEVICE_H

#include "Platform/RootObject.h"

namespace Quazal {
    class EmulationDevice : public RootObject {
    public:
        EmulationDevice();
        virtual ~EmulationDevice();
        virtual void Enable();

        void SetLatency(unsigned int);
        void SetJitter(unsigned int);
        void SetBandwidth(unsigned int);
        void SetPacketDropProbability(float);
        unsigned int GetLatency();
        unsigned int GetJitter();
        unsigned int GetBandwidth();
        float GetPacketDropProbability();

    private:
        bool m_bEnabled; // 0x4
        unsigned int m_uiProtocolHeaderSize; // 0x8
        unsigned int m_uiBandwidth; // 0xC
        unsigned int m_uiLatency; // 0x10
        unsigned int m_uiJitter; // 0x14
        float m_rPacketDropProbability; // 0x18
    };
}

#endif // PLUGINS_EMULATIONDEVICE_H