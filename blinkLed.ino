#include <SPI.h> //INCLUSÃO DE BIBLIOTECA
#include <Ethernet.h> //INCLUSÃO DE BIBLIOTECA

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //ATRIBUIÇÃO DE ENDEREÇO MAC AO ETHERNET SHIELD W5100
byte ip[] = { 192, 168, 0, 14 }; //COLOQUE UMA FAIX DE IP DISPONÍVEL DO SEU ROTEADOR. EX: 192.168.1.110  **** ISSO VARIA, NO MEU CASO É: 192.168.0.175
byte gateway[] = {192, 168, 0, 1}; //GATEWAY DE CONEXÃO (ALTERE PARA O GATEWAY DO SEU ROTEADOR)
byte subnet[] = {255, 255, 255, 0}; //MASCARA DE REDE (ALTERE PARA A SUA MÁSCARA DE REDE)
EthernetServer server(80); //PORTA EM QUE A CONEXÃO SERÁ FEITA

const int ledPin9 = 9; //PINO DIGITAL UTILIZADO PELO LED
const int ledPin8 = 8;
const int ledPin7 = 7;
String readString = String(30); //VARIÁVEL PARA BUSCAR DADOS NO ENDEREÇO (URL)
int status9 = 0, status8 = 0, status7 = 0; //DECLARAÇÃO DE VARIÁVEL DO TIPO INTEIRA(SERÁ RESPONSÁVEL POR VERIFICAR O status9 ATUAL DO LED)

