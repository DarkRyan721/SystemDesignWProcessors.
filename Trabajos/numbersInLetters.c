// #Miguel Angel Cera Contreras
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define specialSize 9
#define elementsNumber 3
// Definiendo los valores constantes de texto
char *unidades[10] = {"", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve"};
char *decenas[10] = {"", "dieci", "veinti", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa"};
char *centenas[10] = {"", "ciento", "doscientos", "trescientos", "cuatrocientos", "quinientos", "seiscientos", "setecientos", "ochocientos", "novecientos"};
char *especiales[specialSize] = {"diez", "once", "doce", "trece", "catorce", "quince", "veinte", "cien", "mil"};
char *millones[10] = {
    "millónes",
    "billón",
    "trillón",
    "cuatrillón",
    "quintillón",
    "sextillón",
    "septillón",
    "octillón",
    "nonillón",
    "decillón",
};
// Valores especiales en numero
int specialNumbers[specialSize] = {10, 11, 12, 13, 14, 15, 20, 100, 1000};

// Funciones usadas
int numberOfNumbers(int);
int eToSpecial(int);
char *digitsToString(int);
int arrayToNumber(int[]);
void numberToMatrix(int, int **);
int divInPair3(int);
int emptyArray(int[]);
int specialArray(int[]);
char *matrixToString(int **, int);
int inputValidation();

int main()
{
    // Valores de entrada y salida
    int numInteger = 0;
    char *numString = NULL;
    // Valores de almacenamiento de datos.
    int **divNumber = NULL;

    // Getting the number and validating it:
    printf("Convertidor de números a palabras en español.\n");
    printf("---------------------------------------------\n");
    numInteger = inputValidation();
    // Creating N matrices for the sizes of numbers
    // Divide by 3 each number in continuous arrays (Matrix)
    divNumber = (int **)malloc(divInPair3(numInteger) * sizeof(int *));
    for (int i = 0; i < divInPair3(numInteger); i++)
    {
        divNumber[i] = (int *)malloc(elementsNumber * sizeof(int));
    }

    // Adding the values, to the matrix. (Go to the fuction to explain.)
    numberToMatrix(numInteger, divNumber);

    // This function goes to each array to convert to string.
    numString = matrixToString(divNumber, numInteger);
    printf("%-9s\n", numString);
    // Delete the memory allocated
    for (int i = 0; i < divInPair3(numInteger); i++)
    {
        free(divNumber[i]);
    }
    free(divNumber);
    return 0;
}

// Get the N numbers to the input.
int numberOfNumbers(int num)
{
    int N = 0;
    while (num != 0)
    {
        num /= 10;
        N++;
    }
    return N;
}

// This function confirms whether the number belongs to the set of the especials numbers.
int eToSpecial(int num)
{
    for (int i = 0; i < specialSize; i++)
    {
        if (num == specialNumbers[i])
            return i;
    }
    return -1;
}

// This function (matrizToString) converts each individual array to a string.
char *digitsToString(int num)
{
    char *numS = (char *)malloc(sizeof(char) * 100);
    if (eToSpecial(num) >= 0)
        strcat(numS, especiales[eToSpecial(num)]);
    else
    {
        strcat(numS, centenas[num / 100]);
        if (eToSpecial(num % 100) >= 0)
        {
            strcat(numS, especiales[eToSpecial(num % 100)]);
        }
        else
        {
            strcat(numS, decenas[(num / 10) % 10]);
            if (num % 100 >= 30)
                strcat(numS, " y ");
            strcat(numS, unidades[(num) % 10]);
        }
    }
    return numS;
}

// Fuction to get a array of 3 elements and return a number.
int arrayToNumber(int arrNum[])
{
    int num = 0;
    int arrDecimal[3] = {100, 10, 1};
    for (int i = 0; i < 3; i++)
    {
        num += (arrNum[i] * arrDecimal[i]);
    }
    return num;
}

void numberToMatrix(int num, int **matrix)
{
    // divInPair3 gives the number to the N arrays that will have
    int N = divInPair3(num);
    // This for is uses to get the decimals (Tens, hundreds, and units, gets each value and divide by 1000 to get the next.
    // with the memory address of the matrix we point to define the values.
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < elementsNumber; j++)
        {
            matrix[i][elementsNumber - j - 1] = (((int)(num / pow(10, j))) % 10);
        }
        num /= 1000;
    }
}

//GEt the rows of the matrix (The N number of elements of arrays)
int divInPair3(int num)
{
    if (numberOfNumbers(num) % 3 == 0)
        return (int)numberOfNumbers(num) / 3;
    if (numberOfNumbers(num) % 3 != 0)
        return ((((int)numberOfNumbers(num)) / 3) + 1);
}

//Gets the confirmation if an array is empty
int emptyArray(int arr[])
{
    for (int i = 0; i < 3; i++)
    {
        if (arr[i] != 0)
            return 0;
    }
    return 1;
}
//Gets the confirmation if an array is special [0,0,1]
int specialArray(int arr[])
{
    if (arr[0] == 0 && arr[1] == 0 && arr[2] == 1)
        return 1;
    return 0;
}

//Go to any individual array and concatenate them in a string
char *matrixToString(int **matrix, int num)
{
    char *matrixS = (char *)malloc(sizeof(char) * 100);

    if (num == 0)
        return "cero";

    for (int i = divInPair3(num) - 1; i >= 0; i--)
    {
        matrixS = strcat(matrixS, " ");
        if (i % 2 != 0)
        {
            if (emptyArray(matrix[i]) == 0)
            {
                if (specialArray(matrix[i]) == 1)
                    matrixS = strcat(matrixS, "mil");
                if (specialArray(matrix[i]) != 1)
                {
                    matrixS = strcat(matrixS, digitsToString(arrayToNumber(matrix[i])));
                    matrixS = strcat(matrixS, " mil");
                }
            }
        }
        if (i % 2 == 0 && i != 0)
        {
            if (specialArray(matrix[i]) == 1)
                matrixS = strcat(matrixS, "un millón");
            if (specialArray(matrix[i]) != 1)
            {
                matrixS = strcat(matrixS, digitsToString(arrayToNumber(matrix[i])));
                matrixS = strcat(matrixS, " ");
                matrixS = strcat(matrixS, millones[i - 2]);
            }
        }
        if (i % 2 == 0 && i == 0)
            if (emptyArray(matrix[i]) == 0)
            {
                matrixS = strcat(matrixS, digitsToString(arrayToNumber(matrix[i])));
            }
    }

    return matrixS;
}


//Get the correct input validation
int inputValidation()
{
    int num;
    char c;
    while (1)
    {
        printf("Ingrese un numero: ");
        if (scanf("%d", &num) == 1)
        {
            // La entrada es numérica, eliminar el carácter '\n' del buffer de entrada
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            return num;
        }
        else
        {
            // La entrada no es numérica, eliminar el carácter '\n' del buffer de entrada
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            printf("Error: Ingrese un valor numérico válido.\n");
        }
    }
}
