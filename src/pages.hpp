#include "sensorData.hpp"

String getTime(tmElements_t);

const int rightButtonPin = 4, leftButtonPin = 5;
short int screenPage = 0;

void overviewPage()
{
	lcd.home();

	lcd.print(getTime(tm));

	lcd.setCursor(0,1);
	lcd.print(temperature);

	lcd.setCursor(0, 2);
	lcd.print("Swiatlo: ");
	lcd.print(lightLevel);
	lcd.print(" lx");

	lcd.setCursor(0, 3);
	lcd.print("Cisn: ");
	lcd.print(pressure);
	lcd.print("hPa");
}

void screenPrinting()
{
	lcd.clear();
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
RTC.read(tm);
	if(tm.Hour < 10)
		hour = "0" + String(tm.Hour);
	else
		hour = String(tm.Hour);

	if(tm.Minute < 10)
		min = "0" + String(tm.Minute);
	else
		min = String(tm.Minute);

	if(tm.Second < 10)
		sec = "0" + String(tm.Second);
	else
		sec = String(tm.Second);

	return hour + ":" + min + ":" + sec;
}
