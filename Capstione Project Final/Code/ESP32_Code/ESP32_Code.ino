#define BLYNK_TEMPLATE_ID "TMPL3Bgw6LPkm"
#define BLYNK_TEMPLATE_NAME "Hii"
#define BLYNK_AUTH_TOKEN "06L3mrc50eDc8rbUfNvjSgbrrd9kCDJS"

#define BLYNK_PRINT Serial  // Enable Serial Debugging

#include <Wire.h>
#include <Adafruit_INA260.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "sivakumar123";
char pass[] = "sivakumar";

Adafruit_INA260 ina260_grid_load;
Adafruit_INA260 ina260_wind;
Adafruit_INA260 ina260_on_grid;
Adafruit_INA260 ina260_solar;

BlynkTimer timer;
WidgetTerminal terminal(V1);

bool relayStates[20];
bool prevRelayStates[20];

bool gridState = false;
bool batteryState = false;

void updateMegaRelays() {
    for (int i = 0; i < 20; i++) {
        if (relayStates[i] != prevRelayStates[i]) {  // Only send if state has changed
            sendRelayStateToMega(i + 1, relayStates[i]);
            prevRelayStates[i] = relayStates[i];  // Update previous state
        }
    }
}

// Function to send relay state changes to Mega
void sendRelayStateToMega(int relayNumber, bool state) {
    String message = "Relay" + String(relayNumber) + ": " + (state ? "ON" : "OFF");
    Serial1.println(message);
    terminal.println("Sent to Mega: " + message);
    terminal.flush();
}

