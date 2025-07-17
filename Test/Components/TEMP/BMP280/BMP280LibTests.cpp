#include <cstdint>
#include "gtest/gtest.h"
#include "Components/TEMP/BMP280/BMP280Lib.h"


const int16_t trimmingValues[] = { 27504, 26435, -1000, (int16_t)36477, -10685, 3024, 2855, 140, -7, 15500, -14600, 6000};
const int32_t tempMeasurement = 519888;
const int32_t presureMeasurement = 415148;

const int32_t expected_t_fine = 128422;

TEST(BMP280, t_fine)
{
    int32_t t_fine = CalculateTfine(tempMeasurement, trimmingValues);

    ASSERT_EQ(expected_t_fine, t_fine);
}

const int32_t expected_temp = 2508;
TEST(BMP280, temp)
{
    int32_t tFine = CalculateTfine(tempMeasurement, trimmingValues);
    int32_t temp = CalculateTemp(tFine);

    ASSERT_EQ(expected_temp, temp);
}