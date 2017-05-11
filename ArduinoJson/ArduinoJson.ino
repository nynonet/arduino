/*
  Autor: Andeson de Jesus de Menezes
  data: 10/05/2017

  Enviando dados do Arduino no formato Json para o Android.

  Exemplo de Json a ser enviado:

  {
    "Leituras":[
      {"titulo":"TEMPERATURA", "valor": "26º" },
      {"titulo":"MOTOR LIGADO?","valor": "SIM"}
     ]
  }

  essa é a estrutura caso precise enviar mais dados basta-se colocar
  mais uma linha de dados. exemplo:
 {
    "Leituras":[
      {"titulo":"TEMPERATURA", "valor": "26º" },
      {"titulo":"MOTOR LIGADO?","valor": "SIM"},
      {"titulo":"UMIDADE DO AR", "valor": "70%" }
     ]
  }

  Esse projeto é somente um exemplo de integraçõa, portanto os 
  dados de leitura serão ficticios e seus valores aleatórios.
  implemente conforme seu projeto. 
*/
int ligado = 13; //porta só para fazer o led piscar 
String comandoJson = ""; 
int TempoParaEnvio = 3000; //a cada 3s segundos envia os dados

float valorTemp = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // para usar a leitura serial. 
  pinMode(ligado, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite( ligado, !digitalRead(ligado) );
 
 valorTemp = random(1, 200);
 
 String tempertura = "{\"titulo\":\"Temperatura\", \"valor\":\""+ String(valorTemp) + "\" }";
 String ledligado = "{\"titulo\":\"Led Ligado?\", \"valor\":\""+ String(digitalRead(ligado)) + "\" }";
 delay(TempoParaEnvio);
 Serial.println( tempertura ); 
 Serial.println( ledligado ); 


}
