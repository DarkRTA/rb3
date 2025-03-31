#include "network/net/Jobs_Wii.h"
#include "Core/StepSequenceJob.h"
#include "RVPackages/NintendoManagementProtocolClient.h"
#include "Services/AccountManagementClient.h"
#include "Services/BackEndServices.h"
#include "net/Server.h"
#include "obj/ObjMacros.h"
#include "os/PlatformMgr.h"
#include "sdk/RevoEX/nwc24/NWC24Config.h"

#define SET_STEP(func) SetStep(Step(static_cast<JobStateFunc>(&func), #func));

JobDeleteOrphanedProfiles::JobDeleteOrphanedProfiles(
    Quazal::NintendoManagementProtocolClient *client
)
    : Quazal::StepSequenceJob(Quazal::DebugString()), unk58(0), unk60(0), unk64(0),
      unkcc(0, 20) {
    if (NWC24GetMyUserId(unk58) == 0) {
        unk60 = TheServer->GetAccountManagementClient();
        if (unk60) {
            unk64 = client;
            if (unk64) {
                SET_STEP(JobDeleteOrphanedProfiles::StepGetProfiles);
            } else {
                SET_STEP(JobDeleteOrphanedProfiles::StepCompleteJob);
            }
        } else {
            SET_STEP(JobDeleteOrphanedProfiles::StepCompleteJob);
        }
    } else {
        SET_STEP(JobDeleteOrphanedProfiles::StepCompleteJob);
    }
}

JobDeleteOrphanedProfiles::~JobDeleteOrphanedProfiles() {}

void JobDeleteOrphanedProfiles::StepGetProfiles() {
    if (unk64->CallGetConsoleUsernames(&unk68, unk58, &unkc0)) {
        unke0 = 300;
        SET_STEP(JobDeleteOrphanedProfiles::StepPrepareToDeleteProfiles);
    } else
        CompleteJob(false);
}

void JobDeleteOrphanedProfiles::StepPrepareToDeleteProfiles() {
    Quazal::CallContext::_State s = unk68.GetState();
    if (s == 1) {
        if (unke0 != 0) {
            SetToWaiting(100);
            unke0--;
        } else {
            CompleteJob(false);
        }
    } else if (s == 2) {
        unkc8 = unkc0.end();
        SET_STEP(JobDeleteOrphanedProfiles::StepPickNextProfile);
    } else {
        unsigned int code = unk68.unk20.m_iReturnCode;
        MILO_LOG(
            "Encountered qError [%s]\n",
            (const char *)Quazal::BackEndServices::FormatQErrorCodeString("", code)
                .m_szContent
        );
        CompleteJob(false);
    }
}

void JobDeleteOrphanedProfiles::StepCompleteJob() { CompleteJob(false); }
void JobDeleteOrphanedProfiles::CompleteJob(bool) { SetToComplete(); }

JobCreateProfile::JobCreateProfile(const char *cc, int i2)
    : Quazal::StepSequenceJob(Quazal::DebugString()), unk74(cc), unk78(0), unk7c(4),
      unk108(i2) {
    if (!cc || !*cc || !TheServer->IsConnected()
        || !TheServer->GetAccountManagementClient()) {
        SET_STEP(JobCreateProfile::StepCompleteJob);
        return;
    } else {
        unkd8.Start();
        SET_STEP(JobCreateProfile::StepCheckDWC);
    }
}

JobCreateProfile::~JobCreateProfile() {}

DataNode JobCreateProfile::OnMsg(const DWCProfanityResultMsg &msg) {
    if (msg.Success()) {
        if (msg->Int(3) != 0) {
            CompleteJob(2);
        } else {
            SET_STEP(JobCreateProfile::StepCheckRockCentral);
            Resume();
        }
    } else {
        CompleteJob(4);
    }
    return 1;
}

void JobCreateProfile::StepCompleteJob() {
    unk78 = 0;
    CompleteJob(4);
}

void JobCreateProfile::CompleteJob(int i) {
    unk7c = i;
    SetToComplete();
}

BEGIN_HANDLERS(JobCreateProfile)
    HANDLE_MESSAGE(DWCProfanityResultMsg)
    HANDLE_CHECK(0x514)
END_HANDLERS

JobDeleteProfile::JobDeleteProfile(unsigned int ui)
    : Quazal::StepSequenceJob(Quazal::DebugString()), unk5c(ui) {
    if (ui == 0 || !TheServer->IsConnected()
        || !TheServer->GetAccountManagementClient()) {
        SET_STEP(JobDeleteProfile::StepCompleteJob);
        return;
    } else {
        SET_STEP(JobDeleteProfile::StepDeleteProfile);
    }
}

JobDeleteProfile::~JobDeleteProfile() {}

void JobDeleteProfile::StepDeleteProfile() {
    Quazal::AccountManagementClient *client = TheServer->GetAccountManagementClient();
    bool remove = false;
    if (client) {
        remove = client->DeleteAccount(&unk60, unk5c);
    }
    if (remove) {
        unkb8 = 300;
        SET_STEP(JobDeleteProfile::StepDeleteProfile)
    } else
        CompleteJob(false);
}

void JobDeleteProfile::StepProcessResults() {
    Quazal::CallContext::_State s = unk60.GetState();
    if (s == 1) {
        if (unkb8 != 0) {
            SetToWaiting(100);
            unkb8--;
        } else
            CompleteJob(false);
    } else if (s == 2) {
        CompleteJob(true);
    } else
        CompleteJob(false);
}

void JobDeleteProfile::StepCompleteJob() { CompleteJob(false); }

void JobDeleteProfile::CompleteJob(bool b) {
    unk58 = b;
    SetToComplete();
}