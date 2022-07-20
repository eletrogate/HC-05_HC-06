// Carrega a biblioteca SoftwareSerial
#include <SoftwareSerial.h>

int pushButton = 10; // pino que lerá o estado do botão
int led = 13;
int stateOfButton = 0;
int LastState = LOW;
char buf;

void setup(){
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  pinMode(led, OUTPUT);
  delay(1000);
}

void loop(){
  if (LastState != digitalRead(pushButton)){
    if (digitalRead(pushButton) == HIGH){
      Serial.println("Estado da chave = Ligado");
      LastState = HIGH;
    }else{
      Serial.println("Estado da chave = Desligado");
      LastState = LOW;
    }
  }
  verificaComandoCelular();
  delay(1000);
}

void verificaComandoCelular(){
  int watchDogCounter = 0;
  while(Serial.available() > 0){
    buf = Serial.read();
    
    // Caracter L para ligar o led
    Serial.println(buf);
    if (buf == 'L')
      digitalWrite(13, HIGH);

    // Caracter D para desligar o led
    if (buf == 'D')
      digitalWrite(13, LOW);

    // Se ficar mais de 5 segundos no loop, sai automaticamente
    delay(100);
    watchDogCounter++;
    if (watchDogCounter > 50)
      break;
  }
}

