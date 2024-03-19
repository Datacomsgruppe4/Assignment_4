#include <stdint.h>

void usart_init(uint16_t ubbr);
void usart_transmit(uint8_t data);
void usart_transmit_str(char *str);
void usart_transmit_str_secure(char str[], int len);
uint8_t usart_receive();
