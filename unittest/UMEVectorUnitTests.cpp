// The MIT License (MIT)
//
// Copyright (c) 2016-2017 CERN
//
// Author: Przemyslaw Karpinski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//
//  This piece of code was developed as part of ICE-DIP project at CERN.
//  "ICE-DIP is a European Industrial Doctorate project funded by the European Community's
//  7th Framework programme Marie Curie Actions under grant PITN-GA-2012-316596".
//

#include <iostream>

#include <random>

#include "../UMEVector.h"

extern int g_totalTests;
extern int g_totalFailed;
extern int g_testMaxId;
extern int g_failCount;
extern bool g_allSuccess;
extern bool g_supressMessages;
extern char *g_test_header_ptr;

#define INIT_TEST(test_header_ptr, supressMesages) { \
    g_test_header_ptr = (test_header_ptr); \
    g_failCount = 0; \
    g_testMaxId = 0; \
    g_allSuccess = true; \
    g_supressMessages = supressMesages;}

#define SUPRESS_MESSAGES() { g_supressMessages = true; }
#define CHECK_CONDITION(cond, msg) \
    g_totalTests++; \
    g_testMaxId++; \
    if(!(cond)){\
        if(g_supressMessages == false) std::cout << "FAIL " << g_test_header_ptr << " Id: " << g_testMaxId << " - " << (msg) << std::endl; \
        g_totalFailed++; \
        g_failCount++; \
        g_allSuccess = false; \
    } \
    else \
    { \
        if(g_supressMessages == false) std::cout << "OK   " << g_test_header_ptr << " Id: " << g_testMaxId << " - " << (msg) << std::endl;  \
    }

void check_condition(bool cond, std::string msg);

#define PRINT_MESSAGE(msg) if(g_supressMessages == false) std::cout << g_test_header_ptr <<  msg << std::endl;

// This PI value is used over all unit tests. Defining it here makes it is 
// possible to use different values in real codes.
#define UME_PI_D 3.141592653589793238462643383279502884197VEC_LEN93993751058209749445923078VEC_LEN4062
#define UME_2PI_D (2.0*UME_PI_D)
#define UME_PI_F float(UME_PI_D)
#define UME_2PI_F (2.0f*UME_PI_F)

bool valueInRange(float value, float expectedValue, float errMargin);
bool valueInRange(double value, double expectedValue, double errMargin);
bool valueInRange(uint32_t value, uint32_t expectedValue, float errMargin);
bool valueInRange(int32_t value, int32_t expectedValue, float errMargin);
bool valueInRange(uint64_t value, uint64_t expectedValue, float errMargin);
bool valueInRange(int64_t value, int64_t expectedValue, float errMargin);
bool valueInRange(bool value, bool expectedValue, float errMargin);

bool valuesExact(uint8_t const *values, uint8_t const *expectedValues, unsigned int count);
bool valuesExact(int8_t const *values, int8_t const *expectedValues, unsigned int count);
bool valuesExact(uint16_t const *values, uint16_t const *expectedValues, unsigned int count);
bool valuesExact(int16_t const *values, int16_t const *expectedValues, unsigned int count);
bool valuesExact(int32_t const *values, int32_t const *expectedValues, unsigned int count);
bool valuesExact(uint32_t const *values, uint32_t const *expectedValues, unsigned int count);
bool valuesExact(int64_t const *values, int64_t const *expectedValues, unsigned int count);
bool valuesExact(uint64_t const *values, uint64_t const *expectedValues, unsigned int count);
bool valuesExact(bool const *values, bool const *expectedValues, unsigned int count);
bool valuesInRange(float const *values, float const *expectedValues, unsigned int count, float errMargin);
bool valuesInRange(double const *values, double const *expectedValues, unsigned int count, double errMargin);

// This is a dirty hack to use the same testing function for both int and float types... 
bool valuesInRange(uint8_t const *values, uint8_t const *expectedValues, unsigned int count, double errMargin);
bool valuesInRange(int8_t const *values, int8_t const *expectedValues, unsigned int count, double errMargin);
bool valuesInRange(uint16_t const *values, uint16_t const *expectedValues, unsigned int count, double errMargin);
bool valuesInRange(int16_t const *values, int16_t const *expectedValues, unsigned int count, double errMargin);
bool valuesInRange(uint32_t const *values, uint32_t const *expectedValues, unsigned int count, double errMargin);
bool valuesInRange(uint64_t const *values, uint64_t const *expectedValues, unsigned int count, double errMargin);
bool valuesInRange(int32_t const *values, int32_t const *expectedValues, unsigned int count, double errMargin);
bool valuesInRange(int64_t const *values, int64_t const *expectedValues, unsigned int count, double errMargin);
bool valuesInRange(bool const *values, bool const *expectedValues, unsigned int count, double errMargin);

// Randomization routines for random-generated tests.
template<typename SCALAR_TYPE>
SCALAR_TYPE randomValue(std::mt19937 & generator) {
    std::uniform_int_distribution<SCALAR_TYPE> dist(std::numeric_limits<SCALAR_TYPE>::min(), std::numeric_limits<SCALAR_TYPE>::max());
    return dist(generator);
}

template<> uint8_t randomValue<uint8_t>(std::mt19937 & generator);
template<> int8_t randomValue<int8_t>(std::mt19937 & generator);
template<> float randomValue<float>(std::mt19937 & generator);
template<> double randomValue<double>(std::mt19937 & generator);
template<> bool randomValue<bool>(std::mt19937 & generator);


int g_totalTests = 0;
int g_totalFailed = 0;
int g_testMaxId = 0;
int g_failCount = 0;
bool g_allSuccess = true;
bool g_supressMessages = false;
char *g_test_header_ptr = NULL;

