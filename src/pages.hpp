#include "sensorData.hpp"

String getTime(tmElements_t);

const int rightButtonPin = 1, leftButtonPin = 2;
short int screenPage = 0;

void overviewPage()
{
	lcd.home();

	lcd.print(getTime(tm));

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

String getTime(tmElements_t tm)
{
	String hour, min, sec;

	if(tm.Hour < 10)
		hour = "0" + String(tm.Hour);
	else
		hour = String(tm.Hour);

	if(tm.Hour < 10)
		min = "0" + String(tm.Minute);
	else
		min = String(tm.Minute);

	if(tm.Hour < 10)
		sec = "0" + String(tm.Second);
	else
		sec = String(tm.Second);

	return hour + ":" + min + ":" + sec;
}
