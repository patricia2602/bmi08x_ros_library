#include "bmi08x_ros_library/bmi08x_interface.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <iomanip> // for using std::fixed and std::setprecision
#include <ctime>

BMI08X bmi = BMI08X();

int main(){
    int8_t rslt = BMI08X_OK;
    bmi08x_dev sensor;
    //sensor = bmi.initialize(rslt);
    std::cout << "status: " <<std::endl;
    struct bmi08x_sensor_data raw_acc;
   // rslt = bmi08a_get_synchronized_data(&raw_acc, NULL, &sensor);
    std::cout << "raw_acc_x" << raw_acc.x << std::endl;
    return 0;
}

