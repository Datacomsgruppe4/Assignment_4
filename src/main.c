#define F_CPU 16000000UL
#define BAUD 115200
#define UBBR (F_CPU / 8 / BAUD - 1)

#include <util/delay.h>
#include <stdint.h>

#include "usart.h"

int main() {
   usart_init(UBBR);


   char hello_world[] = "Hello, World!\n";
   int str_len = sizeof(hello_world) / sizeof(hello_world[0]);

   for (;;) {
      // char received = usart_receive();
      // usart_transmit(received);
      usart_transmit_str(hello_world, str_len);
      _delay_ms(200);
   }

   return 0;
}
