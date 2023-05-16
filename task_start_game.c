
#include "task_start_game.h"

void Task_Start_Game(void *pvParameters) {
    while(1) {
        if(MKII_BUTTON2_BEING_PRESSED()) { // start game if button is pressed

            // reset LCD
            lcd_draw_rectangle(64, 64, 128, 128, LCD_BLACK);

            // initialize all of the tasks
            xTaskCreate(Task_Obstacles, "Task_Obstacles", configMINIMAL_STACK_SIZE, NULL, 2, &Task_Obstacles_Handle);
            xTaskCreate(Task_Obstacles_Timer, "Task_Obstacles_Timer", configMINIMAL_STACK_SIZE, NULL, 2, &Task_Obstacles_Timer_Handle);
            xTaskCreate(Task_Player, "Task_Player", configMINIMAL_STACK_SIZE, NULL, 2, &Task_Player_Handle);
            xTaskCreate(Task_Accelerometer_Timer, "Task_Accelerometer_Timer", configMINIMAL_STACK_SIZE, NULL, 2, &Task_Accelerometer_Timer_Handle);
            xTaskCreate(Task_Accelerometer_Bottom_Half, "Task_Accelerometer_Bottom_Half", configMINIMAL_STACK_SIZE, NULL, 3, &Task_Accelerometer_Bottom_Half_Handle);
            xTaskCreate(Task_Buzzer, "Task_Buzzer", configMINIMAL_STACK_SIZE, NULL, 3, &Task_Buzzer_Handle);
            xTaskCreate(Task_Light_Sensor_Timer, "Task_Light_Sensor_Timer", configMINIMAL_STACK_SIZE, NULL, 2, &Task_Light_Sensor_Timer_Handle);
            xTaskCreate(Task_Light_Sensor_Bottom_Half, "Task_Light_Sensor_Bottom_Half", configMINIMAL_STACK_SIZE, NULL, 3, &Task_Light_Sensor_Bottom_Half_Handle);
            xTaskCreate(Task_Screen_Redraw, "Task_Screen_Redraw", configMINIMAL_STACK_SIZE, NULL, 2, &Task_Screen_Redraw_Handle);

            ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // wait for notification from buzzer that signifies end of game, resets game
            vTaskDelete(Task_Obstacles_Handle);
            vTaskDelete(Task_Obstacles_Timer_Handle);
            vTaskDelete(Task_Player_Handle);
            vTaskDelete(Task_Screen_Redraw_Handle);
            vTaskDelete(Task_Accelerometer_Timer_Handle);
            vTaskDelete(Task_Accelerometer_Bottom_Half_Handle);
            vTaskDelete(Task_Buzzer_Handle);
            vTaskDelete(Task_Light_Sensor_Timer_Handle);
            vTaskDelete(Task_Light_Sensor_Bottom_Half_Handle);
            vTaskDelete(Task_Screen_Redraw_Handle);
        }
    }
}
