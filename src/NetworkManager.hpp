#include <Arduino.h>
#include <SoftwareSerial.h>

class NetworkManager {
public:
	NetworkManager();

	bool wifiConnect(const String &ssid, const String &password);
	bool updateFeed(float temperature, float rain, double pressure, unsigned long lightLevel);

	bool isConnected();

	String sendCommand(String& command, const unsigned int timeout);
private:
	SoftwareSerial esp = SoftwareSerial(9, 10);

	String networkName;
	String networkPassword;
	String apiKey;

	String channel;
	String protocol;
	String hostname;
	String port;

	bool connected;
};
