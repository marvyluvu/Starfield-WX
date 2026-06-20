#include <DHT.H>
#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>


#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#define NEOPIXEL_PIN 6
#define NUM_PIXELS 16
Adafruit_Neopixel pixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

enum ScreenMode {
    SCREEN_TEMP,
    SCREEN_HUM,
    SCREEN_DEW,

};

ScreenMode currentScreen = SCREEN_TEMP;
unsigned long lastScreenChange = 0;
const unsigned long SCREEN_INTERVAL = 4000; // ms

unsigned long lastRead = 0;
const unsigned long READ_INTERVAL = 2000; //ms

float tC = NAN;
float h = NAN;
float dew = NAN;
String dewRisk = "UNKNOWN";
unint32_t riskColor = 0;

float computeDewPoint(float tempC, float humidity) {
    if (humidity <= 0 || humidity > 100 || isnan(tempC)) return NAN;
    float a = 17.27;
    float b = 237.7;
    float alpha = ((a * tempC) / (b + tempC)) + log(humidity / 100.0);
    float dp = (b * alpha) / (a - alpha);
    return dp;

}

void computeDewRisk() {
    if (isnan(tC) || isnan(dew)) {
        dewRisk = "NO DATA";
        riskColor = pixels.Color(0,0,0);
        return;
    }

    float spread = tC - dew;

    if (spread > 3) {
        dewRisk = "LOW";
        riskColor = pixels.Color(0, 150, 0);
    } else if (spread > 1.0){
        dewRisk = "MEDIUM";
        riskColor = pixels.Color(255, 140, 0);
    } else {
        dewRisk = "HIGH";
        riskColor = pixels.Color(200, 0 , 0)
    }
}
void showRiskOnHalo() {
    for (int i = 0; i < NUM_PIXELS; i++){
        pixels.setPixelColor(i, riskColor);
    }
    pixels.show();
}

void updateLCD() {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("STARFIELD WX")

    lcd.setCursor(0,1);
    switch (currentScreen) {
        case SCREEN_TEMP:
        lcd.print("T: ");
        if (isnan(tC)) lcd.print("--.-");
        else {
            lcd.print(tC, 1);
            lcd.print((char)223);
            lcd.print("C");
        }
        lcd.print(" ");
        lcd.print("R: ");
        lcd.print(dewRisk);
        break;

    case SCREEN_HUM:
    lcd.print("H: ");
    else {
        lcd.print(h, 1);
        lcd.print("%");

    }
    lcd.print(" ");
    lcd.print("R:")
    lcd.print(dewRisk);
    break;

    case SCREEN_DEW:
      lcd.print("DEW: ");
      if (isnan(dew)) lcd.print("--.-");
      else {
        lcd.print(dew, 1);
        lcd.print((char)223);
        lcd.print("C");
      }
      lcd.print(" ");
      lcd.print("R:");
      lcd.print(dewRisk);
      break;
  }
}

void setup() {
    dht.begin();
    lcd.begin(16, 2);
    pixels.begin();
    pixels.clear();
    pixels.show();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("STARFIELD");
    lcd.setcCursor(0, 1);
    lcd.print("Booting...");
    delay(1500);

}
void loop() {
    unsigned long now = millis();

    if (now - lastRead >= READ_INTERVAL){
        lastRead = now;
        float newH = dht.readHumidity();
        float newT = dht.readTemperature();

        if (!isnan(newH) && !isnan(newT)) {
            h = newH;
            tC = newT;
            dew = computeDewPoint(tC, h);
            computeDewRisk();
            showRiskOnHalo();
        }
    }
  if (now - lastScreenChange >= SCREEN_INTERVAL) {
    lastScreenChange = now;

    if (currentScreen == SCREEN_TEMP)      currentScreen = SCREEN_HUM;
    else if (currentScreen == SCREEN_HUM)  currentScreen = SCREEN_DEW;
    else                                   currentScreen = SCREEN_TEMP;

    updateLCD();
  }
}