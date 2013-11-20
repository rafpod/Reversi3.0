//
//  Othello.cpp
//  ReversiGL
//
//  Created by RafalP on 25.10.2013.
//
//
#include "cocos2d.h"
#include "Othello.h"


#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "othello.h"


using namespace cocos2d;

static int turner(struct field *f,int sx,int sy,int dx,int dy,char my,char his)
{
    /*
     sx = row of board
     sy = column of board
     dx = move direction on x axis
     dy = move direction on y axis
     my = my pawn, could be 'x' or 'o'
     his = opponent's pawn, could be 'x' or 'o'
     */
    
    int n,cnt=0,x,y;
    
    x=sx; y=sy;
    for (n=1; n<8; n++) {
        x+=dx; //new position of pawn on x axis
        y+=dy; // -;- on y axis
        if (x<0 || x>7 || y<0 || y>7) return 0; //check bounds of board, if are not correct return 0
        if (f->pos[y][x]!=his) break; //if new position is not the same as pos of opponent(so empty or my) then break(end loop)
        cnt++; //if yes then means that opponent's pawn is adjacent to my pawn on new position, so increase cnt
    }
    if (f->pos[y][x]!=my) return 0; //if my pawn is not located on new position during the last iteration then return 0
    if (!cnt) return 0; //if cnt == 0 then return 0
    
    x=sx; y=sy;
    for (n=1; n<8; n++) {
        x+=dx;
        y+=dy;
        if (f->pos[y][x]!=his) break;
        f->pos[y][x]=my; //assign my pawn on the board
    }
    
    return cnt;
}

int move(struct field *f,int x,int y)
{
    int cnt=0;
    char my,his,empty='.'; //pawns
    
    if ((f->turn&1)) { my='X'; his='O'; } else { my='O'; his='X'; }
    //my='X';
    //his='O';
    
    if (f->pos[y][x]!=empty) return 0; //field on the board is not empty, then return 0, if is, check 8 direction of move
    cnt+=turner(f,x,y, 1, 0,my,his);
    cnt+=turner(f,x,y,-1, 0,my,his);
    cnt+=turner(f,x,y, 0, 1,my,his);
    cnt+=turner(f,x,y, 0,-1,my,his);
    cnt+=turner(f,x,y, 1, 1,my,his);
    cnt+=turner(f,x,y,-1, 1,my,his);
    cnt+=turner(f,x,y, 1,-1,my,his);
    cnt+=turner(f,x,y,-1,-1,my,his);
    
    if (!cnt) return 0; // no movement, so return 0
    f->pos[y][x]=my;
    f->turn++;
    
    return cnt;
}

static int turner2(struct field *f,int sx,int sy,int dx,int dy,char my,char his){
    /*
     sx = row of board
     sy = column of board
     dx = move direction on y axis (on row index)
     dy = move direction on x axis (on column index)
     my = my pawn, could be 'x' or 'o'
     his = opponent's pawn, could be 'x' or 'o'
     */
    
    int n,cnt=0,x,y;
    x=sx; y=sy;
    
    for (n=1; n<8; n++) {
        x+=dx; //new position of pawn on y axis (next row)
        y+=dy; // -;- on x axis(next column)
        if (x<0 || x>7 || y<0 || y>7) return 0; //check bounds of board, if are not correct return 0
        if (f->pos[x][y]!=his) break; //if new position is not the same as pos of opponent(so empty or my) then break(end loop)
        cnt++; //if yes then means that opponent's pawn is adjacent to my pawn on new position, so increase cnt
    }
    if (f->pos[x][y]!=my) return 0; //if my pawn is not located on new position during the last iteration then return 0, when my pawn is not at the end, exit
    if (!cnt) return 0; //if cnt == 0 then return 0
    
    x=sx; y=sy;
    for (n=1; n<8; n++) {
        x+=dx;
        y+=dy;
        if (f->pos[x][y]!=his) break;
        f->pos[x][y]=my; //assign my pawn on the board
    }

    
    return cnt;
}

