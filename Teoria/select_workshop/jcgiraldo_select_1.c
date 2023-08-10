/* Ruler 1         2         3         4         5         6         7        */

/********************************** Headers ***********************************/

/* ------------------------ Inclusion of Std Headers ------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/********************************* Variables **********************************/

/* ------------------ Private Declaration used in Function ------------------ */

/*******************************************************************************
 *                                                                              *
 *   If the following declaration is not going to be used any other place in    *
 *   module, it must be defined static inside function Evaluate_Function_v1()   *
 *                                                                              *
 *******************************************************************************/

static double (*function[])() = {
    acos, asin, atan, ceil, cos, cosh, exp, fabs,
    floor, log, log10, sin, sinh, sqrt, tan, tanh};

#ifdef DRIVER

/*******************************************************************************
 *
 *   For testing purposes compile source code using:
 *   gcc -DDRIVER code.c -o code
 *
 *   Once the code has been widely tested, generate object code using:
 *   gcc -c code.c
 *
 ******************************************************************************/

/* ---------------------- Prototype of Tested Function ---------------------- */

double Evaluate_Function_V1(int n, double value);

/* ------------------------ Driver for Embedded Test ------------------------ */

int main(int argc, char *argv[])
{
    int n;
    double value, result;

    if (argc != 3)
        fprintf(stderr, "Usage: %s n value\n", argv[0]);
    else
    {
        n = atoi(argv[1]);
        value = atof(argv[2]);

        if (n >= 0 && n <= 15)
        {
            result = Evaluate_Function_V1(n, value);
            fprintf(stdout, "Function%d( %f ) = %f\n", n, value, result);
        }
        else
            fprintf(stderr, "n must be an integer between 0 and 15\n");
    }

    return 0;

} /* main */

#endif

/****************************** Global Functions ******************************/

/*FN****************************************************************************
 *
 *   Evaluate_Function_V1( int n, double value )
 *
 *   Return:          Value of function number n
 *
 *   Purpose:         This function evaluates a value according to an integer
 *                    that identifies it. This function is implemented using
 *                    complex declarations.
 *
 *   Plan:            It is not necessary
 *
 *   Time to Develope: 10 minutes
 *
 *   Register of Revisions:
 *
 *   DATE       RESPONSIBLE  COMMENT
 *   -----------------------------------------------------------------------
 *   Oct 06/14  J.C.Giraldo  Initial implementation
 *
 *******************************************************************************/

double
Evaluate_Function_V1(int n, double value)
{
    return (*function[n])(value);

} /* Evaluate_Function_V1 */
