#include "getnode.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>


#include <algorithm>    // std::remove
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

GetNode::GetNode()
{
    for (int i = 0; i < 8; i++) {
      usage[i] = 0;
      std::ostringstream oss;
      oss << "/sys/devices/system/cpu/cpu" << i << "/cpufreq/cpuinfo_cur_freq";
      std::string buf = oss.str();
      cpu_node_list[i] = buf;
    }
}

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

int GetNode::getUpdatePeriodMicroSec() {
  // default value from driver is 263808
  // change in /media/boot/exynos5422-odroidxu3.dtb (recompile with kernel)
  return 10000;
}

void GetNode::GetSystemInfo()
{
    kernel_ver = exec("bash -c \"uname -r\"");
    kernel_ver.erase(std::remove(kernel_ver.begin(), kernel_ver.end(), ' '), kernel_ver.end());
    kernel_ver.erase(std::remove(kernel_ver.begin(), kernel_ver.end(), '\t'), kernel_ver.end());
    kernel_ver.erase(std::remove(kernel_ver.begin(), kernel_ver.end(), '\n'), kernel_ver.end());

    os_ver = exec("lsb_release -r");
    os_ver.erase(os_ver.find("Release"),8);
    os_ver.erase(std::remove(os_ver.begin(), os_ver.end(), ' '), os_ver.end());
    os_ver.erase(std::remove(os_ver.begin(), os_ver.end(), '\t'), os_ver.end());
    os_ver.erase(std::remove(os_ver.begin(), os_ver.end(), '\n'), os_ver.end());

    os_name = exec("lsb_release -i");
    os_name.erase(os_name.find("Distributor"),15);
    os_name.erase(std::remove(os_name.begin(), os_name.end(), ' '), os_name.end());
    os_name.erase(std::remove(os_name.begin(), os_name.end(), '\t'), os_name.end());
    os_name.erase(std::remove(os_name.begin(), os_name.end(), '\n'), os_name.end());
}

string GetNode::GetGPUCurFreq()
{
    float fVal = 0.;
    if (kernel_ver[0] == '4') {
      fVal = 600;
    } else {
      std::fstream myfile(GPUFREQ_NODE, std::ios_base::in);
      float a;
      while (myfile >> a) {
          fVal = a;
      }
    }
    string freq;
    ostringstream oss;
    oss << fVal;
    freq = oss.str();
    return freq;
}

string GetNode::GetCPUCurFreq(int cpuNum)
{
    float fVal;
    std::fstream myfile(cpu_node_list[cpuNum].c_str(), std::ios_base::in);
    myfile >> fVal;
    string freq;
    ostringstream oss;
    oss << (fVal/1000);
    freq = oss.str();
    return freq;
}

string GetNode::GetCPUTemp(int cpuNum)
{
    float fVal = 66;
    if (kernel_ver[0] == '4') {
      ostringstream oss;
      oss << TEMP_NODE_v4 << cpuNum << "/temp";
      string path = oss.str();
      std::fstream myfile(path.c_str(), std::ios_base::in);
      myfile >> fVal;
    } else {
      std::fstream myfile(TEMP_NODE, std::ios_base::in);
      string line;
      for (int i = 0; i < (cpuNum + 1)*3 - 1; i++)
        myfile >> line;
      int temp;
      myfile >> temp;
      fVal = temp/1000;
    }
    ostringstream oss;
    oss << fVal;
    string temp = oss.str();
    return temp;
}


int GetNode::open_sensor(const char *node, sensor_t *sensor)
{
    if ((sensor->fd = open(node, O_RDWR)) < 0)
        std::cerr << node << "Open Fail";

    return sensor->fd;
}

int GetNode::OpenINA231()
{
    if (open_sensor(DEV_SENSOR_ARM, &sensor[SENSOR_ARM]) < 0)
        return -1;
    if (open_sensor(DEV_SENSOR_MEM, &sensor[SENSOR_MEM]) < 0)
        return -1;
    if (open_sensor(DEV_SENSOR_KFC, &sensor[SENSOR_KFC]) < 0)
        return -1;
    if (open_sensor(DEV_SENSOR_G3D, &sensor[SENSOR_G3D]) < 0)
        return -1;

    if (read_sensor_status(&sensor[SENSOR_ARM]))
        return -1;
    if (read_sensor_status(&sensor[SENSOR_MEM]))
        return -1;
    if (read_sensor_status(&sensor[SENSOR_KFC]))
        return -1;
    if (read_sensor_status(&sensor[SENSOR_G3D]))
        return -1;

    if (!sensor[SENSOR_ARM].data.enable)
        enable_sensor(&sensor[SENSOR_ARM], 1);
    if (!sensor[SENSOR_MEM].data.enable)
        enable_sensor(&sensor[SENSOR_MEM], 1);
    if (!sensor[SENSOR_KFC].data.enable)
        enable_sensor(&sensor[SENSOR_KFC], 1);
    if (!sensor[SENSOR_G3D].data.enable)
        enable_sensor(&sensor[SENSOR_G3D], 1);

    return 0;
}

