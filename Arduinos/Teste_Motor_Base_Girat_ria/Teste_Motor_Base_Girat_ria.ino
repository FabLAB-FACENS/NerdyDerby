// Projeto Curto Circuito - A4988 & Arduino: Controle para motores Bipolar
//---- Pinos de controle A4988---
#define ENA 9 // Enable ativa os drivers do motor
#define MS1 8 // Seleciona a resolução do passo
#define MS2 7 // Seleciona a resolução do passo
#define MS3 6 // Seleciona a resolução do passo 
#define RST 5 // Desativa os drivers de saída
#define SLP 4 // Inicia um descanso para algumas funções do drive
#define STP 3 // Avanço do passo
#define DIR 2 // Direção do passo
//---- Variáveis de controle ----
int PPR = 0;      // pulsos por resolução
int passo = 0;    // passos
int temp = 0;  // tempo entre os passos

String data = "";
void setup()
{

  pinMode(ENA, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(STP, OUTPUT);
  pinMode(DIR, OUTPUT);
  digitalWrite(SLP, LOW);   // Sleep desabilitado
  digitalWrite(DIR, HIGH);  // Sentido Horário habilitado
  digitalWrite(RST, HIGH);  // RST habilitado
  Serial.begin(9600);
  half();
  //Serial.println("Pressione: r- para resetar // s - para iniciar Sleep // o - para desativar Sleep");
  //delay(100);
  //Serial.println("1 para FULL - STEP // 2 para HALF - STEP // 3 para Quarter - STEP // 4 para Eighth - STEP // 5 para Sixteenth - STEP");

}

void loop()
{
  while (Serial.available() > 0) {
    char character = Serial.read();
    if (character != '\n') {
      data += character;
    }
    delay(10);
  }

  if (data.indexOf("voltah") != -1) {
    voltaH();
  }else if(data.indexOf("voltaah") != -1){
     voltaAH();
  } else if (data.indexOf("1") != -1) {

  } else if (data.indexOf("1") != -1) {
    Serial.println("Full");
    full();
  } else if (data.indexOf("2") != -1) {
    Serial.println("Half");
    half();
  } else if (data.indexOf("3") != -1) {
    Serial.println("1 / 4");
    quarter();
  } else if (data.indexOf("4") != -1) {
    Serial.println("1 / 8");
    eighth();
  } else if (data.indexOf("5") != -1) {
    Serial.println("1 / 16");
    sixteenth();
  } else if (data.indexOf("reset") != -1) {
    Serial.println("Iniciar Reset");
    rst();
  } else if (data.indexOf("sleepOn") != -1) {
    Serial.println("Iniciar Sleep");
    Sleepon();
  } else if (data.indexOf("sleepOff") != -1) {
    Serial.println("Desligar Sleep");
    Sleepoff();
  }

}
void full()
{
  PPR = 200;
  temp = 100;
  Serial.println("Modo Passo Completo (Full - Step)");
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);
}
void half()
{
  PPR = 400;
  temp = 50;
  Serial.println("Modo Meio Passo(Half - Step)");
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);
}
void quarter()
{
  PPR = 800;
  temp = 25;
  Serial.println("Modo Quarter - STEP (1 / 4)");
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, LOW);
}
void eighth()
{
  PPR = 1600;
  temp = 12;
  Serial.println("Modo Eighth - STEP (1 / 8)");
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, LOW);
}
void sixteenth()
{ // Em sixteenth - 3200 passos
  PPR = 3200;
  temp = 6;
  Serial.println("Modo Sixteenth - STEP (1 / 16)");
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, HIGH);
}
void voltaH() {
  digitalWrite(11, HIGH); //LED-02-Vermelho
  ena();
  HR();  // Inicia o sentido horário
  while (PPR > passo)
  { // Enquanto PPR for maior que passo
    // Avança o passo
    digitalWrite(STP, LOW);
    delay(temp); //Tempo em Microseconds
    digitalWrite(STP, HIGH);
    delay(temp);
    passo++; // Aumenta em 1 o valor de passo
  }
  passo = 0; // valor de passso muda pra 0
  ena2();
  digitalWrite(11, LOW); //LED-02-Vermelho
}

void voltaAH() {
  digitalWrite(10, HIGH); //LED-02-Azul
  ena();
  AH();      // Inicia o Sentido Anti-horário
  while (PPR > passo)
  { // Enquanto PPR for maior que passo
    // Avança o passo
    digitalWrite(10, HIGH); //LED-02-Azul
    digitalWrite(STP, LOW);
    delay(temp);
    digitalWrite(STP, HIGH);
    delay(temp);
    passo++;
  }
  passo = 0;
  ena2();
  digitalWrite(10, LOW); //LED-02-Azul
}

void ena2() {
  digitalWrite(ENA, HIGH);  // Ativa o A4988
  delay(10);
}
void ena() {
  digitalWrite(ENA, LOW);   // Desativa o A4988
  delay(10);
}
void HR() {                // Sentido Horário
  passo = 0;
  Serial.println("Sentido - Horario");
  digitalWrite(DIR, HIGH);
}
void AH()  {               // Sentido Anti-Horário
  passo = 0;
  Serial.println("Sentido - Anti-horario");
  digitalWrite(DIR, LOW);
}
void rst()  {      // Reseta os drivers
  digitalWrite(RST, LOW);
  delay(10);
  digitalWrite(RST, HIGH);
  delay(10);
  Serial.println("Reset OK");
}
void Sleepoff()  {   // Desativa o modo Sleep
  Serial.println("Sleep off");
  digitalWrite(SLP, LOW);
  delay(10);
}
void Sleepon()  {   // Ativa o modo Sleep
  Serial.println("Sleep on");
  digitalWrite(SLP, HIGH);
  delay(10);
}