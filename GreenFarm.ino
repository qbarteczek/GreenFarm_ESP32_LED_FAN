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

void setup() {
  // Begin Serial
  Serial.begin(115200);

  // Start WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Start NTP Client
  timeClient.begin();

  // Initialize DHT
  dht.begin();

  // Initialize OLED
  if(!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Set pin modes
  pinMode(fanPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
}

void loop() {
  timeClient.update();
  String formattedTime = timeClient.getFormattedTime();
  int currentHour = timeClient.getHours();

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Display on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Time: ");
  display.println(formattedTime);
  display.print("Temp: ");
  display.print(t);
  display.println(" C");
  display.print("Humidity: ");
  display.print(h);
  display.println(" %");
  display.display();

  // Control fan
  if (h > 30.0) {
    digitalWrite(fanPin, HIGH);
  } else {
    digitalWrite(fanPin, LOW);
  }

  // Control light
  if (currentHour >= lightOnHour && currentHour < lightOffHour) {
    digitalWrite(lightPin, HIGH);
  } else {
    digitalWrite(lightPin, LOW);
  }

  delay(10000); // Update every 10 seconds
}
