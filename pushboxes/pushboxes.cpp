#include <graphics.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include<conio.h>
#include "pushboxes.h"

using namespace std;

#define VALIDCONDITION(pos) (pos.x >= 0 && pos.x < ROWS) && (pos.y >= 0 && pos.y < COLUMNS)

struct _POS man;

IMAGE images[ALL];

int map[ROWS][COLUMNS] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 1, 4, 1, 0, 2, 1, 0, 2, 1, 0, 0},
	{0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0},
	{0, 1, 0, 2, 0, 1, 1, 4, 1, 1, 1, 0},
	{0, 1, 1, 1, 0, 3, 1, 1, 1, 4, 1, 0},
	{0, 1, 2, 1, 1, 4, 1, 1, 1, 1, 1, 0},
	{0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};


int main(void) {
	initimages();
	movesteps();

	closegraph();
	system("pause");
	return 0;
}

void initimages() {
	IMAGE bg_img;
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	loadimage(&bg_img, _T("bg.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	putimage(0, 0, &bg_img);

	loadimage(&images[WALL], _T("wall.bmp"), RATIO, RATIO, true);
	loadimage(&images[FLOOR], _T("floor.bmp"), RATIO, RATIO, true);
	loadimage(&images[BOX_DES], _T("dst.bmp"), RATIO, RATIO, true);
	loadimage(&images[MAN], _T("people.bmp"), RATIO, RATIO, true);
	loadimage(&images[BOX], _T("box.bmp"), RATIO, RATIO, true);
	loadimage(&images[HIT], _T("box.bmp"), RATIO, RATIO, true);

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (map[i][j] == MAN) {
				man.x = i;
				man.y = j;
			}

			putimage(START_X + j * RATIO, START_Y + i * RATIO, &images[map[i][j]]);
		}
	}
}

void movesteps() {
	bool quit = false;
	do
	{
		if (_kbhit()) {
			char ch = _getch();
			if (ch == KEY_UP || ch == KEY_NORTH) {
				getcontrol(UP);
			}
			else if (ch == KEY_DOWN || ch == KEY_SOUTH) {
				getcontrol(DOWN);
			}
			else if (ch == KEY_LEFT || ch == KEY_WEST) {
				getcontrol(LEFT);
			}
			else if (ch == KEY_RIGHT || ch == KEY_EAST) {
				getcontrol(RIGHT);
			}
			else if (ch == KEY_QUIT) {
				quit = true;
			}

			if (isgameover()) {
				quit = true;
				gameover();
				system("pause");
			}
		}


		Sleep(100);
	} while (quit == false);
}

void getcontrol(DIRECTION direct) {
	POS next_pos = man;
	POS next_next_pos = man;
	switch (direct)
	{
	case UP:
		next_pos.x--;
		next_next_pos.x -= 2;
		break;
	case DOWN:
		next_pos.x++;
		next_next_pos.x += 2;
		break;
	case LEFT:
		next_pos.y--;
		next_next_pos.y -= 2;
		break;
	case RIGHT:
		next_pos.y++;
		next_next_pos.y += 2;
		break;
	default:
		break;
	}

	if (VALIDCONDITION(next_pos) && map[next_pos.x][next_pos.y] == FLOOR) {
		changemap(&next_pos, MAN);
		changemap(&man, FLOOR);
		man = next_pos;
	}
	else if (VALIDCONDITION(next_next_pos) && map[next_pos.x][next_pos.y] == BOX) {
		if (map[next_next_pos.x][next_next_pos.y] == FLOOR) {
			changemap(&next_next_pos, BOX);
			changemap(&next_pos, MAN);
			changemap(&man, FLOOR);
			man = next_pos;
		}
		else if (map[next_next_pos.x][next_next_pos.y] == BOX_DES) {
			changemap(&next_next_pos, HIT);
			changemap(&next_pos, MAN);
			changemap(&man, FLOOR);
			man = next_pos;
		}
	}
}

void changemap(POS* pos, PROPS prop) {
	map[pos->x][pos->y] = prop;
	putimage(START_X + pos->y * RATIO, START_Y + pos->x * RATIO, &images[prop]);
}

bool isgameover() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (map[i][j] == BOX_DES) return false;
		}
	}

	return true;
}

void gameover() {
	settextcolor(WHITE);
	RECT rec = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	settextstyle(20, 0, _T("ËÎÌå"));
	drawtext(_T("¹§Ï²ÄúÍ¨¹Ø£¡£¡£¡"), &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}