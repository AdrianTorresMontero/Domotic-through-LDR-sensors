#define LDR_PIN A0
#define PIR_PIN 2
#define LED_PIN 9

int ldrValue;
int filtered = 0;
int motion;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);

  // PWM alta frecuencia
  TCCR1B = TCCR1B & 0b11111000 | 0x01;
}

void loop() {

  // Leer sensores
  ldrValue = analogRead(LDR_PIN);
  motion = digitalRead(PIR_PIN);

  // Filtrar lectura de luz
  filtered = filtered * 0.9 + ldrValue * 0.1;

  // Invertir valor (oscuro = grande)
  int darkness = 1023 - filtered;

  // Convertir oscuridad a brillo PWM
  int pwm = map(darkness, 150, 900, 0, 255);
  pwm = constrain(pwm, 0, 255);

  // Lógica PIR + LDR
  if (motion == HIGH) {
    analogWrite(LED_PIN, pwm);  // brillo automático
  } else {
    analogWrite(LED_PIN, 0);    // apagado total
  }

  delay(20);
}