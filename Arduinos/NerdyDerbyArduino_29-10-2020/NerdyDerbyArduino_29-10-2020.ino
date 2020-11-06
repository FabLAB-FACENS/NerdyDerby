//NERDY DERBY SYSTEM by NICOLAS CASTRO
//#include <SerialDisplay.h> //Inclui a biblioteca Display Serial
//SerialDisplay displays(4, 5, 3); // Dados, clock, numero de modulos

#include <SoftwareSerial.h>

SoftwareSerial placar(2, 3);
SoftwareSerial contagem(4, 5);

#include <Servo.h>
#define servoPin 8
Servo servo;

//Sensores
//GND Verde
//VCC Azul
#define track1Sensor A1 //Cinza
#define track2Sensor A0 //Amarelo
#define track3Sensor A2 //Roxo
String data = "";
long startTime;
long timeTrack1 = -1;
long timeTrack2 = -1;
long timeTrack3 = -1;
long resetTimer = 0;
bool racing1 = false;
bool racing2 = false;
bool racing3 = false;
bool racing = false;
int track1DefaultValue;
int track2DefaultValue;
int track3DefaultValue;
int posicao = 0;
int pospista1;
int pospista2;
int pospista3;
int timepista1;
int timepista2;
int timepista3;

void setup() {
  placar.begin(9600);
  contagem.begin(9600);
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  //   track1DefaultValue = analogRead(track1Sensor);
  //   track2DefaultValue = analogRead(track2Sensor);
  //  track3DefaultValue = analogRead(track3Sensor);

  servo.attach(servoPin);
  servo.write(0);

  pinMode(track1Sensor, INPUT);
  pinMode(track2Sensor, INPUT);
  pinMode(track3Sensor, INPUT);
}
void loop() {
  ReadSerial();
  RaceControl();

  //    Serial.print(analogRead(track1Sensor));
  //    Serial.print(" ");
  //    Serial.print(analogRead(track2Sensor));
  //    Serial.print(" ");
  //    Serial.print(analogRead(track3Sensor));
  //    Serial.println();
}
void ReadSerial() {
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
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  if (data.indexOf("RACE") != -1) {
    Serial.println("Race Start");
    StartRace();
  } else if (data.indexOf("STOP") != -1) {
    //Serial.println("Race Stop");
    StopRace();
  } else if (data.indexOf("test") != -1) {
    for (int i = 0; i < 100; i++) {
      Serial.println("TESTE");
      racing1 = true;
      racing2 = true;
      racing3 = true;
      StartRace();
      delay(2000);
      StopRace();
      delay(5000);
    }
  } else if (data.indexOf("add") != -1) {
    if  (data.indexOf("0") != -1) {
      timeTrack1 = 0;
      racing1 = true;
      Serial.println("Racer 1 Add");

      placar.write("reset");
    }
    if (data.indexOf("1") != -1) {
      timeTrack2 = 0;
      racing2 = true;
      Serial.println("Racer 2 Add");
      placar.write("reset");
    }
    if (data.indexOf("2") != -1) {
      timeTrack3 = 0;
      racing3 = true;
      Serial.println("Racer 3 Add");
      placar.write("reset");
    }
  }
  else if (data.indexOf("rmv") != -1) {
    if (data.indexOf("0") != -1) {
      racing1 = false;
      timeTrack1 = -1;
      //Serial.println("Racer 1 rvm");
    }
    if (data.indexOf("1") != -1) {
      racing2 = false;
      timeTrack2 = -1;
      //Serial.println("Racer 2 rmv");
    }
    if (data.indexOf("2") != -1) {
      racing3 = false;
      timeTrack3 = -1;
      //Serial.println("Racer 3 rmv");
    }
  }
  data = "";
}
void StartRace() {
  //placar.write("reset");
  placar.write("start");
  contagem.write("start");
  delay(3000);
  servo.write(160);
  startTime = millis();
  racing = true;
  pospista1 = 0;
  pospista2 = 0;
  pospista3 = 0;
  posicao = 0;
}
void RaceControl() {
  if (racing) {
    if (racing1) {
      if (analogRead(track1Sensor) < 1) {
        timeTrack1 = millis();
        racing1 = false;
        pospista1 = ++posicao;
        //ShowPosition(1, ++posicao);
      }
    }
    if (racing2) {
      if (analogRead(track2Sensor) < 1) {
        timeTrack2 = millis();
        racing2 = false;
        pospista2 = ++posicao;
        //ShowPosition(2, ++posicao);
      }
    }
    if (racing3) {
      if (analogRead(track3Sensor) < 1) {
        timeTrack3 = millis();
        racing3 = false;
        pospista3 = ++posicao;
        //ShowPosition(3, ++posicao);
      }
    }
    if (racing1 == false && racing2 == false && racing3 == false) {
      racing = false;
      StopRace();
    }
  }
}
void StopRace() {
  //Serial.println("Stop Race");
  if (timeTrack1 >= 0) {
    if (timeTrack1 == 0) {
      timeTrack1 = 9999;
      racing1 = false;
    } else {
      timeTrack1 = timeTrack1 - startTime;
    }
    data = "track0: ";
    data += timeTrack1;
    Serial.println(data);
  }
  if (timeTrack2 >= 0) {
    if (timeTrack2 == 0) {
      timeTrack2 = 9999;
      racing2 = false;
    } else {
      timeTrack2 = timeTrack2 - startTime;
    }
    data = "track1: ";
    data += timeTrack2;
    Serial.println(data);
  }
  if (timeTrack3 >= 0) {
    if (timeTrack3 == 0) {
      timeTrack3 = 9999;
      racing3 = false;
    } else {
      timeTrack3 = timeTrack3 - startTime;
    }
    data = "track2: ";
    data += timeTrack3;
    Serial.println(data);
  }

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
  servo.write(0);
  racing = false;
  placar.print(resultadoplacar);
}
void ShowPosition(int track, int number) {
  //displays.Print(number, track); // E impresso no display 2 o algarismo contido em contador 1
  //displays.Update();
}
