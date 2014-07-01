#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"
#pragma hdrstop
#pragma argsused
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <LiquidCrystal.h> // libraries for hardware and chip setup

#define ADAFRUIT_CC3000_IRQ   3 // These are the interrupt and control pins 

#define ADAFRUIT_CC3000_VBAT  5 // These are the interrupt and control pins
#define ADAFRUIT_CC3000_CS    10 // These are the interrupt and control pins

Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIV2); // setup up instance of WIFI board using defined pis and setting clock speed

#define WLAN_SSID       "Mr cool"           // Declared WIFI SSID
#define WLAN_PASS       "BROEEEAC"          // SSID Passcode
#define WLAN_SECURITY   WLAN_SEC_WPA2       // Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WEBSITE      "www.comp4.net16.net"  // Server URKL
#define WEBPAGE      "/arduinoreciever.php" // Web page adress so the hardware can find the PHP script

uint32_t ip; // define ip  unsigned integer 32 bits long
uint32_t ip1; // define ip  unsigned integer 32 bits long
uint32_t ip2; // define ip  unsigned integer 32 bits long
using namespace std; // load standard controls


struct Tree //user defined record for the Tree
{
int nodeID; // integer deffinition of the id of the node
int Leftpointer; // node that is to the left of the current node
int Rightpointer; // node that is to the right of the current node
boolean (*function)(int); // boolean function pointer so that the node can point to the corresponding function and pass an int variable with it
int Check; // see whether the node has been processed by the traversal program
int sensorvalue; // sensor value to pass through with the function
};


String blog; // string to place the generated boiler log (blog) in to send to the server
Tree node[8]; // create instace of record
int counter = 0; // counter to count amount of bytes read and distributed to a node
LiquidCrystal lcd(8, 9, 4, 2, 6, 7); // define the pins the LCD screen will be connected to on the board
char inByte = '0'; // declare the variable the incoming byte is placed.



void setup(void) // setup function
{
   
  for (int i = 0; i < 8; i++) {
		node[i].nodeID = i; // declare the node ID for each node
	}

                                                  // sets up the tree and joins all the nodes together using the right and left pointers. 
	node[0].Leftpointer = node[1].nodeID;     // all nodes with no  leaf are closed by declaring their left and right pointers as 0.
	node[0].Rightpointer = node[2].nodeID;

	node[1].Leftpointer = node[3].nodeID;
	node[1].Rightpointer = node[4].nodeID;

	node[2].Leftpointer = node[5].nodeID;
	node[2].Rightpointer = node[6].nodeID;

	node[3].Leftpointer = 0;
	node[3].Rightpointer = 0;

	node[4].Leftpointer = 0;
	node[4].Rightpointer = 0;

	node[5].Leftpointer = 0;
	node[5].Rightpointer = 0;

	node[6].Leftpointer = 0;
	node[6].Rightpointer = 0; 


 lcd.begin(16, 2);  // sets up lcd screen with 16 columns long and 2 rows

   cc3000.begin(); // begin the wifi board
 cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY);  // connect wifi board to network

}

