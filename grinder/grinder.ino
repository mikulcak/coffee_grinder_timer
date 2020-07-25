#define WAIT_TIME 3000
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

// unsigned int current_switch_state = 0;

// void onButtonChange(const int state) {
//   Serial.println("Changed: " + String(state));
// }

ButtonDebounce button(SWITCH_INPUT_PIN, 100);

// the setup function runs once when you press reset or power the board
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
  // current_switch_state = digitalRead(SWITCH_INPUT_PIN);
#ifdef SERIAL_PRINT
  Serial.println("Changed: " + String(state));
  Serial.println("timer_running: " + String(timer_running));
  Serial.println("start_timer: " + String(start_timer));
  Serial.println("stop_timer: " + String(stop_timer));
#endif
  // Serial.println("Button pressed");

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
  // buttonUp.update();
  // buttonDown.update();

  // handle_current_switch_state();

  // perform actions according to state variables set above
  if (timer_running == 0 && start_timer == 0 && stop_timer == 0) {
    // do nothing, turn off relay
    digitalWrite(RELAY_PIN, LOW);
    // redraw_display(grind_time, TIMER_COLOR);
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

      // redraw display with current grind time
      // redraw_display(grind_time, TIMER_COLOR);
      // set button back to Start
      // myFiles.loadBitmap(START_BUTTON_ANCHOR_X, START_BUTTON_ANCHOR_Y,
      // START_BUTTON_WIDTH, START_BUTTON_HEIGHT,
      // "startlt.raw");

#ifdef SERIAL_PRINT
      Serial.println("Timer finished");
      Serial.println(grind_start_millis);
      Serial.println(grind_time);
#endif
    } else {
      timer_running = 1;
      // redraw display with current timer value, counting down from the grind
      // time
      // redraw_display(grind_time - (millis() - grind_start_millis),
      // TIMER_COLOR);
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

    // redraw display with current grind time
    // redraw_display(grind_time, TIMER_COLOR);
    // change button back to Start
    // myFiles.loadBitmap(START_BUTTON_ANCHOR_X, START_BUTTON_ANCHOR_Y,
    // START_BUTTON_WIDTH, START_BUTTON_HEIGHT, "startlt.raw");
#ifdef SERIAL_PRINT
    Serial.println("Timer stopped by user");
#endif
  } else {
#ifdef SERIAL_PRINT
    Serial.println("error");
#endif
  }
}
