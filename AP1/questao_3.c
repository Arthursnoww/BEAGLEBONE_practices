#include <stdio.h>
#include <stdbool.h>

#define MASK 0x01 
#define BITS_ZERO(x) 32-x

int countBits(int num, bool w){
    int count = 0;
    for (int i = 0; i < 32; i++) { 
        if ((num >> i) & MASK) {
            count++;
        }
    }
    int bits0 = BITS_ZERO(count);

    if(w == 1){
        return count;
    }else{
        return bits0;
    }
}


int main(void) {
    int num;
    int variavel; 
    bool w;

    scanf("%d", &variavel);
    scanf("%d", &num);
    
    w = variavel;

    int bs = countBits(num, w);

    printf("%d\n", bs);

    return 0;
}  
