

#ifndef _GLOBALS_H
#define _GLOBALS_H

static const int OUTPUT_PORTS_TIMEOUT = 60;

#ifdef __AVR_ATmega328P__
	// TODO change to nano
	static const int INFO_LED_PIN = 6;
	static const int ERROR_LED_PIN = 7;

	static const int DIP_PIN1 = 5;
	static const int DIP_PIN2 = 4;
	static const int DIP_PIN3 = 3;
	static const int DIP_PIN4 = 2;
#endif
#ifdef __AVR_ATmega2560__
	static const int INFO_LED_PIN = 28;
	static const int ERROR_LED_PIN = 36;
	static const int DIP_PIN1 = 52;
	static const int DIP_PIN2 = 50;
	static const int DIP_PIN3 = 48;
	static const int DIP_PIN4 = 46;
#endif


#endif
