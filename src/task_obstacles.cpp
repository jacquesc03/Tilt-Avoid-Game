/*
 * task_obstacles.c
 *
 *  Created on: May 2, 2023
 *      Author: jacqu
 */

#include "task_obstacles.h"

obstacle_t obstacles[NUM_OBSTACLES];
volatile bool init_obstacles = true;

void Task_Obstacles(void *pvParameters) {
    if(init_obstacles) {
        // fills obstacle array with dummy values
        setup_obstacles();
        init_obstacles = false;
    }
    int i = 0;

    while(1) {
        for(i = 0; i < NUM_OBSTACLES; i++) {
            // use of semaphores ensures that there is no race condition with obstacle array
            xSemaphoreTake(Sem_Obstacle_Array, portMAX_DELAY);
            if(obstacles[i].active == true) {
                if((obstacles[i].y + 5) > 140) {
                    // ensures that image doesn't go past the screen
                    obstacles[i].y = 140;
                } else {
                    obstacles[i].y += 5;
                    // makes obstacles fall down screen at 5 pixels per loop
                }
            }
            xSemaphoreGive(Sem_Obstacle_Array);
        }

        // pass in pointer to array, send obstacle information to task_screen_redraw to draw obstacles
        // to screen
        obstacle_t *obstacles_ptr = obstacles;
        xQueueSend(Queue_Screen_Obstacles, &obstacles_ptr, pdMS_TO_TICKS(15));
        xSemaphoreGive(Sem_Obstacle_Array); // done with using array, give up semaphore
        vTaskDelay(pdMS_TO_TICKS(70));
    }
}

// generates random obstacles at a fixed rate
void Task_Obstacles_Timer(void *pvParameters) {
    //Randomizes the location of the obstacles
    srand(time(NULL));
    int i = 0;

    while(init_obstacles == true) {};
        while (1)
        {
            // Generate a random number between 8 and 120
            // Min and max column values so that new obstacle fits on screen
            int random_column = rand() % 97 + 16;
            xSemaphoreTake(Sem_Obstacle_Array, portMAX_DELAY);
            for (i = 0; i < NUM_OBSTACLES; i++) { // iterates and finds obstacles that aren't on screen
                if(obstacles[i].active == false) {
                    obstacles[i].x = random_column; // sets column value to random number

                    // Sets obstacle to the top of screen,
                    // 12 is lowest number so that 32x32 obstacle fits on screen
                    obstacles[i].y = 12;
                    obstacles[i].obstacle_type = SHAPE1; // sets image
                    obstacles[i].active = true; // indicates that it is on screen
                    break;
                }
            }
            xSemaphoreGive(Sem_Obstacle_Array);
            // Delay the task for some time
            vTaskDelay(pdMS_TO_TICKS(2500));
        }
}
