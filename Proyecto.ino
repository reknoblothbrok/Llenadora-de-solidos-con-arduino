
///////////// Keypad ////////////////////
#include <Keypad.h>

const byte FILAS = 2;
const byte COLUMNAS = 2;

char keys[FILAS][COLUMNAS] = {
  { '1', '2'},
  { '4', '5'},
};
byte pinesFilas[FILAS] = { 11, 10};
byte pinesColumnas[COLUMNAS] = { 7, 6};

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

char TECLA;       // almacena la tecla presionada
// 1 = Bolsa de 50g
// 2 = Bolsa de 150g
// 4 = Bolsa de 300g
// 5 = Bolsa de 500g
/////////////////// Salidas ///////////////
int LED1 = 2;     //  LED 1, indica que ocmenzó el proceso
int LED2 = 3;     // LED 2, le manda señal a la banda transportadora pin 3
int LED3 = 12;    // LED 3, Señal de alerta pin 4
int LED4 = 4;    // LED 4, Resistencia para sellar y cortar la bolsa pin 5
int LED5 = 5;     // LED 5, Caudal pin 6

////////////////// Botones o sensores ///////////
int S_C = 8;      // Sensor Capacitivo (Detecta si hay o no bolsas)
int SNC = LOW;    //
int B_A = 13;      // Botón de arranque
int ba = LOW;
int B_P = 9;      // Botón de paro
int bp = LOW;
/////////////// Pot  ////////////////
long pot = A0;      // Potenciometro para indicar cuantas veces se ciclará
long valor;         // Lectura del Pot
int valor2;         // Escala del pot de 0 a 100

long pot2 = A1;     // Pot que representa la distancia (Sensor ultrasonico)
long d;             // Lectura de distancia
float d2;             // Escala de distancia

