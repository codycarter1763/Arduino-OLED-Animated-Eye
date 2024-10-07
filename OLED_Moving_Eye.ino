#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int eyeRadius = 10;
int pupilRadius = 4;
int eyeX = SCREEN_WIDTH / 2;
int eyeY = SCREEN_HEIGHT / 2;
int pupilX = eyeX;
int pupilY = eyeY;
int blinkState = 0;
unsigned long previousMillis = 0;
const long blinkInterval = 2000;
bool isBlinking = false;


void setup() {
  display.clearDisplay();
  display.display();
  delay(1000);
}

void Eye()
{
  display.clearDisplay();
  display.drawCircle(eyeX, eyeY, eyeRadius, SSD1306_WHITE);
  display.fillCircle(pupilX, pupilY, pupilRadius, SSD1306_WHITE);
  display.display();
}

void blinkEye()
{
  if (isBlinking)
  {
    display.clearDisplay();
    display.drawLine(eyeX - eyeRadius, eyeY, eyeX + eyeRadius, eyeY, SSD1306_WHITE);
    display.display();
    delay(200);
    isBlinking = false;
  }
}

void movePupil()
{
  pupilX = eyeX + random(-eyeRadius / 2, eyeRadius / 2);
  pupilY = eyeY + random(-eyeRadius / 2, eyeRadius / 2);
  
}


void loop() 
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= blinkInterval)
  {
    previousMillis = currentMillis;
    isBlinking = true;
  }

  if (isBlinking)
  {
    blinkEye();
  }

  else
  {
    movePupil();
    Eye();
  }

  delay(100);
}
