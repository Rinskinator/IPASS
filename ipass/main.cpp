#include "hwlib.hpp"
#include "pca9685.hpp"
#include "robotHond.hpp"

int main(){
    uint8_t chip_address = 0x40;

    // Knee joint regsiters
    pca9685_lib::servo_registers servo0_registers = {LED0_ON_L, LED0_ON_H, LED0_OFF_L, LED0_OFF_H};
    pca9685_lib::servo_registers servo4_registers = {LED4_ON_L, LED4_ON_H, LED4_OFF_L, LED4_OFF_H};
    pca9685_lib::servo_registers servo8_registers = {LED8_ON_L, LED8_ON_H, LED8_OFF_L, LED8_OFF_H};
    pca9685_lib::servo_registers servo12_registers = {LED12_ON_L, LED12_ON_H, LED12_OFF_L, LED12_OFF_H};

    // leg joint registers
    pca9685_lib::servo_registers servo1_registers = {LED1_ON_L, LED1_ON_H, LED1_OFF_L, LED1_OFF_H};
    pca9685_lib::servo_registers servo5_registers = {LED5_ON_L, LED5_ON_H, LED5_OFF_L, LED5_OFF_H};
    pca9685_lib::servo_registers servo9_registers = {LED9_ON_L, LED9_ON_H, LED9_OFF_L, LED9_OFF_H};
    pca9685_lib::servo_registers servo13_registers = {LED13_ON_L, LED13_ON_H, LED13_OFF_L, LED13_OFF_H};

    // shoulder joint regsisters
    pca9685_lib::servo_registers servo2_registers = {LED2_ON_L, LED2_ON_H, LED2_OFF_L, LED2_OFF_H};
    pca9685_lib::servo_registers servo6_registers = {LED6_ON_L, LED6_ON_H, LED6_OFF_L, LED6_OFF_H};
    pca9685_lib::servo_registers servo10_registers = {LED10_ON_L, LED10_ON_H, LED10_OFF_L, LED10_OFF_H};
    pca9685_lib::servo_registers servo14_registers = {LED14_ON_L, LED14_ON_H, LED14_OFF_L, LED14_OFF_H};

    pca9685_lib::registers all_registers {servo0_registers ,servo4_registers, servo8_registers,servo12_registers,
                                          servo1_registers,servo5_registers,servo9_registers,servo13_registers,
                                          servo2_registers,servo6_registers,servo10_registers,servo14_registers};


    // scl and sda setup
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::d12);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::d13);

    // bus setup
    auto servo_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

    pca9685_lib pca(servo_bus, chip_address);

    pca.setup();

    spot robot_dog(servo_bus, chip_address);


    for(unsigned int i=0; i<3; i++) {

        robot_dog.sit(all_registers);
        hwlib::wait_ms(2000);

        robot_dog.lay_down(all_registers);
        hwlib::wait_ms(2000);

        robot_dog.stand_up(all_registers);
        hwlib::wait_ms(2000);

    }
}