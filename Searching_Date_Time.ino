/*
The following code searches for a specific date and time introduced by the user in a 
CSV filen logged by different sensors. The code checks if both the date and time match
in the same value reading provided by a sensor and if so it prints out the reading 
values associated with that date and time.

Created, edited, and modified Jorge Salazar Sanchez
in June 2019
*/

#include <SPI.h>
#include <SD.h>
#include <string.h>

File myFile;

int arrayPointer = 0;
int n=0;
int q=0;
int number = 6;
int counter=0;
int total_counter=0;
int counter1=0;
int counter2=0;

char* strings[20];
char* zero="0";

String my_date;
String my_hour;
String minute_;

long month_=0;
long day_=0;
long year_=0;

long hour_=0;
long minute_1=0;



///////////////////////////////////////////////////////////////////
// Setting up Communications (SETUP)
//////////////////////////////////////////////////////////////////

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


///////////////////////////////////////////////////////////////////
// Setting up Serial Port and the SD Card
//////////////////////////////////////////////////////////////////

  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  

  if (!SD.begin(10)) {
    Serial.println(F("initialization failed!"));
    return;
  }
  Serial.println(F("initialization done."));
  delay(2000);

Serial.println("");


///////////////////////////////////////////////////////////////////
// Searching for the date and time
//////////////////////////////////////////////////////////////////

// Functions that return the introduced date and time by the user
my_date=readingsdate();
my_hour=readingtime();

delay(3000);

Serial.println("");
Serial.println("");
Serial.println(F("These are the readings related to the selected DATE and TIME:"));
Serial.println("");



    // re-open the file for reading:
  myFile = SD.open("sonde10.csv");

  if (myFile) {
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {

    // Place the reading value in a String variable
      String line1 = myFile.readStringUntil('\n');
      String line2 = line1;
      
   // Break a string value into tokens
      char* a = (char*) line1.c_str();
      //char* c = a;
      char* b = NULL;
      b = strtok(a, ",");    

   // Place the tokens into a characters array
    while(b != NULL){
                  
            strings[arrayPointer] = b;
            arrayPointer++;
            b = strtok(NULL, ",");
   }    

    /////////////////////////////////////////////////////////////////////////
    // Convert each character array value into string values to compare it //
    // with the introduced values (date and time) by the user //
    /////////////////////////////////////////////////////////////////////////

     for (n=0; n<arrayPointer; n++){

       String str(strings[n]);
     
         if (str.equals(my_date)) {
             counter1 += 1;
         } 
         else if ((str.substring(0,number) == my_hour)) {
             counter2 += 1;
         }else {}
      }

     ///////////////////////////////////////////
     //// Check if the code read  ////
     ///////////////////////////////////////////

      counter = counter1 + counter2;

if (counter == 2) {
          Serial.println(line2);
          total_counter += 1;
          counter1 = 0; 
          counter2 = 0;
          
      }else{counter1 = 0; 
            counter2 = 0;}  


  

     ///////////////////////////////////////////
     //// Clear (initialize) existing array ////
     ///////////////////////////////////////////
      memset(strings,0, sizeof(strings));
             arrayPointer = 0;
             n = 0;
 }
 
////////////////////////////////////////////////////////////////////////////
// Checking if there have been reading values. If not, print out a message
////////////////////////////////////////////////////////////////////////////


/*
 if (n == arrayPointer && counter != 2) {
          Serial.println(F("No readings values found for that DATE and TIME. Please, introduce them again."));    
  }else if (n == arrayPointer && counter == 2){
          counter=0;    
    } else {}
*/

 if (total_counter >= 1) {counter=0;}

 else {   Serial.println(F("No readings values found for that DATE and TIME. Please, introduce them again."));}    


}
 
  else {
    // if the file didn't open, print an error:
    Serial.println(F("error opening test.txt"));
  }

    // Close the file
    myFile.close();
    Serial.println("");
    Serial.println(F("finished"));
}




void loop() {

//Nothing to do

}




///////////////////////////////////////////////////////////////////////
// Fucntion that asks for and returns the time introduced by the user 
///////////////////////////////////////////////////////////////////////

