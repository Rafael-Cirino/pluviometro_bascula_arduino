#include <EEPROM.h>

// Edite o período de coleta aqui
long periodo_segundos = 20;

// --------------------------------------------------------------------------------------------

// Declara variáveis
float m3_medido = 0;
float mm_chuva = 0;
int sensor_mag = 3;
int ler_sensor = 0;
int ler_sensor_anterior = 0;
int conta_virada_pote = 0;
float ml_por_virada = 2.7;
int ultimo_endereco = 0;

// Período de cada medição
int tempo_segundos = 0;

long tempsperiodo_segundos = 0;

// Converte a quantidade de viradas de copo para mm de chuva
void calc_chuva() {
  m3_medido = conta_virada_pote * ml_por_virada;
  mm_chuva = m3_medido * 127.39 / pow(10, 3);
  Serial.print("Viradas de copo: ");
  Serial.print(conta_virada_pote);
  Serial.print(" | Qtd de chuva: ");
  Serial.print(mm_chuva);
  Serial.println(" mm");
}

void setup() {
  Serial.begin(9600);
  pinMode(sensor_mag, INPUT);
  ler_sensor_anterior = digitalRead(sensor_mag);

  // Verifica qual é a ultima posição de memória em que dados foram salvos
  ultimo_endereco = int(EEPROM.read(511)) + int(EEPROM.read(512));
  Serial.println("Ultimo endereço: ");
  Serial.println(ultimo_endereco);
}

void loop() {
  // Faz a leitura do sensor
  ler_sensor = digitalRead(sensor_mag);


  if (ler_sensor != ler_sensor_anterior) {
    conta_virada_pote = conta_virada_pote + 1;

    // Ativa o buzzer
    pinMode(6, OUTPUT);
    digitalWrite(6, 82);
    delay(0.3 * 1000);
    noTone(6);

    ler_sensor_anterior = ler_sensor;
    calc_chuva();
  }

  // Salva na memória após um período de tempo em segundos
  if ((millis() - tempsperiodo_segundos) >= periodo_segundos * 1000) {
    // Reinicia marcação de tempo e salvo o valor medido na memória
    tempsperiodo_segundos = millis();
    Serial.println("Salvando na memória");
    EEPROM.write(ultimo_endereco, conta_virada_pote);
    ultimo_endereco = ultimo_endereco + 1;
    conta_virada_pote = 0;

    // Como cada posição só armazena até o valor de 255, verifica se precisa
    //   armazenar o dado na posição subsequente
    if (ultimo_endereco <= 255) {
      EEPROM.write(511, byte(ultimo_endereco));
    }
    if (ultimo_endereco > 255) {
      EEPROM.write(512, byte((ultimo_endereco - 255)));
    }
  }
}
