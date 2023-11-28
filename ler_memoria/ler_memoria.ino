#include <EEPROM.h>


int sensor_mag = 3;
int ler_sensor = 0;
int ler_sensor_anterior = 0;
int conta_virada_pote = 0;
float ml_por_virada = 2.52;
int ultimo_endereco = 0;
int entrada_usuario = 0;
float m3_medido = 0;
float mm_chuva = 0;



void calc_chuva() {
  m3_medido = conta_virada_pote * ml_por_virada;
  mm_chuva = m3_medido * (127.39 / pow(10, 3));
}


void setup() {
  Serial.begin(9600);
  ultimo_endereco = int(EEPROM.read(511)) + int(EEPROM.read(512));
  Serial.println("");
  Serial.println("Digite 1: Para ler os dados");
  Serial.println("Digite 2: Para apagar todos os dados da memória");
}

void loop() {
  if (Serial.available() > 0) {
    entrada_usuario = Serial.read() - 48;
  }
  if (entrada_usuario == 1) {
    for (int i = 0; i <= ultimo_endereco; i = i + 1) {
      conta_virada_pote = int(EEPROM.read(i));
      calc_chuva();
      Serial.print("mm_chuva:");
      Serial.println(mm_chuva);
    }
    entrada_usuario = 0;
  }
  if (entrada_usuario == 2) {
    for (int i = 0; i <= 512; i = i + 1) {
      EEPROM.write(i, 0);
    }
    Serial.println("Dados foram apagados");
    ultimo_endereco = 0;
    entrada_usuario = 0;
  }
}