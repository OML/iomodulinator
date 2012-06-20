#include "connectivity.h"
#include "device.h"

#include <string.h>

#include <bus.h>

struct uart_descriptor* main_uart;

void uart_init(struct uart_descriptor* uart, size_t uid)
{
        main_uart = uart;
                if(uid == 0)
                {
                        ANSBbits.ANSB2 = 0;

                        TRISBbits.TRISB2 = 1;
                        TRISBbits.TRISB7 = 1;

		        U1BRG = 25;
		        U1MODE = 0x8000;
		        U1STA = 0x0420;

		        IFS0bits.U1RXIF = 0;
		        IPC2bits.U1RXIP = 0x7;		// Highest
		        IEC0bits.U1RXIE = 1;

                        uart->rxreg = &U1RXREG;
                        uart->txreg = &U1TXREG;
                        uart->stareg = &U1STA;
                }

                if(uid == 1)
                {
                        ANSBbits.ANSB0 = 0;
                        ANSBbits.ANSB1 = 0;

                        TRISBbits.TRISB0 = 1;
                        TRISBbits.TRISB1 = 1;

		        U2BRG = 25;
		        U2MODE = 0x8000;
		        U2STA = 0x0420;

		        IFS1bits.U2RXIF = 0;
		        IPC7bits.U2RXIP = 0x7;		// Highest
		        IEC1bits.U2RXIE = 1;

                        uart->rxreg = &U2RXREG;
                        uart->txreg = &U2TXREG;
                        uart->stareg = &U2STA;
                }
}