/**
If user can't move method return 0, else return 1
*/
int move2(struct field *f,int x,int y, bool useHelper)
{
    int cnt=0;
    char my,his,empty='.'; //pawns
    
    //=========
    //Change Player
    //=========
    //if ((f->turn&1)) { my='O'; his='X'; } else { my='X'; his='O'; }
    if ((f->turn&1)) { my='X'; his='O'; } else { my='O'; his='X'; }
   // my='X';
   // his='O';
    
    
    if (f->pos[x][y]!=empty) return 0; //field on the board is not empty, then return 0, if is, check 8 direction of move
    cnt+=turner2(f,x,y, 1, 0,my,his);
    cnt+=turner2(f,x,y,-1, 0,my,his);
    cnt+=turner2(f,x,y, 0, 1,my,his);
    cnt+=turner2(f,x,y, 0,-1,my,his);
    cnt+=turner2(f,x,y, 1, 1,my,his);
    cnt+=turner2(f,x,y,-1, 1,my,his);
    cnt+=turner2(f,x,y, 1,-1,my,his);
    cnt+=turner2(f,x,y,-1,-1,my,his);
    
    
    if (!cnt) return 0; // no movement, no one pawn will be turning to other one, so return 0*/
    
    if (useHelper) {
        f->pos[x][y]='Z';
    }
    else
    {
        f->pos[x][y]=my; //refresh data board with new positions of pawns
        f->turn++;
    }
    
    
    return cnt;
}
/*
int move3(struct field *f,int x,int y)
{
    int cnt=0;
    char my,his,empty='.'; //pawns
    
    //=========
    //Change Player
    //=========
    if ((f->turn&1)) { my='O'; his='X'; } else { my='X'; his='O'; }
    // my='X';
    // his='O';
    
    //CCLOG("Pos: %c",f->pos[x][y]);
    if (f->pos[x][y]!=empty) return 0; //field on the board is not empty, then return 0, if is, check 8 direction of move
    cnt+=turner2(f,x,y, 1, 0,my,his);
    cnt+=turner2(f,x,y,-1, 0,my,his);
    cnt+=turner2(f,x,y, 0, 1,my,his);
    cnt+=turner2(f,x,y, 0,-1,my,his);
    cnt+=turner2(f,x,y, 1, 1,my,his);
    cnt+=turner2(f,x,y,-1, 1,my,his);
    cnt+=turner2(f,x,y, 1,-1,my,his);
    cnt+=turner2(f,x,y,-1,-1,my,his);
    
    //CCLOG("CNT: %i", cnt);
    
    if (!cnt) return 0; // no movement, no one pawn will be turning to other one, so return 0//
    f->pos[x][y]='Z'; //refresh data board with new positions of pawns
    //f->turn++;
    
    //CCLOG("NewPos: %c",f->pos[x][y]);
    
    return cnt;
}
*/

int moveHelper(struct field *f)
{
    
    int cnt=0;
    char my,his,empty='.'; //pawns
    
    struct field tmp[64];
    int counter = 0;
    
    tmp[0] = *f;
    
    struct field temp = *f;
    
    //=========
    //Change Player
    //=========
    //if ((f->turn&1)) { my='O'; his='X'; } else { my='X'; his='O'; }
    if ((f->turn&1)) { my='X'; his='O'; } else { my='O'; his='X'; }
    // my='X';
    // his='O';
    
    for (int x=7; x>=0; x--) {
        for (int y = 0; y<8; y++) {
            tmp[counter]=*f;
            move2(&tmp[counter], x, y, true); //move3(&tmp[counter], x, y);
            counter++;
            
            
        }
    }
    
    
    counter =0;
    while(counter<64){
        for (int x=7; x>=0; x--) {
            for (int y = 0; y<8; y++) {
                
                if(tmp[counter].pos[x][y] == 'Z'){
                    f->pos[x][y] = 'Z';
                    //CCLOG("Temp[%i] [%i] -> %c",x,y, tmp[counter].pos[x][y]);
                }
                              
            }
        }
        counter++;
    }
    
    return cnt;
}


