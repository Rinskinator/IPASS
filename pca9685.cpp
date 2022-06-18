#include "hwlib.hpp"
#include "pca9685.hpp"

pca9685_lib::pca9685_lib(hwlib::i2c_bus &bus, uint8_t &slave_address):
        bus(bus),
        slave_address(slave_address)
    {}

void pca9685_lib::write_single(uint8_t data, uint8_t register_address) {
    auto writer = bus.write(slave_address);
    writer.write(register_address);
    writer.write(data);
}

void pca9685_lib::read_register(uint8_t register_address) {
    {
        auto writer = bus.write(slave_address);
        writer.prepare_repeated_start();
        writer.write(register_address);
    }

    auto read_data = bus.read(slave_address).read_byte();
    hwlib::cout << read_data << hwlib::endl;
}

void pca9685_lib::setup() {
    write_single(0x11, MODE1); //mode1_sleep, mode1_address
    read_register(MODE1);

    write_single(0x79, 0xFE); //prescale_value, prescale_address
    read_register(0xFE); //prescale_address

    write_single(0x01, 0x00); //mode1_awake, mode1_address
    read_register(0x00);
}

void pca9685_lib::servo_output(servo_data data, servo_registers reg){

        write_single(data.LED_ON_L, reg.LED_ON_L);
        read_register(reg.LED_ON_L);

        write_single(data.LED_ON_H, reg.LED_ON_H);
        read_register(reg.LED_ON_H);

        write_single(data.LED_OFF_L, reg.LED_OFF_L);
        read_register(reg.LED_OFF_L);

        write_single(data.LED_OFF_H, reg.LED_OFF_H);
        read_register(reg.LED_OFF_H);

    }

pca9685_lib::servo_data pca9685_lib::converter(int percentage) {
    uint8_t data1 = 0x00;
    uint8_t data2 = 0x00;

    if (percentage < 36){
        uint8_t pulse_value = (4.05 * percentage) + 107;
        uint8_t data3 = pulse_value;
        uint8_t data4 = 0x00;
        servo_data data_register_values = {data1, data2, data3, data4};
        return data_register_values;
    }

    else {
        uint16_t pulse_value = (4.05 * percentage) + 107;
        uint8_t data3;
        uint8_t data4;

    data4 = *((uint8_t*)&(pulse_value)+1); //right byte (0x12)
    data3 = *((uint8_t*)&(pulse_value)+0); //left byte  (0x34)
    servo_data data_register_values = {data1, data2, data3, data4};
    return data_register_values;
    }
}


