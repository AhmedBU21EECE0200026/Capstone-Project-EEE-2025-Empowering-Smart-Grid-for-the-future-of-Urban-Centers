#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BH1750.h>

#define V_SEN_1_PIN A0
#define V_SEN_2_PIN A1
#define V_SEN_3_PIN A2
#define V_SEN_4_PIN A3
#define V_SEN_5_PIN A4
#define V_SEN_6_PIN A5
#define V_SEN_7_PIN A6
#define V_SEN_8_PIN A7

#define C_SEN_1_PIN A8
#define C_SEN_2_PIN A9
#define C_SEN_3_PIN A10
#define C_SEN_4_PIN A11
#define C_SEN_5_PIN A12
#define C_SEN_6_PIN A13
#define C_SEN_7_PIN A14
#define C_SEN_8_PIN A15

#define RELAY1 9
#define RELAY2 10
#define RELAY3 11
#define RELAY4 12
#define RELAY5 22
#define RELAY6 24
#define RELAY7 26
#define RELAY8 28
#define RELAY9 30
#define RELAY10 32
#define RELAY11 34
#define RELAY12 36
#define RELAY13 38
#define RELAY14 40
#define RELAY15 42
#define RELAY16 44
#define RELAY17 46
#define RELAY18 48
#define RELAY19 50
#define RELAY20 52

#define BUZZER1 8
#define BUZZER2 1
#define BUZZER3 2
#define BUZZER4 3
#define BUZZER5 4
#define BUZZER6 5
#define BUZZER7 6
#define BUZZER8 7

#define SET_BUTTON1 23
#define SET_BUTTON2 25
#define SET_BUTTON3 27
#define SET_BUTTON4 29
#define SET_BUTTON5 31
#define SET_BUTTON6 33
#define SET_BUTTON7 35
#define SET_BUTTON8 37

#define RESET_BUTTON1 39
#define RESET_BUTTON2 41
#define RESET_BUTTON3 43
#define RESET_BUTTON4 45
#define RESET_BUTTON5 47
#define RESET_BUTTON6 49
#define RESET_BUTTON7 51
#define RESET_BUTTON8 53

const float VOLTAGE_SCALING = 5.0 / 1023.0 * (20.0 / 5.0);
const float ACS712_SENSITIVITY = 0.1;
const int ACS712_ZERO_OFFSET = 512;

float Grid_Voltage = 0;
float Solar_Voltage = 0;
float Wind_Voltage = 0;
float Bat_Voltage = 0;
float Load1_Voltage = 0;
float Load2_Voltage = 0;
float Load3_Voltage = 0;
float Load4_Voltage = 0;

DHT dht(13, DHT11);

#define V_REF_C 5.0
#define SENSITIVITY_C 0.185
#define V_MID_C 2.5
BH1750 lightMeter(0x23);

bool relay1Active = true;
bool relay1State = false;
bool relay2State = false;
bool relay3State = false;
bool relay4State = false;

bool relay2Active = true;
bool relay5State = false;
bool relay6State = false;

bool relay3Active = true;
bool relay7State = false;
bool relay8State = false;

bool relay4Active = true;
bool relay9State = false;
bool relay10State = false;
bool relay11State = false;
bool relay12State = false;

bool relay5Active = true;
bool relay13State = false;
bool relay14State = false;

bool relay6Active = true;
bool relay15State = false;
bool relay16State = false;

bool relay7Active = true;
bool relay17State = false;
bool relay18State = false;

bool relay8Active = true;
bool relay19State = false;
bool relay20State = false;

float G_current = 0;
float G_voltage = 0;
float Grid_Power = 0;

float S_voltage = 0;
float S_current = 0;
float Solar_Power = 0;

float W_voltage = 0;
float W_current = 0;
float Wind_Power = 0;

float B_voltage = 0;
float B_current = 0;
int Bat_Power = 0;
float Bat_Percentage = 0;

float L1_voltage = 0;
float L1_current = 0;
int Load1_Power = 0;

float L2_voltage = 0;
float L2_current = 0;
int Load2_Power = 0;

float L3_voltage = 0;
float L3_current = 0;
int Load3_Power = 0;

float L4_voltage = 0;
float L4_current = 0;
int Load4_Power = 0;

bool shortCircuit1;
bool overload1;

bool shortCircuit2;
bool overload2;

LiquidCrystal_I2C lcd1(0x27, 20, 4);
LiquidCrystal_I2C lcd2(0x26, 20, 4);
LiquidCrystal_I2C lcd3(0x23, 20, 4);

