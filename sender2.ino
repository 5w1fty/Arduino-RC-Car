#include <SoftwareSerial.h>

// Bluetooth Pins
#define BT_TX 2  // Bluetooth TX-Pin
#define BT_RX 3  // Bluetooth RX-Pin

// Joystick Pins
#define JOY_X A0 // X-Achse (Lenkung)
#define JOY_Y A1 // Y-Achse (Geschwindigkeit)

SoftwareSerial BTSerial(BT_TX, BT_RX);

void setup() {
    BTSerial.begin(9600);
    Serial.begin(9600);
}

void loop() {
    int joystickX = analogRead(JOY_X);
    int joystickY = analogRead(JOY_Y);

    // Joystick-Werte anpassen
    int lenkung = map(joystickX, 0, 1023, 45, 135);
    int motor = map(joystickY, 0, 1023, 90, 180);

    // Werte senden
    BTSerial.print(lenkung);
    BTSerial.print(",");
    BTSerial.println(motor);

    // Debugging
    Serial.print("Gesendet -> Lenkung: ");
    Serial.print(lenkung);
    Serial.print(" | Motor: ");
    Serial.println(motor);
    
    delay(100);
}
