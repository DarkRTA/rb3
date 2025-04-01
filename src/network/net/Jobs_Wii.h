#pragma once
#include "Platform/String.h"
#include "Platform/qStd.h"
#include "Services/AccountManagementClient.h"
#include "network/Protocol/ProtocolCallContext.h"
#include "network/Core/StepSequenceJob.h"
#include "network/RVPackages/NintendoManagementProtocolClient.h"
#include "network/ddl/ResultRange.h"
#include "network/ddl/AccountInfo.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/PlatformMgr.h"

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
    Quazal::AccountManagementClient *unk60;
    Quazal::NintendoManagementProtocolClient *unk64;
    Quazal::ProtocolCallContext unk68;
    Quazal::qList<Quazal::String> unkc0;
    Quazal::qList<Quazal::String>::iterator unkc8; // some one-word struct
    Quazal::ResultRange unkcc;
    Quazal::qList<Quazal::BasicAccountInfo> unkd8;
    int unke0;
};

class JobEnumerateFriends : public Quazal::StepSequenceJob {
public:
    JobEnumerateFriends(class WiiFriendList *, Quazal::NintendoManagementProtocolClient *);
    virtual ~JobEnumerateFriends();
};

class JobSendMessage : public Quazal::StepSequenceJob {
public:
    JobSendMessage(int, const char *, const char *, int);
    virtual ~JobSendMessage();
};

class JobEnumerateMessages : public Quazal::StepSequenceJob {
public:
    JobEnumerateMessages(class WiiMessageList *);
    virtual ~JobEnumerateMessages();
};

class JobCreateProfile : public Quazal::StepSequenceJob, public Hmx::Object {
public:
    JobCreateProfile(const char *, int);
    virtual ~JobCreateProfile();
    virtual DataNode Handle(DataArray *, bool);

    void StepCompleteJob();
    void StepCheckDWC();
    void StepCheckRockCentral();
    void CompleteJob(int);

    DataNode OnMsg(const DWCProfanityResultMsg &);

    Quazal::String unk74; // 0x74
    int unk78;
    int unk7c;
    Quazal::ProtocolCallContext unk80;
    Timer unkd8;
    int unk108;
};

class JobDeleteProfile : public Quazal::StepSequenceJob {
public:
    JobDeleteProfile(unsigned int);
    virtual ~JobDeleteProfile();

    void StepDeleteProfile();
    void StepCompleteJob();
    void CompleteJob(bool);
    void StepProcessResults();

    bool unk58;
    unsigned int unk5c;
    Quazal::ProtocolCallContext unk60;
    int unkb8;
};