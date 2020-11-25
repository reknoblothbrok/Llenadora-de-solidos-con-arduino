#include <Keypad.h>

const byte FILAS = 4;
const byte COLUMNAS = 3;

char keys[FILAS][COLUMNAS] = {
  { '1', '2', '3'},
  { '4', '5', '6'},
  { '7', '8', '9'},
  { '*', '0', '#'}
};
byte pinesFilas[FILAS] = { 11, 10, 9, 8};
byte pinesColumnas[COLUMNAS] = { 7, 6, 5};

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

char TECLA;       // almacena la tecla presionada
// 1 = Bóton de arranque
// 2 = Botón de paro de emergencia
// 3 = Botón de paro
// 4 = Sensor de bolsa (Capasitivo)
// 5 = Bolsa de 50g
// 6 = Bolsa de 150g
// 7 = Bolsa de 300g
// 8 = Bolsa de 500g
int LED1 = 2;     // LED 1, indica que comenzó el proceso
int LED2 = 3;     // LED 2, le manda señal a la banda transportadora
int LED3 = 12;    // LED 3, Señal de alerta
int LED4 = 13;    // LED 4, Resistencia para sellar y cortar la bolsa
int LED5 = 4;     // LED 5, Caudal

void setup()
{
  Serial.begin(9600);      // inicializa comunicacion serie
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
}
void loop()
{
  TECLA = teclado.getKey();    // obtiene tecla presionada y asigna a variable
  if (TECLA == '1')           // Se inicia el programa
  {
    digitalWrite(LED1, HIGH);
    digitalRead(TECLA);
    if (TECLA == '4')     // Si detecta que hay bolsas
    {
      TECLA = teclado.getKey();    // obtiene tecla presionada y asigna a variable
      switch(TECLA)
      {
        case '5':                     // Se trabaja con las bolsas de 50g
          digitalWrite(LED4, HIGH);   // Sella la bolsa 
          delay(2000);                // El sellado permanece por 2s
          digitalWrite(LED4, LOW);    // Desactiva el sellado
          digitalWrite(LED2, HIGH);   // Se enciende la banda transportadora
          delay(1000);                // La banda transportadora avanza durante 1 segundo, arrastrando la bolsa a la medida deseada
          digitalWrite(LED5, HIGH);   // Se abre el recipiente
          delay(2000);                // El caudal dura abierto 2s
          digitalWrite(LED5, LOW);    // Se cierra el Caudal
          break;
         case '6':                     // Se trabaja con las bolsa de 150g
          digitalWrite(LED4, HIGH);   // Sella la bolsa 
          delay(2000);                // El sellado permanece por 2s
          digitalWrite(LED4, LOW);    // Desactiva el sellado
          digitalWrite(LED2, HIGH);   // Se enciende la banda transportadora
          delay(3000);                // La banda transportadora avanza durante 3 segundos, arrastrando la bolsa a la medida deseada
          digitalWrite(LED5, HIGH);   // Se abre el recipiente
          delay(3500);                // El caudal dura abierto 3.5s
          digitalWrite(LED5, LOW);    // Se cierra el Caudal
          break;
         case '7':                     // Se trabaja con las bolsa de 300g
          digitalWrite(LED4, HIGH);   // Sella la bolsa 
          delay(2000);                // El sellado permanece por 2s
          digitalWrite(LED4, LOW);    // Desactiva el sellado
          digitalWrite(LED2, HIGH);   // Se enciende la banda transportadora
          delay(6000);                // La banda transportadora avanza durante 6 segundos, arrastrando la bolsa a la medida deseada
          digitalWrite(LED5, HIGH);   // Se abre el recipiente
          delay(6000);                // El caudal dura abierto 6s
          digitalWrite(LED5, LOW);    // Se cierra el Caudal
          break;
         case '8':                     // Se trabaja con las bolsa de 500g
          digitalWrite(LED4, HIGH);   // Sella la bolsa 
          delay(2000);                // El sellado permanece por 2s
          digitalWrite(LED4, LOW);    // Desactiva el sellado
          digitalWrite(LED2, HIGH);   // Se enciende la banda transportadora
          delay(10000);                // La banda transportadora avanza durante 10 segundos, arrastrando la bolsa a la medida deseada
          digitalWrite(LED5, HIGH);   // Se abre el recipiente
          delay(8000);                // El caudal dura abierto 8s
          digitalWrite(LED5, LOW);    // Se cierra el Caudal
          break;
      }
    }
  } 
}
