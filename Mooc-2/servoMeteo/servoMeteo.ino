/*
   TP semaine 2 MOOC FabOC : le servométéo
   créé par Guillaume Habault le 11 avril 2017
   Ce code est en CC0 1.0 Universal
 */

#include <Servo.h>
#include <ESP8266WiFi.h>

#include "pass.h"
//const char* ssid     = "";         // Nom de votre réseau WiFi
//const char* password = "";         // Mot de passe associé

// valeurs pour le serveur Web
const char* host     = "api.openweathermap.org";
const char* apikey   = "1a702a15a2f46e405e61804cf67c0d30";
const char* town     = "Ploudalmézeau,fr";

String keyword = String("\"icon\":\""); //chaîne que l'on recherche dans le JSON

// le serveur Web attend traditionnellement sur le port 80
const int httpPort = 80;
String uri = String("/data/2.5/weather?q=") + town + "&appid=" + apikey + "&units=metric";
// drapeau indiquant pendant l'analyse de la réponse du serveur
// si on est dans l'en-tête HTTP (false) ou dans le contenu de 
// la ressource.
bool inBody = false;

Servo myservo;  // création d'un objet myservo issu de la librairie Servo

// On se place dans le rôle du  client en utilisant WifiClient
WiFiClient client;

void setup() {
	// initialisation du port série
	Serial.begin(9600);

	// on affiche le wifi sur lequel on veut se connecter
	Serial.print("Connexion au WiFi ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);  // on se connecte

	// Le servo est branché sur la broche D1
	myservo.attach(D1);

	while (WiFi.status() != WL_CONNECTED) { // on attend d'être connecté
		delay(500);
		Serial.print(".");
		// On envoie la chaîne vide à la fonction setServo
		setServo("");
	}

	Serial.println("");  // on affiche les paramètres 
	Serial.println("WiFi connecte");  
	Serial.print("Adresse IP du module ESP: ");  
	Serial.println(WiFi.localIP());
	Serial.print("Adresse IP du point d'accès : ");
	Serial.println(WiFi.gatewayIP());

	// On vérifie que la connexion est ok, sinon on passe en mode erreur
	if (!client.connect(host, httpPort)) {
		Serial.println("La connexion avec le serveur a échouée.");
		setServo("");
	}
}


void loop()
{
	Serial.print("connexion au serveur : ");
	Serial.println(host);

	// On vérifie que la connexion est ok, sinon on passe en mode erreur
	if (!client.connect(host, httpPort)) {
		Serial.println("La connexion avec le serveur a échouée.");
		// On envoie la chaîne vide à la fonction setServo
		setServo("");
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
	delay(1000);

	inBody = false; // on est dans l'en-tête

	// on se préparer à recevoir la chaîne de caractères correspondant à l'icone
	String iconString = "";

	// Réception de message
	while(client.available()){
		String line = client.readStringUntil('\r');

		if (line.length() == 1) inBody = true; // passer l'en-tête jusqu'à une ligne vide

		if (inBody) {
			// ligne du corps du message, on cherche le mot clé
			int pos = line.indexOf(keyword);

			if (pos > 0) {
				// indexOf donne la position du début du mot-clé, en ajoutant sa longueur
				// on se place à la fin.
				pos += keyword.length();

				// On ne souhaite garder que les 3 caractères correspondant à l'icône
				line[pos+3] = '\0';

				// on stocke le résultat dans iconString
				iconString = &line[pos]; 
			}
		}
	}

	Serial.print("Icone : ");
	Serial.println(iconString);  // On affiche la valeur de l'icône

	setServo(iconString);     // On envoie l'icone à notre fonction setServo

	delay(10000); // On attend 10 secondes avant la prochaine requête

}

/**
 * Fonction setServo()
 * Détermine la position à prendre pour le servomoteur en fonction de l'icone récupérée et envoye un message sur le port série. 
 * @String icon : L'icone à afficher.
 */
void setServo(String icon) {
  if (icon == "") { // Si l'icone est vide, c'est qu'on a un problème de connexion
    myservo.write(90); // On positionne le servo à 90° et on envoie le message sur le port série
    Serial.println("Erreur : êtes vous bien connecté au wifi ?");
  } else { // Si on a une icone, on va regarder si elle apparait dans la liste des codes de pluie
    String stringPluie = "09d, 09n, 10d, 10n"; // Les cas de pluie
    if (0 <= stringPluie.lastIndexOf(icon)) { // lastIndexOf renvoye -1 si rien n'est trouvé
      myservo.write(180); // On positionne le servo à 180° et on envoie le message sur le port série
      Serial.println("Vous aurez besoin de votre parapluie aujourd'hui !");
    } else { // la recherche a renvoyé une valeur négative
      myservo.write(0); // On positionne le servo à 0° et on envoie le message sur le port série
      Serial.println("Pas besoin de parapluie aujourd'hui !");
    }
  }
}
