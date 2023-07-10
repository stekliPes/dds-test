#include "LampStateReceiver.h"
#include "shared/LampState.h"

#include <iostream>

int main (int, char**)
try 
{
    std::string id;
    LampStateReceiver receiver;
    std::cout << "Press any key to exit...";
    std::cin >> id;
 }
 catch (std::exception &e)
 {
    std::cout << "ERROR: " << e.what() << std::endl;
 }