void loop(void)// the main function that will loop when the board is powered
{
 
      while (!cc3000.checkDHCP()){  // while the DHCP is not connected, wait 1 ms
      delay(100); 
    } 
  
ip = 0;  // set the ip to 0
     cc3000.getHostByName(WEBSITE, &ip); // get the ip adress of the defined website and reference it to ip variable

    Adafruit_CC3000_Client www = cc3000.connectTCP(ip, 80); // create a new connection called www and conect to the ip found above with the port 80
  if (www.connected()) { // if connected....
    www.fastrprint(F("GET ")); // sends the entire string over to the tcp layer without sending bit by bit. The f() formats the string and saves it to dynamic memory.
    www.fastrprint(WEBPAGE);
    www.fastrprint(F(" HTTP/1.1\r\n"));
    www.fastrprint(F("Host: ")); www.fastrprint(WEBSITE); www.fastrprint(F("\r\n"));
    www.fastrprint(F("\r\n"));
    www.println(); }   // overal these ines send the request to the tcp stack and sent to the network to be processed by the server. 
  else {
    lcd.println(F("Connection failed"));    // if not conneccted, display conection failed
    return;}

 int order[7]= {3,4,1,5,6,2,0};  // array that specifies the correct order to place the procedure in the tree so that they exicute in order 

  int bytecount = 0; // counts the bytes the program has recieved from the server

  while (www.connected()) {   
    while (www.available()) {   // while conected and the data is avaliable.....
     
      bytecount++;   // incriment the bytecount every time a byte is recieved
      char c = www.read();   // set incoming byte as variable c 
       if ((bytecount > 166) && (bytecount < 175)){ // if the byte recieved are between two fixed points (this means that only the information we want is stored in the variable)
         inByte = c;                                // if between these two points, inbyte is set to the char
 
   if (int (inByte) > 63) { // if the incoming byte is a letter (int value 63)....
      node[order[counter] - 1].sensorvalue = inByte ; /* every time a node is asigned a function, the counteer is incramented so the next function is assigned to a new node.
                                                  the node with the order number corresponding to the current counter -1 is set to that char. Each char represends a sensor for a function.
                                                  The data is sent procedure then sensor val so the previous node is asigned that sensor val hence the -1 */
   }
else {  // if not a sensor value.....
   
    switch (inByte) // case of stament with the incoming byte
{
case '1': node[order[counter]].function = &Temperaturesensor;// The node (with the order number corresponding to the current counter) funtcion pointer is set to the referance of the procedure function wanted

counter++; // incriment the counter
    break;
case '2': node[order[counter]].function = &AirPessureSwitch;// The node (with the order number corresponding to the current counter) funtcion pointer is set to the referance of the procedure function wanted

counter++; // incriment the counter
    break;
case '3': node[order[counter]].function = &Overheatstat;// The node (with the order number corresponding to the current counter) funtcion pointer is set to the referance of the procedure function wanted

counter++; // incriment the counter
    break;
case '4': node[order[counter]].function = &Fan;// The node (with the order number corresponding to the current counter) funtcion pointer is set to the referance of the procedure function wanted

counter++; // incriment the counter
    break;
case '5': node[order[counter]].function = &Gasvalve;// The node (with the order number corresponding to the current counter) funtcion pointer is set to the referance of the procedure function wanted

counter++; // incriment the counter
    break;
case '6': node[order[counter]].function = &Pump;// The node (with the order number corresponding to the current counter) funtcion pointer is set to the referance of the procedure function wanted

counter++; // incriment the counter
    break;
case '7': node[order[counter]].function = &Ignitionelectrode;// The node (with the order number corresponding to the current counter) funtcion pointer is set to the referance of the procedure function wanted

counter++; // incriment the counter
    break;
    
case '8': { // if inbyte is 8.....
  counter++; // incriment counter
 for (int i = 0; i < 7; i++){ 
   treetraversal(0); // goto tree traversal 8 times each with 0. this gives the chance for each node to be checked and exicuted properly
}

for (int i = 0; i < 7; i++){
   node[i].Check = false;  // set every node check to false so that traversal can run again
}
                                   
   cc3000.getHostByName("www.comp4.net16.net", &ip1) ; // get the ip adress of the defined website and reference it to ip1 variable
{

  Adafruit_CC3000_Client www1 = cc3000.connectTCP(ip1, 80); // create a new connection called www1 and conect to the ip1 found above with the port 80
  if (www1.connected()) { // if connected....
    www1.fastrprint(F("GET ")); // sends the entire string over to the tcp layer without sending bit by bit. The f() formats the string and saves it to dynamic memory.
    www1.fastrprint("/clientsendinstruction.php?a=9");
    www1.fastrprint(F(" HTTP/1.1\r\n"));
    www1.fastrprint(F("Host: ")); www1.fastrprint("www.comp4.net16.net"); www1.fastrprint(F("\r\n"));
    www1.fastrprint(F("\r\n"));
    www1.println(); // code requests the php script on the server (webpage seen above) with the url variable a = 9. This sends the byt 9 to the script which tells the server the program has 
                   //recieved the instruction and it has exicuted. this then changes the server page so it doesnt tell the hardware to run the program
  } else {
    lcd.println(F("Connection failed"));    // if not connected display connection failed
  }
 
  while (www1.connected()) { // while conected to the site....
sendlog(); // execute send log and then close the connection that send the verification bit to the server
www1.close(); 
  }
   
 www.close();  // close intial connection that recieved the bytes

}}
    break;
    
case '9':  // case of 9 (no message from server, hardware will loop around and keep checking)
counter = 0; // set counter to 0 for when an instruction is recieved
lcd.setCursor(0, 0); // sent LCD curser to these co-ordiantes
lcd.write("no pcb chosen"); // display on the LCD the current status
lcd.setCursor(0, 1); 
lcd.write("                         ");

break;
       
       }
    }
  }

    
    }
}

}


