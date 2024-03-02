#include "math/SHA1.h"
#include <stdio.h>
#include <string.h>

CSHA1::CSHA1(){
    &m_block->c = &m_workspace;
    Reset();
}

CSHA1::~CSHA1(){
    Reset();
}

void CSHA1::Reset(){
    m_state[0] = 0x67452301;
    m_state[1] = 0xEFCDAB89;
    m_state[2] = 0x98BADCFE;
    m_state[3] = 0x10325476;
    m_state[4] = 0xC3D2E1F0;
    m_count[0] = 0;
    m_count[1] = 0;
}

void CSHA1::Digest::Copy(unsigned char* c) const {
    memcpy(c, this, 0x14);
}

void CSHA1::Digest::ReportHash(char* c1, unsigned char uc) const {
    char buf[24];
    unsigned int ui;
    if(c1){
        if(uc == 0){
            sprintf(buf, "%02X", digits[0]);
            strcpy(c1, buf);
            for(ui = 1; ui < 0x14; ui++){
                sprintf(buf, "%02X", digits[ui & 0xFF]);
                strcat(c1, buf);
            }
        }
        else if(uc == 1){
            sprintf(buf, "%u", digits[0]);
            strcpy(c1, buf);
            for(ui = 1; ui < 0x14; ui++){
                sprintf(buf, " %u", digits[ui & 0xFF]);
                strcat(c1, buf);
            }
        }
        else strcpy(c1, "Error: Unknown report type!");
    }
}
