#ifndef __LORA_MAIN_FILE_H__
#define __LORA_MAIN_FILE_H__

//#define CONTACT_DATA_MAX_PACKET 10
#include <main.h>

typedef struct {
	float lux;
	float temperature;
	float humidity;
	float pressure;
	float CO2;
	float TVOC;
	float water_temperature;
} SensorsDataTypeDef;

typedef struct {
	uint16_t lamp_d1; // lamp digital 1
	uint16_t lamp_d2; // lamp digital 2
} DevicesDataTypeDef;

#endif // __LORA_MAIN_FILE_H__
