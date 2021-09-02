#include "header.h"

/// Imm
void gen_1b_imm(){
    char* c_temp = dig2hex(contain[i_index_read++]);
//    i_index_read ++;
    asm_code[i_len_temp_asm++] = c_temp[0];
//    i_len_temp_asm ++;
    asm_code[i_len_temp_asm++] = c_temp[1];
//    i_len_temp_asm ++;
    asm_code[i_len_temp_asm++] = 'h';
//    i_len_temp_asm ++;
}

void gen_2b_imm(){
    char* c_temp1 = dig2hex(contain[i_index_read]);
    i_index_read ++;
    char* c_temp2 = dig2hex(contain[i_index_read]);
    i_index_read ++;
    asm_code[i_len_temp_asm] = c_temp2[0];
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = c_temp2[1];
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = c_temp1[0];
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = c_temp1[1];
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'h';
    i_len_temp_asm ++;
}

void gen_4b_imm(){
    char* c_temp1 = dig2hex(contain[i_index_read]);
    i_index_read ++;
    char* c_temp2 = dig2hex(contain[i_index_read]);
    i_index_read ++;
    char* c_temp3 = dig2hex(contain[i_index_read]);
    i_index_read ++;
    char* c_temp4 = dig2hex(contain[i_index_read]);
    i_index_read ++;
    asm_code[i_len_temp_asm] = c_temp4[0];
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = c_temp4[1];
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = c_temp3[0];
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = c_temp3[1];
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = c_temp2[0];
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = c_temp2[1];
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = c_temp1[0];
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = c_temp1[1];
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'h';
    i_len_temp_asm ++;
}

/// opcode
void gen_opcode_add(){
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
}

void gen_opcode_adc(){
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
}

void gen_opcode_and(){
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
}

void gen_opcode_daa(){
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
}

void gen_opcode_push(){
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'u';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'h';
    i_len_temp_asm ++;
}

void gen_opcode_pop(){
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
}

void gen_opcode_xor(){
    asm_code[i_len_temp_asm] = 'x';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'r';
    i_len_temp_asm ++;
}

void gen_opcode_aaa(){
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
}

void gen_opcode_inc(){
    asm_code[i_len_temp_asm] = 'i';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
}

void gen_opcode_pusha(){
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'u';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'h';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
}

void gen_opcode_pushad(){
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'u';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'h';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
}

void gen_opcode_popa(){
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
}

void gen_opcode_popad(){
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
}

void gen_opcode_bound(){
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'u';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
}

void gen_opcode_arpl(){
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'r';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
}

void gen_opcode_movsxd(){
    asm_code[i_len_temp_asm] = 'm';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'v';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'x';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
}

void gen_opcode_jo(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
}

void gen_opcode_jno(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
}

void gen_opcode_jb(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
}

void gen_opcode_jnb(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
}

void gen_opcode_jz(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'z';
    i_len_temp_asm ++;
}

void gen_opcode_jnz(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'z';
    i_len_temp_asm ++;
}

void gen_opcode_jbe(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
}

void gen_opcode_jnbe(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
}

void gen_opcode_js(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
}

void gen_opcode_jns(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
}

void gen_opcode_jp(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
}

void gen_opcode_jnp(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
}

void gen_opcode_jl(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
}

void gen_opcode_jnl(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
}

void gen_opcode_jle(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
}

void gen_opcode_jnle(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
}


void gen_opcode_test(){
    asm_code[i_len_temp_asm] = 't';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 't';
    i_len_temp_asm ++;
}

void gen_opcode_xchg(){
    asm_code[i_len_temp_asm] = 'x';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'h';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'g';
    i_len_temp_asm ++;
}

void gen_opcode_nop(){
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
}

void gen_opcode_mov(){
    asm_code[i_len_temp_asm] = 'm';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'v';
    i_len_temp_asm ++;
}

