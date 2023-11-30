/*
 * Tasks.c
 *
 *  Created on: Nov 30, 2023
 *      Author: Phong
 */

#include "Tasks.h"

void led_orange(){
	HAL_GPIO_TogglePin(orange_GPIO_Port, orange_Pin);
}

void led_pink(){
	HAL_GPIO_TogglePin(pink_GPIO_Port, pink_Pin);
}

void led_purple(){
	HAL_GPIO_TogglePin(purple_GPIO_Port, purple_Pin);
}

void led_red(){
	HAL_GPIO_TogglePin(red_GPIO_Port, red_Pin);
}

void led_white(){
	HAL_GPIO_TogglePin(white_GPIO_Port, white_Pin);
}