void setup() {
  Serial.begin(115200);    // Debugging for Mega
  Serial1.begin(115200);     // Serial1 for ESP32 communication
  Wire.begin();
  lightMeter.begin();
  dht.begin();

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(RELAY5, OUTPUT);
  pinMode(RELAY6, OUTPUT);
  pinMode(RELAY7, OUTPUT);
  pinMode(RELAY8, OUTPUT);
  pinMode(RELAY9, OUTPUT);
  pinMode(RELAY10, OUTPUT);
  pinMode(RELAY11, OUTPUT);
  pinMode(RELAY12, OUTPUT);
  pinMode(RELAY13, OUTPUT);
  pinMode(RELAY14, OUTPUT);
  pinMode(RELAY15, OUTPUT);
  pinMode(RELAY16, OUTPUT);
  pinMode(RELAY17, OUTPUT);
  pinMode(RELAY18, OUTPUT);
  pinMode(RELAY19, OUTPUT);
  pinMode(RELAY20, OUTPUT);

  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);
  pinMode(BUZZER3, OUTPUT);
  pinMode(BUZZER4, OUTPUT);
  pinMode(BUZZER5, OUTPUT);
  pinMode(BUZZER6, OUTPUT);
  pinMode(BUZZER7, OUTPUT);
  pinMode(BUZZER8, OUTPUT);

  pinMode(SET_BUTTON1, INPUT_PULLUP);
  pinMode(SET_BUTTON2, INPUT_PULLUP);
  pinMode(SET_BUTTON3, INPUT_PULLUP);
  pinMode(SET_BUTTON4, INPUT_PULLUP);
  pinMode(SET_BUTTON5, INPUT_PULLUP);
  pinMode(SET_BUTTON6, INPUT_PULLUP);
  pinMode(SET_BUTTON7, INPUT_PULLUP);
  pinMode(SET_BUTTON8, INPUT_PULLUP);

  pinMode(RESET_BUTTON1, INPUT_PULLUP);
  pinMode(RESET_BUTTON2, INPUT_PULLUP);
  pinMode(RESET_BUTTON3, INPUT_PULLUP);
  pinMode(RESET_BUTTON4, INPUT_PULLUP);
  pinMode(RESET_BUTTON5, INPUT_PULLUP);
  pinMode(RESET_BUTTON6, INPUT_PULLUP);
  pinMode(RESET_BUTTON7, INPUT_PULLUP);
  pinMode(RESET_BUTTON8, INPUT_PULLUP);

  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, LOW);
  digitalWrite(RELAY3, LOW);
  digitalWrite(RELAY4, LOW);
  digitalWrite(RELAY5, LOW);
  digitalWrite(RELAY6, LOW);
  digitalWrite(RELAY7, LOW);
  digitalWrite(RELAY8, LOW);
  digitalWrite(RELAY9, LOW);
  digitalWrite(RELAY10, LOW);
  digitalWrite(RELAY11, LOW);
  digitalWrite(RELAY12, LOW);
  digitalWrite(RELAY13, LOW);
  digitalWrite(RELAY14, LOW);
  digitalWrite(RELAY15, LOW);
  digitalWrite(RELAY16, LOW);
  digitalWrite(RELAY17, LOW);
  digitalWrite(RELAY18, LOW);
  digitalWrite(RELAY19, LOW);
  digitalWrite(RELAY20, LOW);

  digitalWrite(BUZZER1, LOW);
  digitalWrite(BUZZER2, LOW);
  digitalWrite(BUZZER3, LOW);
  digitalWrite(BUZZER4, LOW);
  digitalWrite(BUZZER5, LOW);
  digitalWrite(BUZZER6, LOW);
  digitalWrite(BUZZER7, LOW);
  digitalWrite(BUZZER8, LOW);

  lcd1.begin(20,4);
  lcd2.begin(20,4);
  lcd3.begin(20,4);
  lcd1.backlight();
  lcd2.backlight();
  lcd3.noBacklight();
  lcd1.clear();
  lcd2.clear();
  lcd3.clear();
  // updateLCD();
  Serial.println("Mega is ready");
}

void checkButtons_Grid() {
  bool setPressed1 = !digitalRead(SET_BUTTON1);
  bool resetPressed1 = !digitalRead(RESET_BUTTON1);
  if (setPressed1 && resetPressed1) {
    analogWrite(BUZZER1, 300);
    delay(50);
    analogWrite(BUZZER1, 0);
    relay1State = false;
    relay2State = false;
    relay3State = false;
    relay4State = false;
    relay1Active = !relay1Active;
    if (relay1Active) {
      relay1State = true;
      relay2State = true;
    } else {
      relay3State = true;
      relay4State = true;
    }
    updateRelays();
    // updateLCD();
    sendStatusToESP();
    while (!digitalRead(SET_BUTTON1) || !digitalRead(RESET_BUTTON1)) 
    delay(5);
  } else if (setPressed1) {
    analogWrite(BUZZER1, 600);
    delay(50);
    analogWrite(BUZZER1, 0);
    if (relay1Active)
    {
    relay1State = true;
    relay2State = true;
    }
    else
    {
    relay3State = true;
    relay4State = true;
    }
    updateRelays();
    // updateLCD();
    sendStatusToESP();
  } else if (resetPressed1) {
    analogWrite(BUZZER1, 300);
    delay(50);
    analogWrite(BUZZER1, 0);
    if (relay1Active)
    { 
    relay1State = false;
    relay2State = false;
    }
    else
    {
    relay3State = false;
    relay4State = false;
    }
    updateRelays();
    // updateLCD();
    sendStatusToESP();
  }
}

void checkButtons_Solar() {
  bool setPressed2 = !digitalRead(SET_BUTTON2);
  bool resetPressed2 = !digitalRead(RESET_BUTTON2);
  if (setPressed2 && resetPressed2) {
    analogWrite(BUZZER2, 300);
    delay(50);
    analogWrite(BUZZER2, 0);
    relay5State = false;
    relay6State = false;
    /*relay2Active = !relay2Active;
    if (relay2Active) {
      relay5State = true;
    } else {
      relay6State = true;
    }*/
    updateRelays();
    // updateLCD();
    sendStatusToESP();
    while (!digitalRead(SET_BUTTON2) || !digitalRead(RESET_BUTTON2)) 
    delay(5);
  } else if (setPressed2) {
    analogWrite(BUZZER2, 600);
    delay(50);
    analogWrite(BUZZER2, 0);
    //if (relay2Active) 
    relay5State = true;
    //else 
    relay6State = true;
    updateRelays();
    // updateLCD();
    sendStatusToESP();
  } else if (resetPressed2) {
    analogWrite(BUZZER2, 300);
    delay(50);
    analogWrite(BUZZER2, 0);
    //if (relay2Active) 
    relay5State = false;
    //else 
    relay6State = false;
    updateRelays();
    // updateLCD();
    sendStatusToESP();
  }
}

