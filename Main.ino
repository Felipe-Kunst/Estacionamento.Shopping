#include <ESP32Servo.h>
//Pinos dos Segimentos do Display
const int segA = 18, segB = 19, segC = 23, segD = 22, segE = 21, segF = 5, segG = 4;
const int LedVerde = 2, LedVermelho = 15;
//Pino que envia o sinal sonoro
int pinTrig = 12;
//Pino que le o resultado do sinal sonoro
int pinEcho = 14;
int UltimaDistancia = -1;
//Pino dos servos
const int ServoEntrada = 25; //  (Amarelo)
const int ServoSaida = 33;  //  (Vermelho)
//Pinos dos butoes
const int BotaoEntrada = 32; // (Verde)
const int BotaoSaida = 27;  // (Vermelho)
//Pino do display
int count = 0, previousCount = 0;
bool Estado_BotaoEntrada = HIGH;
bool Estado_BotaoSaida = HIGH;
bool EstadoAnterior = HIGH, onLed = HIGH;

Servo CancelaEntrada;
Servo CancelaSaida;

void setup()
{
  Serial.begin(115200);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(LedVermelho, OUTPUT);
  pinMode(LedVerde, OUTPUT);
  pinMode(BotaoEntrada, INPUT_PULLUP);
  pinMode(BotaoSaida, INPUT_PULLUP);
  setupDisplay();
  CancelaEntrada.attach(ServoEntrada);
  CancelaSaida.attach(ServoSaida);
}

int pos = 0;

void loop() {

  if (count >= 0) {
    digitalWrite(LedVermelho, LOW);
    digitalWrite(LedVerde, HIGH);
    if (count > 0 ) {
      digitalWrite(LedVermelho, HIGH);
      digitalWrite(LedVerde, HIGH);

      if (count >= 9) {
        Serial.println("Estacionamento Lotado!!!");
        count = 9;
        digitalWrite(LedVermelho, HIGH);
        digitalWrite(LedVerde, LOW);
      }
    }
  }

  displayShow(count);

  Estado_BotaoSaida = digitalRead(BotaoSaida);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);

  int duration = pulseIn(pinEcho, HIGH);
  int distance = duration / 58;

  if (distance != UltimaDistancia) {
    Serial.print("Distância em CM: ");
    Serial.println(distance);
    UltimaDistancia = distance;
  }


  if (distance < 150) {
    Serial.println("isso nao e um veiculo");
  }

  else {
    Estado_BotaoEntrada = digitalRead(BotaoEntrada);
    if (Estado_BotaoEntrada == LOW && Estado_BotaoEntrada != EstadoAnterior) {
      count++;
      EstadoAnterior = LOW;
      Movimento_CancelaDeEntrada();
      delay(500);
    }
    if (Estado_BotaoEntrada == HIGH && Estado_BotaoEntrada != EstadoAnterior) {
      EstadoAnterior = HIGH;
    }
    if (count != previousCount) {
      previousCount = count;
      displayShow(count);
    }

    // Parte do butao de saida
    if (!Estado_BotaoSaida) {
      count--;
      Movimento_CancelaDeSaida();
    }

    if (count != previousCount) {
      previousCount = count;
      displayShow(count);
      delay(500);
    }
  }
}

//saida dos segmentos do Display
void displayOn(bool a, bool b, bool c, bool d, bool e, bool f, bool g) {
  digitalWrite(segA, a);
  digitalWrite(segB, b);
  digitalWrite(segC, c);
  digitalWrite(segD, d);
  digitalWrite(segE, e);
  digitalWrite(segF, f);
  digitalWrite(segG, g);
}
void setupDisplay() {
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
}

// fUNÇAO PARA MOSTRAR A SEGUENCIA DE NUMEROS 0 a 9
void displayShow(byte numero) {
  switch (numero) {
    case 0: displayMostraZero();
      break;
    case 1: displayMostraUm();
      break;
    case 2: displayMostraDois();
      break;
    case 3: displayMostraTres();
      break;
    case 4: displayMostraQuatro();
      break;
    case 5: displayMostraCinco();
      break;
    case 6: displayMostraSeis();
      break;
    case 7: displayMostraSete();
      break;
    case 8: displayMostraOito();
      break;
    case 9: displayMostraNove();
      break;
  }
}

void displayMostraZero()

//Segimentos(A,B,C,D,E,F,G)
{
  displayOn(1, 1, 1, 1, 1, 1, 0);
}
void displayMostraUm() {
  displayOn(0, 1, 1, 0, 0, 0, 0);
}
void displayMostraDois() {
  displayOn(1, 1, 0, 1, 1, 0, 1);
}
void displayMostraTres() {
  displayOn(1, 1, 1, 1, 0, 0, 1);
}
void displayMostraQuatro() {
  displayOn(0, 1, 1, 0, 0, 1, 1);
}
void displayMostraCinco() {
  displayOn(1, 0, 1, 1, 0, 1, 1);
}
void displayMostraSeis() {
  displayOn(0, 0, 1, 1, 1, 1, 1);
}
void displayMostraSete() {
  displayOn(1, 1, 1, 0, 0, 0, 0);
}
void displayMostraOito() {
  displayOn(1, 1, 1, 1, 1, 1, 1);
}
void displayMostraNove() {
  displayOn(1, 1, 1, 0, 0, 1, 1);
}


void Movimento_CancelaDeEntrada() {
  for (pos = 90; pos >= 0; pos -= 1) {
    CancelaEntrada.write(pos);
    delay(15);
  }
  delay(1000);
  for (pos = 0; pos <= 90; pos += 1) {
    CancelaEntrada.write(pos);
    delay(15);
  }
}


void Movimento_CancelaDeSaida() {
  for (pos = 90; pos >= 0; pos -= 1) {
    CancelaSaida.write(pos);
    delay(15);
  }
  delay(1000);
  for (pos = 0; pos <= 90; pos += 1) {
    CancelaSaida.write(pos);
    delay(15);
  }
}
