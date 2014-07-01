//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#define  LPWSTR         wchar_t*
#include <stdlib.h>
# include <sstream>
#include <winsock2.h>
#include <wchar.h>
					  // libraries used in the main program

#include "projectdone.h"   // link to the header file with all defined function and classes
#include "Unit4.h"   // link to the Form file with Baudrate settings field on it
#include "Unit5.h"   // link to the Form file with Com port settings field on it
#include "Unit6.h"   // link to the Form file with Data bits settings field on it
#include "Unit7.h"   // link to the Form file with Parity bits settings field on it
#include "Unit8.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)  // provides addition information to the compiler (smart package)
#pragma resource "*.fmx"  // provides addition information to the compiler(compile .fmx file)
TForm3 *Form3; // Builds the object Tform3 into Form3 so that it can be used in the program
TForm4 *Form4; // Builds the object Tform4 into Form4 so that it can be used in the program
TForm5 *Form5; // Builds the object Tform5 into Form5 so that it can be used in the program
TForm6 *Form6; // Builds the object Tform6 into Form6 so that it can be used in the program
TForm7 *Form7; // Builds the object Tform7 into Form7 so that it can be used in the program
TForm8 *Form8;
Tsuprima *suprima; // Builds the object Tsuprima into suprima so that it can be used in the program
Tbaxi *baxi;  // Builds the object Tbaxi into baxi so that it can be used in the program
TImportedboiler *Importedboiler;


using namespace std; // Load the Standard Library controls.
wchar_t*  baud  ; // variable to contain the unichar data entered into baud rate settings
wchar_t*  data  ; // variable to contain the unichar data entered into data bits settings
wchar_t*  com  ;  // variable to contain the unichar data entered into com port settings
wchar_t*  par  ;  // variable to contain the unichar data entered into parity settings
int unichartostring [4]; // string to convert each unichar into int
int xpos ; // Circle x position
int  direction = 10; // direction of circle travel

int imporder[8];
wchar_t wcs[8];


__fastcall TForm3::TForm3(TComponent* Owner) // function to set up the inital form
	: TForm(Owner)
{
  	xpos = Form3 -> Circle1 ->Position -> X ;  // set xpos as the current position of the circle

}

int portsend(int choice) {  // function that recieves the Boiler choice and initiates the correstponding function.
	Form3 ->Timer2->Enabled=true; // start the timer 2 (starts the loading bar)
	Form3 ->Timer1->Enabled=true; // starts timer 1 (starts log download and stayus label)
	Form3 -> Label2 -> Text = "runing"; // change status label to running
	memoprocedure = ""; // empty the procedure string to be displayed in the log
	switch (choice) // start case of statment with variable choice (boiler ID is sent here)
{
	case '1': suprima ->PCBtest(); // if Boiler ID is 1, run procedure PCB test within the boiler class in the header file
		break;
	case '2': baxi ->PCBtest(); // if Boiler ID is 2, run procedure PCB test within the boiler class in the header file
	  break;
	case '3': break; // if Boiler ID is 2, run procedure PCB test within the boiler class in the header file
	  }
	Form3 -> Memo1 -> Text = memoprocedure; // output the procedure run through in the procedure memo
	if (transtype == false) {   // if the mode is wirless...
			sendurlrequest();          // send the url with the .GET request to the PHP server
			ulrrequestsend = "";        // empty URL Request for next time
	}
}

void __fastcall TForm4::EditButton1Click(TObject *Sender) // when Baudrate settings button clicked from form 4 (header file declared above)
{

	baud = Edit1 -> Text.c_str(); // set variable baud as the unichar data in text edit
	ShowMessage(baud); // display to the user the value they chose
	for (int y = 0; y < 4; y++) { // incriment y untill all 4 characters have been converted to int
		unichartostring[y] =baud[y] - 48;  // copy the int equivelent of the char into each array cell of unichartostring
	}

	baudratechar = (unichartostring [0] * 1000) + (unichartostring [1] * 100) + (unichartostring [2] * 10) + (unichartostring [3] *1 ); 
		if ((baudratechar > 7000)|| (baudratechar < 1 )){     // check to see if baudrate lies in the correct range
	  ShowMessage("please enter value less than 7000 or greater than 1"); // else output error
	}
}// set Baudrate char to the int equivelent of the values stored in unichartostring. This procedure converts unichar to integer.