void checkButtons_Wind() {
  bool setPressed3 = !digitalRead(SET_BUTTON3);
  bool resetPressed3 = !digitalRead(RESET_BUTTON3);
  if (setPressed3 && resetPressed3) {
    analogWrite(BUZZER3, 300);
    delay(50);
    analogWrite(BUZZER3, 0);
    relay7State = false;
    relay8State = false;
    /*relay3Active = !relay3Active;
    if (relay3Active) {
      relay7State = true;
    } else {
      relay8State = true;
    }*/
    updateRelays();
    // updateLCD();
    sendStatusToESP();
    while (!digitalRead(SET_BUTTON3) || !digitalRead(RESET_BUTTON3)) 
    delay(5);
  } else if (setPressed3) {
    analogWrite(BUZZER3, 600);
    delay(50);
    analogWrite(BUZZER3, 0);
    //if (relay3Active) 
    relay7State = true;
    //else 
    relay8State = true;
    updateRelays();
    // updateLCD();
    sendStatusToESP();
  } else if (resetPressed3) {
    analogWrite(BUZZER3, 300);
    delay(50);
    analogWrite(BUZZER3, 0);
    //if (relay3Active) 
    relay7State = false;
    //else 
    relay8State = false;
    updateRelays();
    // updateLCD();
    sendStatusToESP();
  }
}

void checkButtons_Bat() {
  bool setPressed4 = !digitalRead(SET_BUTTON4);
  bool resetPressed4 = !digitalRead(RESET_BUTTON4);
  if (setPressed4 && resetPressed4) {
    analogWrite(BUZZER4, 300);
    delay(50);
    analogWrite(BUZZER4, 0);
    relay9State = false;
    relay10State = false;
    relay11State = false;
    relay12State = false;
    relay4Active = !relay4Active;
    if (relay4Active) {
      relay9State = true;
      relay10State = true;
    } else {
      relay11State = true;
      relay12State = true;
    }
    updateRelays();
    // updateLCD();
    sendStatusToESP();
    while (!digitalRead(SET_BUTTON4) || !digitalRead(RESET_BUTTON4)) 
    delay(5);
  } else if (setPressed4) {
    analogWrite(BUZZER4, 600);
    delay(50);
    analogWrite(BUZZER4, 0);
    if (relay4Active)
    {
    relay9State = true;
    relay10State = true;
    }
    else{
    relay11State = true;
    relay12State = true;
    }
    updateRelays();
    // updateLCD();
    sendStatusToESP();
  } else if (resetPressed4) {
    analogWrite(BUZZER4, 300);
    delay(50);
    analogWrite(BUZZER4, 0);
    if (relay4Active){
    relay9State = false;
    relay10State = false;
    }
    else{
    relay11State = false;
    relay12State = false;
    }
    updateRelays();
    // updateLCD();
    sendStatusToESP();
  }
}

void checkButtons_Load1() {
  bool setPressed5 = !digitalRead(SET_BUTTON5);
  bool resetPressed5 = !digitalRead(RESET_BUTTON5);
  if (setPressed5 && resetPressed5) {
    analogWrite(BUZZER5, 300);
    delay(50);
    analogWrite(BUZZER5, 0);
    relay13State = false;
    relay14State = false;
    /*relay5Active = !relay5Active;
    if (relay5Active) {
      relay13State = true;
    } else {
      relay14State = true;
    }*/
    updateRelays();
    // updateLCD();
    sendStatusToESP();
    while (!digitalRead(SET_BUTTON5) || !digitalRead(RESET_BUTTON5)) 
    delay(5);
  } else if (setPressed5) {
    analogWrite(BUZZER5, 600);
    delay(50);
    analogWrite(BUZZER5, 0);
    //if (relay5Active) 
    relay13State = true;
    //else 
    relay14State = true;
    updateRelays();
    // updateLCD();
    sendStatusToESP();
  } else if (resetPressed5) {
    analogWrite(BUZZER5, 300);
    delay(50);
    analogWrite(BUZZER5, 0);
    //if (relay5Active) 
    relay13State = false;
    //else 
    relay14State = false;
    updateRelays();
    // updateLCD();
    sendStatusToESP();
  }
}

void checkButtons_Load2() {
  bool setPressed6 = !digitalRead(SET_BUTTON6);
  bool resetPressed6 = !digitalRead(RESET_BUTTON6);
  if (setPressed6 && resetPressed6) {
    analogWrite(BUZZER6, 300);
    delay(50);
    analogWrite(BUZZER6, 0);
    relay15State = false;
    relay16State = false;
    /*relay6Active = !relay6Active;
    if (relay6Active) {
      relay15State = true;
    } else {
      relay16State = true;
    }*/
    updateRelays();
    // updateLCD();
    sendStatusToESP();
    while (!digitalRead(SET_BUTTON6) || !digitalRead(RESET_BUTTON6)) 
    delay(5);
  } else if (setPressed6) {
    analogWrite(BUZZER6, 600);
    delay(50);
    analogWrite(BUZZER6, 0);
    //if (relay6Active) 
    relay15State = true;
    //else 
    relay16State = true;
    updateRelays();
    // updateLCD();
    sendStatusToESP();
  } else if (resetPressed6) {
    analogWrite(BUZZER6, 300);
    delay(50);
    analogWrite(BUZZER6, 0);
    //if (relay6Active) 
    relay15State = false;
    //else 
    relay16State = false;
    updateRelays();
    // updateLCD();
    sendStatusToESP();
  }
}

void checkButtons_Load3() {
  bool setPressed7 = !digitalRead(SET_BUTTON7);
  bool resetPressed7 = !digitalRead(RESET_BUTTON7);
  if (setPressed7 && resetPressed7) {
    analogWrite(BUZZER7, 300);
    delay(50);
    analogWrite(BUZZER7, 0);
    relay17State = false;
    relay18State = false;
    /*relay7Active = !relay7Active;
    if (relay7Active) {
      relay17State = true;
    } else {
      relay18State = true;
    }*/
    updateRelays();
    // updateLCD();
    sendStatusToESP();
    while (!digitalRead(SET_BUTTON7) || !digitalRead(RESET_BUTTON7)) 
    delay(5);
  } else if (setPressed7) {
    analogWrite(BUZZER7, 600);
    delay(50);
    analogWrite(BUZZER7, 0);
    //if (relay7Active) 
    relay17State = true;
    //else 
    relay18State = true;
    updateRelays();
    // updateLCD();
    sendStatusToESP();
  } else if (resetPressed7) {
    analogWrite(BUZZER7, 300);
    delay(50);
    analogWrite(BUZZER7, 0);
    //if (relay7Active) 
    relay17State = false;
    //else 
    relay18State = false;
    updateRelays();
    // updateLCD();
    sendStatusToESP();
  }
}

