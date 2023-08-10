#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n;
double value, result;

#ifdef DRIVER

/* ---------------------- Prototype of Tested Function ---------------------- */

double Evaluate_Function_V4(int n, double value);

/* ------------------------ Driver for Embedded Test ------------------------ */

/*******************************************************************************
 *
 *   For testing purposes compile source code using:
 *   gcc -DDRIVER code.c -o code
 *
 *   Once the code has been widely tested, generate object code using:
 *   gcc -c code.c
 *
 ******************************************************************************/

int main(int argc, char *argv[])
{
    if (argc != 3)
        fprintf(stderr, "Usage: %s n value\n", argv[0]);
    else
    {
        n = atoi(argv[1]);
        value = atof(argv[2]);

        if (n >= 0 && n <= 15)
        {
            result = Evaluate_Function_V4(n, value);
            fprintf(stdout, "Function%d( %f ) = %f\n", n, value, result);
        }
        else
            fprintf(stderr, "n must be an integer between 0 and 15\n");
    }

    return 0;

} /* main */

#endif

/*FN****************************************************************************
 *
 *   Evaluate_Function_V4( int n, double value )
 *
 *   Return:          Value of function number n
 *
 *   Purpose:         This function evaluates a value according to an integer
 *                    that identifies it. This function is implemented using
 *                    proposition with if without else.
 *
 *   Plan:
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
Evaluate_Function_V4(int n, double value)
{
    double result;

    if (n == 0)
        result = acos(value);
    if (n == 1)
        result = asin(value);
    if (n == 2)
        result = atan(value);
    if (n == 3)
        result = ceil(value);
    if (n == 4)
        result = cos(value);
    if (n == 5)
        result = cosh(value);
    if (n == 6)
        result = exp(value);
    if (n == 7)
        result = fabs(value);
    if (n == 8)
        result = floor(value);
    if (n == 9)
        result = log(value);
    if (n == 10)
        result = log10(value);
    if (n == 11)
        result = sin(value);
    if (n == 12)
        result = sinh(value);
    if (n == 13)
        result = sqrt(value);
    if (n == 14)
        result = tan(value);
    if (n == 15)
        result = tanh(value);

    return (result);

} /* Evaluate_Function_V4 */
