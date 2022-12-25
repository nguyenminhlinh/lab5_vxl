/*
 * command_fsm.h
 *
 *  Created on: Dec 25, 2022
 *      Author: minhl
 */

#ifndef COMMAND_FSM_H_
#define COMMAND_FSM_H_

#include "main.h"
#include "timer.h"


extern  char INDEX;
extern  char FINISH;
extern char line_of_command[50];

void command_parser_fsm();

#endif /* COMMAND_FSM_H_ */
