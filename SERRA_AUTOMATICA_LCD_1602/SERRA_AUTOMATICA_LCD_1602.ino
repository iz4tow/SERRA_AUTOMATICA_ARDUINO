//   Serra autonoma con sensore di temperatura e umidità (DHT11), igrometro, fotoresistore, display LCD 20x4, sensore livello acqua e relè.

// include the library code:
#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const int valore_limite = 27; //Valore dell'igrometro al quale il relay sarà ON

//DHT11 Sensor:
#include "DHT.h"
#define DHTPIN 12     // Sensore collegato al PIN 12
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup(){
// PIN 9 al Relè - IN1
Serial.begin(9600);
pinMode(9, OUTPUT);

// set up the LCD's number of columns and rows:
lcd.begin(16, 2);

Serial.println("Serra Autonoma di Franco Avino");
//lcd.print("Serra Autonoma");
  
// Avvio sensore DHT11  
  dht.begin();
}


void loop(){

// set the cursor to column 0, line 1
// (note: line 1 is the second row, since counting begins with 0):
lcd.setCursor(0, 0);

//Livello Acqua
int water = analogRead(A1);
Serial.print ("Sensore acqua: ");
Serial.println(water, DEC);  // Stampa il valore decimale del sensore di livello acqua
  
  if (water >= 100) {
    Serial.println("Acqua: OK"); // Stampa su LCD il testo
    lcd.print("Acqua: OK");
  }
  else{
    Serial.println("Acqua: BASSA"); // Stampa su LCD il testo
    lcd.print("Acqua: BASSA");
    alarm();
    flash();
    delay(2000); // Intervallo di 2 secondi
    }

// Igrometro
int igro = analogRead(A3); // Legge il valore analogico
int umdtrr = 0; // Variabile umidità suolo
umdtrr = map (igro, 100, 990, 100, 0); // converto il valore analogico in percentuale
Serial.print("Umidità del terreno: ");
Serial.print(umdtrr);
Serial.println("%"); //Stampa a schermo il valore
// set the cursor to column 0, line 1
// (note: line 1 is the second row, since counting begins with 0):
lcd.setCursor(0, 1);
lcd.print("Umido: "+String(umdtrr)+"%");

if (umdtrr <= valore_limite)
  digitalWrite(9,HIGH); // Attiva Relè 1
else
  digitalWrite(9,LOW); // Spegni Relè 1
delay(2000); // Attende due secondi


// Lettura umidità e temperatura del sensore DHT11
int h = dht.readHumidity();
int t = dht.readTemperature();

// Misura la temperatura e se maggiore di 40 gradi attiva relè per accendere la ventola
if (t >= 40 )
   digitalWrite (10, HIGH); // Attiva Relè 2
else
   digitalWrite (10, LOW); // Spegni Relè 2
delay (2000);

  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print("C, Umid: ");
  Serial.print(h);
  Serial.println("%");
}

void alarm(){
  tone(8,850,700);  // Imposta tono acustico su PIN 8
  delay(150);       // Aspetta per 0,15 secondi
  tone(8,850,700);  // Imposta tono acustico su PIN 8
  delay(150);       // Aspetta per 0,15 secondi
}

void flash() {
  digitalWrite(13, HIGH);   // Imposta il LED su ON
  delay(1000);               // Aspetta per 1 secondo
  digitalWrite(13, LOW);    // Impostiamo il LED su OFF
  delay(1000);               // Aspetta per 1 secondo
}