double eval_pos(struct field *f,char my,char his)
{
	static double value[8][8]={
		{ 0.064,-0.032, 0.016,-0.008,-0.008, 0.016,-0.032, 0.064},
		{-0.032,-0.032, 0.000, 0.000, 0.000, 0.000,-0.032,-0.032},
		{ 0.016, 0.000, 0.004, 0.002, 0.002, 0.004, 0.000, 0.016},
		{-0.008, 0.000, 0.002, 0.000, 0.000, 0.002, 0.000,-0.008},
		{-0.008, 0.000, 0.002, 0.000, 0.000, 0.002, 0.000,-0.008},
		{ 0.016, 0.000, 0.004, 0.002, 0.002, 0.004, 0.000, 0.016},
		{-0.032,-0.032,-0.000, 0.000, 0.000, 0.000,-0.032,-0.032},
		{ 0.064,-0.032, 0.016,-0.008,-0.008, 0.016,-0.032, 0.064},
	};
	double score=0.0;
	int x,y;
	char empty='.';
	
	if (f->pos[0][0]==empty) {
		for (y=0; y<4; y++) {
			for (x=0; x<4; x++) {
				if (f->pos[y][x]==my) score+=value[y][x];
				else if (f->pos[y][x]==his) score-=value[y][x];
			}
		}
	} else if (f->pos[0][0]==my) score+=value[0][0];
	else score-=value[0][0];
    
	if (f->pos[0][7]==empty) {
		for (y=0; y<4; y++) {
			for (x=4; x<8; x++) {
				if (f->pos[y][x]==my) score+=value[y][x];
				else if (f->pos[y][x]==his) score-=value[y][x];
			}
		}
	} else if (f->pos[0][7]==my) score+=value[0][7];
	else score-=value[0][7];
	
	if (f->pos[7][0]==empty) {
		for (y=4; y<8; y++) {
			for (x=0; x<4; x++) {
				if (f->pos[y][x]==my) score+=value[y][x];
				else if (f->pos[y][x]==his) score-=value[y][x];
			}
		}
	} else if (f->pos[7][0]==my) score+=value[7][0];
	else score-=value[7][0];
	
	if (f->pos[7][7]==empty) {
		for (y=4; y<8; y++) {
			for (x=4; x<8; x++) {
				if (f->pos[y][x]==my) score+=value[y][x];
				else if (f->pos[y][x]==his) score-=value[y][x];
			}
		}
	} else if (f->pos[7][7]==my) score+=value[7][7];
	else score-=value[7][7];
    
	return score;
}

int eval_endpos(struct field *f,char my,char his)
{
	int x,y,score;
	
	for (y=score=0; y<8; y++) {
		for (x=0; x<8; x++) {
			if (f->pos[y][x]==my) score++;
			else if (f->pos[y][x]==his) score--;
		}
    }
	return score;
}

void get_scores(int *_red,int *_green,struct field *f,char my,char his)
{
    int x,y,red,green;
	
	for (y=red=green=0; y<8; y++) {
		for (x=0; x<8; x++) {
			if (f->pos[y][x]==my) red++;
			else if (f->pos[y][x]==his) green++;
		}
    }
    if (_red) *_red=red;
    if (_green) *_green=green;
}

static int maxdepth=6;
static int cancel=0;

