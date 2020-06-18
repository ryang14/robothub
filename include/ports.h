#pragma once
#include <cstdint>

const uint8_t NUMBER_OF_PORTS = 9;
const uint8_t MAX_PORT_SIZE = 64;
extern uint8_t inPorts[NUMBER_OF_PORTS][MAX_PORT_SIZE];
extern uint8_t outPorts[NUMBER_OF_PORTS][MAX_PORT_SIZE];