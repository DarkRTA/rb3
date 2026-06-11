#include <ec/api.h>
#include <ec/mem.h>
#include <new>
#include <exception>
#include <PowerPC_EABI_Support/Runtime/NMWException.h>
#include <string.h>
#include <ec/csup.h>
#include <ec/shoplog_bw.h>

ECResult EC_Init(ECNameValue *p1, unsigned long p2) {
    ECResult status;
    if (ec::op != 0x0) {
        status = ECResult_AlreadyInitialized;
    } else {
        if (p2 == 0 || p1 == 0x0) {
            status = ECResult_InvalidBufHeap;
        } else {
            try {
                status = ec::init(p1, p2);
                if (status == ECResult_Success) {
                    status = ec::op->init();
                    ec::logmsg(ECLogLevel_Info, "ECommerce Library built %s\n", ec::buildDateTime);
                }
            } catch (std::exception) {
                ec::logmsg(ECLogLevel_Error, "Caught exception at  FILE: ec_api.cpp  LINE: %d  COMPILED: Feb  8 2010  20:10:32 \n", 0x38); //0x38 should be __LINE__
                status = ECResult_NoMemory;
            } catch (std::bad_alloc) {
                ec::logmsg(ECLogLevel_Error, "Caught bad_alloc exception at  FILE: ec_api.cpp  LINE: %d  COMPILED: Feb  8 2010  20:10:32 \n", 0x38); //0x38 should be __LINE__
                status = ECResult_ECFail;
            }
        } //do nothing?
    }
    return status;
}

int EC_Shutdown() {
    ECResult status;
    if (ec::op == NULL) {
        return ECResult_Success;
    } else {
        try {
            ec::dumpMemInfo();
            status = ec::op->shutDown();
            if (status == ECResult_Success && (status = ec::shutdown(), status == ECResult_Success)) {
                ec::op->~ECAsyncOpEnv();
                ec::op = NULL;
            }
            ec::dumpMemInfo();
        } catch (std::exception) {
            ec::logmsg(ECLogLevel_Error, "Caught exception at  FILE: ec_api.cpp  LINE: %d  COMPILED: Feb  8 2010  20:10:32 \n", 0x51);
            status = ECResult_NoMemory;
        } catch (std::bad_alloc) {
            ec::logmsg(ECLogLevel_Error, "Caught bad_alloc exception at  FILE: ec_api.cpp  LINE: %d  COMPILED: Feb  8 2010  20:10:32 \n", 0x51);
            status = ECResult_ECFail;
        }        
    }
    return status;
}

int EC_SetParameter(const char *paramId, const char *value) {
    ECResult status;
    if (ec::op == NULL) {
        return ECResult_Init;
    } else if (paramId == NULL) {
        return ECResult_InvalidBufHeap;
    } else {
        try {
            ec::op->lock();
            status = ECResult_Success;
            int cmp = strncmp(paramId, "TIN", 4); //TIN for CAS?
            if (cmp == 0) {
                if (value == NULL) {
                    ec::op->m_TIN = "";
                } else {
                    ec::op->m_TIN = value;
                }
            } else {
                cmp = strncmp(paramId, "AppId", 6); //AppId for CAS?
                if (cmp == 0) {
                    if (value == NULL) {
                        ec::op->m_AppId = "";
                    } else {
                        ec::op->m_AppId = value;
                    }
                } else {
                    cmp = strncmp(paramId, "PCPW", 5); //Parental control password
                    if (cmp == 0) {
                        long what = 0xffffffC0;
                        status = ec::op->checkParentalControlPassword(value, &what);
                        if (status == ECResult_Success && what == 0) {
                            status = ECResult_PCPassIncorrect;
                        }
                    } else {
                        cmp = strncmp(paramId, "USE_NCRS", 9); //what is NCRs
                        if (cmp == 0) {
                            if (value == NULL) {
                                ec::isUseNCRs = false;
                            } else {
                                ec::isUseNCRs = (true - (value == 0));
                            }
                        } else {
                            cmp = strncmp(paramId, "SPACE_CHECK_POLICY", 19);
                            if (cmp == 0) {
                                if (value == NULL) {
                                    status = ECResult_InvalidBufHeap;
                                } else {
                                    cmp = strncmp(value, "SPACE_CHECK_USER_ONLY", 22);
                                    if (cmp == 0) {
                                        ec::op->unk0x190 = 0;
                                    } else {
                                        cmp == strncmp(value, "SPACE_CHECK_ENTIRE_FS", 22);
                                        if (cmp == 0) {
                                            ec::op->unk0x190 = 1;
                                        } else {
                                            status = ECResult_InvalidBufHeap;
                                        }
                                    }
                                }
                            } else {
                                status = ECResult_NotFound;
                            }
                        } 
                    }
                }
            }
        } catch(std::exception) {
            ec::logmsg(ECLogLevel_Error, "Caught exception at  FILE: ec_api.cpp  LINE: %d  COMPILED: Feb  8 2010  20:10:32 \n", 0x9d);
            status = ECResult_NoMemory;
        } catch(std::bad_alloc) {
            ec::logmsg(ECLogLevel_Error, "Caught bad_alloc exception at  FILE: ec_api.cpp  LINE: %d  COMPILED: Feb  8 2010  20:10:32 \n", 0x9d);
            status = ECResult_ECFail;
        }
        ec::op->unlock();
    }
    return status;
}

