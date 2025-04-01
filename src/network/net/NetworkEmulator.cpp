#include "network/net/NetworkEmulator.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"

NetworkEmulator::NetworkEmulator()
    : mInBandwidth(-1), mOutBandwidth(-1), mInJitter(0), mOutJitter(0), mInLatency(0),
      mOutLatency(0), mInDropProb(0), mOutDropProb(0), mEnabled(0) {
    SetName("emulator", ObjectDir::Main());
    // assigning emulation devices here
    DataArray *cfg = SystemConfig("net", "emulator");
    DataArray *bandwidthArr = cfg->FindArray("bandwidth");
    mInBandwidth = bandwidthArr->Int(1);
    mOutBandwidth = bandwidthArr->Int(2);
    DataArray *jitterArr = cfg->FindArray("jitter");
    mInJitter = jitterArr->Int(1);
    mOutJitter = jitterArr->Int(2);
    DataArray *latencyArr = cfg->FindArray("latency");
    mInLatency = latencyArr->Int(1);
    mOutLatency = latencyArr->Int(2);
    DataArray *dropprobArr = cfg->FindArray("dropprob");
    mInDropProb = dropprobArr->Int(1);
    mOutDropProb = dropprobArr->Int(2);
}

void NetworkEmulator::Enable() {
    mEnabled = 1;
    if (!mInDevice->Enabled()) {
        mInDevice->Enable();
        mOutDevice->Enable();
    }
    mInDevice->SetBandwidth(mInBandwidth);
    mOutDevice->SetBandwidth(mOutBandwidth);
    mInDevice->SetJitter(mInJitter);
    mOutDevice->SetJitter(mOutJitter);
    mInDevice->SetLatency(mInLatency);
    mOutDevice->SetLatency(mOutLatency);
    mInDevice->SetPacketDropProbability(mInDropProb / 100.0f);
    mOutDevice->SetPacketDropProbability(mOutDropProb / 100.0f);
}

void NetworkEmulator::Disable() {
    mEnabled = 0;
    mInDevice->SetBandwidth(-1);
    mOutDevice->SetBandwidth(-1);
    mInDevice->SetJitter(0);
    mOutDevice->SetJitter(0);
    mInDevice->SetLatency(0);
    mOutDevice->SetLatency(0);
    mInDevice->SetPacketDropProbability(0);
    mOutDevice->SetPacketDropProbability(0);
}

void NetworkEmulator::SetBandwidth(int in, int out) {
    mInBandwidth = in;
    mOutBandwidth = out;
    if (mEnabled) {
        mInDevice->SetBandwidth(mInBandwidth);
        mOutDevice->SetBandwidth(mOutBandwidth);
    }
}

void NetworkEmulator::SetJitter(int in, int out) {
    mInJitter = in;
    mOutJitter = out;
    if (mEnabled) {
        mInDevice->SetJitter(mInJitter);
        mOutDevice->SetJitter(mOutJitter);
    }
}

void NetworkEmulator::SetLatency(int in, int out) {
    mInLatency = in;
    mOutLatency = out;
    if (mEnabled) {
        mInDevice->SetLatency(mInLatency);
        mOutDevice->SetLatency(mOutLatency);
    }
}

void NetworkEmulator::SetPacketDropProbability(int in, int out) {
    mInDropProb = in;
    mOutDropProb = out;
    if (mEnabled) {
        mInDevice->SetPacketDropProbability(in / 100.0f);
        mOutDevice->SetPacketDropProbability(out / 100.0f);
    }
}

BEGIN_HANDLERS(NetworkEmulator)
    HANDLE_ACTION(enable, Enable())
    HANDLE_ACTION(disable, Disable())
    HANDLE_ACTION(set_bandwidth, SetBandwidth(_msg->Int(2), _msg->Int(3)))
    HANDLE_ACTION(set_jitter, SetJitter(_msg->Int(2), _msg->Int(3)))
    HANDLE_ACTION(set_latency, SetLatency(_msg->Int(2), _msg->Int(3)))
    HANDLE_ACTION(set_dropprob, SetPacketDropProbability(_msg->Int(2), _msg->Int(3)))
    HANDLE_CHECK(0xA1)
END_HANDLERS