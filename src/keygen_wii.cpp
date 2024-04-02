

unsigned char asciiDigitToHex(char digit){
    if(0x61 <= digit && digit <= 0x66){
        return digit - 0x57;
    }
    if(0x41 <= digit && digit <= 0x46){
        return digit - 0x37;
    }
    return digit - 0x30;
}

void parseHex16(const char* input, unsigned char* output){
    for(int i = 0; i < 16; i++){
        unsigned int upper = asciiDigitToHex(input[0]) << 4;
        unsigned int lower = asciiDigitToHex(input[1]);
        output[i] = lower + upper;
        input += 2;
    }
}

// void parseHex16(char *param_1,uchar *param_2)

// {
//   int iVar1;
//   char cVar2;
//   int iVar3;
  
//   for (iVar3 = 0; iVar3 < 0x10; iVar3 = iVar3 + 1) {
//     iVar1 = asciiDigitToHex(*param_1);
//     cVar2 = asciiDigitToHex(param_1[1]);
//     *param_2 = cVar2 + (char)(iVar1 << 4);
//     param_2 = param_2 + 1;
//     param_1 = param_1 + 2;
//   }
//   return;
// }

int random(long l){
    static long s_seed = 0xEB;
    if(l != 0) s_seed = l;
    s_seed = s_seed * 0x19660E + 0x3C6EF35F;
    return s_seed;
}

void mash(unsigned char* uc1, unsigned char* uc2){
    for(int i = 0; i < 8; i++){
        uc1[i] = uc1[i] ^ uc2[i];
    }
}

int roll(int i){
    int med = i + 0x13 >> 0x1f;
    return med * 0x20 | (((i + 0x13) * 0x8000000 + med) >> 0x1b) - med;
}

void swap(char& c1, char& c2){
    char tmp = c1;
    c1 = c2;
    c2 = tmp;
}

void shuffle1(char* c){
    for(int i = 0; i < 8; i++){
        int i1 = i * 4;
        swap(c[roll(i1)], c[i1 + 2]);
        swap(c[roll(i1 + 3)], c[i1 + 1]);
    }
}
