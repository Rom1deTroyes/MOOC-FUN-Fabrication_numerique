/*
   TP semaine 2 MOOC FabOC : le servométéo
   créé par Guillaume Habault le 11 avril 2017
   Ce code est en CC0 1.0 Universal
 */

#include <Servo.h>

Servo myservo;  // création d'un objet myservo issu de la librairie Servo

void setup() {
	// initialisation du port série
	Serial.begin(9600);

	// Le servo est branché sur la broche D1
	myservo.attach(D1);

	Serial.println("SetupOK"); 
}

void loop() {
	String iconString[] ={"", "09d", "09n", "10d", "10n", "20d", "20n"};
	for(int i = 0 ; i < 7 ; i++){
		Serial.print("Icone : ");
		Serial.println(iconString[i]);  // On affiche la valeur de l'icône

		setServo(iconString[i]);     // On envoie l'icone à notre fonction setServo

		delay(1000); // On attend 1 seconde avant la prochaine requête
	}
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
