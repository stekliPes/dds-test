#include "LampStateSender.h"
#include "shared/LampState.h"

#include <iostream>

int main (int, char**)
try 
{
    LampState stateToSend;
    LampStateSender sender;
    std::string id;
    bool state;
    do
    {
        std::cout << "Enter ID of lamp and press enter: ";
        std::cin >> id;
        std::cout << "Enter state to send: ";
        std::cin >> state;
        stateToSend.LampID() = id;
        stateToSend.on() = state;
        std::cout << "Lamp " << stateToSend.LampID() << " state set to " << (stateToSend.on() ? "ON" : "OFF") << std::endl;;
        sender.send(stateToSend);
        std::cout << "LampState sent" << std::endl << std::endl;
        std::cout << "Continue? (Y/N):";
        std::cin >> id;
    }
    while (id!="n" && id!="N");
 }
 catch (std::exception &e)
 {
    std::cout << "ERROR: " << e.what() << std::endl;
 }