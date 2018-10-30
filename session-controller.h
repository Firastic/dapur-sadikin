/* File : session-handler.h */
/* Dapur SADIKIN Game Session Manager & Handler */

#ifndef SESSION_CTRL_H
#define SESSION_CTRL_H

#include "data_structure/integer_table.h"
#include "data_structure/queue.h"
#include "data_structure/graph.h"
#include "data_structure/tree.h"



typedef enum {
  MAIN_MENU,
  IN_GAME,
  CREDITS
} GameState;

void CreatePlayer();

#endif
