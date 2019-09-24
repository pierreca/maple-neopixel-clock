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

#define MAX_INTENSITY 255
#define RAMP_TIME 600

RTC_DS3231 rtc;
Adafruit_NeoPixel hours_ring = Adafruit_NeoPixel(HOURS_PIXELS, HOURS_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel minutes_ring = Adafruit_NeoPixel(MINUTES_PIXELS, MINUTES_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel seconds_ring = Adafruit_NeoPixel(SECONDS_PIXELS, SECONDS_PIN, NEO_GRB + NEO_KHZ800);

uint8_t sec, prev_sec;

uint32_t get_pixel_color(uint8_t intensity) {
  return hours_ring.Color(intensity / 6, intensity / 2, intensity);
}

void setup () {
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
  sec = 0;
  prev_sec = 0;
}

void color_pixels(Adafruit_NeoPixel& ring, uint8_t pixel) {
    ring.clear();
    for (uint8_t i = 0; i <= pixel; i++) {
        ring.setPixelColor(i, get_pixel_color(MAX_INTENSITY));
    }
    ring.show();
}

void display_hours(uint8_t hour_now) {
    uint8_t pix = hour_now % 12;
    color_pixels(hours_ring, pix);
}

void display_minutes(uint8_t minute_now) {
    uint8_t pix = (minute_now * MINUTES_PIXELS / 60) % 60;
    color_pixels(minutes_ring, pix);
}

void display_seconds(uint8_t second_now) {
    uint8_t pix = second_now % 60;
    color_pixels(seconds_ring, pix);
}

void loop () {
    DateTime now = rtc.now();

    display_hours(now.hour());
    display_minutes(now.minute());
    sec = now.second();

    if (sec != prev_sec) {
      Serial.println("new second!");
      if (sec > 0) {   
        display_seconds(sec - 1);
      } else {
        for (uint8_t i = 0; i < 60; i++) {
          seconds_ring.setPixelColor(i, 0);
          seconds_ring.show();
          delay(10);
        }
      }
      
      unsigned long time_now = millis(); 
      while (millis() < time_now + RAMP_TIME) {
        unsigned long elapsed = millis() - time_now;
        unsigned long intensity = elapsed * MAX_INTENSITY / RAMP_TIME;
        seconds_ring.setPixelColor(sec, get_pixel_color(intensity));
        seconds_ring.show();
      }
      prev_sec = sec;
    }
}
