#include "header.h"

char* dig2hex(char b_val){
    char cts[8];
    char *result = (char *)malloc(3 * sizeof(char));

    for (int i = 0; i < 8; i ++){
        cts[i] = ((1 << (7 - i)) & b_val) >> (7 - i);
    }

    int j = 0;
    int i_v1 = 0;
    int i_v2 = 0;
    int i_v3 = 0;
    while (j < 8){
        if (j < 4){
            if (((int) cts[j]) == 1){
                i_v1 += (1 << (3 - j));
            }
        } else {
            if (((int) cts[j]) == 1){
                i_v2 += (1 << (3 - (j - 4)));
            }
        }
        j ++;
    }

    for (short k = 0; k < 3; k ++){
        if (((int) cts[k + 2]) == 1){
            i_v3 += (1 << (2 - k));
        }
    }

    if (i_v1 < 10){
        result[0] = '0' + i_v1;
    } else {
        result[0] = 'a' + (i_v1 - 10);
    }

    if (i_v2 < 10){
        result[1] = '0' + i_v2;
    } else {
        result[1] = 'a' + (i_v2 - 10);
    }

    result[2] = '0' + i_v3;
    
    return result;
}