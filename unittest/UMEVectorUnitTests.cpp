
#include <iostream>

#include <random>

#include <UMEVector.h>

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

template<typename VEC_TYPE, typename SCALAR_TYPE, int SIMD_STRIDE, int VEC_LEN> 
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

template<typename VEC_TYPE, typename MASK_TYPE, typename SCALAR_TYPE, int SIMD_STRIDE, int VEC_LEN>
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

template<typename VEC_TYPE, typename SCALAR_TYPE, int SIMD_STRIDE, int VEC_LEN>
void testADDS_random_static()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE raw_b;
        SCALAR_TYPE result[VEC_LEN];
        SCALAR_TYPE raw_c[VEC_LEN];

        raw_b = randomValue<SCALAR_TYPE>(gen);
        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
            result[i] = raw_a[i] + raw_b;
        }

        VEC_TYPE A(raw_a);
        UME::VECTOR::ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> B(raw_b);
        VEC_TYPE C(raw_c);

        C = A.add(B);

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("ADDS"));
    }
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE raw_b;
        SCALAR_TYPE result[VEC_LEN];
        SCALAR_TYPE raw_c[VEC_LEN];

        raw_b = randomValue<SCALAR_TYPE>(gen);
        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
            result[i] = raw_a[i] + raw_b;
        }

        VEC_TYPE A(raw_a);
        UME::VECTOR::ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> B(raw_b);
        VEC_TYPE C(raw_c);

        C = A + B;

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("ADDS (operator + RHS scalar)"));
    }
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE raw_b;
        SCALAR_TYPE result[VEC_LEN];
        SCALAR_TYPE raw_c[VEC_LEN];

        raw_b = randomValue<SCALAR_TYPE>(gen);
        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
            result[i] = raw_a[i] + raw_b;
        }

        VEC_TYPE A(raw_a);
        UME::VECTOR::ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> B(raw_b);
        VEC_TYPE C(raw_c);

        C = B + A;

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("ADDS (operator + LHS scalar)"));
    }
}

template<typename VEC_TYPE, typename MASK_TYPE, typename SCALAR_TYPE, int SIMD_STRIDE, int VEC_LEN>
void testMADDS_random_static()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    {
        SCALAR_TYPE raw_a[VEC_LEN];
        SCALAR_TYPE raw_b;
        SCALAR_TYPE result[VEC_LEN];
        SCALAR_TYPE raw_c[VEC_LEN];
        bool        raw_mask[VEC_LEN];

        raw_b = randomValue<SCALAR_TYPE>(gen);
        for (int i = 0; i < VEC_LEN; i++) {
            raw_a[i] = randomValue<SCALAR_TYPE>(gen);
            raw_mask[i] = randomValue<bool>(gen);
            result[i] = raw_mask[i] ? raw_a[i] + raw_b : raw_a[i];
        }

        VEC_TYPE A(raw_a);
        UME::VECTOR::ScalarExpression<float, 4> B(raw_b);
        VEC_TYPE C(raw_c);
        MASK_TYPE mask(raw_mask);

        C = A.add(mask, B);

        bool inRange = valuesInRange(result, raw_c, VEC_LEN, 0.01f);
        check_condition(inRange, std::string("MADDS"));
    }
}
template<typename VEC_TYPE, typename SCALAR_TYPE, int SIMD_STRIDE, int VEC_LEN>
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


template<typename VEC_TYPE, typename SCALAR_TYPE, int SIMD_STRIDE, int VEC_LEN>
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

template<typename VEC_TYPE, typename SCALAR_TYPE, int SIMD_STRIDE, int VEC_LEN>
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
        SCALAR_TYPE B;

        B = A.hadd();

        bool inRange = valueInRange(result, B, 0.01f);
        check_condition(inRange, std::string("HADD"));
    }
}


int main() {
    char header[] = { "Float Vector test (STRIDE 4):" };
    INIT_TEST(header, false);

    testADDV_random_static<UME::VECTOR::FloatVector<float, 4, 1000>, float, 4, 1000>();
    testMADDV_random_static<UME::VECTOR::FloatVector<float, 4, 1000>, UME::VECTOR::MaskVector<4, 1000>, float, 4, 1000>();
    testADDS_random_static<UME::VECTOR::FloatVector<float, 4, 1000>, float, 4, 1000>();
    testMADDS_random_static<UME::VECTOR::FloatVector<float, 4, 1000>, UME::VECTOR::MaskVector<4, 1000>, float, 4, 1000>();
    testSUBV_random_static<UME::VECTOR::FloatVector<float, 4, 1000>, float, 4, 1000>();
    testMULV_random_static<UME::VECTOR::FloatVector<float, 4, 1000>, float, 4, 1000>();

    testHADD_random_static<UME::VECTOR::FloatVector<float, 4, 1000>, float, 4, 1000>();
}