void gen_opcode_movs(){
    asm_code[i_len_temp_asm] = 'm';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'v';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
}

void gen_opcode_movsb(){
    asm_code[i_len_temp_asm] = 'm';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'v';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
}

void gen_opcode_movsw(){
    asm_code[i_len_temp_asm] = 'm';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'v';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'w';
    i_len_temp_asm ++;
}

void gen_opcode_movsd(){
    asm_code[i_len_temp_asm] = 'm';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'v';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
}

void gen_opcode_cmps(){
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'm';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
}

void gen_opcode_ret(){
    asm_code[i_len_temp_asm] = 'r';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 't';
    i_len_temp_asm ++;
}

void gen_opcode_les(){
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
}

void gen_opcode_lds(){
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
}

void gen_opcode_aam(){
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'm';
    i_len_temp_asm ++;
}

void gen_opcode_aad(){
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
}

void gen_opcode_xlat(){
    asm_code[i_len_temp_asm] = 'x';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 't';
    i_len_temp_asm ++;
}

void gen_opcode_loopne(){
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
}

void gen_opcode_loope(){
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
}

void gen_opcode_loop(){
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
}

void gen_opcode_jcxz(){
    asm_code[i_len_temp_asm] = 'j';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'x';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'z';
    i_len_temp_asm ++;
}

void gen_opcode_in(){
    asm_code[i_len_temp_asm] = 'i';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
}

void gen_opcode_out(){
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'u';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 't';
    i_len_temp_asm ++;
}

void gen_opcode_hlt(){
    asm_code[i_len_temp_asm] = 'h';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 't';
    i_len_temp_asm ++;
}

void gen_opcode_cmc(){
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'm';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
}

void gen_opcode_or(){
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'r';
    i_len_temp_asm ++;
}

void gen_opcode_sbb(){
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
}

void gen_opcode_sub(){
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'u';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
}

void gen_opcode_cmp(){
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'm';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
}

void gen_opcode_das(){
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
}

void gen_opcode_aas(){
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
}

void gen_opcode_dec(){
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
}

void gen_opcode_imul(){
    asm_code[i_len_temp_asm] = 'i';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'm';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'u';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
}

void gen_opcode_insb(){
    asm_code[i_len_temp_asm] = 'i';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
}

void gen_opcode_insw(){
    asm_code[i_len_temp_asm] = 'i';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'w';
    i_len_temp_asm ++;
}

void gen_opcode_insd(){
    asm_code[i_len_temp_asm] = 'i';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
}

void gen_opcode_outsb(){
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'u';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 't';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
}

void gen_opcode_outsw(){
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'u';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 't';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'w';
    i_len_temp_asm ++;
}

void gen_opcode_outsd(){
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'u';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 't';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
}

void gen_opcode_lea(){
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
}

void gen_opcode_cbw(){
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'w';
    i_len_temp_asm ++;
}

void gen_opcode_cwde(){
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'w';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
}

void gen_opcode_cwd(){
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'w';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
}

void gen_opcode_cdq(){
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'q';
    i_len_temp_asm ++;
}

void gen_opcode_call(){
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
}

/// symbol
//
void gen_space(){
    asm_code[i_len_temp_asm] = ' ';
    i_len_temp_asm ++;
}

// ,
void gen_comma(){
    asm_code[i_len_temp_asm] = ',';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = ' ';
    i_len_temp_asm ++;
}

// [
void gen_lbracket(){
    asm_code[i_len_temp_asm] = '[';
    i_len_temp_asm ++;
}

// ]
void gen_rbracket(){
    asm_code[i_len_temp_asm] = ']';
    i_len_temp_asm ++;
}

// :
void gen_colon(){
    asm_code[i_len_temp_asm] = ':';
    i_len_temp_asm ++;
}

// +
void gen_plus(){
    asm_code[i_len_temp_asm] = '+';
    i_len_temp_asm ++;
}


