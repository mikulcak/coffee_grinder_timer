#include <ButtonDebounce.h>

// D1 am Board ist GPIO5 im Code
#define SWITCH_INPUT_PIN 5

// #define SERIAL_PRINT

#define INITIAL_GRIND_TIME 16500

#define RELAY_PIN 0
#define LED_OUT_PIN 0

unsigned int grind_start_millis = 0;

unsigned int grind_time = INITIAL_GRIND_TIME;

unsigned int start_timer = 0;
unsigned int stop_timer = 0;
unsigned int timer_running = 0;

ButtonDebounce button(SWITCH_INPUT_PIN, 100);

void setup() {
  button.setCallback(handle_current_switch_state);

  pinMode(LED_OUT_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SWITCH_INPUT_PIN, INPUT);

#ifdef SERIAL_PRINT
  Serial.begin(9600);
  Serial.println("Give me coffee!");
#endif
}

void handle_current_switch_state(const int state) {
#ifdef SERIAL_PRINT
  Serial.println("Changed: " + String(state));
  Serial.println("timer_running: " + String(timer_running));
  Serial.println("start_timer: " + String(start_timer));
  Serial.println("stop_timer: " + String(stop_timer));
#endif

  if (state == 1) {
    // button is pressed
    if (timer_running == 0) {
      // timer is not running, start it
      start_timer = 1;
      stop_timer = 0;
    } else {
      // timer is not running, stop it
      stop_timer = 1;
      start_timer = 0;
    }
  }
}

void loop() {
  button.update();

  // perform actions according to state variables set above
  if (timer_running == 0 && start_timer == 0 && stop_timer == 0) {
    // do nothing, turn off relay
    digitalWrite(RELAY_PIN, LOW);
  } else if (timer_running == 0 && start_timer == 1 && stop_timer == 0) {
    // start the timer
    grind_start_millis = millis();
    timer_running = 1;
    // start the grinder
    digitalWrite(RELAY_PIN, HIGH);
    // reset start_timer variable
    start_timer = 0;

#ifdef SERIAL_PRINT
    Serial.println("turn on timer");
#endif
  } else if (timer_running == 1 && start_timer == 0 && stop_timer == 0) {
    // normal timer operation after grinder has been switched on
    if ((millis() - grind_start_millis) > grind_time) {
      // the timer ran through, turn off the relay, start from the top
      digitalWrite(RELAY_PIN, LOW);
      timer_running = 0;

#ifdef SERIAL_PRINT
      Serial.println("Timer finished");
      Serial.println(grind_start_millis);
      Serial.println(grind_time);
#endif
    } else {
      // not really needed here
      timer_running = 1;
    }
  } else if (timer_running == 1 && start_timer == 0 && stop_timer == 1) {
    // timer stop was called by the user
    grind_start_millis = 0;

    // reset commands and status
    timer_running = 0;
    stop_timer = 0;
    start_timer = 0;

    // turn off the grinder
    digitalWrite(RELAY_PIN, LOW);

#ifdef SERIAL_PRINT
    Serial.println("Timer stopped by user");
#endif
  } else {
#ifdef SERIAL_PRINT
    Serial.println("error");
#endif
  }
}
