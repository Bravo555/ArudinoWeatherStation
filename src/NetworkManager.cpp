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

	sendCommand("AT+CIPSTART=\""
				+ protocol + "\",\""
				+ hostname + "\","
				+ port, 250);

	sendCommand("AT+CIPSEND=" + String(request.length() + 2), 500);
	delay(100);
	sendCommand(request, 500);
}

String NetworkManager::sendCommand(String& command, const unsigned int timeout)
{
	Serial.println(command);

	String response = "";

    esp.println(command);

    unsigned long int time = millis();

    while((time+timeout) > millis())
    {
    	while(esp.available())
    	{
    		char c = esp.read();
    		response += c;
    	}
    }
    Serial.println(response);
    return response;
}
