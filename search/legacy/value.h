#ifndef __VALUE_H
#define __VALUE_H

#include "board.h"
#include <climits>

// positive value for black superiority, vice cetera
int v_func(Board& bd, int next_player);
int v_assist(int lian, int huo, int current_pos_player, int next_player);

#endif