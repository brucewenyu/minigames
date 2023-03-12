#pragma once
#ifndef BOX_MAN_S_
#define BOX_MAN_S_

void initimages();
void movesteps();
void getcontrol(enum _DIRECTION direct);
void changemap(struct _POS* pos, enum _PROPS prop);
#endif // !BOX_MAN_S_