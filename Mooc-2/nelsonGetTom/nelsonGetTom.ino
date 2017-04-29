/*
   MOOC Fabriquer un objet connecté : semaine 3

   Faire une requête GET sur l'API Tom

   Le montage :
 * Juste un ESP

 créé le 24 Mai 2016
 par Baptiste Gaultier

 Ce code est en CC0 1.0 Universal

 */

#include <ESP8266WiFi.h>

#include "pass.h"
//const char* ssid     = "";
//const char* password = "";

const char* host = "api.tom.tools";
const char* nelsonName = "monnelson";

void setup() {
	Serial.begin(115200);
	delay(10);

	// connexion au wifi
	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("WiFi connected");  
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}

void loop() {
	Serial.print("connecting to ");
	Serial.println(host);

	// on utilise la classe WiFiClient pour gérer les connexions avec Tom
	WiFiClient client;
	const int httpPort = 80;
	if (!client.connect(host, httpPort)) {
		Serial.println("connection failed");
		return;
	}

	// We now create a URI for the request
	String url = "/nelsons/";
	url += nelsonName;
	url += "/?format=json";

	Serial.print("Requesting URL: ");
	Serial.println(url);

	// on envoie la demande au serveur
	client.print(String("GET ") + url + " HTTP/1.1\r\n" +
			"Host: " + host + "\r\n" + 
			"Connection: close\r\n\r\n");
	unsigned long timeout = millis();
	while (client.available() == 0) {
		if (millis() - timeout > 5000) {
			Serial.println(">>> Client Timeout !");
			client.stop();
			return;
		}
	}

	// on affiche toute la réponse du serveur ligne par ligne dans le moniteur série
	while(client.available()){
		String line = client.readStringUntil('\r');
		Serial.print(line);
	}

	Serial.println();
	Serial.println("closing connection");

	// on attend un peu pour ne pas écrouler Tom
	delay(5000);
}
