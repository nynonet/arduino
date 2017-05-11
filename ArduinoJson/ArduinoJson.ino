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
int TempoParaEnvio = 3000; //a cada 3s segundos envia os dados

float valorTemp = 0;

void setup() {
 
  Serial.begin(9600); // para usar a leitura serial. 
  pinMode(ligado, OUTPUT); //para fazer um led piscar... 
}

void loop() {
 //liga ou desliga o led só de teste. 
 digitalWrite( ligado, !digitalRead(ligado) );
 
 valorTemp = random(-20, 50); //para gerar um valor aleatório. 

 //Gera os dados da temperatura pra enviar como JSON
 String temperatura = "{\"titulo\":\"Temperatura\", \"valor\":\""+ String(valorTemp) + "º\" }";
 
 //Gera os dados do led pra enviar como JSON  1 = ligado; 0 = desligado
 String ledligado = "{\"titulo\":\"Led Ligado?\", \"valor\":\""+ String(!digitalRead(ligado)) + "\" }";

 //Gera os dados do led pra enviar como JSON  1 = ligado; 0 = desligado
 String textoLivre = "{\"titulo\":\"Texto Livre\", \"valor\":\"Aqui posso também escrever um valor e enviar.\" }";

 
 //tempo para o proximo ciclo "envio".
 delay(TempoParaEnvio);

 //Montando o pacote no formato esperado, passando cada grupo de informação.
 //aqui pode colocar quantos grupos deseja. lembrando de colocar a "," entre cada grupo. 
 String pacoteJSON = "{\"Leitura\":["+ temperatura + ","+ ledligado +","+ textoLivre +"]}";

 //envia o comando..
 Serial.println( pacoteJSON );

}
