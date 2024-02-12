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
case 15: SUB( 4, rsp );        break;
case 16: MOV( edi, _[rbp-2] ); break;
case 17: CMP( 0, _[rbp-2] );   break;
case 18: JE( 10 );             break;
case 19: MOV( _[rbp-2], eax ); break;
case 20: MOV( _[rbp-2], ecx ); break;
case 21: SUB( 1, ecx );        break;
case 22: MOV( ecx, edi );      break;
case 23: MOV( eax, _[rbp-3] ); break;
case 24: CALL( -12 );          break;
case 25: MOV( _[rbp-3], ecx ); break;
case 26: ADD( eax, ecx );      break;
case 27: MOV( ecx, _[rbp-1] ); break;
case 28: JMP( 2 );             break;
case 29: MOV( _[rbp-2], eax ); break;
case 30: MOV( eax, _[rbp-1] ); break;
case 31: MOV( _[rbp-1], eax ); break;
case 32: ADD( 4, rsp );        break;
case 33: POP( rbp );           break;
case 34: RET();                break;

} /* switch */

++rip;

} /* for */

} /* main */
