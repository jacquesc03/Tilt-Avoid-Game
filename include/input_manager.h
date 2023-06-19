/*
 * input_manager.h
 *
 *  Created on: May 29, 2023
 *      Author: jacqu
 */

#pragma once


class Inputs {

public:
    void initializeInputs();
    void createTasks();
    void deleteTasks();

    // TODO: potentially make getters for the light sensor, task handles


private:

    // accelerometer tasks/functions and IRQ
    void taskAccelerometerTimer(void *pvParameters);
    void taskAccelerometerBottomHalf(void *pvParameters);
    void ADC14IRQHandler(void);
    void accelerometerInit(void);

    // buzzer tasks/functions
    void playBuzzer(uint16_t ticksPeriod);
    void taskBuzzer(void *pvParameters);
    // TODO: probably add a initBuzzer() function when adding more features to buzzer

    // light sensor tasks/functions
    void taskLightSensorBottomHalf(void *pvParameters);
    void taskLightSensorTimer(void *pvParameters);
    float lightSensorReadLux();
    void lightSensorInit(void);

    // button functions
    void MKIIButton2Init(void);
    bool MKIIButton2BeingPressed(void);

    // Task Handles
    TaskHandle_t Task_Accelerometer_Timer_Handle;
    TaskHandle_t Task_Accelerometer_Bottom_Half_Handle;
    TaskHandle_t Task_Buzzer_Handle;
    Task_Light_Sensor_Timer_Handle;
    Task_Light_Sensor_Bottom_Half_Handle;
};

