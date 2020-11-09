//Autor: Nicolas de Castro Silva
//Descrição: Código utilizado no arduino que controla a contagem regressiva instalada na largada da pista
//Componentes: Regulador de tensão de 5v 2A, 10 matrizes de led 8x8, arduino uno
//Resalvas: 
//1) As matrizes de LED consomem muita energia, por isso é recomendado usar uma fonte e um regulador de alta corrente
//caso queria aumentar a intesidade dos LEDs
//2) Para ser possivel ligar as 10 matrizes, foi feita uma ligação onde foram criadas duas linhas de matrizes, 5 matrizes em cada linha
//devido a limitação de 8 matrizes ligadas em série. A ligação feita pode ser vista no repositório do GitHub  

#include <MatrixCascade.h> //Biblioteca de controle das matrizes
#include <SoftwareSerial.h> //Biblioteca para comunicação com Arduino Central

SoftwareSerial mySerial(2, 3); //Declaração das portar 2(RX) e 3(TX) para comunicação serial com arduino central
String data = ""; //Variavel que armazenara as messasgens enviadas por serial

auto cascade = combineCascades(MatrixCascade<5>(7), MatrixCascade<5>(10)); //Declaração da matriz

void setup() {
  Serial.begin(9600); //Inicialização da comunicação serial com o PC
  mySerial.begin(9600); //Inicialização da comunicação serial com o Arduino Central

  delay(1000);//Espera para que as matrizes possam iniciar corretamente
  cascade.setIntensity(0);//Configura a intensidade dos LED(0 a 15),CUIDADO!!!! Aumentar a intensidade faz o consumo de energia aumentar drasticamente
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
  NerdyDerby();// Mostra Nerdy Derby na tela
}
void loop() {
  //Repetição responsavel por receber as mensagens via serial
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
  if (data.indexOf("start") != -1) {//Se receber "start", inicia a contagem regressiva
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

void Clear() { // Função que apaga todos so LEDS
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

void Bandeirada() {//Animação de bandeirada
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

void Show2() {//Mostra numero 2
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

void Show1() {//Mostra numero 1

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
void ShowGo() {//Escreve GO na tela


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

void Show3() { //Mostra numero 3
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

void NerdyDerby() {//Escreve Nerdy Derby nas matrizes
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
