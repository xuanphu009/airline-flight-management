#include "include/Passenger.h"


Passenger::Passenger() : used(nullptr) {}
Passenger::Passenger(char *_CMND) {strcpy(CMND, _CMND);}
void Passenger::insert(Ticket *x) {
    if(used == nullptr) {
        used = x;
        return;
    } else {
        x->next = used;
        used = x;
    }
}
