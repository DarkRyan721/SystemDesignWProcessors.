#include <stdio.h>
  int FILAS_MATRIZ_B = 3, COLUMNAS_MATRIZ_B = 3;
  int FILAS_MATRIZ_A = 3, COLUMNAS_MATRIZ_A = 3;

  int matrizA [3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
  int matrizB [3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
 
  int producto[3][3];
  int j;
  int i;
  int a;
  int suma;

int main ()
{
    a = 0;
    FOR1: if(a >= COLUMNAS_MATRIZ_B) goto END1;
	  i = 0;
	  FOR2: if( i >= FILAS_MATRIZ_A) goto END2;
	      suma = 0;
    	  j = 0; 
    	  FOR3: if( j >= COLUMNAS_MATRIZ_A) goto END3;
    	        suma += matrizA[i][j] * matrizB[j][a];
    	        j++;
    	        goto FOR3;
    	  END3:
	      producto[i][a] = suma;
	      i++;
	      goto FOR2;
	  END2:
	  a++;
	  goto FOR1;
	 END1:return 0;
}
