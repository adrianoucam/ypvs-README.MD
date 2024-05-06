#include <Servo.h>

Servo servoMotor; // Criando um objeto servoMotor
int potPin = A0; // Pino analógico conectado ao potenciômetro
int rpm; // Variável para armazenar a leitura do potenciômetro
int servoPin = 9; // Pino digital conectado ao servo motor

void setup() {
  servoMotor.attach(servoPin); // Inicializando o servo motor
  Serial.begin(9600); // Inicializando a comunicação serial
}

void loop() {
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
    return 0; // Válvula fechada para rotações abaixo de 3000 RPM
  } else if (rpm >= 3000 && rpm < 5500) {
    return map(rpm, 3000, 5500, 180, 0); // Mapeando a rotação para o ângulo de abertura entre 180 e 0 graus
  } else {
    return 180; // Válvula totalmente aberta para rotações acima de 5500 RPM
  }
}

