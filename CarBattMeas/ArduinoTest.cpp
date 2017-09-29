#include <Arduino.h>
//#include <avr/sleep.h>
#include "LowPower.h"

// number of analog samples to take per reading
#define NUM_SAMPLES 10

int sum = 0;                    // sum of samples taken
unsigned char sample_count = 0; // current sample number
float voltage = 0.0;            // calculated voltage

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	// take a number of analog samples and add them up
	while (sample_count < NUM_SAMPLES)
	{
		sum += analogRead(A7);
		sample_count++;
		delay(10);
	}
	// calculate the voltage
	// use 5.0 for a 5.0V ADC reference voltage
	// 5.015V is the calibrated reference voltage
	voltage = ((float) sum / (float) NUM_SAMPLES * 5.015) / 1024.0;
	// send voltage for display on Serial Monitor
	Serial.print(voltage);
	Serial.println(" V");
	Serial.flush();
	sample_count = 0;
	sum = 0;

	// Enter power down state for 8 s with ADC and BOD module disabled
	LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}
