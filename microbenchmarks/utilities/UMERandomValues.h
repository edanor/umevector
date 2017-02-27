#pragma once
// Randomization routines for random-generated tests.
template<typename SCALAR_TYPE>
SCALAR_TYPE randomValue(std::mt19937 & generator) {
    std::uniform_int_distribution<SCALAR_TYPE> dist(std::numeric_limits<SCALAR_TYPE>::min(), std::numeric_limits<SCALAR_TYPE>::max());
    return dist(generator);
}

template<>
uint8_t randomValue<uint8_t>(std::mt19937 & generator) {
    std::uniform_int_distribution<uint16_t> dist(0, 255);
    return uint8_t(dist(generator));
}

template<>
int8_t randomValue<int8_t>(std::mt19937 & generator) {
    int16_t min = int16_t(std::numeric_limits<int8_t>::min());
    int16_t max = int16_t(std::numeric_limits<int8_t>::max());

    std::uniform_int_distribution<int16_t> dist(min, max);
    int16_t t0 = dist(generator);
    return int8_t(t0);
}

template<>
float randomValue<float>(std::mt19937 & generator) {
    std::uniform_real_distribution<float> dist(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
    return dist(generator);
}

template<>
double randomValue<double>(std::mt19937 & generator) {
    std::uniform_real_distribution<double> dist(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());
    return dist(generator);
}

template<>
bool randomValue<bool>(std::mt19937 & generator) {
    std::uniform_int_distribution<int32_t> dist(std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max());
    int32_t t0 = dist(generator);
    return t0 > 0;
}