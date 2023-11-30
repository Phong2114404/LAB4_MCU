/*
 * Scheduler.c
 *
 *  Created on: Nov 30, 2023
 *      Author: Phong
 */

#include "Scheduler.h"

sTask SCH_tasks_G [SCH_MAX_TASKS];

void SCH_Init(void){
	unsigned char i;
	for(i = 0; i < SCH_MAX_TASKS; i++){
		SCH_Delete_Task(i);
	}
}

void SCH_Update(void) {
	unsigned char i;
	for(i = 0; i < SCH_MAX_TASKS; i++){
		if (SCH_tasks_G[i].pTask){
			if(SCH_tasks_G[i].Delay == 0){
				SCH_tasks_G[i].RunMe = 1;
				if(SCH_tasks_G[i].Period){
					SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
				}
			}
			else{
				SCH_tasks_G[i].Delay--;
			}
		}
	}
}

unsigned char SCH_Add_Task(void(*pFunction)(),uint32_t DELAY,uint32_t PERIOD){
	unsigned char Index = 0;
	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)){
		Index++;
	}
	if(Index == SCH_MAX_TASKS){
		return SCH_MAX_TASKS;
	}
	SCH_tasks_G[Index].pTask = pFunction;
	SCH_tasks_G[Index].Delay = DELAY;
	SCH_tasks_G[Index].Period = PERIOD;
	SCH_tasks_G[Index].RunMe = 0;
	return Index;
}

void SCH_Dispatch_Tasks(void){
	unsigned char Index = 0;
	for(Index = 0; Index < SCH_MAX_TASKS; Index++){
		if(SCH_tasks_G[Index].RunMe > 0){
			(*SCH_tasks_G[Index].pTask)();
			SCH_tasks_G[Index].RunMe -= 1;
		}
		if(SCH_tasks_G[Index].Period == 0){
			SCH_Delete_Task(Index);
		}
	}
}

unsigned char SCH_Delete_Task (uint32_t taskID) {
	unsigned char Return_code;
	if (SCH_tasks_G[taskID].pTask == 0){
		Return_code = 0;
	}
	else {
		Return_code = 1;
	}
	SCH_tasks_G[taskID].pTask = 0x0000;
	SCH_tasks_G[taskID].Delay = 0;
	SCH_tasks_G[taskID].Period = 0;
	SCH_tasks_G[taskID].RunMe = 0;
	return Return_code;
}



