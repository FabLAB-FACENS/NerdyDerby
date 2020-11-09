#include <MatrixCascade.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);
String data = "";

auto cascade = combineCascades(MatrixCascade<5>(7), MatrixCascade<5>(10));

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  delay(1000);
  cascade.setIntensity(0);
  cascade[0].setRotation(2);
  cascade[1].setRotation(2);
  cascade[2].setRotation(2);
  cascade[3].setRotation(2);
  cascade[4].setRotation(2);
  cascade[5].setRotation(2);
  cascade[6].setRotation(2);
  cascade[7].setRotation(2);
  cascade[8].setRotation(2);
  cascade[9].setRotation(2);
  NerdyDerby();
}
void loop() {
  while (mySerial.available() > 0) {
    char character = mySerial.read();
    if (character != '\n') {
      data += character;
    }
    delay(10);
  }
  if (data == "") {
    return;
  }
  if (data.indexOf("start") != -1) {
    Show3();
    delay(1000);
    Show2();
    delay(1000);
    Show1();
    delay(1000);
    ShowGo();
    delay(3000);
    for (int i = 0; i < 20; i++) {
      Bandeirada();
    }
    Clear();
    delay(3000);
    NerdyDerby();
  } else if (data.indexOf("stop") != -1) {
    Clear();
  } else if (data.indexOf("nerdy") != -1) {
    NerdyDerby();
  }
  data = "";

  //delay(1000);

}

void Clear() {
  for (int i = 0; i < 10; i++) {
    cascade[i].set({
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
    });
  }
}

void Bandeirada() {
  for (int i = 0; i < 10; i++) {
    cascade[i].set({
      0b00001111,
      0b00001111,
      0b00001111,
      0b00001111,
      0b11110000,
      0b11110000,
      0b11110000,
      0b11110000,
    });
  }
  delay(100);
  for (int i = 0; i < 10; i++) {
    cascade[i].set({
      0b10000111,
      0b10000111,
      0b10000111,
      0b10000111,
      0b01111000,
      0b01111000,
      0b01111000,
      0b01111000,
    });
  }
  delay(100);
  for (int i = 0; i < 10; i++) {
    cascade[i].set({
      0b11000011,
      0b11000011,
      0b11000011,
      0b11000011,
      0b00111100,
      0b00111100,
      0b00111100,
      0b00111100,
    });
  }
  delay(100);
  for (int i = 0; i < 10; i++) {
    cascade[i].set({
      0b11100001,
      0b11100001,
      0b11100001,
      0b11100001,
      0b00011110,
      0b00011110,
      0b00011110,
      0b00011110,
    });
  }
  delay(100);
  for (int i = 0; i < 10; i++) {
    cascade[i].set({
      0b11110000,
      0b11110000,
      0b11110000,
      0b11110000,
      0b00001111,
      0b00001111,
      0b00001111,
      0b00001111,
    });
  }
  delay(100);
  for (int i = 0; i < 10; i++) {
    cascade[i].set({
      0b01111000,
      0b01111000,
      0b01111000,
      0b01111000,
      0b10000111,
      0b10000111,
      0b10000111,
      0b10000111,
    });
  }
  delay(100);
  for (int i = 0; i < 10; i++) {
    cascade[i].set({
      0b00111100,
      0b00111100,
      0b00111100,
      0b00111100,
      0b11000011,
      0b11000011,
      0b11000011,
      0b11000011,
    });
  }
  delay(100);
  for (int i = 0; i < 10; i++) {
    cascade[i].set({
      0b00011110,
      0b00011110,
      0b00011110,
      0b00011110,
      0b11100001,
      0b11100001,
      0b11100001,
      0b11100001,
    });
  }
  delay(100);
}

void Show2() {
  cascade[2].set({
    0b00000000,
    0b00000000,
    0b01111111,
    0b01111111,
    0b00000011,
    0b00000011,
    0b00000011,
    0b01111111,
  });
  cascade[7].set({
    0b01111111,
    0b01100000,
    0b01100000,
    0b01100000,
    0b01111111,
    0b01111111,
    0b00000000,
    0b00000000,
  });
}