// BLYNK Switch Handlers with Parent Dependency
BLYNK_WRITE(V20) {  // Grid State
    gridState = param.asInt();
    if (!gridState) {  
        Blynk.virtualWrite(V21, 0);  // Turn off Grid Condition
        sendRelayStateToMega(3, false);  
        sendRelayStateToMega(5, false);
    }
}
BLYNK_WRITE(V21) {  // Grid Condition (Only works if Grid State is ON)
    if (gridState) {  
        bool gridCondition = param.asInt();
        sendRelayStateToMega(1, !gridCondition);  // Relay1 & Relay2 ON if Condition OFF
        sendRelayStateToMega(3, gridCondition);  // Relay3 & Relay4 ON if Condition ON
    }
}
BLYNK_WRITE(V24) {  // Battery State
    batteryState = param.asInt();
    if (!batteryState) {  
        Blynk.virtualWrite(V25, 0);  // Turn off Battery Condition
        sendRelayStateToMega(9, false);  
        sendRelayStateToMega(11, false);
    }
}
BLYNK_WRITE(V25) {  // Battery Condition (Only works if Battery State is ON)
    if (batteryState) {  
        bool batteryCondition = param.asInt();
        sendRelayStateToMega(9, !batteryCondition);
        sendRelayStateToMega(11, batteryCondition);
    }
}
// Wind Turbine - Relay7 & Relay8
BLYNK_WRITE(V23) { 
    bool state = param.asInt();
    sendRelayStateToMega(7, state);  
}
// Industrial Load - Relay19 & Relay20
BLYNK_WRITE(V29) { 
    bool state = param.asInt();
    sendRelayStateToMega(19, state);  
}
// Commercial Load - Relay15 & Relay16
BLYNK_WRITE(V27) { 
    bool state = param.asInt();
    sendRelayStateToMega(15, state);  
}
// Main Domestic Load - Relay17 & Relay18
BLYNK_WRITE(V28) { 
    bool state = param.asInt();
    sendRelayStateToMega(17, state);  
}
// On Grid Load - Relay5 & Relay6
BLYNK_WRITE(V26) { 
    bool state = param.asInt();
    sendRelayStateToMega(5, state);  
}
// Process incoming Serial data from Mega
void processMegaData(String data) {
    terminal.println(data);  
    terminal.flush();

    if (data.startsWith("Relay")) {
        int relayNum = data.substring(5, data.indexOf(':')).toInt();
        bool state = data.endsWith("ON");
        relayStates[relayNum - 1] = state;

        // Update Blynk UI
        Blynk.virtualWrite(V20 + relayNum - 1, state);
    }
      else if (data.startsWith("V_SEN4:")) {
        float voltage = data.substring(8).toFloat();
        Blynk.virtualWrite(V34, voltage);
        terminal.printf("Battery Voltage: %.2fV\n", voltage);
    } else if (data.startsWith("C_SEN4:")) {
        float current = data.substring(8).toFloat();
        Blynk.virtualWrite(V34, current);
        terminal.printf("Battery Current: %.2fA\n", current);
    } else if (data.startsWith("Battery_Power:")) {
        float power = data.substring(15).toFloat();
        Blynk.virtualWrite(V34, power);
        terminal.printf("Battery Power: %.2fW\n", power);
    } else if (data.startsWith("V_SEN6:")) {
        float voltage = data.substring(8).toFloat();
        Blynk.virtualWrite(V38, voltage);
        terminal.printf("Commercial Load Voltage: %.2fV\n", voltage);
    } else if (data.startsWith("C_SEN6:")) {
        float current = data.substring(8).toFloat();
        Blynk.virtualWrite(V38, current);
        terminal.printf("Commercial Load Current: %.2fA\n", current);
    } else if (data.startsWith("V_SEN7:")) {
        float voltage = data.substring(8).toFloat();
        Blynk.virtualWrite(V37, voltage);
        terminal.printf("Domestic Load Voltage: %.2fV\n", voltage);
    } else if (data.startsWith("C_SEN7:")) {
        float current = data.substring(8).toFloat();
        Blynk.virtualWrite(V37, current);
        terminal.printf("Domestic Load Current: %.2fA\n", current);
    } else if (data.startsWith("V_SEN8:")) {
        float voltage = data.substring(8).toFloat();
        Blynk.virtualWrite(V39, voltage);
        terminal.printf("Industrial Load Voltage: %.2fV\n", voltage);
    } else if (data.startsWith("C_SEN8:")) {
        float current = data.substring(8).toFloat();
        Blynk.virtualWrite(V39, current);
        terminal.printf("Industrial Load Current: %.2fA\n", current);
    }
}
// Read Power Sensors (ESP32 Side)
void readPowerSensors() {
    float voltage_grid_load = ina260_grid_load.readBusVoltage() / 1000;
    float current_grid_load = ina260_grid_load.readCurrent() / 1000;
    float power_grid_load = ina260_grid_load.readPower() / 1000;
    bool On_Grid_load_Status;
    if(current_grid_load >= 0)
    {
      On_Grid_load_Status = true;
    }
    else
    {
      On_Grid_load_Status = false;
    }

    float voltage_wind = ina260_wind.readBusVoltage() / 1000;
    float current_wind = ina260_wind.readCurrent() / 1000;
    float power_wind = ina260_wind.readPower() / 1000;

    float voltage_on_grid = ina260_on_grid.readBusVoltage() / 1000;
    float current_on_grid = ina260_on_grid.readCurrent() / 1000;
    float power_on_grid = ina260_on_grid.readPower() / 1000;

    float voltage_solar = ina260_solar.readBusVoltage() / 1000;
    float current_solar = ina260_solar.readCurrent() / 1000;
    float power_solar = ina260_solar.readPower() / 1000;

    terminal.println("🔋 ESP32 Power Sensor Readings:");
    String Status = (On_Grid_load_Status) ? "Receiving" : "Sending";
    terminal.printf("Grid Load - V: V | I: A | P: W | %s\n", voltage_grid_load, current_grid_load, power_grid_load,Status);
    terminal.printf("Solar - V: V | I: A | P: W\n", voltage_solar, current_solar, power_solar);
    terminal.printf("Wind - V: V | I: A | P: W\n", voltage_wind, current_wind, power_wind);
    terminal.printf("On Grid Load - V: V | I: A | P: W\n", voltage_on_grid, current_on_grid, power_on_grid);
    terminal.flush();
}

void setup() {
    Serial.begin(115200);
    Serial1.begin(115200, SERIAL_8N1, 16, 17);
    WiFi.begin(ssid, pass);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    Wire.begin();
    ina260_grid_load.begin(0x40);
    ina260_wind.begin(0x41);
    ina260_on_grid.begin(0x44);
    ina260_solar.begin(0x45);

    Serial.println("✅ ESP32 Connected to Blynk!");
    Serial.println("System Initializing...");
    terminal.flush();

    timer.setInterval(200L, readPowerSensors);
}

void loop() {
    Blynk.run();
    timer.run();

    if (Serial1.available()) {
        String data = Serial1.readStringUntil('\n');
        processMegaData(data);
    }

    updateMegaRelays();
}
