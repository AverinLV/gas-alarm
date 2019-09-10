/*
 * ATTENTION!
 * 
 * This code now available only for Arduino UNO based on Atmel ATmega 328P
 * 
 */

unsigned short sensorPin1 = 1; // First sensor pin
unsigned short sensorPin2 = 2; // Second...
unsigned short sensorPin3 = 3; // Third...

unsigned short gas1 = 0; // Gas sensor data value
unsigned short gas2 = 0; // ...
unsigned short gas3 = 0; // ...

unsigned short piezo = 8; // Number of the Piezo port
unsigned short TLV1, TLV2, TLV3 = 0; // Threshold limit value

const unsigned short calibTime = 120;
const unsigned short validTime = 20;

unsigned short aCalib[3][calibTime]; // Array for containing sensors values for calibTime seconds
unsigned short aValid[3][validTime]; // Array for containg validation sensors values for validTime seconds

unsigned short heatingTime = 60; // Time for heating sensors (seconds)

int getMean(int a[], int aSize)
{
  long mean = 0;
  for (int i = 0; i < aSize; i++)
  {
    mean += a[i];
  }
  return mean / aSize;
}

int getDiff(unsigned a, unsigned b)
{
  if (a > b)
  {
    return a - b;
  }
  else
  {
    return b - a;
  }
}

void playSignal(short duration)
{
  digitalWrite(piezo, HIGH);   
  delay(duration);                       
  digitalWrite(piezo, LOW);
}


void setup() 
{
  Serial.begin(9600); // Initialising the Serial Port
  pinMode(piezo, OUTPUT);
  
  playSignal(100);
}

void loop() 
{
  if (heatingTime > 0) // Sensors need some time to heat before correct usage
  {
    heatingTime--;
    Serial.print("Heating process - ");
    Serial.println(heatingTime);
    delay(1000);
    return;
  }
  static unsigned short calibCounter = 0;
  static unsigned short validCounter = 0;
  gas1 = analogRead(sensorPin1); // Get value from sensor
  gas2 = analogRead(sensorPin2); // ...
  gas3 = analogRead(sensorPin3); // ...

  if (calibCounter < calibTime)
  {
    aCalib[0][calibCounter] = gas1;
    aCalib[1][calibCounter] = gas2;
    aCalib[2][calibCounter] = gas3;
    calibCounter++;
    Serial.print("Calibration process - ");
    Serial.println(calibCounter);
    Serial.println(gas1);
    Serial.println(gas2);
    Serial.println(gas3);
    Serial.println("---------------------------------");
    delay(1000);
    return;
  }
  else if (calibCounter == calibTime)
  {
    if (validCounter < validTime)
    {
      aValid[0][validCounter] = gas1;
      aValid[1][validCounter] = gas2;
      aValid[2][validCounter] = gas3;
      validCounter++;
      Serial.print("Collecting validation data - ");
      Serial.println(validCounter);
      Serial.println(gas1);
      Serial.println(gas2);
      Serial.println(gas3);
      Serial.println("---------------------------------");
      delay(1000);
      return;
    }
    else if (validCounter == validTime)
    {
      if (getDiff(getMean(aCalib[0], calibTime), getMean(aValid[0], validTime)) > 5)
      {
        // Validation failed
         Serial.println("Validation failed");
         Serial.println("---------------------------------");
         calibCounter = 0;
         validCounter = 0;
         playSignal(1000);
         delay(250);
         playSignal(1000);
         delay(250);
         playSignal(1000);
         return;
      }
      else if (getDiff(getMean(aCalib[1], calibTime), getMean(aValid[1], validTime)) > 5)
      {
        // Validation failed
         Serial.println("Validation failed");
         Serial.println("---------------------------------");
         calibCounter = 0;
         validCounter = 0;
         playSignal(1000);
         delay(250);
         playSignal(1000);
         delay(250);
         playSignal(1000);
         return;
      }
      else if (getDiff(getMean(aCalib[2], calibTime), getMean(aValid[2], validTime)) > 5)
      {
        // Validation failed
         Serial.println("Validation failed");
         Serial.println("---------------------------------");
         calibCounter = 0;
         validCounter = 0;
         playSignal(1000);
         delay(250);
         playSignal(1000);
         delay(250);
         playSignal(1000);
         return;
      }
      else
      {
        // Validation OK. Sensor is working now
        Serial.println("Validation OK");
        Serial.println("---------------------------------");
        playSignal(100);
        delay(250);
        playSignal(100);
        calibCounter = calibTime + 1;
        validCounter = validTime + 1;
        TLV1 = getMean(aCalib[0], calibTime);
        TLV2 = getMean(aCalib[1], calibTime);
        TLV3 = getMean(aCalib[2], calibTime);
      }
    }
  }

  if ((gas1 >= TLV1 + 30) or (gas2 >= TLV2 + 30) or (gas3 >= TLV3 + 30)) // ALARM LEVEL 4
  {
    digitalWrite(piezo, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(piezo, LOW);    // turn the LED off by making the voltage LOW
    Serial.print("ALARM LEVEL 4");
  }
  else if ((gas1 >= TLV1 + 25 and gas1 < TLV1 + 30) or (gas2 >= TLV2 + 25 and gas2 < TLV2 + 30) or (gas3 >= TLV3 + 25 and gas3 < TLV3 + 30)) // ALARM LEVEL 3
  {
    digitalWrite(piezo, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(piezo, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);
    Serial.print("ALARM LEVEL 3");
  }
  else if ((gas1 >= TLV1 + 20 and gas1 < TLV1 + 25) or (gas2 >= TLV2 + 20 and gas2 < TLV2 + 25) or (gas3 >= TLV3 + 20 and gas3 < TLV3 + 25)) // ALARM LEVEL 2
  {
    digitalWrite(piezo, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(piezo, LOW);    // turn the LED off by making the voltage LOW
    delay(2000);
    Serial.print("ALARM LEVEL 2");
  }
  else if ((gas1 >= TLV1 + 15 and gas1 < TLV1 + 20) or (gas2 >= TLV2 + 15 and gas2 < TLV2 + 20) or (gas3 >= TLV3 + 15 and gas3 < TLV3 + 20)) // ALARM LEVEL 1
  {
    digitalWrite(piezo, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(piezo, LOW);    // turn the LED off by making the voltage LOW
    delay(3000);
    Serial.print("ALARM LEVEL 1");
  }
  else
  {
    delay(1000);
  }
 
  Serial.print("1 - ");
  Serial.println(gas1); // Writing for serial port
  Serial.print("2 - ");
  Serial.println(gas2); // ...
  Serial.print("3 - ");
  Serial.println(gas3); // ...
  Serial.println(TLV1);
  Serial.println(TLV2);
  Serial.println(TLV3);
  Serial.println("---------------------------------");
 
  //delay(1000); // Read sensor every second
}
