#include <avr/io.h>
#include <stdint.h>

#include "usart.h"

/**
 * \brief               Initialize UART0
 * \param[in]           ubbr: uart bit rate
 *                      ubbr = (F_CPU / 15 / baud) - 1
 */
void
usart_init(uint16_t ubbr) {

   UCSR0A = (1 << U2X1);

   // Set baud rate
   UBRR0H = (uint8_t) (ubbr >> 8);
   UBRR0L = (uint8_t) (ubbr);

   // Enable receiver and transmitter
   UCSR0B = (1 << RXEN0) | (1 << TXEN0);

   // Set frame format:
   // 8 bits
   // 1 stop bit
   // No parity
   UCSR0C = 
      (0 << UCSZ02) | (1 << UCSZ01) | (1 << UCSZ00) // 8 bit word size
    | (0 << USBS0) // 1 stop bit
    | (0 << UPM00) | (0 << UPM01) // No parity
   ;

}

void 
usart_transmit(uint8_t data) {
   // Wait for empty USART buffer
   while ( !( UCSR0A & (1 << UDRE0) ) );

   UDR0 = data;
}

void
usart_transmit_str(char str[], int str_len) {

   for (int i = 0; i < str_len; i++) {
      usart_transmit(str[i]);
   }
}

uint8_t
usart_receive() {
   // Wait for data to be received in USART buffer
   while ( !(UCSR0A & (1 << RXC0)) );

   return UDR0;
}