void setup(){
  Ethernet.begin(mac, ip, gateway, subnet); //PASSA OS PARÂMETROS PARA A FUNÇÃO QUE VAI FAZER A CONEXÃO COM A REDE
  server.begin(); //INICIA O SERVIDOR PARA RECEBER DADOS NA PORTA 80
  pinMode(ledPin9, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(ledPin8, OUTPUT);
  pinMode(ledPin7, OUTPUT);
  digitalWrite(ledPin9, LOW); //LED INICIA DESLIGADO
  digitalWrite(ledPin8, LOW);
  digitalWrite(ledPin7, LOW);
  }
void loop(){
EthernetClient client = server.available(); //CRIA UMA CONEXÃO COM O CLIENTE
  if (client) { // SE EXISTE CLIENTE, FAZ
    while (client.connected()) {//ENQUANTO EXISTIR CLIENTE CONECTADO, FAZ
   if (client.available()) { //SE O CLIENTE ESTÁ HABILITADO, FAZ
    char c = client.read(); //LÊ CARACTERE A CARACTERE DA REQUISIÇÃO HTTP
    if (readString.length() < 100) //SE O ARRAY FOR MENOR QUE 100, FAZ
    {
        readString += c; // "readstring" VAI RECEBER OS CARACTERES LIDO
    }  
    if (c == '\n')  //SE ENCONTRAR "\n" É O FINAL DO CABEÇALHO DA REQUISIÇÃO HTTP
    {
        if (readString.indexOf("?") <0){ //SE ENCONTRAR O CARACTER "?", FAZ
        }
        else //SENÃO,FAZ
           if(readString.indexOf("led9Param=1") >0) //SE ENCONTRAR O PARÂMETRO "led9Param=1", FAZ
           {
             digitalWrite(ledPin9, HIGH); //LIGA O LED
             status9 = 1; //VARIÁVEL RECEBE VALOR 1(SIGNIFICA QUE O LED ESTÁ LIGADO)
           }else if(readString.indexOf("led9Param=0") >0){ //SENÃO, FAZ
             digitalWrite(ledPin9, LOW); //DESLIGA O LED
             status9 = 0; //VARIÁVEL RECEBE VALOR 0(SIGNIFICA QUE O LED ESTÁ DESLIGADO)             
           }else if(readString.indexOf("led8Param=1") >0) {
             digitalWrite(ledPin8, HIGH);
             status8 = 1; 
           }else if(readString.indexOf("led8Param=0") >0){
             digitalWrite(ledPin8, LOW);
             status8 = 0;
           }
           else if(readString.indexOf("led7Param=1") >0) {
             digitalWrite(ledPin7, HIGH);
             status7 = 1; 
           }else if(readString.indexOf("led7Param=0") >0){
             digitalWrite(ledPin7, LOW);
             status7 = 0;
           }
          client.println("HTTP/1.1 200 OK"); //ESCREVE PARA O CLIENTE A VERSÃO DO HTTP
          client.println("Content-Type: text/html"); //ESCREVE PARA O CLIENTE O TIPO DE CONTEÚDO(texto/html)
          client.println("");
          client.println("<!DOCTYPE HTML>"); //INFORMA AO NAVEGADOR A ESPECIFICAÇÃO DO HTML
          client.println("<html>"); //ABRE A TAG "html"
          client.println("<head>"); //ABRE A TAG "head"
          client.println("<link rel='icon' type='image/png' href='https://blogmasterwalkershop.com.br/arquivos/artigos/sub_wifi/logo_mws.png'/>"); //DEFINIÇÃO DO ICONE DA PÁGINA
          client.println("<title>IoT Grupo 6 - Controle de Led via Web server</title>"); //ESCREVE O TEXTO NA PÁGINA
          client.println("<style>");
          client.println("body {");
          client.println("background-image:url(https://m.media-amazon.com/images/I/71ZSwH5oRmL._AC_SX569_.jpg);");
          client.println("background-repeat: no-repeat;");
          client.println("}");
          client.println("#card {margin: 100px 0 0 500px;}");
          client.println("");
          client.println("}");
          client.println("</style>");
          client.println("</head>"); //FECHA A TAG "head"
          client.println("<body>"); //DEFINE A COR DE FUNDO DA PÁGINA
          client.println("<center><font color='black'><h1>Projeto Uno Black</font></center></h1>"); //ESCREVE "MASTERWALKER SHOP" EM COR AZUL NA PÁGINA
          client.println("<div id='card'>");
          client.println("<h1><center>CONTROLE DE LED</center></h1>"); //ESCREVE "CONTROLE DE LED" NA PÁGINA
          
          if (status9 == 1){ //SE VARIÁVEL FOR IGUAL A 1, FAZ
          //A LINHA ABAIXO CRIA UM FORMULÁRIO CONTENDO UMA ENTRADA INVISÍVEL(hidden) COM O PARÂMETRO DA URL E CRIA UM BOTÃO APAGAR (CASO O LED ESTEJA LIGADO)
          client.println("<center><form method=get name=LED><input type=hidden name=led9Param value=0 /><input type=submit value=APAGAR></form></center>");
          }
          else
          { //SENÃO, FAZ
          //A LINHA ABAIXO CRIA UM FORMULÁRIO CONTENDO UMA ENTRADA INVISÍVEL(hidden) COM O PARÂMETRO DA URL E CRIA UM BOTÃO ACENDER (CASO O LED ESTEJA DESLIGADO)
          client.println("<center><form method=get name=LED><input type=hidden name=led9Param value=1 /><input type=submit value=ACENDER></form></center>");
          }
          client.println("<center><font size='5'>Status atual do LED1: </center>"); //ESCREVE "Status atual do LED:" NA PÁGINA
          if (status9 == 1){ //SE VARIÁVEL FOR IGUAL A 1, FAZ
              client.println("<center><font color='green' size='5'>LIGADO</center>"); //ESCREVE "LIGADO" EM COR VERDE NA PÁGINA
          }else{ //SENÃO, FAZ
              client.println("<center><font color='red' size='5'>DESLIGADO</center>"); //ESCREVE "DESLIGADO" EM COR VERMELHA NA PÁGINA
          }     

          if (status8 == 1){
              client.println("<center><form method=get name=LED><input type=hidden name=led8Param value=0 /><input type=submit value=APAGAR></form></center>");
          }
          else{
              client.println("<center><form method=get name=LED><input type=hidden name=led8Param value=1 /><input type=submit value=ACENDER></form></center>");
          }
          
          client.println("<center><font color='black' size='5'>Status atual do LED2: </center>");
          
          if (status8 == 1){
              client.println("<center><font color='green' size='5'>LIGADO</center>");
          }
          else
          {
              client.println("<center><font color='red' size='5'>DESLIGADO</center>");
          }
               
          if (status7 == 1){
              client.println("<center><form method=get name=LED><input type=hidden name=led7Param value=0 /><input type=submit value=APAGAR></form></center>");
          }
          else
          {
              client.println("<center><form method=get name=LED><input type=hidden name=led7Param value=1 /><input type=submit value=ACENDER></form></center>");
          }
          
          client.println("<center><font color='black' size='5'>Status atual do LED3: </center>");
          
          if (status7 == 1)
          {
              client.println("<center><font color='green' size='5'>LIGADO</center>");
          }
          else
          {
              client.println("<center><font color='red' size='5'>DESLIGADO</center>");
          }     
          client.println("</div>");
          //client.println("<hr/>"); //TAG HTML QUE CRIA UMA LINHA HORIZONTAL NA PÁGINA
          //client.println("<hr/>"); //TAG HTML QUE CRIA UMA LINHA HORIZONTAL NA PÁGINA
          client.println("</body>"); //FECHA A TAG "body"
          client.println("</html>"); //FECHA A TAG "html"
          readString=""; //A VARIÁVEL É REINICIALIZADA
          client.stop(); //FINALIZA A REQUISIÇÃO HTTP E DESCONECTA O CLIENTE
            }
          }
        }
      }
 }
