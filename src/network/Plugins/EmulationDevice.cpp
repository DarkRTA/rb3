#include "EmulationDevice.h"

namespace Quazal {
    EmulationDevice::EmulationDevice()
        : m_bEnabled(false), m_uiProtocolHeaderSize(0), m_uiBandwidth(-1), m_uiLatency(0),
          m_uiJitter(0), m_rPacketDropProbability(0.0f) {}
    EmulationDevice::~EmulationDevice() {}

    void EmulationDevice::Enable() {
        m_bEnabled = true;
    }

    void EmulationDevice::SetLatency(unsigned int latency) {
        m_uiLatency = latency;
    }

    void EmulationDevice::SetJitter(unsigned int jitter) {
        m_uiJitter = jitter;
    }

    void EmulationDevice::SetBandwidth(unsigned int bandwidth) {
        m_uiBandwidth = bandwidth;
    }

    void EmulationDevice::SetPacketDropProbability(float probability) {
        m_rPacketDropProbability = probability;
    }

    unsigned int EmulationDevice::GetLatency() {
        return m_uiLatency;
    }

    unsigned int EmulationDevice::GetJitter() {
        return m_uiJitter;
    }

    unsigned int EmulationDevice::GetBandwidth() {
        return m_uiBandwidth;
    }

    float EmulationDevice::GetPacketDropProbability() {
        return m_rPacketDropProbability;
    }
}