ECResult EC_GetProgress(unsigned long p1, ECResult *p2) {
    ECResult status;
    if (ec::op == NULL) {
        if (p2 != NULL) {
            p2[6] = ECResult_Init;
            *p2 = ECResult_Init;
        }
        return ECResult_Init;
    } else if (p2 == NULL) {
        return ECResult_InvalidBufHeap;
    } else {
            ec::op->lockProgress();
        try {
            _SHRThread *pOpThread = ec::op->opThread;
            if (pOpThread == NULL) {
                p2[6] = ECResult_NotBusy;
                *p2 = ECResult_NotBusy;
            } else if (p1 == 0 || p1 != pOpThread->osThread.context.gprs[1]) {
                p2[6] = ECResult_NotActive;
                *p2 = ECResult_NotActive;
            } else {
                *p2 = (ECResult)pOpThread->osThread.context.gprs[8];
                unsigned long *pEVar3 = (unsigned long *)p2 + 6;
                unsigned long *puVar2 = pOpThread->osThread.context.gprs + 14;
                p2[1] = (ECResult)pOpThread->osThread.context.gprs[9];
                p2[2] = (ECResult)pOpThread->osThread.context.gprs[10];
                p2[3] = (ECResult)pOpThread->osThread.context.gprs[11];
                p2[4] = (ECResult)pOpThread->osThread.context.gprs[12];
                p2[5] = (ECResult)pOpThread->osThread.context.gprs[13];
                p2[6] = (ECResult)pOpThread->osThread.context.gprs[14];
                int iVar5 = 16;
                unsigned long *puVar1;
                unsigned long result;
                //TODO: do something about this
                do {
                    puVar1++;
                    puVar2 += 2;
                    result = *puVar2;
                    pEVar3[1] = *puVar1;
                    pEVar3 += 2;
                    *pEVar3 = result;
                    iVar5--;
                } while (iVar5 != 0);
                result = ec::getExternalErrCode((ECProgress *)(ec::op->opThread->osThread.context.gprs + 8));
                p2[6] = (ECResult)result;
            }
            status = *p2;
        } catch (std::exception) {
            ec::logmsg(ECLogLevel_Error, "Caught exception at  FILE: ec_api.cpp  LINE: %d  COMPILED: Feb  8 2010  20:10:32 \n", 0x38); //0x38 should be __LINE__
            status = ECResult_NoMemory;
        } catch (std::bad_alloc) {
            ec::logmsg(ECLogLevel_Error, "Caught bad_alloc exception at  FILE: ec_api.cpp  LINE: %d  COMPILED: Feb  8 2010  20:10:32 \n", 0x38); //0x38 should be __LINE__
            status = ECResult_ECFail;
        }
        ec::op->unlockProgress();
    }
    return status;
}

//TODO: Work on this function
int EC_CancelOperation(unsigned long opId) {
    ECResult status;
    _SHRThread *p_Var1;

    if (ec::op == NULL) {
        return ECResult_Init;
    } else {
        ec::op->lock();
        status = ECResult_Success;
        p_Var1 = ec::op->opThread;
        if (p_Var1 == NULL) {
            status = ECResult_NotBusy;
        } else if (opId == 0 && opId != p_Var1->osThread.context.gprs[1]) {
            status = ECResult_NotActive;
            if (p_Var1->osThread.context.gprs[8] == ECResult_NotBusy) {
                status = ECResult_NotBusy;
            } else {
                p_Var1->osThread.context.gprs[11] = 1;
            }
        } else {
            status = ECResult_NotActive;
        }
        ec::op->unlock();
    }
    return status;
}

