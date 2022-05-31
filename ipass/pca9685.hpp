#ifndef YOUR_PROJECT_NAME_PCA9685_HPP
#define YOUR_PROJECT_NAME_PCA9685_HPP

#include "hwlib.hpp"
#include "registerConstants.hpp"


class pca9685_lib {
protected:
    hwlib::i2c_bus &bus;
    uint8_t &slave_address;


public:
    pca9685_lib(hwlib::i2c_bus &bus, uint8_t &slave_address) :
        bus(bus),
        slave_address(slave_address)
    {}

    struct servo_registers {
        uint8_t LED_ON_L;
        uint8_t LED_ON_H;
        uint8_t LED_OFF_L;
        uint8_t LED_OFF_H;
    };

    struct servo_data {
        uint8_t LED_ON_L;
        uint8_t LED_ON_H;
        uint8_t LED_OFF_L;
        uint8_t LED_OFF_H;
    };

    struct movement {
        servo_data front_right_knee;
        servo_data front_left_knee;
        servo_data back_right_knee;
        servo_data back_left_knee;
        servo_data front_right_leg;
        servo_data front_left_leg;
        servo_data back_right_leg;
        servo_data back_left_leg;
        servo_data front_right_shoulder;
        servo_data front_left_shoulder;
        servo_data back_right_shoulder;
        servo_data back_left_shoulder;
    };

    struct registers {
        servo_registers servo0_registers;
        servo_registers servo4_registers;
        servo_registers servo8_registers;
        servo_registers servo12_registers;
        servo_registers servo1_registers;
        servo_registers servo5_registers;
        servo_registers servo9_registers;
        servo_registers servo13_registers;
        servo_registers servo2_registers;
        servo_registers servo6_registers;
        servo_registers servo10_registers;
        servo_registers servo14_registers;
    };


    /**
     * @brief writes byte to pca9685 register.
     *
     * @details This function writes a data byte to a by user specified register address. To write to a specified
     * register the writer object is made. The slave address is written to the pca9685 chip followed by the register
     * address. Once these opperations are preformed the data is writen into the specified register.
     *
     * @param data 8 bits of data. This data is writen to a register.
     * @param register_address the address of the register to write to.
     */

    void write_single(uint8_t data, uint8_t register_address) {
        auto writer = bus.write(slave_address);
        writer.write(register_address);
        writer.write(data);
    }


    /**
     * @brief Reads register byte.
     *
     * @details This function reads the data byte in a user specified register. This function writes the slave addres
     * and register address after which the specified address can be read using a read opperation. The writer object is
     * given a scope after which the writer object is destroyed.
     *
     * @param register_address User specified address of which the user want to read the containments.
     */

    void read_register(uint8_t register_address) {
        {
            auto writer = bus.write(slave_address);
            writer.prepare_repeated_start();
            writer.write(register_address);
        }

        auto read_data = bus.read(slave_address).read_byte();
        hwlib::cout << read_data << hwlib::endl;
    }

    /** @brief funcion used to initialize the pca9685 chip.
     *
     * @details This functions is used to initialize the pca9685 chip. To control servo's the prescale register value
     * needs to be changed to 121. To change the value of this register the sleep bit in the MODE1 register needs to be
     * set first, after which the prescale register value can be changed. Finally the sleep bit in the MODE1 register
     * needs to be changed back to active mode.
     */

    void setup() {
        write_single(0x11, MODE1); //mode1_sleep, mode1_address
        read_register(MODE1);

        write_single(0x79, 0xFE); //prescale_value, prescale_address
        read_register(0xFE); //prescale_address

        write_single(0x01, 0x00); //mode1_awake, mode1_address
        read_register(0x00);
    }


    /**
     * @brief funtion is used to write data to registers to move 1 servo.
     *
     *
     * @param data A struct containing four 8 bit values (LED_ON_L, LED_ON_H, LED_OFF_L, LED_OFF_H). Each value is
     * writen to the corresponding register struct.
     * @param reg A struct containing four 8 bit regsiter addresses (LED_ON_L, LED_ON_H, LED_OFF_L, LED_OFF_H). Each
     * register variable corresponds to a data value.
     */

    void servo_output(servo_data data, servo_registers reg){

        write_single(data.LED_ON_L, reg.LED_ON_L); // always 0
        read_register(reg.LED_ON_L);

        write_single(data.LED_ON_H, reg.LED_ON_H); // always 0
        read_register(reg.LED_ON_H);

        write_single(data.LED_OFF_L, reg.LED_OFF_L); // value
        read_register(reg.LED_OFF_L);

        write_single(data.LED_OFF_H, reg.LED_OFF_H); // value
        read_register(reg.LED_OFF_H);

    }

    /**
     * @brief Converts a percentage to servo register outputs.
     *
     * @details Converts a percentage to register values. The first two registers refere to the on value of the servo.
     * The last two registers refere the value at which the pulse needs to be pulled low. This value is spread out over
     * two registers. If the percentage is lower than 36 the latest register is always 0. If the precentage is higher
     * than 36 the value is split over the two registers.
     *
     * @param percentage User specified percentage.
     * @return returns the servo_data struct containing four data values.
     */

    servo_data converter(int percentage){
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

    /**
     * @brief function to make spot lay down.
     *
     * @details This function is used to put the servo's in the position for spot to lay down. The function uses the
     * converter function to determine the servo positions.
     *
     *
     * @param register_struct struct consisting of the servos used to control spot.
     */

    void lay_down(registers register_struct){

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

    void stand_up(registers register_struct){

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
    void sit(registers register_struct){

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



//    void read_register(uint8_t register_address);
//
//    void write_single(uint8_t data, uint8_t register_address);
//
//    void setup();
//
//    void servo_output(servo_data data, servo_registers reg);

};


#endif //YOUR_PROJECT_NAME_PCA9685_HPP
