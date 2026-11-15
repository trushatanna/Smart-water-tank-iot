#define BLYNK_TEMPLATE_ID "TMPL3Qxd4fb8_"
#define BLYNK_TEMPLATE_NAME "water tank monitor"
#define BLYNK_AUTH_TOKEN "GgbvUE2h4z8hmFvmLbYqLD44Qolcw5-x"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "narzo 50A";
char pass[] = "Narzo 50";

#define TRIG_PIN D5
#define ECHO_PIN D6
#define PUMP_SIGNAL D1

float EMPTY_DISTANCE_CM = 15.0;
float FULL_DISTANCE_CM = 3.0;

bool pumpState = false;

BlynkTimer timer;

void sendWaterLevel()
{
  // Ultrasonic trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read sensor
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // Sensor error: pump OFF
  if (duration == 0) {
    pumpState = false;
    digitalWrite(PUMP_SIGNAL, LOW);

    Blynk.virtualWrite(V4, 0);

    Serial.println("Sensor Error - Pump OFF");
    return;
  }

  float distance = duration * 0.0343 / 2.0;

  // Calculate water level
  float percentage =
    (EMPTY_DISTANCE_CM - distance) /
    (EMPTY_DISTANCE_CM - FULL_DISTANCE_CM) * 100.0;

  percentage = constrain(percentage, 0, 100);

  float waterHeight = max(
    0.0f,
    EMPTY_DISTANCE_CM - distance
  );

  // Automatic control
  if (percentage < 20) {
    pumpState = true;
  }
  else if (percentage >= 90) {
    pumpState = false;
  }

  // Send command to Arduino
  digitalWrite(PUMP_SIGNAL, pumpState ? HIGH : LOW);

  // Water status
  String status;

  if (percentage < 25) {
    status = "LOW";
  }
  else if (percentage < 75) {
    status = "NORMAL";
  }
  else {
    status = "HIGH";
  }

  // Send to Blynk
  Blynk.virtualWrite(V0, percentage);
  Blynk.virtualWrite(V1, distance);
  Blynk.virtualWrite(V2, waterHeight);
  Blynk.virtualWrite(V3, status);
  Blynk.virtualWrite(V4, pumpState ? 1 : 0);

  // Serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.print("Water Level: ");
  Serial.print(percentage);
  Serial.println("%");

  Serial.print("Water Status: ");
  Serial.println(status);

  Serial.print("Pump: ");
  Serial.println(pumpState ? "ON" : "OFF");

  Serial.println("--------------------");
}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("NodeMCU Starting...");

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(PUMP_SIGNAL, OUTPUT);
  digitalWrite(PUMP_SIGNAL, LOW);

  Serial.println("Ultrasonic Sensor Ready");
  Serial.println("Connecting to Blynk...");

  Blynk.begin(
    BLYNK_AUTH_TOKEN,
    ssid,
    pass
  );

  Serial.println("Blynk Connected!");

  timer.setInterval(2000L, sendWaterLevel);
}

void loop()
{
  Blynk.run();
  timer.run();
}
