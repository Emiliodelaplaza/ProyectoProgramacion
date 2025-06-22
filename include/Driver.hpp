#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <string>

using namespace std;

class Driver {
public:
    int driverId;
    string code;
    string fullName;
    string dob; // Date of birth as a string
    string nationality;

    Driver(); // Constructor predeterminado
    Driver(int driverId, string code, string fullName, string dob, string nationality);
};

#endif // DRIVER_HPP