//
//  Othello.h
//  ReversiGL
//
//  Created by RafalP on 25.10.2013.
//
//

#ifndef __ReversiGL__Othello__
#define __ReversiGL__Othello__

struct field {
	char pos[8][8];
	int turn;
};

int move(struct field *f,int x,int y);
double eval(struct field *f,int noop,int depth);
double eval_pos(struct field *f,char my,char his);
int eval_endpos(struct field *f,char my,char his);
int mustpass(struct field *f);
void bestmove(struct field *f,int depth);
int bestmoveisdone(void);
int gameover(struct field *f);
void get_scores(int *_red,int *_green,struct field *f,char my,char his);

//=========================================
// NEW METHODS
//=========================================

//int move2(struct field *f,int x,int y);
int move2(struct field *f,int x,int y, bool useHelper=false);
int mustpass2(struct field *f);
int gameover2(struct field *f);

int moveHelper(struct field *f);

#endif /* defined(__ReversiGL__Othello__) */
