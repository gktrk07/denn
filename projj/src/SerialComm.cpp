#include <iostream>
#include <string>
#include "SerialComm.h"
#include <cstdlib>
#include <boost/asio.hpp>

#define FAILCODE_SET_AND_EXIT(failCode, assignFailCode) \
        failCode = assignFailCode; \
        goto exit;

#define FAILCODE_CHECK_AND_EXIT(failCode, controlFailCode) \
        if (failCode != controlFailCode){ \
			goto exit;}

#define FAILCODE_CHECK_WITH_ANOTHER_VALUE_AND_EXIT(anotherFailCode, undesiredAnotherFailCode, failCode, assignFailCode) \
        if (anotherFailCode == undesiredAnotherFailCode){ \
			failCode = assignFailCode; \
			goto exit;}


bool isInside(int checkValue, int minValue, int maxValue)
{
	if (minValue > maxValue)
	{
		int temp{ maxValue };
		maxValue = minValue;
		minValue = maxValue;
	}

	if ((checkValue < minValue) || (checkValue > maxValue))
	{
		return false;
	}
	else
	{
		return true;
	}
}

FailCode SerialComm::checkConfigData(SerialPortConfig& configData)
{
	FailCode failCode = SERIAL_OK;
	if (configData.portName == "")
	{
		FAILCODE_SET_AND_EXIT(failCode, PORTNAME_IS_NONE);
	}
	if (isInside(configData.baudRate, BAUDRATE_9600, BAUDRATE_115200) == false)
	{
		FAILCODE_SET_AND_EXIT(failCode, BAUDRATE_OUT_OF_RANGE);
	}
	if (isInside(configData.dataBit, DATABIT_5, DATABIT_8) == false)
	{
		FAILCODE_SET_AND_EXIT(failCode, DATABIT_OUT_OF_RANGE);
	}
	if (isInside(configData.parityBit, PARITYBIT_NONE, PARITYBIT_ODD) == false)
	{
		FAILCODE_SET_AND_EXIT(failCode, PARITYBIT_OUT_OF_RANGE);
	}
	if (isInside(configData.stopBit, STOPBIT_1, STOPBIT_2) == false)
	{
		FAILCODE_SET_AND_EXIT(failCode, STOPBIT_OUT_OF_RANGE);
	}
	exit: return FailCode();
}

void SerialComm::assignSerialParams(boost::asio::serial_port* serial, SerialPortConfig& configData)
{
	uint baudRate{0};
	uint dataBit{0};
	boost::asio::serial_port_base::parity::type parityBit{boost::asio::serial_port_base::parity::none};
	boost::asio::serial_port_base::stop_bits::type stopBit{boost::asio::serial_port_base::stop_bits::one};

	switch (configData.baudRate)
	{
	case BAUDRATE_9600:
		baudRate = 9600;
		break;
	case BAUDRATE_38400:
		baudRate = 38400;
		break;
	case BAUDRATE_57600:
		baudRate = 57600;
		break;
	case BAUDRATE_115200:
		baudRate = 115200;
		break;
	default:
		break;
	}

	switch (configData.dataBit)
	{
	case DATABIT_5:
		dataBit = 5;
		break;
	case DATABIT_6:
		dataBit = 6;
		break;
	case DATABIT_7:
		dataBit = 7;
		break;
	case DATABIT_8:
		dataBit = 8;
		break;
	default:
		break;
	}

	switch (configData.parityBit)
	{
	case PARITYBIT_NONE:
		parityBit = boost::asio::serial_port_base::parity::none;
		break;
	case PARITYBIT_ODD:
		parityBit = boost::asio::serial_port_base::parity::odd;
		break;
	case PARITYBIT_EVEN:
		parityBit = boost::asio::serial_port_base::parity::even;
		break;
	default:
		break;
	}

	switch (configData.stopBit)
	{
	case STOPBIT_1:
		stopBit = boost::asio::serial_port_base::stop_bits::one;
		break;
	case STOPBIT_2:
		stopBit = boost::asio::serial_port_base::stop_bits::two;
		break;
	default:
		break;
	}

    serial->set_option(boost::asio::serial_port_base::character_size(dataBit));
	serial->set_option(boost::asio::serial_port_base::baud_rate(baudRate));
    serial->set_option(boost::asio::serial_port_base::parity(parityBit));
    serial->set_option(boost::asio::serial_port_base::stop_bits(stopBit));
}

SerialComm::SerialComm()
{
	this->serialPort = new boost::asio::io_service;
}

SerialComm::~SerialComm()
{
	delete this->serialPort;
}

FailCode SerialComm::startCommunication(SerialPortConfig& configData)
{
	FailCode failCode = SERIAL_OK;
	char c;
    std::string line;

	failCode = checkConfigData(configData);
	FAILCODE_CHECK_AND_EXIT(failCode, SERIAL_OK);

	try
	{
		boost::asio::serial_port serial(*serialPort, configData.portName);

		if (serial.is_open() == false)
		{
			FAILCODE_SET_AND_EXIT(failCode, SERIALPORT_NOT_OPENED);
		}

		this->assignSerialParams(&serial, configData);

        while (true) {
            boost::asio::read(serial, boost::asio::buffer(&c, 1));
            if (c == '\n') {
                // End of line, process the received line
                std::cout << "Received line: " << line << std::endl;
                line.clear();
            } else {
                // Append the character to the current line
                line += c;
            }
        }
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		FAILCODE_SET_AND_EXIT(failCode, SERIALPORT_NOT_OPENED);
	}

	exit: return failCode;
}

FailCode SerialComm::stopCommunication()
{
	return FailCode();
}
