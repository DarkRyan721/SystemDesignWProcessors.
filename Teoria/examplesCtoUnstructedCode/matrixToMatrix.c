#include <stdio.h>

int main ()
{

  int FILAS_MATRIZ_B = 3, COLUMNAS_MATRIZ_B = 3;
  int FILAS_MATRIZ_A = 3, COLUMNAS_MATRIZ_A = 3;

  int matrizA [3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
  int matrizB [3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
 
  int producto[FILAS_MATRIZ_B][COLUMNAS_MATRIZ_B];

  for (int a = 0; a < COLUMNAS_MATRIZ_B; a++)
    {
      // Dentro recorremos las filas de la primera (A)
      for (int i = 0; i < FILAS_MATRIZ_A; i++)
	  {
	  int suma = 0;
	  // Y cada columna de la primera (A)
	  for (int j = 0; j < COLUMNAS_MATRIZ_A; j++)
	    {
	      // Multiplicamos y sumamos resultado
	      suma += matrizA[i][j] * matrizB[j][a];
	    }
	  // Lo acomodamos dentro del producto
	  producto[i][a] = suma;
	  }

    }

  printf ("Imprimiendo producto\n");
  for (int i = 0; i < FILAS_MATRIZ_B; i++)
    {
      for (int j = 0; j < COLUMNAS_MATRIZ_B; j++)
	{
	  printf ("%d ", producto[i][j]);
	}
      printf ("\n");
    }

  return 0;
}
