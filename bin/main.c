#include "header.h"


int main(){
    char st[6] = {0x66, 0xb7, 0x49, 0x01, 0x00, 0x02};
    contain = st;
    init_code_arr();

    parse();
    for (int i = 0; i < i_len_temp_asm; i++){
        printf("%c", asm_code[i]);
    }
}

// test for file reader
// int main(){
//     getbyteArray("1.c");
//     printf("%d", i_len);
//     return 0;
// }

// test for translator
// int main(){
//     char b_val = 0x0d;
//     char* s = dig2hex(b_val);

//     printf("%c", s[0]);
//     printf("%c", s[1]);
//     free(s);
//     return 0;
// }