void GetNode::CloseINA231()
{
    if (sensor[SENSOR_ARM].data.enable)
        enable_sensor(&sensor[SENSOR_ARM], 0);
    if (sensor[SENSOR_MEM].data.enable)
        enable_sensor(&sensor[SENSOR_MEM], 0);
    if (sensor[SENSOR_KFC].data.enable)
        enable_sensor(&sensor[SENSOR_KFC], 0);
    if (sensor[SENSOR_G3D].data.enable)
        enable_sensor(&sensor[SENSOR_G3D], 0);

    close_sensor(&sensor[SENSOR_ARM]);
    close_sensor(&sensor[SENSOR_MEM]);
    close_sensor(&sensor[SENSOR_KFC]);
    close_sensor(&sensor[SENSOR_G3D]);
}

void GetNode::GetINA231()
{
    read_sensor(&sensor[SENSOR_ARM]);
    read_sensor(&sensor[SENSOR_MEM]);
    read_sensor(&sensor[SENSOR_KFC]);
    read_sensor(&sensor[SENSOR_G3D]);

    armuV = (float)(sensor[SENSOR_ARM].data.cur_uV / 100000) / 10;
    armuA = (float)(sensor[SENSOR_ARM].data.cur_uA / 1000) / 1000;
    armuW = (float)(sensor[SENSOR_ARM].data.cur_uW / 1000) / 1000;

    memuV = (float)(sensor[SENSOR_MEM].data.cur_uV / 100000) / 10;
    memuA = (float)(sensor[SENSOR_MEM].data.cur_uA / 1000) / 1000;
    memuW = (float)(sensor[SENSOR_MEM].data.cur_uW / 1000) / 1000;

    kfcuV = (float)(sensor[SENSOR_KFC].data.cur_uV / 100000) / 10;
    kfcuA = (float)(sensor[SENSOR_KFC].data.cur_uA / 1000) / 1000;
    kfcuW = (float)(sensor[SENSOR_KFC].data.cur_uW / 1000) / 1000;

    g3duV = (float)(sensor[SENSOR_G3D].data.cur_uV / 100000) / 10;
    g3duA = (float)(sensor[SENSOR_G3D].data.cur_uA / 1000) / 1000;
    g3duW = (float)(sensor[SENSOR_G3D].data.cur_uW / 1000) / 1000;

}

void GetNode::enable_sensor(sensor_t *sensor, unsigned char enable)
{
    if (sensor->fd > 0) {
        sensor->data.enable = enable ? 1 : 0;
        if (ioctl(sensor->fd, INA231_IOCSSTATUS, &sensor->data) < 0)
            std::cerr << "IOCTL Error";
    }
}

int GetNode::read_sensor_status(sensor_t *sensor)
{
    if (sensor->fd > 0) {
        if (ioctl(sensor->fd, INA231_IOCGSTATUS, &sensor->data) < 0)
            std::cerr << sensor->data.name << "IOCTL Error";
    }
    return 0;
}

void GetNode::read_sensor(sensor_t *sensor)
{
    if (sensor->fd > 0) {
        if (ioctl(sensor->fd, INA231_IOCGREG, &sensor->data) < 0)
            std::cerr << sensor->data.name << "IOCTL Error!";
    }
}

void GetNode::close_sensor(sensor_t *sensor)
{
    if (sensor->fd > 0)
        close(sensor->fd);
}

int GetNode::calUsage(int cpu_idx, int user, int system, int idle)
{
    long total = 0;
    long usage = 0;
    int diff_user, diff_system, diff_idle;

    diff_user = mOldUserCPU[cpu_idx] - user;
    diff_system = mOldSystemCPU[cpu_idx] - system;
    diff_idle = mOldIdleCPU[cpu_idx] - idle;

    total = diff_user + diff_system + diff_idle;
    if (total != 0)
        usage = diff_user * 100 / total;

    mOldUserCPU[cpu_idx] =user;
    mOldSystemCPU[cpu_idx] = system;
    mOldIdleCPU[cpu_idx] = idle;

    return usage;
}

int GetNode::GetCPUUsage(void)
{
    char buf[80] = {0};
    char cpuid[8] = "cpu";
    int findCPU = 0;
    int user, system, nice, idle;
    FILE *fp;
    int cpu_index = 0;

    fp = fopen("/proc/stat", "r");
    if (fp == NULL)
        return 0;

    while (fgets(buf, 80, fp)) {
        char temp[4] = "cpu";
        temp[3] = '0' + cpu_index;
        if (!strncmp(buf, temp, 4)) {
            findCPU = 1;
            sscanf(buf, "%s %d %d %d %d",
                   cpuid, &user, &nice, &system, &idle);
            usage[cpu_index] = calUsage(cpu_index, user, system, idle);
            cpu_index++;
        }
        if (!strncmp(buf, "intr", 4))
            break;
        if (findCPU == 0)
            mOldUserCPU[cpu_index] = mOldSystemCPU[cpu_index] = mOldIdleCPU[cpu_index] = 0;
        else
            findCPU = 0;
    }

    fclose(fp);

    return 0;
}
