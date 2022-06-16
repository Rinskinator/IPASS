#ifndef YOUR_PROJECT_NAME_ROBOTHOND_HPP
#define YOUR_PROJECT_NAME_ROBOTHOND_HPP

#include "hwlib.hpp"
#include "registerConstants.hpp"
#include "pca9685.hpp"

class spot : public pca9685_lib {
private:

public:
    spot(hwlib::i2c_bus &bus, uint8_t &slave_address);

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



    /**
     * @brief function to make spot lay down.
     *
     * @details This function is used to put the servo's in the position for spot to lay down. The function uses the
     * converter function to determine the servo positions.
     *
     * @param register_struct struct consisting of the servos used to control spot.
     */

    void lay_down(registers register_struct);

    /**
     * @brief function to make spot stand_up.
     *
     * @details This function is used to put the servo's in the position for spot to stand up. The function uses the
     * converter function to determine the servo positions.
     *
     * @param register_struct struct consisting of the servos used to control spot.
     */
    void stand_up(registers register_struct);

    /**
     * @brief function to make spot sit.
     *
     * @details This function is used to put the servo's in the position for spot to sit down. The function uses the
     * converter function to determine the servo positions.
     *
     * @param register_struct struct consisting of the servos used to control spot.
     */

    void sit(registers register_struct);

};


#endif //YOUR_PROJECT_NAME_ROBOTHOND_HPP
