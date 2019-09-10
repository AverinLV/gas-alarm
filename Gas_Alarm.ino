/*
 * ATTENTION!
 * 
 * This code now available only for Arduino UNO based on Atmel ATmega 328P
 * 
 */

//int sensorPin1 = 1; // First sensor pin
int sensorPin2 = 2; // Second...
int sensorPin3 = 3; // Third...

int gas1 = 0; // Gas sensor data value
int gas2 = 0; // ...
int gas3 = 0; // ...

int piezo = 8; // Number of the Piezo port
int PDK = 350; // Limit value

void setup() 
{
  //Serial.begin(9600); // Инициализируем серийный порт
  pinMode(piezo, OUTPUT);
  
  digitalWrite(piezo, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(250);                       // wait for a second
  digitalWrite(piezo, LOW);    // turn the LED off by making the voltage LOW
  delay(250);
  digitalWrite(piezo, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(250);                       // wait for a second
  digitalWrite(piezo, LOW);    // turn the LED off by making the voltage LOW
  delay(250);
  digitalWrite(piezo, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(250);                       // wait for a second
  digitalWrite(piezo, LOW);    // turn the LED off by making the voltage LOW
  delay(250);
}

void loop() 
{
  gas1 = analogRead(sensorPin1); // Get value from sensor
  gas2 = analogRead(sensorPin2); // ...
  gas3 = analogRead(sensorPin3); // ...

  if (gas1 > PDK or gas2 > PDK or gas3 > PDK) // ALARM LEVEL 4
  {
    digitalWrite(piezo, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(piezo, LOW);    // turn the LED off by making the voltage LOW
    return;
  }
  else if ((gas1 > 290 and gas1 < 320) or (gas2 > 290 and gas2 < 320) or (gas3 > 290 and gas3 < 320)) // ALARM LEVEL 3
  {
    digitalWrite(piezo, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(piezo, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);
    return;
  }
  else if ((gas1 > 260 and gas1 < 290) or (gas2 > 260 and gas2 < 290) or (gas3 > 260 and gas3 < 290)) // ALARM LEVEL 2
  {
    digitalWrite(piezo, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(piezo, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);
    return;
  }
  else if ((gas1 > 230 and gas1 < 260) or (gas2 > 230 and gas2 < 260) or (gas3 > 230 and gas3 < 260)) // ALARM LEVEL 1
  {
    digitalWrite(piezo, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(piezo, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);
    return;
  }
 
  Serial.print("1 - ");
  Serial.println(gas1); // Writing for serial port
  Serial.print("2 - ");
  Serial.println(gas2); // ...
  Serial.print("3 - ");
  Serial.println(gas3); // ...
  Serial.println("---------------------------------");
 
  delay(1000); // make a little pause
}
