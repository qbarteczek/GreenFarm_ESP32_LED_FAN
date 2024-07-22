#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT.h>

// WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// NTP Client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7200, 60000); // Offset UTC+2 for Poland

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT settings
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Pin settings
const int fanPin = 12;
const int lightPin = 13;

// Time settings
const int lightOnHour = 6;
const int lightOffHour = 18;

// WiFi connection attempts
const int maxWiFiAttempts = 20;

void setup() {
  // Begin Serial
  Serial.begin(115200);

  // Start WiFi
  WiFi.begin(ssid, password);
  int wifiAttempts = 0;
  while (WiFi.status() != WL_CONNECTED && wifiAttempts < maxWiFiAttempts) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    wifiAttempts++;
  }
