/*
  LED RGB Arduino
  https://play.google.com/store/apps/details?id=net.nynonet 
  
  Por Andeson de Jesus de Menezes
  email: andeson@fasb.edu.br
  Twitter: @andeson_jm
*/

//Porta PWM utilizadas 
int R = 11; //Porta para a cor Vermelha "RED"
int G = 10; //Porta para a cor Verde    "Green"
int B = 9;  //Porta para o cor Azul     "Blue"

//variaveis de controle
char dados[1] ; //identificador de qual cor usar. 
char D; //cor a usar
int Pow = 0; //intecidade da cor, que vai de 0 a 255.


void setup() {
  Serial.begin(9600); //Conexão serial inicializada com taxa de 9600, vamos usar a mesma para se comunicar por bluetooh.
}

void loop() {

  if (Serial.available() > 0) { //verifica se há dados recebidos
    Serial.readBytes(dados, 1); //ler o 1 caracter 
    Pow = Serial.parseInt() ; //ler a potencia de 0 á 255, sendo 0 ligado 100% e 255 desligado.
    D = dados[0]; //Armazena o tipo de cor vai trabalhar.
  }

  if (D == 'R') {
    analogWrite(R, Pow); //controla a cor vermelha
  }

  if (D == 'G') {
    analogWrite(G, Pow); //controla a cor verde
  }
  if (D == 'B') {
    analogWrite(B, Pow); //controla a cor azul
  }

  D = '-'; //muda a letra para sair do loop de repetção.

}
