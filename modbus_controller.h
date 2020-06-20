#ifndef MODBUS_CONTROLLER_H
#define MODBUS_CONTROLLER_H

#include <iostream>
#include <string>
#include <utility>
#include "modbus.h"

using namespace std;

#define NUM_OF_MODBUS_READ_BITS                 2
#define NUM_OF_MODBUS_READ_SHORTS               2
#define MODBUS_READ_DISCRETE_INPUTS_OFFSET      10001
#define MODBUS_READ_INPUT_REGISTER_OFFSET       30001
#define MODBUS_WRITE_SINGLE_COIL_OFFSET         1
#define MODBUS_WRITE_SINGLE_REGISTER_OFFSET     40001
/**
 * Modbus Controller Class
 * 
 */

class modbus_controller{
private:
    // create a modbus object
    modbus mb = modbus("192.168.2.7", 502);

    bool read_bit[100];
    bool prev_read_bit[100];
    unsigned short read_short[100];

public:
    void init_modbus_controller();
    void modbus_periodic_func(int id, int size, int val);
    void modbus_func(int id, int size, int val);
    void modbus_read_discrete_inputs(int id, int size, int val);
    void modbus_write_single_coil(int id, int addr, int val);
    void mc_modbus_read_input_registers(int id, int addr, int val);
    void mc_modbus_write_single_register(int id, int addr, int val);
    void mc_modbus_write_multiple_coils(int id, int addr, int value);
    void mc_modbus_write_multiple_registers(int id, int addr, int value);
}mc;

/**
 * Initialize Modbus Controller

 */
void modbus_controller::init_modbus_controller(){
// set slave id
mb.modbus_set_slave_id(1);

// connect with the server
mb.modbus_connect();
}
/**
 * Modbus Periodic Func
 * @param id    ID of the Modbus Funciton
 * @param size  size of data will be rear/write
 * @param val   value to be read and written
 */
void modbus_controller::modbus_func(int id, int size, int val) {
    switch (id)
    {
    case 2:
        modbus_controller::modbus_read_discrete_inputs(id, size, val);
        break;
    case 4:
        modbus_controller::mc_modbus_read_input_registers(id, size, val);
        break;
    case 5:
        modbus_controller::modbus_write_single_coil(id, size, val);
        break;
    case 6:
        modbus_controller::mc_modbus_write_single_register(id, size, val);
        break;
    case 15:
        modbus_controller::mc_modbus_write_multiple_coils(id, size, val);
        break;    
    case 16:
        modbus_controller::mc_modbus_write_multiple_registers(id, size, val);
        break; 
    default:
        break;
    }
}



/**
 * modbus_read_discrete_inputs
 * @param id    ID of the Modbus Funciton
 * @param size  size of data will be rear/write
 * @param val   value to be read and written
 */
void modbus_controller::modbus_read_discrete_inputs(int id, int size, int data) {
unsigned int i;

        // read input bits(discrete input)  function 0x02
        mb.modbus_read_input_bits(0, NUM_OF_MODBUS_READ_BITS, &read_bit[0]);
        for (i = 0; i < NUM_OF_MODBUS_READ_BITS; i++)
        {
                std::cout << " Coil/Register Number: "<< i + MODBUS_READ_DISCRETE_INPUTS_OFFSET << " Addr: "<< i << " Value :" <<read_bit[i] <<endl;
        }
}
/**
 * modbus_read_input_registers
 * @param id    ID of the Modbus Funciton
 * @param size  size of data will be rear/write
 * @param val   value to be read and written
 */
void modbus_controller::mc_modbus_read_input_registers(int id, int size, int data) {
unsigned int i;

        // read input bits(discrete input)  function 0x02
        mb.modbus_read_input_registers(0, NUM_OF_MODBUS_READ_SHORTS, &read_short[0]);
        for (i = 0; i < NUM_OF_MODBUS_READ_SHORTS; i++)
        {
                std::cout << " Coil/Register Number: "<< i + MODBUS_READ_INPUT_REGISTER_OFFSET << " Addr: "<< i << " Value :" <<read_short[i] <<endl;
        }
}
/**
 * mc_modbus_write_single_register
 * @param id    ID of the Modbus Funciton
 * @param size  size of data will be rear/write
 * @param val   value to be read and written
 */
void modbus_controller::mc_modbus_write_single_register(int id, int addr, int value) {
unsigned short short_value;

        short_value = value;
        mb.modbus_write_register(addr, short_value);

        std::cout << " Coil/Register Number: "<< addr + MODBUS_WRITE_SINGLE_REGISTER_OFFSET << " Addr: "<< addr << " Value :" <<short_value <<endl;

}

/**
 * mc_modbus_write_multiple_coils
 * @param id    ID of the Modbus Funciton
 * @param size  size of data will be rear/write
 * @param val   value to be read and written
 */
void modbus_controller::mc_modbus_write_multiple_registers(int id, int addr, int value) {
unsigned short short_array[10];
unsigned int    amount;
unsigned int i;

        amount = 2;
        short_array[0] = 1234;
        short_array[1] = 5678;

        mb.modbus_write_registers(addr, amount, &short_array[0]);

        
        for (size_t i = 0; i < amount; i++)
        {
            std::cout << " Coil/Register Number: "<< addr + i + MODBUS_WRITE_SINGLE_REGISTER_OFFSET << " Addr: " << addr + i;
            std::cout << " Value : " << short_array[i] <<endl;
        }    
}

/**
 * mc_modbus_write_multiple_coils
 * @param id    ID of the Modbus Funciton
 * @param size  size of data will be rear/write
 * @param val   value to be read and written
 */
void modbus_controller::mc_modbus_write_multiple_coils(int id, int addr, int value) {
bool bool_array[10];
unsigned int    amount;
unsigned int i;

        amount = 8;
        bool_array[0] = 1;
        bool_array[1] = 1;
        bool_array[2] = 0;
        bool_array[3] = 0;
        bool_array[4] = 0;
        bool_array[5] = 0;
        bool_array[6] = 1;
        bool_array[7] = 1;
        mb.modbus_write_coils(addr, amount, &bool_array[0]);

        
        for (size_t i = 0; i < amount; i++)
        {
            std::cout << " Coil/Register Number: "<< addr + i + MODBUS_WRITE_SINGLE_COIL_OFFSET << " Addr: " << addr + i;
            std::cout << " Value : " << bool_array[i] <<endl;
        }    
}

/**
 * modbus_write_single_coil
 * @param id    ID of the Modbus Funciton
 * @param size  size of data will be rear/write
 * @param val   value to be read and written
 */
void modbus_controller::modbus_write_single_coil(int id, int addr, int value) {
bool bool_value;

        bool_value = value;
        mb.modbus_write_coil(addr, bool_value);

        std::cout << " Coil/Register Number: "<< addr + MODBUS_WRITE_SINGLE_COIL_OFFSET << " Addr: "<< addr << " Value :" <<value <<endl;

}

/**
 * Modbus Periodic Func
 * @param id    ID of the Modbus Funciton
 * @param size  size of data will be rear/write
 * @param val   value to be read and written
 */
void modbus_controller::modbus_periodic_func(int id, int size, int val) {
    switch (id)
    {
    case 1:
        //modbus_controller::modbus_read_discrete_inputs(id, size, val);
        break;
    
    default:
        break;
    }
}

#endif