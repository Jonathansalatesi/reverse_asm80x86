#include <stdio.h>
#include <stdlib.h>


// open_file.c
// The basic info of the file
int i_len;
int i_len_init;
char* contain;

int i_index_read;           // The index of the binary code has been read

void getbyteArray();


// dig2hex.c
// To let the digital number be heximal
char* dig2hex(char b_val);


// gen_str.c
// parse.c
// The asm code can be stored in the char array.
char asm_code[128];     // The temporary code
int i_len_temp_asm;     // The index of the next byte that can be used

char *code_all;         // All the asm code can be stored here
int i_len_all;          // The number of the byte that we can use
int i_len_temp_all;     // The temporary length

// This function is for init the asm_code[] and code_all[]
void init_code_arr();

void reinit_arr();
void parse();
void parse_modrm();

enum code_state{
    state_init,

    state_EvGv,
    state_GvEv,

    state_EbGb,
    state_GbEb,

    state_EwGw,
    state_GwEw,

    state_EbIb,
    state_EvIb,
    state_EvIv,

    state_66p,
    state_16b_addr,

    state_segment_default,
    state_segment_es,
    state_segment_cs,
    state_segment_ss,
    state_segment_ds,
    state_segment_fs,
    state_segment_gs,

    state_op_rep,
    state_op_repne,

    state_grp1,
    state_grp2,

    state_opcode_add,
    state_opcode_push,
    state_opcode_pop,
    state_opcode_adc,
    state_opcode_and,
    state_opcode_daa,
    state_opcode_xor,
    state_opcode_inc,
    state_opcode_aaa,
    state_opcode_popa,
    state_opcode_popad,
    state_opcode_pusha,
    state_opcode_pushad,
    state_opcode_bound,
    state_opcode_arpl,
    state_opcode_movsxd,
    state_opcode_jo,
    state_opcode_jno,
    state_opcode_jb,
    state_opcode_jnb,
    state_opcode_jz,
    state_opcode_jnz,
    state_opcode_jbe,
    state_opcode_jnbe,
    state_opcode_test,
    state_opcode_xchg,
    state_opcode_nop,
    state_opcode_mov,
    state_opcode_movs,
    state_opcode_cmps,

    state_end
};

enum code_state cs_opcode;
enum code_state cs_ieg;
enum code_state cs_16b_addr;
enum code_state cs_66p;
enum code_state cs_segment;
enum code_state cs_op_re;
enum code_state cs_isGrp1;

void gen_1b_imm();
void gen_2b_imm();
void gen_4b_imm();

void gen_opcode_add();      // add
void gen_opcode_adc();      // adc
void gen_opcode_and();      // and
void gen_opcode_daa();      // daa
void gen_opcode_push();     // push
void gen_opcode_pop();      // pop
void gen_opcode_xor();      // xor
void gen_opcode_aaa();      // aaa
void gen_opcode_inc();      // inc
void gen_opcode_pusha();    // pusha
void gen_opcode_popa();     // popa
void gen_opcode_pushad();   // pushad
void gen_opcode_popad();    // popad
void gen_opcode_bound();    // bound
void gen_opcode_arpl();     // arpl
void gen_opcode_movsxd();   // movsxd
void gen_opcode_jo();       // jo
void gen_opcode_jno();      // jno
void gen_opcode_jb();       // jb
void gen_opcode_jnb();      // jnb
void gen_opcode_jz();       // jz
void gen_opcode_jnz();      // jnz
void gen_opcode_jbe();      // jbe
void gen_opcode_jnbe();     // jnbe
void gen_opcode_test();     // test
void gen_opcode_xchg();     // xchg
void gen_opcode_nop();      // nop
void gen_opcode_mov();      // mov
void gen_opcode_movs();     // movs
void gen_opcode_cmps();     // cmps

void gen_space();           //  
void gen_comma();           // ,
void gen_lbracket();        // [
void gen_rbracket();        // ]
void gen_colon();           // :
void gen_plus();            // +
void gen_enter();           // \n
void gen_dollar();          // $

void gen_code_byte();       // byte
void gen_code_word();       // word
void gen_code_dword();      // dword

void gen_code_ptr();        // ptr

void gen_code_ds();         // ds
void gen_code_es();         // es
void gen_code_cs();         // cs
void gen_code_ss();         // ss
void gen_code_fs();         // fs
void gen_code_gs();         // gs

void gen_code_al();         // al
void gen_code_ah();         // ah
void gen_code_ax();         // ax
void gen_code_eax();        // eax
void gen_code_bl();         // bl
void gen_code_bh();         // bh
void gen_code_bx();         // bx
void gen_code_ebx();        // ebx
void gen_code_cl();         // cl
void gen_code_ch();         // ch
void gen_code_cx();         // cx
void gen_code_ecx();        // ecx
void gen_code_dl();         // dl
void gen_code_dh();         // dh
void gen_code_dx();         // dx
void gen_code_edx();        // edx

void gen_code_sp();         // sp
void gen_code_esp();        // esp
void gen_code_bp();         // bp
void gen_code_ebp();        // ebp
void gen_code_si();         // si
void gen_code_esi();        // esi
void gen_code_di();         // di
void gen_code_edi();        // edi

// complex
void gen_code_segment();    // ds:[, cs:[ ...
void gen_code_jcc();        //  $ + 0x.. 