void checkButtons_Load4() {
  bool setPressed8 = !digitalRead(SET_BUTTON8);
  bool resetPressed8 = !digitalRead(RESET_BUTTON8);
  if (setPressed8 && resetPressed8) {
    analogWrite(BUZZER8, 300);
    delay(50);
    analogWrite(BUZZER8, 0);
    relay19State = false;
    relay20State = false;
    /*relay8Active = !relay8Active;
    if (relay8Active) {
      relay19State = true;
    } else {
      relay20State = true;
    }*/
    updateRelays();
    // updateLCD();
    sendStatusToESP();
    while (!digitalRead(SET_BUTTON8) || !digitalRead(RESET_BUTTON8)) 
    delay(5);
  } else if (setPressed8) {
    analogWrite(BUZZER8, 600);
    delay(50);
    analogWrite(BUZZER8, 0);
    //if (relay8Active) 
    relay19State = true;
    //else 
    relay20State = true;
    updateRelays();
    // updateLCD();
    sendStatusToESP();
  } else if (resetPressed8) {
    analogWrite(BUZZER8, 300);
    delay(50);
    analogWrite(BUZZER8, 0);
    //if (relay8Active) 
    relay19State = false;
    //else 
    relay20State = false;
    updateRelays();
    // updateLCD();
    sendStatusToESP();
  }
}

void Sen_Grid(float voltageThreshold, float currentThreshold, float voltageMin) {
    G_voltage = analogRead(V_SEN_1_PIN) * VOLTAGE_SCALING;
    G_current = (analogRead(C_SEN_1_PIN) - ACS712_ZERO_OFFSET) * (5.0 / 1023.0) / ACS712_SENSITIVITY;
    Grid_Power = G_voltage * G_current;
    lcd1.setCursor(0, 0);
    lcd1.print("Grid Power: ");
    lcd1.print(Grid_Power);
    Serial.println("Main Grid\n");

    Serial.print("Voltage:  "); 
    Serial.print(G_voltage); 
    Serial.println(" V");

    Serial.print("Current:  "); 
    Serial.print(G_current); 
    Serial.println(" A");

    Serial.print("Power:    "); 
    Serial.print(Grid_Power); 
    Serial.println(" W");

    if(relay1Active)
    {
      Serial.println("Sending to Grid");
    }
    else {
      Serial.println("Receving from Grid");
    }

    Serial.println();

    bool shortCircuit = (G_voltage < Grid_Voltage * 0.6) && (G_current > currentThreshold * 1.5);
    bool overload = (G_voltage >= voltageMin && G_voltage <= voltageThreshold) && (G_current > currentThreshold);
    bool limitExceeded = (G_voltage > voltageThreshold || G_current > currentThreshold || G_voltage > voltageMin);

    if (shortCircuit) {
        Serial.println("SC_Grid");
        lcd3.begin(20,4);
        lcd3.backlight();
        lcd3.print("Short Circuit: Grid");
    } else if (overload) {
        Serial.println("OL_Gird");
        lcd3.print("OverLoad: Grid");
    } //else if (limitExceeded) {
        //Serial.println("LE_Grid");
    //}

    if (shortCircuit || overload || limitExceeded) {
        relay1State = false;
        relay2State = false;
        relay3State = false;
        relay4State = false;
    } 
    Grid_Voltage = G_voltage;  // Update previous voltage for next cycle
}

void Sen_Solar(float voltageThreshold, float currentThreshold, float voltageMin) {
    S_voltage = analogRead(V_SEN_2_PIN) * VOLTAGE_SCALING;
    S_current = (analogRead(C_SEN_2_PIN) - ACS712_ZERO_OFFSET) * (5.0 / 1023.0) / ACS712_SENSITIVITY;
    Solar_Power = S_voltage * S_current;
    lcd1.setCursor(0, 1);
    lcd1.print("Solar Power: ");
    lcd1.print(Solar_Power);
    Serial.println("Main Solar\n");

    Serial.print("Voltage:  "); 
    Serial.print(S_voltage); 
    Serial.println(" V");

    Serial.print("Current:  "); 
    Serial.print(S_current); 
    Serial.println(" A");

    Serial.print("Power:    "); 
    Serial.print(Solar_Power); 
    Serial.println(" W");

    Serial.println();

    bool shortCircuit = (S_voltage < Solar_Voltage * 0.6) && (S_current > currentThreshold * 1.5);
    bool overload = (S_voltage >= voltageMin && S_voltage <= voltageThreshold) && (S_current > currentThreshold);
    bool limitExceeded = (S_voltage > voltageThreshold || S_current > currentThreshold || S_voltage > voltageMin);

    if (shortCircuit) {
        Serial.println("SC_Solar");
        lcd3.print("Short Circuit: Solar");
    } else if (overload) {
        Serial.println("OL_Solar");
        lcd3.print("OverLoad: Solar");
    } else if (limitExceeded) {
        //Serial.println("LE_Solar");
    }

    if (shortCircuit || overload || limitExceeded) {
      //Serial.println("Trip Worked");
      relay5State = false;
      relay6State = false;
    }
    Solar_Voltage = S_voltage;  // Update previous voltage for next cycle
}

