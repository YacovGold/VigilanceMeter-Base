

#define BTN_RED 12
#define BTN_GREEN 4

#define LED_RED 11
#define LED_GREEN 6

unsigned long startTestTime;
unsigned short clickCount;

bool isRedBtnDown = false;

bool isTesting = false;

void changeLedsState(uint8_t val)
{
  digitalWrite(LED_RED, val);
  digitalWrite(LED_GREEN, val);
}

void blink()
{
  changeLedsState(HIGH);
  delay(500);
  changeLedsState(LOW);
}

void waitForTestIndication()
{
  auto isRedClick = false;
  auto isGreenClick = false;
  do
  {
    delay(50);
    isRedClick = digitalRead(BTN_RED) == LOW;
    isGreenClick = digitalRead(BTN_GREEN) == LOW;
  } while (isRedClick == false || isGreenClick == false);

  blink();
}

void processBtnClick()
{
  auto isDown = digitalRead(BTN_RED) == LOW;

  if (isDown)
  {
    if (isRedBtnDown == false)
    {
      clickCount++;
      isRedBtnDown = true;
    }
  }
  else
  {
    isRedBtnDown = false;
  }
}

void showResults()
{
  auto avg = clickCount / 5;
  if (avg <= 1)
  {
    digitalWrite(LED_RED, HIGH);
  }
  else if (avg <= 3)
  {
    analogWrite(LED_RED, 255 / 4);
    analogWrite(LED_GREEN, 255 / 4);
  }
  else
  {
    digitalWrite(LED_GREEN, HIGH);
  }
}

void setup()
{
  pinMode(BTN_RED, INPUT_PULLUP);
  pinMode(BTN_GREEN, INPUT_PULLUP);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  blink();
}

void loop()
{
  if (isTesting)
  {
    processBtnClick();

    if (millis() - startTestTime >= 5000)
    {
      showResults();
      isTesting = false;
    }
  }
  else
  {
    waitForTestIndication();
    changeLedsState(LOW);
    startTestTime = millis();
    clickCount = 0;
    isTesting = true;
  }
}
