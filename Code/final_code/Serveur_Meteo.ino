#include <SoftwareSerial.h> 
const int tx = 14;
const int rx = 12;
SoftwareSerial MySerial(rx,tx);

String inputString ="";
String result[10];


//##################################//
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char *ssid = "Abracadabra-N";
const char *password = "blipblop";

WebServer server(80);

void handleRoot() {
  char caracteres[3500];
  
  String light = result[0];
  String pressure = result[1];
  String temp = result[2] ;
  String humidity = result[3];
  String wind = result[4];
  String girouette = result[5];
  String part_03 = result[6];
  String part_1 = result[7];
  String part_5 = result[8];
  String rad = result[9];
  
  snprintf(caracteres, 3500,
  
            "<html>\
  <head>\
    <meta charset = 'utf-8'>\
    <meta http-equiv='refresh' content='1'/>\
    <title>  Prévisions Météo </title>\
    <style>\ 
      h1 {text-align: center; color: navy; background-color: #cae8ec; border-top: solid 2px lightseagreen; border-bottom: solid 2px lightseagreen; border-right : solid 2px lightseagreen; border-left : solid 2px lightseagreen; margin-left : 300px; margin-right : 300px; padding: 20px;}\
      #intro {text-align : center;}\
      body {margin: auto; padding-left: 15px; padding-right: 15px;  border : 2px solid navy;margin : 15px;}\
      h2 {margin-top : 30px; color : rgb(11, 11, 126);text-align : center; border : 2px solid rgb(11, 11, 126); margin-left : 500px; margin-right : 500px;}\
      h3 {color : lightseagreen; text-decoration : underline;}\
      h4 {color : navy; text-align : center;}\
      .cols {float: left; width: 200px; margin-left: 50px; margin-right: 50px; margin-bottom : 75px; text-align : center; border : 2px solid lightseagreen; background-color :#d6ebee ; color: navy;}\
      .cols2 {float: left; width: 22%; margin-left: 17%; margin-right: 1%; margin-bottom: 75px; text-align: center; border: 2px solid lightgreen; background-color: #d6ebee; color: navy;}\
      #suite {clear: both;}\
    </style>\
  </head>\
  <body>\
    <h1> La météo du MétéoCube </h1>\
    <div id='intro'>\
      <p><i>Voici le site internet de notre projet. Il permet de recenser toutes les informations que l'on récolte en temps réel. </i></p>\
    </div>\
    <div id='informations'>\
      <h2> INFORMATIONS </h2>\
      <article class='cols'>\
        <h4>Température</h4>\
        <p>La température est de %s °C et l'humidité de %s pourcents</p>\
      </article>\
      <article class='cols'>\
        <h4>Pression</h4>\
        <p>La pression est de %s mb</p>\
      </article>\
      <article class='cols'>\
        <h4>Luminosité</h4>\
        <p>Aujourd'hui, il fait plutôt : \n %s </p>\
      </article>\
      <article class='cols'>\
        <h4>Vent</h4>\
        <p>La vitesse du vent est de %s m/s et son orientation est : %s </p>\
      </article>\
      <article class='cols'>\
        <h4>Qualité de l'air</h4>\
        <p>Particules de plus de 0.3um/0.1L: %s </p>\
        <p>Particules de plus de 1um/0.1L: %s </p>\
        <p>Particules de plus de 5um/0.1L: %s </p>\
      </article>\
      <article class='cols'>\
        <h4>Radioactivité</h4>\
        <p>Radiation détectée: %s uSv</p>\
      </article>\
    </div>\
    <div id='suite'>\
      <h3> Les modules </h3>\
      <p> Nous avons 4 'modules' différents. Il s'agit de capteurs permettant de récupérer : la température et l'humidité, la pression, un capteur de lumière, et un anémomètre, indiquant la vitesse et la direction du vent. </p>\
      <ol>\
        <li> Notre premier capteur est le capteur de température et d'humidité. </li>\
        <li> Notre second capteur est le capteur de pression. </li>\
        <li> Notre troisème capteur est le capteur de lumière.</li>\
        <li> Notre quatrième objet est l'anémomètre. </li>\
      </ol>\
      <h3> Les liens </h3>\
      <p> Voici les différentes sites web qui nous ont servis à réaliser notre projet (liste non-exhaustive): <a href='https://www.arduino.cc/'></a></p>\
      <h3> Les images du projet </h3>\
        <figure><img src=\'/test.png\' alt=\'Le MétéoCube\'/>\
          <figcaption>Voici notre projet</figcaption>\
        </figure>\
      </div>\
  </body>\
</html>",

    temp, humidity, pressure, light, wind, girouette, part_03 , part_1, part_5, rad

         );
  server.send(200, "text/html", caracteres);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

void setup(void) {
  MySerial.begin(4800);
  inputString.reserve(200);
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  waiting(); // on attend qu'il y ait qqc sur le pin rx
  readData();
  
  for(int j=0; j<10;j++){ // on imprime res
    Serial.println(result[j]);
  }
  Serial.println("###############################"); // marque la séparation entre chaque serie de mesures
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks

}
//#######################################

//#########################################
void waiting(){
  while(!MySerial.available()){ // tant qu'il n'y a rien a lire
    Serial.print(".0");
    delay(1000);
  }
  Serial.println(" ");
  Serial.println("Got a mesure");
}
//########################################
void readData() {
  while (MySerial.available()) {
    char inChar = (char)MySerial.read();
    if (inChar != '$') {
      inputString += inChar;
    }
    else{ // if  == $
      char indice = MySerial.read(); // on recolte l'indice de l'info
      int e = indice - '0'; //  technique illegale pour convertir un caractere en entier
      result[e] = inputString; // on ajoute la données dans le tableau resultat
      inputString = ""; // on vide la chaine
      }
  }
}
//#######################################
