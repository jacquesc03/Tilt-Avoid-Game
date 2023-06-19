/*
 * obstacle.h
 *
 *  Created on: May 29, 2023
 *      Author: jacqu
 */

#pragma once

class Obstacle {


public:
    Obstacle(int x, int y, obstacle_type_t obstacleType, bool active);


private:

    // obstacle specific data
    int x;
    int y;
    obstacle_type_t obstacleType;
    bool active;
};

class ObstacleSystem {
public:

    // TODO: Might be smart to include a function that creates the semaphore
    ObstacleSystem(int numObstacles); // will initialize obstacles array
    void createTasks();
    SemaphoreHandle_t getSemObstacleArray();
    Obstacle getObstacle(int index);

private:
    Obstacle obstacles[numObstacles];
    int numObstacles;
    SemaphoreHandle_t Sem_Obstacle_Array;

    // tasks
    void taskObstacles(void *pvParameters);
    void taskObstaclesTimer(void *pvParameters);

    // task handles
    TaskHandle_t Task_Obstacles_Handle;
    TaskHandle_t Task_Obstacles_Timer_Handle;

};


typedef enum {
    SHAPE1,
    SHAPE2,
    SHAPE3
} obstacle_type_t;
