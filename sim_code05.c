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
case  4: MOV( 4, edi );        break;
case  5: MOV( 12, esi );       break;
case  6: CALL( 6 );            break;
case  7: XOR( ecx, ecx );      break;
case  8: MOV( eax, _[rbp-2] ); break;
case  9: MOV( ecx, eax );      break;
case 10: ADD( 4, rsp );        break;
case 11: POP( rbp );           break;
case 12: RET();                return 0;

case 13: PUSH( rbp );          break;
case 14: MOV( rsp, rbp );      break;
case 15: MOV( edi, _[rbp-1] ); break;
case 16: MOV( esi, _[rbp-2] ); break;
case 17: MOV( 0, _[rbp-3] );   break;
case 18: MOV( _[rbp-1], eax ); break;
case 19: MOV( eax, _[rbp-4] ); break;
case 20: MOV( 1, _[rbp-5] );   break;
case 21: MOV( _[rbp-1], eax ); break;
case 22: CMP( _[rbp-2], eax ); break;
case 23: JLE( 2 );             break;
case 24: MOV( _[rbp-2], eax ); break;
case 25: MOV( eax, _[rbp-4] ); break;
case 26: MOV( 1, _[rbp-3] );   break;
case 27: MOV( _[rbp-3], eax ); break;
case 28: CMP( _[rbp-4], eax ); break;
case 29: JG( 17 );             break;
case 30: MOV( _[rbp-1], eax ); break;
case 31: CLTD();               break;
case 32: IDIV( _[rbp-3] );     break;
case 33: CMP( 0, edx );        break;
case 34: JNE( 7 );             break;
case 35: MOV( _[rbp-2], eax ); break;
case 36: CLTD();               break;
case 37: IDIV( _[rbp-3] );     break;
case 38: CMP( 0, edx );        break;
case 39: JNE( 2 );             break;
case 40: MOV( _[rbp-3], eax ); break;
case 41: MOV( eax, _[rbp-5] ); break;
case 42: JMP( 0 );             break;
case 43: MOV( _[rbp-3], eax ); break;
case 44: ADD( 1, eax );        break;
case 45: MOV( eax, _[rbp-3] ); break;
case 46: JMP( -20 );           break;
case 47: MOV( _[rbp-5], eax ); break;
case 48: POP( rbp );           break;
case 49: RET();                break;

} /* switch */

++rip;

} /* for */

} /* main */
