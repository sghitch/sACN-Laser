/***************************************************
This is an example for our Adafruit 16-channel PWM & Servo driver
PWM test - this will drive 16 PWMs in a 'wave'

Pick one up today in the adafruit shop!
------> http://www.adafruit.com/products/815

These drivers use I2C to communicate, 2 pins are required to
interface.

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
BSD license, all text above must be included in any redistribution
****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SPI.h>
#include <Ethernet.h>
#include <E131.h>

#define BOARD0_ADDR 0x40
#define BOARD1_ADDR 0x41
#define BOARD2_ADDR 0x42
#define BOARD3_ADDR 0x43
#define BOARD4_ADDR 0x44

#define UNIVERSE 1

int levels[50];

byte mac[] = { 0xDE, 0xAD, 0xBE, 0x2F, 0x1E, 0xE3 };
E131 e131;

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm0 = Adafruit_PWMServoDriver(BOARD0_ADDR);
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(BOARD1_ADDR);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(BOARD2_ADDR);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(BOARD3_ADDR);
Adafruit_PWMServoDriver pwm4 = Adafruit_PWMServoDriver(BOARD4_ADDR);
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

void setup()
{
	pwm0.begin();
	pwm1.begin();
	pwm2.begin();
	pwm3.begin();
	pwm4.begin();

	pwm0.setPWMFreq(1600);  // This is the maximum PWM frequency, 490 for arduino
	pwm1.setPWMFreq(1600);  // This is the maximum PWM frequency, 490 for arduino
	pwm2.setPWMFreq(1600);  // This is the maximum PWM frequency, 490 for arduino
	pwm3.setPWMFreq(1600);  // This is the maximum PWM frequency, 490 for arduino
	pwm4.setPWMFreq(1600);  // This is the maximum PWM frequency, 490 for arduino

						  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
						  // some i2c devices dont like this so much so if you're sharing the bus, watch
						  // out for this!
	Wire.setClock(400000);

	Serial.begin(115200);
	delay(10);

	/* Configure via DHCP and listen Unicast on the default port */
	e131.begin(mac);
}

void setLevels()
{
	for (int i = 0; i < 10; i++)
	{
		pmw0.setPWM(i, 0, levels[i] * (4096 / 512));
		pmw1.setPWM(i, 0, levels[i + 10] * (4096 / 512));
		pmw2.setPWM(i, 0, levels[i + 20] * (4096 / 512));
		pmw3.setPWM(i, 0, levels[i + 30] * (4096 / 512));
		pmw4.setPWM(i, 0, levels[i + 40] * (4096 / 512));
	}
}

void loop()
{
	if (e131.parsePacket()) {

		if (e131.universe == UNIVERSE && e131.packet->priority != 0) {

			byte newLevel = e131.data[ADDRESS - 1];
			if (newLevel != level)
			{
				analogWrite(PIN, newLevel);
				level = newLevel;
			}
			digitalWrite(LED, 0);
		}

	}

	setLevels();
}
