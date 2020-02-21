/*
 ============================================================================
 Name        : energyMonitor.cpp
 Author      : kdesnos
 Version     : 1.0
 Copyright   : CeCILL-C, IETR, INSA Rennes
 Description : Energy monitoring functionnalities for Odroid XU3
 ============================================================================
 */

#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include "energyMonitor.h"

static int armP_fd = -1;
static int armA_fd = -1;
static int armV_fd = -1;
static int gpuP_fd = -1;
static int gpuA_fd = -1;
static int gpuV_fd = -1;
static int ddrP_fd = -1;
static int ddrA_fd = -1;
static int ddrV_fd = -1;

int open_sensor(const char *node) {
    int fd = open(node, O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        fprintf(stderr, "ERROR: opening [%s] failed.\n", node);
    }
    return fd;
}

void close_sensor(int fd) {
    if (fd > 0) {
        close(fd);
    }
}

void read_sensor(int fd, float *value) {
    if (fd > 0) {
        char buf[256] = { '\0' };
        const auto n = read(fd, buf, sizeof(buf) - 1);
        if (n > 0) {
            (*value) = static_cast<float>(std::strtod(buf, nullptr));
        }
    }
}

void initEnergyMonitoring() {
    // Open ARM sensors
    armP_fd = open_sensor(DEV_SENSOR_ARM_P);
    armA_fd = open_sensor(DEV_SENSOR_ARM_A);
    armV_fd = open_sensor(DEV_SENSOR_ARM_V);
    // Open GPU sensors
    gpuP_fd = open_sensor(DEV_SENSOR_GPU_P);
    gpuA_fd = open_sensor(DEV_SENSOR_GPU_A);
    gpuV_fd = open_sensor(DEV_SENSOR_GPU_V);
    // Open DDR sensors
    ddrP_fd = open_sensor(DEV_SENSOR_DDR_P);
    ddrA_fd = open_sensor(DEV_SENSOR_DDR_A);
    ddrV_fd = open_sensor(DEV_SENSOR_DDR_V);
}

void getSensorsData(sensors *data) {
    // Read ARM values
    read_sensor(armP_fd, &(data->arm.w));
    read_sensor(armA_fd, &(data->arm.a));
    read_sensor(armV_fd, &(data->arm.v));
    // Read GPU values
    read_sensor(gpuP_fd, &(data->gpu.w));
    read_sensor(gpuA_fd, &(data->gpu.a));
    read_sensor(gpuV_fd, &(data->gpu.v));
    // Read DDR values
    read_sensor(ddrP_fd, &(data->mem.w));
    read_sensor(ddrA_fd, &(data->mem.a));
    read_sensor(ddrV_fd, &(data->mem.v));
}

void stopEnergyMonitoring() {
    // Close ARM sensors
    close_sensor(armP_fd);
    close_sensor(armA_fd);
    close_sensor(armV_fd);
    // Close GPU sensors
    close_sensor(gpuP_fd);
    close_sensor(gpuA_fd);
    close_sensor(gpuV_fd);
    // Close DDR sensors
    close_sensor(ddrP_fd);
    close_sensor(ddrA_fd);
    close_sensor(ddrV_fd);

}

