/*
 * vga.c
 *
 *  Created on: Jun 6, 2024
 *      Author: jimmy
 */

#include "vga.h"

/*
 * @brief delay briefly for vga_write() function
 */
static inline void brief_delay();

/*
 * @brief Initialize VGA peripheral
 */
void vga_init() {
	// Enable GPIOC Clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

	// Initialize PC0-10 as output
	GPIOC->MODER &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1 | GPIO_MODER_MODE2 | GPIO_MODER_MODE3 |
			GPIO_MODER_MODE4 | GPIO_MODER_MODE5 | GPIO_MODER_MODE6 | GPIO_MODER_MODE7 | GPIO_MODER_MODE8 | GPIO_MODER_MODE9 | GPIO_MODER_MODE10);
	GPIOC->MODER |= (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0 | GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0 |
			GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0 | GPIO_MODER_MODE8_0 | GPIO_MODER_MODE9_0 | GPIO_MODER_MODE10_0);
}


/*
 * @brief Write a value to VGA framebuffer
 */
void vga_write(uint8_t x_cord, uint8_t y_cord, uint8_t color) {
	// Reset color and position intermediate registers
	GPIOC->ODR |= RST_MASK;
	brief_delay();
	GPIOC->ODR &= ~RST_MASK;
	brief_delay();

	// Send x coodrdinate to fpga
	GPIOC->ODR &= ~DATA_MASK;
	GPIOC->ODR |= x_cord;
	GPIOC->ODR |= BUFF_WRITE_MASK;
	brief_delay();
	GPIOC->ODR &= ~BUFF_WRITE_MASK;
	brief_delay();

	// Send y coordinate to fpga
	GPIOC->ODR &= ~DATA_MASK;
	GPIOC->ODR |= y_cord;
	GPIOC->ODR |= BUFF_WRITE_MASK;
	brief_delay();
	GPIOC->ODR &= ~BUFF_WRITE_MASK;
	brief_delay();

	// Send color to fpga
	GPIOC->ODR &= ~DATA_MASK;
	GPIOC->ODR |= color;
	GPIOC->ODR |= BUFF_WRITE_MASK;
	brief_delay();
	GPIOC->ODR &= ~BUFF_WRITE_MASK;
	brief_delay();

	// Trigger write to framebuffer
	GPIOC->ODR |= VGA_WRITE_MASK;
	brief_delay();
	GPIOC->ODR &= ~VGA_WRITE_MASK;
	brief_delay();
}


/*
 * @brief Clear VGA screen (write black)
 */
void vga_clear_screen() {
	for(int i = 0; i < 80; i++) {
		for(int j = 0; j < 60; j++) {
			vga_write(i, j, 0);
		}
	}
}

static inline void brief_delay() {
	for(int i = 0; i < DELAY_VAL; i++);
}
