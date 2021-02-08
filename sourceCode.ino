#include <LiquidCrystal.h>
#include <Servo.h>				
int cm=0,inchOut=0,s_distance=0;//initialising distance variables

Servo myservo;//object for servo
int pos = 0;
//method to read data of ultrasonic distance sensors
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//set up function
void setup() {
  lcd.begin(16, 2);
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  myservo.attach(8);
  myservo.write(0);
  pinMode(9, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}
int count=0,flag=0,sanitise=0;
//loop function
void loop() {
  digitalWrite(9, LOW);//green led dimmed
  digitalWrite(13, LOW);//red led dimmed
  cm = 0.01723 * readUltrasonicDistance(7, 7);//distance of a person from entry gate
  s_distance = 0.01723 * readUltrasonicDistance(A5, A5);//distance of hand from sanitiser machine
  inchOut = 0.01723 * readUltrasonicDistance(A1, A2)/2.54;//distance of a person from exit gate
  lcd.setCursor(0,0);
  //default print when no one is near
  if(cm>15 and count<20){
    lcd.print(" ---Welcome!--- ");
    delay(2000);
    lcd.setCursor(0,0);
    lcd.print("No Mask No Entry");
  	flag=0;
    Serial.print("No Person Detected ");
  }
  
  //When there are more than 20 people inside, print "No Space Inside"
  //And do not allow anyone in
  if(count>=20){
    Serial.print("NO SPACE INSIDE");
    lcd.print("No Space Inside ");
  	flag=0;
  }
  
  //The person must sanitise before proceeding any further once he is detected
  if(cm<=15 && count < 20 && sanitise==0){
    	Serial.print("Person Detected |");
  		lcd.setCursor(0,0);
    	lcd.print("Kindly Sanitise   ");
    	//sanitise once the hand is <=10cm from the sanitiser
    	if(s_distance<=10){
    		myservo.write(45);
          	delay(100);
          	myservo.write(90);
          	delay(100);
          	myservo.write(135);
          	delay(100);
          	myservo.write(180);
          	delay(100);
          	myservo.write(0);
          	delay(2000);
          	sanitise=1;
        }
 		Serial.print("Sanitised :");
    	Serial.print(sanitise);
  }
  
  //Measure Temperature once sanitised
  if(cm<=15 && count < 20 && sanitise==1){
    count++;
    if(flag==0){
      	digitalWrite(9, LOW);
  		digitalWrite(13, LOW);
      	lcd.setCursor(0,0);
    	lcd.print("Covid Screening   ");
      	delay(800);
      	lcd.setCursor(0,0);
    	lcd.print("Cooperate Pls  ");
      	delay(800);
      	lcd.setCursor(0,0);
    	lcd.print("Checking Temp.   ");
      	delay(2500);
    }
    flag=1;
    digitalWrite(10, HIGH);//digital pin high only after sanitation
    //temperature is not measured always
    int reading = analogRead(A0);
	float voltage = (reading/ 1024.0) * 5000.0;
	float temp = (voltage) / 10 ;
	temp =temp+ (-50);
    temp=1.8*temp+32;

    //if Temperature High, dont allow entry
    if(temp>99)
    {
      	digitalWrite(13, HIGH);//red led on as temperature high
      	lcd.setCursor(0,0);
    	lcd.print("Your Temp:");
    	lcd.print(temp);
      	lcd.print("F    ");
        count--;
      	delay(2000);
      	lcd.setCursor(0,0);
      	Serial.print("| High Temp!!! :");
      	Serial.print(temp);
      	lcd.print("FEVER Step Aside");
      	
      	//Play alarm to make people around aware and maintain distance
      	for(int i=0;i<10;i++){
      		tone(6, 450, 100);
        	delay(250);
          	tone(6, 650, 100);
        	delay(250);
        }
      	delay(1500);
      	digitalWrite(13, LOW);
      	flag=0;
    }
    
    //if temperature normal, allow entry
    else{
      	digitalWrite(9, HIGH);
      	lcd.setCursor(0,0);
    	lcd.print("Your Temp:");
      	lcd.print(temp);
      	lcd.print("F    ");
      	Serial.print("| Normal Temp :");
      	Serial.print(temp);
      	delay(2000);
      	lcd.setCursor(0,0);
    	lcd.print("You may enter :)");
      	delay(1500);
      	digitalWrite(9, LOW);
      	flag=0;
    }
  }
  delay(2000);//2 second gap after a person has entered (Social distancing)
  digitalWrite(9, LOW);
  digitalWrite(13, LOW);
  //if person approaches exit gate, decrease count of people in
  if(inchOut<=6){
    if(count!=0){
    	count--;
      	delay(2000);
    }
  }
  
  //Display the number of people currently in
  Serial.print("| count in :");
  Serial.println(count);
  sanitise=0;
  lcd.setCursor(0, 1);
  lcd.print("People in: ");
  lcd.print(count);
} 
