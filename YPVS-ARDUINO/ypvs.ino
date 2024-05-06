#include <Servo.h>
// #include <FreqMeasure.h>
/*

A idéia do cara é fazer com arduíno
esse abaixo foi versao inicial
https://forum.arduino.cc/t/bike-servo-controller-based-on-an-rpm-input/1001911

estou usando potenciometro para simular rotacao no thinkercad. mas a biblioteca freqMeasure gera a informacao de rotacao necessaria

*/
  
Servo servoMotor; // Criando um objeto servoMotor
int potPin = A0; // Pino analógico conectado ao potenciômetro
int rpm; // Variável para armazenar a leitura do potenciômetro
int servoPin = 9; // Pino digital conectado ao servo motor
int ledPin = 13;

void setup() {
  servoMotor.attach(servoPin); // Inicializando o servo motor
  Serial.begin(9600); // Inicializando a comunicação serial
  pinMode(ledPin, OUTPUT);
//  FreqMeasure.begin(); // Inicializando a medição de frequência
}

void loop() {
 /* FreqMeasure.available(); // Verificando se há uma nova leitura disponível

  if (FreqMeasure.available()) {
    unsigned long count = FreqMeasure.count(); // Obtendo a contagem da frequência medida
    if (count != 0) { // Verificando se a contagem é válida
      float frequency = FreqMeasure.frequency(); // Convertendo a contagem em frequência
      rpm = frequency * 60; // Convertendo frequência para RPM
    }
  }
*/
  rpm = map(analogRead(potPin), 0, 1023, 0, 10000); // Lendo o valor do potenciômetro e mapeando para o intervalo de 0 a 10000 RPM
  int angle = calculateAngle(rpm); // Calculando o ângulo de abertura da válvula com base na rotação

  servoMotor.write(angle); // Movendo o servo motor para a posição correspondente ao ângulo calculado
  delay(100); // Atraso para suavizar o movimento do servo motor

  Serial.print("RPM: ");
  Serial.print(rpm);
  Serial.print(" Angulo de abertura : ");
  Serial.println(angle);
  delay(500); // Atraso para evitar leituras muito rápidas
}

int calculateAngle(int rpm) {
  if (rpm < 3000) {
    digitalWrite(ledPin, LOW);
    return 0; // Válvula fechada para rotações abaixo de 3000 RPM
  } else if (rpm >= 3000 && rpm < 6000) {
    digitalWrite(ledPin, HIGH);
    return map(rpm, 3000, 6000, 0, 180); // Mapeando a rotação para o ângulo de abertura entre 0 e 180 graus
  } else {
    digitalWrite(ledPin, HIGH);
    return 180; // Válvula totalmente aberta para rotações acima de 6000 RPM
  }
}
