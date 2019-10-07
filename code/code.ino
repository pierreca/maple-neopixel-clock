// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include "RTClib.h"
#include <avr/interrupt.h>

#define MODE_DISPLAY 0
#define MODE_SET_HOURS 1
#define MODE_SET_MINUTES 2
#define MODE_SET_SECONDS 3

#define HOURS_PIN    2
#define HOURS_PIXELS 12

#define MINUTES_PIN  3
#define MINUTES_PIXELS 24

#define SECONDS_PIN 4
#define SECONDS_PIXELS 60

#define MAX_INTENSITY 255
#define CURRENT_SEC_ANIMATION_RAMP_TIME 600

#define INC_BTN_PIN 5
#define SET_BTN_PIN 6

RTC_DS3231 rtc;
Adafruit_NeoPixel hours_ring = Adafruit_NeoPixel(HOURS_PIXELS, HOURS_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel minutes_ring = Adafruit_NeoPixel(MINUTES_PIXELS, MINUTES_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel seconds_ring = Adafruit_NeoPixel(SECONDS_PIXELS, SECONDS_PIN, NEO_GRB + NEO_KHZ800);

uint8_t sec, prev_sec, current_mode;

DateTime now;

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

  // set button pins as inputs
  pinMode(SET_BTN_PIN, INPUT_PULLUP);
  pinMode(INC_BTN_PIN, INPUT_PULLUP);
 
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

void new_minute_animation() {
  for (uint8_t i = 0; i < 60; i++) {
    seconds_ring.setPixelColor(i, 0);
    seconds_ring.show();
    delay(10);
  }
}

void light_up_current_second(uint8_t current_sec) {
  unsigned long current_sec_animation_start = millis(); 
  while (millis() < current_sec_animation_start + CURRENT_SEC_ANIMATION_RAMP_TIME) {
    unsigned long elapsed = millis() - current_sec_animation_start;
    unsigned long intensity = elapsed * MAX_INTENSITY / CURRENT_SEC_ANIMATION_RAMP_TIME;
    seconds_ring.setPixelColor(sec, get_pixel_color(intensity));
    seconds_ring.show();
  }
}

void serial_print_time(uint8_t hours, uint8_t minutes, uint8_t seconds) {
  Serial.print(hours, DEC);
  Serial.print(':');
  Serial.print(minutes, DEC);
  Serial.print(':');
  Serial.print(seconds, DEC);
  Serial.println();
}

void display_time() {
  DateTime now = rtc.now();

  display_hours(now.hour());
  display_minutes(now.minute());
  sec = now.second();

  if (sec != prev_sec) {
    serial_print_time(now.hour(), now.minute(), now.second());
    if (sec == 0) {
      // turn off all seconds pixel in a quick animation around the ring
      new_minute_animation();
    } else {   
      // light up all second pixels until now
      display_seconds(sec - 1);
    }

    // animate current seconds pixel
    light_up_current_second(sec);
    prev_sec = sec;
  }
}

void display_H() {
  hours_ring.clear();
  hours_ring.setPixelColor(3, get_pixel_color(MAX_INTENSITY));
  hours_ring.setPixelColor(9, get_pixel_color(MAX_INTENSITY));
  hours_ring.show();

  minutes_ring.clear();
  for (int i = 3; i <= 9; i++) {
    minutes_ring.setPixelColor(i, get_pixel_color(MAX_INTENSITY));
    minutes_ring.setPixelColor(i + 12, get_pixel_color(MAX_INTENSITY));
  }
  minutes_ring.show();
}

void display_M() {
  hours_ring.clear();
  hours_ring.setPixelColor(1, get_pixel_color(MAX_INTENSITY));
  hours_ring.setPixelColor(11, get_pixel_color(MAX_INTENSITY));
  hours_ring.show();

  minutes_ring.clear();
  for (int i = 3; i <= 9; i++) {
    minutes_ring.setPixelColor(i, get_pixel_color(MAX_INTENSITY));
    minutes_ring.setPixelColor(i + 12, get_pixel_color(MAX_INTENSITY));
  }
  minutes_ring.show();
}

void display_S() {
  hours_ring.clear();
  hours_ring.setPixelColor(3, get_pixel_color(MAX_INTENSITY));
  hours_ring.setPixelColor(9, get_pixel_color(MAX_INTENSITY));
  hours_ring.show();

  minutes_ring.clear();
  for (int i = 0; i <= 3; i++) {
    minutes_ring.setPixelColor(i, get_pixel_color(MAX_INTENSITY));
    minutes_ring.setPixelColor(i + 12, get_pixel_color(MAX_INTENSITY));
  }
  for (int j = 6; j <= 11; j++) {
    minutes_ring.setPixelColor(j, get_pixel_color(MAX_INTENSITY));
    minutes_ring.setPixelColor(j + 12, get_pixel_color(MAX_INTENSITY));
  }
  minutes_ring.show();
}

uint8_t value_set;

bool increase_value_set_if_btn_pressed(uint8_t modulo) {
  bool changed = digitalRead(INC_BTN_PIN) == LOW;
  if (changed) {
    delay(200);
    value_set++;
    if (value_set > modulo - 1) {
      value_set = 0;
    }
  }
  for (int i = 0; i <= value_set; i++) {
    seconds_ring.setPixelColor(i, seconds_ring.Color(0,0,255));
  }

  return changed;
}

void set_time_hours() {
  Serial.println("set hours");
  display_H();
  seconds_ring.clear();
  for (int i = 24; i <= 59; i++) {
    seconds_ring.setPixelColor(i, seconds_ring.Color(255,0,0));
  }
  if(increase_value_set_if_btn_pressed(24)) {
    DateTime now = rtc.now();
    rtc.adjust(DateTime(now.year(), now.month(), now.day(), value_set, now.minute(), now.second()));
  }
  seconds_ring.show();
}

void set_time_minutes() {
  Serial.println("set minutes");
  display_M();
  seconds_ring.clear();
  if(increase_value_set_if_btn_pressed(60)) {
    DateTime now = rtc.now();
    rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour(), value_set, now.second()));
  }
  seconds_ring.show();
}

void set_time_seconds() {
  Serial.println("set seconds");
  display_S();
  seconds_ring.clear();
  if(increase_value_set_if_btn_pressed(60)) {
    DateTime now = rtc.now();
    rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour(), now.minute(), value_set));
  }
  seconds_ring.show();
}

void loop () {
  if (digitalRead(SET_BTN_PIN) == LOW) {
    current_mode++;
    DateTime now = rtc.now();
    switch (current_mode) {
      case MODE_SET_HOURS:
        value_set = now.hour();
        break;
      case MODE_SET_MINUTES:
        value_set = now.minute();
        break;
      case MODE_SET_SECONDS:
        value_set = now.second();
        break;
      default:
        value_set = 0;
        break;
    }
    delay(300);
  } else {
    switch(current_mode) {
      case MODE_DISPLAY:
        display_time();
        break;
      case MODE_SET_HOURS:
        set_time_hours();
        break;
      case MODE_SET_MINUTES:
        set_time_minutes();
        break;
      case MODE_SET_SECONDS:
        set_time_seconds();
        break;
      default:
        current_mode = MODE_DISPLAY;
        break;
    }
  }
}
