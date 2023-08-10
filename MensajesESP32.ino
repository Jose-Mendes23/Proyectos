//Enviar un mensaje de WhatsApp desde ESP32 el isparador del mensaje es el Pulsador
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ProgramCounter";
const char* password = "23231225.A";
//COLOCAMOS EL TOKEN QUE NOS ENTREGA META
String token="Bearer EAAOMavsg6DIBOZBIXX0lQxTi5oLseXSBZC1Qrarxta3gtUvfq2EPkDTIzWTI1UMZC3UMDQpLQOLttxi6X73JaPkz4cX9DHNU9RhTGYgCV5Vgj7DnQZAt5F5IKwEXv4XZA0BNJYZCaVL3G1PYHK8JmsI1Cp2bnGCYO177JzzOGISN5FcD33jOkbuX2wljTPv0PtukxSTNf0F2ZA4qRvi8AZDZD";
//COLOCAMOS LA URL A DONDE SE ENVIAN LOS MENSAJES DE WHATSAPP
String servidor = "https://graph.facebook.com/v17.0/112715311917598/messages";
//CREAMOS UNA JSON DONDE SE COLOCA EL NUMERO DE TELEFONO Y EL MENSAJE
String payload = "{\"messaging_product\":\"whatsapp\",\"to\":\"584242580500\",\"type\":\"text\",\"text\": {\"body\": \"Se acaba de activar el circuito\"}}";

/////////////// PIN DEL PULSADOR ///////////////
int pinPulsador = 4;

//ESTADO DEL SENSOR
int pulsado = LOW;

void setup() {
  Serial.begin(9600);
  //ACTIVAMOS EL PIN SEL SENSOR DE MOVIMIENTO
  pinMode(pinPulsador, INPUT);

  //COLOCAMOS USUARIO Y CONTRASEÑA DE NUESTRA RED WIFI
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Se ha conectado al wifi con la ip: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //DETECTAMOS EL ESTADO DEL DETECTO DE OVIMIENTO
  pulsado = digitalRead(pinPulsador);
  //SI SE DETECTA MOVIMIENTO

  if (pulsado == HIGH) {
    Serial.println("Se acaba de pulsar el interruptor");
    //delay(5000);
    delay(50);

    if(WiFi.status()== WL_CONNECTED){
      //INICIAMOS EL OBJETO HTTP QUE POSTERIORMENTE ENVIARA EL MENSAJE
      HTTPClient http;
      //COLOCAMOS LA URL DEL SERVIDOR A DONDE SE ENVIARA EL MENSAJE
      http.begin(servidor.c_str());
      //COLOCAMOS LA CABECERA DONDE INDICAMOS QUE SERA TIPO JSON
      http.addHeader("Content-Type", "application/json"); 
      //AGREGAMOS EL TOKEN EN LA CABECERA DE LOS DATOS A ENVIAR
      http.addHeader("Authorization", token);    
      //ENVIAMOS LOS DATOS VIA POST
      int httpPostCode = http.POST(payload);
      //SI SE LOGRARON ENVIAR LOS DATOS

      if (httpPostCode > 0) {
        //RECIBIMOS LA RESPUESTA QUE NOS ENTREGA META
        int httpResponseCode = http.GET();
        //SI HAY RESPUESTA LA MOSTRAMOS
        if (httpResponseCode>0) {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          String payload = http.getString();
          Serial.println(payload);
        }
        else {
          Serial.print("Error code: ");
          Serial.println(httpResponseCode);
        }
      }
      http.end();
    }
    else {
      Serial.println("WiFi Desconectado");
    }
  }

  //delay(1000);
}