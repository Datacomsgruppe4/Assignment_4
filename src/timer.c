
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "timer.h"
#include "usart.h"

void timer_init(uint16_t compare_value) {
   // TCCR1B |= (0b100 << CS12); // Prescale 256
   TCCR1B |= (1 << CS12);
   // TCCR1B |= (0b01 << WGM13);
   TCCR1B |= (1 << WGM12);

   // Put compare_value into OCR register
   OCR1AH = (uint8_t) compare_value >> 8;
   OCR1AL = (uint8_t) compare_value;

   // Enable interrupt
   TIMSK1 |= (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect) {
   counter += 1; 

   char str[64];
   sprintf(str, "Counter: %d\r\n", counter/1000);
   usart_transmit_str(str);
}
