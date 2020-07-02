#include <Arduino.h>
#include <AceRoutine.h>
#include <NativeEthernet.h>
#include <PacketSerial.h>
#include <ArduinoJson.h>
#include "ports.h"
#include "index.h"

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

// size of buffer used to capture HTTP requests
#define REQ_BUF_SZ 80
char HTTP_req[REQ_BUF_SZ] = {0}; // buffered HTTP request stored as null terminated string
uint8_t req_index = 0;           // index into HTTP_req buffer

// sets every element of str to 0 (clears array)
void StrClear(char *str, char length)
{
    for (int i = 0; i < length; i++)
    {
        str[i] = 0;
    }
}

// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if string not found
char StrContains(char *str, const char *sfind)
{
    uint8_t found = 0;
    uint8_t index = 0;
    size_t len;

    len = strlen(str);

    if (strlen(sfind) > len)
    {
        return 0;
    }
    while (index < len)
    {
        if (str[index] == sfind[found])
        {
            found++;
            if (strlen(sfind) == found)
            {
                return 1;
            }
        }
        else
        {
            found = 0;
        }
        index++;
    }

    return 0;
}

COROUTINE(netowrkTask)
{
    COROUTINE_BEGIN();

    // start the Ethernet connection and the server:
    Ethernet.begin(mac);
    MDNS.begin("RobotHub", 2);
    MDNS.setServiceName("robothub");
    MDNS.addService("_http._tcp", 80);

    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
        Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
        while (true)
        {
            delay(1); // do nothing, no point running without Ethernet hardware
        }
    }
    if (Ethernet.linkStatus() == LinkOFF)
    {
        Serial.println("Ethernet cable is not connected.");
    }

    // start the server
    server.begin();
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());

    while (true)
    {
        EthernetClient client = server.available(); // try to get client

        if (client)
        { // got client?
            boolean currentLineIsBlank = true;
            while (client.connected())
            {
                if (client.available())
                {                           // client data available to read
                    char c = client.read(); // read 1 byte (character) from client
                    // buffer first part of HTTP request in HTTP_req array (string)
                    // leave last element in array as 0 to null terminate string (REQ_BUF_SZ - 1)
                    if (req_index < (REQ_BUF_SZ - 1))
                    {
                        HTTP_req[req_index] = c; // save HTTP request character
                        req_index++;
                    }
                    //Serial.print(c); // print HTTP request character to serial monitor
                    // last line of client request is blank and ends with \n
                    // respond to client only after last line received
                    if (c == '\n' && currentLineIsBlank)
                    {

                        // open requested web page file
                        if (StrContains(HTTP_req, "GET / ") || StrContains(HTTP_req, "GET /index.html"))
                        {
                            //webFile = SD.open("index.html"); // open web page file

                            // send a standard http response header
                            client.println("HTTP/1.1 200 OK");
                            client.println("Content-Type: text/html");
                            client.println("Connnection: close");
                            client.println();
                            unsigned int bytesWritten = 0;
                            while (bytesWritten < public_index_html_len)
                            {
                                bytesWritten += client.write(&public_index_html[bytesWritten], public_index_html_len - bytesWritten);
                            }
                        }
                        else if (StrContains(HTTP_req, "GET /ports.json"))
                        {
                            DynamicJsonDocument doc(NUMBER_OF_PORTS * 1040);
                            copyArray(inPorts, doc.to<JsonArray>());

                            // send a standard http response header
                            client.println("HTTP/1.1 200 OK");
                            client.println("Content-Type: application/json");
                            client.println("Connnection: close");
                            client.println();
                            serializeJson(doc, client);
                        }
                        else if (StrContains(HTTP_req, "GET /routines.json"))
                        {
                            DynamicJsonDocument doc(NUMBER_OF_PORTS * 1040);
                            JsonArray array = doc.to<JsonArray>();

                            for (Coroutine **p = ace_routine::Coroutine::getRoot(); (*p) != nullptr;
                                 p = (*p)->getNext())
                            {
                                JsonObject coroutineOpj = array.createNestedObject();
                                coroutineOpj["name"] = (*p)->getName().getCString();
                            }

                            // send a standard http response header
                            client.println("HTTP/1.1 200 OK");
                            client.println("Content-Type: application/json");
                            client.println("Connnection: close");
                            client.println();
                            serializeJson(doc, client);
                        }
                        // reset buffer index and all buffer elements to 0
                        req_index = 0;
                        StrClear(HTTP_req, REQ_BUF_SZ);
                        break;
                    }
                    // every line of text received from the client ends with \r\n
                    if (c == '\n')
                    {
                        // last character on line of received text
                        // starting new line with next character read
                        currentLineIsBlank = true;
                    }
                    else if (c != '\r')
                    {
                        // a text character was received from client
                        currentLineIsBlank = false;
                    }
                }          // end if (client.available())
            }              // end while (client.connected())
            client.stop(); // close the connection
        }                  // end if (client)
        COROUTINE_YIELD();
    }

    COROUTINE_END();
}