#ifndef projectdoneH
#define projectdoneH
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Menus.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Effects.hpp>
#include <FMX.Filter.Effects.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Memo.hpp>
#include <string>
#include <iostream.h>
#include <winsock2.h>
//various libraries used in the program.
bool transtype = false;  // depending of it this is true or false, the data transmission is selected
bool timer1 = false;   //set timer1 off.
char datachar = '8';    //set the amount of characters set via serial to 8.
char paritychar = 'n';  // set the parity of the serial conection to none.
char comportchar = '2';  // use com 2.
int baudratechar = 9600;   // baud rate of 9600.

const char CTemperaturesensor = '1';
const char CAirPessureSwitch = '2';
const char COverheatstat = '3';
const char CFan = '4';
const char CGasvalve = '5';
const char CPump = '6';
const char CIgnitionelectrode = '7';
const char Cendbit = '8';
				// defines each procedure to an ID to be sent to the hardware.

String memoprocedure = "";     // empty the string(used to display running procedures).
String source = "";            // empty the string(used to display the log).
string ulrrequestsend ;        // define string (used to send the .GET request).
using namespace std;           // Load the Standard Library controls.


class boiler                   // define new Super class called Boiler
{
   public:                     // it is public so it is defined Globaly.
	  void Temperaturesensor(char val)   /* Procedure for the Temperature sensor with local
									   variable that has a value for val passed to it. */
	  {
	  send(CTemperaturesensor, val);   // call the send function and parse through the variable val and the ID for the sensor.
	  memoprocedure = memoprocedure + "Simulate Temperaturesensor \n " ;  /* append the procedure to the string memoprcedure with a line
																		   break so that it can be displayed in a memo box.*/
	  }
	  void AirPessureSwitch(char val) /* Procedure for the AirPessureSwitch with local
										variable that has a value for val passed to it. */
	  {
	  send(CAirPessureSwitch, val);    // call the send function and parse through the variable val and the ID for the sensor.
	  memoprocedure = memoprocedure + "Simulate AirPessureSwitch \n " ;  /* append the procedure to the string memoprcedure with a line
																		   break so that it can be displayed in a memo box.*/
	  }
	  void Overheatstat(char val) /* Procedure for the Overheatstat with local
										variable that has a value for val passed to it. */
	  {
	   send(COverheatstat, val);  // call the send function and parse through the variable val and the ID for the sensor.
	   memoprocedure = memoprocedure + "Simulate Overheatstat \n " ;  /* append the procedure to the string memoprcedure with a line
																		   break so that it can be displayed in a memo box.*/
	  }
	  void Fan(char val) /* Procedure for the AirPessureSwitch with local
										variable that has a value for val passed to it. */
	  {
	   send(CFan, val); // call the send function and parse through the variable val and the ID for the procedure.
	   memoprocedure = memoprocedure + "Test Fan \n " ; /* append the procedure to the string memoprcedure with a line
																		   break so that it can be displayed in a memo box.*/
	  }
	  void Gasvalve(char val) /* Procedure for the Gasvalve with local
										variable that has a value for val passed to it. */
	  {
	   send(CGasvalve, val);  // call the send function and parse through the variable val and the ID for the procedure.
	   memoprocedure = memoprocedure + "Test Gasvalve \n " ; /* append the procedure to the string memoprcedure with a line
																		   break so that it can be displayed in a memo box.*/
	  }
	  void Pump(char val) /* Procedure for the Pump with local
										variable that has a value for val passed to it. */
	  {
	   send(CPump, val);  // call the send function and parse through the variable val and the ID for the procedure.
	   memoprocedure = memoprocedure + "Test Pump \n " ; /* append the procedure to the string memoprcedure with a line
																		   break so that it can be displayed in a memo box.*/
	  }
	   void Ignitionelectrode(char val) /* Procedure for the Ignitionelectrode with local
										variable that has a value for val passed to it. */
	  {
	  send(CIgnitionelectrode, val);  // call the send function and parse through the variable val and the ID for the procedure.
	  memoprocedure = memoprocedure + "Test Ignitionelectrode \n " ;  /* append the procedure to the string memoprcedure with a line
																		   break so that it can be displayed in a memo box.*/
	  }
	  void endbit() //Procedure that defines the endbit to tell the program end of bytes.
	  {
	  send(Cendbit, '0'); // calls send and passes the endbit ID and '0' for the val char.
	  memoprocedure = memoprocedure + "sending data \n " ; //appends endbit to memoprcedure to be displaye in teh program.
	  }
	  private : // private declaration, can only be seen locally.


