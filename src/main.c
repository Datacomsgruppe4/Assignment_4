#include <avr/io.h>
#include "UART.h"

void UART_Init(unsigned int baudrate) {
    unsigned int ubrr = (F_CPU / 16 / baudrate) - 1;
    
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    
    // Enable receiver and transmitter
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    
    // Set frame format: 8 data bits, 1 stop bit, no parity
    UCSR0C = (3<<UCSZ00);
}

void UART_Transmit(unsigned char data) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1<<UDRE0)));
    
    // Put data into buffer, sends the data
    UDR0 = data;
}

unsigned char UART_Receive(void) {
    // Wait for data to be received
    while (!(UCSR0A & (1<<RXC0)));
    
    // Get and return received data from buffer
    return UDR0;
}

void UART_SendString(const char *str) {
    while (*str) {
        UART_Transmit(*str++);
    }
}

void UART_ReceiveString(char *str, unsigned int maxLen) {
    unsigned char receivedChar;
    unsigned int i = 0;
    
    do {
        receivedChar = UART_Receive();
        str[i++] = receivedChar;
    } while(receivedChar != '\0' && i < maxLen - 1);
    
    // Ensure string is null-terminated
    str[i] = '\0';
}
