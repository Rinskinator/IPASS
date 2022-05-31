#ifndef YOUR_PROJECT_NAME_MPU6050_HPP
#define YOUR_PROJECT_NAME_MPU6050_HPP

#include "hwlib.hpp"

class mpu6050_lib {
private:
    hwlib::i2c_bus &bus;
    uint8_t &slave_address;


public:
    mpu6050_lib(hwlib::i2c_bus &bus, uint8_t &slave_address) :
        bus(bus),
        slave_address(slave_address)
    {}

    void read_register(uint8_t register_address) {
        {
            auto writer = bus.write(slave_address);
            writer.prepare_repeated_start();
            writer.write(register_address);
        }

        auto read_data = bus.read(slave_address).read_byte();
        hwlib::cout << read_data << hwlib::endl;
    }

    void write_single(uint8_t data, uint8_t register_address) {
        auto writer = bus.write(slave_address);
        writer.write(register_address);
        writer.write(data);
    }

    void setup(){

    }
};


#endif //YOUR_PROJECT_NAME_MPU6050_HPP
