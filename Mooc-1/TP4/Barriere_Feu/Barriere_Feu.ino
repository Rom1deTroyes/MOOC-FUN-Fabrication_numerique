/*
 * Barrière et Feu Bicolore
 * Simulation d'une Barrière et feu bicolore pour le Mooc FUN/MinesTelecom Programmer un objet avec Arduino/TP04
 *
 * This code relased relased under GNU GENERAL PUBLIC LICENSE V3
 * This code use Sweep by BARRAGAN <http://barraganstudio.com> (this example code is in the public domain).
 *
 * Consigne :
 * - fonctions de l'exemple "Sweep" et bases d'électroniques décrites cette semaine
 * - Fonctionnement normal :
 *   - Feu au rouge
 *   - Barrière fermée (0°)
 * - Si Bouton Appuyé :
 *   - Message "Bouton appuye" dans Moniteur Série
 *   - Barrière se lève doucement à 90°
 *   - Puis Feu Vert 5 secondes
 *   - Feu Rouge
 *   - Barrière redescend doucement
 * - Séquence exécutée à l'infini
 *
 * Montage :
 * - Barrière :
 *   - Servomoteur sur les broches 9, +5V et GND
 * - Bouton d'appel :
 *   - Broche 02 : Point central reliant le Bouton Poussoir et la Résistance de Rappel
 *     - Bouton poussoir : Broche +5V et Broche Point Central
 *     - Résistance de Rappel 1KΩ : Broche GND et Point Central
 * - Feu bicolore :
 *   - Broche 03 : LED rouge en série avec une résistance de 220Ω
 *   - Broche 04 : LED verte en série avec une résistance de 220Ω
 *
 */


/*
 * Les Bibliothèques
 */

// Pour contrôler des servomoteurs
#include <Servo.h> 


/*
 * Les constantes
 */

// Les diodes du feu Barrière : chaqu'une sur sa broche.
const int barriereRouge = 3; // On Branche la diode Rouge sur la broche 3
const int barriereVerte = 4; // On Branche la diode Verte sur la broche 4

// Le bouton poussoir est connecté à la broche 2
const int boutonAppel = 2;

/*
 * Les variables
 */
// Variable qui mémorise l'état du bouton poussoir (1==appuyé, 0==libre)
int etatBouton = 0;

// Un Objet Servo pour contrôler un servomoteur
Servo myservo;  // create servo object to control a servo 
// Variable qui mémorise la position du servomoteur
int pos = 0;

// Routine d'initialisation (ne s'exécute qu'une fois au démarage).
void setup() {

	// on souhaite communiquer avec l'ordinateur
	Serial.begin(9600); 

	/* Configuration des broches pour les feux */
	// Les broches sur les quelles sont branchées les diodes doivent être des sorties
	// Pour le feu Barrière :
	pinMode(barriereVerte, OUTPUT); // Broche de la diode Verte en sortie
	pinMode(barriereRouge, OUTPUT); // Broche de la diode Rouge en sortie

	// Le bouton d'appel est en entré :
	pinMode(boutonAppel, INPUT);

	/* Initialisation des feux (devrait être rouge clignotant dans la vraie vie !)*/
	// On allume le feu Barrière en Rouge.
	digitalWrite(barriereVerte, LOW);    // Éteint la diode Verte
	digitalWrite(barriereRouge, HIGH);    // Allume la diode Rouge

	/* La Barrière */
	// Attache le servomoteur de la broche 9 à l'Objet Servo
	myservo.attach(9);
	// Ferme la barrière
	myservo.write(0);
}


// le code dans cette fonction est exécuté en boucle
void loop(){
	// read the state of the pushbutton value:
	etatBouton = digitalRead(boutonAppel);

	// si le bouton est appuyé
	if (etatBouton == HIGH) {
		/*
		 * Envoie un message sur le moniteur série
		 */
		Serial.println("Bouton appuye");

		/*
		 * Monte la barrière
		 */
		for(pos = 0; pos < 90; pos += 1)  // de 0 degrés à 90 degrés par pas de 1 degré
		{
			myservo.write(pos);              // tell servo to go to position in variable 'pos' 
			delay(15);                       // waits 15ms for the servo to reach the position 
		} 

		/*
		 * Passe le feu au Vert
		 */
		digitalWrite(barriereRouge, LOW);    // Éteint la diode Rouge
		digitalWrite(barriereVerte, HIGH);   // Allume la diode Verte

		/*
		 * Attend 5 secondes
		 */
		delay(5000);

		/*
		 * Passe le feu au Rouge
		 */
		digitalWrite(barriereVerte, LOW);   // Éteint la diode Verte
		digitalWrite(barriereRouge, HIGH);   // Allume la diode Rouge

		/*
		 * Descend la barrière
		 */
		for(pos = 90; pos>=1; pos-=1)     // de 90 degrés à 0 degrés par pas de 1 degré
		{
			myservo.write(pos);              // tell servo to go to position in variable 'pos' 
			delay(15);                       // waits 15ms for the servo to reach the position 
		}
	}
}
