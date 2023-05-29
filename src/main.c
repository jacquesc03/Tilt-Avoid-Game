#include "msp.h"
#include "main.h"
#include <stdio.h>


// initialize Semaphore, Queue, and Task Handles
SemaphoreHandle_t Sem_Obstacle_Array;
QueueHandle_t Queue_Screen_Player;
QueueHandle_t Queue_Screen_Obstacles;
QueueHandle_t Queue_Player;
TaskHandle_t Task_Start_Game_Handle;
TaskHandle_t Task_Accelerometer_Bottom_Half_Handle;
TaskHandle_t Task_Accelerometer_Timer_Handle;
TaskHandle_t Task_Buzzer_Handle;
TaskHandle_t Task_Light_Sensor_Timer_Handle;
TaskHandle_t Task_Light_Sensor_Bottom_Half_Handle;
TaskHandle_t Task_Obstacles_Handle;
TaskHandle_t Task_Obstacles_Timer_Handle;
TaskHandle_t Task_Player_Handle;
TaskHandle_t Task_Screen_Redraw_Handle;

/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    light_sensor_init(); // initializes light sensor
    accelerometer_init(); // initializes accelerometer
    MKII_BUTTON2_INIT(); // initializes S2 on BoosterPack
    Crystalfontz128x128_Init(); // initialize display

    __enable_irq(); // enable interrupts

    // create queues and semaphores
    Queue_Player = xQueueCreate(1, sizeof(uint8_t));
    if(Queue_Player == NULL) {

    }
    Queue_Screen_Obstacles = xQueueCreate(1, sizeof(obstacle_t*));
    if(Queue_Screen_Obstacles == NULL) {

    }
    Queue_Screen_Player = xQueueCreate(1, sizeof(player_t));
    if(Queue_Screen_Player == NULL) {

    }
    Sem_Obstacle_Array = xSemaphoreCreateBinary();
    xSemaphoreGive(Sem_Obstacle_Array);

    // start game
    xTaskCreate(Task_Start_Game, "Task_Start_Game", configMINIMAL_STACK_SIZE, NULL, 2, &Task_Start_Game_Handle);
    vTaskStartScheduler();
    while(1){};
}

void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while(1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    while(1)
    {
    }
}
