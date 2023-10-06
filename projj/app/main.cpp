#include "Configuration.h"
/*
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
*/
#include <random>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "mqtt/async_client.h"


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
/*
std::cout << "deneme" << std::endl;
    using namespace std;
    using namespace std::chrono;
    cout << "deneme" << endl;
    const std::string DFLT_ADDRESS{ "tcp://localhost:1883" };

    const string TOPIC{ "data/rand" };
    const int	 QOS = 1;

    const auto PERIOD = seconds(5);

    const int MAX_BUFFERED_MSGS = 120;	// 120 * 5sec => 10min off-line buffering

    const string PERSIST_DIR{ "data-persist" };

    string address = DFLT_ADDRESS;

    mqtt::async_client cli(address, "", MAX_BUFFERED_MSGS, PERSIST_DIR);

    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(MAX_BUFFERED_MSGS * PERIOD);
    connOpts.set_clean_session(true);
    connOpts.set_automatic_reconnect(true);

    // Create a topic object. This is a conventience since we will
    // repeatedly publish messages with the same parameters.
    mqtt::topic top(cli, TOPIC, QOS, true);


    try {
        // Connect to the MQTT broker
        cout << "Connecting to server '" << address << "'..." << flush;
        cli.connect(connOpts)->wait();
        cout << "OK\n" << endl;

        unsigned nsample = 0;

        // The time at which to reads the next sample, starting now
        auto tm = steady_clock::now();

        while (true) {
            // Pace the samples to the desired rate
            this_thread::sleep_until(tm);

            // Create the payload as a text CSV string
            string payload = "asd";
            cout << payload << endl;

            // Publish to the topic
            top.publish(std::move(payload));

            tm += PERIOD;
        }

        // Disconnect
        cout << "\nDisconnecting..." << flush;
        cli.disconnect()->wait();
        cout << "OK" << endl;
    }
    catch (const mqtt::exception& exc) {
        cerr << exc.what() << endl;
        return 1;
    }
    */
    return 0;
}
