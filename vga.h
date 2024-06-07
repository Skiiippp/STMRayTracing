/*
 * vga.h
 *
 *  Created on: Jun 6, 2024
 *      Author: jimmy
 */

#ifndef SRC_VGA_H_
#define SRC_VGA_H_

#include "main.h"

#define BUFF_WRITE_MASK	(GPIO_ODR_OD8)	// Write to deserializer buffer
#define RST_MASK 	(GPIO_ODR_OD9)		// Reset deserializer buffer
#define VGA_WRITE_MASK (GPIO_ODR_OD10)	// Write to framebuffer
#define DATA_MASK	(0xFF);				// Clear GPIO output
#define DELAY_VAL	1					// Value for delaying between FPGA changes

void vga_init();
void vga_write(uint8_t x_cord, uint8_t y_cord, uint8_t color);
void vga_clear_screen();

#endif /* SRC_VGA_H_ */
