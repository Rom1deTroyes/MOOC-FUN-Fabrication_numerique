// BoissonMatic' 2014
// john@labfab.fr sous licence WTFPL v2.0 


#include <Servo.h> 
 
Servo servoBas;  //  création d'un premier objet servo, pour le Pan
Servo servoHaut;  //  création du second, pour le tilt
 
int pos = 0;    // variable pour stocker une position

int  const MINPAN = 0; // valeur mini du Pan, en degré.
int const MAXPAN = MINPAN + 90;  // Un quart de tour panoramique
int  const MINTILT = 180;  // valeur mini du Tilt (en cas de servo monté "à l'envers" ! :] )
int const MAXTILT = MINTILT - 90;  // avec un max au quart de tour.

void setup() 
{ 
  servoBas.attach(9);  //   attache le servo du bas à la broche 9
  servoHaut.attach(10);  // celui du haut à la broche 10
  
  // Mise en place de la machine en position de départ
  servoBas.write(MINPAN);  
  servoHaut.write(MINTILT);
  
  delay(1000); // admettant qu'il faille une seconde pour faire demi-tour
               // à un servo bien nourri.
} 
 
 
void loop() 
{ 
  // on fait faire un quart de tour au servo panoramique
  servoBas.write(MAXPAN);
  
  // La boucle "for" permet d'adoucir le déplacement du moteur
  for(pos = 180; pos>=70; pos-=1) // On dépasse le quart de tour, 
                                  // pour que le versement du liquide soit plus rapide 
  {                                
    servoHaut.write(pos); 
    // le servo tourne de la valeur de l'angle indiquée par la variable 'pos' 
    delay(20);                      
    // on laisse un peu de temp au servo pour arriver à la position demandée
  } 
  delay(3000);  // encore du temps pour qu'assez de liquide coule du récipient.
  
  for(pos = 70; pos<=180; pos+=1)     // la même dans l'autre sens 
  {                                
    servoHaut.write(pos);
    delay(25);
  } 

  servoBas.write(MINPAN );  // retour en position initiale
  delay(400);

  servoHaut.detach(); // on détache les moteurs un par un. 
  servoBas.detach();  
  // la séquence n'aura lieu donc physiquement lieu qu'une seule fois, 
  // même si la boucle principale loop() continue à tourner.
  
  servoHaut.attached(); 
  // devrait retourner quelque chose
  // comme "false" sur votre moniteur serie.
}
