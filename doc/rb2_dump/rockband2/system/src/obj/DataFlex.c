/*
    Compile unit: C:\rockband2\system\src\obj\DataFlex.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x805E033C -> 0x805E0D14
*/
struct yy_buffer_state {
    // total size: 0x28
    struct _FILE * yy_input_file; // offset 0x0, size 0x4
    char * yy_ch_buf; // offset 0x4, size 0x4
    char * yy_buf_pos; // offset 0x8, size 0x4
    unsigned int yy_buf_size; // offset 0xC, size 0x4
    int yy_n_chars; // offset 0x10, size 0x4
    int yy_is_our_buffer; // offset 0x14, size 0x4
    int yy_is_interactive; // offset 0x18, size 0x4
    int yy_at_bol; // offset 0x1C, size 0x4
    int yy_fill_buffer; // offset 0x20, size 0x4
    int yy_buffer_status; // offset 0x24, size 0x4
};
static struct yy_buffer_state * yy_current_buffer; // size: 0x4, address: 0x80A54E98
static char * yy_c_buf_p; // size: 0x4, address: 0x80A54E9C
static int yy_init; // size: 0x4, address: 0x80A47A00
static int yy_start; // size: 0x4, address: 0x80A54EA0
struct _FILE * yyin; // size: 0x4, address: 0x80A54EA4
struct _FILE * yyout; // size: 0x4, address: 0x80A54EA8
static signed short yy_accept[122]; // size: 0xF4, address: 0x8084EE10
static int yy_ec[256]; // size: 0x400, address: 0x8084EF08
static int yy_meta[46]; // size: 0xB8, address: 0x8084F308
static signed short yy_base[136]; // size: 0x110, address: 0x8084F3C0
static signed short yy_def[136]; // size: 0x110, address: 0x8084F4D0
static signed short yy_nxt[564]; // size: 0x468, address: 0x8084F5E0
static signed short yy_chk[564]; // size: 0x468, address: 0x8084FA48
// Range: 0x805E033C -> 0x805E0784
int yylex() {
    // Local variables
    int yy_current_state; // r30
    char * yy_cp; // r29
    char * yy_bp; // r28
    int yy_act; // r4
    unsigned char yy_c; // r7
    int yy_amount_of_matched_text; // r30
    int yy_next_state; // r3

    // References
    // -> static int yy_did_buffer_switch_on_eof;
    // -> static int yy_n_chars;
    // -> int gDataLine;
    // -> int yyleng;
    // -> char * yytext;
    // -> static signed short yy_nxt[564];
    // -> static signed short yy_chk[564];
    // -> static signed short yy_base[136];
    // -> static int yy_meta[46];
    // -> static signed short yy_def[136];
    // -> static char * yy_last_accepting_cpos;
    // -> static int yy_last_accepting_state;
    // -> static signed short yy_accept[122];
    // -> static int yy_ec[256];
    // -> static char yy_hold_char;
    // -> static char * yy_c_buf_p;
    // -> static struct yy_buffer_state * yy_current_buffer;
    // -> struct _FILE * yyout;
    // -> struct _FILE __files[];
    // -> struct _FILE * yyin;
    // -> static int yy_start;
    // -> static int yy_init;
}

// Range: 0x805E0784 -> 0x805E09C0
static int yy_get_next_buffer() {
    // Local variables
    char * dest; // r30
    char * source; // r29
    int number_to_move; // r31
    int i; // r3
    int ret_val; // r29
    int num_to_read; // r0
    int yy_c_buf_p_offset; // r29

    // References
    // -> struct _FILE * yyin;
    // -> static int yy_n_chars;
    // -> static char * yy_c_buf_p;
    // -> char * yytext;
    // -> static struct yy_buffer_state * yy_current_buffer;
}

// Range: 0x805E09C0 -> 0x805E0A80
static int yy_get_previous_state() {
    // Local variables
    int yy_current_state; // r3
    char * yy_cp; // r8
    unsigned char yy_c; // r9

    // References
    // -> static char * yy_c_buf_p;
    // -> static signed short yy_nxt[564];
    // -> static signed short yy_chk[564];
    // -> static signed short yy_base[136];
    // -> static int yy_meta[46];
    // -> static signed short yy_def[136];
    // -> static char * yy_last_accepting_cpos;
    // -> static int yy_last_accepting_state;
    // -> static signed short yy_accept[122];
    // -> static int yy_ec[256];
    // -> char * yytext;
    // -> static int yy_start;
}

// Range: 0x805E0A80 -> 0x805E0B20
static int yy_try_NUL_trans() {
    // Local variables
    char * yy_cp; // r5
    unsigned char yy_c; // r8

    // References
    // -> static signed short yy_nxt[564];
    // -> static signed short yy_chk[564];
    // -> static signed short yy_base[136];
    // -> static int yy_meta[46];
    // -> static signed short yy_def[136];
    // -> static char * yy_last_accepting_cpos;
    // -> static int yy_last_accepting_state;
    // -> static signed short yy_accept[122];
    // -> static char * yy_c_buf_p;
}

// Range: 0x805E0B20 -> 0x805E0B74
void yyrestart(struct _FILE * input_file /* r31 */) {
    // References
    // -> struct _FILE * yyin;
    // -> static struct yy_buffer_state * yy_current_buffer;
}

// Range: 0x805E0B74 -> 0x805E0BA0
void yy_load_buffer_state() {
    // References
    // -> static char yy_hold_char;
    // -> struct _FILE * yyin;
    // -> char * yytext;
    // -> static char * yy_c_buf_p;
    // -> static int yy_n_chars;
    // -> static struct yy_buffer_state * yy_current_buffer;
}

// Range: 0x805E0BA0 -> 0x805E0C38
struct yy_buffer_state * yy_create_buffer(struct _FILE * file /* r29 */, int size /* r30 */) {
    // Local variables
    struct yy_buffer_state * b; // r31
}

// Range: 0x805E0C38 -> 0x805E0C84
void yy_init_buffer(struct yy_buffer_state * b /* r30 */, struct _FILE * file /* r31 */) {}

// Range: 0x805E0C84 -> 0x805E0CCC
void yy_flush_buffer() {
    // References
    // -> static struct yy_buffer_state * yy_current_buffer;
}

// Range: 0x805E0CCC -> 0x805E0D0C
static void yy_fatal_error() {
    // References
    // -> struct _FILE __files[];
}

// Range: 0x805E0D0C -> 0x805E0D10
static void * yy_flex_alloc() {}

// Range: 0x805E0D10 -> 0x805E0D14
static void * yy_flex_realloc() {}

char * yytext; // size: 0x4, address: 0x80A54EAC
static char * yy_last_accepting_cpos; // size: 0x4, address: 0x80A54EB0
static int yy_last_accepting_state; // size: 0x4, address: 0x80A54EB4
static int yy_did_buffer_switch_on_eof; // size: 0x4, address: 0x80A54EB8
int yyleng; // size: 0x4, address: 0x80A54EBC
static int yy_n_chars; // size: 0x4, address: 0x80A54EC0
static char yy_hold_char; // size: 0x1, address: 0x80A54EC4

