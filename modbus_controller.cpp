
#include <iostream>
#include <string>
#include <utility>
#include <chrono>
#include <thread> 
#include "modbus_controller.h"

using namespace std;









int main(int argc, char **argv)
{
std::string::size_type sz;   // alias of size_t    
int result;
int expected_param;
int id = 0;
int param_1 = 0;
int param_2 = 0;

//check id
if (argc < 2)
{
    std::cout << "Invalid Command" <<std::endl;
    return 0;
}

//command interpreter
id = std::stoi (std::string(argv[1]),&sz);

// Init Modbus Controller
mc.init_modbus_controller();

std::cout <<std::endl;
switch (id)
{
case 2:
    std::cout << "Function Code 0x02 : Read Discrete Inputs" <<std::endl;
    break;
case 4:
    std::cout << "Function Code 0x04 : Read Input Registers" <<std::endl;
    break;
case 5:
    if (argc < 4)
    {
        std::cout << "Invalid Command" <<std::endl;
        return 0;
    }
    std::cout << "Function Code 0x05 : Write Single Coil" <<std::endl;
    param_1 = std::stoi (std::string(argv[2]),&sz);
    param_2 = std::stoi (std::string(argv[3]),&sz);
    break;
case 6:
    if (argc < 4)
    {
        std::cout << "Invalid Command" <<std::endl;
        return 0;
    }
    std::cout << "Function Code 0x06 : Write Single Register" <<std::endl;
    param_1 = std::stoi (std::string(argv[2]),&sz);
    param_2 = std::stoi (std::string(argv[3]),&sz);
    break;
case 15:
    if (argc < 3)
    {
        std::cout << "Invalid Command" <<std::endl;
        return 0;
    }
    std::cout << "Function Code 0x0F : Write Multiple Coils" <<std::endl;
    param_1 = std::stoi (std::string(argv[2]),&sz);
    break;
case 16:
    if (argc < 3)
    {
        std::cout << "Invalid Command" <<std::endl;
        return 0;
    }
    std::cout << "Function Code 0x10 : Write Multiple Registers" <<std::endl;
    param_1 = std::stoi (std::string(argv[2]),&sz);
    break;
default:
    std::cout << "Invalid Command" <<std::endl;
    break;
}

// Send Modbus Request
mc.modbus_func(id, param_1, param_2);
mc.modbus_func(id, param_1, param_2);

//create a thread
//std::thread t2(modbus_scanner, id, size, val); // pass by value
//t2.join();


return 0;
/*----------------------------------------------------------------------------------------------------------------------------------*/

}

//Modbus Read Multiple Coil function 0x01
void modbus_scanner(int id, int size, int val)
{ 
    while (1) 
    {
        //std::cout << "Thread 1 executing\n";
        
        mc.modbus_periodic_func(id, size, val);

        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
}