void Sen_Wind(float voltageThreshold, float currentThreshold, float voltageMin) {
    W_voltage = analogRead(V_SEN_3_PIN) * VOLTAGE_SCALING;
    W_current = (analogRead(C_SEN_3_PIN) - ACS712_ZERO_OFFSET) * (5.0 / 1023.0) / ACS712_SENSITIVITY;
    Wind_Power = W_voltage * W_current;
    lcd2.setCursor(0, 0);
    lcd2.print("Wind Power: ");
    lcd2.print(Wind_Power);
    Serial.println("Wind Turbine\n");

    Serial.print("Voltage:  "); 
    Serial.print(W_voltage); 
    Serial.println(" V");

    Serial.print("Current:  "); 
    Serial.print(W_current); 
    Serial.println(" A");

    Serial.print("Power:    "); 
    Serial.print(Wind_Power); 
    Serial.println(" W");

    Serial.println();

    bool shortCircuit = (W_voltage < Wind_Voltage * 0.6) && (W_current > currentThreshold * 1.5);
    bool overload = (W_voltage >= voltageMin && W_voltage <= voltageThreshold) || (W_current > currentThreshold);
    bool limitExceeded = (W_voltage > voltageThreshold || W_current > currentThreshold || W_voltage > voltageMin);

    if (shortCircuit) {
        Serial.println("SC_Wind");
        lcd3.print("Short Circuit: Wind");
    } else if (overload) {
        Serial.println("OL_Wind");
        lcd3.print("OverLoad: Wind");
    } else if (limitExceeded) {
        Serial.println("LE_Wind");
    }

    if (shortCircuit || overload || limitExceeded) {
        relay7State = false;
        relay8State = false;
    }
    Wind_Voltage = W_voltage;  // Update previous voltage for next cycle
}

void Sen_Bat(float voltageThreshold, float currentThreshold, float voltageMin) {
    B_voltage = (analogRead(V_SEN_4_PIN) * VOLTAGE_SCALING) + 2.9;
    B_current = (analogRead(C_SEN_4_PIN) - ACS712_ZERO_OFFSET) * (5.0 / 1023.0) / ACS712_SENSITIVITY;
    //Serial.println(B_voltage);
    //Serial.println(B_current);
    Bat_Percentage = 0;
    if (B_voltage <= 10.0) Bat_Percentage = 0;
    else if (B_voltage < 12.0) Bat_Percentage = map(B_voltage * 10, 100, 120, 0, 10); // Mapping between 10V (0%) and 12V (10%)
    else if (B_voltage < 12.8) Bat_Percentage = 10;
    else if (B_voltage < 12.9) Bat_Percentage = 20;
    else if (B_voltage < 13.0) Bat_Percentage = 30;
    else if (B_voltage < 13.1) Bat_Percentage = 40;
    else if (B_voltage < 13.2) Bat_Percentage = 50;
    else if (B_voltage < 13.3) Bat_Percentage = 60;
    else if (B_voltage < 13.4) Bat_Percentage = 70;
    else if (B_voltage < 13.5) Bat_Percentage = 80;
    else if (B_voltage < 13.6) Bat_Percentage = 90;
    else Bat_Percentage = 100;
    Bat_Power = B_voltage * B_current;
    lcd2.setCursor(0, 1);
    lcd2.print("Bat Power: ");
    lcd2.print(Bat_Power);
    lcd2.setCursor(0, 2);
    lcd2.print("Bat Percentage: ");
    lcd2.print(Bat_Percentage);
    Serial.println("Battery\n");

    Serial.print("Voltage:  "); 
    Serial.print(B_voltage); 
    Serial.println(" V");

    Serial.print("Current:  "); 
    Serial.print(B_current); 
    Serial.println(" A");

    Serial.print("Power:    "); 
    Serial.print(Bat_Power); 
    Serial.println(" W");

    Serial.print("Battery Percentage: "); 
    Serial.print(Bat_Percentage); 
    Serial.println(" %");

    if(relay4Active)
    {
      Serial.println("Battery Charging");
    }
    else {
    Serial.println("Battery Discharging");
    }

    Serial.println();

    bool limitExceeded5 = LOW;
    bool overload5 = LOW;
    bool shortCircuit5 = LOW;
    shortCircuit5 = (B_voltage < voltageMin) && (B_current > currentThreshold);
    overload5 = B_current > currentThreshold;
    limitExceeded5 = (B_voltage > voltageThreshold || B_current > currentThreshold);

    if (shortCircuit5) {
        Serial.println("SC_Bat");
        lcd3.print("Short Circuit: Bat");
    } else if (overload5) {
        Serial.println("OL_Bat");
        lcd3.print("OverLoad: Bat");
    } else if (limitExceeded5) {
        Serial.println("LE_Bat");
    }

    if (shortCircuit5 || overload5 || limitExceeded5) {
        relay9State = false;
        relay10State = false;
        relay11State = false;
        relay12State = false;
        updateRelays();
    }
    else {
      limitExceeded5 = LOW;
      overload5 = LOW;
      shortCircuit5 = LOW;
    }
    Bat_Voltage = B_voltage;  // Update previous voltage for next cycle
}

void Sen_Load1(float voltageThreshold, float currentThreshold, float voltageMin) { // On grod load
    L1_voltage = analogRead(V_SEN_5_PIN) * VOLTAGE_SCALING;
    L1_current = ((analogRead(C_SEN_5_PIN) - ACS712_ZERO_OFFSET) * (5.0 / 1023.0) / ACS712_SENSITIVITY) - 1.1;
    Load1_Power = L1_voltage * L1_current;
    lcd2.setCursor(0, 3);
    lcd2.print("OnGridLoad_P: ");
    lcd2.print(Load1_Power);
    Serial.println("On Grid Load\n");

    Serial.print("Voltage:  "); 
    Serial.print(L1_voltage); 
    Serial.println(" V");

    Serial.print("Current:  "); 
    Serial.print(L1_current); 
    Serial.println(" A");

    Serial.print("Power:    "); 
    Serial.print(Load1_Power); 
    Serial.println(" W");

    Serial.println();

    bool limitExceeded4 = LOW;
    bool overload4 = LOW;
    bool shortCircuit4 = LOW;
    shortCircuit4 = (L1_voltage < voltageMin) && (L1_current > currentThreshold);
    overload4 = L1_current > currentThreshold;
    limitExceeded4 = (L1_voltage > voltageThreshold || L1_current > currentThreshold);

    if (shortCircuit4) {
        Serial.println("SC_Load1");
        lcd3.setCursor(0, 2);
        lcd3.print("Short Circuit: Load1");
    } else if (overload4) {
        Serial.println("OL_Load1");
        lcd3.setCursor(0, 3);
        lcd3.print("OverLoad: Load1");
    } else if (limitExceeded4) {
        Serial.println("LE_Load1");
    }

    if (shortCircuit4 || overload4 || limitExceeded4) {
        relay13State = false;
        relay14State = false;
        updateRelays();
    }
    else {
      limitExceeded4 = LOW;
      overload4 = LOW;
      shortCircuit4 = LOW;
    }
    Load1_Voltage = L1_voltage;  // Update previous voltage for next cycle
    return Load1_Power;
}

