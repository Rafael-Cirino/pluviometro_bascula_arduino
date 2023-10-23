#include <EEPROM.h>


int sensor_mag = 3;
int ler_sensor = 0;
int ler_sensor_anterior = 0;
int conta_virada_pote = 0;
float ml_por_virada = 2.52;
int ultimo_endereco = 0;
float m3_medido = 0;
float mm_chuva = 0;



void calc_chuva() {
  m3_medido = conta_virada_pote * ml_por_virada;
  mm_chuva = m3_medido / pow(10, 3);
}

void print_chuva() {
  Serial.print("Viradas de copo: ");
  Serial.print(conta_virada_pote);
  Serial.print(" | Qtd de chuva: ");
  Serial.print(mm_chuva);
  Serial.println(" mm");
}


void setup() {
  Serial.begin(9600);
  ler_sensor_anterior = 0;
  ultimo_endereco = int(EEPROM.read(511)) + int(EEPROM.read(512));
}

void loop() {
  for (int i = 0; i <= ultimo_endereco; i = i + 1) {
    conta_virada_pote = int(EEPROM.read(i));
    calc_chuva();
    Serial.print("mm_chuva:");
    Serial.println(mm_chuva);
  }
  ultimo_endereco = -1;
}