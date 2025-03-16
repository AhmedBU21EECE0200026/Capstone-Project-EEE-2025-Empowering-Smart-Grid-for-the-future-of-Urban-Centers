#include <Wire.h>
#include <Adafruit_INA260.h>

Adafruit_INA260 ina260_on_grid_load;
Adafruit_INA260 ina260_wind;
Adafruit_INA260 ina260_main_grid;
Adafruit_INA260 ina260_main_solar;

void readPowerSensors() {
    float voltage_grid_load = ina260_on_grid_load.readBusVoltage() / 1000.0;
    float current_grid_load = ina260_on_grid_load.readCurrent() / 1000.0;
    float power_grid_load = ina260_on_grid_load.readPower() / 1000.0;

    float voltage_wind = ina260_wind.readBusVoltage() / 1000.0;
    float current_wind = ina260_wind.readCurrent() / 1000.0;
    float power_wind = ina260_wind.readPower() / 1000.0;

    float voltage_on_grid = ina260_main_grid.readBusVoltage() / 1000.0;
    float current_on_grid = ina260_main_grid.readCurrent() / 1000.0;
    float power_on_grid = ina260_main_grid.readPower() / 1000.0;

    float voltage_solar = ina260_main_solar.readBusVoltage() / 1000.0;
    float current_solar = ina260_main_solar.readCurrent() / 1000.0;
    float power_solar = ina260_main_solar.readPower() / 1000.0;

    bool On_Grid_load_Status = (current_grid_load >= 0);
    String Status_1 = On_Grid_load_Status ? "Sending" : "Receiving";

    bool Main_Grid_Status = (current_on_grid >= 0);
    String Status_2 = Main_Grid_Status ? "Receiving" : "Sending";

    // Print formatted output with new lines
    Serial.println("🔋 On Grid Load:");
    Serial.printf("   Voltage: %.2f V\n", voltage_grid_load);
    Serial.printf("   Current: %.2f A\n", current_grid_load);
    Serial.printf("   Power: %.2f W\n", power_grid_load);
    Serial.printf("   Status: %s\n\n", Status_1.c_str());

    Serial.println("☀️ Main Solar:");
    Serial.printf("   Voltage: %.2f V\n", voltage_solar);
    Serial.printf("   Current: %.2f A\n", current_solar);
    Serial.printf("   Power: %.2f W\n\n", power_solar);

    Serial.println("🌬️ Wind:");
    Serial.printf("   Voltage: %.2f V\n", voltage_wind);
    Serial.printf("   Current: %.2f A\n", current_wind);
    Serial.printf("   Power: %.2f W\n\n", power_wind);

    Serial.println("⚡ Main Grid:");
    Serial.printf("   Voltage: %.2f V\n", voltage_on_grid);
    Serial.printf("   Current: %.2f A\n", current_on_grid);
    Serial.printf("   Power: %.2f W\n\n", power_on_grid);
    Serial.printf("   Status: %s\n\n", Status_2.c_str());
    
    Serial.println("------------------------------------------------");
}

void setup() {
    Serial.begin(115200);
    Wire.begin();
    
    if (!ina260_on_grid_load.begin(0x40)) {
        Serial.println("⚠️ Error initializing INA260 at 0x40 (Grid Load)");
        while (1);
    }
    if (!ina260_wind.begin(0x41)) {
        Serial.println("⚠️ Error initializing INA260 at 0x41 (Wind)");
        while (1);
    }
    if (!ina260_main_grid.begin(0x44)) {
        Serial.println("⚠️ Error initializing INA260 at 0x44 (On Grid)");
        while (1);
    }
    if (!ina260_main_solar.begin(0x45)) {
        Serial.println("⚠️ Error initializing INA260 at 0x45 (Solar)");
        while (1);
    }

    Serial.println("System Initializing...");
}

void loop() {
    readPowerSensors();
    delay(1000); // Add delay to prevent overwhelming the serial output
}
