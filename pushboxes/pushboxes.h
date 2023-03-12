#pragma once
#ifndef BOX_MAN_H_
#define BOX_MAN_H_

#define RATIO 66
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 768
#define START_X 88
#define START_Y 100
#define ROWS 9
#define COLUMNS 12

#define KEY_UP    'w'

#define KEY_LEFT  'a'
#define KEY_RIGHT 'd'
#define KEY_DOWN  's'
#define KEY_QUIT  'q'

#define KEY_NORTH  72
#define KEY_SOUTH  80
#define KEY_EAST  77
#define KEY_WEST  75

enum _PROPS {
	WALL,
	FLOOR,
	BOX_DES,
	MAN,
	BOX,
	HIT,
	ALL
};

enum _DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct _POS {
	int x;
	int y;
};


typedef enum _DIRECTION DIRECTION;
typedef enum  _PROPS PROPS;
typedef struct _POS POS;

void initimages();
void movesteps();
void getcontrol(DIRECTION direct);
void changemap(POS* pos, PROPS prop);
bool isgameover();
void gameover();
#endif // !BOX_MAN_H_