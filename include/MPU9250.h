/*------------------------------------------------------------------------------
* Copyright © Tyler Barkin – All Rights Reserved
* Proprietary and Confidential
* Copying of this file or use of code contained in this file via any
* medium is strictly prohibited unless prior written permission is obtained
* from Tyler Barkin, Inc.
* Created by Tyler Barkin 2018
------------------------------------------------------------------------------*/
#ifndef INCLUDE_MPU9250_H_
#define INCLUDE_MPU9250_H_

#include "include/MPU9250_interface.h"
#include "quaternion_filter.h"
//-----------------------------------------------------------------------------
class II2C;

//-----------------------------------------------------------------------------
#define MAX_COMPASS_SAMPLE_RATE (100)

enum Ascale {
    AFS_2G                          = (0<<3),
    AFS_4G                          = (1<<3),
    AFS_8G                          = (2<<3),
    AFS_16G                         = (3<<3),
};

enum Gscale {
    GFS_250DPS                      = (0<<3),
    GFS_500DPS                      = (1<<3),
    GFS_1000DPS                     = (2<<3),
    GFS_2000DPS                     = (3<<3),
};

enum LPFscale {
    INV_FILTER_256HZ_NOLPF2         = (0),
    INV_FILTER_188HZ                = (1),
    INV_FILTER_98HZ                 = (2),
    INV_FILTER_42HZ                 = (3),
    INV_FILTER_20HZ                 = (4),
    INV_FILTER_10HZ                 = (5),
    INV_FILTER_5HZ                  = (6),
    INV_FILTER_2100HZ_NOLPF         = (7)
};

class MPU9250 : public IMPU9250 {
 public:
    MPU9250(const II2C& i2c,
        uint8_t address = MPU9250_ADDRESS_AD0) :
    i2c_(i2c),
    device_address_(address),
    initialized_(false),
    ascale_(AFS_2G),
    gscale_(GFS_1000DPS),
    lpfscale_(INV_FILTER_42HZ),
    aRes(0),
    gRes(0) {}

    std::error_code Initialize() const;
    void SetupGyro(Gscale val) const;
    void SetupAccl(Ascale val) const;
    void SetupLPF(LPFscale val) const;
    void SetupSampleRate(uint16_t rate) const;
    // void SetupFIFO(uint8_t rate) const;
    void SetupCompass(void) const;
    void SetupCompassSampleRate(uint8_t magrate, uint16_t rate) const;
    void SetBypass(bool val) const;

    AccelerationResult GetAccelerationResult() const;
    GyroResult GetGyroResult() const;
    void getAres() const;
    void getGres() const;


 protected:
    const II2C& i2c_;
    const uint8_t device_address_;
    mutable bool initialized_;
    const Ascale ascale_;
    const Gscale gscale_;
    const LPFscale lpfscale_;

    mutable float aRes;
    mutable float gRes;
    
        // Maximum clock stretch is 24ms.  Use 30ms to give a 25% margin
    constexpr static uint8_t TIMEOUT_READ_WRITE_MS = 200;


    constexpr static uint8_t MPU9250_ADDRESS_AD0 = 0x68 << 1;  // Device address when ADO = 0

    constexpr static uint8_t SELF_TEST_X_GYRO = 0x00;
    constexpr static uint8_t SELF_TEST_Y_GYRO = 0x01;
    constexpr static uint8_t SELF_TEST_Z_GYRO = 0x02;

    // constexpr static uint8_t X_FINE_GAIN      = 0x03; // [7:0] fine gain
    // constexpr static uint8_t Y_FINE_GAIN      = 0x04;
    // constexpr static uint8_t Z_FINE_GAIN      = 0x05;
    // constexpr static uint8_t XA_OFFSET_H      = 0x06; // User-defined trim values for accelerometer
    // constexpr static uint8_t XA_OFFSET_L_TC   = 0x07;
    // constexpr static uint8_t YA_OFFSET_H      = 0x08;
    // constexpr static uint8_t YA_OFFSET_L_TC   = 0x09;
    // constexpr static uint8_t ZA_OFFSET_H      = 0x0A;
    // constexpr static uint8_t ZA_OFFSET_L_TC   = 0x0B;

    constexpr static uint8_t SELF_TEST_X_ACCEL = 0x0D;
    constexpr static uint8_t SELF_TEST_Y_ACCEL = 0x0E;
    constexpr static uint8_t SELF_TEST_Z_ACCEL = 0x0F;

