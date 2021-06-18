#include "header.h"

void getbyteArray(char* path){
    FILE *fp;
    char element;
    fp = fopen(path, "rb");
    
    i_len_init = 128;
    contain = (char *)malloc(i_len_init * sizeof(char));
    if (contain == NULL){
        printf("Error: null ptr...");
        return;
    }
    
    char* temp = contain;
    i_len = 0;
    while(!feof(fp)){
        element = getc(fp);
        if (i_len == i_len_init){
            i_len_init *= 2;
            temp = (char* )realloc(contain, i_len_init * sizeof(char));
            contain = temp;
            if (contain == NULL){
                printf("Error: null ptr...");
                return;
            }
        }
        temp[i_len] = element;
        i_len += 1;
    }
    fclose(fp);

    int i = 0;
    int j;
    while (i < i_len){
        j = 0;
        while (j < 16){
            if (i >= i_len){
                break;
            }
            printf("%2x ", temp[i]);
            i ++;
            j ++;
        }
        printf("\n");
    }
}