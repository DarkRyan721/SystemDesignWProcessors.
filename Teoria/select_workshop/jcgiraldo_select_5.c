#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n;
double value, result;

#ifdef DRIVER

/* ---------------------- Prototype of Tested Function ---------------------- */

double Evaluate_Function_V5(int n, double value);

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
            result = Evaluate_Function_V5(n, value);
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
 *   Evaluate_Function_V5( int n, double value )
 *
 *   Return:          Value of function number n
 *
 *   Purpose:         This function evaluates a value according to an integer
 *                    that identifies it. This function is implemented using
 *                    proposition with switch-case.
 *
 *   Plan:            It is not necessary
 *
 *   Time to Develope: 10 minutes
 *
 *   Register of Revisions:
 *
 *   DATE       RESPONSIBLE  COMMENT
 *   -----------------------------------------------------------------------
 *   Oct 19/14  J.C.Giraldo  Initial implementation
 *
 *******************************************************************************/

double
Evaluate_Function_V5(int n, double value)
{
    double result;

    switch (n)
    {

    case 0:
        result = acos(value);
        break;

    case 1:
        result = asin(value);
        break;

    case 2:
        result = atan(value);
        break;

    case 3:
        result = ceil(value);
        break;

    case 4:
        result = cos(value);
        break;

    case 5:
        result = cosh(value);
        break;

    case 6:
        result = exp(value);
        break;

    case 7:
        result = fabs(value);
        break;

    case 8:
        result = floor(value);
        break;

    case 9:
        result = log(value);
        break;

    case 10:
        result = log10(value);
        break;

    case 11:
        result = sin(value);
        break;

    case 12:
        result = sinh(value);
        break;

    case 13:
        result = sqrt(value);
        break;

    case 14:
        result = tan(value);
        break;

    case 15:
        result = tanh(value);
        break;
    }

    return (result);

} /* Evaluate_Function_V5 */
