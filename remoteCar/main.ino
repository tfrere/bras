//#include "infraredLib/IRremote.h"
//#include "infraredLib/IRremoteInt.h"

#include "IRremote.h"
#include "IRremoteInt.h"

#define BUTTON_1 16753245 // FFA25D
#define BUTTON_2 16736925 // FF629D
#define BUTTON_3 16769565 // FFE21D

#define BUTTON_4 16720605 // FF22DD
#define BUTTON_5 16712445 // FF02FD
#define BUTTON_6 16761405 // FFC23D

#define BUTTON_7 16769055 // FFE01F
#define BUTTON_8 16754775 // FFA857
#define BUTTON_9 16748655 // FF906F

#define BUTTON_10 16738455 // FF6897
#define BUTTON_11 16750695 // FF9867
#define BUTTON_12 16756815 // FFB04F

#define BUTTON_13 16724175 // FF30CF
#define BUTTON_14 16718055 // FF18E7
#define BUTTON_15 16743045 // FF7A85

#define BUTTON_16 16716015 // FF10EF
#define BUTTON_17 16726215 // FF38C7
#define BUTTON_18 16734885 // FF5AA5

#define BUTTON 16728765 // FF42BD
#define BUTTON 16730805 // FF4AB5
#define BUTTON 16732845 // FF52AD

#define REPEAT 4294967295

int IR_PIN = 11;

byte relayPin[4] = {2,3,4,5};
 
IRrecv irrecv(IR_PIN);
decode_results results;

void setup(){

	Serial.begin(9600);

	pinMode(relayPin[0],OUTPUT);
	pinMode(relayPin[1],OUTPUT);

	irrecv.enableIRIn(); // Starts the receiver

}

long currentTime = 0;
long lastRepeat  = -1;

void loop(){
	currentTime++;

	//Detect end of repeat 
	if (irrecv.decode(&results)) {
		// When signal recieved
		Serial.println(results.value);
		irrecv.resume(); // Receive the next value
		switch(results.value) {
			case BUTTON_1 :
				digitalWrite(relayPin[0],HIGH);
				Serial.println("BOUTON1");
				break;
			case BUTTON_2 :
				digitalWrite(relayPin[0],HIGH);
				digitalWrite(relayPin[1],HIGH);
				Serial.println("BOUTON2");
				break;
			case BUTTON_3 :
				digitalWrite(relayPin[1],HIGH);
				Serial.println("BOUTON3");
				break;
			case REPEAT :
				lastRepeat = currentTime;
				Serial.println("REFRESH");
				break;
			default : 
				digitalWrite(relayPin[0],LOW);
				digitalWrite(relayPin[1],LOW);
		}
	}
	else if ( ( lastRepeat != -1 ) && ( currentTime - lastRepeat >= 10 ) )
	{
		digitalWrite(relayPin[0],LOW);
		digitalWrite(relayPin[1],LOW);
		
		lastRepeat = -1;
		currentTime = 0;
	}
	delay(100);

	//delay(10);
}