String readingsdate() {
  
// Introduce the MONTH:
Serial.println(F("Introduce the MONTH"));

while (Serial.available()==0);
month_ = Serial.parseInt();  
Serial.println(month_);


// Ckeck and validation of the MONTH:
while ((month_>12) || (month_ <= 0)) {

        Serial.println(F("Please, Introduce the MONTH again. This is not a valid MONTH"));
        Serial.end();
        Serial.flush();
        Serial.begin(9600);
        while (Serial.available()==0);
        month_ = Serial.parseInt();  

}

        Serial.println("");
        Serial.print(F("You introduced the month = "));
        Serial.println(month_);
        Serial.println("");
        delay(2000);

// Introduce the DAY:
        Serial.end();
        Serial.flush();
        Serial.begin(9600);
        Serial.println(F("Introduce the DAY"));
        while (Serial.available()==0);
        day_ = Serial.parseInt();  
        Serial.println(day_);


// Ckeck and validation of the DAY:
while ((day_ > 31) || (day_ <= 0)) {

        Serial.println(F("Please, Introduce the DAY again. This is not a valid DAY"));
        Serial.end();
        Serial.flush();
        Serial.begin(9600);
        while (Serial.available()==0);
        day_ = Serial.parseInt();  

}

        Serial.println("");
        Serial.print(F("You introduced the DAY = "));
        Serial.println(day_);
        Serial.println("");
        delay(2000);


// Introduce the YEAR:
        Serial.end();
        Serial.flush();
        Serial.begin(9600);
        Serial.println(F("Introduce the YEAR"));
        while (Serial.available()==0);
        year_ = Serial.parseInt();  
        Serial.println(year_);


// Ckeck and validation of the YEAR:
while ((year_ > 2019) || (year_ < 2015) || (year_ == 0)) {

        Serial.println(F("Please, Introduce the YEAR again. This is not a valid YEAR"));
        Serial.end();
        Serial.flush();
        Serial.begin(9600);
        while (Serial.available()==0);
        year_ = Serial.parseInt();  

}

        Serial.println("");
        Serial.print(F("You introduced the YEAR = "));
        Serial.println(year_);
        Serial.println("");



delay(2000);


// Print out and return the date introduced by the user:
String mydate = ((String)month_+"/"+day_+"/"+year_);
Serial.print(F("The date to search is: "));
Serial.println(mydate);
Serial.println("");
Serial.println("");
Serial.println("");

return mydate;

}




///////////////////////////////////////////////////////////////////////
// Fucntion that asks for and returns the time introduced by the user 
///////////////////////////////////////////////////////////////////////

String readingtime() {

// Introduce the HOUR:
Serial.println(F("Introduce the HOUR"));

while (Serial.available()==0);
hour_ = Serial.parseInt();  
Serial.println(hour_);


// Ckeck and validation of the HOUR:
while ((hour_>=24) || (hour_<0)) {

        Serial.println(F("Please, Introduce the HOUR again. This is not a valid HOUR"));
        Serial.end();
        Serial.flush();
        Serial.begin(9600);
        while (Serial.available()==0);
        hour_ = Serial.parseInt();  

}


/////////////////////////////////////////////////////////////////////////////////////////////////
// In case the HOUR_ variable is less than ten, the index "to" of the substring function updates
// because the default hour provided by the sensor has only one digit
/////////////////////////////////////////////////////////////////////////////////////////////////

if (hour_ < 10) {
     number =  number - 1; 
}

else {}

        Serial.println("");
        Serial.print(F("You introduced the HOUR = "));
        Serial.print(hour_);
        Serial.println(F("h"));
        Serial.println("");
        delay(2000);

// Introduce the MINUTE/s:
        Serial.end();
        Serial.flush();
        Serial.begin(9600);
        Serial.println(F("Introduce the minute/s"));
        while (Serial.available()==0);
        minute_1 = Serial.parseInt();  
        Serial.println(minute_1);


// Ckeck and validation of the MINUTE/s:
while ((minute_1 > 59) || (minute_1 < 0)) {

        Serial.println(F("Please, Introduce the MINUTE/s again. This is not a valid MINUTE"));
        Serial.end();
        Serial.flush();
        Serial.begin(9600);
        while (Serial.available()==0);
        minute_1 = Serial.parseInt();  

}


/////////////////////////////////////////////////////////////////////////////////////////////////
// In case the value of the MINUTE_1 variable introduced by the user is less than ten, that is, 
// only one digit, the value of the MINUTE_ variable is updated to two digits (adding a zero (0))
/////////////////////////////////////////////////////////////////////////////////////////////////

 if (minute_1 < 10){
   minute_ =  ((String)"0"+minute_1);
   goto jump;
 }  

else { 
   minute_= (String) minute_1;
   goto jump;
}


// The algorithm keeps on executing the code once the MINUTE_1 variable updated
jump:
        Serial.println("");
        Serial.print(F("You introduced the MINUTE = "));
        Serial.print(minute_);
        Serial.println(F("min"));
        Serial.println("");
        delay(2000);


        String myhour = ((String)hour_+":"+minute_+":");

        Serial.print(F("The TIME to search is: "));
        Serial.print((String)hour_+":"+minute_);
        Serial.println(F("h"));
        Serial.println("");

return myhour;

}
  
  
  
  
  
  






