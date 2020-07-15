#include "sbus_serial.h"

#include <iostream>

int main(int argc, char *argv[])
{
    SBusSerialPort sbus(argv[1]);
    while(true) {
      SBusMsg msg = sbus.getData();
      std::cout << "Thr: " << msg.channels[0] << ", Dir: " << msg.channels[1] << std::endl;
    }
    return 0;
}