void Sen_Load2(float voltageThreshold, float currentThreshold, float voltageMin) { //Over Load
    L2_voltage = analogRead(V_SEN_6_PIN) * VOLTAGE_SCALING;
    L2_current = (analogRead(C_SEN_6_PIN) - ACS712_ZERO_OFFSET) * (5.0 / 1023.0) / ACS712_SENSITIVITY;
    Load2_Power = L2_voltage * L2_current;
    Serial.println("Over Load\n");

    Serial.print("Voltage:  "); 
    Serial.print(L2_voltage); 
    Serial.println(" V");

    Serial.print("Current:  "); 
    Serial.print(L2_current); 
    Serial.println(" A");

    Serial.print("Power:    "); 
    Serial.print(Load2_Power); 
    Serial.println(" W");

    Serial.println();

    bool limitExceeded = LOW;
    overload1 = LOW;
    shortCircuit1 = LOW;
    shortCircuit1 = (L2_voltage < voltageMin) && (L2_current > currentThreshold);
    overload1 = L2_current > currentThreshold;
    limitExceeded = (L2_voltage > voltageThreshold && L2_current > currentThreshold);

    if (shortCircuit1) {
        Serial1.println("ShortCircuit1: ON");
        lcd3.setCursor(0, 2);
        lcd3.print("Short Circuit: Load2");
    } else if (overload1) {
        Serial1.println("OverLoad1: ON");
        lcd3.setCursor(0, 3);
        lcd3.print("OverLoad: Load2");
        Serial.println("Over Load Load2");
    } else if (limitExceeded) {
        Serial.println("LE_Load2");
    }

    if (shortCircuit1 || overload1 || limitExceeded) {
      relay15State = false;
      relay16State = false;
      updateRelays();
      analogWrite(BUZZER6, 600);
      delay(1500);
      analogWrite(BUZZER6, 0);
    }
    else {
      limitExceeded = LOW;
      overload1 = LOW;
      shortCircuit1 = LOW;
    }
    Load2_Voltage = L2_voltage;  // Update previous voltage for next cycle
    return Load2_Power,relay15State,relay16State;
}

void Sen_Load3(float voltageThreshold, float currentThreshold, float voltageMin) { //Fault or short circuit
    L3_voltage = analogRead(V_SEN_7_PIN) * VOLTAGE_SCALING;
    L3_current = (analogRead(C_SEN_7_PIN) - ACS712_ZERO_OFFSET) * (5.0 / 1023.0) / ACS712_SENSITIVITY;
    Load3_Power = L3_voltage * L3_current;
    Serial.println("Fault Load\n");

    Serial.print("Voltage:  "); 
    Serial.print(L3_voltage); 
    Serial.println(" V");

    Serial.print("Current:  "); 
    Serial.print(L3_current); 
    Serial.println(" A");

    Serial.print("Power:    "); 
    Serial.print(Load3_Power); 
    Serial.println(" W");

    Serial.println();

    bool limitExceeded = LOW;
    shortCircuit2 = LOW;
    overload2 = LOW;
    shortCircuit2 = (L3_voltage < voltageMin) && (L3_current > currentThreshold);
    overload2 = L3_current > currentThreshold;
    limitExceeded = (L3_voltage > voltageThreshold && L3_current > currentThreshold);

    if (shortCircuit2) {
        Serial1.println("ShortCircuit2: ON");
        shortCircuit2 = false;
        lcd3.setCursor(0, 2);
        lcd3.print("Short Circuit: Load3");
        Serial.println("Short Circuit Load3");
    } else if (overload2) {
        Serial1.println("Overload2: ON");
        overload2 = false;
        lcd3.setCursor(0, 3);
        lcd3.print("OverLoad: Load3");
        Serial.println("Short Circuit Load3");
    } else if (limitExceeded) {
        Serial.println("LE_Load3");
    }

    if (shortCircuit2 || overload2 || limitExceeded) {
      relay17State = false;
      relay18State = false;
      updateRelays();
      analogWrite(BUZZER7, 600);
      delay(1500);
      analogWrite(BUZZER7, 0);
    }
    else {
      limitExceeded = LOW;
      overload2 = LOW;
      shortCircuit2 = LOW;
    }
    Load3_Voltage = L3_voltage;  // Update previous voltage for next cycle
    return Load3_Power;
}

void Sen_Load4(float voltageThreshold, float currentThreshold, float voltageMin) { // Industrial Load
    L4_voltage = analogRead(V_SEN_8_PIN) * VOLTAGE_SCALING;
    L4_current = (analogRead(C_SEN_8_PIN) - ACS712_ZERO_OFFSET) * (5.0 / 1023.0) / ACS712_SENSITIVITY;
    Load4_Power = L4_voltage * L4_current;
    Serial.println("Industrial Load\n");

    Serial.print("Voltage:  "); 
    Serial.print(L4_voltage); 
    Serial.println(" V");

    Serial.print("Current:  "); 
    Serial.print(L4_current); 
    Serial.println(" A");

    Serial.print("Power:    "); 
    Serial.print(Load4_Power); 
    Serial.println(" W");

    Serial.println();

    bool limitExceeded = LOW;
    bool overload = LOW;
    bool shortCircuit = LOW;
    shortCircuit = (L4_voltage < voltageMin) && (L4_current > currentThreshold);
    overload = L4_current > currentThreshold;
    limitExceeded = (L4_voltage > voltageThreshold && L4_current > currentThreshold);

    if (shortCircuit) {
        Serial.println("SC_Load4");
        lcd3.setCursor(0, 2);
        lcd3.print("Short Circuit: Load4");
    } else if (overload) {
        Serial.println("OL_Load4");
        lcd3.setCursor(0, 3);
        lcd3.print("OverLoad: Load4");
    } else if (limitExceeded) {
        Serial.println("LE_Load4");
    }

    if (limitExceeded || overload || shortCircuit) {
        relay19State = false;
        relay20State = false;
        updateRelays();
    }
    else {
      limitExceeded = LOW;
      overload = LOW;
      shortCircuit = LOW;
    }
    Load4_Voltage = L4_voltage;  // Update previous voltage for next cycle
    return Load4_Power;
}