void check_condition(bool cond, std::string msg) {
    g_totalTests++;
    g_testMaxId++;
    if (!(cond)) {
        if (g_supressMessages == false) {
            std::cout << "FAIL " << g_test_header_ptr << " Id: " << g_testMaxId << " - " << (msg.c_str()) << std::endl;
        }
        g_totalFailed++;
        g_failCount++;
        g_allSuccess = false;
    }
    else
    {
        if (g_supressMessages == false) {
            std::cout << "OK   " << g_test_header_ptr << " Id: " << g_testMaxId << " - " << (msg.c_str()) << std::endl;
        }
    }
}

bool valueInRange(float value, float expectedValue, float errMargin) {

    if (expectedValue == 0.0f)
    {
        return (errMargin >= value) & ((-errMargin) <= value);
    }
    else if (value > 0.0f)
    {
        return ((expectedValue)*(1.0f + errMargin) >= value)
            & ((expectedValue)*(1.0f - errMargin) <= value);
    }
    else
    {
        return ((expectedValue)*(1.0f + errMargin) <= value)
            & ((expectedValue)*(1.0f - errMargin) >= value);
    }
}

bool valueInRange(double value, double expectedValue, double errMargin) {
    if (expectedValue == 0.0)
    {
        return (errMargin >= value) & ((-errMargin) <= value);
    }
    else if (value > 0.0f)
    {
        return ((expectedValue)*(1.0f + errMargin) >= value)
            & ((expectedValue)*(1.0f - errMargin) <= value);
    }
    else
    {
        return ((expectedValue)*(1.0f + errMargin) <= value)
            & ((expectedValue)*(1.0f - errMargin) >= value);
    }
}

bool valueInRange(bool value, bool expectedValue, float errMargin) {
    return value == expectedValue;
}

bool valueInRange(uint32_t value, uint32_t expectedValue, float errMargin) {
    return valueInRange((float)value, (float)expectedValue, errMargin);
}

bool valueInRange(int32_t value, int32_t expectedValue, float errMargin) {
    return valueInRange((float)value, (float)expectedValue, errMargin);
}

bool valueInRange(uint64_t value, uint64_t expectedValue, float errMargin) {
    return valueInRange((float)value, (float)expectedValue, errMargin);
}

bool valueInRange(int64_t value, int64_t expectedValue, float errMargin) {
    return valueInRange((float)value, (float)expectedValue, errMargin);
}

bool valuesExact(uint8_t const *values, uint8_t const *expectedValues, unsigned int count)
{
    bool retval = true;
    for (unsigned int i = 0; i < count; i++) {
        if (values[i] != expectedValues[i])
        {
            retval = false;
            break;
        }
    }
    return retval;
}

bool valuesExact(int8_t const *values, int8_t const *expectedValues, unsigned int count)
{
    bool retval = true;
    for (unsigned int i = 0; i < count; i++) {
        if (values[i] != expectedValues[i])
        {
            retval = false;
            break;
        }
    }
    return retval;
}

bool valuesExact(uint16_t const *values, uint16_t const *expectedValues, unsigned int count)
{
    bool retval = true;
    for (unsigned int i = 0; i < count; i++) {
        if (values[i] != expectedValues[i])
        {
            retval = false;
            break;
        }
    }
    return retval;
}

bool valuesExact(int16_t const *values, int16_t const *expectedValues, unsigned int count)
{
    bool retval = true;
    for (unsigned int i = 0; i < count; i++) {
        if (values[i] != expectedValues[i])
        {
            retval = false;
            break;
        }
    }
    return retval;
}

bool valuesExact(int32_t const *values, int32_t const *expectedValues, unsigned int count)
{
    bool retval = true;
    for (unsigned int i = 0; i < count; i++) {
        if (values[i] != expectedValues[i])
        {
            retval = false;
            break;
        }
    }
    return retval;
}

bool valuesExact(uint32_t const *values, uint32_t const *expectedValues, unsigned int count)
{
    bool retval = true;
    for (unsigned int i = 0; i < count; i++) {
        if (values[i] != expectedValues[i])
        {
            retval = false;
            break;
        }
    }
    return retval;
}

bool valuesExact(int64_t const *values, int64_t const *expectedValues, unsigned int count)
{
    bool retval = true;
    for (unsigned int i = 0; i < count; i++) {
        if (values[i] != expectedValues[i])
        {
            retval = false;
            break;
        }
    }
    return retval;
}

bool valuesExact(uint64_t const *values, uint64_t const *expectedValues, unsigned int count)
{
    bool retval = true;
    for (unsigned int i = 0; i < count; i++) {
        if (values[i] != expectedValues[i])
        {
            retval = false;
            break;
        }
    }
    return retval;
}

bool valuesExact(bool const *values, bool const *expectedValues, unsigned int count)
{
    bool retval = true;
    for (unsigned int i = 0; i < count; i++) {
        if (values[i] != expectedValues[i])
        {
            retval = false;
            break;
        }
    }
    return retval;
}

bool valuesInRange(float const *values, float const *expectedValues, unsigned int count, float errMargin)
{
    bool retval = true;
    for (unsigned int i = 0; i < count; i++) {
        if (!valueInRange(values[i], expectedValues[i], errMargin))
        {
            retval = false;
            break;
        }
    }
    return retval;
}

bool valuesInRange(double const *values, double const *expectedValues, unsigned int count, double errMargin)
{
    bool retval = true;
    for (unsigned int i = 0; i < count; i++) {
        if (!valueInRange(values[i], expectedValues[i], errMargin))
        {
            retval = false;
            break;
        }
    }
    return retval;
}

// This is a dirty hack to use the same testing function for both int and float types... 
bool valuesInRange(bool const *values, bool const *expectedValues, unsigned int count, double errMargin)
{
    return valuesExact(values, expectedValues, count);
}

bool valuesInRange(uint8_t const *values, uint8_t const *expectedValues, unsigned int count, double errMargin)
{
    return valuesExact(values, expectedValues, count);
}

bool valuesInRange(int8_t const *values, int8_t const *expectedValues, unsigned int count, double errMargin)
{
    return valuesExact(values, expectedValues, count);
}

bool valuesInRange(uint16_t const *values, uint16_t const *expectedValues, unsigned int count, double errMargin)
{
    return valuesExact(values, expectedValues, count);
}

