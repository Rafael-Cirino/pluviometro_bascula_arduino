boolean ler_sensor;
int conta_virada_pote;

void interrupt_3(){
  conta_virada_pote = conta_virada_pote + 1;
  Serial.println(conta_virada_pote);
}


void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(3),interrupt_3,CHANGE);
}

void loop() {
  ler_sensor = digitalRead(3);

}