//TODO: Work on cntlzw on at `ec::op->unk0xc0.size() != 0`
ECResult EC_GetCachedBalance(int *param_1) {
    ECResult status;
    if (ec::op == NULL) {
        status = ECResult_Init;
    } else if (param_1 == NULL) {
        status = ECResult_InvalidBufHeap;
    } else if (ec::op->unk0x174 == false) {
        status = ECResult_NeedECConnect;
    } else {
        if (ec::op->unk0xc0.size() != 0) {
            status = ECResult_NotRegistered;
        } else {
            if (ec::op->unk0x50 == false) {
                status = ECResult_NotFound;
            } else {
                status = ECResult_Success;
                *param_1 = ec::op->unk0x4c;
            }
        }
    }
    return status;
}

ECResult EC_DeleteTitle() {
    ECResult status;
    unsigned long long content;
    if (ec::op == NULL) {
        return ECResult_Init;
    } else {
        try {
            status = ec::deleteTitleContent(content);
        } catch(std::exception) {
            ec::logmsg(ECLogLevel_Error, "Caught exception at  FILE: ec_api.cpp  LINE: %d  COMPILED: Feb  8 2010  20:10:32 \n", 0x11c);
            status = ECResult_NoMemory;
        } catch(std::bad_alloc) {
            ec::logmsg(ECLogLevel_Error, "Caught bad_alloc exception at  FILE: ec_api.cpp  LINE: %d  COMPILED: Feb  8 2010  20:10:32 \n", 0x11c);
            status = ECResult_ECFail;
        }
    }
    return status;
}

//TODO: Work on this function
int EC_GetTitleInfo(unsigned long long titleId, ECTitleInfo *titleInfo, int *param_3) {
    ECResult EVar1;
    int iVar2;
    unsigned long long in_stack_ffffffcc;
    
    if (ec::op == NULL) {
        EVar1 = ECResult_Init;
    } else if (param_3 == NULL) {
        EVar1 = ECResult_InvalidBufHeap;
    } else if (titleInfo == 0 && titleId == 0x0) {
        EVar1 = ECResult_InvalidBufHeap;
    } else {
        try {
            ec::op->lock();
            iVar2 = 1;
            EVar1 = ec::getTitleInfos(titleInfo,(unsigned long *)0xffffffc8,titleId, in_stack_ffffffcc);
            if ((EVar1 == ECResult_Success) && (iVar2 == 0)) {
                EVar1 = ECResult_TitleNotOwned;
            }
            ec::op->unlock();
        } catch(std::exception) {
            ec::logmsg(ECLogLevel_Error, "Caught exception at  FILE: ec_api.cpp  LINE: %d  COMPILED: Feb  8 2010  20:10:32 \n", 0x144);
            EVar1 = ECResult_NoMemory;
        } catch(std::bad_alloc) {
            ec::logmsg(ECLogLevel_Error, "Caught bad_alloc exception at  FILE: ec_api.cpp  LINE: %d  COMPILED: Feb  8 2010  20:10:32 \n", 0x144);
            EVar1 = ECResult_ECFail;
        }
    }
    return EVar1;
}

//TODO: Work on this entire function (it's way too long)
ECResult ec::getTitleInfos(ECTitleInfo *titleInfo, unsigned long *p1, unsigned long long p2, bool p3) {}

//TODO: Figure out the types for the parameters here
//TODO: EC_GetOverhead is called by WiiCommergeMgr::InitCommerce
//TODO: Also figure out if there's a better way to do this. the `goto` spam seems a little ridiculous
//? p1 is overhead type?
ECResult EC_GetOverhead(int p1, int *p2, int *p3) {
    ECResult status = ECResult_Success;
    if (p2 == NULL || p3 == NULL) return ECResult_InvalidBufHeap;
    /*if (p1 != 0) {
        if (p1 != 2) {
            if (p1 != 1) {
                if (p1 != 3) {
                    goto f;
                } else {
                    *p2 = 3;
                    *p3 = 8;
                    goto end;
                }
            } else {
                *p2 = 2;
                *p3 = 6;
                goto end;
            }
        } else {
            *p2 = 2;
            *p3 = 2;
            goto end;
        }
    } else {
        *p2 = 3;
        *p3 = 8;
        goto end;
    }
f: 
    status = ECResult_InvalidBufHeap;
end:*/
    switch (p1) {
        case 0:
            *p2 = 3;
            *p3 = 8;
            break;
        case 2:
            *p2 = 2;
            *p3 = 6;
            break;
        case 1:
            *p2 = 2;
            *p3 = 2;
            break;
        case 3:
            *p2 = 3;
            *p3 = 8;
            break;
        default:
            status = ECResult_InvalidBufHeap;
    }
    return status;
}

//TODO: work on the two `lwz` before `bl checkECDKSyncNeededForTitle`
int EC_GetIsSyncNeeded() {
    int status;
    if (ec::op == NULL) {
        status = -4041;
    } else {
        status = checkECDKSyncNeededForTitle() != 0 & -4006;
    }
    return status;
}