    constexpr static uint8_t SELF_TEST_A       = 0x10;

    constexpr static uint8_t XG_OFFSET_H       = 0x13;  // User-defined trim values for gyroscope
    constexpr static uint8_t XG_OFFSET_L       = 0x14;
    constexpr static uint8_t YG_OFFSET_H       = 0x15;
    constexpr static uint8_t YG_OFFSET_L       = 0x16;
    constexpr static uint8_t ZG_OFFSET_H       = 0x17;
    constexpr static uint8_t ZG_OFFSET_L       = 0x18;
    constexpr static uint8_t SMPLRT_DIV        = 0x19;
    constexpr static uint8_t CONFIG            = 0x1A;
    constexpr static uint8_t GYRO_CONFIG       = 0x1B;
    constexpr static uint8_t ACCEL_CONFIG1     = 0x1C;
    constexpr static uint8_t ACCEL_CONFIG2     = 0x1D;
    constexpr static uint8_t LP_ACCEL_ODR      = 0x1E;
    constexpr static uint8_t WOM_THR           = 0x1F;

    // Duration counter threshold for motion interrupt generation, 1 kHz rate,
    // LSB = 1 ms
    constexpr static uint8_t MOT_DUR           = 0x20;
    // Zero-motion detection threshold bits [7:0]
    constexpr static uint8_t ZMOT_THR          = 0x21;
    // Duration counter threshold for zero motion interrupt generation, 16 Hz rate,
    // LSB = 64 ms
    constexpr static uint8_t ZRMOT_DUR         = 0x22;