void Show1() {

  cascade[2].set({
    0b00000000,
    0b00000000,
    0b00111000,
    0b01111000,
    0b11011000,
    0b00011000,
    0b00011000,
    0b00011000,
  });

  cascade[7].set({
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b11111111,
    0b11111111,
    0b00000000,
    0b00000000,
  });
}
void ShowGo() {


  cascade[1].set({
    0b00000000,
    0b00000000,
    0b00001111,
    0b00001111,
    0b00001100,
    0b00001100,
    0b00001100,
    0b11101101,
  });

  cascade[2].set({
    0b00000000,
    0b00000000,
    0b11110111,
    0b11110111,
    0b00110110,
    0b00110110,
    0b00000110,
    0b11110110,
  });

  cascade[3].set({
    0b00000000,
    0b00000000,
    0b11111000,
    0b11111000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011011,
  });

  cascade[6].set({
    0b11101101,
    0b11101101,
    0b00001100,
    0b00001100,
    0b00001111,
    0b00001111,
    0b00000000,
    0b00000000,
  });
  cascade[7].set({
    0b11110110,
    0b10110110,
    0b00110110,
    0b00110110,
    0b11110111,
    0b11110111,
    0b00000000,
    0b00000000,
  });
  cascade[8].set({
    0b00011011,
    0b00011011,
    0b00011000,
    0b00011000,
    0b11111000,
    0b11111000,
    0b00000000,
    0b00000000,
  });
}

void Show3() {
  cascade[0].set({
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01111111,
  });

  cascade[1].set({
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b11111111,
  });

  cascade[2].set({
    0b00000000,
    0b00000000,
    0b01111111,
    0b01111111,
    0b00000011,
    0b00000011,
    0b00000011,
    0b00111111,
  });

  cascade[3].set({
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01111111,
  });

  cascade[4].set({
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b11111110,
  });

  cascade[5].set({
    0b01111111,
    0b01111111,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
  });
  cascade[6].set({
    0b11111111,
    0b11111111,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
  });
  cascade[7].set({
    0b00111111,
    0b00000011,
    0b00000011,
    0b00000011,
    0b01111111,
    0b01111111,
    0b00000000,
    0b00000000,
  });
  cascade[8].set({
    0b01111111,
    0b01111111,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
  });
  cascade[9].set({
    0b11111110,
    0b11111110,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
  });
}

void NerdyDerby() {
  cascade[0].set({
    0b01111110,
    0b01111110,
    0b01100110,
    0b01100110,
    0b01100110,
    0b01100110,
    0b01100110,
    0b01100110
  });
  cascade[1].set({
    0b01111110,
    0b01111110,
    0b01100110,
    0b01100110,
    0b01111110,
    0b01100000,
    0b01111110,
    0b01111110,
  });
  cascade[2].set({
    0b01111110,
    0b01111110,
    0b01100110,
    0b01100110,
    0b01100000,
    0b01100000,
    0b01100000,
    0b01100000,
  });
  cascade[3].set({
    0b00000110,
    0b00000110,
    0b01111110,
    0b01111110,
    0b01100110,
    0b01100110,
    0b01111110,
    0b01111110,
  });
  cascade[4].set({
    0b01100110,
    0b01100110,
    0b01100110,
    0b01111110,
    0b01111110,
    0b00000110,
    0b01111110,
    0b01111110,
  });
  cascade[5].set({
    0b00000000,
    0b01111100,
    0b01111110,
    0b01100110,
    0b01100110,
    0b01100110,
    0b01111110,
    0b01111100,
  });
  cascade[6].set({
    0b00000000,
    0b01111110,
    0b01111110,
    0b01100110,
    0b01111110,
    0b01100000,
    0b01111110,
    0b01111110,
  });
  cascade[7].set({
    0b00000000,
    0b01111110,
    0b01111110,
    0b01100110,
    0b01100110,
    0b01100000,
    0b01100000,
    0b01100000,
  });
  cascade[8].set({
    0b00000000,
    0b01100000,
    0b01100000,
    0b01111110,
    0b01111110,
    0b01100110,
    0b01111110,
    0b01111110,
  });
  cascade[9].set({
    0b00000000,
    0b01100110,
    0b01100110,
    0b01111110,
    0b01111110,
    0b00000110,
    0b01111110,
    0b01111110,
  });

}
