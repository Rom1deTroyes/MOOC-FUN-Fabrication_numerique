/*
   MOOC Fabriquer un objet connecté : semaine 3

   Lit la valeur analogique du servo moteur sur la broche et envoie
   cette valeur sur la plateforme TOM en utilisant une requête PATCH
   Toutes les 3 secondes, nous récupérons la valeur sur TOM afin de voir si le
   servo a bougé

 */

#include <Servo.h>

// création de l'objet servo issu du moule Servo
Servo myservo;

// initialisation des constantes spécifiques à votre installation
// n'oubliez pas d'effacer vos identifiants wifi et nelson lors du dépôt de votre TP
const String nelsonName = "";
const char* ssid        = "";
const char* password    = "";

// adresse et port du serveur tom
const String host     = "api.tom.tools"; 
const int httpPort    = 80;

// pos contient la valeur actuelle de notre servo
int pos = 0;

void wifiConnection(const char* ssid, const char* password) {
	/* A COMPLÉTER */
	// on se connecte à l'ESP (cas du simulateur)
	// on se connecte au Wifi
	// on récupère une adresse IP
	// on vérifie qu'on est bien connecté
}

void sendPatch() {
	/* A COMPLÉTER */
	// on envoie une requête patch sur Tom
}

void setup() {
	// on souhaite communiquer avec l'ordinateur
	Serial.begin(9600);
	/* A COMPLÉTER */


}

void loop() {
	/* A COMPLÉTER */


	// lire la valeur du servo moteur

	// convertir celle-ci entre 0 et 180 
	// on attend trois secondes avant la prochaine  requête
	delay (3000);

	// pensez à attacher et détacher le servo suivant l'utilisation  

}
