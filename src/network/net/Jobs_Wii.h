#pragma once
#include "Platform/qStd.h"
#include "network/Protocol/ProtocolCallContext.h"
#include "network/Core/StepSequenceJob.h"
#include "network/RVPackages/NintendoManagementProtocolClient.h"
#include "network/ddl/ResultRange.h"
#include "network/ddl/AccountInfo.h"

class JobDeleteOrphanedProfiles : public Quazal::StepSequenceJob {
public:
    JobDeleteOrphanedProfiles(Quazal::NintendoManagementProtocolClient *);
    virtual ~JobDeleteOrphanedProfiles();

    void StepGetProfiles();
    void StepPrepareToDeleteProfiles();
    void StepPickNextProfile();
    void StepLookUpProfile();
    void StepDeleteProfile();
    void StepCompleteJob();
    void CompleteJob(bool);

    unsigned long long unk58;
    int unk60;
    Quazal::NintendoManagementProtocolClient *unk64;
    Quazal::ProtocolCallContext unk68;
    Quazal::qList<Quazal::String> unkc0;
    int unkc8; // some one-word struct
    Quazal::ResultRange unkcc;
    Quazal::qList<Quazal::BasicAccountInfo> unkd8;
    int unke0;
};