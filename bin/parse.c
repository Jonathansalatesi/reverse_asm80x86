#include "header.h"


void init_code_arr(){
    i_len_temp_asm = 0;
    i_len_all = 128;
    i_len_temp_all = 0;
    i_index_read = 0;

    cs_opcode = state_init;
    cs_ieg = state_init;
    cs_16b_addr = state_init;
    cs_66p = state_init;
    cs_segment = state_segment_default;
    cs_op_re = state_init;
    cs_isGrp = state_init;
    cs_3ps = state_init;

    code_all = (char *)malloc(i_len_all * sizeof(char));
}

void reinit_arr(){
    i_len_temp_asm = 0;

    cs_opcode = state_init;
    cs_ieg = state_init;
    cs_16b_addr = state_init;
    cs_66p = state_init;
    cs_segment = state_segment_default;
    cs_op_re = state_init;
    cs_isGrp = state_init;
    cs_3ps = state_init;
}

char parse_prefix(){
    switch (contain[i_index_read]){
        case (char)0x66:{
            cs_66p = state_66p;
            i_index_read ++;
            return 0x01;
        }
        case (char)0x67:{
            cs_16b_addr = state_16b_addr;
            i_index_read ++;
            return 0x01;
        }
        case (char)0x26:{
            if (cs_segment != state_segment_default){
                i_index_read ++;
                return 0x01;
            } else {
                cs_segment = state_segment_es;
                i_index_read ++;
                return 0x01;
            }
        }
        case (char)0x36:{
            if (cs_segment != state_segment_default){
                i_index_read ++;
                return 0x01;
            } else {
                cs_segment = state_segment_ss;
                i_index_read ++;
                return 0x01;
            }
        }
        case (char)0x2e:{
            if (cs_segment != state_segment_default){
                i_index_read ++;
                return 0x01;
            } else {
                cs_segment = state_segment_cs;
                i_index_read ++;
                return 0x01;
            }
        }
        case (char)0x3e:{
            if (cs_segment != state_segment_default){
                i_index_read ++;
                return 0x01;
            } else {
                cs_segment = state_segment_ds;
                i_index_read ++;
                return 0x01;
            }
        }
        case (char)0x64:{
            if (cs_segment != state_segment_default){
                i_index_read ++;
                return 0x01;
            } else {
                cs_segment = state_segment_fs;
                i_index_read ++;
                return 0x01;
            }
        }
        case (char)0x65:{
            if (cs_segment != state_segment_default){
                i_index_read ++;
                return 0x01;
            } else {
                cs_segment = state_segment_gs;
                i_index_read ++;
                return 0x01;
            }
        }
        case (char)0xf2:{
            if (cs_op_re != state_init){
                i_index_read ++;
                return 0x01;
            } else {
                cs_op_re = state_op_repne;
                i_index_read ++;
                return 0x01;
            }
        }
        case (char)0xf3:{
            if (cs_op_re != state_init){
                i_index_read ++;
                return 0x01;
            } else {
                cs_op_re = state_op_rep;
                i_index_read ++;
                return 0x01;
            }
        }
        default:{
            return 0x00;
        }
    }
}

