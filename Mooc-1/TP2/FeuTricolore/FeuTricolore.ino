/*
 * FeuTricolorePieton
 * Simulation d'un feu tricolore pour le Mooc FUN/MinesTelecom Programmer un objet avec Arduino/TP02
 *
 * This code relased relased under GNU GENERAL PUBLIC LICENSE V3
 *
 * CONSIDERATIONS :
 * Je suis, comme beaucoup d'autres, assez dubitatif sur ce qui est demandé dans ces premiers exercices...
 * J'ai donc décidé de retenir 2 principes :
 *  - Prenez toujours les hypothèses qui vous arrangent :)
 *    - Donc je n'utilise pas d'interruption et encore moins de milis()
 *  - La réponse d'Emmanuel dans la conversation suivante :
 *    https://www.fun-mooc.fr/courses/MinesTelecom/04017S02/session02/discussion/forum/49a1da04c7cbd68b1f8b8561b3c5859446659c20/threads/589c8e051c89dc637f002d95#
 *    "Si le bouton est maintenu appuyé pendant que le feu voiture est au vert" == "après avoir allumé le LED verte pendant 3s, l'arduino peux tester si le bouton est préssé pour en tenir compte (et laisser passer les piétons)."
 *    - Le feu piéton passe au vert SI ET SEULEMENT SI le bouton d'appel est appuyé au moment ou le feu vert s'éteint.
 * 
 * Consigne :
 * - Réaliser un feu tricolore accompagné d'un feu "piéton" bicolore (rouge et vert).
 * - Feu tricolore : même consigne que la semaine dernière
 *   - LED orange (broche 11) allumée 1 seconde (première LED à s'allumer)
 *   - LED rouge (broche 12) allumée 3 secondes
 *   - LED verte (broche 10) allumée 3 secondes
 *   - Si on n'appuie pas sur le bouton, on repasse à orange
 * - Feu bicolore (piéton)
 *   - LED rouge (broche 9) constament allumée
 *   - LED verte (broche 8) 
 *   - bouton (broche 2)
 *   - Si bouton appuyé pendant feu voiture vert
 *     - alors feu tricolore orange 1 seconde
 *     - puis rouge + feu piéton vert
 *     - Après 5 secondes
 *       - feu piéton rouge
 *       - fonctionnement normal reprend
 *
 *  Montage
 * - Voir shéma en consigne du cours : https://www.fun-mooc.fr/c4x/MinesTelecom/04017S02/asset/layer_21.svg
 *   - Broche 12 : LED rouge en série avec une résistance de 220Ω
 *   - Broche 11 : LED orange en série avec une résistance de 220Ω
 *   - Broche 10 : LED verte en série avec une résistance de 220Ω
 *   - Broche 09 : LED rouge en série avec une résistance de 220Ω
 *   - Broche 08 : LED verte en série avec une résistance de 220Ω
 *   - Broche 02 : Point central reliant le Bouton Poussoir et la Résistance de Rappel
 *     - Bouton poussoir : Broche +5V et Broche Point Central
 *     - Résistance de Rappel 1KΩ : Broche GND et Point Central
 */

/* Feu Voiture */
// Les 3 diodes : chaqu'une sur sa broche.
const int ledVoitureVerte = 10; // On Branche la diode Verte sur la broche 10
const int ledVoitureOrange = 11; // On Branche la diode Orange sur la broche 11
const int ledVoitureRouge = 12; // On Branche la diode Rouge sur la broche 12
/* Feu Pieton */
// Les 2 diodes : chaqu'une sur sa broche.
const int ledPietonVerte = 8; // On Branche la diode Verte sur la broche 8
const int ledPietonRouge = 9; // On Branche la diode Rouge sur la broche 9
// Le Bouton d'appel sur sa broche
const int boutonAppel = 2; // On Branche le bouton d'Appel piéton sur la broche 2

// Variables indiquant l'état du bouton lors de la dernière lecture
int boutonEtat = 0;

// Routine d'initialisation (ne s'exécute qu'une fois au démarage).
void setup() {
  // Les broches sur les quelles sont branchées les diodes doivent etre des sorties
  pinMode(ledVoitureVerte, OUTPUT); // Broche de la diode Verte en sortie
  pinMode(ledVoitureOrange, OUTPUT); // Broche de la diode Orange en sortie
  pinMode(ledVoitureRouge, OUTPUT); // Broche de la diode Rouge en sortie
  pinMode(ledPietonVerte, OUTPUT); // Broche de la diode Verte en sortie
  pinMode(ledPietonRouge, OUTPUT); // Broche de la diode Rouge en sortie
  // Le bouton d'appel est une entrée :
  pinMode(boutonAppel, INPUT); // Broche du bouton en entrée

  // On initialise le feu (dans la vraie vie : orange clignotant et piéton au rouge !)
  digitalWrite(ledVoitureVerte, LOW);    // éteint la diode Verte
  digitalWrite(ledVoitureOrange, HIGH);    // Allume la diode Orange
  digitalWrite(ledVoitureRouge, LOW);    // éteint la diode Rouge
  digitalWrite(ledPietonVerte, LOW);    // éteint la diode Verte
  digitalWrite(ledPietonRouge, HIGH);    // Allume la diode Rouge
}



// Boucle infinie (exécutée encore et encore).
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

/*
 * Vérifie si le passage piéton a été demandé
 */
  if (boutonEtat == HIGH) { // le bouton a été appuyé
    // On allume le feu piéton au vert pendant 5s
    digitalWrite(ledPietonRouge, LOW);
    digitalWrite(ledPietonVerte, HIGH);
    delay(5000);
    
    // On remet le feu piéton au rouge
    digitalWrite(ledPietonRouge, HIGH);
    digitalWrite(ledPietonVerte, LOW);
  } else { // le passage piéton n'a pas été demandé
    // Fonctionnement normal
  delay(3000);               // On attend 3 secondes
  }
  
/*
 * Passe le feu au Vert
 */
  digitalWrite(ledVoitureRouge, LOW);    // éteint la diode Rouge
  digitalWrite(ledVoitureVerte, HIGH);   // Allume la diode Verte
  delay(3000);               // On attend 3 secondes

/*
 * Enregistrement de l'état du bouton d'appel
 * On lit la valeur de la broche, et on la stoque dans sa variable.
 * Se serait plus clair d'utiliser une valeur booléenne, mais on a pas encore vu ça...
 * Ce serait plus propre avec une fonction lireEtat() mais on a pas vu ça non plus...
 * Ce serait plus élégant d'utiliser une intéruption, mais là, c'est pour dans longtemps !
 */
  boutonEtat = digitalRead(boutonAppel);
}
