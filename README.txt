• The URL of the GitHub repository where people can down- load your feature extractor
https://github.com/mbmosher/KML5

• A description of the types of things your feature extractor could be used for
     I was very intrigued by the GameTrak controller, but couldn’t find a reasonably prices USB one on Amazon/Ebay.  So I ordered an xbox one for $6 hoping I could use the easy solder hack on it. (http://x37v.com/x37v/writing/mad-catz-gametrak-mod-for-maxmsp/).  Alas, the one I received is a rev 1 with no easy mode select.  I also had an Ardunio MKR1000 lying around that was not cooperating as a wifi client so I thought I’d put it into the gametrak controller.  Since the MKR100 has wifi, I could have it directly send OSC over UDP and not have to bother with a Processing or Max serial-to-OSC converter running on the computer.  (Though, the MKR1000 is expensive, a serial-to-OSC converter makes mroe sense for use with something the more affordable Arduino Nano.)  All I did was cut the wires for the 2 joysticks and 2 z lines, soldered them to to the Ardunio analog input pins, solderdered all the red wires to VCC and all the black wires to  ground.  Overall it’s a nice controller, I just wish the X/Y joysticks had the same spring resistance that the z axis does.
     For the output, I wrote a basic FM synthesizer that I like playing with.

• How to compile it, if necessary (including information about any external libraries that are required)
     To run the output you just need Max7.
     To run the Arduino code, you need a few libraries.  The SPI library is built into the Arduino IDE, but you’ll need to use the library manager to get WiFi101, which aslo gives you WiFiUDP.  Then, you’ll need to manually install the CNMAT OSC library (https://github.com/CNMAT/OSC).  To run this project you do need to change the SSID and password in the Arduino code to match your wifi network login.  It only works with WEP, WPA, and WPA2.My MKR1000 was being a real pain with uploading (one of the reasons I decided to bake it into this controller), but I found that pressing the reset button right before clicking upload in the IDE usually worked.  


• How to run it and use it
     Just provide power to the arduino, run the max patch, and wekinator.  You need to set up wekinator with 7 inputs and 8 continuous outputs.  I used neural network for the inputs.  To keep it clean, I used the input/output editor such that inputs 5-7 are only used on outputs 1-4, and inputs 2-4 are only used on outputs 5-8.  I turned input 1 off completely (the foot switch) as I did not use it for this project.  You do need to edit the output ranges in wekinator as well.  They should be: 0-1, 0-3, 0-255, 0-10, 0-0.5, 0-3, 0-255, 0-10, 0-0.5    