bool valuesInRange(int16_t const *values, int16_t const *expectedValues, unsigned int count, double errMargin)
{
    return valuesExact(values, expectedValues, count);
}

bool valuesInRange(uint32_t const *values, uint32_t const *expectedValues, unsigned int count, double errMargin)
{
    return valuesExact(values, expectedValues, count);
}

bool valuesInRange(uint64_t const *values, uint64_t const *expectedValues, unsigned int count, double errMargin)
{
    return valuesExact(values, expectedValues, count);
}

bool valuesInRange(int32_t const *values, int32_t const *expectedValues, unsigned int count, double errMargin)
{
    return valuesExact(values, expectedValues, count);
}

bool valuesInRange(int64_t const *values, int64_t const *expectedValues, unsigned int count, double errMargin)
{
    return valuesExact(values, expectedValues, count);
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
    //std::uniform_real_distribution<float> dist(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
    std::uniform_real_distribution<float> dist(-5.0f, 5.0f);
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

template<typename MASK_TYPE, int VEC_LEN, int SIMD_STRIDE>
void testLAND_random_static()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    {
        bool raw_a[VEC_LEN];
        bool raw_b[VEC_LEN];
        bool result[VEC_LEN];
        bool raw_c[VEC_LEN];

        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<bool>(gen);
            raw_b[i] = randomValue<bool>(gen);
            result[i] = raw_a[i] && raw_b[i];
        }

        MASK_TYPE A(raw_a);
        MASK_TYPE B(raw_b);
        MASK_TYPE C(raw_c);

        C = A.land(B);

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("LANDV"));
    }
    {
        bool raw_a[VEC_LEN];
        bool raw_b[VEC_LEN];
        bool result[VEC_LEN];
        bool raw_c[VEC_LEN];

        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<bool>(gen);
            raw_b[i] = randomValue<bool>(gen);
            result[i] = raw_a[i] && raw_b[i];
        }

        MASK_TYPE A(raw_a);
        MASK_TYPE B(raw_b);
        MASK_TYPE C(raw_c);

        C = A && B;

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("LANDV(operator &&)"));
    }
}

template<typename MASK_TYPE, int VEC_LEN, int SIMD_STRIDE>
void testLOR_random_static()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    {
        bool raw_a[VEC_LEN];
        bool raw_b[VEC_LEN];
        bool result[VEC_LEN];
        bool raw_c[VEC_LEN];

        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<bool>(gen);
            raw_b[i] = randomValue<bool>(gen);
            result[i] = raw_a[i] || raw_b[i];
        }

        MASK_TYPE A(raw_a);
        MASK_TYPE B(raw_b);
        MASK_TYPE C(raw_c);

        C = A.lor(B);

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("LORV"));
    }
    {
        bool raw_a[VEC_LEN];
        bool raw_b[VEC_LEN];
        bool result[VEC_LEN];
        bool raw_c[VEC_LEN];

        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<bool>(gen);
            raw_b[i] = randomValue<bool>(gen);
            result[i] = raw_a[i] || raw_b[i];
        }

        MASK_TYPE A(raw_a);
        MASK_TYPE B(raw_b);
        MASK_TYPE C(raw_c);

        C = A || B;

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("LORV(operator ||)"));
    }
}

template<typename VEC_TYPE, typename SCALAR_TYPE, int VEC_LEN, int SIMD_STRIDE>
void testADDV_random_static()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE raw_b[VEC_LEN];
        SCALAR_TYPE result[VEC_LEN];
        SCALAR_TYPE raw_c[VEC_LEN];

        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
            raw_b[i] = randomValue<SCALAR_TYPE>(gen);
            result[i] = raw_a[i] + raw_b[i];
        }

        VEC_TYPE A(raw_a);
        VEC_TYPE B(raw_b);
        VEC_TYPE C(raw_c);

        C = A.add(B);

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("ADDV"));
    }
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE raw_b[VEC_LEN];
        SCALAR_TYPE result[VEC_LEN];
        SCALAR_TYPE raw_c[VEC_LEN];

        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
            raw_b[i] = randomValue<SCALAR_TYPE>(gen);
            result[i] = raw_a[i] + raw_b[i];
        }

        VEC_TYPE A(raw_a);
        VEC_TYPE B(raw_b);
        VEC_TYPE C(raw_c);

        C = A + B;

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("ADDV(operator +)"));
    }
}

template<typename VEC_TYPE, typename MASK_TYPE, typename SCALAR_TYPE, int VEC_LEN, int SIMD_STRIDE>
void testMADDV_random_static()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE raw_b[VEC_LEN];
        SCALAR_TYPE result[VEC_LEN];
        SCALAR_TYPE raw_c[VEC_LEN];
        bool        raw_mask[VEC_LEN];

        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
            raw_b[i] = randomValue<SCALAR_TYPE>(gen);
            raw_mask[i] = randomValue<bool>(gen);
            result[i] = raw_mask[i] ? raw_a[i] + raw_b[i] : raw_a[i];
        }

        VEC_TYPE A(raw_a);
        VEC_TYPE B(raw_b);
        VEC_TYPE C(raw_c);
        MASK_TYPE mask(raw_mask);

        C = A.add(mask, B);

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("MADDV"));
    }
}

template<typename VEC_TYPE, typename SCALAR_TYPE, int VEC_LEN, int SIMD_STRIDE>
void testADDS_random_static()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE b;
        SCALAR_TYPE result[VEC_LEN];
        SCALAR_TYPE raw_c[VEC_LEN];

        b = randomValue<SCALAR_TYPE>(gen);
        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
            result[i] = raw_a[i] + b;
        }

        VEC_TYPE A(raw_a);
        VEC_TYPE C(raw_c);

        C = A.add(b);

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("ADDS"));
    }
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE b;
        SCALAR_TYPE result[VEC_LEN];
        SCALAR_TYPE raw_c[VEC_LEN];

        b = randomValue<SCALAR_TYPE>(gen);
        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
            result[i] = raw_a[i] + b;
        }

        VEC_TYPE A(raw_a);
        VEC_TYPE C(raw_c);

        C = A + b;

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("ADDS (operator + RHS scalar)"));
    }
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE b;
        SCALAR_TYPE result[VEC_LEN];
        SCALAR_TYPE raw_c[VEC_LEN];

        b = randomValue<SCALAR_TYPE>(gen);
        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
            result[i] = raw_a[i] + b;
        }

        VEC_TYPE A(raw_a);
        VEC_TYPE C(raw_c);

        C = b + A;

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("ADDS (operator + LHS scalar)"));
    }
}

