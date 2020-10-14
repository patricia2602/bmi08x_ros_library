#include "bmi08x_ros_library/bmi08x_interface.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <iomanip> // for using std::fixed and std::setprecision
#include <ctime>

BMI08X bmi=BMI08X();

void set_default(bmi08x_dev *dev){
    dev->accel_cfg.power = BMI08X_ACCEL_PM_ACTIVE;
    dev->accel_cfg.range = BMI088_ACCEL_RANGE_3G;
    dev->accel_cfg.bw = BMI08X_ACCEL_BW_NORMAL;
    dev->accel_cfg.odr = BMI08X_ACCEL_ODR_100_HZ;

    // gyro
    
    dev->gyro_cfg.power = BMI08X_GYRO_PM_NORMAL;
    dev->gyro_cfg.odr = BMI08X_GYRO_BW_23_ODR_200_HZ;
    dev->gyro_cfg.range = BMI08X_GYRO_RANGE_1000_DPS;
    dev->gyro_cfg.bw = BMI08X_GYRO_BW_23_ODR_200_HZ;
}

int main(){
    int8_t rslt = BMI08X_OK;
    std::cout << "First: " << BMI08X_OK << std::endl;
    uint8_t data = 0;
    bmi08x_dev dev;
    dev = bmi.initialize(rslt);
   
    // get gyro power mode
    rslt = bmi08g_get_power_mode(&dev);
    rslt = bmi08a_get_power_mode(&dev);
//    set_default(&dev);

    
    //    rslt = bmi08a_set_regs(BMI08X_REG_ACCEL_PWR_CTRL, &cmd, 1, &sensor);
//    rslt = bmi08a_set_power_mode(&dev);    
//    set_default(&dev);
//    rslt = bmi08a_set_meas_conf(&dev);
    rslt = bmi08a_get_meas_conf(&dev);   
//    rslt = bmi08a_get_regs(0x7D, &data, 1, &dev);
    


//    while(rslt == BMI08X_OK && dev.accel_cfg.power == BMI08X_ACCEL_PM_ACTIVE){
//        rslt = bmi08a_get_data(&raw_acc, &dev);
//	std::cout << "raw_acc_x:" << raw_acc.x << " raw_acc_y:" << raw_acc.y << " raw_acc_z:" << raw_acc.z << std::endl;
//    }


//    // talk to gyro
//    struct bmi08x_sensor_data raw_gyro;
//    rslt = bmi08g_set_power_mode(&dev);
//    set_default(&dev);
//    while (rslt == BMI08X_OK){
//    rslt = bmi08g_get_data(&raw_gyro, &dev);
//    std::cout << std::fixed << "raw_gyro_x: " << raw_gyro.x << "\n raw_gyro_y:" << raw_gyro.y << "\n raw_gyro_z:" << raw_gyro.z << std::endl;
//    }


    // talk to acc
    struct bmi08x_sensor_data raw_acc;
    int32_t raw_tmp;
    std::cout << "Second: " << (rslt!=BMI08X_OK) << std::endl;
    set_default(&dev);
    rslt = bmi08a_set_power_mode(&dev);
    rslt = bmi08a_set_meas_conf(&dev);
    while (rslt == BMI08X_OK){
    rslt = bmi08a_get_data(&raw_acc, &dev);
    std::cout << std::fixed << "raw_acc_x: " << raw_acc.x << "\n raw_acc_y:" << raw_acc.y << "\n raw_acc_z:" << raw_acc.z << std::endl;
    rslt = bmi08a_get_sensor_temperature(&dev, &raw_tmp);
    std::cout << "temperature" << raw_tmp << std::endl;
    }

    return 0;
}

