#ifndef SRC_UART_H_
#define SRC_UART_H_

#include "main.h"

#define USARTDIV 694 // USART baud rate divisor when 115.2kbps at 80MHz
#define MAX_STRING 1024		// Max input string size
#define OFFSET_TO_CODE 1	// For escape codes

void UART_init();
void UART_print(const char *string);
void UART_ESC_code(const char *code);
void int_to_str(uint16_t conv, char *str);
void float_to_str(float conv, char *str);

#endif /* SRC_UART_H_ */
