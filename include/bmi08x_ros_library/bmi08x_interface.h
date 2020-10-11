#ifndef _BMI08X_INTERFACE_H_
#define _BMI08X_INTERFACE_H_

#include  <linux/i2c-dev.h>  // manage i2c interface in ARM
#include  <stdint.h>         //All these libraries are needed to 
#include  <iostream>         //use the functions we'll implement, 
#include  <time.h>           //such as delay
#include  <stdio.h>
#include  <stdint.h>
#include  <stdlib.h>
#include  <string.h>
#include  <math.h>
#include  <unistd.h>
#include  <sys/ioctl.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <fcntl.h>
#include  <unistd.h>

#include "bmi08x.h"             //include the bmi160 repo headers
#include "bmi08x_defs.h"        //

void delay_us(uint32_t period, void *intf_ptr);

BMI08X_INTF_RET_TYPE i2c_read(uint8_t reg_addr, uint8_t *read_data, uint32_t len, void *intf_ptr);

BMI08X_INTF_RET_TYPE i2c_write(uint8_t reg_addr, uint8_t *read_data, uint32_t len, void *intf_ptr);

class BMI08X{
    public:
        BMI08X();
        bmi08x_dev initialize(int8_t &rslt);

        void set_sensor_settings(struct bmi08x_dev *dev, int mode, int8_t &rslt);

        void read_sensor_data(struct bmi108x_dev *dev, int8_t &rslt);
};


#endif
