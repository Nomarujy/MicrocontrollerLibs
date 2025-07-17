#pragma once

#include <cstdint>

#ifdef DEBUG
int32_t CalculateTfine(const int32_t tempMeasurement, const int16_t* trimmingValues);
int32_t CalculateTemp(const int32_t t_fine);
#endif