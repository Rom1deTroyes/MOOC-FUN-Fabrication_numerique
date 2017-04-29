/*
   MOOC Fabriquer un objet connecté : semaine 3

   Lit la valeur analogique du servo moteur sur la broche A0 et envoie
   cette valeur sur la plateforme TOM en utilisant une requête PATCH
   Toutes les 3 secondes, nous récupérons la valeur sur TOM afin de voir si le
   servo a bougé

   Le montage :
 * Un servo moteur branché sur les broches 3V3, GND et D1
 * La patte retour d'information du servo est branchée sur la broche A0

 créé le 30 Mars 2016
 par Laurent Mattlé et Baptiste Gaultier
 modifié le 18 avril 2017
 par Baptiste Gaultier

 Ce code est en CC0 1.0 Universal

 */
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

#include <Servo.h>

// création de l'objet servo issu du moule Servo
Servo myservo;

// déclaration d'une variable payload dont on va se servir pour
// l'envoie et la réception de nos messages JSON
String payload;

// initialisation des constantes spécifiques à votre installation
// n'oubliez pas d'effacer vos identifiants wifi et nelson lors du dépôt de votre TP
#include "pass.h"
//const String nelsonName = "";
//const char* ssid = "";
//const char* password = "";

// initialise deux variables entières :

// pos contient la valeur actuelle de notre servo
int pos = 0;
// lastPos contient la valeur de notre servo lors du dernier tour de boucle
int lastPos = 0;

// tolerance permet d'avoir une approximation du feeback entre deux tours
// de boucle
int tolerance = 2;

void setup() {
	// on souhaite communiquer avec l'ordinateur
	Serial.begin(9600);
	Serial.setDebugOutput(true);

	Serial.println("Nelson v0.3 PATCH starting...");

	for(uint8_t t = 4; t > 0; t--) {
		Serial.printf("[SETUP] WAIT %d...\n", t);
		Serial.flush();
		delay(1000);
	}

	// on se connecte au Wifi
	WiFiMulti.addAP(ssid, password);

}

void loop() {
	// on regarde si on est bien connecté au point d'accès wifi
	if((WiFiMulti.run() == WL_CONNECTED)) {
		// création d'un objet appelé http réutilisable et sorti du moule HTTPClient
		HTTPClient http;

		// on se connecte à notre serveur...
		Serial.println("[HTTP] begin...");

		// on construit l'uri qui doit contenir le nom de notre nelson
		String uri = "/nelsons/" + nelsonName + "/";

		// et on se connecte sur le port HTTP qui est traditionnellement le port 80
		http.begin("api.tom.tools", 80, uri);

		Serial.println("[HTTP] GET...");    
		// démarrer la connexion et envoyer les entêtes HTTP
		// ces entêtes sont là pour dire que nous envoyons des données au format JSON
		http.addHeader("Content-type", "application/json");

		// Maintenant, nous cherchons à faire une requête GET
		int httpCode = http.GET();

		// httpCode sera négatif si on rencontre une erreur
		if(httpCode > 0) {
			// les entêtes HTTP ont été envoyés et nous n'avons pas rencontré d'erreur
			Serial.printf("[HTTP] GET... code: %d\n", httpCode);

			// si le serveur TOM répond par OK
			if(httpCode == HTTP_CODE_OK) {
				// alors on récupère la réponse sous forme de chaîne de caractères
				String payload = http.getString();
				Serial.println("[HTTP] GET... payload:");
				// on affiche ici la réponse reçue par le serveur
				Serial.println(payload);

				// dans le JSON reçu par le serveur
				// on s'intéresse à l'élément position qui contient un nombre entier
				// que l'on vient extraire ci-dessous
				int start = payload.indexOf("position\":");
				int end = payload.indexOf(',', start + 1 );
				String positionString = "";
				for (int i= start + 10; i < end; i++)
					positionString += payload.charAt(i);

				// on récupère la valeur de position et on la stocke dans la variable pos 
				pos = positionString.toInt();

				// nous écrivons ensuite cette valeur sur le servo
				myservo.attach(D1);
				myservo.write(pos);
				delay(500);
				myservo.detach();
			}
		}
		// attention, si la connexion HTTP échoue, on affiche le problème rencontré sur le port série
		else
			Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());

		// dans tous les cas, nous devons fermer la connexion HTTP avec http.end()
		http.end();

		// et nous n'oublions pas de relâcher le servo afin de pouvoir le manipuler
		int pos = map(analogRead(A0), 0, 1023, 0, 179);

		// on attend trois secondes avant la prochaine requête
		delay(3000);

		// on regarde à nouveau si le servo n'a pas bougé
		int lastPos = map(analogRead(A0), 0, 1023, 0, 179);

		Serial.print("pos:");
		Serial.println(pos);
		Serial.print("last:");
		Serial.println(lastPos);

		// le code ci-dessous permet d'envoyer une requête PATCH à TOM
		// uniquement si quelqu'un a manipulé le servo

		// on regarde si le servo a bougé depuis le dernier tour de boucle
		if(abs(pos - lastPos) > tolerance) {
			// si le servo a bougé alors on envoie à Tom une requête PATCH
			Serial.println("[HTTP] PATCH...");

			// cette requête contient du JSON avec la valeur courante mesurée par le servo
			String payload = "{\"position\":";
			payload += String(lastPos);
			payload += "}";

			Serial.print("[HTTP] PATCH... payload:");
			Serial.println(payload);

			// démarrer la connexion et envoyer les entêtes HTTP
			http.addHeader("Content-type", "application/json");
			httpCode = http.sendRequest("PATCH", (uint8_t *) payload.c_str(), payload.length());

			// httpCode sera négatif si on rencontre une erreur
			if(httpCode > 0) {
				// les entêtes HTTP ont été envoyés et on affiche la réponse du serveur
				Serial.printf("[HTTP] PATCH... code: %d\n", httpCode);

				// si le serveur TOM répond par OK
				if(httpCode == HTTP_CODE_OK)
					Serial.println("[HTTP] PATCH... OK!");
			}
			// attention, si la connexion HTTP échoue, on affiche le problème rencontré sur le port série
			else
				Serial.printf("[HTTP] PATCH... failed, error: %s\n", http.errorToString(httpCode).c_str());

			// dans tous les cas, nous devons fermer la connexion HTTP avec http.end()
			http.end();
		}
	}
}
