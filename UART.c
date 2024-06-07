#include "UART.h"
#include <string.h>

static uint8_t move_flag = 0; // Used to track if color should be changed
static uint8_t recv_char;

/**
 * @brief Initialize USART2
 */
void UART_init() {

	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;	// Enable clock for GPIOA
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;	// Enable clock for USART2

	// Configure PA2 and 3 to be alternate function
	GPIOA->MODER &= ~(GPIO_MODER_MODE2 | GPIO_MODER_MODE3);
	GPIOA->MODER |= ((2 << GPIO_MODER_MODE2_Pos) | (2 << GPIO_MODER_MODE3_Pos));
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2 | GPIO_AFRL_AFSEL3);

	// Configure USART alternate function
	GPIOA->AFR[0] |= ((7 << GPIO_AFRL_AFSEL2_Pos) | (7 << GPIO_AFRL_AFSEL3_Pos));
	USART2->BRR |= (USARTDIV);	// Set baud rate

	// Enable USART, transmit, recieve, recieve interrupts
	USART2->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE);

	NVIC->ISER[1] = (1 << (USART2_IRQn & 0x1F));	// Enable USART2 inteerupts
	__enable_irq();	// Inteerupt global enable

}

/**
 * @brief Send a null terminated string over UART
 */
void UART_print(const char *string) {
	int i = 0;

	// block until avaliable to write to TDR
	while(!(USART2->ISR & USART_ISR_TC));

	// While string != null terminator
	while(string[i] != '\0') {
		USART2->TDR = string[i];

		// block until avaliable to write to TDR
		while(!(USART2->ISR & USART_ISR_TC));
		i++;
	}

	// Send null terminator
	USART2->TDR = '\0';
}

/**
 * @brief Converted an unsigned integer to a string
 */
void int_to_str(uint16_t conv, char *str) {
	int curr_int = 0;	// current int being extracted
	int curr_int_index = 0;
	char t_str_buff[6];	// Will fit any 16-bit number and a null terminator
	int new_str_index = 0;

	// Check if string is 0
	if(conv == 0) {
		str[0] = '0';
		str[1] = '\0';
		return;
	}

	// While the current int being extracted != 0, get the next digit
	while(conv != 0) {
		curr_int = conv % 10;
		t_str_buff[curr_int_index] = curr_int + '0';
		curr_int_index ++;
		conv /= 10;
	}

	// Insert values into the string
	while(curr_int_index > 0) {
		curr_int_index--;
		str[new_str_index] = t_str_buff[curr_int_index];
		new_str_index++;
	}

	// Null terminate string
	str[new_str_index] = '\0';
}

/**
 * @brief onvert float to str, with 3 decimal places. Fails at vals >= 100
 */
void float_to_str(float conv, char *str) {
	uint16_t whole_part, dec_part;

	// Get whole and decimal parts of float
	whole_part = (uint16_t)conv;
	dec_part = (conv - whole_part) * 1000;

	// Convert whole part to string, increment str ptr
	int_to_str(whole_part, str);
	str += 1;

	// Check num of digits
	if(whole_part > 9) {
		str += 1;
	}

	// Insert dec point, increment string pointer
	str[0] = '.';
	str += 1;

	if(dec_part < 100) {
		str[0] = '0';
		str += 1;
	}

	if(dec_part < 10) {
		str[0] = '0';
		str += 1;
	}

	// Convert dec part to string
	int_to_str(dec_part, str);

}

/**
 * @brief Send an escape code with the string argument.
 */
void UART_ESC_code(const char *code) {
	char str_to_send[MAX_STRING];

	str_to_send[0] = 0x1b;
	strcpy(str_to_send + OFFSET_TO_CODE, code);
	UART_print(str_to_send);
}


