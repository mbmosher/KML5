// Code to output OSC via UDP and Serial from an Arduino MKR1000
// Designed for use with GameTrak Rev1
// Six pot inputs on A1-A7, Foot switchon A0 with a 10k pull down resistor
// /wek/inputs Switch LeftY LeftX LeftZ RightY RightX RightZ

// Libraries
#include <OSCBoards copy.h>
#include <OSCBoards.h>
#include <OSCBundle.h>
#include <OSCData.h>
#include <OSCMatch.h>
#include <OSCMessage.h>
#include <OSCTiming.h>
#include <SLIPEncodedSerial.h>
#include <SLIPEncodedUSBSerial.h>
#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>

// Wifi variables
int status = WL_IDLE_STATUS;
char ssid[] = "XXXXXXXX"; // your network SSID (name)
char pass[] = "XXXXX";    // your network password (use for WPA, or use as key for WEP)
unsigned int localPort = 2390;      // local port to listen on, needed to UDP to work
WiFiUDP Udp;
IPAddress broadcast(255, 255, 255, 255);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWiFiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial
  
  Udp.begin(localPort);
  
  analogReadResolution(12);
}

void loop() {
  // Read sensors
  float vals[7];
  OSCMessage msg("/wek/inputs");
  for(int i = 0; i < 7; i++) {
    vals[i] = (float)analogRead(i);
    msg.add(vals[i]);
  }
  //  Clean the foot switch, Dumb, use a digital pin in the future
  /*
  if(vals[0] < 3000) {
    vals[0] = 0.0;
  } else {
    vals[0] = 4095.0;
  }
  */
  // Send to serial (optional)
  char data[256];
  sprintf(data, "/wek/inputs %f %f %f %f %f %f %f \n", vals[0], vals[1], vals[2], vals[3], vals[4], vals[5], vals[6]);
  Serial.println(data);
  Serial.flush();
  yield();

  // Broadcast over UDP (OSC)
  Udp.beginPacket(broadcast, 6448);
  msg.send(Udp);
  Udp.endPacket();
}








void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


