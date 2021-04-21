/*
   Sistema de seguridad con una teclado matricial y una pantalla LCD 16x2
*/
#include <LiquidCrystal.h>
#include <Adafruit_Keypad.h>

//Alarmas
const int redLed = PB3;
const int greenLed = PB4;
const int buzzer = PB5;

//Posiciones de memoria
char* password = "1337";  //Contraseña
int pos = 0; //Variable a guardar la posición del keypad

//Configuración del teclado matricial
const byte ROWS = 4;  //Filas
const byte COLS = 4;  //Columnas
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {PB12, PB13, PB5, PB15}; //Declaración de pines para las filas
byte colPins[COLS] = {PA8, PA9, PA10, PB6};   //Declaración de pines para las columnas

//Declaración de objetos en función a las librerias
Adafruit_Keypad panelDeControl = Adafruit_Keypad (makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd (PB0, PB1, PA7, PA6, PA5, PA4);

void setup() {
  lcd.begin (16, 2);        //Activación de la pantalla lcd
  panelDeControl.begin ();  //Activación del teclado matricial
  setLocked (true);         //Activación del bloqueo de la cerradura

  pinMode (redLed, OUTPUT);
  pinMode (greenLed, OUTPUT);
  pinMode (buzzer, OUTPUT);
}

void loop() {
  //Inicio del sistema
  lcd.setCursor(3, 0);
  lcd.print("Bienvenido,");
  lcd.setCursor(2, 1);
  lcd.print("Señor usuario.");
  delay(2500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Digite su pass");
  
  panelDeControl.tick();
  //Proceso de lectura para el teclado matricial
  while (panelDeControl.available()) {
    keypadEvent e = panelDeControl.read();

    //Si se presiona una de los teclas no numericas, denegar el acceso inmediatamente
    if ((char)e.bit.KEY == '*' || (char)e.bit.KEY == '#' || (char)e.bit.KEY == 'A' || (char)e.bit.KEY == 'B' || (char)e.bit.KEY == 'C' || (char)e.bit.KEY == 'D') {
      pos = 0;
      setLocked (true);
      lcd.clear();
      lcd.setCursor(0, 0);  lcd.print("Acceso");
      lcd.setCursor(0, 1);  lcd.print("Denegado");
      delay(2500);
      lcd.clear();
    }

    //Comparando el tamaño del arreglo para verificar la contraseña - Seguridad baja
    //Si se presiona otra tecla, se registra el cambio en la posición en función a la contraseña
    if ((char)e.bit.KEY == password [pos]) {
      pos++;
    }

    //Si la contraseña es correcta
    if (pos == 4) {
      setLocked (false);  //Se desbloquea la "cerradura"

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Tabien");
      delay(3000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Acceso");
      lcd.setCursor(0, 1);
      lcd.print("Permitido");
      delay(10000);
      lcd.clear();
    }

    //Si la contraseña es correcta
    if (pos == 4) {
      setLocked (false);  //Se desbloquea la cerradura

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Tabien");
      delay(3000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Acceso");
      lcd.setCursor(0, 1);
      lcd.print("Permitido");
      delay(10000);
      lcd.clear();
    }
    delay(100);
  }
}

void setLocked(int locked) {
  if (locked) {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
  }
  else {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
  }
}
