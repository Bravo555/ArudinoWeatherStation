#include "sensorData.hpp"

const int rightButtonPin = 1, leftButtonPin = 2;
short int screenPage = 0;

void overviewPage()
{
	lcd.home();

	lcd.print("Temperatura: ");
	lcd.print(temperature);

	lcd.setCursor(0, 1);
	lcd.print("Czy pada: ");
	lcd.print(rainStatus ? "tak" : "nie");

	lcd.setCursor(14,1);
	tmElements_t tm;
	lcd.print(tm.Hour);
	lcd.print(":");
	lcd.print(tm.Minute);
	lcd.print(":");
	lcd.print(tm.Second);
	lcd.print(":");

	lcd.setCursor(0, 2);
	lcd.print("Swiatlo: ");
	lcd.print(lightLevel);
	lcd.print("lx");

	lcd.setCursor(0, 3);
	lcd.print("Cisnienie: ");
	lcd.print(pressure);
	lcd.print("kPa");
}

void screenPrinting()
{
		if(digitalRead(rightButtonPin)==LOW)
			screenPage++;
		if(digitalRead(leftButtonPin)==LOW)
			screenPage--;
		switch(screenPage)
		{
			case 0:
				overviewPage();
			break;
			case 1:

			break;
		}
}