void parse(){
    char flag = 0x00;
    for(;;){
        flag = parse_prefix();
        if (flag == 0x00){
            break;
        }
    }

    switch (contain[i_index_read]){
        // The upper part of opcode map
        case (char)0x00:{
            gen_opcode_add();
            gen_space();
            cs_opcode = state_opcode_add;
            cs_ieg = state_EbGb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x01:{
            gen_opcode_add();
            gen_space();
            cs_opcode = state_opcode_add;
            if (cs_66p == state_66p){
                cs_ieg = state_EwGw;
            } else {
                cs_ieg = state_EvGv;
            }
            
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x02:{
            gen_opcode_add();
            gen_space();
            cs_opcode = state_opcode_add;
            cs_ieg = state_GbEb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x03:{
            gen_opcode_add();
            gen_space();
            cs_opcode = state_opcode_add;
            if (cs_66p == state_66p){
                cs_ieg = state_GwEw;
            } else {
                cs_ieg = state_GvEv;
            }
            
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x04:{
            gen_opcode_add();
            gen_space();
            cs_opcode = state_opcode_add;
            i_index_read ++;
            gen_code_al();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0x05:{
            gen_opcode_add();
            gen_space();
            cs_opcode = state_opcode_add;
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_ax();
                gen_comma();
                gen_2b_imm();
            } else {
                gen_code_eax();
                gen_comma();
                gen_4b_imm();
            }
            break;
        }
        case (char)0x06:{
            gen_opcode_push();
            gen_space();
            cs_opcode = state_opcode_push;
            i_index_read ++;
            gen_code_es();
            break;
        }
        case (char)0x07:{
            gen_opcode_pop();
            gen_space();
            cs_opcode = state_opcode_pop;
            i_index_read ++;
            gen_code_es();
            break;
        }
        case (char)0x10:{
            gen_opcode_adc();
            gen_space();
            cs_opcode = state_opcode_adc;
            cs_ieg = state_EbGb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x11:{
            gen_opcode_adc();
            gen_space();
            cs_opcode = state_opcode_adc;
            if (cs_66p == state_66p){
                cs_ieg = state_EwGw;
            } else {
                cs_ieg = state_EvGv;
            }
            
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x12:{
            gen_opcode_adc();
            gen_space();
            cs_opcode = state_opcode_adc;
            cs_ieg = state_GbEb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x13:{
            gen_opcode_adc();
            gen_space();
            cs_opcode = state_opcode_adc;
            if (cs_66p == state_66p){
                cs_ieg = state_GwEw;
            } else {
                cs_ieg = state_GvEv;
            }
            
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x14:{
            gen_opcode_adc();
            gen_space();
            cs_opcode = state_opcode_adc;
            i_index_read ++;
            gen_code_al();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0x15:{
            gen_opcode_adc();
            gen_space();
            cs_opcode = state_opcode_adc;
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_ax();
                gen_comma();
                gen_2b_imm();
            } else {
                gen_code_eax();
                gen_comma();
                gen_4b_imm();
            }
            break;
        }
        case (char)0x16:{
            gen_opcode_push();
            gen_space();
            cs_opcode = state_opcode_push;
            i_index_read ++;
            gen_code_ss();
            break;
        }
        case (char)0x17:{
            gen_opcode_pop();
            gen_space();
            cs_opcode = state_opcode_pop;
            i_index_read ++;
            gen_code_ss();
            break;
        }
        case (char)0x20:{
            gen_opcode_and();
            gen_space();
            cs_opcode = state_opcode_and;
            cs_ieg = state_EbGb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x21:{
            gen_opcode_and();
            gen_space();
            cs_opcode = state_opcode_and;
            if (cs_66p == state_66p){
                cs_ieg = state_EwGw;
            } else {
                cs_ieg = state_EvGv;
            }
            
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x22:{
            gen_opcode_and();
            gen_space();
            cs_opcode = state_opcode_and;
            cs_ieg = state_GbEb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x23:{
            gen_opcode_and();
            gen_space();
            cs_opcode = state_opcode_and;
            if (cs_66p == state_66p){
                cs_ieg = state_GwEw;
            } else {
                cs_ieg = state_GvEv;
            }
            
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x24:{
            gen_opcode_and();
            gen_space();
            cs_opcode = state_opcode_and;
            i_index_read ++;
            gen_code_al();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0x25:{
            gen_opcode_and();
            gen_space();
            cs_opcode = state_opcode_and;
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_ax();
                gen_comma();
                gen_2b_imm();
            } else {
                gen_code_eax();
                gen_comma();
                gen_4b_imm();
            }
            break;
        }
        case (char)0x27:{
            gen_opcode_daa();
            cs_opcode = state_opcode_daa;
            i_index_read ++;
            break;
        }
        case (char)0x30:{
            gen_opcode_xor();
            gen_space();
            cs_opcode = state_opcode_xor;
            cs_ieg = state_EbGb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x31:{
            gen_opcode_xor();
            gen_space();
            cs_opcode = state_opcode_xor;
            if (cs_66p == state_66p){
                cs_ieg = state_EwGw;
            } else {
                cs_ieg = state_EvGv;
            }
            
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x32:{
            gen_opcode_xor();
            gen_space();
            cs_opcode = state_opcode_xor;
            cs_ieg = state_GbEb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x33:{
            gen_opcode_xor();
            gen_space();
            cs_opcode = state_opcode_xor;
            if (cs_66p == state_66p){
                cs_ieg = state_GwEw;
            } else {
                cs_ieg = state_GvEv;
            }
            
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x34:{
            gen_opcode_xor();
            gen_space();
            cs_opcode = state_opcode_xor;
            i_index_read ++;
            gen_code_al();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0x35:{
            gen_opcode_xor();
            gen_space();
            cs_opcode = state_opcode_xor;
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_ax();
                gen_comma();
                gen_2b_imm();
            } else {
                gen_code_eax();
                gen_comma();
                gen_4b_imm();
            }
            break;
        }
        case (char)0x37:{
            gen_opcode_aaa();
            cs_opcode = state_opcode_aaa;
            i_index_read ++;
            break;
        }
        case (char)0x40:{
            gen_opcode_inc();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_ax();
            } else {
                gen_code_eax();
            }
            cs_opcode = state_opcode_inc;
            break;
        }
        case (char)0x41:{
            gen_opcode_inc();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_cx();
            } else {
                gen_code_ecx();
            }
            cs_opcode = state_opcode_inc;
            break;
        }
        case (char)0x42:{
            gen_opcode_inc();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_dx();
            } else {
                gen_code_edx();
            }
            cs_opcode = state_opcode_inc;
            break;
        }
        case (char)0x43:{
            gen_opcode_inc();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_bx();
            } else {
                gen_code_ebx();
            }
            cs_opcode = state_opcode_inc;
            break;
        }
        case (char)0x44:{
            gen_opcode_inc();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_sp();
            } else {
                gen_code_esp();
            }
            cs_opcode = state_opcode_inc;
            break;
        }
        case (char)0x45:{
            gen_opcode_inc();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_bp();
            } else {
                gen_code_ebp();
            }
            cs_opcode = state_opcode_inc;
            break;
        }
        case (char)0x46:{
            gen_opcode_inc();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_si();
            } else {
                gen_code_esi();
            }
            cs_opcode = state_opcode_inc;
            break;
        }
        case (char)0x47:{
            gen_opcode_inc();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_di();
            } else {
                gen_code_edi();
            }
            cs_opcode = state_opcode_inc;
            break;
        }
        case (char)0x50:{
            gen_opcode_push();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_ax();
            } else {
                gen_code_eax();
            }
            cs_opcode = state_opcode_push;
            break;
        }
        case (char)0x51:{
            gen_opcode_push();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_cx();
            } else {
                gen_code_ecx();
            }
            cs_opcode = state_opcode_push;
            break;
        }
        case (char)0x52:{
            gen_opcode_push();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_dx();
            } else {
                gen_code_edx();
            }
            cs_opcode = state_opcode_push;
            break;
        }
        case (char)0x53:{
            gen_opcode_push();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_bx();
            } else {
                gen_code_ebx();
            }
            cs_opcode = state_opcode_push;
            break;
        }
        case (char)0x54:{
            gen_opcode_push();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_sp();
            } else {
                gen_code_esp();
            }
            cs_opcode = state_opcode_push;
            break;
        }
        case (char)0x55:{
            gen_opcode_push();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_bp();
            } else {
                gen_code_ebp();
            }
            cs_opcode = state_opcode_push;
            break;
        }
        case (char)0x56:{
            gen_opcode_push();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_si();
            } else {
                gen_code_esi();
            }
            cs_opcode = state_opcode_push;
            break;
        }
        case (char)0x57:{
            gen_opcode_push();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_di();
            } else {
                gen_code_edi();
            }
            cs_opcode = state_opcode_push;
            break;
        }
        case (char)0x60:{
            if (cs_66p == state_66p){
                gen_opcode_pusha();
                cs_opcode = state_opcode_pusha;
            } else {
                gen_opcode_pushad();
                cs_opcode = state_opcode_pushad;
            }
            i_index_read ++;
            break;
        }
        case (char)0x61:{
            if (cs_66p == state_66p){
                gen_opcode_popa();
                cs_opcode = state_opcode_popa;
            } else {
                gen_opcode_popad();
                cs_opcode = state_opcode_popad;
            }
            i_index_read ++;
            break;
        }
        case (char)0x62:{
            // About this code understanding, there're also some problems of understanding.
            // Haven't gotten the correct answer for this code...
            gen_opcode_bound();
            gen_space();
            i_index_read ++;
            cs_opcode = state_opcode_push;
            if (cs_66p != state_66p){
                cs_ieg = state_GvEv;
            } else {
                cs_ieg = state_GwEw;
            }
            parse_modrm();
            break;
        }
        case (char)0x63:{
            if (cs_66p == state_66p){
                gen_opcode_arpl();
                gen_space();
                i_index_read ++;
                cs_opcode = state_opcode_arpl;
                cs_ieg = state_EwGw;
                parse_modrm();
            } else {
                gen_opcode_movsxd();
                gen_space();
                i_index_read ++;
                cs_opcode = state_opcode_movsxd;
                cs_ieg = state_GvEv;
                parse_modrm();
            }
            break;
        }
        case (char)0x70:{
            gen_opcode_jo();
            gen_code_jcc();
            cs_opcode = state_opcode_jo;
            break;
        }
        case (char)0x71:{
            gen_opcode_jno();
            gen_code_jcc();
            cs_opcode = state_opcode_jno;
            break;
        }
        case (char)0x72:{
            gen_opcode_jb();
            gen_code_jcc();
            cs_opcode = state_opcode_jb;
            break;
        }
        case (char)0x73:{
            gen_opcode_jnb();
            gen_code_jcc();
            cs_opcode = state_opcode_jnb;
            break;
        }
        case (char)0x74:{
            gen_opcode_jz();
            gen_code_jcc();
            cs_opcode = state_opcode_jz;
            break;
        }
        case (char)0x75:{
            gen_opcode_jnz();
            gen_code_jcc();
            cs_opcode = state_opcode_jnz;
            break;
        }
        case (char)0x76:{
            gen_opcode_jbe();
            gen_code_jcc();
            cs_opcode = state_opcode_jbe;
            break;
        }
        case (char)0x77:{
            gen_opcode_jnbe();
            gen_code_jcc();
            cs_opcode = state_opcode_jnbe;
            break;
        }
        case (char)0x80:{
            cs_isGrp = state_grp1;
            cs_ieg = state_EbIb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x81:{
            cs_isGrp = state_grp1;
            cs_ieg = state_EvIv;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x82:{
            cs_isGrp = state_grp1;
            cs_ieg = state_EbIb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x83:{
            cs_isGrp = state_grp1;
            cs_ieg = state_EvIb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x84:{
            cs_ieg = state_EbGb;
            cs_opcode = state_opcode_test;
            gen_opcode_test();
            gen_space();
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x85:{
            if (cs_66p = state_66p){
                cs_ieg = state_EwGw;
            } else {
                cs_ieg = state_EvGv;
            }
            cs_opcode = state_opcode_test;
            gen_opcode_test();
            gen_space();
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x86:{
            cs_ieg = state_EbGb;
            cs_opcode = state_opcode_xchg;
            gen_opcode_xchg();
            gen_space();
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x87:{
            if (cs_66p = state_66p){
                cs_ieg = state_EwGw;
            } else {
                cs_ieg = state_EvGv;
            }
            cs_opcode = state_opcode_xchg;
            gen_opcode_xchg();
            gen_space();
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x90:{
            cs_opcode = state_opcode_nop;
            gen_opcode_nop();
            i_index_read ++;
            break;
        }
        case (char)0x91:{
            cs_opcode = state_opcode_xchg;
            gen_opcode_xchg();
            i_index_read ++;
            gen_space();
            if (cs_66p == state_66p){
                gen_code_cx();
                gen_comma();
                gen_code_ax();
            } else {
                gen_code_ecx();
                gen_comma();
                gen_code_eax();
            }
            break;
        }
        case (char)0x92:{
            cs_opcode = state_opcode_xchg;
            gen_opcode_xchg();
            i_index_read ++;
            gen_space();
            if (cs_66p == state_66p){
                gen_code_dx();
                gen_comma();
                gen_code_ax();
            } else {
                gen_code_edx();
                gen_comma();
                gen_code_eax();
            }
            break;
        }
        case (char)0x93:{
            cs_opcode = state_opcode_xchg;
            gen_opcode_xchg();
            i_index_read ++;
            gen_space();
            if (cs_66p == state_66p){
                gen_code_bx();
                gen_comma();
                gen_code_ax();
            } else {
                gen_code_ebx();
                gen_comma();
                gen_code_eax();
            }
            break;
        }
        case (char)0x94:{
            cs_opcode = state_opcode_xchg;
            gen_opcode_xchg();
            i_index_read ++;
            gen_space();
            if (cs_66p == state_66p){
                gen_code_sp();
                gen_comma();
                gen_code_ax();
            } else {
                gen_code_esp();
                gen_comma();
                gen_code_eax();
            }
            break;
        }
        case (char)0x95:{
            cs_opcode = state_opcode_xchg;
            gen_opcode_xchg();
            i_index_read ++;
            gen_space();
            if (cs_66p == state_66p){
                gen_code_bp();
                gen_comma();
                gen_code_ax();
            } else {
                gen_code_ebp();
                gen_comma();
                gen_code_eax();
            }
            break;
        }
        case (char)0x96:{
            cs_opcode = state_opcode_xchg;
            gen_opcode_xchg();
            i_index_read ++;
            gen_space();
            if (cs_66p == state_66p){
                gen_code_si();
                gen_comma();
                gen_code_ax();
            } else {
                gen_code_esi();
                gen_comma();
                gen_code_eax();
            }
            break;
        }
        case (char)0x97:{
            cs_opcode = state_opcode_xchg;
            gen_opcode_xchg();
            i_index_read ++;
            gen_space();
            if (cs_66p == state_66p){
                gen_code_di();
                gen_comma();
                gen_code_ax();
            } else {
                gen_code_edi();
                gen_comma();
                gen_code_eax();
            }
            break;
        }
        case (char)0xa0:{
            // mov al, byte ptr ds:[xxh]
            cs_opcode = state_opcode_mov;
            gen_opcode_mov();
            i_index_read ++;
            gen_space();
            gen_code_al();
            gen_comma();
            gen_code_byte();
            gen_space();
            gen_code_ptr();
            gen_space();
            gen_code_ds();
            gen_colon();
            gen_lbracket();
            gen_1b_imm();
            gen_rbracket();
            break;
        }
        case (char)0xa1:{
            cs_opcode = state_opcode_mov;
            gen_opcode_mov();
            i_index_read ++;
            gen_space();
            if (cs_66p == state_66p){
                // mov ax, word ptr ds:[xxxxh]
                gen_code_ax();
                gen_comma();
                gen_code_word();
                gen_space();
                gen_code_ptr();
                gen_space();
                gen_code_ds();
                gen_colon();
                gen_lbracket();
                gen_2b_imm();
                gen_rbracket();
            } else {
                // mov eax, dword ptr ds:[xxxx xxxxh]
                gen_code_eax();
                gen_comma();
                gen_code_dword();
                gen_space();
                gen_code_ptr();
                gen_space();
                gen_code_ds();
                gen_colon();
                gen_lbracket();
                gen_4b_imm();
                gen_rbracket();
            }
            break;
        }
        case (char)0xa2:{
            // mov byte ptr ds:[xxh], al
            cs_opcode = state_opcode_mov;
            gen_opcode_mov();
            i_index_read ++;
            gen_space();
            gen_code_byte();
            gen_space();
            gen_code_ptr();
            gen_space();
            gen_code_ds();
            gen_colon();
            gen_lbracket();
            gen_1b_imm();
            gen_rbracket();
            gen_comma();
            gen_code_al();
            break;
        }
        case (char)0xa3:{
            cs_opcode = state_opcode_mov;
            gen_opcode_mov();
            i_index_read ++;
            gen_space();
            if (cs_66p == state_66p){
                // mov word ptr ds:[xxxxh], ax
                gen_code_word();
                gen_space();
                gen_code_ptr();
                gen_space();
                gen_code_ds();
                gen_colon();
                gen_lbracket();
                gen_2b_imm();
                gen_rbracket();
                gen_comma();
                gen_code_ax();
            } else {
                // mov dword ptr ds:[xxxx xxxxh], eax
                gen_code_dword();
                gen_space();
                gen_code_ptr();
                gen_space();
                gen_code_ds();
                gen_colon();
                gen_lbracket();
                gen_4b_imm();
                gen_rbracket();
                gen_comma();
                gen_code_eax();
            }
            break;
        }
        case (char)0xa4:{
            // movs byte ptr es:[edi], byte ptr ds:[esi]
            // That can be simplified as movsb
            // gen_opcode_movs();
            // gen_space();
            // gen_code_byte();
            // gen_space();
            // gen_code_ptr();
            // gen_space();
            // gen_code_es();
            // gen_colon();
            // gen_lbracket();
            // gen_code_edi();
            // gen_rbracket();
            // gen_comma();
            // gen_code_byte();
            // gen_space();
            // gen_code_ptr();
            // gen_space();
            // gen_code_ds();
            // gen_colon();
            // gen_lbracket();
            // gen_code_esi();
            // gen_rbracket();
            gen_opcode_movsb();
            cs_opcode = state_opcode_movs;
            i_index_read ++;
            break;
        }
        case (char)0xa5:{
            if (cs_66p == state_66p){
                // movs word ptr es:[edi], word ptr ds:[esi]
                // That can be simplified as movsw
                // gen_opcode_movs();
                // gen_space();
                // gen_code_word();
                // gen_space();
                // gen_code_ptr();
                // gen_space();
                // gen_code_es();
                // gen_colon();
                // gen_lbracket();
                // gen_code_edi();
                // gen_rbracket();
                // gen_comma();
                // gen_code_word();
                // gen_space();
                // gen_code_ptr();
                // gen_space();
                // gen_code_ds();
                // gen_colon();
                // gen_lbracket();
                // gen_code_esi();
                // gen_rbracket();
                gen_opcode_movsw();
                cs_opcode = state_opcode_movs;
                i_index_read ++;
            } else {
                // movs dword ptr es:[edi], dword ptr ds:[esi]
                // That can be simplified as movsd
                // gen_opcode_movs();
                // gen_space();
                // gen_code_dword();
                // gen_space();
                // gen_code_ptr();
                // gen_space();
                // gen_code_es();
                // gen_colon();
                // gen_lbracket();
                // gen_code_edi();
                // gen_rbracket();
                // gen_comma();
                // gen_code_dword();
                // gen_space();
                // gen_code_ptr();
                // gen_space();
                // gen_code_ds();
                // gen_colon();
                // gen_lbracket();
                // gen_code_esi();
                // gen_rbracket();
                gen_opcode_movsd();
                cs_opcode = state_opcode_movs;
                i_index_read ++;
            }
            break;
        }
        case (char)0xa6:{
            // cmps byte ptr ds:[esi], byte ptr es:[edi]
            // That can be simplified as cmpsb
            gen_opcode_cmps();
            cs_opcode = state_opcode_cmps;
            i_index_read ++;
            gen_space();
            gen_code_byte();
            gen_space();
            gen_code_ptr();
            gen_space();
            gen_code_ds();
            gen_colon();
            gen_lbracket();
            gen_code_esi();
            gen_rbracket();
            gen_comma();
            gen_code_byte();
            gen_space();
            gen_code_ptr();
            gen_space();
            gen_code_es();
            gen_colon();
            gen_lbracket();
            gen_code_edi();
            gen_rbracket();
            break;
        }
        case (char)0xa7:{
            if (cs_66p == state_66p){
                // cmps word ptr ds:[esi], word ptr es:[edi]
                // That can be simplified as cmpsw
                gen_opcode_cmps();
                cs_opcode = state_opcode_cmps;
                i_index_read ++;
                gen_space();
                gen_code_word();
                gen_space();
                gen_code_ptr();
                gen_space();
                gen_code_ds();
                gen_colon();
                gen_lbracket();
                gen_code_esi();
                gen_rbracket();
                gen_comma();
                gen_code_word();
                gen_space();
                gen_code_ptr();
                gen_space();
                gen_code_es();
                gen_colon();
                gen_lbracket();
                gen_code_edi();
                gen_rbracket();
            } else {
                // cmps dword ptr ds:[esi], dword ptr es:[edi]
                // That can be simplified as cmpsd
                gen_opcode_cmps();
                cs_opcode = state_opcode_cmps;
                i_index_read ++;
                gen_space();
                gen_code_dword();
                gen_space();
                gen_code_ptr();
                gen_space();
                gen_code_ds();
                gen_colon();
                gen_lbracket();
                gen_code_esi();
                gen_rbracket();
                gen_comma();
                gen_code_dword();
                gen_space();
                gen_code_ptr();
                gen_space();
                gen_code_es();
                gen_colon();
                gen_lbracket();
                gen_code_edi();
                gen_rbracket();
            }
            break;
        }
        case (char)0xb0:{
            // mov al, xxh
            cs_opcode = state_opcode_mov;
            gen_opcode_mov();
            i_index_read ++;
            gen_space();
            gen_code_al();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0xb1:{
            // mov cl, xxh
            cs_opcode = state_opcode_mov;
            gen_opcode_mov();
            i_index_read ++;
            gen_space();
            gen_code_cl();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0xb2:{
            // mov dl, xxh
            cs_opcode = state_opcode_mov;
            gen_opcode_mov();
            i_index_read ++;
            gen_space();
            gen_code_dl();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0xb3:{
            // mov bl, xxh
            cs_opcode = state_opcode_mov;
            gen_opcode_mov();
            i_index_read ++;
            gen_space();
            gen_code_bl();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0xb4:{
            // mov ah, xxh
            cs_opcode = state_opcode_mov;
            gen_opcode_mov();
            i_index_read ++;
            gen_space();
            gen_code_ah();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0xb5:{
            // mov ch, xxh
            cs_opcode = state_opcode_mov;
            gen_opcode_mov();
            i_index_read ++;
            gen_space();
            gen_code_ch();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0xb6:{
            // mov dh, xxh
            cs_opcode = state_opcode_mov;
            gen_opcode_mov();
            i_index_read ++;
            gen_space();
            gen_code_dh();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0xb7:{
            // mov bh, xxh
            cs_opcode = state_opcode_mov;
            gen_opcode_mov();
            i_index_read ++;
            gen_space();
            gen_code_bh();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0xc0:{
            // shift Grp2
            cs_isGrp = state_grp2;
            cs_ieg = state_EbIb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0xc1:{
            cs_isGrp = state_grp2;
            cs_ieg = state_EvIb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0xc2:{
            // ret near xx xxh
            cs_opcode = state_opcode_ret;
            gen_opcode_ret();
            i_index_read ++;
            gen_space();
            gen_code_near();
            gen_space();
            gen_2b_imm();
            break;
        }
        case (char)0xc3:{
            // ret near
            cs_opcode = state_opcode_ret;
            gen_opcode_ret();
            i_index_read ++;
            gen_space();
            gen_code_near();
            break;
        }
        case (char)0xc4:{
            // The default address is 32 bits.
            cs_opcode = state_opcode_les;
            gen_opcode_les();
            i_index_read ++;
            gen_space();
            if (cs_66p == state_66p){
                // les ax, ds:[xxh]
                // Attention !!!
                cs_ieg = state_only_Gw;
                parse_modrm();
                gen_comma();
                gen_code_segment();
                gen_4b_imm();
                gen_rbracket();
            } else {
                // les eax, ds:[xxh]
                // Attention !!!
                cs_ieg = state_only_Gv;
                parse_modrm();
                gen_comma();
                gen_code_segment();
                gen_4b_imm();
                gen_rbracket();
            }
            gen_code_bh();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0xc5:{
            // The default address is 32 bits.
            cs_opcode = state_opcode_lds;
            gen_opcode_lds();
            i_index_read ++;
            gen_space();
            if (cs_66p == state_66p){
                // lds ax, ds:[xxh]
                // Attention !!!
                cs_ieg = state_only_Gw;
                parse_modrm();
                gen_comma();
                gen_code_segment();
                gen_4b_imm();
                gen_rbracket();
            } else {
                // lds eax, ds:[xxh]
                // Attention !!!
                cs_ieg = state_only_Gv;
                parse_modrm();
                gen_comma();
                gen_code_segment();
                gen_4b_imm();
                gen_rbracket();
            }
            gen_code_bh();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0xc6:{
            // Grp11 Mov
            cs_isGrp = state_grp11;
            cs_ieg = state_EbIb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0xc7:{
            cs_isGrp = state_grp11;
            cs_ieg = state_EvIv;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0xd0:{
            cs_isGrp = state_grp2;
            cs_ieg = state_Eb1;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0xd1:{
            cs_isGrp = state_grp2;
            cs_ieg = state_Ev1;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0xd2:{
            cs_isGrp = state_grp2;
            cs_ieg = state_EbCL;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0xd3:{
            cs_isGrp = state_grp2;
            cs_ieg = state_EvCL;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0xd4:{
            cs_opcode = state_opcode_aam;
            i_index_read ++;
            gen_opcode_aam();
            gen_space();
            gen_1b_imm();
            break;
        }
        case (char)0xd5:{
            cs_opcode = state_opcode_aad;
            i_index_read ++;
            gen_opcode_aad();
            gen_space();
            gen_1b_imm();
            break;
        }
        case (char)0xd6:{
            // void opcode
            i_index_read ++;
            break;
        }
        case (char)0xd7:{
            cs_opcode = state_opcode_xlat;
            i_index_read ++;
            gen_opcode_xlat();
            break;
        }
        case (char)0xe0:{
            cs_opcode = state_opcode_loopne;
            i_index_read ++;
            gen_opcode_loopne();
            gen_code_jcc();
            break;
        }
        case (char)0xe1:{
            cs_opcode = state_opcode_loope;
            i_index_read ++;
            gen_opcode_loope();
            gen_code_jcc();
            break;
        }
        case (char)0xe2:{
            cs_opcode = state_opcode_loop;
            i_index_read ++;
            gen_opcode_loop();
            gen_code_jcc();
            break;
        }
        case (char)0xe3:{
            cs_opcode = state_opcode_jcxz;
            i_index_read ++;
            gen_opcode_jcxz();
            gen_code_jcc();
            break;
        }
        case (char)0xe4:{
            cs_opcode = state_opcode_in;
            i_index_read ++;
            gen_opcode_in();
            gen_space();
            gen_code_al();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0xe5:{
            cs_opcode = state_opcode_in;
            i_index_read ++;
            gen_opcode_in();
            gen_space();
            if (cs_66p == state_66p){
                gen_code_ax();
            } else {
                gen_code_eax();
            }
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0xe6:{
            cs_opcode = state_opcode_out;
            i_index_read ++;
            gen_opcode_out();
            gen_space();
            gen_1b_imm();
            gen_comma();
            gen_code_al();
            break;
        }
        case (char)0xe7:{
            cs_opcode = state_opcode_out;
            i_index_read ++;
            gen_opcode_out();
            gen_space();
            gen_1b_imm();
            gen_comma();
            if (cs_66p == state_66p){
                gen_code_ax();
            } else {
                gen_code_eax();
            }
            break;
        }
        case (char)0xf1:{
            i_index_read ++;
            break;
        }
        case (char)0xf4:{
            cs_opcode = state_opcode_hlt;
            gen_opcode_hlt();
            i_index_read ++;
            break;
        }
        case (char)0xf5:{
            cs_opcode = state_opcode_cmc;
            gen_opcode_cmc();
            i_index_read ++;
            break;
        }
        case (char)0xf6:{
            cs_isGrp = state_grp3;
            cs_ieg = state_only_Eb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0xf7:{
            cs_isGrp = state_grp3;
            cs_ieg = state_only_Ev;
            i_index_read ++;
            parse_modrm();
            break;
        }
        //// The lower part of opcode map
        case (char)0x08:{
            gen_opcode_or();
            gen_space();
            cs_opcode = state_opcode_or;
            cs_ieg = state_EbGb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x09:{
            gen_opcode_or();
            gen_space();
            cs_opcode = state_opcode_or;
            if (cs_66p == state_66p){
                cs_ieg = state_EwGw;
            } else {
                cs_ieg = state_EvGv;
            }
            
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x0a:{
            gen_opcode_or();
            gen_space();
            cs_opcode = state_opcode_or;
            cs_ieg = state_GbEb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x0b:{
            gen_opcode_or();
            gen_space();
            cs_opcode = state_opcode_or;
            if (cs_66p == state_66p){
                cs_ieg = state_GwEw;
            } else {
                cs_ieg = state_GvEv;
            }
            
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x0c:{
            gen_opcode_or();
            gen_space();
            cs_opcode = state_opcode_or;
            i_index_read ++;
            gen_code_al();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0x0d:{
            gen_opcode_or();
            gen_space();
            cs_opcode = state_opcode_or;
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_ax();
                gen_comma();
                gen_2b_imm();
            } else {
                gen_code_eax();
                gen_comma();
                gen_4b_imm();
            }
            break;
        }
        case (char)0x0e:{
            gen_opcode_push();
            gen_space();
            cs_opcode = state_opcode_push;
            i_index_read ++;
            gen_code_cs();
            break;
        }
        case (char)0x0f:{
            i_index_read ++;
            parse_2b_opcode();
            break;
        }
        case (char)0x18:{
            gen_opcode_sbb();
            gen_space();
            cs_opcode = state_opcode_sbb;
            cs_ieg = state_EbGb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x19:{
            gen_opcode_sbb();
            gen_space();
            cs_opcode = state_opcode_sbb;
            if (cs_66p == state_66p){
                cs_ieg = state_EwGw;
            } else {
                cs_ieg = state_EvGv;
            }
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x1a:{
            gen_opcode_sbb();
            gen_space();
            cs_opcode = state_opcode_sbb;
            cs_ieg = state_GbEb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x1b:{
            gen_opcode_sbb();
            gen_space();
            cs_opcode = state_opcode_sbb;
            if (cs_66p == state_66p){
                cs_ieg = state_GwEw;
            } else {
                cs_ieg = state_GvEv;
            }
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x1c:{
            gen_opcode_sbb();
            gen_space();
            cs_opcode = state_opcode_sbb;
            i_index_read ++;
            gen_code_al();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0x1d:{
            gen_opcode_sbb();
            gen_space();
            cs_opcode = state_opcode_sbb;
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_ax();
                gen_comma();
                gen_2b_imm();
            } else {
                gen_code_eax();
                gen_comma();
                gen_4b_imm();
            }
            break;
        }
        case (char)0x1e:{
            gen_opcode_push();
            gen_space();
            cs_opcode = state_opcode_push;
            i_index_read ++;
            gen_code_ds();
            break;
        }
        case (char)0x1f:{
            cs_opcode = state_opcode_pop;
            gen_opcode_pop();
            i_index_read ++;
            gen_space();
            gen_code_ds();
            break;
        }
        case (char)0x28:{
            gen_opcode_sub();
            gen_space();
            cs_opcode = state_opcode_sub;
            cs_ieg = state_EbGb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x29:{
            gen_opcode_sub();
            gen_space();
            cs_opcode = state_opcode_sub;
            if (cs_66p == state_66p){
                cs_ieg = state_EwGw;
            } else {
                cs_ieg = state_EvGv;
            }
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x2a:{
            gen_opcode_sub();
            gen_space();
            cs_opcode = state_opcode_sbb;
            cs_ieg = state_GbEb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x2b:{
            gen_opcode_sub();
            gen_space();
            cs_opcode = state_opcode_sbb;
            if (cs_66p == state_66p){
                cs_ieg = state_GwEw;
            } else {
                cs_ieg = state_GvEv;
            }
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x2c:{
            gen_opcode_sub();
            gen_space();
            cs_opcode = state_opcode_sbb;
            i_index_read ++;
            gen_code_al();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0x2d:{
            gen_opcode_sub();
            gen_space();
            cs_opcode = state_opcode_sbb;
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_ax();
                gen_comma();
                gen_2b_imm();
            } else {
                gen_code_eax();
                gen_comma();
                gen_4b_imm();
            }
            break;
        }
        case (char)0x2f:{
            cs_opcode = state_opcode_das;
            gen_opcode_das();
            i_index_read ++;
            break;
        }
        case (char)0x38:{
            gen_opcode_cmp();
            gen_space();
            cs_opcode = state_opcode_cmp;
            cs_ieg = state_EbGb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x39:{
            gen_opcode_cmp();
            gen_space();
            cs_opcode = state_opcode_cmp;
            if (cs_66p == state_66p){
                cs_ieg = state_EwGw;
            } else {
                cs_ieg = state_EvGv;
            }
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x3a:{
            gen_opcode_cmp();
            gen_space();
            cs_opcode = state_opcode_cmp;
            cs_ieg = state_GbEb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x3b:{
            gen_opcode_cmp();
            gen_space();
            cs_opcode = state_opcode_cmp;
            if (cs_66p == state_66p){
                cs_ieg = state_GwEw;
            } else {
                cs_ieg = state_GvEv;
            }
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x3c:{
            gen_opcode_cmp();
            gen_space();
            cs_opcode = state_opcode_cmp;
            i_index_read ++;
            gen_code_al();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0x3d:{
            gen_opcode_cmp();
            gen_space();
            cs_opcode = state_opcode_sbb;
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_ax();
                gen_comma();
                gen_2b_imm();
            } else {
                gen_code_eax();
                gen_comma();
                gen_4b_imm();
            }
            break;
        }
        case (char)0x3f:{
            cs_opcode = state_opcode_aas;
            gen_opcode_aas();
            i_index_read ++;
            break;
        }
        case (char)0x48:{
            gen_opcode_dec();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_ax();
            } else {
                gen_code_eax();
            }
            cs_opcode = state_opcode_dec;
            break;
        }
        case (char)0x49:{
            gen_opcode_dec();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_cx();
            } else {
                gen_code_ecx();
            }
            cs_opcode = state_opcode_dec;
            break;
        }
        case (char)0x4a:{
            gen_opcode_dec();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_dx();
            } else {
                gen_code_edx();
            }
            cs_opcode = state_opcode_dec;
            break;
        }
        case (char)0x4b:{
            gen_opcode_dec();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_bx();
            } else {
                gen_code_ebx();
            }
            cs_opcode = state_opcode_dec;
            break;
        }
        case (char)0x4c:{
            gen_opcode_dec();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_sp();
            } else {
                gen_code_esp();
            }
            cs_opcode = state_opcode_dec;
            break;
        }
        case (char)0x4d:{
            gen_opcode_dec();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_bp();
            } else {
                gen_code_ebp();
            }
            cs_opcode = state_opcode_dec;
            break;
        }
        case (char)0x4e:{
            gen_opcode_dec();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_si();
            } else {
                gen_code_esi();
            }
            cs_opcode = state_opcode_dec;
            break;
        }
        case (char)0x4f:{
            gen_opcode_dec();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_di();
            } else {
                gen_code_edi();
            }
            cs_opcode = state_opcode_dec;
            break;
        }
        case (char)0x58:{
            gen_opcode_pop();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_ax();
            } else {
                gen_code_eax();
            }
            cs_opcode = state_opcode_pop;
            break;
        }
        case (char)0x59:{
            gen_opcode_pop();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_cx();
            } else {
                gen_code_ecx();
            }
            cs_opcode = state_opcode_pop;
            break;
        }
        case (char)0x5a:{
            gen_opcode_pop();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_dx();
            } else {
                gen_code_edx();
            }
            cs_opcode = state_opcode_pop;
            break;
        }
        case (char)0x5b:{
            gen_opcode_pop();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_bx();
            } else {
                gen_code_ebx();
            }
            cs_opcode = state_opcode_pop;
            break;
        }
        case (char)0x5c:{
            gen_opcode_pop();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_sp();
            } else {
                gen_code_esp();
            }
            cs_opcode = state_opcode_pop;
            break;
        }
        case (char)0x5d:{
            gen_opcode_pop();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_bp();
            } else {
                gen_code_ebp();
            }
            cs_opcode = state_opcode_pop;
            break;
        }
        case (char)0x5e:{
            gen_opcode_pop();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_si();
            } else {
                gen_code_esi();
            }
            cs_opcode = state_opcode_pop;
            break;
        }
        case (char)0x5f:{
            gen_opcode_pop();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_code_di();
            } else {
                gen_code_edi();
            }
            cs_opcode = state_opcode_pop;
            break;
        }
        case (char)0x68:{
            gen_opcode_push();
            gen_space();
            i_index_read ++;
            if (cs_66p == state_66p){
                gen_2b_imm();
            } else {
                gen_4b_imm();
            }
            cs_opcode = state_opcode_push;
            break;
        }
        case (char)0x69:{
            gen_opcode_imul();
            gen_space();
            i_index_read ++;
            // if (cs_66p == state_66p){
            //     gen_2b_imm();
            // } else {
            //     gen_4b_imm();
            // }
            cs_opcode = state_opcode_imul;
            cs_3ps = state_3ps;
            cs_ieg = state_GvEv;
            parse_modrm();
            gen_comma();
            gen_4b_imm();
            break;
        }
        case (char)0x6a:{
            gen_opcode_push();
            gen_space();
            i_index_read ++;
            gen_1b_imm();
            cs_opcode = state_opcode_push;
            break;
        }
        case (char)0x6b:{
            gen_opcode_imul();
            gen_space();
            i_index_read ++;
            // if (cs_66p == state_66p){
            //     gen_2b_imm();
            // } else {
            //     gen_4b_imm();
            // }
            cs_opcode = state_opcode_imul;
            cs_3ps = state_3ps;
            cs_ieg = state_GvEv;
            parse_modrm();
            gen_comma();
            gen_1b_imm();
            break;
        }
        case (char)0x6c:{
            gen_opcode_insb();
            i_index_read ++;
            cs_opcode = state_opcode_ins;
            break;
        }
        case (char)0x6d:{
            if (cs_66p = state_66p){
                gen_opcode_insw();
            } else {
                gen_opcode_insd();
            }
            i_index_read ++;
            cs_opcode = state_opcode_ins;
            break;
        }
        case (char)0x6e:{
            gen_opcode_outsb();
            i_index_read ++;
            cs_opcode = state_opcode_outs;
            break;
        }
        case (char)0x6f:{
            if (cs_66p = state_66p){
                gen_opcode_outsw();
            } else {
                gen_opcode_outsd();
            }
            i_index_read ++;
            cs_opcode = state_opcode_outs;
            break;
        }
        case (char)0x78:{
            gen_opcode_js();
            gen_code_jcc();
            cs_opcode = state_opcode_js;
            break;
        }
        case (char)0x79:{
            gen_opcode_jns();
            gen_code_jcc();
            cs_opcode = state_opcode_jns;
            break;
        }
        case (char)0x7a:{
            gen_opcode_jp();
            gen_code_jcc();
            cs_opcode = state_opcode_jp;
            break;
        }
        case (char)0x7b:{
            gen_opcode_jnp();
            gen_code_jcc();
            cs_opcode = state_opcode_jnp;
            break;
        }
        case (char)0x7c:{
            gen_opcode_jl();
            gen_code_jcc();
            cs_opcode = state_opcode_jl;
            break;
        }
        case (char)0x7d:{
            gen_opcode_jnl();
            gen_code_jcc();
            cs_opcode = state_opcode_jnl;
            break;
        }
        case (char)0x7e:{
            gen_opcode_jle();
            gen_code_jcc();
            cs_opcode = state_opcode_jle;
            break;
        }
        case (char)0x7f:{
            gen_opcode_jnle();
            gen_code_jcc();
            cs_opcode = state_opcode_jnle;
            break;
        }
        case (char)0x88:{
            gen_opcode_mov();
            gen_space();
            cs_opcode = state_opcode_mov;
            cs_ieg = state_EbGb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x89:{
            gen_opcode_mov();
            gen_space();
            cs_opcode = state_opcode_mov;
            if (cs_66p == state_66p){
                cs_ieg = state_EwGw;
            } else {
                cs_ieg = state_EvGv;
            }
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x8a:{
            gen_opcode_mov();
            gen_space();
            cs_opcode = state_opcode_mov;
            cs_ieg = state_GbEb;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x8b:{
            gen_opcode_mov();
            gen_space();
            cs_opcode = state_opcode_mov;
            if (cs_66p == state_66p){
                cs_ieg = state_GwEw;
            } else {
                cs_ieg = state_GvEv;
            }
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x8c:{
            gen_opcode_mov();
            gen_space();
            if (cs_66p == state_66p){
                cs_ieg = state_only_Ew;
            } else {
                cs_ieg = state_only_Ev;
            }
            i_index_read ++;
            parse_modrm();
            gen_comma();
            gen_code_segname();
            break;
        }
        case (char)0x8d:{
            gen_opcode_lea();
            gen_space();
            if (cs_66p = state_66p){
                cs_ieg = state_GwEw;
            } else {
                cs_ieg = state_GvEv;
            }
            i_index_read ++;
            parse_modrm();
            gen_comma();
            gen_code_segname();
            break;
        }
        case (char)0x8e:{
            gen_opcode_mov();
            gen_space();
            gen_code_segname();
            gen_comma();
            cs_ieg = state_only_Ew;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x8f:{
            // Grp 1A, pop Ev
            cs_isGrp = state_grp1a;
            cs_ieg = state_only_Ev;
            cs_opcode = state_opcode_pop;
            i_index_read ++;
            parse_modrm();
            break;
        }
        case (char)0x98:{
            // cbw / cwde
            if (cs_66p = state_66p){
                cs_opcode = state_opcode_cbw;
                gen_opcode_cbw();
            } else {
                cs_opcode = state_opcode_cwde;
                gen_opcode_cwde();
            }
            i_index_read ++;
            break;
        }
        case (char)0x99:{
            // cwd / cdq
            if (cs_66p = state_66p){
                cs_opcode = state_opcode_cwd;
                gen_opcode_cwd();
            } else {
                cs_opcode = state_opcode_cdq;
                gen_opcode_cdq();
            }
            i_index_read ++;
            break;
        }
        case (char)0x9a:{
            // far call Ap
            gen_opcode_call();
            i_index_read ++;
            gen_space();
            gen_code_far();
            gen_space();
            gen_code_ptr();
            gen_space();
            i_index_read += 4;
            gen_2b_imm();
            gen_colon();
            i_index_read -= 6;
            gen_4b_imm();
            i_index_read += 2;
            break;
        }
        // !!!
        default:{
            i_index_read ++;
            break;
        }
    }
}

void parse_2b_opcode(){
    return;
}

void parse_modrm(){
    // !!verify the addr mode
    switch (contain[i_index_read]){
        case (char)0x00:{
            if (cs_ieg == state_GbEb){
                // xx al, byte ptr ds:[eax]
                gen_code_al();
                gen_comma();
                gen_code_byte();
                gen_space();
                gen_code_ptr();
                gen_space();
                gen_code_segment();
                gen_code_eax();
                gen_rbracket();
            } else if (cs_ieg == state_EbGb){
                // xx byte ptr ds:[eax], al
                gen_code_byte();
                gen_space();
                gen_code_ptr();
                gen_space();
                gen_code_segment();
                gen_code_eax();
                gen_rbracket();
                gen_comma();
                gen_code_al();
            } else if (cs_ieg == state_GwEw){
                // xx ax, word ptr ds:[eax]
                gen_code_ax();
                gen_comma();
                gen_code_word();
                gen_space();
                gen_code_ptr();
                gen_space();
                gen_code_segment();
                gen_code_eax();
                gen_rbracket();
            } else if (cs_ieg == state_EwGw){
                // xx word ptr ds:[eax], ax
                gen_code_word();
                gen_space();
                gen_code_ptr();
                gen_space();
                gen_code_segment();
                gen_code_eax();
                gen_rbracket();
                gen_comma();
                gen_code_ax();
            } else if (cs_ieg == state_GvEv){
                // xx eax, dword ptr ds:[eax]
                gen_code_eax();
                gen_comma();
                gen_code_dword();
                gen_space();
                gen_code_ptr();
                gen_space();
                gen_code_segment();
                gen_code_eax();
                gen_rbracket();
            } else if (cs_ieg == state_EvGv){
                // xx dword ptr ds:[eax], eax
                gen_code_dword();
                gen_space();
                gen_code_ptr();
                gen_space();
                gen_code_segment();
                gen_code_eax();
                gen_rbracket();
                gen_comma();
                gen_code_eax();
            }
            break;
        }

        default:{
            break;
        }
    }
}