    constexpr static uint8_t FIFO_EN            = 0x23;
    constexpr static uint8_t I2C_MST_CTRL       = 0x24;
    constexpr static uint8_t I2C_SLV0_ADDR      = 0x25;
    constexpr static uint8_t I2C_SLV0_REG       = 0x26;
    constexpr static uint8_t I2C_SLV0_CTRL      = 0x27;
    constexpr static uint8_t I2C_SLV1_ADDR      = 0x28;
    constexpr static uint8_t I2C_SLV1_REG       = 0x29;
    constexpr static uint8_t I2C_SLV1_CTRL      = 0x2A;
    constexpr static uint8_t I2C_SLV2_ADDR      = 0x2B;
    constexpr static uint8_t I2C_SLV2_REG       = 0x2C;
    constexpr static uint8_t I2C_SLV2_CTRL      = 0x2D;
    constexpr static uint8_t I2C_SLV3_ADDR      = 0x2E;
    constexpr static uint8_t I2C_SLV3_REG       = 0x2F;
    constexpr static uint8_t I2C_SLV3_CTRL      = 0x30;
    constexpr static uint8_t I2C_SLV4_ADDR      = 0x31;
    constexpr static uint8_t I2C_SLV4_REG       = 0x32;
    constexpr static uint8_t I2C_SLV4_DO        = 0x33;
    constexpr static uint8_t I2C_SLV4_CTRL      = 0x34;
    constexpr static uint8_t I2C_SLV4_DI        = 0x35;
    constexpr static uint8_t I2C_MST_STATUS     = 0x36;
    constexpr static uint8_t INT_PIN_CFG        = 0x37;
    constexpr static uint8_t INT_ENABLE         = 0x38;
    constexpr static uint8_t DMP_INT_STATUS     = 0x39;  // Check DMP interrupt
    constexpr static uint8_t INT_STATUS         = 0x3A;
    constexpr static uint8_t ACCEL_XOUT_H       = 0x3B;
    constexpr static uint8_t ACCEL_XOUT_L       = 0x3C;
    constexpr static uint8_t ACCEL_YOUT_H       = 0x3D;
    constexpr static uint8_t ACCEL_YOUT_L       = 0x3E;
    constexpr static uint8_t ACCEL_ZOUT_H       = 0x3F;
    constexpr static uint8_t ACCEL_ZOUT_L       = 0x40;
    constexpr static uint8_t TEMP_OUT_H         = 0x41;
    constexpr static uint8_t TEMP_OUT_L         = 0x42;
    constexpr static uint8_t GYRO_XOUT_H        = 0x43;
    constexpr static uint8_t GYRO_XOUT_L        = 0x44;
    constexpr static uint8_t GYRO_YOUT_H        = 0x45;
    constexpr static uint8_t GYRO_YOUT_L        = 0x46;
    constexpr static uint8_t GYRO_ZOUT_H        = 0x47;
    constexpr static uint8_t GYRO_ZOUT_L        = 0x48;
    constexpr static uint8_t EXT_SENS_DATA_00   = 0x49;
    constexpr static uint8_t EXT_SENS_DATA_01   = 0x4A;
    constexpr static uint8_t EXT_SENS_DATA_02   = 0x4B;
    constexpr static uint8_t EXT_SENS_DATA_03   = 0x4C;
    constexpr static uint8_t EXT_SENS_DATA_04   = 0x4D;
    constexpr static uint8_t EXT_SENS_DATA_05   = 0x4E;
    constexpr static uint8_t EXT_SENS_DATA_06   = 0x4F;
    constexpr static uint8_t EXT_SENS_DATA_07   = 0x50;
    constexpr static uint8_t EXT_SENS_DATA_08   = 0x51;
    constexpr static uint8_t EXT_SENS_DATA_09   = 0x52;
    constexpr static uint8_t EXT_SENS_DATA_10   = 0x53;
    constexpr static uint8_t EXT_SENS_DATA_11   = 0x54;
    constexpr static uint8_t EXT_SENS_DATA_12   = 0x55;
    constexpr static uint8_t EXT_SENS_DATA_13   = 0x56;
    constexpr static uint8_t EXT_SENS_DATA_14   = 0x57;
    constexpr static uint8_t EXT_SENS_DATA_15   = 0x58;
    constexpr static uint8_t EXT_SENS_DATA_16   = 0x59;
    constexpr static uint8_t EXT_SENS_DATA_17   = 0x5A;
    constexpr static uint8_t EXT_SENS_DATA_18   = 0x5B;
    constexpr static uint8_t EXT_SENS_DATA_19   = 0x5C;
    constexpr static uint8_t EXT_SENS_DATA_20   = 0x5D;
    constexpr static uint8_t EXT_SENS_DATA_21   = 0x5E;
    constexpr static uint8_t EXT_SENS_DATA_22   = 0x5F;
    constexpr static uint8_t EXT_SENS_DATA_23   = 0x60;
    constexpr static uint8_t MOT_DETECT_STATUS  = 0x61;
    constexpr static uint8_t I2C_SLV0_DO        = 0x63;
    constexpr static uint8_t I2C_SLV1_DO        = 0x64;
    constexpr static uint8_t I2C_SLV2_DO        = 0x65;
    constexpr static uint8_t I2C_SLV3_DO        = 0x66;
    constexpr static uint8_t I2C_MST_DELAY_CTRL = 0x67;
    constexpr static uint8_t SIGNAL_PATH_RESET  = 0x68;
    constexpr static uint8_t MOT_DETECT_CTRL    = 0x69;
    constexpr static uint8_t USER_CTRL          = 0x6A;  // Bit 7 enable DMP, bit 3 reset DMP
    constexpr static uint8_t PWR_MGMT_1         = 0x6B; // Device defaults to the SLEEP mode
    constexpr static uint8_t PWR_MGMT_2         = 0x6C;
    constexpr static uint8_t DMP_BANK           = 0x6D;  // Activates a specific bank in the DMP
    constexpr static uint8_t DMP_RW_PNT         = 0x6E;  // Set read/write pointer to a specific start address in specified DMP bank
    constexpr static uint8_t DMP_REG            = 0x6F;  // Register in DMP from which to read or to which to write
    constexpr static uint8_t DMP_REG_1          = 0x70;
    constexpr static uint8_t DMP_REG_2          = 0x71;
    constexpr static uint8_t FIFO_COUNTH        = 0x72;
    constexpr static uint8_t FIFO_COUNTL        = 0x73;
    constexpr static uint8_t FIFO_R_W           = 0x74;
    constexpr static uint8_t WHO_AM_I_MPU9250   = 0x75; // Should return = 0x71
    constexpr static uint8_t XA_OFFSET_H        = 0x77;
    constexpr static uint8_t XA_OFFSET_L        = 0x78;
    constexpr static uint8_t YA_OFFSET_H        = 0x7A;
    constexpr static uint8_t YA_OFFSET_L        = 0x7B;
    constexpr static uint8_t ZA_OFFSET_H        = 0x7D;
    constexpr static uint8_t ZA_OFFSET_L        = 0x7E;



};

#endif  // INCLUDE_MPU9250_H_
