//NERDY DERBY SYSTEM by NICOLAS CASTRO

#include <SoftwareSerial.h> //Biblioteca que habilita a utilização de comunicação serial entre arduinos
#include <Servo.h> //Biblioteca que habilita a utilização do servomotor

SoftwareSerial placar(3, 2);//declaração da instancia software serial que se comunica com o arduino do placar(chegada)
SoftwareSerial contagem(5, 4);//declaração da instancia sofware serial que se comunica com o ardunino da contagem regressiva(largada)

#define servoPin 6//Definição da porta de saida que controla os servos
Servo servo;//declaração da instancia que controla os servos

//Sensores
#define track1Sensor A1 //Porta de controle da pista 1
#define track2Sensor A0 //Porta de controle da pista 2
#define track3Sensor A2 //Porta de controle da pista 3

String data = ""; //variavel que recebe as mensagens enviadas pelo computador

long startTime; //Momento em que a corrida começou

long timeTrack1 = -1;//Tempo que o carrinho levou para percorrer a pista 1
long timeTrack2 = -1;//Tempo que o carrinho levou para percorrer a pista 2
long timeTrack3 = -1;//Tempo que o carrinho levou para percorrer a pista 3

long resetTimer = 0;

bool racing1 = false;//Flag que indica se há um carrinho na pista 1
bool racing2 = false;//Flag que indica se há um carrinho na pista 2
bool racing3 = false;//Flag que indica se há um carrinho na pista 3

bool racing = false;//Flag que indica que a corrida está acontecendo

int posicao = 0; //Contador da posição

int pospista1;//Posição na pista 1
int pospista2;//Posição na pista 2
int pospista3;//Posição na pista 3

int timepista1;//Tempo da pista1
int timepista2;//Tempo da pista2
int timepista3;//Tempo da pista3

void setup() {



  placar.begin(9600);//Inicializa a comunicação serial com o arduino do placar(chegada)
  contagem.begin(9600);//Inicializa a comunicação serial com o arduino da contagem(largada)
  Serial.begin(9600);//Inicializa a comunicação serial com o PC

  servo.attach(servoPin);//Inicializa o Servo Motor
  servo.write(0);//Define a posição inicial do servo

  pinMode(track1Sensor, INPUT);//Define o pino do sensor da pista 1 como entrada
  pinMode(track2Sensor, INPUT);//Define o pino do sensor da pista 2 como entrada
  pinMode(track3Sensor, INPUT);//Define o pino do sensor da pista 3 como entrada
}
void loop() {
  ReadSerial(); //Função responsável por tratar as entradas de mensagem do computador
  RaceControl();//Controle da corrida
}
void ReadSerial() {
  //Loop que recebe as mensagens do computador
  while (Serial.available() > 0) {
    char character = Serial.read();
    if (character != '\n') {
      data += character;
    }
    delay(10);
  }
  if (data == "") {
    return;
  }
  //Função que inicia a corrida
  if (data.indexOf("RACE") != -1) {
    //Serial.println("Race Start");
    StartRace();
  } else if (data.indexOf("STOP") != -1) {//Função que para a corrida
    //Serial.println("Race Stop");
    StopRace();
  } else if (data.indexOf("test") != -1) {//Função de teste dos servos
    for (int i = 0; i < 100; i++) {
      racing1 = true;
      racing2 = true;
      racing3 = true;
      StartRace();
      delay(2000);
      StopRace();
      delay(5000);
    }
  } else if (data.indexOf("add") != -1) {//Função que habilita a contagem de tempo em uma das pistas
    placar.write("reset");
    if  (data.indexOf("0") != -1) {
      timeTrack1 = 0;
      racing1 = true;
    }
    if (data.indexOf("1") != -1) {
      timeTrack2 = 0;
      racing2 = true;
    }
    if (data.indexOf("2") != -1) {
      timeTrack3 = 0;
      racing3 = true;
    }
  }
  else if (data.indexOf("rmv") != -1) {//Função que desabilita a contagem de tempo em uma das pistas
    if (data.indexOf("0") != -1) {
      racing1 = false;
      timeTrack1 = -1;
    }
    if (data.indexOf("1") != -1) {
      racing2 = false;
      timeTrack2 = -1;
    }
    if (data.indexOf("2") != -1) {
      racing3 = false;
      timeTrack3 = -1;
    }
  } else if (data.indexOf("TEST") != -1) {
    delay(1000);
    Serial.println  ("OK");
  }

  data = "";
}

