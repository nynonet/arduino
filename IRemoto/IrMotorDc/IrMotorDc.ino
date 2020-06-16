/**
 * Andeson de Jesus de Menezes
 * andeson@fasb.edu.br
 * Data: 23/11/2019
 * 
 * Controlar Motor DC por IR
 * 
 * Tecla 1 - Aciona os motores para ir p/frete
 * Tecla 2 - Aciona os motores para ir p/traz 
 * Tecla 4 - Aciona os motores para ir p/Direita 
 * Tecla 5 - Aciona os motores para ir p/Esqueda
 * Tecla 9 - Para todos os motores
 * 
 * Biblioteca do IRemote -> https://github.com/z3t0/Arduino-IRremote 
 */
#include <IRremote.h>

//Motor Direito
int motor_d_p = 3;  //Motor Direito Pino Positivo
int motor_d_n = 4;  //Motor Direito Pino Negativo

//Motor Esquedo
int motor_e_p = 6;  //Motor Esquerdo Pino Positivo
int motor_e_n = 7;  //Motor Esquerdo Pino Negativo


int RECV_PIN = 11;   //Pino do IR Sinal
float ValorIR;       //Valor recebido do Controle Remoto 

IRrecv irrecv(RECV_PIN); //Configura a porta que irá usar 
decode_results results;  //decodifica resultados 

void setup() {
  // Indica que todos os pinos dos motores são opção de Saída
  pinMode(motor_d_p, OUTPUT); 
  pinMode(motor_d_n, OUTPUT);
  pinMode(motor_e_p, OUTPUT);
  pinMode(motor_e_n, OUTPUT);
  
  Serial.begin(9600); // Abre comunicação serial para testar as leituras 
  
  irrecv.enableIRIn(); // Inicializa o receptor IR
}

void loop() {
  
  if (irrecv.decode(&results))    {
    Serial.print("Valor lido : ");
    Serial.println(results.value, HEX);
    ValorIR = (results.value);

    if (ValorIR == 0xFF30CF) //Verifica se a tecla 1 foi acionada
    {
      //Motor Direito p/frete
      digitalWrite(motor_d_p, HIGH);  
      digitalWrite(motor_d_n, LOW);  
      //Motor Esquerdo p/frete
      digitalWrite(motor_e_p, HIGH);  
      digitalWrite(motor_e_n, LOW);  
    }
    
    if (ValorIR == 0xFF18E7) //Verifica se a tecla 2 foi acionada
    {
      //Motor Direito p/traz
      digitalWrite(motor_d_p, LOW);  
      digitalWrite(motor_d_n, HIGH);  
      //Motor Esquerdo p/traz
      digitalWrite(motor_e_p, LOW);  
      digitalWrite(motor_e_n, HIGH);  
    }
    
    if (ValorIR == 0xFF10EF) //Verifica se a tecla 4 foi acionada
    { 
      //Motor Direito p/Direita
      digitalWrite(motor_d_p, HIGH);  
      digitalWrite(motor_d_n, LOW);  
      //Motor Esquerdo fica parado 
      digitalWrite(motor_e_p, LOW);  
      digitalWrite(motor_e_n, LOW);  
    }
    
    if (ValorIR == 0xFF38C7) //Verifica se a tecla 5 foi acionada
    { 
      //Motor Esquerdo p/Esquerda
      digitalWrite(motor_e_p, HIGH);  
      digitalWrite(motor_e_n, LOW);  
      //Motor Direito fica parado 
      digitalWrite(motor_d_p, LOW);  
      digitalWrite(motor_d_n, LOW);  
    }
    
    if (ValorIR == 0xFF52AD) //Verifica se a tecla 9 foi acionada
    { 
      //Motor Direito parado 
      digitalWrite(motor_d_p, LOW);  
      digitalWrite(motor_d_n, LOW);  
      //Motor Esquerdo parado
      digitalWrite(motor_e_p, LOW);  
      digitalWrite(motor_e_n, LOW);  
    }
    
    irrecv.resume(); //Le o próximo valor
  }

}
