/*
 * TP semaine 1 MOOC Fabrication Numérique : la servoserrure
 * Montage : voir shémas.
 * 
 * Ce code est en CC-By-SA Rom1deTroyes
 * Ce code utilise du code venant de :
 *  Sweep by BARRAGAN <http://barraganstudio.com> 
 *   modified 28 May 2015 by Michael C. Miller 
 *   modified 8 Nov 2013 by Scott Fitzgerald
 */

#include <Servo.h> 

Servo myservo;  // création d'un objet myservo issu de la bibliothèque Servo
int pos; // Position du servo
const int potPin = A0 ; // Broche du potentiomètre de retour.

/*
 * Broches utilisées et niveau d'alimentation du Servo
 * (dé)commentez en fonctiond de votre carte !
 */

/* ARDUINO 
#define ledPin 13     // ARDUINO Broche de la LED (interne)
#define ledLogic HIGH // Logique : LED allumée sur signal HIGH
#define servoPin 9    // ARDUINO Broche de contrôle du servo-moteur
#define maxPot 1023   // Alimentation en 5v5
 */

/*  ESP
 */
#define ledPin BUILTIN_LED // ESP Broche de la LED (interne)
#define ledLogic LOW       // Logique : LED allumée sur signal HIGH
#define servoPin D1        // ESP Broche de contrôle du servo-moteur
#define maxPot 1023        // Alimentation en 3V3 : 654
/**/

/* SIMULATEUR
const int ledPin = 13;      // Broche de la LED (interne)
const bool ledLogic = HIGH; // Logique : LED allumée sur signal LOW
const int servoPin = 9;     // Broche de contrôle du servo-moteur
const int maxPot = 1023 ;   // Alimentation en 5v
 */

// déclaration de variables attestant le franchissment des étapes :
boolean etape1 = false;
boolean etape2 = false;
boolean etape3 = false;

// déclaration des variables pour enregistrer le code secret
int code1 = 120;
int code2 = 60;
int code3 = 60;


/*
 * Fonction appelée pour vérouiller la serrure.
 */
void rAz(){
	// On repasse à FAUX les variables étapes.
	etape1 = false;
	etape2 = false;
	etape3 = false;
}

/*
 * Fonction appelée si on déverouille la serrure.
 */
void victoire(){
	Serial.println("Bravo, la porte s'ouvre");
	// on fait clignoter notre led trois fois
	for(int i = 0 ; i < 3 ; i++) {
		digitalWrite(ledPin, ledLogic);
		delay(500);
		digitalWrite(ledPin, !ledLogic);
		delay(500);
	}
}

/*
 * Dépace un Servo à la position donnée
 * @val : position à atteindre en degrès.
 */
void moveServo(int val){
	// le servo branché sur la bonne broche
	myservo.attach(servoPin);
	// on bouge le servo dans la position demandée
	myservo.write(val);
	// On attend qu'il se déplace
	delay(100);
	// on détache le servo pour pouvoir le tourner à la main.
	myservo.detach();
}

void setup() 
{
	// initialisation du port série
	Serial.begin(9600);

	// initialisation de la broche ledPin comme sortie puis on l'éteint
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, !ledLogic); 

	// on s'assure que le servo est bien à 0
	moveServo(0);
} 

void loop() 
{
	pos = analogRead(potPin);            // lit le potentiomètre du servo (valeur comprise entre 0 et 1023)
	//  pos = analogRead(myservo.read());  // lit le potentiomètre du servo (valeur comprise entre 0 et 1023)
	Serial.println(pos);                 // Permet d'étaloner le potentiomètre en lançant le moniteur série
	pos = map(pos, 0, maxPot, 0, 179);   // change l'échelle pour que nous soyons en degrés (valeur comprise en 0° et 179°)
	//  moveServo(pos);                      // Si le servo est sans retour d'information, on le simule avec un potard, on peut bouger le servo pour suivre le mouvement du potard.
	delay(15);                           // petite attente pour que tout se passe bien

	// test pour l'étape 1 : on cherche la position 1
	if(etape1 == false && pos > code1) {
		etape1 = true;
		Serial.println("Etape 1 : OK");
	}

	// test pour l'étape 2
	// on s'assure que l'étape 1 est franchie, et qu'on cherche la position 2
	if(etape1 == true && etape2 == false && pos < code2) {
		etape2 = true;
		Serial.println("Etape 2 : OK");
	}

	// test pour l'étape 3
	// on s'assure que l'étape 2 est franchie, et qu'on cherche la position 3
	if(etape2 == true && etape3 == false && pos > code3) {
		etape3 = true;
		Serial.println("Etape 3 : OK");

		// Gagné !
		victoire();
		// On remet tout à zéro pour repartir sur une nouvelle épreuve
		rAz();
	}
}
