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


/* CONSTANTES */
const int TRIG_PIN = D0;
const int ECHO_PIN = D1;


/* VARIÁVEIS */
long duration;
int distance;


/* SETUP */
void setup() {
  
  // Pinos do sensor ultrassom
  pinMode(TRIG_PIN, OUTPUT); 
  pinMode(ECHO_PIN, INPUT); 

  // Inicia comunicação serial com taxa 9600 bps
  Serial.begin(9600); 
  
}


/* LOOP PRINCIPAL */
void loop() {

  // Reseta o trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Força um pulso HIGH de 10us no trigger
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Le a duração do pulso de resposta
  duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calcula a distância do objeto
  distance = duration*0.034/2;
  
  // Escreve o resultado no monitor serial
  Serial.print("Distância: ");
  Serial.println(distance);

  // Delay para estabilização
  delay(100);
  
}
