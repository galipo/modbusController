# MODBUS C++ Master(TCP Client) Demo

## 0.0 Development Environment Setup
1. install virtualbox 6.1
2. install ubuntu 18.04
2. install git version 2.17.1
3. install visual studio code : follow the steps in the link : https://code.visualstudio.com/docs/cpp/config-linux

## 0.1 Compiler
1. install cmake : sudo apt-get install cmake
2. compiled using c++11 compilers
3

## 0.1MODBUS Slave Simulator Setup

MODBUS Slave Sim IP     : 192.168.2.7
MODBUS Slave Sim Port   : 502
VM Ubuntu 18.4 IP       : 192.168.224.3

## 1 Source Files

1. /communication_manager/modbus_controller.cpp :
- main() function
2. /communication_manager/modbus.h : 
- modbus tcp connnect function
- modbus function code request send and response receive functions
3. /communication_manager/modbus_controller.h
- Register/Coil Read/Write and print results funcitons


