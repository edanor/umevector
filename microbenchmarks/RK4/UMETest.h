#pragma once

#include "../utilities/MeasurementHarness.h"
#include "../utilities/UMERandomValues.h"

template<typename SCALAR_T, int PROBLEM_LENGTH, int STRIDE, int STEP_COUNT>
class UMETest : public Test {
private:
    static const int OPTIMAL_ALIGNMENT = UME::VECTOR::Vector<SCALAR_T, PROBLEM_LENGTH, STRIDE>::ALIGNMENT();

    class SwapBuffer {
    private:
        SCALAR_T *y1;
        SCALAR_T *y2;

        bool which = false;

    public:

        SwapBuffer() {
            y1 = (SCALAR_T*)UME::DynamicMemory::AlignedMalloc(sizeof(SCALAR_T)*PROBLEM_LENGTH, OPTIMAL_ALIGNMENT);
            y2 = (SCALAR_T*)UME::DynamicMemory::AlignedMalloc(sizeof(SCALAR_T)*PROBLEM_LENGTH, OPTIMAL_ALIGNMENT);
        }

        ~SwapBuffer() {
            UME::DynamicMemory::AlignedFree(y1);
            UME::DynamicMemory::AlignedFree(y2);
        }

        // Returns available buffer
        float* getActiveBuffer() {
            if (which) return y1;
            else return y2;
        }

        float* getOtherBuffer() {
            if (which) return y2;
            else return y1;
        }

        // Swap buffers
        void swap() {
            which = !which;
        }
    };

    template<typename USER_LAMBDA_T>
    UME_NEVER_INLINE void rk4_vectorized(
        UME::VECTOR::Vector<SCALAR_T, PROBLEM_LENGTH, STRIDE> & result,
        UME::VECTOR::Vector<SCALAR_T, PROBLEM_LENGTH, STRIDE> x,
        UME::VECTOR::Vector<SCALAR_T, PROBLEM_LENGTH, STRIDE> y,
        SCALAR_T dx,
        USER_LAMBDA_T & f)
    {
        float halfdx = dx * 0.5f;

        // Implement RK4 algorithm - very straightforward process.
        // the user function is here attached as a fragment of computation
        // graph, and it can be optimized for each 'k' independantly.
        auto k1 = dx * f(x, y);
        auto k2 = dx * f(x + halfdx, y + k1 * halfdx);
        auto k3 = dx * f(x + halfdx, y + k2 * halfdx);
        auto k4 = dx * f(x + dx, y + k3 * dx);

        // Merge into full computational graph and start evaluation.
        result = y + (1.0f / 6.0f) * (k1 + 2.0f * k2 + 2.0f * k3 + k4);
    }

    SwapBuffer* y_swap;
    SwapBuffer* x_swap;

    SCALAR_T *y_initial; // Copy of initial values of 'y' for verification

public:
    UME_NEVER_INLINE virtual void initialize() {
        // Set initial values
        std::random_device rd;
        std::mt19937 gen(rd());

        y_swap = new SwapBuffer();
        x_swap = new SwapBuffer();

        y_initial = (SCALAR_T*)UME::DynamicMemory::AlignedMalloc(sizeof(SCALAR_T)*PROBLEM_LENGTH, OPTIMAL_ALIGNMENT);

        for (int i = 0; i < PROBLEM_LENGTH; i++) {
            y_initial[i] = randomValue<SCALAR_T>(gen);

            y_swap->getActiveBuffer()[i] = y_initial[i];
            y_swap->getOtherBuffer()[i] = randomValue<SCALAR_T>(gen);
            x_swap->getActiveBuffer()[i] = randomValue<SCALAR_T>(gen);
            x_swap->getOtherBuffer()[i] = randomValue<SCALAR_T>(gen);
        }
    }

    UME_NEVER_INLINE virtual void benchmarked_code() {
        int steps = STEP_COUNT; // Number of time steps to calculate
        float timestep = 0.001f;

        auto userFunction = [](auto X, auto Y) { return X * X + Y; };

        for (int i = 0; i < STEP_COUNT; i++) {
            // Bind the buffers to the UME::VECTOR objects.
            UME::VECTOR::Vector<float, PROBLEM_LENGTH, STRIDE> y_vec(y_swap->getActiveBuffer());
            UME::VECTOR::Vector<float, PROBLEM_LENGTH, STRIDE> result_vec(y_swap->getOtherBuffer());
            UME::VECTOR::Vector<float, PROBLEM_LENGTH, STRIDE> x_vec(x_swap->getActiveBuffer());
            UME::VECTOR::Vector<float, PROBLEM_LENGTH, STRIDE> next_x_vec(x_swap->getOtherBuffer());
            UME::VECTOR::Scalar<float, STRIDE> timestep_s(timestep);

            // Calculate the derivative
            rk4_vectorized(
                result_vec,
                x_vec,
                y_vec,
                timestep,
                userFunction);

            /*
            std::cout << "Iteration: " << i << "\n";
            for (int j = 0; j < 5; j++) {
                std::cout <<
                    "    x(" << x_vec.elements[j] << ") "
                    "y(" << y_vec.elements[j] << ") "
                    "res(" << result_vec.elements[j] << ")\n";
            }*/

            // Increment x with the timestep
            next_x_vec = x_vec + timestep_s;

            // Swap the buffers
            y_swap->swap();
            x_swap->swap();
        }
    }

    UME_NEVER_INLINE virtual void cleanup() {
        UME::DynamicMemory::AlignedFree(y_initial);

        delete y_swap;
        delete x_swap;
    }

    UME_NEVER_INLINE virtual void verify() {
        // TODO:
    }

    UME_NEVER_INLINE virtual std::string get_test_identifier() {
        std::string retval = "";

        retval += "UME::VECTOR (X*X+Y), " +
            ScalarToString<SCALAR_T>::value() + " " +
            std::to_string(PROBLEM_LENGTH) + " " +
            std::to_string(STRIDE);

        return retval;
    }
};