void __fastcall TForm5::EditButton1Click(TObject *Sender) // when Baudrate settings button clicked from form 5 (header file declared above)
{
	com = Edit1 -> Text.c_str();  // set variable com to unichar data entered by the user
	comportchar=com[0];         // convert unichar to char to be used by the program
	ShowMessage(comportchar); // show the user the variable they entered
	   if ((int(comportchar) < 49) || ((int(com[1]) > 48)&& (int(com[1]) < 59))) { // if the data first number is less than the ascii value for 0 or the second number is the ascii value for 1-9 show the error. 
	ShowMessage("please enter number between 1 and 10");   
   }
}

void __fastcall TForm6::EditButton1Click(TObject *Sender) // when Baudrate settings button clicked from form 5 (header file declared above)
{
	par = Edit1 -> Text.c_str(); // set variable com to unichar data entered by the user
	paritychar=par[0];         // convert unichar to char to be used by the program
	if ((paritychar != 'y')&&(paritychar != 'n')) { // if no valid parity option
	ShowMessage("enter a valid parity option"); // output error
	}
	ShowMessage(paritychar);  // show the user the variable they entered
}

void __fastcall TForm7::EditButton1Click(TObject *Sender) // when Baudrate settings button clicked from form 5 (header file declared above)
{
	data = Edit1 -> Text.c_str(); // set variable com to unichar data entered by the user
	datachar=data[0];            // convert unichar to char to be used by the program
	ShowMessage(datachar); // show the user the variable they entered
   if ((int(datachar) < 49) || ((int(data[1]) > 48)&& (int(data[1]) < 59))) { // if the data first number is less than the ascii value for 0 or the second number is the ascii value for 1-9 show the error. 
	ShowMessage("please enter number between 1 and 10");   
   }
}

void __fastcall TForm3::ListBoxItem1Click(TObject *Sender) // button for Boiler 1
{
	portsend('1'); // send the Boiler ID 1 to portsend funtion
}

void __fastcall TForm3::ListBoxItem2Click(TObject *Sender) // button for Boiler 2
{
	portsend('2'); // send the Boiler ID 2 to portsend funtion
}

void __fastcall TForm3::MenuItem4Click(TObject *Sender) // button for Baudrate settings in menu
{
TForm4 *Form = new TForm4( this );
	Form4->ShowModal(); // display Form4 with Baudrate settings on it
}

void __fastcall TForm3::MenuItem5Click(TObject *Sender) // button for Com port settings in menu
{
TForm5 *Form = new TForm5( this );
	Form5->ShowModal(); // display Form5 with Com port settings on it
}

void __fastcall TForm3::MenuItem6Click(TObject *Sender) // button for Data bit settings in menu
{
TForm6 *Form = new TForm6( this );
	Form6->ShowModal(); // display Form6 with Data bit settings on it
}

void __fastcall TForm3::MenuItem7Click(TObject *Sender) // button for Parity settings in menu
{
TForm7 *Form = new TForm7( this );
	Form7->ShowModal(); // display Form7 with Parity settings on it
}


void __fastcall TForm3::MenuItem8Click(TObject *Sender) // help button in menu
{
	ShowMessage("copyright Euroboiler parts, designed and coded by Jaskiran Nagi. vs.1");  // display software information to user

}


void __fastcall TForm3::Timer2Timer(TObject *Sender)  // function for timer that is exicuted periodiaclly when timmer is enabled.
{

	Circle1 ->Position -> X = Circle1 ->Position -> X + direction ; /* move circle in one direction by adding the data in the direction variable to 
																  the x position */
	if (Circle1 -> Position -> X < (xpos -80) || Circle1 ->Position -> X > ( xpos + 80)) {
		direction = - direction; // if the position of the shape goes to far to either side, reverse the direction

	}
}

void __fastcall TForm3::Timer1Timer(TObject *Sender) // contents of function are executed ant regular interval when timer is enabled
{
	recivelog(); // recieve the log from the server
	Form3 -> Memo2->Text = source; // source contains the log information. This outputs the Log in a memo to display to the user
	if (timer1 == false) { // after log retrieved, timer is disabled. therefor if disabled...
		Form3 ->Timer1->Enabled=false;
		Form3 ->Timer2->Enabled=false; // disable both timers 
		Label2 ->Text = "Succesfully uploaded"; // change status label
		Circle1 ->Position -> X = xpos  ; // reset loading bar
	}
}


void __fastcall TForm3::Button1Click(TObject *Sender) // Retrieve log
{
	recivelog(); // manualy retrieve log from server
	Form3 -> Memo2->Text = source + "\n" + "\n" ; // output log with a line between each entry for clarity
}