template<typename VEC_TYPE, typename MASK_TYPE, typename SCALAR_TYPE, int VEC_LEN, int SIMD_STRIDE>
void testMADDS_random_static()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE b;
        SCALAR_TYPE result[VEC_LEN];
        SCALAR_TYPE raw_c[VEC_LEN];
        bool        raw_mask[VEC_LEN];

        b = randomValue<SCALAR_TYPE>(gen);
        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
            raw_mask[i] = randomValue<bool>(gen);
            result[i] = raw_mask[i] ? raw_a[i] + b : raw_a[i];
        }

        VEC_TYPE A(raw_a);
        VEC_TYPE C(raw_c);
        MASK_TYPE mask(raw_mask);

        C = A.add(mask, b);

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("MADDS"));
    }
}
template<typename VEC_TYPE, typename SCALAR_TYPE, int VEC_LEN, int SIMD_STRIDE>
void testSUBV_random_static()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE raw_b[VEC_LEN];
        SCALAR_TYPE result[VEC_LEN];
        SCALAR_TYPE raw_c[VEC_LEN];

        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
            raw_b[i] = randomValue<SCALAR_TYPE>(gen);
            result[i] = raw_a[i] - raw_b[i];
        }

        VEC_TYPE A(raw_a);
        VEC_TYPE B(raw_b);
        VEC_TYPE C(raw_c);

        C = A.sub(B);

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("SUBV"));
    }
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE raw_b[VEC_LEN];
        SCALAR_TYPE result[VEC_LEN];
        SCALAR_TYPE raw_c[VEC_LEN];

        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
            raw_b[i] = randomValue<SCALAR_TYPE>(gen);
            result[i] = raw_a[i] - raw_b[i];
        }

        VEC_TYPE A(raw_a);
        VEC_TYPE B(raw_b);
        VEC_TYPE C(raw_c);

        C = A - B;

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("SUBV(operator -)"));
    }
}

template<typename VEC_TYPE, typename SCALAR_TYPE, int VEC_LEN, int SIMD_STRIDE>
void testMULV_random_static()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE raw_b[VEC_LEN];
        SCALAR_TYPE result[VEC_LEN];
        SCALAR_TYPE raw_c[VEC_LEN];

        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
            raw_b[i] = randomValue<SCALAR_TYPE>(gen);
            result[i] = raw_a[i] * raw_b[i];
        }

        VEC_TYPE A(raw_a);
        VEC_TYPE B(raw_b);
        VEC_TYPE C(raw_c);

        C = A.mul(B);

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("MULV"));
    }
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE raw_b[VEC_LEN];
        SCALAR_TYPE result[VEC_LEN];
        SCALAR_TYPE raw_c[VEC_LEN];

        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
            raw_b[i] = randomValue<SCALAR_TYPE>(gen);
            result[i] = raw_a[i] * raw_b[i];
        }

        VEC_TYPE A(raw_a);
        VEC_TYPE B(raw_b);
        VEC_TYPE C(raw_c);

        C = A * B;

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("MULV(operator *)"));
    }
}

template<typename VEC_TYPE, typename SCALAR_TYPE, int VEC_LEN, int SIMD_STRIDE>
void testHADD_random_static()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE result = SCALAR_TYPE(0);

        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
            result += raw_a[i];
        }

        VEC_TYPE A(raw_a);
        SCALAR_TYPE b;

        b = A.hadd();

        bool inRange = valueInRange(result, b, 0.01f);
        check_condition(inRange, std::string("HADD"));
    }
}

template<typename VEC_TYPE, typename SCALAR_TYPE, int VEC_LEN, int SIMD_STRIDE>
void testMemoryOwnership() 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        
        for (int i=0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
        }
        
        VEC_TYPE A; // Vector owns the memory.
        
        for (int i=0; i < VEC_LEN; i++) {
            A.elements[i] = raw_a[i];
        }
        
        bool inRange = valueInRange(A.elements, &raw_a[0], 0.01f);
        check_condition(inRange, std::string("Memory ownership"));
    }
}

