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
    cs_isGrp1 = state_init;

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
    cs_isGrp1 = state_init;
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
        // !!!
        default:{
            break;
        }
    }

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