void sendStatusToESP() {
  Serial1.println(relay1State ? "Relay1: ON" : "Relay1: OFF");
  Serial1.println(relay2State ? "Relay2: ON" : "Relay2: OFF");
  Serial1.println(relay3State ? "Relay3: ON" : "Relay3: OFF");
  Serial1.println(relay4State ? "Relay4: ON" : "Relay4: OFF");
  Serial1.println(relay5State ? "Relay5: ON" : "Relay5: OFF");
  Serial1.println(relay6State ? "Relay6: ON" : "Relay6: OFF");
  Serial1.println(relay7State ? "Relay7: ON" : "Relay7: OFF");
  Serial1.println(relay8State ? "Relay8: ON" : "Relay8: OFF");
  Serial1.println(relay9State ? "Relay9: ON" : "Relay9: OFF");
  Serial1.println(relay10State ? "Relay10: ON" : "Relay10: OFF");
  Serial1.println(relay11State ? "Relay11: ON" : "Relay11: OFF");
  Serial1.println(relay12State ? "Relay12: ON" : "Relay12: OFF");
  Serial1.println(relay13State ? "Relay13: ON" : "Relay13: OFF");
  Serial1.println(relay14State ? "Relay14: ON" : "Relay14: OFF");
  Serial1.println(relay15State ? "Relay15: ON" : "Relay15: OFF");
  Serial1.println(relay16State ? "Relay16: ON" : "Relay16: OFF");
  Serial1.println(relay17State ? "Relay17: ON" : "Relay17: OFF");
  Serial1.println(relay18State ? "Relay18: ON" : "Relay18: OFF");
  Serial1.println(relay19State ? "Relay19: ON" : "Relay19: OFF");
  Serial1.println(relay20State ? "Relay20: ON" : "Relay20: OFF");
  Serial1.print("V_SEN4: "); Serial1.println(readVoltage(V_SEN_4_PIN)); // Battery Voltage
  Serial1.print("C_SEN4: "); Serial1.println(readCurrent(C_SEN_4_PIN)); // Battery Current
  Serial1.print("Battery_Power: "); Serial1.println(Bat_Power);
  Serial1.print("Battery Percentage: "); Serial1.println(Bat_Percentage);
  Serial1.print("V_SEN6: "); Serial1.println(readVoltage(V_SEN_6_PIN)); // Commercial Voltage(OL)
  Serial1.print("C_SEN6: "); Serial1.println(readCurrent(C_SEN_6_PIN)); // Commercial Current(OL)
  Serial1.print("Commercial_Power: "); Serial1.println(Load2_Power);
  Serial1.print("V_SEN7: "); Serial1.println(readVoltage(V_SEN_7_PIN)); // Domestic Voltage(SC)
  Serial1.print("C_SEN7: "); Serial1.println(readCurrent(C_SEN_7_PIN)); // Domestic Current(SC)
  Serial1.print("Domestic_Power: "); Serial1.println(Load3_Power);
  Serial1.print("V_SEN8: "); Serial1.println(readVoltage(V_SEN_8_PIN)); // Industrial Voltage
  Serial1.print("C_SEN8: "); Serial1.println(readCurrent(C_SEN_8_PIN)); // Industrial Current
  Serial1.print("Industrial_Power: "); Serial1.println(Load4_Power);
  Serial1.print("Temperature: "); Serial1.println(dht.readTemperature());
  //Serial1.print("Humidity: "); Serial1.println(dht.readHumidity());
  lightMeter.begin();
  Serial1.print("Light: "); Serial1.println(lightMeter.readLightLevel());
  Serial.println("Sent status to ESP32");

}

void updateRelays() {
  digitalWrite(RELAY1, relay1State ? HIGH : LOW);
  digitalWrite(RELAY2, relay2State ? HIGH : LOW);
  digitalWrite(RELAY3, relay3State ? HIGH : LOW);
  digitalWrite(RELAY4, relay4State ? HIGH : LOW);
  digitalWrite(RELAY5, relay5State ? HIGH : LOW);
  digitalWrite(RELAY6, relay6State ? HIGH : LOW);
  digitalWrite(RELAY7, relay7State ? HIGH : LOW);
  digitalWrite(RELAY8, relay8State ? HIGH : LOW);
  digitalWrite(RELAY9, relay9State ? HIGH : LOW);
  digitalWrite(RELAY10, relay10State ? HIGH : LOW);
  digitalWrite(RELAY11, relay11State ? HIGH : LOW);
  digitalWrite(RELAY12, relay12State ? HIGH : LOW);
  digitalWrite(RELAY13, relay13State ? HIGH : LOW);
  digitalWrite(RELAY14, relay14State ? HIGH : LOW);
  digitalWrite(RELAY15, relay15State ? HIGH : LOW);
  digitalWrite(RELAY16, relay16State ? HIGH : LOW);
  digitalWrite(RELAY17, relay17State ? HIGH : LOW);
  digitalWrite(RELAY18, relay18State ? HIGH : LOW);
  digitalWrite(RELAY19, relay19State ? HIGH : LOW);
  digitalWrite(RELAY20, relay20State ? HIGH : LOW);
}

