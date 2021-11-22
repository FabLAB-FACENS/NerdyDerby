//Autor: Nicolas de Castro Silva
//Descrição: Código do Arduino que controla os displays na chegada do NerdyDerby, onde é exibido a posição e o tempo de cada carrinho
//Materiais ultilizado: Arduino Uno, regulador 5v 1a, 3 Displays 7 seguimentos RoboCore, 3 displays de 4 digitos e 7 seguimentos

#include <SoftwareSerial.h> //Declaração da biblioteca para utilizar comunicação serial
#include <SerialDisplay.h> //Biblicoteca para utilização dos displays da Robocore
#include <TM1637Display.h> //Biblioteca para utilizaçãod os displays de 4 digitos

TM1637Display displayTime3(7, 6);//Declaração das portas para os displays de 4 digitos CLK/DIO
TM1637Display displayTime2(9, 8);//Declaração das portas para os displays de 4 digitos CLK/DIO
TM1637Display displayTime1(11, 10);//Declaração das portas para os displays de 4 digitos CLK/DIO

SerialDisplay displaysPositions(12, 13, 3); // Dados, clock, numero de modulos

SoftwareSerial mySerial(2, 3); //Declaração das portas para utilização de comunicação serial
String data = ""; //Variavel que armazena as mensagem recebidas por serial

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Inicialização da comunicação Serial com o PC
  mySerial.begin(9600); // Inicialização da comunicalçao Serial com o Arduino Central
  displayTime1.setBrightness(5);//Controle de luminosidade do display de 4 digitos
  displayTime2.setBrightness(5);//Controle de luminosidade do display de 4 digitos
  displayTime3.setBrightness(5);//Controle de luminosidade do display de 4 digitos
  ShowPosition(1,1);
  ShowPosition(2,2);
  ShowPosition(3,3);
  ShowTime1(1111);
  ShowTime2(2222);
  ShowTime3(3333);
}

void loop() {
  //Repetição que recebe as mensagens pela comunicação Serial
  while (mySerial.available() > 0) {
    char character = mySerial.read();
    if (character != '\n') {
      data += character;
    }
    delay(10);
  }
  
  //Recebimento do resultado da corrida calculado pelo arduino central
  if (data.indexOf("result") != -1) { 
    Serial.println(data.substring(23, 27));
    ShowPosition(1, data[7]);
    ShowPosition(2, data[9]);
    ShowPosition(3, data[11]);
    ShowTime1(data.substring(13, 17).toInt());
    ShowTime2(data.substring(18, 22).toInt());
    ShowTime3(data.substring(23, 27).toInt());
    data = "";
  } else if (data.indexOf("reset") != -1) {//Limpeza dos displays
    Serial.println("Reset");
    ClearTimes();
    data = "";
  } else if (data.indexOf("start") != -1) {//Contagem regressiva no inicio da corrida
    Serial.println("Start");
    for (int i = 3; i >= 0 ; i--) {
      ShowPosition(1, i);
      ShowPosition(2, i);
      ShowPosition(3, i);
      delay(1000);
    }
    data = "";
  }
}
void ShowPosition(int track, int number) {
  displaysPositions.Print(number, track); // E impresso no display 2 o algarismo contido em contador 1
  displaysPositions.Update();
}
void ShowTime1(int number) {
  displayTime1.showNumberDec(number);
}
void ShowTime2(int number) {
  displayTime2.showNumberDec(number);
}
void ShowTime3(int number) {
  displayTime3.showNumberDec(number);
}

void ClearTimes() {
  displayTime1.clear();
  displayTime2.clear();
  displayTime3.clear();
  displaysPositions.Off(0);
  displaysPositions.Update();
}
