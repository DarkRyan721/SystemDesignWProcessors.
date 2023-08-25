// printf prototype: printf(const char* restric format, ...); 
// scanf prototype: scanf(const char* format,...)

// int (* func_ptr) (const char* restric format, ...); Apuntador a una funcion con parametros que retorna un entero
// int * func_ptr (const char* restric format, ...); Funcion con parametros que retorna un apuntador


/*
Tabla de intercambio de variables:
              b          b_ptr
a         a=b          a = *b_ptr 
a_ptr     a_ptr=&b     a_ptr=b_ptr

  &(dirreccion): ... la dirreccion de ...
  *(indirreccion): ... el contenido de lo apuntado por ...
    indirrecta: no toma de manera dirrcta el valor, lo toma referirse a la variable (indirreccion)
  =(asignacion): ...toma...

*/

/*
Memorias de asignacion para la ejecucion de un programa.
4 Zonas importantes.
  Codigo
  Datos
  Stack
  Heap
  (Capitulo Anderson - Run time enviroment)
*/


