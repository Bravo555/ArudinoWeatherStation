const int pinTermometru = 0;
void setup() {
Serial.begin(9600);

}

float odczyt_temperatury(){
float temperatura;
temperatura = (analogRead(pinTermometru)/1024.0)*500;
temperatura = temperatura - 276;
return temperatura;
}

void loop() {
Serial.println(odczyt_temperatury());
delay(1000);
}
