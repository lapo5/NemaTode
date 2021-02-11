#include <iostream>
#include <libserial/SerialPort.h>
#include <libserial/SerialStream.h>

#include <boost/version.hpp>

#include <nmeaparse/nmea.h>
#include <iomanip>

using namespace LibSerial;
using namespace std;
using namespace nmea;

int main()
{

    /*
    // Create and open the serial port for communication.


    cout << "Read buf: " << buf << endl;
     */

    // Create a GPS service that will keep track of the fix data.
    NMEAParser parser;
    GPSService gps(parser);
    parser.log = true;		// true: will spit out all sorts of parse info on each sentence.

    // Handle events when the lock state changes
    gps.onLockStateChanged += [](bool newlock){
        if (newlock){
            cout << "\t\t\tGPS acquired LOCK!" << endl;
        }
        else {
            cout << "\t\t\tGPS lost lock. Searching..." << endl;
        }
    };

    // Handle any changes to the GPS Fix... This is called after onSentence
    gps.onUpdate += [&gps](){
        cout << "\t\t\tPosition: " << gps.fix.latitude << "'N, " << gps.fix.longitude << "'E" << endl << endl;
    };

    // (optional) - Handle events when the parser receives each sentence
    parser.onSentence += [&gps](const NMEASentence& n){
        cout << "Received " << (n.checksumOK() ? "good" : "bad") << " GPS Data: " << n.name << endl;
    };


    SerialPort   my_serial_port( "/dev/ttyACM0" );

    bool isOpen = my_serial_port.IsOpen();

    cout << "Is open: " << isOpen << endl;

    char* buffer = new char[100];
    int position = 0;

    int count = 0;
    while(count < 100) {
        try {
            my_serial_port.ReadByte(buffer[position], 0);

            if(buffer[position] == '\n') {
                parser.readLine(buffer);
                cout << "Sending: " << buffer << endl;
                for (int i = 0; i < position; i++) buffer[i] = '\0';
                position = 0;
                count ++;
            }
            else{
                position++;
            }

        } catch (NMEAParseError &) {
            cout << "QUI?" << endl;
        }
    }


    cout << gps.fix.toString() << endl;
}


