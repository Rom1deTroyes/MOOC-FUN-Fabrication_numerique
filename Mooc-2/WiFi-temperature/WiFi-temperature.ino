/* TP semaine 2 MOOC FabOC : récupération de la température.
 *
 * Ce code est en CC0 1.0 Universal
 */

#include <ESP8266WiFi.h>

// valeurs pour le WiFi
//const char* ssid     = "";
//const char* password = "";
#include "pass.h"

// valeurs pour le serveur Web
const char* host     = "api.openweathermap.org";
const char* apikey   = "1a702a15a2f46e405e61804cf67c0d30"; // il est possible d'utiliser la clé d'API suivante : 1a702a15a2f46e405e61804cf67c0d30
const char* town     = "Ploudalmézeau,fr";

String keyword = String("\"temp\":"); //chaîne que l'on recherche dans le JSON

void setup() {
	// initialisation du port série
	Serial.begin(115200);
	delay(10);

	// We start by connecting to a WiFi network

	// on affiche le wifi sur lequel on veut se connecter
	Serial.print("Connexion au WiFi ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);  // On se connecte

	while (WiFi.status() != WL_CONNECTED) { // On attend d'être connecté
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


// déclaration d'une variable qui stockera la température reçue dans le fichier JSon
float temperature = 0;

// drapeau indiquant pendant l'analyse de la réponse du serveur
// si on est dans l'en-tête HTTP (false) ou dans le contenu de
// la ressource.
bool inBody = false;


void loop() {
	Serial.print("Connexion au serveur : ");
	Serial.println(host);

	// On se place dans le rôle du  client en utilisant WifiClient
	WiFiClient client;

	// le serveur Web attend traditionnellement sur le port 80
	const int httpPort = 80;

	// Si la connexion échoue cela sera pour la prochaine fois
	if (!client.connect(host, httpPort)) {
		Serial.println("connection failed");
		return;
	}

	// La connexion a réussi on forme le chemin
	// URL complexe composée du chemin et de deux
	// questions contenant le nom de ville et l'API key

	String url = String("/data/2.5/weather?q=") + town + "&appid=" + apikey;

	Serial.print("demande URL: ");
	Serial.println(url);

	client.print(String("GET ") + url + " HTTP/1.1\r\n" +
			"Host: " + host + "\r\n" +
			"Connection: close\r\n\r\n");

	// On attend 1 seconde
	delay(10000);

	inBody = false; // on est dans l'en-tête

	// On lit les données reçues, s'il y en a
	while(client.available()){
		String line = client.readStringUntil('\r');

		if (line.length() == 1) inBody = true; /* passer l'en-tête jusqu'à une ligne vide */
		if (inBody) {  // ligne du corps du message, on cherche le mot clé
			int pos = line.indexOf(keyword);

			if (pos > 0) { /* mot clé trouvé */
				// indexOf donne la position du début du mot-clé, en ajoutant sa longueur
				// on se place à la fin.
				pos += keyword.length();

				Serial.println (&line[pos]);

				temperature = atof(&line[pos]);

			} /* fin récupération du flottant */
		} /* fin de la recherche du mot clé */
	} /* fin data available */

	Serial.println();Serial.print ("Temperature = "); Serial.println(temperature-273.15); // temp en Kelvin

	Serial.println("connexion fermée");

	delay(120000); // 2 minutes
}
