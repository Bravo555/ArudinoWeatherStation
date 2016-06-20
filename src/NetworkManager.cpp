#include "NetworkManager.hpp"

NetworkManager::NetworkManager()
{
	esp.begin(9600);
	connected = false;

	protocol = "TCP";
	hostname = "api.thingspeak.com";
	port = "80";

	apiKey = "P1U3BM0XT5L8M4UI";
}

bool NetworkManager::wifiConnect(const String &ssid, const String &password)
{
	esp.println("AT+CWMODE=1");
	delay(200);
	esp.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");

	if (esp.available()) {
    	Serial.write(esp.read());
		connected = true;
		return true;
	}
	else
		return false;
}

bool NetworkManager::isConnected()
{
	return connected;
}

bool NetworkManager::updateFeed(float temperature, float rain, double pressure, unsigned long lightLevel)
{
	String request = "GET /update?api_key=" + apiKey
					+ "&field1=" + String(temperature)
					+ "&field2=" + String(rain)
					+ "&field3=" + String(pressure)
					+ "&field4=" + String(lightLevel);
	delay(100);

	esp.println("AT+CIPSTART=\""
	 			+ protocol + "\",\""
				+ hostname + "\","
				+ port);

	esp.println("AT+CIPSEND=" + String(request.length() + 2));
	delay(100);
	esp.println(request);
}