	void send(char test, char sensorvalue ){ // recieves two bits of data, Procedure id (test) and value of sensor(sensorvalue);

	   if (transtype == true) {  // if true, the program undergoes wired transmission
	   ofstream myfile; // start file declaration
  myfile.open ("example1.bat"); // open this file thst is stored in the same folder
  myfile << "@echo off " << "mode COM" << comportchar << " BAUD="<< baudratechar << " PARITY="<< paritychar << " data=" << datachar << endl;
  myfile << "echo " << test << " > com" << comportchar << endl;
  myfile.close();  /* change all the text to the text above with the variables put in. This is Bash and when exicuted
					  will use Comand line shell to send the corresponding data to the COM port chosen with the settings
					  that have been declared. then closes the file */

  system("example.bat");  // run the batch file to send the data to the com port
	   }


  else {
	 ulrrequestsend = ulrrequestsend + test  ;// append the test id and value to the .GET url to send the ID to the server.
	  }


} };


class TImportedboiler: public boiler // new inherited subclass called TImportedboiler
{
   public:
	  void PCBtest(int proc,int sens){  // public function that recieves the procedure id and then calls the corresponding procedure in the super class. Each procedue is sent in order meaning that the function calls are in order.
	  switch (proc) {
	  case 1:                        // correspoding superclass procedure function called
	  Temperaturesensor(sens);
	  break;
	  case 2:
	  AirPessureSwitch(sens);
	  break;
	  case 3:
	  Overheatstat(sens);
	  break;
	  case 4:
	  Fan(sens);
	  break;
	  case 5:
	  Gasvalve(sens);
	  break;
	  case 6:
	  Pump(sens);
	  break;
	  case 7:
	  Ignitionelectrode(sens);
	  break;
	  case 8:
	  endbit();      // end bit sent after all recieved.
	   }
	  }
	  }
	  ;

	extern PACKAGE TImportedboiler *Importedboiler; // export boiler class


// Derived class
class Tsuprima : public boiler // new inherited subclass called Tsuprima
{
   public:
	  void PCBtest(){  // public function calling on the procedures in the super class in a specific order and with specific function values.
	  Temperaturesensor('a');
	  AirPessureSwitch('b');
	  Overheatstat('c');
	  Fan('d');
	  Gasvalve('e');
	  Pump('f');
	  Ignitionelectrode('g');
	  endbit();
	  }
   }   ;

   extern PACKAGE Tsuprima *suprima; // externalises this class so it can be called upon in the .cpp file.

 // Derived class
class Tbaxi : public boiler // inherited class from boiler superclass called Tbaxi.
{
   public:
	  void PCBtest(){   // public function calling on the procedures in the super class in a specific order and with specific function values.
	  Ignitionelectrode('0');
	  Pump('0');
	  Gasvalve('0');
	  Fan('0');
	  Overheatstat('0');
	  AirPessureSwitch('0');
	  Temperaturesensor('0');
	  endbit();
	  }
   }   ;

   extern PACKAGE Tbaxi *baxi;  // externalises this class so it can be called upon in the .cpp file.
//---------------------------------------------------------------------------
class TForm3 : public TForm   // public form class to define all items on the main VLC form.
{
__published:	// IDE-managed Components
	TListBox *ListBox1; // list box for all boilers
	TListBoxItem *ListBoxItem1; // first boiler button
	TListBoxItem *ListBoxItem2; // second boiler button
	TSearchBox *SearchBox1;     // search text box for boilers
	TSearchEditButton *SearchEditButton1; // search button
	TMainMenu *MainMenu1; // main menu declaration
	TMenuItem *MenuItem1; // import option
	TMenuItem *MenuItem2; // com port option
	TMenuItem *MenuItem4; // parity option
	TMenuItem *MenuItem5; // data option
	TMenuItem *MenuItem6; // Baudrate option
	TMenuItem *MenuItem7; // help option
	TMenuItem *MenuItem8; // menu item 'settings'
	TLabel *Label1; // main program title
	TTimer *Timer2; // timer responsible for loading bar
	TCircle *Circle1; // object moved for loading bar
	TMemo *Memo1;     // memo to display all procedures running
	TLabel *Label2;   // status lable telling the user when it has uploaded
	TMemo *Memo2;     // log memo to display the log
	TTimer *Timer1;   // timer responsible to outputting log, procedure memo, changing the status lable and stoping the loading bar.
	TButton *Button1; // button to download log manually
	TAffineTransformEffect *AffineTransformEffect1;
	TLabel *Label3;
	TButton *Button2;
	TListBoxItem *ListBoxItem3; // drop down effect


	void __fastcall ListBoxItem1Click(TObject *Sender);
	void __fastcall ListBoxItem2Click(TObject *Sender);
	void __fastcall MenuItem4Click(TObject *Sender);
	void __fastcall MenuItem5Click(TObject *Sender);
	void __fastcall MenuItem6Click(TObject *Sender);
	void __fastcall MenuItem7Click(TObject *Sender);
	void __fastcall MenuItem8Click(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall MenuItem2Click(TObject *Sender);
	void __fastcall ListBoxItem3Click(TObject *Sender);
												  // deifne gloabal procedures for each of the declarations in the class.

private:	// User declarations
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);         //  intialises form
};


extern PACKAGE TForm3 *Form3;    // externalises this class so it can be called upon in the .cpp file.


