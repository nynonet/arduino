const int PinPiezo = A0;  //porta analógica com o piezo fio branco. e resitor ligado nele / gnd
const int PinPresenca = A1;  //porta analógica com o sensor de presença fio amarelo

int ReadingPiezo = 0;
int ReadingPresenca = 0;

long tempo = 0;
long timeStart = 0;
int timeCount = 0;
int timeRead = 1000;
void setup() {
  Serial.begin(9600);
}

void loop() {

  //lendo o valor do sensor de presença
  //  ReadingPresenca = analogRead(PinPresenca);
  ReadingPresenca = 11;

  if ( ReadingPresenca > 0 ) {
    // fazer leitura tem mão presente.

    if ( timeStart == 0 ) {
      timeStart = millis();
      timeCount = 0;
    }

    //lendo o valor do sensor piezo
    ReadingPiezo = analogRead(PinPiezo);
    tempo = millis() - timeStart;

    if (ReadingPiezo >= 10) {
      Serial.print("Tempo: ");
      Serial.print(tempo);

      Serial.print("  Count: ");
      Serial.print(timeCount);

      Serial.print("  Valor: ");
      Serial.println(ReadingPiezo);
     
      if ( tempo >= timeRead ) {
        timeCount += 1;
        timeStart = millis();
      }
      
      ReadingPiezo = 0;
    }


  } else {
    ReadingPiezo = 0;
    timeStart = 0;
    timeCount = 0;
  }




  //delay(500);  // delay to avoid overloading the serial port buffer

}

