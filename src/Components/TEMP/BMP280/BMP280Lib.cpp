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
    int32_t var1, var2;

    var1 = (((tempMeasurement >> 3) - ((int32_t)trimmingValues[TrimmingNames::dig_T1] << 1)) * ((int32_t)trimmingValues[TrimmingNames::dig_T2])) >> 11;
    var2 = (tempMeasurement >> 4) - ((int32_t)trimmingValues[TrimmingNames::dig_T1]);
    var2 = ((var2 * var2) >> 12) * ((int32_t)trimmingValues[TrimmingNames::dig_T3]) >> 14;

    return var1 + var2;
}

int32_t CalculateTemp(const int32_t t_fine)
{
    return (t_fine * 5 + 128) >> 8;
}