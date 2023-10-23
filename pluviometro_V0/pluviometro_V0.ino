int ler_sensor_anterior;
boolean ler_sensor;
int conta_virada_pote;

void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT);
  pinMode(6, OUTPUT);
  ler_sensor_anterior = digitalRead(3);
}

void loop() {
  ler_sensor = digitalRead(3);
  
  if (ler_sensor != ler_sensor_anterior) {
    conta_virada_pote = conta_virada_pote + 1;
    pinMode(6, OUTPUT);
    digitalWrite(6, 82);
    delay(0.5 * 1000);
    noTone(6);
    ler_sensor_anterior = ler_sensor;
    Serial.print("Viradas de copo: ");
    Serial.print(conta_virada_pote);

    float m3_medido = (conta_virada_pote * 2.52)/pow(10, 6);
    float mm_chuva = (m3_medido*1000)/0.00785;
    Serial.print(" | Qtd de chuva: ");
    Serial.print(mm_chuva);
    Serial.println(" mm");
  }
}