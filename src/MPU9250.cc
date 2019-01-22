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

    /* Reset device. */
    uint8_t write[] = {
            0x80,
            PWR_MGMT_1
    };
    error = i2c_.Write(device_address_,boost::asio::buffer(write),MPU9250::TIMEOUT_READ_WRITE_MS);
    HAL_Delay(100);
    /* Wake up chip. */
    write[0] = 0x00;
    error = i2c_.Write(device_address_,boost::asio::buffer(write),MPU9250::TIMEOUT_READ_WRITE_MS);
    HAL_Delay(100);

    SetupGyro(gscale_);
    SetupAccl(ascale_);
    SetupLPF(lpfscale_);
    SetupSampleRate(500);
    // SetupFIFO();
    SetupCompass();
    // SetupCompassSampleRate(50, 500);
    

    initialized_ = true;
    return std::error_code();
}

void MPU9250::SetupGyro(Gscale val) const {
  uint8_t data[] = {
            GYRO_CONFIG,
            val
  };
  
  i2c_.Write(device_address_,boost::asio::buffer(data),MPU9250::TIMEOUT_READ_WRITE_MS);

  /* Checking the read write order */
  // uint8_t ct[1];
  // i2c_.Read(device_address_,
  //   MPU9250::GYRO_CONFIG,
  //   boost::asio::buffer(ct),
  //   MPU9250::TIMEOUT_READ_WRITE_MS);

  // c = ct[0] & 0xFF;
  // c = c & ~0x02; // Clear Fchoice bits [1:0]
  // c = c & ~0x18; // Clear AFS bits [4:3]
  // c = c | gscale_ << 3; // Set full scale range for the gyro
  // write[0] = c;
  // write[1] = MPU9250::GYRO_CONFIG;
  // i2c_.Write(device_address_,boost::asio::buffer(write),MPU9250::TIMEOUT_READ_WRITE_MS);
}

void MPU9250::SetupAccl(Ascale val) const {
  uint8_t data[] = {
    ACCEL_CONFIG1,
    val
  };
  
  i2c_.Write(device_address_,boost::asio::buffer(data),MPU9250::TIMEOUT_READ_WRITE_MS);

}

void MPU9250::SetupLPF(LPFscale val) const {
  uint8_t data[] = {
    CONFIG,
    val
            
  };
  
  i2c_.Write(device_address_,boost::asio::buffer(data),MPU9250::TIMEOUT_READ_WRITE_MS);

}

/**
 *  @brief      Set sampling rate.
 *  Sampling rate must be between 4Hz and 1kHz.
 *  @param[in]  rate    Desired sampling rate (Hz).
 */
void MPU9250::SetupSampleRate(uint16_t rate) const {
  if (rate < 4){
    rate = 4;
  }
  else if (rate > 1000) {
    rate = 1000;
  }
  uint8_t div = 1000 / rate - 1;
  uint8_t data[] = {
    SMPLRT_DIV,
    div
            
  };
  
  i2c_.Write(device_address_,boost::asio::buffer(data),MPU9250::TIMEOUT_READ_WRITE_MS);
  
}

// void MPU9250::SetupFIFO(LPFscale val) const {
//   uint8_t data[] = {
//             val,
//             SMPLRT_DIV
//   };
  
//   i2c_.Write(device_address_,boost::asio::buffer(data),MPU9250::TIMEOUT_READ_WRITE_MS);

// }

void MPU9250::SetupCompass(void) const {
  // uint8_t AK8963_CNTL                 = 0x0A;
  // uint8_t AK8963_POWER_DOWN           = 0x00;
  // uint8_t AK8963_FUSE_ROM_ACCESS      = 0x0F;

  // uint8_t akm_addr = 0x0C<<1;
  MPU9250::SetBypass(true);
// 
  // // Power Down Magnometer
  // uint8_t data[] = {
  //           AK8963_CNTL,
  //           AK8963_POWER_DOWN
  // };
  // i2c_.Write(akm_addr,boost::asio::buffer(data),MPU9250::TIMEOUT_READ_WRITE_MS);
  // HAL_Delay(1);
  // // Fuse Rom Access
  // data[0] = AK8963_CNTL;
  // data[1] = AK8963_FUSE_ROM_ACCESS;
  // i2c_.Write(akm_addr,boost::asio::buffer(data),MPU9250::TIMEOUT_READ_WRITE_MS);
  // HAL_Delay(1);





  /* Find compass. Possible addresses range from 0x0C to 0x0F. */
  // uint8_t tmp[1];
  // for (akm_addr = 0x01<<1; akm_addr <= 0xEF<<1; akm_addr++) {
  //   auto error = i2c_.Read(akm_addr,
  //     0x00,
  //     boost::asio::buffer(tmp),
  //     MPU9250::TIMEOUT_READ_WRITE_MS);
  //   if(error) {
  //     break;
  //   }
  // }
  

}


// void MPU9250::SetupCompassSampleRate(uint8_t magrate, uint16_t rate) const {
//   uint8_t div = 0;
//   if (!magrate || magrate > rate || magrate > MAX_COMPASS_SAMPLE_RATE){
//   } else {
//     div = rate / magrate - 1;
//   }
//   uint8_t data[] = {
//     I2C_SLV4_CTRL,
//     div
            
//   };
  
//   i2c_.Write(device_address_,boost::asio::buffer(data),MPU9250::TIMEOUT_READ_WRITE_MS);

// }

void MPU9250::SetBypass(bool val) const {
  uint8_t tmp[1];
  i2c_.Read(device_address_,
    MPU9250::USER_CTRL,
    boost::asio::buffer(tmp),
    MPU9250::TIMEOUT_READ_WRITE_MS);

  
  uint8_t data[] = {
    USER_CTRL,
    tmp[0] &= ~0x20
            
  };
  
  i2c_.Write(device_address_,boost::asio::buffer(data),MPU9250::TIMEOUT_READ_WRITE_MS);

  HAL_Delay(3);

  data[0] = INT_PIN_CFG;
  data[1] = 0x02;
  i2c_.Write(device_address_,boost::asio::buffer(data),MPU9250::TIMEOUT_READ_WRITE_MS);
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