void recivelog(){      // define procedure to download log
	WSADATA WSAData;   // Variable to store the details of the network connection set by the computer.
	WSAStartup(MAKEWORD(2,0), &WSAData); // start network connection

	SOCKET sock;  // Variable to store the socket details of the network connection
	SOCKADDR_IN sin; // Pointer to the socket address to write data to the socket

	char buffer[1]; // define a buffer 1 byte long to read each letter of the log


	string srequest = "GET /Desktoplog.php/ HTTP/1.1\r\n";
	srequest += "Host: comp4.net16.net\r\n";
	srequest += "Connection: close\r\n";
	srequest += "Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5\r\n";
	srequest += "Accept-Language: fr,fr-fr;q=0.8,en-us;q=0.5,en;q=0.3\r\n";
	srequest += "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n";
	srequest += "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; fr; rv:1.8.1.3) Gecko/20070309 Firefox/2.0.0.3\r\n";
	srequest += "Referer: http://pozzyx.net/\r\n";
	srequest += "\r\n";
   /* the code above appends all the formating and necisary informations such as webpage
	website connection type, html version etc. for the program to execute.  */
	size_t request_size = srequest.size() + 1;  /* increase the size of the request by 1 so
	no bytes are lost */

	char crequest[5000]; // declare a request char array
	strncpy( crequest, srequest.c_str(), request_size ); /* copy unichar string into the crequest
	varibale so that the data can be used. The array uses up as much as the size of the request. */

	int i = 0;  // declare the buffer as 0;


	sock = socket(AF_INET, SOCK_STREAM, 0); // define the socket as the current socket settings.

	sin.sin_addr.s_addr = inet_addr("31.170.161.56"); // connect to IP of website
	sin.sin_family = AF_INET;
	sin.sin_port = htons(80); // port HTTP.

	connect(sock, (SOCKADDR *)&sin, sizeof(sin)); // connect to socket address
	send(sock, crequest, strlen(crequest), 0); // send request string to server
	bool read = false; // if read is true the program will store the bytes its recieves.



		   do {
		i = recv(sock, buffer, sizeof(buffer), 0); // copy data into buffer
		if (buffer[0] == 'Q') { // if Q (start bit) is recieved, read = true
		   read = true;

		   i = recv(sock, buffer, sizeof(buffer), 0);  // copy data into buffer
		}

		if (buffer[0] == 'Z') { // if Z (end bit) is recieved, read = false
		   read = false; // stop reading so define read as false
		   timer1 = false; // stop timer 1 so that the log downloads, the status lable changes and stops the loading bar
		}

		if (read == true) {// while read is true, add the buffer to the source. this builds up a log
		   source = source + buffer[0]; // add buffer to log
		}


   } while (i != 0)    ;   // while there is data

	closesocket(sock); // close socket
	WSACleanup();   // clean up all recieved data from heap.
   return;
}

void sendurlrequest(){ // sends the .GET request to the server
	WSADATA WSAData; // Variable to store the details of the network connection set by the computer.
	WSAStartup(MAKEWORD(2,0), &WSAData); // start network connection

	SOCKET sock; // Variable to store the socket details of the network connection
	SOCKADDR_IN sin; // Pointer to the socket address to write data to the socket

	char buffer[1024]; // buffer to recieve data into


	string srequest = "GET /clientsendinstruction.php?a=" + ulrrequestsend + " HTTP/1.1\r\n";
	srequest += "Host: www.comp4.net16.net\r\n";
	srequest += "Connection: close\r\n";
	srequest += "Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5\r\n";
	srequest += "Accept-Language: fr,fr-fr;q=0.8,en-us;q=0.5,en;q=0.3\r\n";
	srequest += "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n";
	srequest += "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; fr; rv:1.8.1.3) Gecko/20070309 Firefox/2.0.0.3\r\n";
	srequest += "Referer: http://pozzyx.net/\r\n";
	srequest += "\r\n";
    /* the code above appends all the formating and necisary informations such as webpage
	website connection type, html version etc. for the program to execute.  */

	size_t request_size = srequest.size() + 1; /* increase the size of the request by 1 so
	no bytes are lost */

	char crequest[5000];  // declare a request char array
	strncpy( crequest, srequest.c_str(), request_size ); /* copy unichar string into the crequest
	varibale so that the data can be used. The array uses up as much as the size of the request. */

	int i = 0; // declare the buffer as 0;


	sock = socket(AF_INET, SOCK_STREAM, 0); // define the socket as the current socket settings.

	sin.sin_addr.s_addr = inet_addr("31.170.161.56"); // connect to IP of website
	sin.sin_family = AF_INET;
	sin.sin_port = htons(80); // port HTTP.

	connect(sock, (SOCKADDR *)&sin, sizeof(sin)); // connect to socket address
	send(sock, crequest, strlen(crequest), 0); // send request string to server


	do
	{
		i = recv(sock, buffer, sizeof(buffer), 0); // retrieves the received data buffer.

	} while (i != 0);// while there is data.


	closesocket(sock); // close socket
	WSACleanup(); // clean up all recieved data from heap.


}

#endif
