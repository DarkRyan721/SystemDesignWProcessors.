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
case  4: MOV( 6, edi );        break;
case  5: CALL( 6 );            break;
case  6: XOR( ecx, ecx );      break;
case  7: MOV( eax, _[rbp-2] ); break;
case  8: MOV( ecx, eax );      break;
case  9: ADD( 4, rsp );        break;
case 10: POP( rbp );           break;
case 11: RET();                return 0;

case 12: PUSH( rbp );          break;
case 13: MOV( rsp, rbp );      break;
case 14: SUB( 4, rsp );        break;
case 15: MOV( edi, _[rbp-2] ); break;
case 16: CMP( 0, _[rbp-2] );   break;
case 17: JNE( 2 );             break;
case 18: MOV( 0, _[rbp-1] );   break;
case 19: JMP( 16 );            break;
case 20: CMP( 1, _[rbp-2] );   break;
case 21: JNE( 2 );             break;
case 22: MOV( 1, _[rbp-1] );   break;
case 23: JMP( 12 );            break;
case 24: MOV( _[rbp-2], eax ); break;
case 25: SUB( 1, eax );        break;
case 26: MOV( eax, edi );      break;
case 27: CALL( -16 );          break;
case 28: MOV( _[rbp-2], ecx ); break;
case 29: SUB( 2, ecx );        break;
case 30: MOV( ecx, edi );      break;
case 31: MOV( eax, _[rbp-3] ); break;
case 32: CALL( -21 );          break;
case 33: MOV( _[rbp-3], ecx ); break;
case 34: ADD( eax, ecx );      break;
case 35: MOV( ecx, _[rbp-1] ); break;
case 36: MOV( _[rbp-1], eax ); break;
case 37: ADD( 4, rsp );        break;
case 38: POP( rbp );           break;
case 39: RET();                break;

} /* switch */

++rip;

} /* for */

} /* main */
