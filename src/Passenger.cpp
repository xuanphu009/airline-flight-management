#include "../include/Passenger.h"



Passenger::Passenger() {number_of_tickets = 0;}
bool Passenger::valid_user() {
    return strlen(CMND) > 0 && strlen(last_name) > 0 && strlen(first_name) > 0 && (gender) != nullptr;
}
bool Passenger::operator == (Passenger &other) {
    return strcmp(CMND, other.CMND) == 0 && strcmp(last_name, other.last_name) == 0 && strcmp(first_name, other.first_name) == 0 && *gender == *other.gender;

}
std::ofstream& operator<<(std::ofstream &out, const Passenger &other) {
    out << other.CMND << std::endl
    << other.last_name << std::endl
    << other.first_name << std::endl
    << *other.gender << std::endl
    << other.number_of_tickets << std::endl;
    return out;
}
std::ostream& operator<<(std::ostream &out, const Passenger &other) {
    out << other.CMND << std::endl
    << other.last_name << std::endl
    << other.first_name << std::endl
    << *other.gender << std::endl
    << other.number_of_tickets << std::endl;
    return out;
}
std::ifstream& operator>>(std::ifstream &in, Passenger &other) {
    other.gender = new bool;
    in >> other.CMND;
    in.ignore();
    in.getline(other.last_name, LEN_LAST_NAME);
    in >> other.first_name
    >> *other.gender
    >> other.number_of_tickets;
    return in;
}