// \n
void gen_enter(){
    asm_code[i_len_temp_asm] = '\n';
    i_len_temp_asm ++;
}

// $
void gen_dollar(){
    asm_code[i_len_temp_asm] = '$';
    i_len_temp_asm ++;
}

/// code
void gen_code_byte(){
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'y';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 't';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
}

void gen_code_word(){
    asm_code[i_len_temp_asm] = 'w';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'r';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
}

void gen_code_dword(){
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'w';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'o';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'r';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
}

void gen_code_ptr(){
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 't';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'r';
    i_len_temp_asm ++;
}

void gen_code_near(){
    asm_code[i_len_temp_asm] = 'n';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'r';
    i_len_temp_asm ++;
}

void gen_code_far(){
    asm_code[i_len_temp_asm] = 'f';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'r';
    i_len_temp_asm ++;
}

void gen_code_ds(){
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
}

void gen_code_es(){
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
}

void gen_code_cs(){
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
}
void gen_code_ss(){
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
}

void gen_code_fs(){
    asm_code[i_len_temp_asm] = 'f';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
}

void gen_code_gs(){
    asm_code[i_len_temp_asm] = 'g';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
}

void gen_code_al(){
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
}

void gen_code_ah(){
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'h';
    i_len_temp_asm ++;
}

void gen_code_ax(){
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'x';
    i_len_temp_asm ++;
}

void gen_code_eax(){
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'a';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'x';
    i_len_temp_asm ++;
}

void gen_code_bl(){
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
}

void gen_code_bh(){
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'h';
    i_len_temp_asm ++;
}

void gen_code_bx(){
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'x';
    i_len_temp_asm ++;
}

void gen_code_ebx(){
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'x';
    i_len_temp_asm ++;
}

void gen_code_cl(){
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
}

void gen_code_ch(){
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'h';
    i_len_temp_asm ++;
}

void gen_code_cx(){
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'x';
    i_len_temp_asm ++;
}

void gen_code_ecx(){
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'c';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'x';
    i_len_temp_asm ++;
}

void gen_code_dl(){
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'l';
    i_len_temp_asm ++;
}

void gen_code_dh(){
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'h';
    i_len_temp_asm ++;
}

void gen_code_dx(){
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'x';
    i_len_temp_asm ++;
}

void gen_code_edx(){
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'x';
    i_len_temp_asm ++;
}

void gen_code_sp(){
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
}

void gen_code_esp(){
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
}

void gen_code_bp(){
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
}

void gen_code_ebp(){
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'b';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'p';
    i_len_temp_asm ++;
}

void gen_code_si(){
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'i';
    i_len_temp_asm ++;
}

void gen_code_esi(){
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 's';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'i';
    i_len_temp_asm ++;
}

void gen_code_di(){
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'i';
    i_len_temp_asm ++;
}

void gen_code_edi(){
    asm_code[i_len_temp_asm] = 'e';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'd';
    i_len_temp_asm ++;
    asm_code[i_len_temp_asm] = 'i';
    i_len_temp_asm ++;
}


// complex gen func
// segment
void gen_code_segname(){
    if (cs_segment == state_segment_default){
        gen_code_ds();
    } else if (cs_segment == state_segment_es){
        gen_code_es();
    } else if (cs_segment == state_segment_ss){
        gen_code_ss();
    } else if (cs_segment == state_segment_cs){
        gen_code_cs();
    } else if (cs_segment == state_segment_ds){
        gen_code_ds();
    } else if (cs_segment == state_segment_fs){
        gen_code_fs();
    } else if (cs_segment == state_segment_gs){
        gen_code_gs();
    }
}

void gen_code_segment(){
    gen_code_segname();
    gen_colon();
    gen_lbracket();
}

// This function is useful just for 7xh
void gen_code_jcc(){
    gen_space();
    gen_dollar();
    gen_space();
    gen_plus();
    gen_space();
    i_index_read ++;
    gen_1b_imm();
}
