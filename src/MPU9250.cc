/*------------------------------------------------------------------------------
* Copyright © Tyler Barkin – All Rights Reserved
* Proprietary and Confidential
* Copying of this file or use of code contained in this file via any
* medium is strictly prohibited unless prior written permission is obtained
* from Tyler Barkin, Inc.
* Created by Tyler Barkin 2018
------------------------------------------------------------------------------*/

#include "include/MPU9250.h"
#include "include/i2c_interface.h"
#include "include/error_categories.h"

std::error_code MPU9250::Initialize() const {
    if (initialized_)
        return std::error_code();

    auto error = i2c_.Initialize();
    if (error)
        return error;

    
    char write[] = {
            0x00,
            0x6B
    };
    i2c_.Write(device_address_,boost::asio::buffer(write),MPU9250::TIMEOUT_READ_WRITE_MS);
    HAL_Delay(100);

    write[0] = 0x01;
    i2c_.Write(device_address_,boost::asio::buffer(write),MPU9250::TIMEOUT_READ_WRITE_MS);
    HAL_Delay(100);

    write[0] = 0x03;
    write[1] = 0x1A;
    i2c_.Write(device_address_,boost::asio::buffer(write),MPU9250::TIMEOUT_READ_WRITE_MS);
    HAL_Delay(100);

    write[0] = 0x04;
    write[1] = 0x19;
    i2c_.Write(device_address_,boost::asio::buffer(write),MPU9250::TIMEOUT_READ_WRITE_MS);
    HAL_Delay(100);


    uint16_t ct[1];
    uint8_t c;
    error = i2c_.Read(device_address_,
                             MPU9250::GYRO_CONFIG,
                             boost::asio::buffer(ct),
                             MPU9250::TIMEOUT_READ_WRITE_MS);
    if (error)
        return (error);
    c = ct[0] & 0xFF;
    c = c & ~0x02; // Clear Fchoice bits [1:0]
    c = c & ~0x18; // Clear AFS bits [4:3]
    c = c | gscale_ << 3; // Set full scale range for the gyro
    write[0] = MPU9250::GYRO_CONFIG;
    write[1] = c;
    i2c_.Write(device_address_,boost::asio::buffer(write),MPU9250::TIMEOUT_READ_WRITE_MS);

    error = i2c_.Read(device_address_,
                             MPU9250::ACCEL_CONFIG1,
                             boost::asio::buffer(ct),
                             MPU9250::TIMEOUT_READ_WRITE_MS);
    if (error)
        return (error);
    c = ct[0] & 0xFF;
    c = c & ~0x18;  // Clear AFS bits [4:3]
    c = c | ascale_ << 3; // Set full scale range for the accelerometer
    write[0] = MPU9250::ACCEL_CONFIG1;
    write[1] = c;
    i2c_.Write(device_address_,boost::asio::buffer(write),MPU9250::TIMEOUT_READ_WRITE_MS);


    error = i2c_.Read(device_address_,
                             MPU9250::ACCEL_CONFIG2,
                             boost::asio::buffer(ct),
                             MPU9250::TIMEOUT_READ_WRITE_MS);
    if (error)
        return (error);
    c = ct[0] & 0xFF;
    c = c & ~0x0F; // Clear accel_fchoice_b (bit 3) and A_DLPFG (bits [2:0])
    c = c | ascale_ << 3; // Set full scale range for the accelerometer
    c = c | 0x03;  // Set accelerometer rate to 1 kHz and bandwidth to 41 Hz
    write[0] = MPU9250::ACCEL_CONFIG2;
    write[1] = c;
    i2c_.Write(device_address_,boost::asio::buffer(write),MPU9250::TIMEOUT_READ_WRITE_MS);

    initialized_ = true;
    return std::error_code();
}


//-----------------------------------------------------------------------------
void MPU9250::getAres() const {
  switch (ascale_)
  {
    // Possible accelerometer scales (and their register bit settings) are:
    // 2 Gs (00), 4 Gs (01), 8 Gs (10), and 16 Gs  (11).
    // Here's a bit of an algorith to calculate DPS/(ADC tick) based on that
    // 2-bit value:
    case AFS_2G:
      aRes = 2.0f / 32768.0f;
      break;
    case AFS_4G:
      aRes = 4.0f / 32768.0f;
      break;
    case AFS_8G:
      aRes = 8.0f / 32768.0f;
      break;
    case AFS_16G:
      aRes = 16.0f / 32768.0f;
      break;
  }
}
//-----------------------------------------------------------------------------

void MPU9250::getGres() const {
  switch(gscale_)
  {
    // Possible gyro scales (and their register bit settings) are:
    // 250 DPS (00), 500 DPS (01), 1000 DPS (10), and 2000 DPS (11).
    // Here's a bit of an algorith to calculate DPS/(ADC tick) based on that
    // 2-bit value:
    case GFS_250DPS:
      gRes = 250.0f / 32768.0f;
      break;
    case GFS_500DPS:
      gRes = 500.0f / 32768.0f;
      break;
    case GFS_1000DPS:
      gRes = 1000.0f / 32768.0f;
      break;
    case GFS_2000DPS:
      gRes = 2000.0f / 32768.0f;
      break;
  }
}

//-----------------------------------------------------------------------------
IMPU9250::AccelerationResult MPU9250::GetAccelerationResult() const {
    if (!initialized_)
        return AccelerationResult(IMUError::UNINITIALIZED);

    // The read is 16 bits
    uint16_t buffer[3];

    auto error = i2c_.Read(device_address_,
                             MPU9250::ACCEL_XOUT_H,
                             boost::asio::buffer(buffer),
                             MPU9250::TIMEOUT_READ_WRITE_MS);
    if (error)
        return AccelerationResult(error);

    int16_t buffer_signed[3];
    buffer_signed[0] = (buffer[0]>>8) | (buffer[0]<<8);
    buffer_signed[1] = (buffer[1]>>8) | (buffer[1]<<8);
    buffer_signed[2] = (buffer[2]>>8) | (buffer[2]<<8);
    return AccelerationResult( buffer_signed[0]*aRes, buffer_signed[1]*aRes,  buffer_signed[2]*aRes);
}

IMPU9250::GyroResult MPU9250::GetGyroResult() const {
    if (!initialized_)
        return GyroResult(IMUError::UNINITIALIZED);

    // The read is 16 bits
    uint16_t buffer[3];

    auto error = i2c_.Read(device_address_,
                             MPU9250::GYRO_XOUT_H,
                             boost::asio::buffer(buffer),
                             MPU9250::TIMEOUT_READ_WRITE_MS);
    if (error)
        return GyroResult(error);
    int16_t buffer_signed[3];
    buffer_signed[0] = (buffer[0]>>8) | (buffer[0]<<8);
    buffer_signed[1] = (buffer[1]>>8) | (buffer[1]<<8);
    buffer_signed[2] = (buffer[2]>>8) | (buffer[2]<<8);
    return GyroResult( buffer_signed[0]*gRes, buffer_signed[1]*gRes,  buffer_signed[2]*gRes);
}


