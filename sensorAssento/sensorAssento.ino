/*
        SENSOR DE ASSENTO

        Código para ler o valor dos dois módulos HX711 usados para 
        sensoriar o assento no protótipo do projeto Ergolax.
        
        Evans Picolo
        out/2020

        *OBS: Calibre o sensor alterando o valor da constante global THRESHOLD.
        
*/

// --- Mapa de pinos ---
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
#define LED_PIN  2 //D4


// --- Pinos do módulo HX711 ---
#define  ADDO   D4    //Data Out do primeiro módulo
#define  ADSK   D3    //SCK do primeiro módulo
#define  ADDO2  D6    //Data Out do segundo módulo
#define  ADSK2  D5    //SCK do segundo módulo


// --- Protótipo das Funções Auxiliares ---
unsigned long ReadCount();       //conversão AD do HX711 (primeiro módulo)
unsigned long ReadCount2();      //conversão AD do HX711 (segundo módulo)
void GetReference();             //calibragem automatica


// --- Constantes ---
const unsigned long THRESHOLD = 1000;   // AJUSTE DE SENSIBILIDADE DO SENSOR
const unsigned long LOOP_DELAY = 100;    // ms


// --- Variáveis Globais ---
unsigned long convert;       // valor lido no primeiro módulo
unsigned long convert2;      // valor lido no segundo módulo
unsigned long reference;     // valor padrão de leitura do sensor
unsigned long reference2;
boolean balance;             // flag indicando se o peso está distribuido no assento



// --- Configurações Iniciais ---
void setup()
{
   pinMode(ADDO, INPUT_PULLUP);   //entrada para receber os dados
   pinMode(ADSK, OUTPUT);         //saída para SCK
   pinMode(ADDO2, INPUT_PULLUP);  
   pinMode(ADSK2, OUTPUT);        
   
   Serial.begin(115200);    // o ESP8266 parece não trabalhar bem em 9600 bps

   Serial.print("\n\nCalibrando sensor...\n");
   GetReference();
   Serial.print("Referencia: ");
   Serial.print(reference);
   Serial.print("/");
   Serial.print(reference2);
   Serial.print("\n\n");

} //end setup


// --- Loop Infinito ---
void loop()
{
  convert = ReadCount();
  convert2 = ReadCount2();

  if(abs(convert - reference) > THRESHOLD || abs(convert2 - reference2) > THRESHOLD)
  {
    balance = false;
  }
  else
  {
    balance = true;
  }
  
  Serial.print("Sensor 1: ");
  Serial.print(convert);
  Serial.print("\t");
  Serial.print("Sensor 2: ");
  Serial.print(convert2);
  Serial.print("\t");
  Serial.print("Status: ");
  if(balance)
    Serial.print("Peso distribuido");
  else
    Serial.print("Peso mal distribuido");
  Serial.print("\n");

  
  delay(LOOP_DELAY);



} //end loop


// --- Funções ---
unsigned long ReadCount()
{
  unsigned long Count = 0;
  unsigned char i;
  
  digitalWrite(ADSK, LOW);
  
  while(digitalRead(ADDO));
  
  for(i=0;i<24;i++)
  {
     digitalWrite(ADSK, HIGH);
     Count = Count << 1;
     digitalWrite(ADSK, LOW);
     if(digitalRead(ADDO)) Count++;
  
  } //end for
  
  digitalWrite(ADSK, HIGH);
  Count = Count^0x800000;
  digitalWrite(ADSK, LOW);
  
  return(Count);


} //end ReadCount

unsigned long ReadCount2()
{
  unsigned long Count = 0;
  unsigned char i;
  
  digitalWrite(ADSK2, LOW);
  
  while(digitalRead(ADDO2));
  
  for(i=0;i<24;i++)
  {
     digitalWrite(ADSK2, HIGH);
     Count = Count << 1;
     digitalWrite(ADSK2, LOW);
     if(digitalRead(ADDO2)) Count++;
  
  } //end for
  
  digitalWrite(ADSK2, HIGH);
  Count = Count^0x800000;
  digitalWrite(ADSK2, LOW);
  
  return(Count);


} //end ReadCount2


void GetReference()
{
  for(int i=0; i<10; i++)
  {
    reference += ReadCount();
    reference2 += ReadCount2();
  }
  reference = reference/10;
  reference2 = reference2/10;
}






