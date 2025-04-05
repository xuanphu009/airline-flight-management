#include "../include/Ticket.h"


Ticket::Ticket()  {}
Ticket::Ticket(unsigned int _seat, char *_CMND) : seat(_seat) {strcpy(CMND, _CMND);}