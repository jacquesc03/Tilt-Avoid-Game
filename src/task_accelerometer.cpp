/*
 * task_accelerometer.c
 *
 *  Created on: May 2, 2023
 *      Author: jacqu
 */

#include "main.h"

volatile uint32_t ACC_DIR = 0;
uint32_t accHighLimit = 2100;
uint32_t accLowLimit = 1900;

void Task_Accelerometer_Timer(void *pvParameters)
 {
     while(1)
     {
         /*
          * Start the ADC conversion
          */
         ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

         /*
          * Delay 50mS
          */
         vTaskDelay(pdMS_TO_TICKS(50));

     }
 }

void Task_Accelerometer_Bottom_Half(void *pvParameters){
    player_t dir; // current direction
    player_t prev_dir; // previous direction

    // set defaults in struct variables
    dir.player_color = NO_COLOR;
    prev_dir.player_color = NO_COLOR;
    prev_dir.move_direction = MOVE_CENTER;
    dir.x_position = -1;
    uint32_t ulEventsToProcess;

    // determines
    while(1){ // determines if board is being tilted to the left, to the right, or in the center
        ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        if(ACC_DIR > accHighLimit){
            dir.move_direction = MOVE_RIGHT;
        }else if(ACC_DIR < accLowLimit){
            dir.move_direction = MOVE_LEFT;
        }else{
            dir.move_direction = MOVE_CENTER;
        }

        // sends direction information to task_player to move the player, doesn't update unless there is a change
        if(dir.move_direction != prev_dir.move_direction) {
            xQueueSend(Queue_Player, &dir, 0);
        }
        prev_dir = dir;
    }
}

void ADC14_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    ACC_DIR = ADC14->MEM[0]; // Read the value and clear the interrupt
    ADC14->CLRIFGR0 |= ADC14_CLRIFGR0_CLRIFG1;

    vTaskNotifyGiveFromISR(Task_Accelerometer_Bottom_Half_Handle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

}
