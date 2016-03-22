const int pinTermometru = 0;
const int pinCzujnikaOpadow = 2;
void setup() {
Serial.begin(9600);

}

bool badanie_opadow(){
bool Deszcz;
if(analogRead(pinCzujnikaOpadow)<400)
    Deszcz = 1;
else
    Deszcz = 0;
return Deszcz;
}

float odczyt_temperatury(){
float temperatura;
temperatura = (analogRead(pinTermometru)/1024.0)*500;
temperatura = temperatura - 277;
return temperatura;
}

void loop() {
Serial.println(odczyt_temperatury());
Serial.println(badanie_opadow());
delay(1000);
}
