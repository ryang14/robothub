#include <AceRoutine.h>
#include <PacketSerial.h>
#include "ports.h"

const uint32_t SERIAL_BAUD = 3000000;

PacketSerial_<COBS, 0, 1024> packetSerial1;
PacketSerial_<COBS, 0, 1024> packetSerial2;
PacketSerial_<COBS, 0, 1024> packetSerial3;
PacketSerial_<COBS, 0, 1024> packetSerial4;
PacketSerial_<COBS, 0, 1024> packetSerial5;
PacketSerial_<COBS, 0, 1024> packetSerial6;
PacketSerial_<COBS, 0, 1024> packetSerial7;
PacketSerial_<COBS, 0, 1024> packetSerial8;

void onPacketReceived(const void *sender, const uint8_t *buffer, size_t size)
{
    if (size <= MAX_PORT_SIZE)
    {
        if (sender == &packetSerial1)
        {
            memcpy(inPorts[1], buffer, size);
            packetSerial1.send(outPorts[1], size);
        }
        else if (sender == &packetSerial2)
        {
            memcpy(inPorts[2], buffer, size);
            packetSerial2.send(outPorts[2], size);
        }
        else if (sender == &packetSerial3)
        {
            memcpy(inPorts[3], buffer, size);
            packetSerial3.send(outPorts[3], size);
        }
        else if (sender == &packetSerial4)
        {
            memcpy(inPorts[4], buffer, size);
            packetSerial4.send(outPorts[4], size);
        }
        else if (sender == &packetSerial5)
        {
            memcpy(inPorts[5], buffer, size);
            packetSerial5.send(outPorts[5], size);
        }
        else if (sender == &packetSerial6)
        {
            memcpy(inPorts[6], buffer, size);
            packetSerial6.send(outPorts[6], size);
        }
        else if (sender == &packetSerial7)
        {
            memcpy(inPorts[7], buffer, size);
            packetSerial7.send(outPorts[7], size);
        }
        else if (sender == &packetSerial8)
        {
            memcpy(inPorts[8], buffer, size);
            packetSerial8.send(outPorts[8], size);
        }
    }
}

COROUTINE(packetSerialTask)
{
    COROUTINE_BEGIN();
    Serial1.begin(SERIAL_BAUD);
    packetSerial1.setStream(&Serial1);
    packetSerial1.setPacketHandler(&onPacketReceived);
    Serial2.begin(SERIAL_BAUD);
    packetSerial2.setStream(&Serial2);
    packetSerial2.setPacketHandler(&onPacketReceived);
    Serial3.begin(SERIAL_BAUD);
    packetSerial3.setStream(&Serial3);
    packetSerial3.setPacketHandler(&onPacketReceived);
    Serial4.begin(SERIAL_BAUD);
    packetSerial4.setStream(&Serial4);
    packetSerial4.setPacketHandler(&onPacketReceived);
    Serial5.begin(SERIAL_BAUD);
    packetSerial5.setStream(&Serial5);
    packetSerial5.setPacketHandler(&onPacketReceived);
    Serial6.begin(SERIAL_BAUD);
    packetSerial6.setStream(&Serial6);
    packetSerial6.setPacketHandler(&onPacketReceived);
    Serial7.begin(SERIAL_BAUD);
    packetSerial7.setStream(&Serial7);
    packetSerial7.setPacketHandler(&onPacketReceived);
    Serial8.begin(SERIAL_BAUD);
    packetSerial8.setStream(&Serial8);
    packetSerial8.setPacketHandler(&onPacketReceived);

    while (true)
    {
        packetSerial1.update();
        COROUTINE_YIELD();
        packetSerial2.update();
        COROUTINE_YIELD();
        packetSerial3.update();
        COROUTINE_YIELD();
        packetSerial4.update();
        COROUTINE_YIELD();
        packetSerial5.update();
        COROUTINE_YIELD();
        packetSerial6.update();
        COROUTINE_YIELD();
        packetSerial7.update();
        COROUTINE_YIELD();
        packetSerial8.update();
        COROUTINE_YIELD();
    }
    COROUTINE_END();
}