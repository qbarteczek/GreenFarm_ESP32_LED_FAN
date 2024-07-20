Połączenia
ESP32:
OLED (I2C):

SDA (OLED) -> Pin 21 (ESP32)
SCL (OLED) -> Pin 22 (ESP32)
VCC -> 3.3V (ESP32)
GND -> GND (ESP32)
DHT22:

VCC -> 3.3V (ESP32)
GND -> GND (ESP32)
Data -> Pin 4 (ESP32) (można dowolnie zmienić)
Wiatraczek i oświetlenie przez tranzystory:

Wiatraczek:
Kolektor -> Wiatraczek (czerwony)
Emiter -> GND
Baza -> Rezystor 1k -> Pin 12 (ESP32)
Oświetlenie:
Kolektor -> Oświetlenie LED (czerwony)
Emiter -> GND
Baza -> Rezystor 1k -> Pin 13 (ESP32)
