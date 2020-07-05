#include <Arduino.h>
#include <TeensyThreads.h>
#include "tasks.h"

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  //Serial.println("task setup");
  threads.setDefaultStackSize(4096);
  threads.addThread(networkTask);
  threads.addThread(packetSerialTask);
}

void loop()
{
  threads.yield();
}
