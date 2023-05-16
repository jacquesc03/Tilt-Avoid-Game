/*
 * task_screen_redraw.c
 *
 *  Created on: May 3, 2023
 *      Author: jacqu
 */

#include "task_screen_redraw.h"

void Task_Screen_Redraw(void *pvParameters) {
    int i;
    bool collision;
    int collision_count = 0; // keeps track of if there is a collision
    while(1) {

        // player and obstacle data
        player_t screen_player;
        obstacle_t* obstacles_ptr;

        xQueueReceive(Queue_Screen_Player, &screen_player, 0);
        xQueueReceive(Queue_Screen_Obstacles, &obstacles_ptr, 0);

        // resets LCD to black
        lcd_draw_rectangle(64, 64, 140, 140, LCD_BLACK);

        // loops through obstacles array and finds the ones that are active and draws those to the screen
        for(i = 0; i < NUM_OBSTACLES; i++) {
            if((obstacles_ptr + i)->active) {
                lcd_draw_image((obstacles_ptr + i)->x, (obstacles_ptr + i)->y, 32, 32, thwomp_mario, LCD_RED, LCD_BLACK);
                if((obstacles_ptr + i)->y == 140) { // turns the obstacle off if it reaches the end of the LCD
                    xSemaphoreTake(Sem_Obstacle_Array, portMAX_DELAY);
                    obstacles[i].active = false; // makes obstacle inactive
                    xSemaphoreGive(Sem_Obstacle_Array);
                }
                // checks each iteration if there is a collision between player and obstacle
                collision = detect_collision(screen_player.x_position, 120, (obstacles_ptr + i)->x, (obstacles_ptr + i)->y);
                if(collision) {
                    collision_count++;
                }
            }
        }
        uint16_t fColor;
        switch(screen_player.player_color) { // assigns 16-bit color of player based on initial LUX value
        case PLAYER_RED:
            fColor = LCD_RED;
            break;
        case PLAYER_BLUE:
            fColor = LCD_BLUE;
            break;
        case PLAYER_GREEN:
            fColor = LCD_GREEN;
        }

        // draw 24x24 player with x_position based on accelerometer input
        lcd_draw_rectangle(screen_player.x_position, 120, 24, 24, fColor);

        if(collision_count > 0) { // notifies buzzer if there is a collision to signify game end
            xTaskNotifyGive(Task_Buzzer_Handle);
            collision_count = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(30));
    }
}
// detects collisions between player and obstacle
bool detect_collision(uint16_t player_x, uint16_t player_y, uint16_t obstacle_x, uint16_t obstacle_y)
{
    // convert unsigned to signed value so that absolute value math works
    int16_t signed_player_x = (int16_t) player_x;
    int16_t signed_player_y = (int16_t) player_y;
    int16_t signed_obstacle_x = (int16_t) obstacle_x;
    int16_t signed_obstacle_y = (int16_t) obstacle_y;

    // finds change in x and y between obstacle and player
    int16_t dx = abs(signed_player_x - signed_obstacle_x);
    int16_t dy = abs(signed_player_y - signed_obstacle_y);

    // check if the distance between the centers is less than the sum of the radii
    if (dx < (24/2 + 32/2) && dy < (24/2 + 32/2)) { // 24x24 for player, 32x32 for obstacle
        return true;
    }
    return false;
}


