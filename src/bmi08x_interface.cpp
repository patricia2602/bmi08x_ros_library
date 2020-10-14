#include "bmi08x_ros_library/bmi08x_interface.h"

int file;
int adapter_nr = 2;
char filename[40];

BMI08X::BMI08X(){  //the main sensor interface class constructor

    sprintf(filename, "/dev/i2c-1");
    file = open(filename, O_RDWR);

    if ( file < 0)
    {
        std::cout << ("Failed to open the bus.") << std::endl;
        exit(1);
    }

    /* The I2C address */

    if (ioctl(file, I2C_SLAVE, BMI08X_ACCEL_I2C_ADDR_SECONDARY) < 0 || ioctl(file, I2C_SLAVE, BMI08X_GYRO_I2C_ADDR_SECONDARY) < 0)
    {
        std::cout << ("Failed to acquire either bus access and/or talk to slave.") << std::endl;
        exit(1);
    }
        else{
        printf("BMI08X_ACCEL found at 0x%02X\nBMI08X_GYRO found at 0x%02X\n",  BMI08X_ACCEL_I2C_ADDR_SECONDARY, BMI08X_GYRO_I2C_ADDR_SECONDARY);
    }

}

BMI08X_INTF_RET_TYPE i2c_read(uint8_t reg_addr, uint8_t *read_data, uint32_t len, void *intf_ptr){
            // std::cout << ("i2c_read.") << std::endl;

            uint8_t buffer_write[2];
            memset(buffer_write, '\0',2);
            int n_writ;
            n_writ = 0;
            // Request data
            buffer_write[0] = reg_addr;

            n_writ = write(file,buffer_write,1);

            if(n_writ!=1){
                std::cout << ("BMI08X Reading Error (cannot request data): Failed to write.") << std::endl;
                return -1;
            }

            int n_read;
            // Read data
            n_read = read(file,read_data,len);
            if(n_read != len)
            {
                /* ERROR HANDLING: i2c transaction failed */
                std::cout << "BMI08X Reading Error (not enough data readed) :Failed to read" << std::endl;

                return -1;
            }

            return BMI08X_OK;
}

BMI08X_INTF_RET_TYPE i2c_write(uint8_t reg_addr, const uint8_t *read_data, uint32_t len, void *intf_ptr){
            // std::cout << ("i2c_write.") << std::endl;
            
            uint8_t buffer_write[len+1]; // cast needed???!?
            memset(buffer_write,'\0',len+1);
            int n_writ;
            buffer_write[0] = reg_addr;

            for(int i = 0; i<len; i++)
            {
                buffer_write[i+1] = read_data[i];
            }
            n_writ = write(file,buffer_write, len+1);

            if( n_writ < len+1)
            {
                /* ERROR HANDLING: i2c transaction failed */
                std::cout << "BMI08X Writing Error (not enough data readed) :Failed to read" << std::endl;
                return -1;
            }
            return BMI08X_OK;

}

void user_delay(uint32_t period, void *intf_ptr){
            // std::cout << ("i2c_delayed for: ") << period*1000 << " ms" << std::endl;
            usleep(period*1000);

}

bmi08x_dev BMI08X::initialize(int8_t &rslt){
    struct bmi08x_dev dev;
    uint8_t acc_dev_addr = BMI08X_ACCEL_I2C_ADDR_SECONDARY; 
    uint8_t gyro_dev_addr = BMI08X_GYRO_I2C_ADDR_SECONDARY;
    dev.intf_ptr_accel = &acc_dev_addr;
    dev.intf_ptr_gyro = &gyro_dev_addr;
    dev.accel_chip_id = acc_dev_addr;
    dev.gyro_chip_id = gyro_dev_addr;
    dev.intf = BMI08X_I2C_INTF;
    dev.read = i2c_read;
    dev.write = i2c_write;
    dev.delay_us = user_delay;
    dev.variant = BMI088_VARIANT;

    rslt = bmi08a_init(&dev);
    rslt = bmi08g_init(&dev);

    return dev;
}

