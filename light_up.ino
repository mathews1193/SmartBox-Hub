#include <dht11.h> // Library for temp sensor 

#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

#define DHT11PIN 11 // temp sensor pin 11 
#define touchPin 2 // touch sensor pin 2 

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // address of data on lcd 
dht11 DHT11;

float TempF; // temp in f 
int num; // mode select number 
int num2 = 0; // counter for light show 

int ledPin = 13;

int redPin= 10; // red pin 10
int greenPin = 9; // green pin 9
int bluePin = 8; // blue pin 8 

int count = 0; // count for color change 

void setup()
{
  lcd.init(); // Initiate the LCD:
  lcd.backlight();

  Serial.begin(9600); // open serial communication and set to 9600 

  pinMode(redPin, OUTPUT); // red pin output  
  pinMode(greenPin, OUTPUT); // green pin output 
  pinMode(bluePin, OUTPUT); // blue pin output

  lcd.setCursor(3, 0); // Set the cursor on the first column and first row.
  lcd.print("Smart Box");
  
  lcd.setCursor(2, 1); // Set the cursor on the first column and second row.
  lcd.print("Hub Creature");
  lights();
  delay(3000);

  lcd.clear();

  lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  lcd.print("1) Light Show");
  lcd.setCursor(0, 1); // Set the cursor on the first column and second row.
  lcd.print("2) Temp Sensor");

 // go to serial moniter and enter option 
 
  Serial.println("Enter option here: "); //Prompt User for Input
  while(Serial.available()==0) { // Wait for User to Input Data  
  }
  num=Serial.parseInt();  //Read the data the user has input

  lcd.clear();
  lcd.setCursor(2, 0); // Set the cursor on the second column and first row.
  lcd.print("Loading....");
  lights();
  delay(2000);
  
}

void loop()
{
  if (num == 1){
    lcd.clear();
    lcd.print("Light Show"); // option 1 touch sensor light show 
    delay(3000);

    
    lcd.clear();
    int touchValue = digitalRead(touchPin);
    while(touchValue == HIGH){
    count++;
    if (touchValue == HIGH) {
      if (count == 1){
        setColor(255, 0, 0); // Red Color
        lcd.clear();
        lcd.setCursor(5, 0); // Set the cursor on the first column and first row.
        lcd.print("Red");
        delay(1500);
        
      }
      else if (count == 2){
        setColor(0, 255, 0); // Green Color
        lcd.clear();
        lcd.setCursor(5, 0); // Set the cursor on the first column and first row.
        lcd.print("Green");
        delay(1500);
      }
      else if (count == 3){
        setColor(0, 0, 255); // Blue Color
        lcd.clear();
        lcd.setCursor(5, 0); // Set the cursor on the first column and first row.
        lcd.print("Blue");
        delay(1500);
      }
      else if (count == 4){
        setColor(255, 255, 255); // White Color
        lcd.clear();
        lcd.setCursor(5, 0); // Set the cursor on the first column and first row.
        lcd.print("White");
        delay(1500);
      }
      else if (count == 5){
        setColor(170, 0, 255); // Purple Color
        lcd.clear();
        lcd.setCursor(5, 0); // Set the cursor on the first column and first row.
        lcd.print("Purple");
        delay(1500);
      }
      else if (count == 6){
        setColor(255, 255, 0);  // yellow
        lcd.clear();
        lcd.setCursor(5, 0); // Set the cursor on the first column and first row.
        lcd.print("Yellow");
        delay(1500);
      }
      else if (count == 7){
       setColor(0, 255, 255);  // aqua
        lcd.clear();
        lcd.setCursor(5, 0); // Set the cursor on the first column and first row.
        lcd.print("Aqua");
        delay(1500);
      }
      else{
        num2++; 
        
        if(num2 < 3){
          count = 0;
        }
        else{
        lcd.clear();
        lcd.print("Mode Changed"); // mode changed after light show is finished 
        touchValue = LOW;
          num++;
         return; // exit statement 
        }
      }
    } 
   else{
     return; // exit while loop 
    }
   delay(3000);
   }
 }
 else {
  lcd.clear();
  lcd.print("Temp Sensor"); // option 2 temperature sensor 
  delay(3000);
 
  int chk = DHT11.read(DHT11PIN);

  lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  lcd.print("Hum (%): ");
  lcd.print((float)DHT11.humidity, 1);
  
  TempF = ((float)DHT11.temperature*1.8)+32; // convert temp c to f 
  
  lcd.setCursor(0, 1); // Set the cursor on the first column and second row.
  lcd.print("Temp(F): ");
  lcd.print(TempF, 1); // temp in f 
  
  delay(8000);
  lcd.clear();

  if (TempF < 49){
    setColor(0, 0, 255); // Blue Color
    delay(1000);
    lcd.print("Cold Temp"); // cold temp 
  }else if (TempF > 50 || TempF < 89){
    setColor(0, 255, 0); // Green Color
    delay(1000);
    lcd.print("Normal Temp"); // normal temp 
  }else if (TempF > 90){
    setColor(255, 0, 0); // Red Color
    delay(1000);
    lcd.print("Hot Temp");
  }else{
    setColor(255, 255, 255); // White Color
    delay(1000);
    lcd.print("Invalid temp");
  }
  delay(6000);
  }
}
// Function to read RGB light 
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
// Function to blink  variety of lights on RGB
void lights(){
  setColor(255, 0, 0); // Red Color
  delay(1000);
  setColor(0, 255, 0); // Green Color
  delay(1000);
  setColor(0, 0, 255); // Blue Color
  delay(1000);
  setColor(255, 255, 0);  // yellow
  delay(1000);
  setColor(255, 255, 255); // White Color
  delay(1000);
  setColor(0, 255, 255);  // aqua
  delay(1000);
  setColor(170, 0, 255); // Purple Color
  delay(1000);
}
