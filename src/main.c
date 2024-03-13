#define F_CPU 16000000UL
#define BAUD 115200
#define UBBR (F_CPU / 8 / BAUD - 1)

#include <stdio.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

#include "usart.h"


int main() {
   usart_init(UBBR);

   char send_something[] = "Enter timestamp ([hh]:[mm]:[ss]): ";

   uint8_t hour, minute, second;

   usart_transmit_str(send_something);

   char user_input[32] = {0};

   for (int i = 0; i < 32; i++) {
      char chr = usart_receive();
      usart_transmit(chr);

      user_input[i] = chr;

      if (chr == '\r') break;
   }
   usart_transmit_str("\r\n");

   sscanf(user_input, "%hhu:%hhu:%hhu", &hour, &minute, &second);

   for (;;) {
      char output[32] = {0};
      sprintf(output, "Hour: %hhu Minute: %hhu Second: %hhu\r\n", hour, minute, second);

      usart_transmit_str(output);

      second += 1;
      minute += second / 60;
      hour += minute / 60;

      second %= 60;
      minute %= 60;
      hour %= 24;

      _delay_ms(1000);
   }
}
