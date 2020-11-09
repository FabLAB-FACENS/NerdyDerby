#include <SoftwareSerial.h>
#include <SerialDisplay.h>
#include <TM1637Display.h>

TM1637Display displayTime3(9, 8);
TM1637Display displayTime2(11, 10);
TM1637Display displayTime1(13, 12);

SerialDisplay displaysPositions(7, 6, 3); // Dados, clock, numero de modulos

SoftwareSerial mySerial(2, 3);
String data = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  displayTime1.setBrightness(5);
  displayTime2.setBrightness(5);
  displayTime3.setBrightness(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (mySerial.available() > 0) {
    char character = mySerial.read();
    if (character != '\n') {
      data += character;
    }
    delay(10);
  }
  if (data.indexOf("result") != -1) { 
    Serial.println(data.substring(23, 27));
    ShowPosition(1, data[7]);
    ShowPosition(2, data[9]);
    ShowPosition(3, data[11]);
    ShowTime1(data.substring(13, 17).toInt());
    ShowTime2(data.substring(18, 22).toInt());
    ShowTime3(data.substring(23, 27).toInt());
    data = "";
  } else if (data.indexOf("reset") != -1) {
    Serial.println("Reset");
    ClearTimes();
    data = "";
  } else if (data.indexOf("start") != -1) {
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
