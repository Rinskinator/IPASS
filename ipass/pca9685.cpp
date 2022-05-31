//#include "hwlib.hpp"
//#include "pca9685.hpp"

// kijken of de struct hier kan????

//void pca9685_lib::write_single(uint8_t data, uint8_t register_address) {
//    auto writer = bus.write(slave_address);
//    writer.write(register_address);
//    writer.write(data);
//}
//
//void pca9685_lib::read_register(uint8_t register_address) {
//    {
//        auto writer = bus.write(slave_address);
//        writer.prepare_repeated_start();
//        writer.write(register_address);
//    }
//
//    auto read_data = bus.read(slave_address).read_byte();
//    hwlib::cout << read_data << hwlib::endl;
//}
//
//void pca9685_lib::setup() {
//    write_single(0x11, MODE1); //mode1_sleep, mode1_address
//    read_register(MODE1);
//
//    write_single(0x79, 0xFE); //prescale_value, prescale_address
//    read_register(0xFE); //prescale_address
//
//    write_single(0x01, 0x00); //mode1_awake, mode1_address
//    read_register(0x00);
//}
//
//void pca9685_lib::servo_output(servo_data data, servo_registers reg){
//
//        write_single(data.LED_ON_L, reg.LED_ON_L);
//        read_register(reg.LED_ON_L);
//
//        write_single(data.LED_ON_H, reg.LED_ON_H);
//        read_register(reg.LED_ON_H);
//
//        write_single(data.LED_OFF_L, reg.LED_OFF_L);
//        read_register(reg.LED_OFF_L);
//
//        write_single(data.LED_OFF_H, reg.LED_OFF_H);
//        read_register(reg.LED_OFF_H);
//
//    }

