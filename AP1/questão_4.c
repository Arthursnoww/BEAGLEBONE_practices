#include <stdio.h>
#include <stdbool.h>

#define MASK(x,y) ((1 << (j - i + 1)) - 1) << i

int setBits(bool w, unsigned int i, unsigned int j, unsigned int value) {
    if( w == 1){
        int aux = MASK(i, j);
        value |= aux;
        return value;
    }else{
        int aux = MASK(i, j);
        value &= ~aux;
        return value;
    }
}
  
int main() {
    unsigned int w, i, j, value;

    scanf("%d", &w);
    scanf("%d", &i);
    scanf("%d", &j);
    scanf("%d", &value);

    bool ww = w; 

    unsigned int num = setBits(ww, i, j, value);
    printf("%d\n", num); 
    return 0;
}  
