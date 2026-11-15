#define RELAY_PIN 7
#define CONTROL_PIN 2

bool previousState = false;

void setup()
{
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(CONTROL_PIN, INPUT);

  digitalWrite(RELAY_PIN, HIGH); // Relay OFF

  Serial.println("Automatic Pump Controller Ready");
}

void loop()
{
  int command = digitalRead(CONTROL_PIN);

  if (command == HIGH)
  {
    digitalWrite(RELAY_PIN, LOW);

    if (!previousState)
    {
      Serial.println("PUMP ON");
      previousState = true;
    }
  }
  else
  {
    digitalWrite(RELAY_PIN, HIGH);

    if (previousState)
    {
      Serial.println("PUMP OFF");
      previousState = false;
    }
  }

  delay(200);
}
