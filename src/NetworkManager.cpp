#include "NetworkManager.hpp"

NetworkManager::NetworkManager()
{
	esp.begin(9600);
	esp.println("AT+CIPMUX=1");
	connected = false;

	channel = "0";
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

bool NetworkManager::updateFeed(String field, String value)
{
	String request = "GET /update?api_key=" + apiKey + "&" + field + "=" + value;
	delay(100);

	esp.println("AT+CIPSTART=" + channel + ",\""
	 			+ protocol + "\",\""
				+ hostname + "\","
				+ port);

	esp.println("AT+CIPSEND=" + channel + "," + String(request.length() + 2));
	delay(100);
	esp.println(request);
}
