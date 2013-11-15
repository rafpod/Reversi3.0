//
//  AI.h
//  ReversiGL
//
//  Created by RafalP on 14.11.2013.
//
//

#ifndef __ReversiGL__AI__
#define __ReversiGL__AI__

#include "Othello.h"

double eval2(struct field *f,int noop,int depth);
double eval_pos2(struct field *f,char my,char his);
int eval_endpos2(struct field *f,char my,char his);
void bestmove2(struct field *f,int depth);
int bestmoveisdone2(void);



#endif /* defined(__ReversiGL__AI__) */
