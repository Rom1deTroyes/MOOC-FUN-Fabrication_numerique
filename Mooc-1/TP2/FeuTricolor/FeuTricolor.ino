/*
 * Feu tricolore + Feu Pietons
 * Simulation d'un feu tricolore pour le Mooc FUN/MinesTelecom Programmer un objet avec Arduino/TP02
 *
 * This code relased relased under GNU GENERAL PUBLIC LICENSE V3
 *
 * Consigne :
 * - fonctions de l'exemple "Blink" et bases d'électroniques décrites cette semaine
 * - feu tricolore 3 LED (vert, orange, rouge) :
 *   - Orange en premier
 *   - Orange 1 seconde
 *   - orange s'éteindre puis rouge s'allume
 *   - Rouge  3 secondes
 *   - rouge off, vert on
 *   - Verte  3 secondes
 * - Séquence exécutée à l'infini

 * Montage :
 * Chaque LED est branchée en série avec une résistance de 220 Ohms
 * - Feu voiture :
 *   - LED verte sur la broche 10
 *   - LED orange sur la broche 11
 *   - LED rouge sur la broche 12
 * - Feu Piéton :
 *   - LED verte sur la broche 8 
 *   - LED rouge sur la broche 9
 *   - Bouton poussoir branché sur la broche 2 depuis +5V
 * Une résistance de 1KΩ bracnhé sur la broche 2 depuis GND


 */
 
// Les 3 diodes du feu voiture : chaqu'une sur sa broche.
const int ledVoitureVerte = 10; // On Branche la diode Verte sur la broche 10
const int ledVoitureOrange = 11; // On Branche la diode Orange sur la broche 11
const int ledVoitureRouge = 12; // On Branche la diode Rouge sur la broche 12

// Les 2 diodes du feu piéton : chaqu'une sur sa broche.
const int ledPietonVerte = 8; // On Branche la diode Verte sur la broche 8
const int ledPietonRouge = 9; // On Branche la diode Rouge sur la broche 9

// Le bouton poussoir est connecté à la broche 2
const int boutonAppel = 2;

// Variable qui mémorise l'état du bouton poussoir (1==appuyé, 0==libre)
int etatBouton = 0;


// Routine d'initialisation (ne s'exécute qu'une fois au démarage).
void setup() {
  /* Configuration des broches pour les feux */
  // Les broches sur les quelles sont branchées les diodes doivent être des sorties
  // Pour le feu Voiture :
  pinMode(ledVoitureVerte, OUTPUT); // Broche de la diode Verte en sortie
  pinMode(ledVoitureOrange, OUTPUT); // Broche de la diode Orange en sortie
  pinMode(ledVoitureRouge, OUTPUT); // Broche de la diode Rouge en sortie
  // Pour le feu Piéton :
  pinMode(ledPietonVerte, OUTPUT); // Broche de la diode Verte en sortie
  pinMode(ledPietonRouge, OUTPUT); // Broche de la diode Rouge en sortie
  // Le bouton d'appel est en entré :
  pinMode(boutonAppel, INPUT);

  /* Initialisation des feux (devrait être orange clignotant dans la vraie vie !)*/
  // On allume le feu Voiture en orange.
  digitalWrite(ledVoitureVerte, LOW);    // éteint la diode Verte
  digitalWrite(ledVoitureRouge, LOW);    // éteint la diode Rouge
  digitalWrite(ledVoitureOrange, HIGH);    // allume la diode Orange
  // Dans le fonctionnement normal, le feu piéton est toujours rouge
  digitalWrite(ledPietonVerte, LOW);    // éteint la diode Verte
  digitalWrite(ledPietonRouge, HIGH);    // Allume la diode Rouge

  /* Pour repscter la consigne du TP, on va devoir déplacer des truc par ici...
   * C'est pas propre, mais pour que la LED orange soit la première LED à s'allumer alors
   * que la lecture du bouton se fait quand le feu est vert, on va commencer le cycle ici.
   */
       


}



void loop() {

/* 
 * Passe le feu au Orange
 */
  digitalWrite(ledVoitureVerte, LOW);   // éteint la diode Verte
  digitalWrite(ledVoitureOrange, HIGH);    // Allume la diode Orange
  delay(1000);               // On attend 1 seconde

/*
 * Passe le feu au Rouge
 */
  digitalWrite(ledVoitureOrange, LOW);    // éteint la diode Orange
  digitalWrite(ledVoitureRouge, HIGH);   // Allume la diode Rouge
  delay(3000);               // On attend 3 secondes
  
/*
 * Passe le feu au Vert
 */
  digitalWrite(ledVoitureRouge, LOW);    // éteint la diode Rouge
  digitalWrite(ledVoitureVerte, HIGH);   // Allume la diode Verte
  delay(3000);               // On attend 3 secondes

}

