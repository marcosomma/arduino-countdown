// OUTPUT
// Segments
int s1 = 12;
int s2 = 8;
int s3 = 4;
int s4 = 6;
int s5 = 7;
int s6 = 11;
int s7 = 3;
int point = 5;
// Digits
int d4 = 2;
int d3 = 9;
int d2 = 10;
int d1 = 13;
//Sound
int outputSound = 17;
int ledOn = 18;
int ledCountDown = 19;

// INPUT
int buttonStart = 14;
int buttonStartState = 0;
int buttonReset = 15;
int buttonResetState = 0;
int buttonSwitch = 16;
int buttonSwitchState = 0;
int buttonSwitchPreavious = LOW;

int del = 1845;
int switchSelector = 0;
int fixedMinutes[] = {
    0, 0, 1, 2, 3, 4, 5, 10, 15, 20, 30, 45, 60};
int minutes = fixedMinutes[switchSelector];
int seconds = 0;

long M = minutes * 1000L;
long S = 0;
long n = 0;

void setup()
{
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);
  pinMode(s5, OUTPUT);
  pinMode(s6, OUTPUT);
  pinMode(s7, OUTPUT);
  pinMode(point, OUTPUT);
  pinMode(outputSound, OUTPUT);
  pinMode(ledOn, OUTPUT);
  pinMode(ledCountDown, OUTPUT);
  pinMode(buttonStart, INPUT);
  pinMode(buttonReset, INPUT);
  pinMode(buttonSwitch, INPUT);

  if (fixedMinutes[switchSelector] == 0)
  {
    switch (switchSelector)
    {
    default:
      seconds = 30;
      break;
    case 1:
      seconds = 45;
      break;
    };
  }
  bipSound();
}

void loop()
{
  digitalWrite(ledOn, HIGH);
  do
  {
    reset();
    digitalWrite(ledCountDown, LOW);
    buttonStartState = digitalRead(buttonStart);
    buttonSwitchState = digitalRead(buttonSwitch);

    if (buttonStartState == HIGH)
    {
      bipSound();
      setIterator();
      break;
    }

    if (buttonSwitchState == HIGH && buttonSwitchPreavious == LOW)
    {
      bipSound();
      switchTime();
      reset();
      buttonSwitchPreavious = HIGH;
    }
    else if (buttonSwitchState == LOW && buttonSwitchPreavious == HIGH)
    {
      buttonSwitchPreavious = LOW;
    }

    showSelect();

  } while (n == 0);
  do
  {
    digitalWrite(ledCountDown, HIGH);
    buttonResetState = digitalRead(buttonReset);

    if (buttonResetState == HIGH)
    {
      bipSound();
      reset();
      break;
    }

    if (S == 0)
    {
      S = 6 * 1000;
      M = M - 1000;
    }

    showCountDown();

    n--;
    S--;

    if (n == 100 || n == 200 || n == 300 || n == 400 || n == 500)
    {
      endSound(50);
    }
    if (n == 0)
    {
      endSound(500);
    }
    delayMicroseconds(del);

  } while (n != 0);
}

void switchTime()
{
  if (switchSelector >= (sizeof(fixedMinutes) / 2) - 1)
  {
    switchSelector = 0;
  }
  else
  {
    switchSelector++;
  }
  if (fixedMinutes[switchSelector] == 0)
  {
    switch (switchSelector)
    {
    default:
      seconds = 30;
      break;
    case 1:
      seconds = 45;
      break;
    }
  }
  else
  {
    seconds = 0;
  }
}

void reset()
{
  minutes = fixedMinutes[switchSelector];
  M = minutes * 1000L;
  S = seconds * 100L;
  n = 0;
}

void setIterator()
{
  n = M * 6 + S;
}

void showCountDown()
{
  clearLEDs();
  pickDigit(1);
  pickNumber((M / 10000) % 10);
  delayMicroseconds(del);

  clearLEDs();
  pickDigit(2);
  pickNumber((M / 1000) % 10);
  delayMicroseconds(del);

  clearLEDs();
  pickDigit(3);
  dispDec(3);
  pickNumber((S / 1000) % 10);
  delayMicroseconds(del);

  clearLEDs();
  pickDigit(4);
  pickNumber((S / 100) % 10);
  delayMicroseconds(del);
}