boolean Temperaturesensor(int intval){ // The main procedures that depending on the boiler are called depending on the boiler and the value of the sensor. Each assigned to a tree node.
        lcd.setCursor(0, 0); /* in here would go the instructions to control the hardware such as pin modulation but for proof of concept when called it displays the undergoing
                              process in the LCD screen and adds the procedure to the log to send to the url. */
        lcd.print("temp sens  ");   
        lcd.setCursor(0, 1); 
        lcd.print(intval -96); 
        blog = blog + "temsenstest";
      delay (1000); } 
boolean AirPessureSwitch(int intval){ // The main procedures that depending on the boiler are called depending on the boiler and the value of the sensor. Each assigned to a tree node.
        lcd.setCursor(0, 0); /* in here would go the instructions to control the hardware such as pin modulation but for proof of concept when called it displays the undergoing
                              process in the LCD screen and adds the procedure to the log to send to the url. */
        lcd.print("air pressure           "); 
        lcd.setCursor(0, 1);
        lcd.print(intval -96);  
        blog = blog + "airswitchtest";
      delay (1000); }
boolean Overheatstat(int intval){ // The main procedures that depending on the boiler are called depending on the boiler and the value of the sensor. Each assigned to a tree node.
        lcd.setCursor(0, 0);/* in here would go the instructions to control the hardware such as pin modulation but for proof of concept when called it displays the undergoing
                              process in the LCD screen and adds the procedure to the log to send to the url. */
        lcd.print("overheat          "); 
        lcd.setCursor(0, 1);
        lcd.print(intval -96);  
        blog = blog + "overheattest";
      delay (1000); }
boolean Fan(int intval){ // The main procedures that depending on the boiler are called depending on the boiler and the value of the sensor. Each assigned to a tree node.
        lcd.setCursor(0, 0);/* in here would go the instructions to control the hardware such as pin modulation but for proof of concept when called it displays the undergoing
                              process in the LCD screen and adds the procedure to the log to send to the url. */
        lcd.print("fan         "); 
        lcd.setCursor(0, 1);
       lcd.print(intval -96);
       blog = blog + "fantest";
      delay (1000); }
boolean Gasvalve(int intval){ // The main procedures that depending on the boiler are called depending on the boiler and the value of the sensor. Each assigned to a tree node.
        lcd.setCursor(0, 0);/* in here would go the instructions to control the hardware such as pin modulation but for proof of concept when called it displays the undergoing
                              process in the LCD screen and adds the procedure to the log to send to the url. */
        lcd.print("gasvalve          "); 
        lcd.setCursor(0, 1);
        lcd.print(intval -96);
        blog = blog + "gastest";
      delay (1000); }
