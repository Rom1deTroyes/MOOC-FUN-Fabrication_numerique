/*
   WiFiClient-compteur
   créé par Laurent Toutain le 17 Mai 2016

   Ce code est en CC0 1.0 Universal
 */

#include <ESP8266WiFi.h>
#include "pass.h"


// valeurs pour le serveur Web
const char* host     = "api.tom.tools";

void setup() {
	// On débute la communication série
	Serial.begin(115200);

	Serial.print("Connexion au WiFi ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);    // On se connecte

	while (WiFi.status() != WL_CONNECTED) { // On attend
		delay(500);
		Serial.print(".");
	}

	Serial.println("");  // on affiche les paramètres
	Serial.println("WiFi connecté");
	Serial.print("Adresse IP du module ESP: ");
	Serial.println(WiFi.localIP());
	Serial.print("Adresse IP de la box : ");
	Serial.println(WiFi.gatewayIP());
}


void loop() {
	Serial.print("Connexion au serveur : ");
	Serial.println(host);

	// On se place dans le rôle ndu  client en utilisant WifiClient
	WiFiClient client;

	// le serveur Web attend tradionnellement sur le port 80
	const int httpPort = 80;

	// Si la connexio échoue ca sera pour la prochaine fois
	if (!client.connect(host, httpPort)) {
		Serial.println("connection failed");
		return;
	}


	// La connexion a réussie on forme le chemin
	String url = String("/hits/");

	Serial.print("demande URL: ");
	Serial.println(url);

	// On l'envoie au serveur sur plusieurs lignes
	// GET /hits/ HTTP/1.1
	// Hosts: api.tom.tools
	// Connection: close
	// 
	// La première ligne précise à la fin version du protocole attendu
	// La deuxième rappelle au serveur sous quel nom on l'appelle, en
	// effet, à une même adresse IP on peut avoire différents serveurs
	// repondant à des noms différents.
	// La troisième ligne indique que le serveur doit fermer la
	// connexion apres la réponse et ne pas attendre d'autres requêtes.
	client.print(String("GET ") + url + " HTTP/1.1\r\n" +
			"Host: " + host + "\r\n" +
			"Connection: close\r\n\r\n");

	// On attend 1 seconde
	delay(1000);

	// On lit les données reçues, s'il y en a
	while(client.available()){
		String line = client.readStringUntil('\r'); // découpe ligne par ligne
		Serial.print(line);
	}

	// plus de données
	Serial.println();
	Serial.println("connexion fermée");

	delay(30000);
}
