#include "sensorData.hpp"

void overviewPage()
{
	lcd.home();

	lcd.print("Temperature: ");
	lcd.print(temperature);

	lcd.setCursor(0, 1);
	lcd.print("Is raining: ");
	lcd.print(rainStatus ? "yes" : "no");

	lcd.setCursor(0, 2);
	lcd.print("Light: ");
	lcd.print(lightLevel);
	lcd.print("lx");

	lcd.setCursor(0, 3);
	lcd.print("Pressure: ");
	lcd.print(pressure);
	lcd.print("kPa");
}
