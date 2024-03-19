#include <avr/interrupt.h>
#include <stdbool.h>
#define F_CPU 16000000UL
#define BAUD 115200
#define UBBR (F_CPU / 8 / BAUD - 1)

#include <stdio.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

#include "usart.h"
#include "timer.h"


int main() {
   sei();
   usart_init(UBBR);
   timer_init(62500);
   

   // char send_something[] = "Enter timestamp ([hh]:[mm]:[ss]): ";
   // int str_len = sizeof(send_something) / sizeof(send_something[0]);
   //
   // uint8_t hour, minute, second;
   //
   // usart_transmit_str(send_something, str_len);
   //
   // char user_input[32] = {0};
   //
   // for (int i = 0; i < 32; i++) {
   //    char chr = usart_receive();
   //    usart_transmit(chr);
   //
   //    user_input[i] = chr;
   //
   //    if (chr == '\r') break;
   // }
   // usart_transmit_str("\r\n", 2);
   //
   // sscanf(user_input, "%hhu:%hhu:%hhu", &hour, &minute, &second);
   //
   // for (;;) {
   //    char output[32] = {0};
   //    sprintf(output, "Hour: %hhu Minute: %hhu Second: %hhu\r\n", hour, minute, second);
   //
   //    usart_transmit_str(output, 32);
   //
   //    second += 1;
   //    minute += second / 60;
   //    hour += minute / 60;
   //
   //    second %= 60;
   //    minute %= 60;
   //    hour %= 24;
   //
   //    _delay_ms(1000);
   // }

   for (;;) {
      char str[256];
      // sprintf(str, "Timer flag: %d\r\n", counter);
      uint16_t cmp_val = (OCR1AH << 8) | (OCR1AL);
      sprintf(str, "%u\r\n", cmp_val);
      
      //
      // if (counter_flag) {
      //    
      // }
      // usart_transmit_str(str);
   }
}
