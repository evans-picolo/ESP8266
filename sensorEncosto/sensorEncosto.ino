/*
        PIEZO

        Teste de sensor de força/contato com cápsula peizoelétrica.

        Evans Picolo
        out/2020

 */

// --- Mapeamento de pinos ---
#define  PZT  A0


// --- Protótipos das funções ---
boolean verifyBack();    //Retorna true se estiver encostado (leitura > 0) e false se não estiver


// --- Constantes ---
const unsigned int PZT_THRESHOLD = 10;


// --- Variáveis globais ---
unsigned int  piezo;        //Leitura do piezo
unsigned long loopCount;    //Contador de loops
boolean       lean;         //1 = encostado / 0 = nao encostado
unsigned char cooldown;     //Quantidades de loops para ignorar após uma mudança de estado para evitar instabilidade;


// --- Conifutrações iniciais ---
void setup()
{
    Serial.begin(112500);
    Serial.println();

    lean = false;
    cooldown = 4;
    loopCount = 0;
}


// --- Loop infinito ---
void loop()
{
    piezo = analogRead(PZT);

    lean = verifyBack();
    
    Serial.print(loopCount);
    Serial.print("\t");
    Serial.print("Piezo: ");
    Serial.print(piezo);
    Serial.print("   ");
    if(lean)
        Serial.print("Encostado");
    else
        Serial.print("Não encostado!");
    Serial.print("\n");

    loopCount++;
    cooldown++;
    delay(500);

} //end loop


// --- Funções auxiliares ---

boolean verifyBack()
{
    if(piezo > PZT_THRESHOLD && cooldown > 3)
    {
        cooldown = 0;
        return !lean;
    }
    else
    {
        return lean;
    }  
    
} // end verifyPiezo;

