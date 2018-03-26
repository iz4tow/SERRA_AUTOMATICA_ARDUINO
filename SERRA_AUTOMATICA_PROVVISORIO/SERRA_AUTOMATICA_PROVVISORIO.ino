//   Serra autonoma con sensore di temperatura e umidità (DHT11), igrometro, fotoresistore, display LCD 20x4, sensore livello acqua e relè.


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

Serial.println("Serra Autonoma di Franco Avino");
  
// Avvio sensore DHT11  
  dht.begin();
}


void loop(){
  
//Livello Acqua
int water = analogRead(A1);
Serial.print ("Sensore acqua: ");
Serial.println(water, DEC);  // Stampa il valore decimale del sensore di livello acqua
  
  if (water >= 100) {
    Serial.println("Acqua: OK"); // Stampa su LCD il testo
  }
  else{
    Serial.println("Acqua: BASSA"); // Stampa su LCD il testo
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
  tone(3,850,700);  // Imposta tono acustico su PIN 3
  delay(150);       // Aspetta per 0,15 secondi
  tone(3,850,700);  // Imposta tono acustico su PIN 3
  delay(150);       // Aspetta per 0,15 secondi
}

void flash() {
  digitalWrite(13, HIGH);   // Imposta il LED su ON
  delay(1000);               // Aspetta per 1 secondo
  digitalWrite(13, LOW);    // Impostiamo il LED su OFF
  delay(1000);               // Aspetta per 1 secondo
}

