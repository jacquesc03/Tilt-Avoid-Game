/*
 * player_manager.h
 *
 *  Created on: May 29, 2023
 *      Author: jacqu
 */

#ifndef INCLUDE_PLAYER_MANAGER_H_
#define INCLUDE_PLAYER_MANAGER_H_

class Player {
public:
    Player();
    ~Player();
    int getXPosition();
    int getYPosition();
    move_direction_t getMoveDirection();
    player_color_t getPlayerColor();
    TaskHandle_t getTaskPlayerHandle();
    QueueHandle_t getQueuePlayerHandle();
    void setXPosition(int x_position);
    void setYPosition(int y_position);
    void setMoveDirection(move_direction_t move_direction);
    void setPlayerColor(player_color_t player_color);
    void createTasks();
    void deleteTasks();

    // enum for player direction
    enum move_direction_t {
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_CENTER,
        NO_DIRECTION
    };

private:

    void Task_Player(void *pvParameters);
    int x_position;
    int y_position;
    move_direction_t move_direction;
    player_color_t player_color;
    TaskHandle_t Task_Player_Handle;
    QueueHandle_t Queue_Player;

};


// enum for player color
typedef enum { // TODO: define this as a color in the Display manager
    PLAYER_RED,
    PLAYER_GREEN,
    PLAYER_BLUE,
    NO_COLOR
} player_color_t;
#endif /* INCLUDE_PLAYER_MANAGER_H_ */
