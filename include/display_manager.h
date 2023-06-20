/*
 * display_manager.h
 *
 *  Created on: May 29, 2023
 *      Author: jacqu
 */

#pragma once

class Display {
public:

    Display();
    QueueHandle_t getQueueScreenPlayer();
    QueueHandle_t getQueueScreenObstacles();

    // TODO: Potentially make a function that accesses the Queues


private:

    void taskScreenRedraw(void *pvParameters);
    bool detectCollision(uint16_t playerX, uint16_t playerY, uint16_t obstacleX, uint16_t obstacleY);

    // handles
    TaskHandle_t Task_Screen_Redraw_Handle;
    QueueHandle_t Queue_Screen_Player;
    QueueHandle_t Queue_Screen_Obstacles;

};
