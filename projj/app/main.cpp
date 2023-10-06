#include "Configuration.h"

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>


void printFailCode(FailCode& failCode)
{
    switch (failCode)
    {
    case SERIAL_OK:
        std::cout << "No error occured.";
        break;
    case NAME_IS_INVALID:
        std::cout << "ERROR: The port name is invalid!!!";
        break;
    case BAUDRATE_OUT_OF_RANGE:
        std::cout << "ERROR: The baudrate is out of range!!!";
        break;
    case DATABIT_OUT_OF_RANGE:
        std::cout << "ERROR: The data bit is out of range!!!";
        break;
    case PARITYBIT_OUT_OF_RANGE:
        std::cout << "ERROR: The parity bit is out of range!!!";
        break;
    case STOPBIT_OUT_OF_RANGE:
        std::cout << "ERROR: The stop bit is out of range!!!";
        break;
    case SERIALPORT_NOT_OPENED:
        std::cout << "ERROR: The serial port was not opened!!!";
        break;
    case NOT_OBTAINED_SERIALPORT_STATUS:
        std::cout << "ERROR: The serial port status was not obtained!!!";
        break;
    case PORTNAME_IS_NONE:
        std::cout << "ERROR: The port name is none!!!";
        break;
    case READING_ERROR:
        std::cout << "ERROR: An error occured while reading from serial port!!!";
        break;
    default:
        break;
    }

    std::cout << std::endl << "The program is closing...";
}

int main() {

    
    SerialComm serialComm;
    SerialPortConfig configData;
    FailCode failCode{ SERIAL_OK };

    configData.portName = static_cast<std::string>(SC_PORT_NAME);
    configData.baudRate = SC_BAUDRATE;
    configData.dataBit = SC_DATABIT;
    configData.stopBit = SC_STOPBIT;
    configData.parityBit = SC_PARITYBIT;

    failCode = serialComm.startCommunication(configData);
    printFailCode(failCode);
    
    return 0;
}
