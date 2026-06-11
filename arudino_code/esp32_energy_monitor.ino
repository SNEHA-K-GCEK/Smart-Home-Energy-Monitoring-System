#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Hardware Pin Configuration matching Phase 11 specs
const int CURRENT_SENSOR_PIN = 34; // ACS712 Out
const int ALERT_LED_PIN = 26;      // Safety Status LED
const int BUZZER_PIN = 27;         // Warning Alarm Buzzer

// Threshold constants
const float POWER_THRESHOLD = 2000.0; // 2000 Watts limit
const float VOLTAGE_MAINS = 230.0;    // Standard household voltage reference

void setup() {
    Serial.begin(115200);

    // Initialize Hardware Pins
    pinMode(CURRENT_SENSOR_PIN, INPUT);
    pinMode(ALERT_LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    // Initialize I2C OLED Display (Pins 21 and 22 are default on ESP32)
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 OLED display allocation failed"));
        for(;;);
    }

    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
}

void loop() {
    // 1. Read Analog Signal from ACS712 Current Sensor
    int rawValue = analogRead(CURRENT_SENSOR_PIN);
    // Convert the analog signal to Amperes (assuming 185mV/A sensitivity for ACS712)
    float voltageOffset = (rawValue / 4095.0) * 3.3;
    float current = (voltageOffset - 1.65) / 0.185;
    if (current < 0.05) current = 0.0; // Filter out baseline line noise

    // 2. Calculate derived electrical metrics
    float power = VOLTAGE_MAINS * current;

    // 3. Evaluate safety alerts against power thresholds
    bool highConsumption = (power > POWER_THRESHOLD);

    if (highConsumption) {
        digitalWrite(ALERT_LED_PIN, HIGH);
        digitalWrite(BUZZER_PIN, HIGH); // Fire high-pitched alarm audio tone
    } else {
        digitalWrite(ALERT_LED_PIN, LOW);
        digitalWrite(BUZZER_PIN, LOW);
    }

    // 4. Update the Local OLED Monitor Display layout
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("--- LIVE ENERGY ---");
    display.print("Voltage: "); display.print(VOLTAGE_MAINS, 1); display.println(" V");
    display.print("Current: "); display.print(current, 2); display.println(" A");
    display.print("Power:   "); display.print(power, 1); display.println(" W");
    display.println("-------------------");
    display.print("Status:  "); display.println(highConsumption ? "OVERLOAD!" : "NORMAL");
    display.display();

    // 5. Stream values over USB Serial interface line to our Python app link
    Serial.print(VOLTAGE_MAINS);
    Serial.print(",");
    Serial.println(current);

    delay(2000); // Sample readings every 2 seconds
}