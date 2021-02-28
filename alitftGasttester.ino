#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

// Color definitions
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GassensorPin A4
#define __CS 10
#define __DC 9
#define __RST 12

//#define __CS 10
//#define __DC 8
//#define __RST 9
float Gassensor1;
float Gassensor2;
TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC, __RST);
int counter ;
int PUSHER = 0 ;
const unsigned char sinagua [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0xFF, 0xC0, 0x00, 0x00, 0x0F, 0xE3, 0xF0, 0x00, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x00, 0x71,
  0x00, 0x8E, 0x00, 0x00, 0xE2, 0x00, 0x47, 0x00, 0x01, 0x86, 0x00, 0x61, 0x80, 0x03, 0x0C, 0x00,
  0x30, 0xC0, 0x07, 0x0C, 0x00, 0x30, 0xE0, 0x06, 0x1C, 0x00, 0x38, 0x60, 0x0C, 0x1C, 0x00, 0x38,
  0x30, 0x0C, 0x1C, 0x7E, 0x38, 0x30, 0x18, 0x1D, 0xFF, 0xB8, 0x18, 0x18, 0x3F, 0xE7, 0xFC, 0x18,
  0x18, 0x7F, 0x81, 0xFE, 0x18, 0x18, 0xFF, 0xC3, 0xFF, 0x18, 0x19, 0xE7, 0xFF, 0xE7, 0x88, 0x11,
  0x86, 0xE7, 0x61, 0x88, 0x13, 0x06, 0x66, 0x60, 0xC8, 0x1A, 0x06, 0x24, 0x60, 0x58, 0x1A, 0x07,
  0x3C, 0xE0, 0x58, 0x1A, 0x03, 0x18, 0xE0, 0x58, 0x18, 0x03, 0xDB, 0xC0, 0x18, 0x08, 0x01, 0xFF,
  0x80, 0x18, 0x0C, 0x00, 0xFF, 0x00, 0x30, 0x0C, 0x00, 0x3C, 0x00, 0x30, 0x06, 0x00, 0x7E, 0x00,
  0x60, 0x07, 0x00, 0xFF, 0x00, 0xE0, 0x03, 0x33, 0xFF, 0xCC, 0xC0, 0x01, 0x9F, 0xC3, 0xF9, 0x80,
  0x00, 0xE0, 0x00, 0x07, 0x00, 0x00, 0x70, 0x00, 0x0E, 0x00, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x00,
  0x0F, 0xE7, 0xF0, 0x00, 0x00, 0x01, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

void setup(void) {
  Serial.begin(9600);
  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(BLACK);
  tft.setCursor(3, 30);// default for cheapo tft 128x128 , 0x0
  tft.setTextSize(1);
  tft.setTextColor(RED);
  tft.println("   STARTING SYSTEM  ");
  tft.drawBitmap(45, 50, sinagua, 40, 40, YELLOW);
  delay(1000);
  tft.fillScreen(BLACK);
}


void loop() {
  // tft.fillRect(0, 80, 128, 12, WHITE);
  if (counter > 128) {
    tft.fillRect(0, 60, 128, 75, BLACK);
    counter = 0;
  }
  tft.fillRect(2, 26, 55, 14, BLACK);
  tft.fillRect(80, 26, 55, 14, BLACK);
  Gassensor1 = analogRead(GassensorPin);
  Gassensor1 = map(Gassensor1, 0, 1024, 0, 100);
  tft.setCursor(3, 14);
  tft.setTextColor(MAGENTA);
  tft.println("  ! BAD AIR SENSOR !");
  tft.setCursor(3, 50);
  tft.setTextColor(CYAN);
  tft.print("AIR% =");
  tft.fillRect(47, 46, 40, 12, BLACK);
  tft.setCursor(50, 50);
  tft.print(Gassensor1);
  if (Gassensor1 > 0 && Gassensor1 < 15) {
    tft.drawBitmap(45, 70, sinagua, 40, 40, GREEN);
    tft.setCursor(80, 28);
    tft.setTextColor(BLUE);
    tft.println("AIR OK");
  }
  if (Gassensor1 > 15 && Gassensor1 < 60) {
    tft.drawBitmap(45, 70, sinagua, 40, 40, YELLOW);
    tft.setCursor(80, 28);
    tft.setTextColor(YELLOW);
    tft.println("NOT OK");
  }
  if (Gassensor1 > 60 && Gassensor1 < 100) {
    tft.drawBitmap(45, 705, sinagua, 40, 40, RED);
    tft.setCursor(80, 28);
    tft.setTextColor(YELLOW);
    tft.println("! BAD ! ");
  }
  counter = counter + 1 ;
  if (Gassensor1 > 0 && Gassensor1 <= 5) {
    tft.setCursor(3, 28);
    tft.setTextColor(BLUE);
    tft.println("WAITING");
    // counter = 0;
  }
  if (Gassensor1 > 5 && Gassensor1 < 100) {
    tft.setCursor(3, 28);
    tft.setTextColor(GREEN);
    tft.println("SNIFFING");
  }
  Gassensor2 = analogRead(GassensorPin);
  Gassensor2 = map(Gassensor2, 0, 1024, 128, 61);
  tft.drawLine(0, 65, 128, 65, RED);
  tft.drawLine(0, 45, 128, 45, RED);
  if (Gassensor1 >= 0 && Gassensor1 <= 4) tft.drawLine(counter, 128, counter, Gassensor2, GREEN);
  if (Gassensor1 > 4 && Gassensor1 < 70){
    tft.drawLine(counter, 128, counter, Gassensor2, YELLOW);
    tft.drawLine(counter, 128, counter, Gassensor2 + 3, GREEN);
  }
  if (Gassensor1 >= 70 && Gassensor1 < 101) {
    tft.drawLine(counter, 128, counter, Gassensor2, RED);
    tft.drawLine(counter, 128, counter, Gassensor2 + 3, YELLOW);
  }
  delay(50);
}