void __fastcall TForm3::Button2Click(TObject *Sender)// button to switch data transmission methods
{
	if (transtype == false) { // if this function is called and the transtype is false (wireless)....
		transtype = true;   // make transtype true (wired)
		Form3 -> Label3 -> Text = "wired" ; // change trasmission label to wired
	}

	else {
		transtype = false; // otherwies make the transtype false
		Form3 -> Label3 -> Text = "wireless"; // change the trasmission label to wirless
	}
}





void __fastcall TForm3::MenuItem2Click(TObject *Sender)
{
TForm8 *Form = new TForm8( this );  // create insatnce of new form
Form->ShowModal(); // show new form
}

void __fastcall TForm8::Button1Click(TObject *Sender)
{

 bool error = false; // if more than one value for the order given
 bool error1 = false; // if order is out of the range specified
 int val[8] = {0,0,0,0,0,0,0,0}; // create val array



  wcscpy(wcs,Edit9 ->Text.c_str());
  wcscat(wcs,Edit10 ->Text.c_str());
  wcscat(wcs,Edit11 ->Text.c_str());
  wcscat(wcs,Edit12 ->Text.c_str());
  wcscat(wcs,Edit13 ->Text.c_str());
  wcscat(wcs,Edit14 ->Text.c_str());
  wcscat(wcs,Edit15 ->Text.c_str());
 // concats all unichar strings together from the text edits in the import form into a single unichar string

 val[1] = Edit1 ->Text.c_str()[0] - 48;
 val[2] = Edit2 ->Text.c_str()[0] - 48;
 val[3] = Edit3 ->Text.c_str()[0] - 48;
 val[4] = Edit4 ->Text.c_str()[0] - 48;
 val[5] = Edit5 ->Text.c_str()[0] - 48;
 val[6] = Edit6 ->Text.c_str()[0] - 48;
 val[7] = Edit7 ->Text.c_str()[0] - 48;
// converts the order for each procedure order (recieved from the input form) from unichar into integer.


int count[7] = {0,0,0,0,0,0,0};  // counter for each order to see if it occurs more than once

for (int i = 0; i < 8; i++) {
switch (val[i]) {
case 1:
count[1]++;
	break;
case 2:
count[2] ++;
	break;
case 3:
count[3] ++;
	break;
case 4:
count[4] ++;
	break;
case 5:
count[5] ++;
	break;
case 6:
count[6] ++;
	break;
case 7:
count[7] ++;
	break;
}
  }   // sees whether for each value of i, there are more than one value for the order number. if so the counter array with cell is incrimented by one.

  for (int i = 1; i < 8; i++) {
   imporder[val[i]] = i;   // this arranges the procedure import order (globally defined) in chronological order so the procedures are called in the correct order.
  }



for (int i = 0; i < 8; i++) {
 if (count[i] > 1) {
  error = true;    // see whether the order number occurs more than once. if so, make bool variable true.
 }
 else if ((val[i] > 8) || (val[i] < 1)) {
  error1 = true;  // see whether the order number is within range. if so, make bool variable true.
 }



 }

if (error == true) {         // if the error val is true, output error message
ShowMessage("Please enter one value for each procedure.");
return;   // return to the begining of the function
}

else if (error1 == true) {   // if the error val is true, output error message
ShowMessage("Please enter value between 1 and 8.");
return;  // return to the begining of the function
}
else {
Form3 -> ListBoxItem3 -> Visible = true;  // display menu button for new boiler
Form3 -> ListBoxItem3 -> Text = Edit8 -> Text.c_str();    } // write the boiler name defined on the button
  }

void __fastcall TForm3::ListBoxItem3Click(TObject *Sender)
{
	Form3 ->Timer2->Enabled=true; // start the timer 2 (starts the loading bar)
	Form3 ->Timer1->Enabled=true; // starts timer 1 (starts log download and stayus label)
	Form3 -> Label2 -> Text = "runing"; // change status label to running
	memoprocedure = ""; // empty the procedure string to be displayed in the log

for (int i = 1; i < 8; i++) {
  Importedboiler -> PCBtest(imporder[i],wcs[i]);
  }
  Importedboiler -> PCBtest(8,'0');
  Form3 -> Memo1 -> Text = memoprocedure; // output the procedure run through in the procedure memo
	if (transtype == false) {   // if the mode is wirless...
			sendurlrequest();          // send the url with the .GET request to the PHP server
			ulrrequestsend = "";        // empty URL Request for next time
	}

}
//---------------------------------------------------------------------------

