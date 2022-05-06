//Bibliothèques
#include <Servo.h>

//déplacement
int capt1 = 1;  
int capt2 = 2;
int capt3 = 3;
int capt4 = 4;
int ENA = 5;  // moteur (gauche)
int ENB = 6;  // moteur (droit)
int IN1=8;
int IN2=9;
int IN3=10;
int IN4=11;

// donner les plateaux
int bouton = 7;
int ENA_2 = 12;
int ENB_2 = 13;
int IN1_2 = 14;
int IN2_2 = 15;
int IN3_2 = 16;
int IN4_2 = 17;

// détection d'objets
int trig_1 = 18;
int echo_1 = 19;
long lecture_echo_1;
long cm_1;
int trig_2 = 20;
int echo_2 = 21;
long lecture_echo_2;
long cm_2;
int trig_3 = 22;
int echo_3 = 23;
long lecture_echo_3;
long cm_3;
int trig_4 = 24;
int echo_4 = 25;
long lecture_echo_4;
long cm_4;


int etat_bouton;
int etat_capt1;
int etat_capt2;
int etat_capt3;
int etat_capt4;
int i;

//Ouverture de la porte
Servo servoOuvrePorte;

int intensiteMoteurDroit;
int intensiteMoteurGauche;
int servoOuvrePortePin;
int angleOuverturePoignee = 0;
int valeurMaxIntensiteRoues;
int codeBarreDetecte;
int dernierCodeBarre;

void setup() {
  pinMode (capt1, INPUT);
      	(capt2, INPUT);
      	(capt3, INPUT);
      	(capt4, INPUT);
      	(ENA, OUTPUT);
      	(ENB, OUTPUT);
      	(IN1, OUTPUT);
      	(IN2, OUTPUT);
      	(IN3, OUTPUT);
      	(IN4, OUTPUT);
     	 
  pinMode(trig_1, OUTPUT);
  digitalWrite(trig_1, LOW);
  pinMode(echo_1, INPUT);
  Serial.begin(9600);
 
  pinMode(trig_2, OUTPUT);
  digitalWrite(trig_2, LOW);
  pinMode(echo_2, INPUT);
  Serial.begin(9600);
 
  pinMode(trig_3, OUTPUT);
  digitalWrite(trig_3, LOW);
  pinMode(echo_3, INPUT);
  Serial.begin(9600);
 
  pinMode(trig_4, OUTPUT);
  digitalWrite(trig_4, LOW);
  pinMode(echo_4, INPUT);
  Serial.begin(9600);
  servoOuvrePorte.attach(servoOuvrePortePin);
}



void suivit_de_ligne() {
  etat_capt1 = digitalRead (capt1);
  etat_capt2 = digitalRead (capt2);
  etat_capt3 = digitalRead (capt3);
  etat_capt4 = digitalRead (capt4);

  if (etat_capt1 == 0 and etat_capt2 == 1 and etat_capt3 == 1 and etat_capt4 == 0) {
	// avancer tout droit
	analogWrite(ENA, 200);
	analogWrite(ENB, 200);
	digitalWrite(IN1,LOW);
	digitalWrite(IN2,HIGH);
	digitalWrite(IN3,LOW);
	digitalWrite(IN4,HIGH);
  }
  if (etat_capt1 == 0 and etat_capt2 == 1 and etat_capt3 == 0 and etat_capt4 == 0) {
	// réalignement à droite
	analogWrite(ENA, 100);
	analogWrite(ENB, 200);
	digitalWrite(IN1,LOW);
	digitalWrite(IN2,HIGH);
	digitalWrite(IN3,LOW);
	digitalWrite(IN4,HIGH);
  }
  if (etat_capt1 == 0 and etat_capt2 == 0 and etat_capt3 == 1 and etat_capt4 == 0) {
	// réalignement à gauche
	analogWrite(ENA, 200);
	analogWrite(ENB, 100);
	digitalWrite(IN1,LOW);
	digitalWrite(IN2,HIGH);
	digitalWrite(IN3,LOW);
	digitalWrite(IN4,HIGH);
  }
}



void angle_droit_gauche() {
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);   
}

void angle_droit_droite() {
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);    
}



