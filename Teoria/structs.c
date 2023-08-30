#include <stdio.h>
//Tipos de datos: Escalares, agregados.
// 1 byte son 8 bits
// sizeof mide en bytes
// 4 formas de vida de la variables: declarar, definir, iniciar y usar

//bitwise: (>>, <<, ~, &, |), unicamente sobre enteros 

//enum {id,id,id} id;


//Paquetes de distintos tipos
//struct {unsigned char x[4]; float y;} number;
// size of usigned char: 1, array of 4 unsigned char: 4,  size of float: 4, Total = 4 + 4 = 8;

/*
    
    printf("Size: %lu\n", sizeof( char ));
    printf("Size: %lu\n", sizeof( float ));
    printf("Size: %lu\n", sizeof( number ));
    
*/

// Paquetes con el mismo espacio de memoria
// union {unsigned char x[4]; float y; unsigned int z} number;
// Un arreglo de char visto como un solo flotante, Un flotante visto de como un arreglo de char

/*
    //number.x[0] = 0xFF;
    //number.x[1] = 0x33;
    //number.x[2] = 0xFF;
    //number.x[3] = 0xAA;
    
    //number.y = 3.14159;
    number.y = 3.082023;
    printf("Data 1: %x\n", number.x[0] );
    printf("Data 2: %X\n", number.x[1] );
    printf("Data 3: %x\n", number.x[2] );
    printf("Data 4: %X\n", number.x[3] );
    
    printf("Number.y: %E\n", number.y );
    printf("Number.z: %E\n", number.z );
    //Representacion de y en IEEE-754: oxff33ffaa, cuando se inicia el arr
*/

//union {float f; unsigned int i;} number;
// unsigned int i, tiene el mismo espacio de memoria pero visto como un unsigned int

/*
    number.f = 3.14159265;

    
    for(int pos = 31; pos >=0; pos--)
    {
        printf("%d", number.i & (1<<pos) ? 1 : 0);
        
    }

*/


union {int (*x)[10]; int (*y)(); int *z;} number;
//lu: long: tamaños grandes, unsigned: tamaños siempre positivos.}
//Toma el tamaño del apuntador, no del tamaño de lo apuntado.

int a[10] = {1,2,3};
int b();
int c;

int main()
{
    // number.x = a;
    number.y = main;
    // printf("Size: %lu\n", sizeof(number) );
    // printf("Array[2]: %ls\n", *(number.x+2));
    printf("Hola\n");
    (*number.y)();
    return 0;
}
