#include "Driver.hpp"

// Constructor predeterminado
Driver::Driver()
    : driverId(0), code(""), fullName(""), dob(""), nationality("") {}

// Constructor con parámetros
Driver::Driver(int driverId, string code, string fullName, string dob, string nationality)
    : driverId(driverId), code(code), fullName(fullName), dob(dob), nationality(nationality) {}