template<typename VEC_TYPE, typename SCALAR_TYPE, int VEC_LEN, int SIMD_STRIDE>
void testGatherScatterDynamic()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    {
        SCALAR_TYPE raw_a[VEC_LEN*10];
        SCALAR_TYPE expected[VEC_LEN];
        SCALAR_TYPE raw_b[VEC_LEN];
        
        for (int i=0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
        }
        
        for (int i=0; i < VEC_LEN; i++) {
            expected[i] = raw_a[i*4];
        }

        VEC_TYPE A(VEC_LEN, raw_a, 4); // gather with stride '4'
        VEC_TYPE B(VEC_LEN, raw_b); // scatter (store) with stride '1'
        
        B = A; // Gather from 'raw_a' with stride, and store to 'raw_b'.
        
        bool inRange = valueInRange(&raw_b[0], &expected[0], 0.01f);
        check_condition(inRange, std::string("Gather + store (dynamic)"));
    }
    {
        SCALAR_TYPE raw_a[VEC_LEN*10];
        SCALAR_TYPE expected[VEC_LEN*10];
        SCALAR_TYPE raw_b[VEC_LEN*10];
        
        for (int i=0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
        }
        
        // Initialize passive elements
        for (int i=0; i < VEC_LEN*10; i++) {
            expected[i] = SCALAR_TYPE(0);
            raw_b[i] = SCALAR_TYPE(0);
        }
        
        // Initialize expected elements
        for (int i=0; i < VEC_LEN; i++) {
            expected[i*8] = raw_a[i*2];
        }

        VEC_TYPE A(VEC_LEN, raw_a, 2); // gather with stride '2'
        VEC_TYPE B(VEC_LEN, raw_b, 8); // scatter with stride '8'
        
        B = A; // Gather from 'raw_a' with stride, and store to 'raw_b'.
        
        bool inRange = valueInRange(&raw_b[0], &expected[0], 0.01f);
        check_condition(inRange, std::string("Gather + scatter (dynamic)"));
    }
    
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE expected[VEC_LEN*10];
        SCALAR_TYPE raw_b[VEC_LEN*10];
        
        for (int i=0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
        }
        
        // Initialize passive elements
        for (int i=0; i < VEC_LEN*10; i++) {
            expected[i] = SCALAR_TYPE(0);
            raw_b[i] = SCALAR_TYPE(0);
        }
        
        // Initialize expected elements
        for (int i=0; i < VEC_LEN; i++) {
            expected[i*8] = raw_a[i];
        }
        VEC_TYPE A(VEC_LEN, raw_a); // gather (load) with stride '1'
        VEC_TYPE B(VEC_LEN, raw_b, 8); // scatter with stride '8'
        
        B = A; // Gather from 'raw_a' with stride, and store to 'raw_b'.
        
        bool inRange = valueInRange(&raw_b[0], &expected[0], 0.01f);
        check_condition(inRange, std::string("load + scatter (dynamic)"));
    }
}


template<typename VEC_TYPE, typename SCALAR_TYPE, int VEC_LEN, int SIMD_STRIDE>
void testGatherScatterStatic()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    {
        SCALAR_TYPE raw_a[VEC_LEN*10];
        SCALAR_TYPE expected[VEC_LEN];
        SCALAR_TYPE raw_b[VEC_LEN];
        
        for (int i=0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
        }
        
        for (int i=0; i < VEC_LEN; i++) {
            expected[i] = raw_a[i*4];
        }

        VEC_TYPE A(raw_a, 4); // gather with stride '4'
        VEC_TYPE B(raw_b); // scatter (store) with stride '1'
        
        B = A; // Gather from 'raw_a' with stride, and store to 'raw_b'.
        
        bool inRange = valueInRange(&raw_b[0], &expected[0], 0.01f);
        check_condition(inRange, std::string("Gather + store (static)"));
    }
    {
        SCALAR_TYPE raw_a[VEC_LEN*10];
        SCALAR_TYPE expected[VEC_LEN*10];
        SCALAR_TYPE raw_b[VEC_LEN*10];
        
        for (int i=0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
        }
        
        // Initialize passive elements
        for (int i=0; i < VEC_LEN*10; i++) {
            expected[i] = SCALAR_TYPE(0);
            raw_b[i] = SCALAR_TYPE(0);
        }
        
        // Initialize expected elements
        for (int i=0; i < VEC_LEN; i++) {
            expected[i*8] = raw_a[i*2];
        }

        VEC_TYPE A(raw_a, 2); // gather with stride '2'
        VEC_TYPE B(raw_b, 8); // scatter with stride '8'
        
        B = A; // Gather from 'raw_a' with stride, and store to 'raw_b'.
        
        bool inRange = valueInRange(&raw_b[0], &expected[0], 0.01f);
        check_condition(inRange, std::string("Gather + scatter (static)"));
    }
    
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE expected[VEC_LEN*10];
        SCALAR_TYPE raw_b[VEC_LEN*10];
        
        for (int i=0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
        }
        
        // Initialize passive elements
        for (int i=0; i < VEC_LEN*10; i++) {
            expected[i] = SCALAR_TYPE(0);
            raw_b[i] = SCALAR_TYPE(0);
        }
        
        // Initialize expected elements
        for (int i=0; i < VEC_LEN; i++) {
            expected[i*8] = raw_a[i];
        }
        VEC_TYPE A(raw_a); // gather (load) with stride '1'
        VEC_TYPE B(raw_b, 8); // scatter with stride '8'
        
        B = A; // Gather from 'raw_a' with stride, and store to 'raw_b'.
        
        bool inRange = valueInRange(&raw_b[0], &expected[0], 0.01f);
        check_condition(inRange, std::string("load + scatter (static)"));
    }
}

