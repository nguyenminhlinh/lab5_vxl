/*
 * uart_fsm.c
 *
 *  Created on: Dec 25, 2022
 *      Author: minhl
 */


#include <uart_fsm.h>
#include<stdio.h>
#include <string.h>
UART_HandleTypeDef huart2;
ADC_HandleTypeDef hadc1;

int STATE = 0;
int ADC_value;

char str[50];

void uart_communiation_fsm(){
	switch(STATE){
	case 0:
		if(FINISH == 1){
			FINISH = 0;
			if(strncmp(line_of_command,"RST",3) == 0 || strncmp(line_of_command,"rst",3) == 0){
				ADC_value = HAL_ADC_GetValue(&hadc1);
				STATE = 1;
				setTimer1(3000);
			}
			if(strncmp(line_of_command,"RST",3) != 0 && strncmp(line_of_command,"rst",3) != 0){
				STATE = 3;
			}
		}
		break;
	case 1:
		HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "\r\n!ADC = %d#\r", ADC_value),1000);
		STATE = 2;

		break;
	case 3:
		HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "\r\nWrong begin command\r"),1000);
		//HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, line_of_command),1000);
		STATE = 0;
		break;
	case 2:
		if(FINISH == 1){
			FINISH = 0;
			if(strncmp(line_of_command,"OK",2) != 0 && strncmp(line_of_command,"ok",2) != 0){
					HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "\r\n Wrong end command\r"),1000);
					//HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, line_of_command),1000);
				}
				if(strncmp(line_of_command,"OK",2) == 0 || strncmp(line_of_command,"ok",2) == 0){
					STATE = 0;
					setTimer1(3000);
				}

		}

		if(timer1_flag==1){
			STATE = 1;
			setTimer1(3000);
		}
		break;
	default:
		break;
	}
}
