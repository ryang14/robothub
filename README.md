# Robot Hub

The goal of this project is to have a completely open source Lego Mindstorms like hub/controller.

The communication method uses device initiated messages over serial and is inspired by the VEX V5. The PacketSerial library is used to monitor all 8 hardware serial ports for packets using the COBS protocol. When a packet is received, it is stored in the corresponding input buffer and the output buffer is sent in response. The buffers are 64 bytes long, but packet size is determined by the device.

The interface is through a web app written in Svelte and served using the native ethernet interface of the Teensy 4.1. It is packed into a single html file and included in a header file. The port input buffers are exposed at /ports.json. The web app will use the port buffers to render widgets for each port with info about the connected motor/sensor. To package the web app, run npm i then npm run package in the webapp directory.
