#ifndef PEER_H_
#define PEER_H_

#include "data.h"

void generatePeer(Position* pos, int available_level[MAX_LEVEL-2]);
void nextPeer(Field* field, int score, Position next2peer);
int fallPeer(Field* field);

#endif