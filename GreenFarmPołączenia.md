Schemat Połączeń
OLED Display:
SDA (OLED) -> Pin 21 (ESP32)
SCL (OLED) -> Pin 22 (ESP32)
VCC -> 3.3V (ESP32)
GND -> GND (ESP32)
DHT22:
VCC -> 3.3V (ESP32)
GND -> GND (ESP32)
Data -> Pin 4 (ESP32)
Wiatraczek i Oświetlenie przez tranzystory:
Wiatraczek:

Kolektor -> Wiatraczek (czerwony)
Emiter -> GND
Baza -> Rezystor 1k -> Pin 12 (ESP32)
Oświetlenie:

Kolektor -> Oświetlenie LED (czerwony)
Emiter -> GND
Baza -> Rezystor 1k -> Pin 13 (ESP32)


tranzystory mają być npn czy pnp ?

W Twoim przypadku najlepiej użyć tranzystorów typu NPN, takich jak np. 2N2222 lub BC547. Tranzystory NPN są łatwiejsze do sterowania w przypadku mikrokontrolerów takich jak ESP32, ponieważ wymagają one sygnału wysokiego na bazie, aby przewodzić prąd między kolektorem a emiterem.

Połączenia z tranzystorami NPN:
Wiatraczek:

Kolektor (C) -> Czerwony przewód wiatraczka
Emiter (E) -> Masa (GND)
Baza (B) -> Rezystor 1k -> Pin 12 (ESP32)
Oświetlenie LED:

Kolektor (C) -> Czerwony przewód LED
Emiter (E) -> Masa (GND)
Baza (B) -> Rezystor 1k -> Pin 13 (ESP32)
Schemat z tranzystorami NPN:
                 +5V
                  |
                 |
       +---------+---------+
       |         |         |
      LED       Wiatraczek |
       |         |         |
       |        |          |
       |        |          |
     Kolektor  Kolektor    |
       |        |          |
       |        |          |
    Emiter    Emiter       |
       |        |          |
       |        |          |
      Masa      Masa       |
                 |         |
            \|/  |         |
            Rezystor 1k    |
            /|\  |         |
                Baza       |
                 |         |
                Pin 13   Pin 12
                (ESP32)  (ESP32)
Opis działania:
Kolektor tranzystora NPN jest podłączony do dodatniego przewodu wiatraczka lub LED.
Emiter tranzystora jest podłączony do masy (GND).
Baza tranzystora jest podłączona do pinu ESP32 przez rezystor 1k, który ogranicza prąd bazy, chroniąc tranzystor i mikrokontroler.
