/*
 * ili9325_fsmc.h
 *
 *  Created on: 6 рту. 2017 у.
 *      Author: l-pro
 */

#ifndef SANDBOX_ILI9325_ILI9325_FSMC_H_
#define SANDBOX_ILI9325_ILI9325_FSMC_H_


#include "stm32f7xx_hal.h"

namespace Stm32PlusPlus { namespace Display {

#define LCD_REG              (*((volatile unsigned short *) 0x60000000))
#define LCD_RAM              (*((volatile unsigned short *) (0x60000000 | 0x00020000)))

#define LCD_RESET_GPIO_Port GPIOC
#define LCD_RESET_Pin GPIO_PIN_6

class DisplayFsmcInterface {
public:

	static void init(){
		__HAL_RCC_GPIOC_CLK_ENABLE();

		GPIO_InitTypeDef init;
		init.Mode = GPIO_MODE_OUTPUT_PP;
		init.Pin = LCD_RESET_Pin;
		init.Pull = GPIO_NOPULL;
		init.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(LCD_RESET_GPIO_Port, &init);


		MPU_Region_InitTypeDef MPU_InitStruct;

		// Disable the MPU
		HAL_MPU_Disable();

		// Configure the MPU attributes for 16Mb NOR Flash
		MPU_InitStruct.Enable = MPU_REGION_ENABLE;
		MPU_InitStruct.BaseAddress = 0x60000000;
		MPU_InitStruct.Size = MPU_REGION_SIZE_1MB;
		MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
		MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
		MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
		MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
		MPU_InitStruct.Number = MPU_REGION_NUMBER1;
		MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
		MPU_InitStruct.SubRegionDisable = 0x00;
		MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
		HAL_MPU_ConfigRegion(&MPU_InitStruct);
		// Enable the MPU
		HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
	}

	static void reset(){
		HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
		HAL_Delay(10);
	}

	static void setAddress(uint16_t address){
		*((uint16_t*) 0x60000000) = address;
	}

	static void write(uint16_t value){
		*((uint16_t*) (0x60000000 | 0x00020000)) = value;
	}

	static uint16_t read(){
		return *((uint16_t*) (0x60000000 | 0x00020000));
	}

};

}}


#endif /* SANDBOX_ILI9325_ILI9325_FSMC_H_ */
