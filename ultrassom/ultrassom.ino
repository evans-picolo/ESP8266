/*
  Ultrassom
  
  Programa para teste do sensor de distância ultrassônico HC-SR04
  
  Evans Picolo
  07/2020

  *OBS:
    - Alguns sensores só funcionam com Vcc = 5V (VU / Vusb)
  
*/

/* MAPEAMENTO DE PINOS */
#define D0      16
#define D1       5
#define D2       4
#define D3       0
#define D4       2
#define D5      14
#define D6      12
#define D7      13
#define D8      15
#define D9       3
#define D10      1
#define LED_PIN  2


/* BIBLIOTECAS */
#include <Ultrasonic.h>


/* CONSTANTES */
const int TRIG_PIN = D0;
const int ECHO_PIN = D1;


/* VARIÁVEIS */
int distance;


/* INSTANCIAMENTOS */
Ultrasonic ultrasonic(TRIG_PIN,ECHO_PIN);


/* SETUP */
void setup() {

  // Inicia comunicação serial com taxa 9600 bps
  Serial.begin(9600); 
  
}


/* LOOP PRINCIPAL */
void loop() {

  // Le sensor ultrassonico
  distance = ultrasonic.read();
  
  // Escreve o resultado no monitor serial
  Serial.print("Distância: ");
  Serial.println(distance);

  // Delay para estabilização
  delay(100);
  
}
