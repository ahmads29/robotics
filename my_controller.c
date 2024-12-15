#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <webots/keyboard.h>

#define TIME_STEP 64

// Initialize sensors and motors
void initializeSensors(WbDeviceTag *sensors, WbDeviceTag *left_motor, WbDeviceTag *right_motor) {
    sensors[0] = wb_robot_get_device("ps0");
    sensors[1] = wb_robot_get_device("ps1");
    wb_distance_sensor_enable(sensors[0], TIME_STEP);
    wb_distance_sensor_enable(sensors[1], TIME_STEP);
    *left_motor = wb_robot_get_device("left wheel motor");
    *right_motor = wb_robot_get_device("right wheel motor");
    wb_motor_set_position(*left_motor, INFINITY);
    wb_motor_set_position(*right_motor, INFINITY);
    wb_motor_set_velocity(*left_motor, 0.0);
    wb_motor_set_velocity(*right_motor, 0.0);
}

// Process keyboard inputs
void processKeyboardInput(int key, WbDeviceTag left_motor, WbDeviceTag right_motor) {
    double speed = 2.0;
    if (key == WB_KEYBOARD_UP) {
        wb_motor_set_velocity(left_motor, speed);
        wb_motor_set_velocity(right_motor, speed);
    } else if (key == WB_KEYBOARD_DOWN) {
        wb_motor_set_velocity(left_motor, -speed);
        wb_motor_set_velocity(right_motor, -speed);
    } else if (key == WB_KEYBOARD_LEFT) {
        wb_motor_set_velocity(left_motor, -speed);
        wb_motor_set_velocity(right_motor, speed);
    } else if (key == WB_KEYBOARD_RIGHT) {
        wb_motor_set_velocity(left_motor, speed);
        wb_motor_set_velocity(right_motor, -speed);
    } else {
        wb_motor_set_velocity(left_motor, 0.0);
        wb_motor_set_velocity(right_motor, 0.0);
    }
}

int main() {
    wb_robot_init();

    WbDeviceTag sensors[2];
    WbDeviceTag left_motor, right_motor;
    initializeSensors(sensors, &left_motor, &right_motor);

    wb_keyboard_enable(TIME_STEP);

    while (wb_robot_step(TIME_STEP) != -1) {
        int key = wb_keyboard_get_key();
        processKeyboardInput(key, left_motor, right_motor);
    }

    wb_robot_cleanup();
    return 0;
}
