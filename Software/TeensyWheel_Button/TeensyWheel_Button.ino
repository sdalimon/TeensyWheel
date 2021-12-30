
/* Software for TeensyWheel - A replacement PCB for the Flashfire ForceWheel WH2304-V racing wheel
    using a Teensy 4.1
   You must select Joystick from the "Tools > USB Type" menu

   Shawn D'Alimonte 2021-12-30
*/

#include <Bounce2.h>
#include "IO_Pins.h"
#include <stdio.h>

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.

// Normal buttons
Bounce buttons[NUM_BTNS] = {Bounce()};

// Paddles
Bounce paddleLeft = Bounce(PAD_L, 10);
Bounce paddleRight = Bounce(PAD_R, 10);

// D-Pad
Bounce dUp = Bounce(DP_UP, 10);
Bounce dDown = Bounce(DP_DOWN, 10);
Bounce dLeft = Bounce(DP_LEFT, 10);
Bounce dRight = Bounce(DP_RIGHT, 10);

void setup() {
  int i;

  //Serial.begin(115200);
  //while (!Serial); // Wait for USB Serial
  //Serial.println("TeensyWheel");

  // Configure Input Pins
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);
  pinMode(BTN_4, INPUT_PULLUP);
  pinMode(BTN_5, INPUT_PULLUP);
  pinMode(BTN_6, INPUT_PULLUP);
  pinMode(BTN_7, INPUT_PULLUP);
  pinMode(BTN_8, INPUT_PULLUP);
  pinMode(BTN_9, INPUT_PULLUP);
  pinMode(BTN_10, INPUT_PULLUP);
  pinMode(BTN_11, INPUT_PULLUP);
  pinMode(BTN_12, INPUT_PULLUP);
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(SENSE_HIGH, INPUT_PULLUP);
  pinMode(SENSE_MED, INPUT_PULLUP);
  pinMode(SENSE_LOW, INPUT_PULLUP);
  pinMode(SENSE_LOW, INPUT_PULLUP);
  pinMode(PAD_L, INPUT_PULLUP);
  pinMode(PAD_R, INPUT_PULLUP);
  pinMode(DP_UP, INPUT_PULLUP);
  pinMode(DP_DOWN, INPUT_PULLUP);
  pinMode(DP_LEFT, INPUT_PULLUP);
  pinMode(DP_RIGHT, INPUT_PULLUP);
  pinMode(GEAR_UP, INPUT_PULLUP);
  pinMode(GEAR_DOWN, INPUT_PULLUP);
  pinMode(GEAR_REV, INPUT_PULLUP);

  // Configure Output pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(VIB_1, OUTPUT);
  pinMode(VIB_2, OUTPUT);

  // LEDs off
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);

  // Vibrator Off
  digitalWrite(VIB_1, LOW);
  digitalWrite(VIB_2, LOW);

  // Inititialize Bounce objects for buttons
  for (i = 0; i < NUM_BTNS; i++) {
    buttons[i].attach(BTN_MAP[i]);
    buttons[i].interval(10);
  }

  // Set all buttons and axes to default
  for (i = 0; i < NUM_BTNS; i++) {
    Joystick.button(i, 0);
  }
  Joystick.hat(-1);
  Joystick.X(512);
  Joystick.Y(1023);
  Joystick.Z(0);
  Joystick.Zrotate(512);
}

void loop() {
  int i;
  static int dx = 0;  // DPad X position
  static int dy = 0;  // DPad Y position
  static bool d_chg = 1; // Has Dpad changed?

  static int last_wheel = -1;
  static int last_acce1 = -1;
  static int last_brake = -1;
  static int last_paddle = -1;

  // Update all Bounce statuses
  for (i = 0; i < NUM_BTNS; i++) {
    buttons[i].update();
  }
  paddleLeft.update();
  paddleRight.update();
  dUp.update();
  dDown.update();
  dLeft.update();
  dRight.update();

  // Send Button Changes
  for (i = 0; i < NUM_BTNS; i++) {
    if (buttons[i].fell()) Joystick.button(i + 1, 1);
    if (buttons[i].rose()) Joystick.button(i + 1, 0);
  }

  // Handle D-Pad as POV Hat
  if (dUp.fell()) {
    dy = 1;
    d_chg = 1;
  }
  if (dUp.rose()) {
    dy = 0;
    d_chg = 1;
  }
  if (dDown.fell()) {
    dy = -1;
    d_chg = 1;
  }
  if (dDown.rose()) {
    dy = 0;
    d_chg = 1;
  }
  if (dRight.fell()) {
    dx = 1;
    d_chg = 1;
  }
  if (dRight.rose()) {
    dx = 0;
    d_chg = 1;
  }
  if (dLeft.fell()) {
    dx = -1;
    d_chg = 1;
  }
  if (dLeft.rose()) {
    dx = 0;
    d_chg = 1;
  }
  if (d_chg == 1) {
    if (dy == 1 && dx == 0)       Joystick.hat(0);
    else if (dy == 1  && dx == 1) Joystick.hat(45);
    else if (dy == 0  && dx == 1) Joystick.hat(90);
    else if (dy == -1 && dx == 1) Joystick.hat(135);
    else if (dy == -1  && dx == 0) Joystick.hat(180);
    else if (dy == -1  && dx == -1) Joystick.hat(225);
    else if (dy == 0  && dx == -1) Joystick.hat(270);
    else if (dy == 1  && dx == -1) Joystick.hat(315);
    else Joystick.hat(-1);
    d_chg = 0;
  }

  // Wheel is X axis
  {
    int wheel = 1023 - analogRead(WHEEL);
    if (wheel != last_wheel) {
      Joystick.X(wheel);
      last_wheel = wheel;
    }
  }

  // Accel is Y axis
  {
    int accel = 1023 - analogRead(ACCEL);
    if (accel != last_acce1) {
      Joystick.Y(accel);
      last_acce1 = accel;
    }
  }

  // Brake is Z axis
  {
    int brake = analogRead(BRAKE);
    if (brake != last_brake) {
      Joystick.Z(brake);
      last_brake = brake;
    }
  }

  // Paddles are Z Rotation axis
  {
    static int paddle = 512;
    if (paddleLeft.fell()) {
      paddle = 0;
    }
    if (paddleLeft.rose()) {
      paddle = 512;
    }
    if (paddleRight.fell()) {
      paddle = 1023;
    }
    if (paddleRight.rose()) {
      paddle = 512;
    }
    if (paddle != last_paddle) {
      Joystick.Zrotate(paddle);
      last_paddle = paddle;
    }
  }

}
