/*
 * task_light_sensor.h
 *
 *  Created on: May 2, 2023
 *      Author: jacqu
 */

#ifndef TASK_LIGHT_SENSOR_H_
#define TASK_LIGHT_SENSOR_H_

#include "main.h"
#include "math.h"

#define OPT3001_SLAVE_ADDRESS 0x44
#define OPT_INTERRUPT_PIN 11
#define RESULT_REG 0x00
#define CONFIG_REG 0x01
#define LOWLIMIT_REG 0x02
#define HIGHLIMIT_REG 0x03
#define MANUFACTUREID_REG 0x7E
#define DEVICEID_REG 0x7F

typedef enum {
    RED,
    BLUE,
    GREEN,
} COLOR;


void Task_Light_Sensor_Timer(void *pvParameters);

void Task_Light_Sensor_Bottom_Half(void *pvParameters);

float light_sensor_read_lux(void);

#endif /* TASK_LIGHT_SENSOR_H_ */