boolean Pump(int intval){ // The main procedures that depending on the boiler are called depending on the boiler and the value of the sensor. Each assigned to a tree node.
        lcd.setCursor(0, 0); /* in here would go the instructions to control the hardware such as pin modulation but for proof of concept when called it displays the undergoing
                              process in the LCD screen and adds the procedure to the log to send to the url. */
        lcd.print("pump          "); 
        lcd.setCursor(0, 1);
        lcd.print(intval -96); 
        blog = blog + "pumptest";
      delay (1000); }
boolean Ignitionelectrode(int intval){ // The main procedures that depending on the boiler are called depending on the boiler and the value of the sensor. Each assigned to a tree node.
        lcd.setCursor(0, 0); /* in here would go the instructions to control the hardware such as pin modulation but for proof of concept when called it displays the undergoing
                              process in the LCD screen and adds the procedure to the log to send to the url. */
        lcd.print("ignition          "); 
        lcd.setCursor(0, 1);
        lcd.print(intval -96);
        blog = blog + "igntest";
      delay (1000); }


void treetraversal(int currentnode){ // Tree traversal algorithm 

	if ((node[currentnode].Leftpointer > 0) && (node[node[currentnode].Leftpointer].Check == false)) { 
	currentnode = node[currentnode].Leftpointer ;
	treetraversal(currentnode); }
/* See if node has a left pointer and if the left pointer node has been check or not. if not, make current node the left pointer and recurse with this node.
 this will check to see if the current node has a left pointer and it has been checked and if so it will recurse again till it cant find one.
once it finds a checked node or node without left leaf, check to see if it has a right and if it has been checked. */
	else if ((node[currentnode].Rightpointer > 0) && (node[node[currentnode].Rightpointer].Check == false)) {
	currentnode = node[currentnode].Rightpointer;
	treetraversal(currentnode);}
/* repeat the process but with right nodes untill the furthermost node has been found with no leafs or unchecked nodes beneith. if not, it will recures again with this new variable as 
as current node */

	else {
	node[currentnode].Check = true; // this node is now checked and the variable in the record is set to checked.
node[currentnode].function(node[currentnode].sensorvalue); // this executes the function pointer with the sensor value for this node meaning that the function is executed by the traversal.

}// this is a pre order tree traversal

}

void sendlog(){ // this function returns the log generated by the testing functions.
 
  blog = ("/arduinoserverlog.php?a=" + blog); // each diagnosis is appended to blog and then appended to a variable in the .GET URl so the string can be sent to the server and added to the log.
    while (!cc3000.checkDHCP()){ // while the DHCP is not connected, wait 1 ms
      delay(100); 
    } 
    
   cc3000.getHostByName("www.comp4.net16.net", &ip2); // get the ip adress of the defined website and reference it to ip2 variable
 
  Adafruit_CC3000_Client www2 = cc3000.connectTCP(ip2, 80); // create a new connection called www2 and conect to the ip found above with the port 80
  if (www2.connected()) { // if connected....
    www2.fastrprint(F("GET "));// sends the entire string over to the tcp layer without sending bit by bit. The f() formats the string and saves it to dynamic memory.
    www2.fastrprint(blog.c_str());
    www2.fastrprint(F(" HTTP/1.1\r\n"));
    www2.fastrprint(F("Host: ")); www2.fastrprint("www.comp4.net16.net"); www2.fastrprint(F("\r\n"));
    www2.fastrprint(F("\r\n"));
    www2.println(); // This code sends the request to the server with the log assigned to a variable in the URL so that the server reads and concats the log with the incoming information.
      lcd.print(blog); // display log on the LCD of the hardware
  } else {
    lcd.println(F("Connection failed"));  // if conection failed, lcd print the message   
  }
 
  while (www2.connected()) { //while connected......
    delay(100);      // delay 1 ms (gives enough time for the request to be sent)
www2.close();        // close the connection
  } 
 
}

