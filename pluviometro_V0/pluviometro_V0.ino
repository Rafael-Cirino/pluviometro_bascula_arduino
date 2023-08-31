int ler_sensor_anterior;
boolean ler_sensor;
int conta_virada_pote;

void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT);
  ler_sensor_anterior = 0;
}

void loop() {
  ler_sensor = digitalRead(3);
  if (ler_sensor != ler_sensor_anterior) {
    conta_virada_pote = conta_virada_pote + 1;
    Serial.println(conta_virada_pote);
    delay(2 * 1000);
    ler_sensor_anterior = ler_sensor;
  }
}