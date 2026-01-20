#include <Wire.h>
#include <WiFi.h>
#include <esp_now.h>
#include <TinyGPSPlus.h>
#include "MPU6050.h"

/* ================= PIN DEFINITIONS ================= */
#define GSM_RX 16        // ESP32 RX ← SIM900A TX
#define GSM_TX 17        // ESP32 TX → SIM900A RX

#define LED_CRASH 13     // ON for 5 seconds when crash detected
#define LED_GPS   27     // ON when GPS lock
#define LED_GSM   33     // ON when GSM registered



/* ================= OBJECTS ================= */
HardwareSerial gsmSerial(2);
TinyGPSPlus gps;
MPU6050 mpu;

/* ================= DATA STRUCTURES ================= */
typedef struct {
  bool alcoholDetected;
} AlcoholData;

AlcoholData alcoholData;

/* ================= VARIABLES ================= */
unsigned long crashLedTimer = 0;
bool crashLedActive = false;

/* ================= FUNCTION DECLARATIONS ================= */
void sendCrashSMS(const String &msg);
bool detectCrash();

/* ================= ESP-NOW CALLBACK (FIXED) ================= */
void OnDataRecv(const esp_now_recv_info *info,
                const uint8_t *incomingData,
                int len) {

  memcpy(&alcoholData, incomingData, sizeof(alcoholData));

  if (alcoholData.alcoholDetected) {
    String msg = "ALERT: Alcohol detected.\n";

    if (gps.location.isValid()) {
      msg += "Location:\nhttps://www.google.com/maps?q=";
      msg += String(gps.location.lat(), 6);
      msg += ",";
      msg += String(gps.location.lng(), 6);
    } else {
      msg += "GPS not fixed.";
    }

    sendCrashSMS(msg);
  }
}

/* ================= SETUP ================= */
void setup() {
  Serial.begin(115200);

  pinMode(LED_CRASH, OUTPUT);
  pinMode(LED_GPS, OUTPUT);
  pinMode(LED_GSM, OUTPUT);

  digitalWrite(LED_CRASH, LOW);
  digitalWrite(LED_GPS, LOW);
  digitalWrite(LED_GSM, LOW);

  /* ---------- I2C + MPU6050 FIRST ---------- */
  Wire.begin(23,22);
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }
  Serial.println("MPU6050 ready");

  /* ---------- GSM ---------- */
  gsmSerial.begin(9600, SERIAL_8N1, GSM_RX, GSM_TX);
  delay(3000);

  gsmSerial.println("AT");
  delay(1000);
  gsmSerial.println("AT+CMGF=1");   // SMS text mode
  delay(1000);

  /* ---------- GPS (UART0 passthrough assumed externally) ---------- */
  Serial.println("Waiting for GPS fix...");

  /* ---------- ESP-NOW ---------- */
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    while (1);
  }

  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("ESP-NOW ready");
}

/* ================= LOOP ================= */
void loop() {

  /* ---------- GPS STATUS ---------- */
  while (Serial.available()) {
    gps.encode(Serial.read());
  }

  if (gps.location.isValid()) {
    digitalWrite(LED_GPS, HIGH);
  } else {
    digitalWrite(LED_GPS, LOW);
  }

  /* ---------- GSM NETWORK STATUS ---------- */
  gsmSerial.println("AT+CREG?");
  delay(200);

  if (gsmSerial.find(",1") || gsmSerial.find(",5")) {
    digitalWrite(LED_GSM, HIGH);
  } else {
    digitalWrite(LED_GSM, LOW);
  }

  /* ---------- CRASH DETECTION ---------- */
  if (detectCrash()) {
    digitalWrite(LED_CRASH, HIGH);
    crashLedTimer = millis();
    crashLedActive = true;

    String msg = "CRASH DETECTED!\n";
    if (gps.location.isValid()) {
      msg += "Location:\nhttps://www.google.com/maps?q=";
      msg += String(gps.location.lat(), 6);
      msg += ",";
      msg += String(gps.location.lng(), 6);
    }

    sendCrashSMS(msg);
  }

  /* ---------- CRASH LED AUTO OFF (5s) ---------- */
  if (crashLedActive && millis() - crashLedTimer >= 5000) {
    digitalWrite(LED_CRASH, LOW);
    crashLedActive = false;
  }

  delay(500);
}

/* ================= FUNCTIONS ================= */

bool detectCrash() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  float magnitude = sqrt(ax * ax + ay * ay + az * az) / 16384.0;

  return (magnitude > 3.0);  // tuned crash threshold
}

void sendCrashSMS(const String &msg) {
  gsmSerial.println("AT+CMGS=\"+94782009028\"");  // replace number
  delay(500);
  gsmSerial.print(msg);
  delay(500);
  gsmSerial.write(26); // CTRL+Z
  delay(3000);
}
