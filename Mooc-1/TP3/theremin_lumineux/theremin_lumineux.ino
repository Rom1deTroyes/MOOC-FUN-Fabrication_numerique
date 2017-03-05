/*
 * Thérémin lumineux
 * Simulation d'un Thérémin lumineux pour le Mooc FUN/MinesTelecom Programmer un objet avec Arduino/TP03
 *
 * This code relased relased under GNU GENERAL PUBLIC LICENSE V3
 * Consigne
 * - Adapter AnalogInOutSerial pour que la fréquence du buzzer (branché sur la broche 8) soit proportionnelle à la luminosité mesurée par la photorésistance (branchée sur la broche 0)
 * - Plus la luminosité reçue par la photorésistance est importante, plus la fréquence jouée par le buzzer sera élevée
 * - Inversement, si on passe notre main devant le capteur de luminosité alors le son émis sera grave→fréquence basse.
 * - Prendre une photo de votre circuit ou à prendre une capture d'écran du simulateur et à nous l'envoyer dans l'évaluation par les pairs.
 *
 * Matériel
 * - Un Buzzer : Piézo éléctrique, mais aussi haut-parleur...
 * - Un capteur : Photo éléctrique, remplaçable par un potentiomètre, un ultrason, Infrarouge, ...
 *   - Une resistance de rappel de 10K Ohms
 * - Personnelement j'ai ajouté :
 *   - un intérupteur pour couper le buzzer (et préserver mes oreilles !)
 *   - un potensiomètre avec la photorésistance pour ajuster la luminosité
 *   - On pourait aussi avoir deux potentiomètres pour régler buzzMin et buzzMax à la volée !
 *
 * Montage
 * - Broche 8 : Piezo branché entre la broche 8 et la masse
 * - Broche A0 : Point Central reliant la photorésistance et la résistance de rappel.
 *   - Photorésistance : Broche 5V et Point Central (vers la broche A0)
 *   - Résistance de Rappel (10kΩ) : Broche GND et Point Central (vers la broche A0)
 *
 * Utilisation
 * - Brancher le matériel, charger le programme, faites du bruit !
 * - En modifiant les variables buzzMin et buzzMax, on peut réduire la plage des notes jouées, et donc transformer le bruit en musique.
 */

// Le Buzzer sur la broche 8
const int buzzer = 8 ;
// Fréquences MINimale et MAXimale du Buzzer
// Dans les indices de la consigne, on donne entre 50 Hz et 30 000 Hz... Pour les oreilles on peut choisir plus agréable !
// https://fr.wikipedia.org/w/index.php?title=Gamme_naturelle&section=18#Tableau_de_synth.C3.A8se
int buzzMin = 50 ; // Pour un Do = 264
// Fréquence maximale du Buzzer
int buzzMax = 30000 ; // Pour 3 Ocatves plus haut = 3*buzzMin

// La photoresistance sur la broche A0
const int capteur = A0 ;
// variable pour stocker la valeur reçue sur A0
int sensorValue;

void setup() {
  // Initialise la communication avec l'ordinateur
  Serial.begin(9600);
}

void loop() {
  // lire la valeur du capteur et la sauver dans sa variable.
  sensorValue = analogRead(capteur);

  // Étalonnage de la valeur captée vers un intervalle de fréquences audibles
  int pitch = map(sensorValue, 0, 1023, buzzMin, buzzMax);

  // Jouer la fréquence sur le buzzer
  tone(buzzer, pitch);

  // envoie tout ça vers l'ordinateur
  Serial.print("Capteur = " );                       
  Serial.print(sensorValue);      
  Serial.print("\t Pitch = ");
  Serial.println(pitch);

  // attendre 10 ms
  delay(10);
}
