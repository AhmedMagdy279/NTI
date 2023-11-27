/*
 * OS.c
 *
 * Created: 11/27/2023 9:52:11 AM
 *  Author: M3gZ
 */ 



#include "OS.h"


static OS_struct taskArray [MAX_NUM_OF_TASKS];
static u8 taskCounter = 0;

OS_feedback OS_TaskCreate(fncPtr function, u8 periodicity, OS_state default_state, u8 delay)
{

	OS_feedback status = NOK_INIT;

	// Check ptr is not NULL
	if(function == NULLPTR)
	{
		status = NOK_NULL_PTR;
	}
	// Max Number of Tasks not exceeded
	else if(taskCounter >= MAX_NUM_OF_TASKS)
	{
		status = NOK_TASK_COUNT_VIOLATION;
	}
	// Hyper period violation
	else if( periodicity > HYPER_PERIOD)
	{
		status = NOK_HYPER_PERIOD_VIOLATION;
	}
	else
	{
		// Create Task
		taskArray[taskCounter].function = function;
		taskArray[taskCounter].task_Periodicity = periodicity;
		taskArray[taskCounter].task_state = default_state;
		taskArray[taskCounter].Task_tick_counter = 1;
		taskArray[taskCounter].First_delay = delay;
		// Increment # of created tasks
		taskCounter++;
		status = OK_FB;
	}
	return status;
}

/* LInked to ISR --- Time --- Task Ststes*/
void OS_Task_Handler(void)
{
	u8 Task_Id;
	for(Task_Id = 0; Task_Id<taskCounter; Task_Id++)
	{
		if(taskArray[Task_Id].task_state != SUSPENDED || taskArray[Task_Id].task_state != READY)
		{
			// Check if the Task can be set to "Ready"
			if(taskArray[Task_Id].Task_tick_counter >= taskArray[Task_Id].task_Periodicity)
			{
				taskArray[Task_Id].task_state = READY;
				taskArray[Task_Id].Task_tick_counter = 1;
			}
			else
			{
				taskArray[Task_Id].Task_tick_counter++;
			}
		}
		else
		{
			// Nothing
		}

	}
}


void OS_TaskExecution(void)
{
	u8 Task_Id;
	for(Task_Id = 0; Task_Id<taskCounter; Task_Id++)
	{
		//we need to check here for the first delay and avoid performing the task with first delay period
		if(taskArray[Task_Id].task_state == READY && taskArray[Task_Id].First_delay > 0)
		{
			taskArray[Task_Id].First_delay--;
		}
		else if(taskArray[Task_Id].task_state == READY && taskArray[Task_Id].First_delay == 0)
		{
			taskArray[Task_Id].function();
			taskArray[Task_Id].task_state = BLOCKED;
		}
		else
		{
			// Nothing
		}
	}
}