void readDHT() {
    //dht.begin();
    int temperature = dht.readTemperature();
    //int humidity = dht.readHumidity();
    //Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
    //Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
    lcd1.setCursor(0, 2);
    lcd1.print("Temperature: ");
    lcd1.print(temperature);
    Serial.println("Temparature: ");
    Serial.println(temperature);
}

void readLightIntensity() {
    lightMeter.begin();
    int lux = lightMeter.readLightLevel();
    //Serial.println(lightMeter.readLightLevel());
    lcd1.setCursor(0, 3);
    lcd1.print("Light: ");
    lcd1.print(lux);
    Serial.println("Light Internsity: ");
    Serial.println(lux);
}

float readVoltage(int pin) {
    float voltage = (analogRead(pin) * VOLTAGE_SCALING);  // Read the analog value (0-1023)
    return voltage;
}

float readCurrent(int sensorPin) {
    int rawValue = analogRead(sensorPin);  // Read raw sensor value
    float voltage = (rawValue * V_REF_C) / 1023.0;  // Convert to voltage
    float current = (voltage - V_MID_C) / SENSITIVITY_C;  // Calculate current in Amperes
    return current;
}

void updateRelaysFromESP32(String command) {
  if (command.startsWith("Relay")) {
    int relayNum = command.substring(5, command.indexOf(':')).toInt();
    bool state = command.endsWith("ON");

    switch (relayNum) {
      case 1:
      case 2:
        relay1State = state;
        relay2State = state;
        break;
      case 3:
      case 4:
        relay3State = state;
        relay4State = state;
        break;
      case 5:
      case 6:
        relay5State = state;
        relay6State = state;
        break;
      case 7:
      case 8:
        relay7State = state;
        relay8State = state;
        break;
      case 9:
      case 10:
        relay9State = state;
        relay10State = state;
        break;
      case 11:
      case 12:
        relay11State = state;
        relay12State = state;
        break;
      case 13:
      case 14:
        relay13State = state;
        relay14State = state;
        break;
      case 15:
      case 16:
        relay15State = state;
        relay16State = state;
        break;
      case 17:
      case 18:
        relay17State = state;
        relay18State = state;
        break;
      case 19:
      case 20:
        relay19State = state;
        relay20State = state;
        break;
    }
  }
}

void processESP32Command(String data) {
    if (data.startsWith("Relay")) {
        int relayNum = data.substring(5, data.indexOf(':')).toInt();  // Extract relay number
        bool state = data.endsWith("ON");  // Determine relay state (ON/OFF)

        // Update the corresponding relay state variable
        switch (relayNum) {
            case 1: relay1State = state; break;
            case 2: relay2State = state; break;
            case 3: relay3State = state; break;
            case 4: relay4State = state; break;
            case 5: relay5State = state; break;
            case 6: relay6State = state; break;
            case 7: relay7State = state; break;
            case 8: relay8State = state; break;
            case 9: relay9State = state; break;
            case 10: relay10State = state; break;
            case 11: relay11State = state; break;
            case 12: relay12State = state; break;
            case 13: relay13State = state; break;
            case 14: relay14State = state; break;
            case 15: relay15State = state; break;
            case 16: relay16State = state; break;
            case 17: relay17State = state; break;
            case 18: relay18State = state; break;
            case 19: relay19State = state; break;
            case 20: relay20State = state; break;
            default: return;  // Ignore invalid relay numbers
        }

        updateRelays();  // Apply the state change

        Serial.print("Relay ");
        Serial.print(relayNum);
        Serial.println(state ? " turned ON" : " turned OFF");
    }
}

void loop() {
  float V_SEN1 = readVoltage(V_SEN_1_PIN); // Main Grid
  float V_SEN2 = readVoltage(V_SEN_2_PIN); // Main solar
  float V_SEN3 = readVoltage(V_SEN_3_PIN); // Wind turbine
  float V_SEN4 = readVoltage(V_SEN_4_PIN); // Battery
  float V_SEN5 = readVoltage(V_SEN_5_PIN); // On grid load
  float V_SEN6 = readVoltage(V_SEN_6_PIN); // Over load
  float V_SEN7 = readVoltage(V_SEN_7_PIN); // Short circuit
  float V_SEN8 = readVoltage(V_SEN_8_PIN); // Industrial Load

  float C_SEN1 = readCurrent(C_SEN_1_PIN); // Main Grid
  float C_SEN2 = readCurrent(C_SEN_2_PIN); // Main solar
  float C_SEN3 = readCurrent(C_SEN_3_PIN); // Wind turbine
  float C_SEN4 = readCurrent(C_SEN_4_PIN); // Battery
  float C_SEN5 = readCurrent(C_SEN_5_PIN); // On grid load
  float C_SEN6 = readCurrent(C_SEN_6_PIN); // Over load
  float C_SEN7 = readCurrent(C_SEN_7_PIN); // Short circuit
  float C_SEN8 = readCurrent(C_SEN_8_PIN); // Industrial Load

  lcd3.setCursor(0, 0);
  lcd3.print("EEE-2025 Future of");
  lcd3.setCursor(0, 1);
  lcd3.print("Electrical SmartGrid");

  readDHT();
  readLightIntensity();
  checkButtons_Grid();
  checkButtons_Solar();
  checkButtons_Wind();
  checkButtons_Bat();
  checkButtons_Load1();
  checkButtons_Load2();
  checkButtons_Load3();
  checkButtons_Load4();
  Sen_Grid(12.5,10,11);
  Sen_Solar(21,10,6);
  Sen_Wind(12.5,5,11);
  Sen_Bat(13.6,9,12.4);
  Sen_Load1(12.5,2,11);
  Sen_Load2(5.5,2.0,3.5);
  Sen_Load3(5.5,1.5,3.5);
  Sen_Load4(5.5,5,3);
  sendStatusToESP();
  String data = Serial1.readStringUntil('\n');  // Read ESP32 message
  processESP32Command(data);  // Function to handle data
}
