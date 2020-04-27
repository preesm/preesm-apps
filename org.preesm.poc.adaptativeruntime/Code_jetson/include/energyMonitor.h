/*
	============================================================================
	Name        : energyMonitor.h
	Author      : kdesnos
	Version     : 1.0
	Copyright   : CeCILL-C, IETR, INSA Rennes
	Description : Energy monitoring functionnalities for Odroid XU3
	============================================================================
*/

#ifndef ENERGY_MONITOR_H
#define ENERGY_MONITOR_H

typedef struct {
    float v;
    float a;
    float w;
} sensor_data;

typedef struct {
    sensor_data arm;
    sensor_data gpu;
    sensor_data mem;
} sensors;

// A57 + Denver2
#define DEV_SENSOR_ARM_P  "/sys/bus/i2c/drivers/ina3221x/0-0041/iio_device/in_power1_input"
#define DEV_SENSOR_ARM_A  "/sys/bus/i2c/drivers/ina3221x/0-0041/iio_device/in_current1_input"
#define DEV_SENSOR_ARM_V  "/sys/bus/i2c/drivers/ina3221x/0-0041/iio_device/in_voltage1_input"
// Mem
#define DEV_SENSOR_DDR_P  "/sys/bus/i2c/drivers/ina3221x/0-0040/iio_device/in_power2_input"
#define DEV_SENSOR_DDR_A  "/sys/bus/i2c/drivers/ina3221x/0-0040/iio_device/in_current2_input"
#define DEV_SENSOR_DDR_V  "/sys/bus/i2c/drivers/ina3221x/0-0040/iio_device/in_voltage2_input"
// GPU
#define DEV_SENSOR_GPU_P  "/sys/bus/i2c/drivers/ina3221x/0-0040/iio_device/in_power0_input"
#define DEV_SENSOR_GPU_A  "/sys/bus/i2c/drivers/ina3221x/0-0040/iio_device/in_current0_input"
#define DEV_SENSOR_GPU_V  "/sys/bus/i2c/drivers/ina3221x/0-0040/iio_device/in_voltage0_input"

void initEnergyMonitoring();

void getSensorsData(sensors *data);

void stopEnergyMonitoring();

#endif

