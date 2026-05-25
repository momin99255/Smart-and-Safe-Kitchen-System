const int PIR_PIN = 27; 
const int LDR_PIN = 34; 
const int LED_PIN = 2;  

const int myDarkThreshold = 300; 

unsigned long lastMotionTime = 0;
const unsigned long delayTime = 5000;

void setup() {
  Serial.begin(9600); 
  
  pinMode(PIR_PIN, INPUT_PULLDOWN);
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("PIR warming up...");
  delay(3000); 
  Serial.println("Ready!");
  
  digitalWrite(LED_PIN, LOW);
  Serial.println("🚀 Simple Hybrid System Online...");
}

void loop() {
  int motion = digitalRead(PIR_PIN);
  int ldrValue = analogRead(LDR_PIN);

  Serial.print("LDR Value: ");
  Serial.print(ldrValue);
  Serial.print(" | Motion State: ");
  Serial.println(motion);

//module 1 (if light detects led always off if light off and motion detects light on for 5 sec and gets reset )

 if (ldrValue > myDarkThreshold) {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Enough light");
  }

  if (ldrValue < myDarkThreshold && motion == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    lastMotionTime = millis();
    Serial.println("MOTION DETECTED -> LED ON / TIMER RESET");
  }

  if (digitalRead(LED_PIN) == HIGH && (millis() - lastMotionTime > delayTime)) {
    digitalWrite(LED_PIN, LOW); 
    Serial.println("5 Seconds Timeout -> LED OFF");
  }

  delay(200);
}