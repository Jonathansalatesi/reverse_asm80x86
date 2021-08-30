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
void parse_2b_opcode();
void parse_modrm();

enum code_state{
    state_init,

    state_only_Eb,
    state_only_Ew,
    state_only_Ev,

    state_only_Gb,
    state_only_Gw,
    state_only_Gv,

    state_EvGv,
    state_GvEv,

    state_EbGb,
    state_GbEb,

    state_EwGw,
    state_GwEw,

    state_EbIb,
    state_EvIb,
    state_EvIv,

    state_Eb1,
    state_Ev1,

    state_EbCL,
    state_EvCL,

    state_66p,
    state_16b_addr,
    state_3ps,

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
    state_grp1a,
    state_grp2,
    state_grp3,
    state_grp11,

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

    state_opcode_js,
    state_opcode_jns,
    state_opcode_jp,
    state_opcode_jnp,
    state_opcode_jl,
    state_opcode_jnl,
    state_opcode_jle,
    state_opcode_jnle,

    state_opcode_test,
    state_opcode_xchg,
    state_opcode_nop,
    state_opcode_mov,
    state_opcode_movs,
    state_opcode_cmps,
    state_opcode_ret,
    state_opcode_les,
    state_opcode_lds,
    state_opcode_aam,
    state_opcode_aad,
    state_opcode_xlat,
    state_opcode_loopne,
    state_opcode_loope,
    state_opcode_loop,
    state_opcode_jcxz,
    state_opcode_in,
    state_opcode_out,
    state_opcode_hlt,
    state_opcode_cmc,
    state_opcode_or,
    state_opcode_sbb,
    state_opcode_sub,
    state_opcode_cmp,
    state_opcode_das,
    state_opcode_aas,
    state_opcode_dec,
    state_opcode_imul,
    state_opcode_ins,
    state_opcode_outs,
    state_opcode_lea,

    state_opcode_cbw,
    state_opcode_cwde,
    state_opcode_cwd,
    state_opcode_cdq,

    state_opcode_call,

    state_end
};

enum code_state cs_opcode;
enum code_state cs_ieg;
enum code_state cs_16b_addr;
enum code_state cs_66p;
enum code_state cs_segment;
enum code_state cs_op_re;
enum code_state cs_isGrp;
enum code_state cs_3ps;         // Three parameters for one code

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

void gen_opcode_js();       // js
void gen_opcode_jns();      // jns
void gen_opcode_jp();       // jp
void gen_opcode_jnp();      // jnp
void gen_opcode_jl();       // jl
void gen_opcode_jnl();      // jnl
void gen_opcode_jle();      // jle
void gen_opcode_jnle();     // jnle

void gen_opcode_test();     // test
void gen_opcode_xchg();     // xchg
void gen_opcode_nop();      // nop
void gen_opcode_mov();      // mov
void gen_opcode_movs();     // movs
void gen_opcode_movsb();    // movsb
void gen_opcode_movsw();    // movsw
void gen_opcode_movsd();    // movsd
void gen_opcode_cmps();     // cmps
void gen_opcode_ret();      // ret
void gen_opcode_les();      // les
void gen_opcode_lds();      // lds
void gen_opcode_aam();      // aam
void gen_opcode_aad();      // aad
void gen_opcode_xlat();     // xlat
void gen_opcode_loopne();   // loopne
void gen_opcode_loope();    // loope
void gen_opcode_loop();     // loop
void gen_opcode_jcxz();     // jcxz
void gen_opcode_in();       // in
void gen_opcode_out();      // out
void gen_opcode_hlt();      // hlt
void gen_opcode_cmc();      // cmc
void gen_opcode_or();       // or
void gen_opcode_sbb();      // sbb
void gen_opcode_sub();      // sub
void gen_opcode_cmp();      // cmp
void gen_opcode_das();      // das
void gen_opcode_aas();      // aas
void gen_opcode_dec();      // dec
void gen_opcode_imul();     // imul
void gen_opcode_insb();     // insb
void gen_opcode_insw();     // insw
void gen_opcode_insd();     // insd
void gen_opcode_outsb();    // outsb
void gen_opcode_outsw();    // outsw
void gen_opcode_outsd();    // outsd

void gen_opcode_lea();      // lea

void gen_opcode_cbw();      // cbw
void gen_opcode_cwde();     // cwde
void gen_opcode_cwd();      // cwd
void gen_opcode_cdq();      // cdq

void gen_opcode_call();     // call

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
void gen_code_near();       // near
void gen_code_far();        // far

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
void gen_code_segname();    // ds, cs, ss, gs, fs, es
void gen_code_segment();    // ds:[, cs:[ ...
void gen_code_jcc();        //  $ + 0x.. 