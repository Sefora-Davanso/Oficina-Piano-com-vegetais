#include <movingAvg.h>

// Ajuste conforme necessário
const int limiarPressionado = 400;
const int limiarSolto = 1020;
const byte numPinos = 6;

const byte pinosEntrada[numPinos] = {A0, A1, A2, A3, A4, A5};
const char teclas[numPinos] = {'t', 'y', 'u', 'i', 'o', 'p'};

struct estruturaEntrada {
  byte pinoAnalogico;
  char tecla;
  movingAvg filtro = movingAvg(20);
  boolean pressionado = false;
};

estruturaEntrada pinos[numPinos];

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < numPinos; i++) {
    pinos[i].pinoAnalogico = pinosEntrada[i];
    pinos[i].tecla = teclas[i];
    pinos[i].filtro.begin();
  }
}

void loop() {
  for (int i = 0; i < numPinos; i++) {
    float mediaAtual = pinos[i].filtro.reading(analogRead(pinos[i].pinoAnalogico));
    boolean estadoAnterior = pinos[i].pressionado;
    boolean estadoAtual = estadoAnterior;

    if (mediaAtual < limiarPressionado) {
      estadoAtual = true;
    } else if (mediaAtual > limiarSolto) {
      estadoAtual = false;
    }

    if (estadoAtual != estadoAnterior) {
      if (estadoAtual) {
        Serial.println(pinos[i].tecla);  // Envia a tecla pressionada
      }
    }
    pinos[i].pressionado = estadoAtual;
  }
}

