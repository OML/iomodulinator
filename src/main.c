#include <bus.h>
#include <offsets.h>

#include "device.h"
#include "timers.h"


void incoming_event(struct bus_descriptor* bus, char* data, size_t len)
{
        struct bus_event_hdr* evhdr = get_bus_event_header(data);
        struct bus_set_outputs* setout = get_bus_set_outputs(data);

        switch(evhdr->type)
        {
                case EV_SET_OUTPUTS:
                {
                        PORTAbits.RA7 = (setout->bits & 1)?1:0;
                        PORTBbits.RB9 = (setout->bits & 2)?1:0;
                        PORTBbits.RB8 = (setout->bits & 4)?1:0;
                        PORTBbits.RB6 = (setout->bits & 8)?1:0;
                        PORTBbits.RB5 = (setout->bits & 16)?1:0;
                }
        }
}


int main (void)
{
        clock_start();
        bus_init(2, DT_IO);

        while(1)
        {
                bus_do_work();
        }        
}
