#include "hwlib.hpp"
#include "robotHond.hpp"
#include "registerConstants.hpp"

spot::spot(hwlib::i2c_bus &bus, uint8_t &slave_address):
    pca9685_lib(bus,slave_address)
    {}

void spot::lay_down(registers register_struct){

    movement lay_down_input = {converter(90),
                               converter(-5),
                               converter(85),
                               converter(3),
                               converter(40),
                               converter(67),
                               converter(60),
                               converter(50),
                               converter(65),
                               converter(45),
                               converter(62),
                               converter(32)

    };

    write_single(0x11, 0x00); //mode1_sleep, mode1_address
    read_register(0x00);

    servo_output(lay_down_input.front_right_knee,       register_struct.servo0_registers);
    servo_output(lay_down_input.front_left_knee,        register_struct.servo4_registers);
    servo_output(lay_down_input.back_right_knee,        register_struct.servo8_registers);
    servo_output(lay_down_input.back_left_knee,         register_struct.servo12_registers);

    servo_output(lay_down_input.front_right_leg,        register_struct.servo1_registers);
    servo_output(lay_down_input.front_left_leg,         register_struct.servo5_registers);
    servo_output(lay_down_input.back_right_leg,         register_struct.servo9_registers);
    servo_output(lay_down_input.back_left_leg,          register_struct.servo13_registers);

    servo_output(lay_down_input.front_right_shoulder,   register_struct.servo2_registers);
    servo_output(lay_down_input.front_left_shoulder,    register_struct.servo6_registers);
    servo_output(lay_down_input.back_right_shoulder,    register_struct.servo10_registers);
    servo_output(lay_down_input.back_left_shoulder,     register_struct.servo14_registers);

    write_single(0x01, 0x00); //mode1_awake, mode1_address
    read_register(0x00);
//        hwlib::wait_ms(5000);

}


void spot::stand_up(registers register_struct){

    movement stand_input_back = {converter(90),
                                 converter(-5),
                                 converter(60),
                                 converter(25),
                                 converter(40),
                                 converter(67),
                                 converter(60),
                                 converter(50),
                                 converter(65),
                                 converter(45),
                                 converter(62),
                                 converter(32)

    };

    movement stand_input_front = {converter(75),
                                  converter(10),
                                  converter(60),
                                  converter(25),
                                  converter(40),
                                  converter(67),
                                  converter(60),
                                  converter(50),
                                  converter(65),
                                  converter(45),
                                  converter(62),
                                  converter(32)

    };

    write_single(0x11, 0x00); //mode1_sleep, mode1_address
    read_register(0x00);

    servo_output(stand_input_back.front_right_knee,       register_struct.servo0_registers);
    servo_output(stand_input_back.front_left_knee,        register_struct.servo4_registers);
    servo_output(stand_input_back.back_right_knee,        register_struct.servo8_registers);
    servo_output(stand_input_back.back_left_knee,         register_struct.servo12_registers);

    servo_output(stand_input_back.front_right_leg,        register_struct.servo1_registers);
    servo_output(stand_input_back.front_left_leg,         register_struct.servo5_registers);
    servo_output(stand_input_back.back_right_leg,         register_struct.servo9_registers);
    servo_output(stand_input_back.back_left_leg,          register_struct.servo13_registers);

    servo_output(stand_input_back.front_right_shoulder,   register_struct.servo2_registers);
    servo_output(stand_input_back.front_left_shoulder,    register_struct.servo6_registers);
    servo_output(stand_input_back.back_right_shoulder,    register_struct.servo10_registers);
    servo_output(stand_input_back.back_left_shoulder,     register_struct.servo14_registers);

    write_single(0x01, 0x00); //mode1_awake, mode1_address
    read_register(0x00);

    hwlib::wait_ms(500);

    write_single(0x11, 0x00); //mode1_sleep, mode1_address
    read_register(0x00);

    servo_output(stand_input_front.front_right_knee,       register_struct.servo0_registers);
    servo_output(stand_input_front.front_left_knee,        register_struct.servo4_registers);
    servo_output(stand_input_front.back_right_knee,        register_struct.servo8_registers);
    servo_output(stand_input_front.back_left_knee,         register_struct.servo12_registers);

    servo_output(stand_input_front.front_right_leg,        register_struct.servo1_registers);
    servo_output(stand_input_front.front_left_leg,         register_struct.servo5_registers);
    servo_output(stand_input_front.back_right_leg,         register_struct.servo9_registers);
    servo_output(stand_input_front.back_left_leg,          register_struct.servo13_registers);

    servo_output(stand_input_front.front_right_shoulder,   register_struct.servo2_registers);
    servo_output(stand_input_front.front_left_shoulder,    register_struct.servo6_registers);
    servo_output(stand_input_front.back_right_shoulder,    register_struct.servo10_registers);
    servo_output(stand_input_front.back_left_shoulder,     register_struct.servo14_registers);

    write_single(0x01, 0x00); //mode1_awake, mode1_address
    read_register(0x00);

}

void spot::sit(registers register_struct) {

    movement sit_input = {converter(40),
                          converter(45),
                          converter(80),
                          converter(10),
                          converter(40),
                          converter(65),
                          converter(40),
                          converter(65),
                          converter(65),
                          converter(45),
                          converter(62),
                          converter(32)

    };

    write_single(0x11, 0x00); //mode1_sleep, mode1_address
    read_register(0x00);

    servo_output(sit_input.front_right_knee,       register_struct.servo0_registers);
    servo_output(sit_input.front_left_knee,        register_struct.servo4_registers);
    servo_output(sit_input.back_right_knee,        register_struct.servo8_registers);
    servo_output(sit_input.back_left_knee,         register_struct.servo12_registers);

    servo_output(sit_input.front_right_leg,        register_struct.servo1_registers);
    servo_output(sit_input.front_left_leg,         register_struct.servo5_registers);
    servo_output(sit_input.back_right_leg,         register_struct.servo9_registers);
    servo_output(sit_input.back_left_leg,          register_struct.servo13_registers);

    servo_output(sit_input.front_right_shoulder,   register_struct.servo2_registers);
    servo_output(sit_input.front_left_shoulder,    register_struct.servo6_registers);
    servo_output(sit_input.back_right_shoulder,    register_struct.servo10_registers);
    servo_output(sit_input.back_left_shoulder,     register_struct.servo14_registers);

    write_single(0x01, 0x00); //mode1_awake, mode1_address
    read_register(0x00);
    //        hwlib::wait_ms(5000);

}