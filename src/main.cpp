#include <Arduino.h>

#define OUTENABLED_PIN 7
#define SHIFT_PIN 8
#define STORE_PIN 9
#define DATA_PIN 10
#define ONBOARD_LED_PIN 13
// #define DEBUG true

int counter = 0;

int numberMap[] = {
  170, 138,  26, 202,  42,  74, 154,  10,  58, 186,
  160, 128,  16, 192,  32,  64, 144,   0,  48, 176,
  161, 129,  17, 193,  33,  65, 145,   1,  49, 177,
  166, 134,  22, 198,  38,  70, 150,   6,  54, 182,
  164, 132,  20, 196,  36,  68, 148,   4,  52, 180,
  162, 130,  18, 194,  34,  66, 146,   2,  50, 178,
  163, 131,  19, 195,  35,  67, 147,   3,  51, 179,
  168, 136,  24, 200,  40,  72, 152,   8,  56, 184,
  169, 137,  25, 201,  41,  73, 153,   9,  57, 185,
  171, 139,  27, 203,  43,  75, 155,  11,  59, 187,
};

void updateShiftRegister(uint8_t value)
{
  digitalWrite(STORE_PIN, LOW);
  shiftOut(DATA_PIN, SHIFT_PIN, MSBFIRST, value);
  digitalWrite(STORE_PIN, HIGH);
}

void updateShiftChainedRegisters(uint8_t value, uint8_t value2)
{
  digitalWrite(STORE_PIN, LOW);
  shiftOut(DATA_PIN, SHIFT_PIN, MSBFIRST, value);
  shiftOut(DATA_PIN, SHIFT_PIN, MSBFIRST, value2);
  digitalWrite(STORE_PIN, HIGH);
}

void updateShiftChainedRegisters(uint8_t value1, uint8_t value2, uint8_t value3, uint8_t value4)
{
  digitalWrite(STORE_PIN, LOW);
  shiftOut(DATA_PIN, SHIFT_PIN, MSBFIRST, value1);
  shiftOut(DATA_PIN, SHIFT_PIN, MSBFIRST, value2);
  shiftOut(DATA_PIN, SHIFT_PIN, MSBFIRST, value3);
  shiftOut(DATA_PIN, SHIFT_PIN, MSBFIRST, value4);
  digitalWrite(STORE_PIN, HIGH);
}

void shuffleAll()
{
  for (uint8_t i = 0; i < 255; i++)
  {
    updateShiftRegister(i);
    delay(1);
  }
  updateShiftRegister(255);
}

void setup()
{
  pinMode(OUTENABLED_PIN, OUTPUT);
  digitalWrite(OUTENABLED_PIN, LOW);

  pinMode(STORE_PIN, OUTPUT);
  pinMode(SHIFT_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(ONBOARD_LED_PIN, OUTPUT);

  counter = 0;

#ifdef DEBUG
  Serial.begin(9600);
#endif
  shuffleAll();
}

void loop()
{
#ifdef DEBUG
  Serial.print(counter);
  Serial.print(" ");
  Serial.print(numberMap[counter], BIN);
  Serial.println();
#endif

  // updateShiftChainedRegisters(255, numberMap[counter]);
  // updateShiftChainedRegisters(numberMap[counter], numberMap[counter], numberMap[counter], numberMap[counter]);
  updateShiftChainedRegisters(255, 255, 255, numberMap[counter]);

  delay(50);

  counter++;

#ifdef DEBUG
  if (counter >= 100)
  {
    Serial.println("---------");
    delay(200);
    shuffleAll();
  }
#endif

  counter = counter % 100;
}
