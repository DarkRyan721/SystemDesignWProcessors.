/* Ruler 1         2         3         4         5         6         7        */

#ifndef	x86_INSTRUCTION_SET_H
#define x86_INSTRUCTION_SET_H

/* DATA MOVEMENT OPERATIONS */

#define PUSH( src )  _[--rsp]  =  src
#define  POP( dst )      dst   = _[rsp++]
#define  MOV( src, dst ) dst   =  src

/* FLOW CONTROL OPERATIONS */

#define  JMP( off )      rip  +=  off

#define   JE( off )      rip   = ( (ZF)     ? JMP( off ) : rip )
#define  JNE( off )      rip   = (!(ZF)     ? JMP( off ) : rip )
#define   JL( off )      rip   = ( (SF)     ? JMP( off ) : rip ) 
#define  JGE( off )      rip   = (!(SF)     ? JMP( off ) : rip ) 
#define  JLE( off )      rip   = ( (SF||ZF) ? JMP( off ) : rip )
#define   JG( off )      rip   = (!(SF||ZF) ? JMP( off ) : rip )

#define CALL( off ) PUSH( rip ), JMP( off )
#define  RET()       POP( rip )

/* ARITHMETIC OPERATIONS */

#define  INC( dst )      dst++
#define  DEC( dst )      dst--
#define  NEG( dst )      dst   = -dst

#define  ADD( src, dst ) dst  +=  src
#define  SUB( src, dst ) dst  -=  src
#define IMUL( src, dst ) dst  *=  src
#define IDIV( src )      edx   =  eax % src, eax /= src

#define  CMP( src, dst )    ZF = dst == src, SF = dst < src

/* BITWISE OPERATIONS */

#define  NOT( dst )      dst   = ~​dst
#define   OR( src, dst ) dst  |=  src
#define  AND( src, dst ) dst  &=  src
#define  XOR( src, dst ) dst  ^=  src

#define  SHL( src, dst ) dst <<=  src
#define  SHR( src, dst ) dst >>=  src
#define  SAL( src, dst ) dst <<=  src
#define  SAR( src, dst ) dst >>=  src

/* OTHER OPERATIONS */

#define  NOP()
#define CLTD()           edx   =  0

#endif /* x86_INSTRUCTION_SET_H */
