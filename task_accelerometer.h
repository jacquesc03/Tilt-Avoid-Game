/*
 * task_accelerometer.h
 *
 *  Created on: May 2, 2023
 *      Author: jacqu
 */

#ifndef TASK_ACCELEROMETER_H_
#define TASK_ACCELEROMETER_H_

#include "main.h"

// starts ADC14 conversion
void Task_Accelerometer_Timer(void *pvParameters);


// Uses the ADC data from Accelerometer to create a function
// that calculates the x position on the LCD based on the acceleration
void Task_Accelerometer_Bottom_Half(void *pvParameters);



#endif /* TASK_ACCELEROMETER_H_ */
