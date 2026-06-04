#include <ec/soap.h>
#include <ec/misc.h>
#include <PowerPC_EABI_Support/Runtime/NMWException.h>
#include <new>
#include <exception>

#ifndef SOAP_ADD_EL
#define SOAP_ADD_EL(n,v) 
#endif

const char ec::Soap::ecs[4] = "ecs";
const char ec::Soap::ias[4] = "ias";
const char ec::Soap::cas[4] = "cas";
const char ec::Soap::beginningFmt[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\"\n                   xmlns:SOAP-ENC=\"http://schemas.xmlsoap.org/soap/encoding/\"\n                   xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n                   xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"\n                   xmlns:%s=\"urn:%s.wsapi.broadon.com\">\n<SOAP-ENV:Body>\n<%s:%s xsi:type=\"%s:%sRequestType\">\n  <%s:Version>%s</%s:Version>\n  <%s:MessageId>%s</%s:MessageId>\n";
const char ec::Soap::ending[] = ">\n</SOAP-ENV:Body>\n</SOAP-ENV:Envelope>\n";

//TODO: find out why it expands the first function calls like the ECString constructor
void ec::Soap::addElement(const char *name, const char *value) {
    ECString val;
    ec::xml_escape(ECString(value), val);
    stream << indent;
    stream << '<';
    stream << service;
    stream << ':';
    stream << name;
    stream << '>';
    stream << val;
    stream << "</";
    stream << service;
    stream << ':';
    stream << name;
    stream << ">\n";
}

ECString ec::ECOstringstream::str(ECString &str) {
    return m_Buffer.assign(str);
}

void ec::Soap::startComplex(const char *name) {
    //? is ec::ECOstringstream::operator<< void?
    stream << indent;
    stream << '<';
    stream << service;
    stream << ':';
    stream << name;
    stream << ">\n";
    tagStack.push_back(ECString(name));
    indent.append(unk0xc8);
    return;
}

//TODO: Figure this out
void ec::Soap::end() {
    if (tagStack.size() == 1) {
        ECString *idk = tagStack.data() + (tagStack.size() - 1) * 3; //? wtf is this
        if (idk->compare(0, idk->size(), action, strlen(action)) == 0 && oneIndentLen != indent.size()) {
            size_t mCount = tagStack.size();
            size_t indentSize = indent.size();
            ECOstringstream errStream;
            errStream << "Error: ec::Soap::end(): action: ";
            errStream << action;
            errStream << "  tagStack.size(): ";
            errStream << mCount;
            errStream << "  indent.size(): ";
            errStream << indentSize;
            errStream << "  oneIndentLen: ";
            errStream << oneIndentLen;
            int iVar2 = indentSize * 12;
            do {
                errStream << "  tagStack[";
                errStream << indentSize;
                errStream << "]: ";
                errStream << tagStack.data() + iVar2;
                indentSize--;
                iVar2 -= 12;
            } while (true);
        }
        stream << "</";
        stream << service;
        stream << ':';
        stream << action;
        stream << ending;
        logmsg(ECLogLevel_Info, "\n%s\n", stream.str().c_str());
        indent.clear();
        
    }
}

//TODO: Figure out 0x80ae0ef8 to 0x80ae0f40
void ec::Soap::endComplex() {
    ECString smth(*(tagStack.data() + (tagStack.size() - 1) * 3));
    (tagStack.data() + tagStack.size() - 1 * 3)->~basic_string();
    if (oneIndentLen >= indent.size()) {
        indent.end();
        size_t smth1 = oneIndentLen;
        indent.end();
        indent.data();
    }
}

ECResult ec::Soap::getResp(const ECString &huh) {
    ECOstringstream *aEStack44, *EStack50;
    ECResult result;
    httpStatus = 0;
    this->commError = 0;
    unk0x34.clear();
    unk0x4c = 0;
    unk0x4d = 0;
    unk0x94 = -1;
    logmsg(ECLogLevel_Info, "%s\n%s\n", action, huh.c_str());
    //TODO: cntlzw here not working? idk how it works normally but i think this is right?
    if (huh.size() >> 5 != 0) {
        result = ECResult_ConfigErr;
    } else {
        try {
            env->unlock();
            result = getWsResponse(huh);
            status = result;
        } catch(std::exception) {
            logmsg(ECLogLevel_Error, "Caught exception at  FILE: ec_soap.cpp  LINE: %d  COMPILED: Feb  8 2010  20:10:22 \n", 0x10d);
            result = ECResult_NoMemory;
        } catch (std::bad_alloc) {
            logmsg(ECLogLevel_Error, "Caught bad_alloc exception at  FILE: ec_soap.cpp  LINE: %d  COMPILED: Feb  8 2010  20:10:22 \n", __LINE__);
            result = ECResult_ECFail;
        } 
        if (result != 0) {
            status = result;
            env->lock();
        }
        if (EC_FAIL(status)) {
            logmsg(ECLogLevel_Error, "Error %d doing web service request for %s  commError %d  HTTP status code %d\n", status, action, commError, httpStatus);
        } else {
            unk0x94 = 0;
            unk0x98.clear();
            getCommonElements();
        }
        if (status != ECResult_Success) {
            logmsg(ECLogLevel_Info, "%s got response:\n%s\n", action, response.c_str());
            unk0x4d = 1; //phase?
        } else {
            char *pcVar2, *pcVar5, *pcVar6, *pcVar7;
            response.c_str();
            pcVar2 = unk0x34.c_str();
            pcVar5 = aEStack44->str().c_str();
            pcVar6 = EStack50->str().c_str();
            pcVar7 = huh.c_str();
            logmsg(ECLogLevel_Error, "%s got %d\n%s\n%s\n%s\n%s\n%s\n", action, status, pcVar7, pcVar6, pcVar5, pcVar2);
            //aEStack44.str().~basic_string();
            if (status == ECResult_WebServiceError) unk0x4d = 1;
        }
        result = status;
    }
    return result;
}



