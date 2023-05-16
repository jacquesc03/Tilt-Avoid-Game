/*
 * setup.c
 *
 *  Created on: May 2, 2023
 *      Author: jacqu
 */

#include "setup.h"


void light_sensor_init(void)
{
    // Initialize OPT3001
    // sets conversion time to 100ms, turns on continuous conversion, leaves everything else to default
    i2c_init();
    i2c_write_16(OPT3001_SLAVE_ADDRESS,CONFIG_REG,0xC610);
}

void accelerometer_init(void){
    P6->SEL0 |= BIT1; //Makes accelerometer in x direction an analog input
    P6->SEL1 |= BIT1;

    ADC14->CTL0 = ADC14_CTL0_SHT02 | ADC14_CTL0_SHP;
    ADC14->CTL0 |= ADC14_CTL0_CONSEQ_1;

    ADC14->CTL1 = ADC14_CTL1_RES_2;

    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_14;

    ADC14->MCTL[1] |= ADC14_MCTLN_EOS;

    ADC14->IER0 |= ADC14_IER0_IE1;

    NVIC_EnableIRQ(ADC14_IRQn);
    NVIC_SetPriority(ADC14_IRQn, 2);

    ADC14->CTL0 |= ADC14_CTL0_ON;
}

// loops through and creates all of the obstacles with dummy variables
void setup_obstacles(void) {
    int i;
    xSemaphoreTake(Sem_Obstacle_Array, portMAX_DELAY);
    for(i = 0; i < NUM_OBSTACLES; i++) {
        obstacles[i].x = 0;
        obstacles[i].y = 0;
        obstacles[i].obstacle_type = SHAPE1;
        obstacles[i].active = false;
    }
    xSemaphoreGive(Sem_Obstacle_Array);
}

// initializes S2 Button on BoosterPack
void MKII_BUTTON2_INIT(void) {
    P3->DIR &= ~BIT5;
}

// detects if button is being pressed
bool MKII_BUTTON2_BEING_PRESSED(void) {
    if((P3->IN & BIT5) == 32) {
        return false;
    } else {
        return true;
    }
}
