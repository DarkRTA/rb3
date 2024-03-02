/* included in sha512.c */

const struct _hash_descriptor sha384_desc =
{
    "sha384",
    4,
    48,
    128,
    &sha384_init,
    &sha384_process,
    &sha384_done,
    &sha384_test
};

void sha384_init(hash_state * md)
{
    _ARGCHK(md != NULL);

    md->sha512.curlen = 0;
    md->sha512.length = 0;
    md->sha512.state[0] = CONST64(0xcbbb9d5dc1059ed8);
    md->sha512.state[1] = CONST64(0x629a292a367cd507);
    md->sha512.state[2] = CONST64(0x9159015a3070dd17);
    md->sha512.state[3] = CONST64(0x152fecd8f70e5939);
    md->sha512.state[4] = CONST64(0x67332667ffc00b31);
    md->sha512.state[5] = CONST64(0x8eb44a8768581511);
    md->sha512.state[6] = CONST64(0xdb0c2e0d64f98fa7);
    md->sha512.state[7] = CONST64(0x47b5481dbefa4fa4);
}

void sha384_process(hash_state * md, const unsigned char *buf, unsigned long len)
{
   _ARGCHK(md != NULL);
   _ARGCHK(buf != NULL);
   sha512_process(md, buf, len);
}

void sha384_done(hash_state * md, unsigned char *hash)
{
   unsigned char buf[64];

   _ARGCHK(md != NULL);
   _ARGCHK(hash != NULL);

   sha512_done(md, buf);
   memcpy(hash, buf, 48);
#ifdef CLEAN_STACK
   zeromem(buf, sizeof(buf));
#endif
}

int  sha384_test(void)
{
  static const struct {
      unsigned char *msg;
      unsigned char hash[48];
  } tests[] = {
    { "abc",
      { 0xcb, 0x00, 0x75, 0x3f, 0x45, 0xa3, 0x5e, 0x8b,
        0xb5, 0xa0, 0x3d, 0x69, 0x9a, 0xc6, 0x50, 0x07,
        0x27, 0x2c, 0x32, 0xab, 0x0e, 0xde, 0xd1, 0x63,
        0x1a, 0x8b, 0x60, 0x5a, 0x43, 0xff, 0x5b, 0xed,
        0x80, 0x86, 0x07, 0x2b, 0xa1, 0xe7, 0xcc, 0x23,
        0x58, 0xba, 0xec, 0xa1, 0x34, 0xc8, 0x25, 0xa7 }
    },
    { "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu",
      { 0x09, 0x33, 0x0c, 0x33, 0xf7, 0x11, 0x47, 0xe8,
        0x3d, 0x19, 0x2f, 0xc7, 0x82, 0xcd, 0x1b, 0x47,
        0x53, 0x11, 0x1b, 0x17, 0x3b, 0x3b, 0x05, 0xd2,
        0x2f, 0xa0, 0x80, 0x86, 0xe3, 0xb0, 0xf7, 0x12,
        0xfc, 0xc7, 0xc7, 0x1a, 0x55, 0x7e, 0x2d, 0xb9,
        0x66, 0xc3, 0xe9, 0xfa, 0x91, 0x74, 0x60, 0x39 }
    },
    { NULL, { 0 }}
  };

  int failed, i;
  unsigned char tmp[48];
  hash_state md;

  for (failed = i = 0; tests[i].msg != NULL; i++) {
      sha384_init(&md);
      sha384_process(&md, tests[i].msg, strlen(tests[i].msg));
      sha384_done(&md, tmp);
      if (memcmp(tmp, tests[i].hash, 48)) {
#if 0
         int j;
         printf("\nSHA-384 Test %d failed\nGot (as a result): ", i);
         for (j = 0; j < 48; j++) {
             printf("%02x ", tmp[j]);
         }
         printf("\n");
#endif
         failed = 1;
      }
  }
  if (failed == 1) {
     return CRYPT_FAIL_TESTVECTOR;
  } else {
     return CRYPT_OK;
  }
}





