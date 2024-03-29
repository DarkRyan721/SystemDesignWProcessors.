/* Ruler 1         2         3         4         5         6         7        */

/********************************** Headers ***********************************/

/* ------------------------ Inclusion of Std Headers ------------------------ */

#include <stdio.h>  // Due to fprintf
#include <stdint.h> // Due to uint32_t, uint8_t

/* ------------------------ Inclusion of Own Headers ------------------------ */

#include "x86_instruction_set.h"



/**************************** Symbolic  Constants *****************************/

#define STACK_SIZE 64

uint32_t _[STACK_SIZE];
uint32_t rsp = STACK_SIZE - 1;
uint32_t rbp = STACK_SIZE - 1;
uint32_t rip = 0, edi, esi, ecx, edx, eax;
uint32_t r8, r9;
uint8_t  ZF, CF, SF, OF;



/******************************* Main Function ********************************/

/*FN****************************************************************************
*
*   Purpose: Run the function Print().
*
*   Register of Revisions:
*
*   DATE         RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Mar 26/2023  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

int main()
{
fprintf( stdout, "rip\trsp\trbp\tedi\tesi\tedx\tecx\teax\n" );

for(;;) {

fprintf( stdout, "%d\t%d\t%X\t%X\t%X\t%X\t%X\t%X\n",
		rip, rsp, rbp, edi, esi, edx, ecx, eax );

switch( rip ) {

case  0: PUSH( rbp );          break;
case  1: MOV( rsp, rbp );      break;
case  2: SUB( 4, rsp );        break;
case  3: MOV( 0, _[rbp-1] );   break;
case  4: MOV( 5, _[rbp-2] );   break;
case  5: MOV( _[rbp-2], edi ); break;
case  6: CALL( 6 );            break;
case  7: XOR( ecx, ecx );      break;
case  8: MOV( eax, _[rbp-3] ); break;
case  9: MOV( ecx, eax );      break;
case 10: ADD( 4, rsp );        break;
case 11: POP( rbp );           break;
case 12: RET();                return 0;

case 13: PUSH( rbp );          break;
case 14: MOV( rsp, rbp );      break;
case 15: MOV( edi, _[rbp-1] ); break;
case 16: MOV( 0, _[rbp-2] );   break;
case 17: MOV( _[rbp-1], eax ); break;
case 18: MOV( eax, _[rbp-3] ); break;
case 19: CMP( 0, _[rbp-3] );   break;
case 20: JLE( 7 );             break;
case 21: MOV( _[rbp-3], eax ); break;
case 22: ADD( _[rbp-2], eax ); break;
case 23: MOV( eax, _[rbp-2] ); break;
case 24: MOV( _[rbp-3], eax ); break;
case 25: ADD( -1, eax );       break;
case 26: MOV( eax, _[rbp-3] ); break;
case 27: JMP( -9 );            break;
case 28: MOV( _[rbp-2], eax ); break;
case 29: POP( rbp );           break;
case 30: RET();                break;

} /* switch */

++rip;

} /* for */

} /* main */
