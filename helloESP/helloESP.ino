/*
  Hello ESP
  
  Programa para teste inicial do ESP -- Blink
  
  Evans Picolo
  07/2020
  
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


/* Constantes */
const int DELAY_TIME = 1000; // ms

/* Função Setup */
void setup() {
  
  pinMode(LED_PIN, OUTPUT);
}

/* Loop princiapl */
void loop() {
  
  digitalWrite(LED_PIN, HIGH);   
  delay(DELAY_TIME);                       
  digitalWrite(LED_PIN , LOW);    
  delay(DELAY_TIME);                       

}
