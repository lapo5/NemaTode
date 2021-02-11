#ifndef MY_HAL_SIRIUS_FP9_ROVER
#define MY_HAL_SIRIUS_FP9_ROVER

#include <iostream>
#include <libserial/SerialPort.h>
#include <libserial/SerialPortConstants.h>

#include <nmeaparse/nmea.h>
#include <iomanip>

#include "HAL_Sirius_F9P_Rover.cpp"


using namespace LibSerial;
using namespace std;
using namespace nmea;

class SiriusF9P_Rover{

protected:
    NMEAParser parser;
    GPSService gps;
    SerialPort my_serial_port;
    char* buffer;
    int position;

public:
    SiriusF9P_Rover(std::string port, unsigned int baudRate, unsigned int buf_size)
    {
        gps.attachToParser(parser);

        // Handle events when the lock state changes
        gps.onLockStateChanged += [](bool newlock){
            if (newlock){
                cout << "\t\t\tGPS acquired LOCK!" << endl;
            }
            else {
                cout << "\t\t\tGPS lost lock. Searching..." << endl;
            }
        };


        // (optional) - Handle events when the parser receives each sentence
        parser.onSentence += [](const NMEASentence& n){
            cout << "Received " << (n.checksumOK() ? "good" : "bad") << " GPS Data: " << n.name << endl;
        };

        my_serial_port.Open(port);

        if(baudRate == 115200)
            my_serial_port.SetBaudRate(LibSerial::BaudRate::BAUD_115200);

        position = 0;
        buffer = new char[buf_size];

    }

    bool isPortOpen() {
        return my_serial_port.IsOpen();
    }

    void readSerial(){
        do{
            my_serial_port.ReadByte(buffer[position], 0);
            ++position;
        }while(buffer[position - 1] != '\n');

        try {
            parser.readLine(buffer);
        } catch (NMEAParseError &e) {
            cout << "Error in parsing: " << e.what() << endl;
        }

        cout << "Sending: " << buffer << endl;
        for (int i = 0; i < position; i++) buffer[i] = '\0';
        position = 0;
    }

    void printStatus(){
        cout << gps.fix.toString() << endl;
    }

};

#endif //MY_HAL_SIRIUS_FP9_ROVER
