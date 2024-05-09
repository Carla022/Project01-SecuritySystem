#include <LiquidCrystal.h> // LCD Library

LiquidCrystal lcd(10,9,8,7,6,5); // Initializing LCD object with its pin connections
const int motionSensorPin = 12;      // Defining motionSensorPin variable to Arduino pin num
const int buzzerPin = 2;             // Defining Passive Buzzer variable to Arduino pin num
String defaultMessage = "Alarm Activated"; // Default message bottom lcd row
String alternateMessage = "Motion detected! A human is present."; // Human present top lcd row
String scrollingMessage2 = "No Motion detected."; // No human present top lcd row
int messageLength1; // length of message (integer)
int messageLength2; // length of message2 (integer)
int scrollDelay = 400; // Value to control speed of scrolling
int topMessagePosition = 0; // Start position for top row message
unsigned long previousMillis = 0;
unsigned long interval = 100; // Value to control smoothness of scroll
int duration = 4000; // 2 seconds
unsigned long startTime = 0; // Variable to store the start time
int buzzerState = LOW; // Initial state of the buzzer




unsigned long function1StartTime = 0;
unsigned long function2StartTime = 0;
unsigned long function1Interval = 1000; // Function 1 interval in milliseconds
unsigned long function2Interval = 500;  // Fun



void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Initializing the LCD with 16 columns and 2 rows
  lcd.setCursor(0, 0); // setting the cursor on lcd 
  Serial.println("Simple Human Detector Alarm"); //printing to output
  pinMode(motionSensorPin, INPUT); // making sensor the input
  pinMode(buzzerPin, OUTPUT); //making bugger the output

  messageLength2 = scrollingMessage2.length(); 
  messageLength1 = alternateMessage.length();

 lcd.setCursor(0, 1);
  lcd.print(defaultMessage);


  // Initial beep to indicate the system is ready

  tone(buzzerPin, 200, 200);
  delay(400);
  tone(buzzerPin, 600, 400);
  delay(2000);
}

void loop() {
  int motionState = digitalRead(motionSensorPin); //Read pin of sensor

  // Check if it's time to display the scrolling message
  if (motionState == HIGH) {

    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
      // tone(buzzerPin, 200, 200);
      // delay(400);
      // tone(buzzerPin, 600, 400);      
      lcd.setCursor(0, 0);
      lcd.print("                "); // Clearing the top row
      lcd.setCursor(0, 0);

    //calling function 
    warSiren() ;

    Serial.println("Motion detected! A human is present."); //print output
  }
 else {
    // No motion detected, display the default message on the bottom row
    lcd.setCursor(0, 1);
    lcd.print(defaultMessage);
    // Smoothly scroll the top row message from right to left
    smoothScrollTopRowMessage(); //calling other function
  
  }

  delay(300); // 300 delay between sensor readings
}

void smoothScrollTopRowMessage() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Scrolling message on the top row of the LCD from right to left
    lcd.setCursor(0, 0);
    lcd.print(scrollingMessage2.substring(topMessagePosition, topMessagePosition + 16));
    topMessagePosition++;

    // Reseting position if message scrolled completely
    if (topMessagePosition > messageLength2) {
      topMessagePosition = 0;
    }
  }
}

void smoothScrollAlternateMessage() {
  // Smoothly scroll the alternate message on the top row of the LCD from right to left
  for (int i = 0; i < alternateMessage.length() + 16; i++) {
    lcd.setCursor(0, 0);
    int endIndex = min(i + 16, alternateMessage.length());
    lcd.print(alternateMessage.substring(i, endIndex));
    delay(scrollDelay);
  }
}

// Function to generate a war siren-like sound
void warSiren() {
  int frequency = 100; // Starting frequency (adjust as needed)
  int endFrequency = 1000; // Ending frequency (adjust as needed)
  int step = 10; // Frequency step (adjust as needed)
  int duration = 10; // Duration for each step in milliseconds (adjust as needed)
  int direction = 1; // Direction of frequency change (1 for increasing, -1 for decreasing)

   while (true) {
    tone(buzzerPin, frequency);
    delay(duration);
    noTone(buzzerPin);
    
    frequency += step * direction;
    
    // Check if we've reached the end frequency
    if (frequency >= endFrequency || frequency <= 100) {
      direction *= -1; // Reverse the direction
    }
  }
}






