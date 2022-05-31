#ifndef YOUR_PROJECT_NAME_PCA9685_HPP
#define YOUR_PROJECT_NAME_PCA9685_HPP

#include "hwlib.hpp"
#include "registerConstants.hpp"


class pca9685_lib {
protected:
    hwlib::i2c_bus &bus;
    uint8_t &slave_address;


public:
    pca9685_lib(hwlib::i2c_bus &bus, uint8_t &slave_address) ;

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

    void write_single(uint8_t data, uint8_t register_address) ;


    /**
     * @brief Reads register byte.
     *
     * @details This function reads the data byte in a user specified register. This function writes the slave addres
     * and register address after which the specified address can be read using a read opperation. The writer object is
     * given a scope after which the writer object is destroyed.
     *
     * @param register_address User specified address of which the user want to read the containments.
     */

    void read_register(uint8_t register_address) ;


    /** @brief funcion used to initialize the pca9685 chip.
     *
     * @details This functions is used to initialize the pca9685 chip. To control servo's the prescale register value
     * needs to be changed to 121. To change the value of this register the sleep bit in the MODE1 register needs to be
     * set first, after which the prescale register value can be changed. Finally the sleep bit in the MODE1 register
     * needs to be changed back to active mode.
     */

    void setup() ;

    /**
     * @brief funtion is used to write data to registers to move 1 servo.
     *
     *
     * @param data A struct containing four 8 bit values (LED_ON_L, LED_ON_H, LED_OFF_L, LED_OFF_H). Each value is
     * writen to the corresponding register struct.
     * @param reg A struct containing four 8 bit regsiter addresses (LED_ON_L, LED_ON_H, LED_OFF_L, LED_OFF_H). Each
     * register variable corresponds to a data value.
     */

    void servo_output(servo_data data, servo_registers reg) ;

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

    servo_data converter(int percentage);

};


#endif //YOUR_PROJECT_NAME_PCA9685_HPP
