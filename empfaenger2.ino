#include <Servo.h>
#include <SoftwareSerial.h>

// Pins
#define SERVO_PIN 9     // Servo für die Lenkung
#define ESC_PIN 10      // ESC für den Motor
#define BT_RX 11        // Bluetooth RX
#define BT_TX 12        // Bluetooth TX

// Servo- und ESC-Objekte
Servo lenkung;
Servo motor;
SoftwareSerial BTSerial(BT_RX, BT_TX); // SoftwareSerial für Bluetooth

// Eingangsvariablen
int lenkWinkel = 90;   // Startposition der Lenkung (neutral)
int motorPower = 90;   // Neutralstellung für ESC (Mittelwert für Stop)

void setup() {
    // Servos an Pins anschließen
    lenkung.attach(SERVO_PIN);
    motor.attach(ESC_PIN);
    
    // Bluetooth starten
    BTSerial.begin(9600);
    
    // Initiale Position setzen
    lenkung.write(lenkWinkel);
    motor.write(motorPower);
    Serial.begin(9600); // Serielle Kommunikation starten
    Serial.println("Started");
}

void loop() {
    // Prüfen, ob Daten über Bluetooth empfangen wurden
    if (BTSerial.available()) {
        String data = BTSerial.readStringUntil('\n');
        int commaIndex = data.indexOf(',');
        Serial.print("BT Available");
        if (commaIndex > 0) {
            int lenkungWert = data.substring(0, commaIndex).toInt();
            int motorWert = data.substring(commaIndex + 1).toInt();
            
            // Werte aktualisieren
            lenkung.write(lenkungWert);
            motor.write(motorWert);
            
            // Debugging
            Serial.print("Empfangen -> Lenkung: ");
            Serial.print(lenkungWert);
            Serial.print(" | Motor: ");
            Serial.println(motorWert);
        }else{
          Serial.println("Kein Empfang!");
        }
    }
    
    delay(50); // Kurze Pause zur Stabilisierung
}
