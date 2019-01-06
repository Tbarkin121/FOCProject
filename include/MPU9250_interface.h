/*------------------------------------------------------------------------------
* Copyright © Tyler Barkin – All Rights Reserved
* Proprietary and Confidential
* Copying of this file or use of code contained in this file via any
* medium is strictly prohibited unless prior written permission is obtained
* from Tyler Barkin, Inc.
* Created by Tyler Barkin 2018
------------------------------------------------------------------------------*/

#ifndef INCLUDE_MPU9250_INTERFACE_H_
#define INCLUDE_MPU9250_INTERFACE_H_

#include <boost/units/base_unit.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/velocity.hpp>
#include <boost/units/systems/si/acceleration.hpp>
#include <boost/units/systems/si/angular_velocity.hpp>
#include <boost/units/systems/si/angular_acceleration.hpp>
#include <system_error>  // NOLINT(build/c++11)

using namespace boost::units;  // NOLINT(build/namespaces)
using namespace boost::units::si;  // NOLINT(build/namespaces)

//-----------------------------------------------------------------------------

enum class IMUError {
    UNINITIALIZED = 1
};

namespace std {
    template <>
    struct is_error_code_enum<IMUError> : public true_type {};
}

std::error_code make_error_code(IMUError error);
std::error_condition make_error_condition(IMUError error);

//-----------------------------------------------------------------------------
class IMPU9250 {
 public:
        IMPU9250() {}

        virtual std::error_code Initialize() const = 0;

        // struct AccelerationResult {
        //     AccelerationResult(quantity<acceleration, float> ax,
        //                         quantity<acceleration, float> ay, 
        //                         quantity<acceleration, float> az)
        //         : accel_x(ax), accel_y(ay), accel_z(az) {}
        //     explicit AccelerationResult(std::error_code err)
        //         : accel_x(0), accel_y(0), accel_z(0), error(err) {}

        //     quantity<acceleration, float> accel_x;
        //     quantity<acceleration, float> accel_y;
        //     quantity<acceleration, float> accel_z;
        //     std::error_code error;
        // };

        struct AccelerationResult {
            AccelerationResult(float ax, float ay, float az)
                : accel_x(ax), accel_y(ay), accel_z(az) {}
            explicit AccelerationResult(std::error_code err)
                : accel_x(0), accel_y(0), accel_z(0), error(err) {}
            float accel_x;
            float accel_y;
            float accel_z;
            std::error_code error;

        };

        virtual AccelerationResult GetAccelerationResult() const = 0;

        struct GyroResult {
            GyroResult(float gx, float gy, float gz)
                : gyro_x(gx), gyro_y(gy), gyro_z(gz) {}
            explicit GyroResult(std::error_code err)
                : gyro_x(0), gyro_y(0), gyro_z(0), error(err) {}
            float gyro_x;
            float gyro_y;
            float gyro_z;
            std::error_code error;

        };

        virtual GyroResult GetGyroResult() const = 0;

        virtual void getAres() const = 0;
        virtual void getGres() const = 0;

};

#endif  // INCLUDE_MPU9250_INTERFACE_H_
