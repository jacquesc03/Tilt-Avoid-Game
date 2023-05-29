/*
 * task_player.c
 *
 *  Created on: May 2, 2023
 *      Author: jacqu
 */

#include "task_player.h"

void Task_Player(void *pvParameters) {
    player_t current_status;
    current_status.move_direction = MOVE_CENTER;

    // chooses initial color of the player
    float light = light_sensor_read_lux();
    if(light < 200.0)
    {
        current_status.player_color = PLAYER_BLUE;
    }
    else if (light < 500.0)
    {
        current_status.player_color = PLAYER_GREEN;
    }
    else
    {
        current_status.player_color = PLAYER_RED;
    }
    current_status.x_position = 64;
    player_t temp;
    while(1) {
        if(xQueueReceive(Queue_Player, &temp, 0) == pdTRUE) {
            if(temp.move_direction != NO_DIRECTION) {
                current_status.move_direction = temp.move_direction; // assigns move direction from accelerometer task
            }
        }

        // moves x position 5 pixels to the left or right depending on acceleration direction
        switch (current_status.move_direction) {
        case MOVE_LEFT:
            if(current_status.x_position - 5 < 12) { // accounts for if player reaches left end of LCD
                current_status.x_position = 12;
            } else {
                current_status.x_position -= 5;
            }
            break;
        case MOVE_RIGHT:
            if(current_status.x_position + 5 > 116) { // accounts for if player reaches right end of LCD
                current_status.x_position = 116;
            } else {
                current_status.x_position += 5;
            }
            break;
        }

        xQueueSend(Queue_Screen_Player, &current_status, pdMS_TO_TICKS(3)); // send information to task_screen_redraw
        vTaskDelay(pdMS_TO_TICKS(PLAYER_TASK_DELAY_MS));
    }
}
