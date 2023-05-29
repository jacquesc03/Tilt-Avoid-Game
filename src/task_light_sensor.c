
#include "task_light_sensor.h"

void Task_Light_Sensor_Timer(void *pvParameters) {
    while(1) {
        // delay for 5 seconds
        vTaskDelay(pdMS_TO_TICKS(1000));
        xTaskNotifyGive(Task_Light_Sensor_Bottom_Half_Handle);
    }
}

// task no longer used, we decided to change the way the ambient light sensor is used in the program
void Task_Light_Sensor_Bottom_Half(void *pvParameters) {

    // receive notification from timer to update color information
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    // reads light value
    float light = light_sensor_read_lux();

    player_t playerColor; // current playerColor
    player_t prevPlayerColor; // previous playerColor

    // default value to compare to
    prevPlayerColor.player_color = PLAYER_RED;

    // indicate that this function is not changing direction,
    // allows for use of one queue between two tasks
    playerColor.move_direction = NO_DIRECTION;
    prevPlayerColor.move_direction = NO_DIRECTION;

    while(1) { // changes color of the player based on LUX values
        if(light < 200.0)
        {
            playerColor.player_color = PLAYER_BLUE;
        }
        else if (light < 500.0)
        {
            playerColor.player_color = PLAYER_GREEN;
        }
        else
        {
            playerColor.player_color = PLAYER_RED;
        }

        // send player color if there is a change
        if(playerColor.player_color != prevPlayerColor.player_color) {
            xQueueSend(Queue_Player, &playerColor, portMAX_DELAY);
        }

        // updates light variable
        prevPlayerColor = playerColor;
        vTaskDelay(pdMS_TO_TICKS(20));
        light = light_sensor_read_lux();
    }
}

// read LUX value using formula provided in OPT3001 Datasheet
float light_sensor_read_lux(void)
{
    uint16_t result_reg = i2c_read_16(OPT3001_SLAVE_ADDRESS,RESULT_REG);
    uint16_t exponent = (result_reg>>12) & 0b111;
    uint16_t fractional = result_reg & 0x0FFF;
    float LSB_Size = 0.01*pow(2,exponent);
    float lux = LSB_Size * fractional;

    return lux;
}

