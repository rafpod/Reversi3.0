//
//  AI.cpp
//  ReversiGL
//
//  Created by RafalP on 14.11.2013.
//
//

#include "AI.h"
#include "cocos2d.h"

#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace cocos2d;


double eval_pos2(struct field *f,char my,char his)
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
		for (x=3; x>=0; x--) {
			for (y=0; y<4; y++) {
				if (f->pos[x][y]==my) score+=value[x][y];
				else if (f->pos[x][y]==his) score-=value[x][y];
			}
		}
	} else if (f->pos[0][0]==my) score+=value[0][0];
	else score-=value[0][0];
    
	if (f->pos[0][7]==empty) {
		for (x=3; x>=0; x--) {
			for (y=4; y<8; y++) {
				if (f->pos[x][y]==my) score+=value[x][y];
				else if (f->pos[x][y]==his) score-=value[x][y];
			}
		}
	} else if (f->pos[0][7]==my) score+=value[0][7];
	else score-=value[0][7];
	
	if (f->pos[7][0]==empty) {
		for (x=7; x>=4; x--) {
			for (y=0; y<4; y++) {
				if (f->pos[x][y]==my) score+=value[x][y];
				else if (f->pos[x][y]==his) score-=value[x][y];
			}
		}
	} else if (f->pos[7][0]==my) score+=value[7][0];
	else score-=value[7][0];
	
	if (f->pos[7][7]==empty) {
		for (x=7; x>=4; x--) {
			for (y=4; y<8; y++) {
				if (f->pos[x][y]==my) score+=value[x][y];
				else if (f->pos[x][y]==his) score-=value[x][y];
			}
		}
	} else if (f->pos[7][7]==my) score+=value[7][7];
	else score-=value[7][7];
    
	return score;
}


int eval_endpos2(struct field *f,char my,char his)
{
	int x,y,score;
	
	for (x=7,score=0; x>=0; x--) {
		for (y=0; y<8; y++) {
			if (f->pos[x][y]==my) score++;
			else if (f->pos[x][y]==his) score--;
		}
    }
	return score;
}


static int maxdepth=6;
static int cancel=0;

double eval2(struct field *f,int noop,int depth)
{
    int x,y;
    float score=0.0,bestscore=-99.9;
    struct field tmp;
    char my,his;
	
	if (cancel) pthread_exit(NULL);
    
    //if ((f->turn&1)) { my='O'; his='X'; } else { my='X'; his='O'; }
     if ((f->turn&1)) { my='X'; his='O'; } else { my='O'; his='X'; }
	
    if (depth>=maxdepth) return eval_pos2(f,my,his);
    
    noop++;
    
    tmp=*f;
    for (x=7; x>=0; x--) {
        for (y=0; y<8; y++) {
            if (move2(&tmp,x,y)) {
                noop=0;
                score=-eval2(&tmp,noop,depth+1);
                if (score>bestscore) bestscore=score;
                tmp=*f;
            }
        }
    }
    if (noop==1) {
        tmp.turn++;
        return -eval2(&tmp,noop,depth);
    } else if (noop==2) {
        return eval_endpos2(f,my,his);
    } else {
        return bestscore;
    }
}

static int randomize=0;
int _bestmove2(struct field *f)
{
	int x,y,best=64;
	struct field tmp;
	double bestscore=-99.9,score;
	
#ifdef DEBUG
	printf("--- turn=%d, depth=%d, rand=%d\n",f->turn,maxdepth,randomize);
#endif
	tmp=*f;
	for (x=7; x>=0; x--) {
		for (y=0; y<8; y++) {
			if (move2(&tmp,x,y)) {
				score=-eval2(&tmp,0,0);
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
	//=====================
    //ERROR MUST FIX
    //if here is not casting 'data' compiler shouts 'error', so here is needed use cast to desirable type
    //=====================
     struct field *f= (field*)data;
     
     best=_bestmove2(f);
    
    return NULL;
}

int bestmoveisdone2(void)
{
	int tmp;
	if (best!=-1) {
		tmp=best;
		best=-1;
		return tmp;
	}
	return -1;
}

void bestmove2(struct field *f,int diff)
{
    pthread_attr_t attr;
    static pthread_t posixThreadID=0; //ID of thread
    int returnVal;
	
	switch (diff) {
		case 0:	maxdepth=0; randomize=500; break;
		default:
		case 1:	maxdepth=1; randomize=10; break;
		case 2:	maxdepth=4; randomize=0; break;
        case 3:	maxdepth=5; randomize=80; break;
        case 4:	maxdepth=5; randomize=0; break;
	}
	srand(time(NULL));
	
	if (posixThreadID) {
		cancel=1;
        
        //===================================
        //should be ID to joinable type of thread?(now is detached thread)
        //Join so current thread is waiting for indicated thread will be ended
        //===================================
		pthread_join(posixThreadID,NULL);
		cancel=0;
	}
	
    returnVal = pthread_attr_init(&attr);
    assert(!returnVal);
    returnVal = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); //set type of thread
    assert(!returnVal);
	
    //=======================================
    //create thread(ID, attribute, function which is executed in thread, argument which is delivered to function)
    // Attribute can be NULL, if attr is NULL then thread will use default values of attribute
    //=======================================
    int threadError = pthread_create(&posixThreadID, &attr, &PosixThreadMainRoutine, f);
	
    returnVal = pthread_attr_destroy(&attr);
    assert(!returnVal); //popup error if returnvalue !=0, default if assert(0) then popup error
    assert(!threadError);
}



