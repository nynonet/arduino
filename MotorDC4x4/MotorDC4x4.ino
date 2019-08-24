/*
  Andeson de Jesus de Menezes
  Data: 22/08/2019 
  Projeto controlar 4 Motores DC v6; 4x4

  Componentes:
    4 - Motores DC 6v;
    1 - Protoboard ;
    8 - Fios p/plugs macho/macho;
    
*/

int motorDDP = 13;   //motor Direito Dianteiro Positivo
int motorDDN = 12;   //motor Direito Dianteiro Negativo
int motorDTP = 11;   //motor Direito Traseiro Positivo
int motorDTN = 10;   //motor Direito Traseiro Negativo

int motorEDP = 9;   //motor Esquerdo Dianteiro Positivo
int motorEDN = 8;   //motor Esquerdo Dianteiro Negativo
int motorETP = 7;   //motor Esquerdo Traseiro Positivo
int motorETN = 6;   //motor Esquerdo Traseiro Negativo

void setup() {
  pinMode(motorDDP, OUTPUT); 
  pinMode(motorDDN, OUTPUT); 
  pinMode(motorDTP, OUTPUT);
  pinMode(motorDTN, OUTPUT);
  pinMode(motorEDP, OUTPUT);
  pinMode(motorEDN, OUTPUT);
  pinMode(motorETP, OUTPUT);
  pinMode(motorETN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  char s = Serial.read();

  if ( s == '0') {
    Serial.println("Parado");
    parar();
  }

  if ( s == '1') {
    Serial.println("Ir para frente");
    IrParaFrente();
  }

  if ( s == '2') {
    Serial.println("Ir para traz");
    IrParaTraz();
  }

  if ( s == '3') {
    Serial.println("Vira para Direita");
    VirarDireita();
  }

  if ( s == '4') {
    Serial.println("Vira para Esquerda");
    VirarEsquerda();
  }

  if ( s == '5') {
    Serial.println("Gira a Direita");
    GiraADireita();
  }
  
  if ( s == '6') {
    Serial.println("Gira a Esquerda");
    GiraAEsquerda();
  }
  
  
}

void parar() {
   //Manda para o motor Direito Dianteiro
  digitalWrite( motorDDP, LOW );
  digitalWrite( motorDDN, LOW );
  //Manda para o motor Direito Traseiro
  digitalWrite( motorDTP, LOW );
  digitalWrite( motorDTN, LOW );
  //Manda para o motor Esquerdo Dianteiro
  digitalWrite( motorEDP, LOW );
  digitalWrite( motorEDN, LOW );
  //Manda para o motor Esquerdo Traseiro
  digitalWrite( motorETP, LOW );
  digitalWrite( motorETN, LOW );
}

/**
 * Comando que faz os 4 motores ir p/Frete se movendo todos no mesmo sentido
 */
void IrParaFrente(){
  //Manda p/frete motor Direito Dianteiro
  digitalWrite( motorDDP, HIGH );
  digitalWrite( motorDDN, LOW );
  //Manda p/frete motor Direito Traseiro
  digitalWrite( motorDTP, HIGH );
  digitalWrite( motorDTN, LOW );

  //Manda p/frete motor Esquerdo Dianteiro
  digitalWrite( motorEDP, HIGH );
  digitalWrite( motorEDN, LOW );
  //Manda p/frete motor Esquerdo Traseiro
  digitalWrite( motorETP, HIGH );
  digitalWrite( motorETN, LOW );
}

/**
 * Comando que faz os 4 motores ir p/Traz se movendo todos no mesmo sentido
 */
void IrParaTraz(){
  //Manda p/Traz motor Direito Dianteiro
  digitalWrite( motorDDP, LOW );
  digitalWrite( motorDDN, HIGH );
  //Manda p/Traz motor Direito Traseiro
  digitalWrite( motorDTP, LOW );
  digitalWrite( motorDTN, HIGH );

  //Manda p/Traz motor Esquerdo Dianteiro
  digitalWrite( motorEDP, LOW );
  digitalWrite( motorEDN, HIGH );
  //Manda p/Traz motor Esquerdo Traseiro
  digitalWrite( motorETP, LOW );
  digitalWrite( motorETN, HIGH );
}

/**
 * Comando faz que os motores do lado direito parem e os do lado esquerdo
 * siga em frente o resultado é uma curva a direita
 */
void VirarDireita(){
  //Manda para o motor Direito Dianteiro
  digitalWrite( motorDDP, LOW );
  digitalWrite( motorDDN, LOW );
  //Manda para o motor Direito Traseiro
  digitalWrite( motorDTP, LOW );
  digitalWrite( motorDTN, LOW );

  //Manda p/Frente motor Esquerdo Dianteiro
  digitalWrite( motorEDP, HIGH );
  digitalWrite( motorEDN, LOW );
  //Manda p/Frente motor Esquerdo Traseiro
  digitalWrite( motorETP, HIGH );
  digitalWrite( motorETN, LOW );
}

/**
 * Comando faz que os motores do lado esquerdo parem e os do lado direito
 * siga em frente o resultado é uma curva a esquerda
 */
void VirarEsquerda(){
  //Manda p/Frente motor Direito Dianteiro
  digitalWrite( motorDDP, HIGH );
  digitalWrite( motorDDN, LOW );
  //Manda p/Frente motor Direito Traseiro
  digitalWrite( motorDTP, HIGH );
  digitalWrite( motorDTN, LOW );

  //Manda para o motor Esquerdo Dianteiro
  digitalWrite( motorEDP, LOW );
  digitalWrite( motorEDN, LOW );
  //Manda para o motor Esquerdo Traseiro
  digitalWrite( motorETP, LOW );
  digitalWrite( motorETN, LOW );
}


/**
 * Gira sobre o eixo para a direita. 
 */
void GiraADireita(){
  //Manda para o motor Direito Dianteiro
  digitalWrite( motorDDP, LOW );
  digitalWrite( motorDDN, HIGH );
  //Manda para o motor Direito Traseiro
  digitalWrite( motorDTP, LOW );
  digitalWrite( motorDTN, HIGH );

  //Manda p/Frente motor Esquerdo Dianteiro
  digitalWrite( motorEDP, HIGH );
  digitalWrite( motorEDN, LOW );
  //Manda p/Frente motor Esquerdo Traseiro
  digitalWrite( motorETP, HIGH );
  digitalWrite( motorETN, LOW );
}

/**
 * Gira sobre o eixo para a esquerda. 
 */
void GiraAEsquerda(){
  //Manda p/Frente motor Direito Dianteiro
  digitalWrite( motorDDP, HIGH );
  digitalWrite( motorDDN, LOW );
  //Manda p/Frente motor Direito Traseiro
  digitalWrite( motorDTP, HIGH );
  digitalWrite( motorDTN, LOW );

  //Manda para o motor Esquerdo Dianteiro
  digitalWrite( motorEDP, LOW );
  digitalWrite( motorEDN, HIGH );
  //Manda para o motor Esquerdo Traseiro
  digitalWrite( motorETP, LOW );
  digitalWrite( motorETN, HIGH );
}
