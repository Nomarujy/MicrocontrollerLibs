#include "BMP280Lib.h"

enum TrimmingNames {
    dig_T1 = 0,
    dig_T2,
    dig_T3,
    dig_P1,
    dig_P2,
    dig_P3,
    dig_P4,
    dig_P5,
    dig_P6,
    dig_P7,
    dig_P8,
    dig_P9,
};

int32_t CalculateTfine(const int32_t tempMeasurement, const int16_t* trimmingValues)
{
    int32_t var1, var2,
    dig_T1 = (uint16_t)trimmingValues[TrimmingNames::dig_T1],
    dig_T2 = trimmingValues[TrimmingNames::dig_T2],
    dig_T3 = trimmingValues[TrimmingNames::dig_T3];

    var1 = (((tempMeasurement >> 3) - (dig_T1 << 1)) * dig_T2) >> 11;
    var2 = (tempMeasurement >> 4) - dig_T1;
    var2 = ((var2 * var2) >> 12) * dig_T3 >> 14;

    return var1 + var2;
}

// Returns temperature in DegC, resolution is 0.01 DegC. Output value of “5123” equals 51.23 DegC.
// t_fine carries fine temperature as global value
int32_t CalculateTemp(const int32_t t_fine)
{
    return (t_fine * 5 + 128) >> 8;
}

// Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8 fractional bits).
// Output value of “24674867” represents 24674867/256 = 96386.2 Pa = 963.862 hPa
uint32_t CalculatePresure(const int64_t t_fine, const int64_t presureMeasurement, const int16_t* trimmingValues)
{
    int64_t var1, var2, p,
    dig_P1 = (uint16_t)trimmingValues[TrimmingNames::dig_P1],
    dig_P2 = trimmingValues[TrimmingNames::dig_P2],
    dig_P3 = trimmingValues[TrimmingNames::dig_P3],
    dig_P4 = trimmingValues[TrimmingNames::dig_P4],
    dig_P5 = trimmingValues[TrimmingNames::dig_P5],
    dig_P6 = trimmingValues[TrimmingNames::dig_P6],
    dig_P7 = trimmingValues[TrimmingNames::dig_P7],
    dig_P8 = trimmingValues[TrimmingNames::dig_P8],
    dig_P9 = trimmingValues[TrimmingNames::dig_P9];

    var1 = t_fine - 128000;
    var2 = var1 * var1 * dig_P6;
    var2 = var2 + ((var1 * dig_P5) << 17);
    var2 = var2 + (dig_P4 << 35);
    var1 = ((var1 * var1 * dig_P3) >> 8) + ((var1 * dig_P2) << 12);
    var1 = ((((int64_t)1) << 47) + var1) * dig_P1 >> 33;

    if (var1 == 0)
    {
        return 0;  // avoid exception caused by division by zero
    }

    p = 1048576 - presureMeasurement;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (dig_P9 * (p >> 13) * (p >> 13)) >> 25;
    var2 = (dig_P8 * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (dig_P7 << 4);

    return (uint32_t)p;
}

uint32_t ConvertToPA(const int64_t presure)
{
    return presure / 256;
}