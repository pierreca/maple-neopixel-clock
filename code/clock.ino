// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include "RTClib.h"

#define HOURS_PIN    2
#define HOURS_PIXELS 12

#define MINUTES_PIN  3
#define MINUTES_PIXELS 24

#define SECONDS_PIN 4
#define SECONDS_PIXELS 60

RTC_DS3231 rtc;
Adafruit_NeoPixel hours_ring = Adafruit_NeoPixel(HOURS_PIXELS, HOURS_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel minutes_ring = Adafruit_NeoPixel(MINUTES_PIXELS, MINUTES_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel seconds_ring = Adafruit_NeoPixel(SECONDS_PIXELS, SECONDS_PIN, NEO_GRB + NEO_KHZ800);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {

#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif

  Serial.begin(9600);

  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  hours_ring.begin();
  minutes_ring.begin();
  seconds_ring.begin();
}

void color_pixels (Adafruit_NeoPixel& ring, uint8_t pixel_before, uint8_t pixel, uint8_t pixel_after) {
    ring.clear();
    ring.setPixelColor(pixel, ring.Color(0,100,0));
    ring.setPixelColor(pixel_before, ring.Color(0,20,0));
    ring.setPixelColor(pixel_after, ring.Color(0,20,0));
    ring.show();
}

void display_hours(uint8_t hour_now) {
    Serial.print("hour:");
    Serial.print(hour_now, DEC);
    Serial.println();
    
    uint8_t pix_before = (hour_now - 1) % 12;
    uint8_t pix = hour_now % 12;
    uint8_t pix_after = (hour_now + 1) % 12;

    Serial.print("hour pixel: ");
    Serial.print(pix, DEC);
    Serial.println();
    
    color_pixels(hours_ring, pix_before, pix, pix_after);
}

void display_minutes(uint8_t minute_now) {
    Serial.print("minute:");
    Serial.print(minute_now, DEC);
    Serial.println();
    
    uint8_t pix = (minute_now * MINUTES_PIXELS / 60) % 60;
    uint8_t pix_before = (pix - 1) % 60;
    uint8_t pix_after = (pix + 1) % 60;

    Serial.print("minute pixel: ");
    Serial.print(pix, DEC);
    Serial.print("before minute pixel: ");
    Serial.print(pix_before, DEC);
    Serial.print("after minute pixel: ");
    Serial.print(pix_after, DEC);
    Serial.println();
    
    color_pixels(minutes_ring, pix_before, pix, pix_after);
}

void display_seconds(uint8_t second_now) {
    Serial.print("second:");
    Serial.print(second_now, DEC);
    Serial.println();
    
    uint8_t pix_before = (second_now - 1) % 60;
    uint8_t pix = second_now % 60;
    uint8_t pix_after = (second_now + 1) % 60;

    Serial.print("second pixel: ");
    Serial.print(pix, DEC);
    Serial.println();
    
    color_pixels(seconds_ring, pix_before, pix, pix_after);
}

void loop () {
    Serial.print("loop start");
    Serial.println();
    DateTime now = rtc.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    Serial.print("before setting pixels");
    Serial.println();
    display_hours(now.hour());
    display_minutes(now.minute());
    display_seconds(now.second());
    Serial.print("after setting pixels");
    Serial.println();
    delay(1000);
    Serial.print("loop end");
    Serial.println();
}
