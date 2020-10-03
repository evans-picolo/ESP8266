/*
        SENSOR DE ASSENTO

        Código para ler o valor dos dois módulos HX711 usados para 
        sensoriar o assento no protótipo do projeto Ergolax.
        
        Evans Picolo
        out/2020
        
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
unsigned long ReadCount();  //conversão AD do HX711 (primeiro módulo)
unsigned long ReadCount2(); //conversão AD do HX711 (segundo módulo)


// --- Variáveis Globais ---
unsigned long convert;    // valor lido no primeiro módulo
unsigned long convert2;   // valor lido no segundo módulo


// --- Configurações Iniciais ---
void setup()
{
   pinMode(ADDO, INPUT_PULLUP);   //entrada para receber os dados
   pinMode(ADSK, OUTPUT);         //saída para SCK
   pinMode(ADDO2, INPUT_PULLUP);  
   pinMode(ADSK2, OUTPUT);        
   
   Serial.begin(115200);    // o ESP8266 parece não trabalhar bem em 9600 bps

} //end setup


// --- Loop Infinito ---
void loop()
{
  
  convert = ReadCount();
  convert2 = ReadCount2();
  
  Serial.print("Sensor 1: ");
  Serial.print(convert);
  Serial.print("\t");
  Serial.print("Sensor 2: ");
  Serial.print(convert2);
  Serial.print("\n");
  
  delay(100);



} //end loop


// --- Funções primeiro sensor --
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


// --- Função segundo sensor --
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







