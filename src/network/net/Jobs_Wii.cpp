#include "network/net/Jobs_Wii.h"
#include "RVPackages/NintendoManagementProtocolClient.h"
#include "net/Server.h"
#include "sdk/RevoEX/nwc24/NWC24Config.h"

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
                SetStep(Step(
                    &JobDeleteOrphanedProfiles::StepGetProfiles,
                    "JobDeleteOrphanedProfiles::StepGetProfiles"
                ));
            } else {
                SetStep(Step(
                    &JobDeleteOrphanedProfiles::StepCompleteJob,
                    "JobDeleteOrphanedProfiles::StepCompleteJob"
                ));
            }
        } else {
            SetStep(Step(
                &JobDeleteOrphanedProfiles::StepCompleteJob,
                "JobDeleteOrphanedProfiles::StepCompleteJob"
            ));
        }
    } else {
        SetStep(Step(
            &JobDeleteOrphanedProfiles::StepCompleteJob,
            "JobDeleteOrphanedProfiles::StepCompleteJob"
        ));
    }
}

JobDeleteOrphanedProfiles::~JobDeleteOrphanedProfiles() {}

void JobDeleteOrphanedProfiles::StepGetProfiles() {
    if (unk64->CallGetConsoleUsernames(&unk68, unk58, &unkc0)) {
        unke0 = 300;
        SetStep(Step(
            &JobDeleteOrphanedProfiles::StepPrepareToDeleteProfiles,
            "JobDeleteOrphanedProfiles::StepPrepareToDeleteProfiles"
        ));
    } else
        CompleteJob(false);
}

void JobDeleteOrphanedProfiles::StepPrepareToDeleteProfiles() {}

void JobDeleteOrphanedProfiles::StepCompleteJob() { CompleteJob(false); }
void JobDeleteOrphanedProfiles::CompleteJob(bool) { SetToComplete(); }