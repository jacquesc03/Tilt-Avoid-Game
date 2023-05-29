/*
 * task_buzzer.c
 *
 *  Created on: May 3, 2023
 *      Author: saculgrad
 */

#include <task_buzzer.h>

void play_buzzer(uint16_t ticks_period){

    // initializes pins for buzzer
    P2->DIR |= BIT7;

    P2->SEL0 |= BIT7;
    P2->SEL1 &= ~BIT7;

    // initializes PWM
    TIMER_A0->CTL = 0;

    TIMER_A0->CCR[0] = ticks_period - 1;

    TIMER_A0->CCR[4] = (ticks_period / 2) - 1;

    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;

    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK;


    TIMER32_1->CONTROL = 0; //Stop timer
    TIMER32_1->CONTROL = TIMER32_CONTROL_ONESHOT | TIMER32_CONTROL_SIZE; //Set as 32bit, one shot
    TIMER32_1->LOAD = 100000000; //Set load register with note duration

    TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK; //Clear mode
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP | TIMER_A_CTL_CLR; //Clear and start timer

    TIMER32_1->CONTROL |= TIMER32_CONTROL_ENABLE; //Start timer
    while(TIMER32_1->VALUE != 0){} //Wait until timer reaches 0

    TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK; //Turn off timer
}

void Task_Buzzer(void *pvParameters){
    BaseType_t status;

    while(1){ // waits for notification from task_screen_redraw that detects a collision, plays buzzer
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        play_buzzer(22944);

        // notifies task_start_game to reset the game
        xTaskNotifyGive(Task_Start_Game_Handle);
    }
}

