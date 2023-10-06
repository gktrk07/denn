#include <iostream>
#include <boost/asio.hpp>

enum BaudRate
{
	BAUDRATE_9600 = 0,
	BAUDRATE_38400 = 1,
	BAUDRATE_57600 = 2,
	BAUDRATE_115200 = 3
};

enum DataBit
{
	DATABIT_5 = 0,
	DATABIT_6 = 1,
	DATABIT_7 = 2,
	DATABIT_8 = 3
};

enum StopBit
{
	STOPBIT_1 = 0,
	STOPBIT_2 = 1
};

enum ParityBit
{
	PARITYBIT_NONE = 0,
	PARITYBIT_EVEN = 1,
	PARITYBIT_ODD = 2
};

enum FailCode
{
	SERIAL_OK = 0,
	NAME_IS_INVALID = 1,
	BAUDRATE_OUT_OF_RANGE = 2,
	DATABIT_OUT_OF_RANGE = 3,
	PARITYBIT_OUT_OF_RANGE = 4,
	STOPBIT_OUT_OF_RANGE = 5,
	SERIALPORT_NOT_OPENED  = 6,
	NOT_OBTAINED_SERIALPORT_STATUS = 7,
	PORTNAME_IS_NONE = 8,
	READING_ERROR = 9
};

struct SerialPortConfig
{
	std::string portName;
	BaudRate baudRate;
	DataBit dataBit;
	StopBit stopBit;
	ParityBit parityBit;
};

class SerialComm
{
private:
	boost::asio::io_service *serialPort;
	FailCode checkConfigData(SerialPortConfig& configData);
	void assignSerialParams(boost::asio::serial_port* serial, SerialPortConfig& configData);

public:
	SerialComm();
	~SerialComm();
	FailCode startCommunication(SerialPortConfig& configData);
	FailCode stopCommunication();
};