int main() {
    {
        char header[] = { "Mask Vector test (STRIDE 8):" };
        INIT_TEST(header, false);
        testLAND_random_static<UME::VECTOR::MaskVector<100, 8>, 100, 8>();
        testLOR_random_static<UME::VECTOR::MaskVector<100, 8>, 100, 8>();
        testMemoryOwnership<UME::VECTOR::MaskVector<100, 8>, bool, 100, 8>();
        testGatherScatterDynamic<UME::VECTOR::MaskVector<UME_DYNAMIC_LENGTH, 8>, bool, 100, 8>();
        testGatherScatterStatic<UME::VECTOR::MaskVector<100, 8>, bool, 100, 8>();
    }

    {
        char header[] = { "Uint32_t Vector test (STRIDE 4):" };
        INIT_TEST(header, false);
        testADDV_random_static<UME::VECTOR::UintVector<uint32_t, 100, 4>, uint32_t, 100, 4>();
        testMADDV_random_static<UME::VECTOR::UintVector<uint32_t, 100, 4>, UME::VECTOR::MaskVector<100, 4>, uint32_t, 100, 4>();
        testADDS_random_static<UME::VECTOR::UintVector<uint32_t, 100, 4>, uint32_t, 100, 4>();
        testMADDS_random_static<UME::VECTOR::UintVector<uint32_t, 100, 4>, UME::VECTOR::MaskVector<100, 4>, uint32_t, 100, 4>();
        testSUBV_random_static<UME::VECTOR::UintVector<uint32_t, 100, 4>, uint32_t, 100, 4>();
        testMULV_random_static<UME::VECTOR::UintVector<uint32_t, 100, 4>, uint32_t, 100, 4>();

        testHADD_random_static<UME::VECTOR::UintVector<uint32_t, 100, 4>, uint32_t, 100, 4>();
        
        testMemoryOwnership<UME::VECTOR::UintVector<uint32_t, 100, 4>, uint32_t, 100, 4>();
        testGatherScatterDynamic<UME::VECTOR::UintVector<uint32_t, UME_DYNAMIC_LENGTH, 4>, uint32_t, 100, 4>();
        testGatherScatterStatic<UME::VECTOR::UintVector<uint32_t, 100, 4>, uint32_t, 100, 4>();
    }
    {
        char header[] = { "Int32_t Vector test (STRIDE 4):" };
        INIT_TEST(header, false);
        testADDV_random_static<UME::VECTOR::IntVector<int32_t, 100, 4>, int32_t, 100, 4>();
        testMADDV_random_static<UME::VECTOR::IntVector<int32_t, 100, 4>, UME::VECTOR::MaskVector<100, 4>, int32_t, 100, 4>();
        testADDS_random_static<UME::VECTOR::IntVector<int32_t, 100, 4>, int32_t, 100, 4>();
        testMADDS_random_static<UME::VECTOR::IntVector<int32_t, 100, 4>, UME::VECTOR::MaskVector<100, 4>, int32_t, 100, 4>();
        testSUBV_random_static<UME::VECTOR::IntVector<int32_t, 100, 4>, int32_t, 100, 4>();
        testMULV_random_static<UME::VECTOR::IntVector<int32_t, 100, 4>, int32_t, 100, 4>();

        testHADD_random_static<UME::VECTOR::IntVector<int32_t, 100, 4>, int32_t, 100, 4>();
        
        testMemoryOwnership<UME::VECTOR::IntVector<int32_t, 100, 4>, int32_t, 100, 4>();
        testGatherScatterDynamic<UME::VECTOR::IntVector<int32_t, UME_DYNAMIC_LENGTH, 4>, int32_t, 100, 4>();
        testGatherScatterStatic<UME::VECTOR::IntVector<int32_t, 100, 4>, int32_t, 100, 4>();
    }
    {
        char header[] = { "Float Vector test (STRIDE 4):" };
        INIT_TEST(header, false);

        testADDV_random_static<UME::VECTOR::FloatVector<float, 1000, 4>, float, 1000, 4>();
        testMADDV_random_static<UME::VECTOR::FloatVector<float, 1000, 4>, UME::VECTOR::MaskVector<1000, 4>, float, 1000, 4>();
        testADDS_random_static<UME::VECTOR::FloatVector<float, 1000, 4>, float, 1000, 4>();
        testMADDS_random_static<UME::VECTOR::FloatVector<float, 1000, 4>, UME::VECTOR::MaskVector<1000, 4>, float, 1000, 4>();
        testSUBV_random_static<UME::VECTOR::FloatVector<float, 1000, 4>, float, 1000, 4>();
        testMULV_random_static<UME::VECTOR::FloatVector<float, 1000, 4>, float, 1000, 4>();

        testHADD_random_static<UME::VECTOR::FloatVector<float, 1000, 4>, float, 1000, 4>();
        testMemoryOwnership<UME::VECTOR::IntVector<float, 1000, 4>, float, 1000, 4>();
        testGatherScatterDynamic<UME::VECTOR::IntVector<float, UME_DYNAMIC_LENGTH, 4>, float, 1000, 4>();
        testGatherScatterStatic<UME::VECTOR::IntVector<float, 100, 4>, float, 1000, 4>();
    }
    {
        float rawA[100], rawB[100], rawC[100], rawD[100], rawE[100], rawF[100];
        UME::VECTOR::FloatVector<float, 100, 4> A(rawA);
        UME::VECTOR::FloatVector<float, 100, 4> B(rawB);
        UME::VECTOR::FloatVector<float, 100, 4> C(rawC);
        UME::VECTOR::FloatVector<float, 100, 4> D(rawD);
        UME::VECTOR::FloatVector<float, 100, 4> E(rawE);
        UME::VECTOR::FloatVector<float, 100, 4> F(rawF);

        auto t0 = A.add(B);
        auto t1 = t0.mul(C);
        auto t2 = t1.div(D);
        auto t3 = t2.sub(E);

        F = t3;
    }

    {
        float rawA[100], rawB[100], rawC[100], rawD[100], rawE[100], rawF[100];
        bool rawM[100];

        for (int i = 0; i < 100; i++) {
            rawA[i] = float(i) + 1.0f;
            rawB[i] = float(i) + 2.0f;
            rawC[i] = float(i) + 3.0f;
            rawD[i] = float(i) + 4.0f;
            rawE[i] = float(i) + 5.0f;
            rawF[i] = float(i) + 6.0f;

            rawM[i] = (i % 2) == 0 ? true : false;
        }

        UME::VECTOR::FloatVector<float, 100, 4> A(rawA);
        UME::VECTOR::FloatVector<float, 100, 4> B(rawB);
        UME::VECTOR::FloatVector<float, 100, 4> C(rawC);
        UME::VECTOR::FloatVector<float, 100, 4> D(rawD);
        UME::VECTOR::FloatVector<float, 100, 4> E(rawE);
        UME::VECTOR::FloatVector<float, 100, 4> F(rawF);
        UME::VECTOR::MaskVector<100, 4> mask(rawM);

        auto t0 = A.add(mask, B);
        auto t1 = t0.mul(C);
        auto t2 = t1.div(D);
        auto t3 = t2.sub(mask, E);

        F = t3;
    }
    {
        float rawA[100], rawB[100], rawC[100], rawD[100], rawE[100], rawF[100], rawG[100];
        bool rawM[100];

        for (int i = 0; i < 100; i++) {
            rawA[i] = float(i) + 1.0f;
            rawB[i] = float(i) + 2.0f;
            rawC[i] = float(i) + 3.0f;
            rawD[i] = float(i) + 4.0f;
            rawE[i] = float(i) + 5.0f;
            rawF[i] = float(i) + 6.0f;
            rawG[i] = float(i) + 7.0f;

            rawM[i] = (i % 2) == 0 ? true : false;
        }

        UME::VECTOR::FloatVector<float, 100, 4> A(rawA);
        UME::VECTOR::FloatVector<float, 100, 4> B(rawB);
        UME::VECTOR::FloatVector<float, 100, 4> C(rawC);
        UME::VECTOR::FloatVector<float, 100, 4> D(rawD);
        UME::VECTOR::FloatVector<float, 100, 4> E(rawE);
        UME::VECTOR::FloatVector<float, 100, 4> F(rawF);
        UME::VECTOR::FloatVector<float, 100, 4> G(rawG);
        UME::VECTOR::MaskVector<100, 4> mask(rawM);

        auto t0 = A.add(mask, B);
        auto t1 = t0.fmuladd(C, D);
        auto t2 = t1.sub(mask, E);
        auto t3 = t2.fmulsub(F, t2);

        G = t3;
    }
    {
        float rawA[100], rawB[100], rawC[100], rawD[100], rawE[100], rawF[100], rawG[100];
        bool rawM[100];

        for (int i = 0; i < 100; i++) {
            rawA[i] = float(i) + 1.0f;
            rawB[i] = float(i) + 2.0f;
            rawC[i] = float(i) + 3.0f;
            rawD[i] = float(i) + 4.0f;
            rawE[i] = float(i) + 5.0f;
            rawF[i] = float(i) + 6.0f;
            rawG[i] = float(i) + 7.0f;

            rawM[i] = (i % 2) == 0 ? true : false;
        }

        UME::VECTOR::FloatVector<float, 100, 4> A(rawA);
        UME::VECTOR::FloatVector<float, 100, 4> B(rawB);
        UME::VECTOR::FloatVector<float, 100, 4> C(rawC);
        UME::VECTOR::FloatVector<float, 100, 4> D(rawD);
        UME::VECTOR::FloatVector<float, 100, 4> E(rawE);
        UME::VECTOR::FloatVector<float, 100, 4> F(rawF);
        UME::VECTOR::FloatVector<float, 100, 4> G(rawG);
        UME::VECTOR::MaskVector<100, 4> mask(rawM);

        auto t0 = A.add(mask, B);
        auto t1 = t0.fmuladd(C, D);
        auto t2 = t1.fmuladd(E, E);
        auto t3 = t2.fmulsub(F, t2);

        G = t3;
    }
    {
        int32_t rawA[100], rawB[100];
        float rawC[100], rawD[100];

        for (int i = 0; i < 100; i++) {
            rawA[i] = i + 1;
            rawB[i] = i + 2;
            rawC[i] = float(i) + 3.0f;
            rawD[i] = float(i) + 4.0f;
        }

        UME::VECTOR::IntVector<int32_t, 100, 4> A(rawA);
        UME::VECTOR::IntVector<int32_t, 100, 4> B(rawB);
        UME::VECTOR::FloatVector<float, 100, 4> C(rawC);
        UME::VECTOR::FloatVector<float, 100, 4> D(rawD);

        auto t0 = A.add(B);
        auto t1 = t0.itof();
        auto t2 = t1.add(D);
        C = t2;
    }
    {
        int32_t rawA[100], rawB[100];
        uint32_t rawC[100], rawD[100];

        for (int i = 0; i < 100; i++) {
            rawA[i] = i + 1;
            rawB[i] = i + 2;
            rawC[i] = i + 3;
            rawD[i] = i + 4;
        }

        UME::VECTOR::IntVector<int32_t, 100, 4> A(rawA);
        UME::VECTOR::IntVector<int32_t, 100, 4> B(rawB);
        UME::VECTOR::UintVector<uint32_t, 100, 4> C(rawC);
        UME::VECTOR::UintVector<uint32_t, 100, 4> D(rawD);

        auto t0 = A.add(B);
        auto t1 = t0.itou();
        auto t2 = t1.add(D);
        C = t2;
    }
    {
        uint32_t rawA[100], rawB[100];
        int32_t rawC[100], rawD[100];

        for (int i = 0; i < 100; i++) {
            rawA[i] = i + 1;
            rawB[i] = i + 2;
            rawC[i] = i + 3;
            rawD[i] = i + 4;
        }

        UME::VECTOR::UintVector<uint32_t, 100, 4> A(rawA);
        UME::VECTOR::UintVector<uint32_t, 100, 4> B(rawB);
        UME::VECTOR::IntVector<int32_t, 100, 4> C(rawC);
        UME::VECTOR::IntVector<int32_t, 100, 4> D(rawD);

        auto t0 = A.add(B);
        auto t1 = t0.utoi();
        auto t2 = t1.add(D);
        C = t2;
    }

    {
        float rawA[100], rawB[100], rawC[100], rawD[100], rawE[100];

        for (int i = 0; i < 100; i++) {
            rawA[i] = float(i) + 1.0f;
            if(i % 2 == 0) rawB[i] = float(i) + 2.0f;
            else rawB[i] = float(i) + 0.5f;
            rawC[i] = float(i) + 3.0f;
            rawD[i] = float(i) + 4.0f;
            rawE[i] = float(i) + 5.0f;
        }

        UME::VECTOR::FloatVector<float, 100, 4> A(rawA);
        UME::VECTOR::FloatVector<float, 100, 4> B(rawB);
        UME::VECTOR::FloatVector<float, 100, 4> C(rawC);
        UME::VECTOR::FloatVector<float, 100, 4> D(rawD);
        UME::VECTOR::FloatVector<float, 100, 4> E(rawE);

        auto t0 = A.cmpgt(B);
        auto t1 = C.add(t0, D);
        E = t1;
    }
    {
        float rawA[100];
        int32_t rawB[100], rawC[100], rawD[100], rawE[100];

        for (int i = 0; i < 100; i++) {
            rawA[i] = float(i) + 1.0f;
            if (i % 2 == 0) rawB[i] = i + 2;
            else rawB[i] = i;
            rawC[i] = i + 3;
            rawD[i] = i + 4;
            rawE[i] = i + 5;
        }

        UME::VECTOR::FloatVector<float, 100, 4> A(rawA);
        UME::VECTOR::IntVector<int32_t, 100, 4> B(rawB);
        UME::VECTOR::IntVector<int32_t, 100, 4> C(rawC);
        UME::VECTOR::IntVector<int32_t, 100, 4> D(rawD);
        UME::VECTOR::IntVector<int32_t, 100, 4> E(rawE);

        auto t0 = B.cmpgt(A.ftoi());
        auto t1 = C.add(t0, D);
        E = t1;
    }
    {
        float rawA[100], rawB[100], rawC[100];
        bool rawM[100];

        for (int i = 0; i < 100; i++) {
            rawA[i] = float(i) + 1.0f;
            rawB[i] = float(i) + 2.0f;

            rawM[i] = (i % 2) == 0 ? true : false;
        }

        UME::VECTOR::FloatVector<float, 100, 4> A(rawA);
        UME::VECTOR::FloatVector<float, 100, 4> B(rawB);
        UME::VECTOR::FloatVector<float, 100, 4> C(rawC);
        UME::VECTOR::MaskVector<100, 4> mask(rawM);

        C = A.blend(mask, B);
    }
    {
        bool rawA[100], rawB[100], rawC[100];

        for (int i = 0; i < 100; i++) {
            rawA[i] = (i % 2) == 0 ? true : false;
            rawB[i] = (i % 2) == 0 ? true : false;
            rawC[i] = (i % 2) == 0 ? true : false;
        }

        UME::VECTOR::MaskVector<100, 4> maskA(rawA);
        UME::VECTOR::MaskVector<100, 4> maskB(rawB);
        UME::VECTOR::MaskVector<100, 4> maskC(rawC);

        auto t0 = maskA.land(maskB);
        maskC = t0.lnot();
    }

    {
        uint32_t rawA[100], rawB[100], rawC[100];

        UME::VECTOR::Vector<uint32_t, 100, 4> A(rawA);
        UME::VECTOR::Vector<uint32_t, 100, 4> B(rawB);
        UME::VECTOR::Vector<uint32_t, 100, 4> C(rawC);

        C = (((A + B).utof()).sin()).ftou();
    }
    {
        float rawA[100], rawB[100], rawC[100];

        UME::VECTOR::Vector<float, 100, 4> A(rawA);
        UME::VECTOR::Vector<float, 100, 4> B(rawB);
        UME::VECTOR::Vector<float, 100, 4> C(rawC);

        C = (A + B).sin();
        //C = A.band(B);
    }
    {
        uint32_t rawA[100], rawB[100], rawC[100];

        UME::VECTOR::Vector<uint32_t, 100, 4> A(rawA);
        UME::VECTOR::Vector<uint32_t, 100, 4> B(rawB);
        UME::VECTOR::Vector<uint32_t, 100, 4> C(rawC);

        C = A.lsh(B);
    }
    {
        int32_t rawA[100], rawC[100];
        uint32_t rawB[100];

        UME::VECTOR::Vector<int32_t, 100, 4> A(rawA);
        UME::VECTOR::Vector<uint32_t, 100, 4> B(rawB);
        UME::VECTOR::Vector<int32_t, 100, 4> C(rawC);

        C = A.lsh(B);
    }
    {
        int32_t rawA[100], rawC[100];

        UME::VECTOR::Vector<int32_t, 100, 4> A(rawA);
        UME::VECTOR::Vector<int32_t, 100, 4> C(rawC);

        int32_t b = 4;

        C = A.lsh(4);
    }
    {
        int32_t rawA[8], rawB[8], rawC[8];

        for (int i = 0; i < 8; i++) {
            rawA[i] = i;
            rawB[i] = i + 8;
            rawC[i] = i + 16;
        }

        UME::VECTOR::Vector<int32_t, 8, DefaultStride<int32_t>::value> A(rawA);
        UME::VECTOR::Vector<int32_t> B (8, rawB);
        UME::VECTOR::Vector<int32_t> C(8, rawC);

        A = B;
        B = A - (C + A);
        }
    {
        int32_t rawA[8], rawB[8], rawC[8], rawD[8];

        for (int i = 0; i < 8; i++) {
            rawA[i] = i;
            rawB[i] = i + 8;
            rawC[i] = i + 16;
            rawD[i] = 0;
        }

        UME::VECTOR::Vector<int32_t, 8, DefaultStride<int32_t>::value> A(rawA);
        UME::VECTOR::Vector<int32_t> B(8, rawB);
        UME::VECTOR::Vector<int32_t> C(8, rawC);
        UME::VECTOR::Vector<int32_t> D(8, rawD);

        A = B;
        B = A - (C + A);

        D = B.abs();
    }
    {
        float rawA[100], rawB[100], rawC[100];

        for (int i = 0; i < 100; i++) {
            rawA[i] = i;
            rawB[i] = 100 * i;
            rawC[i] = 10000 * i;
        }

        UME::VECTOR::Vector<float, 100, 4> A(rawA);
        UME::VECTOR::Vector<float, 100, 4> B(rawB);
        UME::VECTOR::Vector<float, 100, 4> C(rawC);

        auto t0 = A.adda(B);

        // Trigger the evaluation
        UME::VECTOR::MonadicEvaluator eval(t0);
    }
    {
        float rawA[100], rawB[100], rawC[100];

        for (int i = 0; i < 100; i++) {
            rawA[i] = i;
            rawB[i] = 100 * i;
            rawC[i] = 10000 * i;
        }

        UME::VECTOR::Vector<float, 100, 4> A(rawA);
        UME::VECTOR::Vector<float, 100, 4> B(rawB);
        UME::VECTOR::Vector<float, 100, 4> C(rawC);

        auto t0 = (A.adda(B)).adda(C);

        // Trigger the evaluation
        UME::VECTOR::MonadicEvaluator eval(t0);
    }
}
