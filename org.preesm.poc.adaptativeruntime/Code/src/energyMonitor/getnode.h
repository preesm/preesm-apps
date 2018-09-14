#ifndef GETNODE_H
#define GETNODE_H

#include <sys/ioctl.h>
#include <iostream>
using namespace std;

#define GPUFREQ_NODE    "/sys/devices/11800000.mali/clock"
#define TEMP_NODE       "/sys/devices/10060000.tmu/temp"
#define TEMP_NODE_v4    "/sys/class/thermal/thermal_zone"

typedef struct ina231_iocreg__t {
    char name[20];
    unsigned int enable;
    unsigned int cur_uV;
    unsigned int cur_uA;
    unsigned int cur_uW;
} ina231_iocreg_t;

typedef struct sensor__t {
    int  fd;
    ina231_iocreg_t data;
} sensor_t;

#define INA231_IOCGREG      _IOR('i', 1, ina231_iocreg_t *)
#define INA231_IOCSSTATUS   _IOW('i', 2, ina231_iocreg_t *)
#define INA231_IOCGSTATUS   _IOR('i', 3, ina231_iocreg_t *)

// A15
#define DEV_SENSOR_ARM  "/dev/sensor_arm"
// Mem
#define DEV_SENSOR_MEM  "/dev/sensor_mem"
// A7
#define DEV_SENSOR_KFC  "/dev/sensor_kfc"
// GPU
#define DEV_SENSOR_G3D  "/dev/sensor_g3d"

enum    {
    SENSOR_ARM = 0,
    SENSOR_MEM,
    SENSOR_KFC,
    SENSOR_G3D,
    SENSOR_MAX
};

class GetNode
{
public:
    GetNode();
    string cpu_node_list[8];
    // A15
    float armuV,armuA, armuW;
    // GPU
    float g3duV, g3duA, g3duW;
    // A7
    float kfcuV, kfcuA, kfcuW;
    // Mem
    float memuV, memuA, memuW;
    int usage[8];
    string os_name1;
    string os_name;
    string os_ver;
    string kernel_ver;

    string GetGPUCurFreq(void);
    string GetCPUCurFreq(int cpuNum);
    string GetCPUTemp(int cpuNum);
    int GetCPUUsage(void);
    int calUsage(int cpu_idx, int user, int system, int idle);

    int open_sensor(const char *node, sensor_t *sensor);
    void close_sensor(sensor_t *sensor);
    void enable_sensor(sensor_t *sensor, unsigned char enable);
    int read_sensor_status(sensor_t *sensor);
    void read_sensor(sensor_t *sensor);

    int getUpdatePeriodMicroSec(void);

    int OpenINA231(void);
    void CloseINA231(void);
    void GetINA231(void);
    void GetSystemInfo(void);

private:
    sensor_t sensor[SENSOR_MAX];
    int mOldUserCPU[8];
    int mOldSystemCPU[8];
    int mOldIdleCPU[8];

};

#endif // GETNODE_H
