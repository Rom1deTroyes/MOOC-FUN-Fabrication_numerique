/*
 * FeuTricolor
 * Simulation d'un feu tricolore pour le Mooc FUN/MinesTelecom Programmer un objet avec Arduino/TP01
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
 */
 
// Les 3 diodes : chaqu'une sur sa broche.
int ledVerte = 10; // On Branche la diode Verte sur la broche 10
int ledOrange = 11; // On Branche la diode Orange sur la broche 11
int ledRouge = 12; // On Branche la diode Rouge sur la broche 12

// Routine d'initialisation (ne s'exécute qu'une fois au démarage).
void setup() {
  // Les broches sur les quelles sont brnchées les diodes doivent etre des sorties
  pinMode(ledVerte, OUTPUT); // Broche de la diode Verte en sortie
  pinMode(ledOrange, OUTPUT); // Broche de la diode Orange en sortie
  pinMode(ledRouge, OUTPUT); // Broche de la diode Rouge en sortie
  // On éteint toutes les diodes (meusure de sécurité, j'ai eu des parasites sans).
  digitalWrite(ledVerte, LOW);    // éteint la diode Verte
  digitalWrite(ledOrange, LOW);    // éteint la diode Orange
  digitalWrite(ledRouge, LOW);    // éteint la diode Rouge
}



// Boucle infinie (exécutée encore et encore).
void loop() {

/* 
 * Passe le feu au Orange
 */
  digitalWrite(ledVerte, LOW);   // éteint la diode Verte
  digitalWrite(ledRouge, LOW);    // éteint la diode Rouge (par sécurité car elle ne devrait pas etre allumée)
  digitalWrite(ledOrange, HIGH);    // Allume la diode Orange
  delay(1000);               // On attend 1 seconde

/*
 * Passe le feu au Rouge
 */
  digitalWrite(ledOrange, LOW);    // éteint la diode Orange
  digitalWrite(ledVerte, LOW);    // éteint la diode Verte  (par sécurité car elle ne devrait pas etre allumée)
  digitalWrite(ledRouge, HIGH);   // Allume la diode Rouge

  delay(3000);               // On attend 3 secondes
  
/*
 * Passe le feu au Vert
 */
  digitalWrite(ledRouge, LOW);    // éteint la diode Rouge
  digitalWrite(ledOrange, LOW);    // éteint la diode Orange  (par sécurité car elle ne devrait pas etre allumée)
  digitalWrite(ledVerte, HIGH);   // Allume la diode Verte

  delay(3000);               // On attend 3 secondes

}