void StartRace() {
  placar.write("start");//Inicia a contagem regressiva nos displays da chegada
  contagem.write("start");//Inicia a contagem regressiva no display da largada
  delay(3000);
  racing = true;//Habilita a contagem de tempo geral
  pospista1 = 0;
  pospista2 = 0;
  pospista3 = 0;
  posicao = 0;
  servo.write(160);//Altera a posição do servo
  startTime = millis();//registra o instante em que a corrida começou
}
void RaceControl() {
  if (racing) {
    if (racing1) {
      if (analogRead(track1Sensor) < 1) {
        timeTrack1 = millis();// Registra o horario que o corredor passou pelo sensor
        racing1 = false;
        pospista1 = ++posicao;//Seta a posição na pista 1
      }
    }
    if (racing2) {
      if (analogRead(track2Sensor) < 1) {
        timeTrack2 = millis();// Registra o horario que o corredor passou pelo sensor
        racing2 = false;
        pospista2 = ++posicao;//Seta a posição na pista 2
      }
    }
    if (racing3) {
      if (analogRead(track3Sensor) < 1) {
        timeTrack3 = millis();// Registra o horario que o corredor passou pelo sensor
        racing3 = false;
        pospista3 = ++posicao;//Seta a posição na pista 3
      }
    }
    if (racing1 == false && racing2 == false && racing3 == false) {
      racing = false;
      StopRace();
    }
  }
}
void StopRace() {//Função que para a corrida
  if (timeTrack1 >= 0) {
    if (timeTrack1 == 0) {//Se o tempo for igual zero, o tempo é setado em 9999
      timeTrack1 = 9999;
      racing1 = false;
    } else {//Se não o horario que o corredor passo pelo sensor é subtraido pelo hoario que a corrida começou
      timeTrack1 = timeTrack1 - startTime;//Calcula o tempo do corredor
    }
    //Montagem da String que vai para o computador
    data = "track0: ";
    data += timeTrack1;
    Serial.println(data);//Envia o tempo para o computador
  }
  if (timeTrack2 >= 0) {//Se o tempo for igual zero, o tempo é setado em 9999
    if (timeTrack2 == 0) {
      timeTrack2 = 9999;
      racing2 = false;
    } else {//Se não o horario que o corredor passo pelo sensor é subtraido pelo hoario que a corrida começou
      timeTrack2 = timeTrack2 - startTime;//Calcula o tempo do corredor
    }
    //Montagem da String que vai para o computador
    data = "track1: ";
    data += timeTrack2;
    Serial.println(data);//Envia o tempo para o computador
  }
  if (timeTrack3 >= 0) {//Se o tempo for igual zero, o tempo é setado em 9999
    if (timeTrack3 == 0) {
      timeTrack3 = 9999;
      racing3 = false;
    } else {//Se não o horario que o corredor passo pelo sensor é subtraido pelo hoario que a corrida começou
      timeTrack3 = timeTrack3 - startTime;//Calcula o tempo do corredor
    }
    //Montagem da String que vai para o computador
    data = "track2: ";
    data += timeTrack3;
    Serial.println(data);//Envia o tempo para o computador
  }
  servo.write(0);//Reseta a posição do servo
  racing = false;

  //Montagem da string que é enviada para o placar
  String resultadoplacar = "result ";
  resultadoplacar += pospista1;
  resultadoplacar += " ";
  resultadoplacar += pospista2;
  resultadoplacar += " ";
  resultadoplacar += pospista3;
  resultadoplacar += " ";
  resultadoplacar += timeTrack1;
  resultadoplacar += " ";
  resultadoplacar += timeTrack2;
  resultadoplacar += " ";
  resultadoplacar += timeTrack3;
  timeTrack1 = -1;
  timeTrack2 = -1;
  timeTrack3 = -1;
  pospista1 = 0;
  pospista2 = 0;
  pospista3 = 0;
  posicao = 0;
  placar.print(resultadoplacar);
}
