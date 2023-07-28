/*

**********ESSE CODIGO ABAIXO FUNCIONA PARA MAIORIA DOS CASOS, PASSA EM 2 TESTE, E USA MASCARA, NAO ENTENDI PORQUE tem
********** 4 BITS '0' NO DESLOCAMENTO DE 86, já que 86 é um numero de 7 bits


#include <stdio.h>

#define MASK(x,y) ((1 << (x - (x-y)+1))-1) << (x-y)

int main() {
    unsigned int n;
    scanf("%u", &n);

    unsigned char num[33];

    int tam = 0;
    while (n > 0){
        num[tam] = n % 2;
        tam++;
        n = n / 2;
    }
    int count = 0;
    for(int i = tam; i >= 0; i--){
        if(num[i] & 1){
            count++;
        }
    }

    unsigned int n_value = MASK(tam, count);

    for (int i = tam; i > 0; i--) {
        printf("%u", (n_value >> i-1) & 0x01);
    }
    printf("\n");

}
******POREM O CODIGO ABAIXO É MAIS GENERICO E CONSEGUE PASSAR EM TODOS CASOS DE TESTE.

*/


  #include <stdio.h>

  #define MASK 0x01 
  #define SHIFT_LEFT(bits) (0xFF << (8 - bits))

  int main() {
      int num;

      scanf("%d", &num);

      int bits_setados = 0;
      for (int i = 0; i < 32; i++) { 
          if ((num >> i) & MASK) {
              bits_setados++;
          }
      }

      int resultado = num << bits_setados; 
      resultado |= SHIFT_LEFT(bits_setados);

      for (int i = 0; i < 8; i++) {
          if (resultado & (0x80 >> i)) {
              printf("1");
          } else {
              printf("0");
          }
      }
      printf("\n");

      return 0;
  }    