double eval(struct field *f,int noop,int depth)
{
    int x,y;
    float score=0.0,bestscore=-99.9;
    struct field tmp;
    char my,his;
	
	if (cancel) pthread_exit(NULL);
    
    if ((f->turn&1)) { my='X'; his='O'; } else { my='O'; his='X'; }
	
    if (depth>=maxdepth) return eval_pos(f,my,his);
    
    noop++;
    
    tmp=*f;
    for (y=0; y<8; y++) {
        for (x=0; x<8; x++) {
            if (move(&tmp,x,y)) {
                noop=0;
                score=-eval(&tmp,noop,depth+1);
                if (score>bestscore) bestscore=score;
                tmp=*f;
            }
        }
    }
    if (noop==1) {
        tmp.turn++;
        return -eval(&tmp,noop,depth);
    } else if (noop==2) {
        return eval_endpos(f,my,his);
    } else {
        return bestscore;
    }
}

/*
 If user can't do movement of pawn, then function return 1, if can return 0
 */
int mustpass(struct field *f)
{
	int x,y;
	struct field tmp;
	
	tmp=*f;
	for (y=0; y<8; y++) {
		for (x=0; x<8; x++) {
			if (move(&tmp,x,y)) return 0;
			
		}
	}
	return 1;
}

/**
If user can't do movement of pawn, then function return 1, if can return 0
 */
int mustpass2(struct field *f)
{
	int x,y;
	struct field tmp;
	
	tmp=*f;
	for (x=0; x<8; x++) {
		for (y=0; y<8; y++) {
			if (move2(&tmp,x,y)) return 0;
			
		}
	}
	return 1;
}


int gameover(struct field *f)
{
	int ret;
	if (!mustpass(f)) return 0; //user can move so return 0
	f->turn++;
	ret=mustpass(f);
	f->turn--;
	return ret;
}

/**
If game is over return 1, else return 0
*/
int gameover2(struct field *f)
{
	int ret;
	if (!mustpass2(f)) return 0;
	f->turn++;
	ret=mustpass2(f);
	f->turn--;
	return ret;
}


static int randomize=0;
int _bestmove(struct field *f)
{
	int x,y,best=64;
	struct field tmp;
	double bestscore=-99.9,score;
	
#ifdef DEBUG
	printf("--- turn=%d, depth=%d, rand=%d\n",f->turn,maxdepth,randomize);
#endif
	tmp=*f;
	for (y=0; y<8; y++) {
		for (x=0; x<8; x++) {
			if (move(&tmp,x,y)) {
				score=-eval(&tmp,0,0);
				if (randomize>0) score+=(rand()%randomize)/100.0f;
#ifdef DEBUG
				printf("%d,%d: %.4f\n",x,y,score);
#endif
				if (score>bestscore) {
					bestscore=score;
					best=x+y*8;
				}
				tmp=*f;
			}
		}
	}
	return best;
}

volatile static int best=-1;

static void* PosixThreadMainRoutine(void* data)
{
	// ERROR MUST FIX
    struct field *f=(field*)data;
	
	best=_bestmove(f);
	
    return NULL;
}

int bestmoveisdone(void)
{
	int tmp;
	if (best!=-1) {
		tmp=best;
		best=-1;
		return tmp;
	}
	return -1;
}

void bestmove(struct field *f,int diff)
{
    pthread_attr_t attr;
    static pthread_t posixThreadID=0;
    int returnVal;
	
	switch (diff) {
		case 1:	maxdepth=0; randomize=500; break;
		default:
		case 2:	maxdepth=1; randomize=10; break;
		case 3:	maxdepth=4; randomize=0; break;
	}
	srand(time(NULL));
	
	if (posixThreadID) {
		cancel=1;
		pthread_join(posixThreadID,NULL);
		cancel=0;
	}
	
    returnVal = pthread_attr_init(&attr);
    assert(!returnVal);
    returnVal = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    assert(!returnVal);
	
    int threadError = pthread_create(&posixThreadID, &attr, &PosixThreadMainRoutine, f);
	
    returnVal = pthread_attr_destroy(&attr);
    assert(!returnVal);
    assert(!threadError);
}