void showSelect()
{
  clearLEDs();
  pickDigit(1);
  pickNumber((minutes / 10) % 10);
  delayMicroseconds(del);

  clearLEDs();
  pickDigit(2);
  pickNumber((minutes) % 10);
  delayMicroseconds(del);

  clearLEDs();
  pickDigit(3);
  dispDec(3);
  pickNumber((seconds / 10) % 10);
  delayMicroseconds(del);

  clearLEDs();
  pickDigit(4);
  pickNumber((seconds) % 10);
  delayMicroseconds(del);
}

void pickDigit(int x)
{
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);

  switch (x)
  {
  case 1:
    digitalWrite(d1, LOW);
    break;
  case 2:
    digitalWrite(d2, LOW);
    digitalWrite(point, HIGH); //new
    break;
  case 3:
    digitalWrite(d3, LOW);
    break;
  default:
    digitalWrite(d4, LOW);
    break;
  }
}

void pickNumber(int x)
{
  switch (x)
  {
  default:
    zero();
    break;
  case 1:
    one();
    break;
  case 2:
    two();
    break;
  case 3:
    three();
    break;
  case 4:
    four();
    break;
  case 5:
    five();
    break;
  case 6:
    six();
    break;
  case 7:
    seven();
    break;
  case 8:
    eight();
    break;
  case 9:
    nine();
    break;
  }
}

void dispDec(int x)
{
  digitalWrite(point, LOW);
}

void clearLEDs()
{
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  digitalWrite(s4, LOW);
  digitalWrite(s5, LOW);
  digitalWrite(s6, LOW);
  digitalWrite(s7, LOW);
  digitalWrite(point, LOW);
}

void zero()
{
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  digitalWrite(s4, HIGH);
  digitalWrite(s5, HIGH);
  digitalWrite(s6, HIGH);
  digitalWrite(s7, LOW);
}

void one()
{
  digitalWrite(s1, LOW);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  digitalWrite(s4, LOW);
  digitalWrite(s5, LOW);
  digitalWrite(s6, LOW);
  digitalWrite(s7, LOW);
}

void two()
{
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, LOW);
  digitalWrite(s4, HIGH);
  digitalWrite(s5, HIGH);
  digitalWrite(s6, LOW);
  digitalWrite(s7, HIGH);
}

void three()
{
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  digitalWrite(s4, HIGH);
  digitalWrite(s5, LOW);
  digitalWrite(s6, LOW);
  digitalWrite(s7, HIGH);
}

void four()
{
  digitalWrite(s1, LOW);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  digitalWrite(s4, LOW);
  digitalWrite(s5, LOW);
  digitalWrite(s6, HIGH);
  digitalWrite(s7, HIGH);
}

void five()
{
  digitalWrite(s1, HIGH);
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  digitalWrite(s4, HIGH);
  digitalWrite(s5, LOW);
  digitalWrite(s6, HIGH);
  digitalWrite(s7, HIGH);
}

void six()
{
  digitalWrite(s1, HIGH);
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  digitalWrite(s4, HIGH);
  digitalWrite(s5, HIGH);
  digitalWrite(s6, HIGH);
  digitalWrite(s7, HIGH);
}

void seven()
{
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  digitalWrite(s4, LOW);
  digitalWrite(s5, LOW);
  digitalWrite(s6, LOW);
  digitalWrite(s7, LOW);
}

void eight()
{
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  digitalWrite(s4, HIGH);
  digitalWrite(s5, HIGH);
  digitalWrite(s6, HIGH);
  digitalWrite(s7, HIGH);
}

void nine()
{
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  digitalWrite(s4, HIGH);
  digitalWrite(s5, LOW);
  digitalWrite(s6, HIGH);
  digitalWrite(s7, HIGH);
}

void endSound(int duration)
{
  int tone = 2915;
  for (long i = 0; i < duration * 1000L; i += tone * 2)
  {
    digitalWrite(outputSound, HIGH);
    delayMicroseconds(tone);
    digitalWrite(outputSound, LOW);
    delayMicroseconds(tone);
  }
}

void bipSound()
{
  int tone = 275;
  for (long i = 0; i < 2 * 1000L; i += tone * 2)
  {
    digitalWrite(outputSound, HIGH);
    delayMicroseconds(tone);
    digitalWrite(outputSound, LOW);
    delayMicroseconds(tone);
  }
}