void donner_plateau() {
  // à compléter si besoin
  etat_bouton = 0;
  i = 30;
  while (i > 0) {
	etat_bouton = digitalRead (bouton);
	if (etat_bouton == 1) {
  	analogWrite(ENA_2, 200);
  	analogWrite(ENB_2, 200);
  	digitalWrite(IN1_2,HIGH);
  	digitalWrite(IN2_2,LOW);
  	digitalWrite(IN3_2,LOW);
  	digitalWrite(IN4_2,HIGH);
  	delay (1000);
  	i = 1;
	}  
	i = i--;
	delay (1000);
  }
  delay (5000);
}



void ouverturePorte()
{
  //Il faut que le code bar soit bien placé identiquement devant toutes les portes.
  codeBarreDetecte = lireCodeBarre();
  if(codeBarreDetecte && codeBarreDetecte =! dernierCodeBarre)//on verifie que l'on detecte un code bar et qu'il n'est pas identique au précédent
  {
	dernierCodeBarre = codeBarreDetecte;
	codeBarreDetecte = 0;

	intesiteMoteurDroit = 0;
	intesiteMoteurGauche = 0;
	//Se mettre face à la porte
	if(codeBar == impaire)
	{
  	angle_droit_droite();
	}
	if(codeBarre == paire)
	{
 	angle_droit_gauche();
	}
	digitalWrite(trig_1, HIGH);
	delayMicroseconds(10);
	digitalWrite(trig_1, LOW);
	lecture_echo_1 = pulseIn(echo_1,HIGH);
	cm_1 = lecture_echo_1 /58;

	if(cm_1 > distancePorteChariot) // Si il n'y a pas de porte
	{
  	break;
	}
	else
	{
  	while(1)
  	{
    	suivit_de_ligne();
   	 
    	intensiteMoteurDroit = analogRead(intensiteMoteurDroitPin);
    	intensiteMoteurGauche = analogRead(intensiteMoteurGauchePin);
   	 
    	if(intensiteMoteurDroit < intensiteNormaleMoteurs && intensiteMoteurGauche < intensiteNormaleMoteurs)
    	{
      	servoOuvrePorte.write(angleOuverturePoignee);
      	break;
    	}
  	}
  	servoOuvrePorte.write(0);
	}
  }
}



void detection_objet() {
  digitalWrite(trig_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_1, LOW);
  lecture_echo_1 = pulseIn(echo_1,HIGH);
  cm_1 = lecture_echo_1 /58;

  digitalWrite(trig_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_2, LOW);
  lecture_echo_2 = pulseIn(echo_2,HIGH);
  cm_2 = lecture_echo_2 /58;

  digitalWrite(trig_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_3, LOW);
  lecture_echo_3 = pulseIn(echo_3,HIGH);
  cm_3 = lecture_echo_3 /58;

  digitalWrite(trig_4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_4, LOW);
  lecture_echo_4 = pulseIn(echo_4,HIGH);
  cm_4 = lecture_echo_4 /58;

  if (cm_1 < 30 or cm_2 < 30 or cm_3 < 30 or cm_4 < 30) {
	// arret
	digitalWrite(IN1,HIGH);
	digitalWrite(IN2,HIGH);
	digitalWrite(IN3,HIGH);
	digitalWrite(IN4,HIGH);
  }  
}



void loop() {
 
  ouverture_porte();
  detection_objet();
  // lit à gauche
  etat_capt1 = digitalRead (capt1);
  etat_capt2 = digitalRead (capt2);
  etat_capt3 = digitalRead (capt3);
  etat_capt4 = digitalRead (capt4);
  if (etat_capt1 == 1 and etat_capt2 == 1 and etat_capt3 == 1 and etat_capt4 == 0) {   
	angle_droit_gauche();
	donner_plateau();
	angle_droit_droite();
  }
  // lit à droite
  etat_capt1 = digitalRead (capt1);
  etat_capt2 = digitalRead (capt2);
  etat_capt3 = digitalRead (capt3);
  etat_capt4 = digitalRead (capt4);
  if (etat_capt1 == 0 and etat_capt2 == 1 and etat_capt3 == 1 and etat_capt4 == 1) {   
	angle_droit_droite();
	donner_plateau();
	angle_droit_gauche();
  }
  suivit_de_ligne();
}
