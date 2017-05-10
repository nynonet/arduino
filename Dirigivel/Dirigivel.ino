/*
  Controle para dirigivel uso no CIC 2017 FASB.
  Andeson de Jesus de Menezes
  10/05/2017

  Instruções:

  Usando a ponte H coloque:

  Motor A 
  pino 9 no positivo  
  pino 10 no negativo

  Motor B
  pino 11 no positivo
  pino 12 no negativo

  Agora alimente a ponte H com as voltagem de 5 ou 3.3 volts.
  e lige o pino negativo a placa.  

  Comandos para controle:
  1 - Move p/frete
  2 - Move p/traz
  3 - Move p/Direita
  4 - Move p/Esquerda
  5 - Para motor frete/traz
  6 - Para motor direita/esquerda
*/

//portas digitais

int frente = 9;
int traz = 10;
int direita = 11;
int esquerda = 12;

int comando = "0";

void setup() {
  // put your setup code here, to run once:
  pinMode(frente, OUTPUT);
  pinMode(traz, OUTPUT);
  pinMode(direita, OUTPUT); 
  pinMode(esquerda, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if ( Serial.available() ) {

      comando = Serial.parseInt(); //ler o comando do bluetooth
  }

  if ( comando == 1 ) {
    digitalWrite( frente, HIGH );
    digitalWrite( traz, LOW );
    Serial.println("Indo p/ frente");
  }

  if ( comando == 2 ) {
    digitalWrite( frente, LOW );
    digitalWrite( traz, HIGH );
    Serial.println("Indo p/ traz");
  }

  if ( comando == 3 ) {
    digitalWrite( direita, HIGH );
    digitalWrite( esquerda, LOW );
    Serial.println("Indo p/ direita");
  }

  if ( comando == 4 ) {
    digitalWrite( direita, LOW );
    digitalWrite( esquerda, HIGH );
    Serial.println("Indo p/ esquerda");
  }

  if ( comando == 5 ) {
    digitalWrite( frente, LOW );
    digitalWrite( traz, LOW );
    Serial.println("desligando os motores frente e traz ");
  }

  if ( comando == 6 ) {
    digitalWrite( direita, LOW );
    digitalWrite( esquerda, LOW );
    Serial.println("desligando os motores direito e esquerdo ");
  }
  
  comando = 0; //limpa o comando
}
