/*
 * OS.h
 *
 * Created: 11/27/2023 9:52:00 AM
 *  Author: M3gZ
 */ 



#ifndef OS_H_
#define OS_H_

#include "../LIB/Std_Types.h"

typedef void (*fncPtr)(void);           /**< Function pointer for registering tasks. */

#define MAX_NUM_OF_TASKS            ((u8)3)
#define HYPER_PERIOD                ((u8)6)

typedef enum
{
	SUSPENDED,
	BLOCKED,
	READY
} OS_state;


/*Task Control Block*/
typedef struct
{
	fncPtr      function;
	OS_state    task_state;
	u8          task_Periodicity;
	u8          Task_tick_counter;
	u8			First_delay;
} OS_struct;


typedef enum
{
	OK_FB,
	NOK_HYPER_PERIOD_VIOLATION,
	NOK_TASK_COUNT_VIOLATION,
	NOK_NULL_PTR,
	NOK_INIT
} OS_feedback;


OS_feedback OS_TaskCreate(fncPtr task, u8 default_time_burst, OS_state default_state, u8 delay);

void OS_Task_Handler(void);

void OS_TaskExecution(void);


#endif /* OS_H_ */