void setup()
{
  Serial.begin(9600);      // inicializa comunicacion serie
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(S_C, INPUT);
  pinMode(B_A, INPUT);
  pinMode(B_P, INPUT);

  
}
void loop()
{
  bp = digitalRead(B_P);

  if(bp != HIGH)
  {
  d = analogRead(pot2);
  d2 = (d * 10)/1024;
  Serial.print("El nivel del tanque es: ");
  Serial.println(d2);
  if(d2 > 1)
  {
  ba = digitalRead(B_A);
  if(ba == HIGH)
  {
  digitalWrite(LED1, HIGH);    // Indica que la maquina está encendida

  valor = analogRead(pot);
  valor2 = (valor * 100)/1024;
  Serial.print("La cantidad de veces que se debe ciclar son: ");
  Serial.println(valor2 + 1);
  delay(1000);
  TECLA = teclado.getKey();    // Obtiene tecla presionada y asigna a variable
  switch(TECLA)
  {
        case '1':                     // Se trabaja con las bolsas de 50g
           valor = analogRead(pot);
           valor2 = (valor * 100)/1024;
           for(int i = 0; i <= valor2; i++)
           {
           SNC = digitalRead(S_C);
           
           if(SNC == HIGH)
           {
             
             digitalWrite(LED4, HIGH);   // Sella la bolsa 
             delay(2000);                // El sellado permanece por 2s
             digitalWrite(LED4, LOW);    // Desactiva el sellado
             digitalWrite(LED2, HIGH);   // Se enciende la banda transportadora
             delay(1000);                // La banda transportadora avanza durante 1 segundo, arrastrando la bolsa a la medida deseada
             digitalWrite(LED2, LOW);
             digitalWrite(LED5, HIGH);   // Se abre el recipiente
             delay(2000);                // El caudal dura abierto 2s
             digitalWrite(LED5, LOW);    // Se cierra el Caudal
             }
           else                        // Enciende Alerta por falta de bolsas
           {
            for(int i = 1; i <= 10; i++)   //Parpadea el LED de alarma
            {
             digitalWrite(LED3, HIGH);
             delay(1000);
             digitalWrite(LED3, LOW);
             delay(1000);
            }
           }
             }
          break;
         case '2':                     // Se trabaja con las bolsa de 150g
             valor = analogRead(pot);
             valor2 = (valor * 100)/1024;
             for(int i = 0; i <= valor2; i++)
             {
          SNC = digitalRead(S_C);
          if(SNC == HIGH)
          {
             
          digitalWrite(LED4, HIGH);   // Sella la bolsa 
          delay(2000);                // El sellado permanece por 2s
          digitalWrite(LED4, LOW);    // Desactiva el sellado
          digitalWrite(LED2, HIGH);   // Se enciende la banda transportadora
          delay(3000);                // La banda transportadora avanza durante 3 segundos, arrastrando la bolsa a la medida deseada
          digitalWrite(LED2, LOW);
          digitalWrite(LED5, HIGH);   // Se abre el recipiente
          delay(3500);                // El caudal dura abierto 3.5s
          digitalWrite(LED5, LOW);    // Se cierra el Caudal
          }
          
          else                        // Enciende Alerta por falta de bolsas
          {
            for(int i = 1; i <= 10; i++)   //Parpadea el LED de alarma
            {
            digitalWrite(LED3, HIGH);
            delay(1000);
            digitalWrite(LED3, LOW);
            delay(1000);
            }
          }
             }
          break;
         case '4':                     // Se trabaja con las bolsa de 300g
             valor = analogRead(pot);
             valor2 = (valor * 100)/1024;

             for(int i = 0; i <= valor2; i++)
             {
          SNC = digitalRead(S_C);
          if(SNC == HIGH)
          {
            
          digitalWrite(LED4, HIGH);   // Sella la bolsa 
          delay(2000);                // El sellado permanece por 2s
          digitalWrite(LED4, LOW);    // Desactiva el sellado
          digitalWrite(LED2, HIGH);   // Se enciende la banda transportadora
          delay(6000);                // La banda transportadora avanza durante 6 segundos, arrastrando la bolsa a la medida deseada
          digitalWrite(LED2, LOW);
          digitalWrite(LED5, HIGH);   // Se abre el recipiente
          delay(6000);                // El caudal dura abierto 6s
          digitalWrite(LED5, LOW);    // Se cierra el Caudal
          }
          
          else                        // Enciende Alerta por falta de bolsas
          {
            for(int i = 1; i <= 10; i++)   //Parpadea el LED de alarma
            {
            digitalWrite(LED3, HIGH);
            delay(1000);
            digitalWrite(LED3, LOW);
            delay(1000);
            }
          }
             }
          break;
         case '5':                     // Se trabaja con las bolsa de 500g
             valor = analogRead(pot);
             valor2 = (valor * 100)/1024;

             for(int i = 0; i <= valor2; i++)
             {
          SNC = digitalRead(S_C);
          if(SNC == HIGH)
          {
            
          digitalWrite(LED4, HIGH);   // Sella la bolsa 
          delay(2000);                // El sellado permanece por 2s
          digitalWrite(LED4, LOW);    // Desactiva el sellado
          digitalWrite(LED2, HIGH);   // Se enciende la banda transportadora
          delay(10000);                // La banda transportadora avanza durante 10 segundos, arrastrando la bolsa a la medida deseada
          digitalWrite(LED2, LOW);
          digitalWrite(LED5, HIGH);   // Se abre el recipiente
          delay(8000);                // El caudal dura abierto 8s
          digitalWrite(LED5, LOW);    // Se cierra el Caudal
          }
          
          else                        // Enciende Alerta por falta de bolsas
          {
            for(int i = 1; i <= 10; i++)   //Parpadea el LED de alarma
            {
            digitalWrite(LED3, HIGH);
            delay(1000);
            digitalWrite(LED3, LOW);
            delay(1000);
            }
          }
             }
          break;
      }
  }
  else
 {
  digitalWrite(LED1, LOW);
 }
  }
  else
  {
    digitalWrite(LED1, LOW);
    for(int i = 1; i <= 10; i++)   //Parpadea el LED de alarma
            {
            digitalWrite(LED3, HIGH);
            delay(1000);
            digitalWrite(LED3, LOW);
            delay(1000);
            }
    }
 }
 else
 {
  digitalWrite(LED1, LOW);
 }
  
}
