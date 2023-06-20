//
//#ifndef MAIN_H_
//#define MAIN_H_
//
#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>
//
///* Game header files */
//#include "task_accelerometer.h"
//#include "task_buzzer.h"
//#include "task_light_sensor.h"
//#include "task_obstacles.h"
//#include "task_player.h"
//#include "task_screen_redraw.h"
//#include "setup.h"
//#include "i2c.h"
//#include "image.h"
//#include "lcd.h"
//#include "task_start_game.h"
//
//// colors for LCD
//#define LCD_RED 0xF800
//#define LCD_GREEN 0x07E0
//#define LCD_BLUE 0x001F
//#define LCD_BLACK 0x0000
//
//
//// enum for obstacle type
//typedef enum {
//    SHAPE1,
//    SHAPE2,
//    SHAPE3
//} obstacle_type_t;
//
//// struct for player, contains information about the player
//typedef struct {
//    move_direction_t move_direction;
//    player_color_t player_color;
//    int x_position;
//} player_t;
//
//// struct for obstacle, contains information about the obstacle
//struct obstacle_t;
//
//typedef struct {
//    int x;
//    int y;
//    obstacle_type_t obstacle_type;
//    bool active;
//} obstacle_t;
//
//
//extern SemaphoreHandle_t Sem_Obstacle_Array;
//extern QueueHandle_t Queue_Screen_Player;
//extern QueueHandle_t Queue_Screen_Obstacles;
//extern QueueHandle_t Queue_Player;
//
//extern obstacle_t obstacles[NUM_OBSTACLES]; // holds obstacles
//
//extern TaskHandle_t Task_Start_Game_Handle;
//extern TaskHandle_t Task_Accelerometer_Timer_Handle;
//extern TaskHandle_t Task_Accelerometer_Bottom_Half_Handle;
//extern TaskHandle_t Task_Screen_Redraw_Handle;
//extern TaskHandle_t Task_Buzzer_Handle;
//extern TaskHandle_t Task_Light_Sensor_Timer_Handle;
//extern TaskHandle_t Task_Light_Sensor_Bottom_Half_Handle;
//extern TaskHandle_t Task_Obstacles_Handle;
//extern TaskHandle_t Task_Obstacles_Timer_Handle;
//extern TaskHandle_t Task_Player_Handle;
//
//
//
//#endif /* MAIN_H_ */
