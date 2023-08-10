/* Ruler 1         2         3         4         5         6         7        */

/********************************** Headers ***********************************/

/* ------------------------ Inclusion of Std Headers ------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// #include "bench.h"

#define LOOPS 10000000

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
double Evaluate_Function_V2(int n, double value);
double Evaluate_Function_V3(int n, double value);
double Evaluate_Function_V4(int n, double value);
double Evaluate_Function_V5(int n, double value);

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
            register int temp;

            Time_Since_Previous();
            for (temp = 0; temp < LOOPS; temp++)
                result = Evaluate_Function_V5(n, value);

            fprintf(stdout, "%E\tFunction%d( %f ) = %f\n",
                    Time_Since_Previous() / (double)LOOPS, n, value, result);
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
 *   Time to Develope: 3 minutes
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

/*FN****************************************************************************
 *
 *   Evaluate_Function_V2( int n, double value )
 *
 *   Return:          Value of function number n
 *
 *   Purpose:         This function evaluates a value according to an integer
 *                    that identifies it. This function is implemented using
 *                    proposition with if with nested else.
 *
 *   Plan:            It is not necessary
 *
 *   Time to Develope: 40 minutes
 *
 *   Register of Revisions:
 *
 *   DATE       RESPONSIBLE  COMMENT
 *   -----------------------------------------------------------------------
 *   Oct 06/14  J.C.Giraldo  Initial implementation
 *
 *******************************************************************************/

double
Evaluate_Function_V2(int n, double value)
{
    double result;

    if (n < 8)
        if (n < 4)
            if (n < 2)
                if (n < 1) /* n==0 */
                    result = acos(value);
                else /* n==1 */
                    result = asin(value);
            else if (n < 3) /* n==2 */
                result = atan(value);
            else /* n==3 */
                result = ceil(value);
        else if (n < 6)
            if (n < 5) /* n==4 */
                result = cos(value);
            else /* n==5 */
                result = cosh(value);
        else if (n < 7) /* n==6 */
            result = exp(value);
        else /* n==7 */
            result = fabs(value);
    else if (n < 12)
        if (n < 10)
            if (n < 9) /* n==8 */
                result = floor(value);

            else /* n==9 */
                result = log(value);
        else if (n < 11) /* n==10 */
            result = log10(value);
        else /* n==11 */
            result = sin(value);
    else if (n < 14)
        if (n < 13) /* n==12 */
            result = sinh(value);
        else /* n==13 */
            result = sqrt(value);
    else if (n < 15) /* n==14 */
        result = tan(value);
    else /* n==15 */
        result = tanh(value);

    return (result);

} /* Evaluate_Function_V2 */

/*FN****************************************************************************
 *
 *   Evaluate_Function_V3( int n, double value )
 *
 *   Return:          Value of function number n
 *
 *   Purpose:         This function evaluates a value according to an integer
 *                    that identifies it. This function is implemented using
 *                    proposition with if with nested else.
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
Evaluate_Function_V3(int n, double value)
{
    double result;

    if (n == 0)
        result = acos(value);
    else if (n == 1)
        result = asin(value);
    else if (n == 2)
        result = atan(value);
    else if (n == 3)
        result = ceil(value);
    else if (n == 4)
        result = cos(value);
    else if (n == 5)
        result = cosh(value);
    else if (n == 6)
        result = exp(value);
    else if (n == 7)
        result = fabs(value);
    else if (n == 8)
        result = floor(value);
    else if (n == 9)
        result = log(value);
    else if (n == 10)
        result = log10(value);
    else if (n == 11)
        result = sin(value);
    else if (n == 12)
        result = sinh(value);
    else if (n == 13)
        result = sqrt(value);
    else if (n == 14)
        result = tan(value);
    else
        result = tanh(value);

    return (result);

} /* Evaluate_Function_V3 */

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