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
case 14: MOV( edi, _[rbp-2] ); break;
case 15: MOV( 0, _[rbp-3] );   break;
case 16: MOV( 1, _[rbp-4] );   break;
case 17: CMP( 0, _[rbp-2] );   break;
case 18: JNE( 2 );             break;
case 19: MOV( 0, _[rbp-1] );   break;
case 20: JMP( 21 );            break;
case 21: CMP( 1, _[rbp-2] );   break;
case 22: JNE( 2 );             break;
case 23: MOV( 1, _[rbp-1] );   break;
case 24: JMP( 17 );            break;
case 25: MOV( 2, _[rbp-6] );   break;
case 26: MOV( _[rbp-6], eax ); break;
case 27: CMP( _[rbp-2], eax ); break;
case 28: JG( 11 );             break;
case 29: MOV( _[rbp-3], eax ); break;
case 30: ADD( _[rbp-4], eax ); break;
case 31: MOV( eax, _[rbp-5] ); break;
case 32: MOV( _[rbp-4], eax ); break;
case 33: MOV( eax, _[rbp-3] ); break;
case 34: MOV( _[rbp-5], eax ); break;
case 35: MOV( eax, _[rbp-4] ); break;
case 36: MOV( _[rbp-6], eax ); break;
case 37: ADD( 1, eax );        break;
case 38: MOV( eax, _[rbp-6] ); break;
case 39: JMP( -14 );           break;
case 40: MOV( _[rbp-5], eax ); break;
case 41: MOV( eax, _[rbp-1] ); break;
case 42: MOV( _[rbp-1], eax ); break;
case 43: POP( rbp );           break;
case 44: RET();                break;

} /* switch */

++rip;

} /* for */

} /* main */
