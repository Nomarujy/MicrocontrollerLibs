#pragma once

#include <cstdint>

#ifdef TestMethods
int32_t CalculateTfine(const int32_t tempMeasurement, const int16_t* trimmingValues);
int32_t CalculateTemp(const int32_t t_fine);
uint32_t CalculatePresure(const int64_t t_fine, const int64_t presureMeasurement, const int16_t* trimmingValues);
#endif