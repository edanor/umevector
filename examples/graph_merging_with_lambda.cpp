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

// This example shows how to allow

#include "../UMEVector.h"

#include <random>

#define STEPS 20
#define VEC_LEN 64
#define STRIDE 8

float randomValue(std::mt19937 & generator) {
    std::uniform_real_distribution<float> dist(-5.0f, 5.0f);
    return dist(generator);
}

// This class is an example of a class defined within a framework. This could
// be a standalone function as well. In this case only the member function has
// to be a template to access derived type.
// The class implements a very simple solver for Runge-Kutta equation solver.
class FrameworkClass {
private:
    // RK internal state
 
public:
    // RK4 solver
    //  result - vector object mapped to user-provided result buffer
    //  x - user-defined 
    //  userFunc - user defined lambda function to be evaluated
    template<typename USER_LAMBDA_T>
    UME_FORCE_INLINE void rk4(
        UME::VECTOR::Vector<float, STRIDE, VEC_LEN> & result,
        UME::VECTOR::Vector<float, STRIDE, VEC_LEN> x,
        UME::VECTOR::Vector<float, STRIDE, VEC_LEN> y,
        float dx,
        USER_LAMBDA_T & f)
    {
        // All scalars have to be mapped to special type to
        // make sure they are not destroyed before they are actually needed.
        UME::VECTOR::Scalar<float, STRIDE> dx_s(dx);
        UME::VECTOR::Scalar<float, STRIDE> halfdx_s(dx * 0.5f);
        UME::VECTOR::Scalar<float, STRIDE> two(2.0f);
        UME::VECTOR::Scalar<float, STRIDE> sixth(1.0f / 6.0f);

        // Also bind the function parameters so that they persist through expression resolution.

        // Implement RK4 algorithm - very straightforward process.
        // the user function is here attached as a fragment of computation
        // graph, and it can be optimized for each 'k' independantly.
        auto k1 = dx_s * f(x, y);
        auto k2 = dx_s * f(x + halfdx_s, y + k1 * halfdx_s);
        auto k3 = dx_s * f(x + halfdx_s, y + k2 * halfdx_s);
        auto k4 = dx_s * f(x + dx_s, y + k3 * dx_s);

        // Merge into full computational graph and start evaluation.
        auto t0 = y + sixth * (k1 + two * k2 + two * k3 + k4);
        result = t0;
    }

    template<typename USER_LAMBDA_T>
    UME_FORCE_INLINE float rk4_scalar(
        float x,
        float y,
        float dx,
        USER_LAMBDA_T & f)
    {
        // All scalars have to be mapped to special type to
        // make sure they are not destroyed before they are actually needed.
        float dx_s(dx);
        float halfdx_s(dx * 0.5f);
        float two(2.0f);
        float sixth(1.0f / 6.0f);

        // Also bind the function parameters so that they persist through expression resolution.

        // Implement RK4 algorithm - very straightforward process.
        // the user function is here attached as a fragment of computation
        // graph, and it can be optimized for each 'k' independantly.
        auto k1 = dx_s * f(x, y);
        auto k2 = dx_s * f(x + halfdx_s, y + k1 * halfdx_s);
        auto k3 = dx_s * f(x + halfdx_s, y + k2 * halfdx_s);
        auto k4 = dx_s * f(x + dx_s, y + k3 * dx_s);

        // Merge into full computational graph and start evaluation.
        auto t0 = y + sixth * (k1 + two * k2 + two * k3 + k4);
        return t0;
    }
};


// This class is what user defines in his code. The class makes use of 
// the FrameworkClass to access domain specific functionality, and UME::VECTOR
// to access vector EDSL.
class UserClass 
{
private:
    // Use framework class to do some computation
    FrameworkClass framework;

    // Since the user is in control of memory objects, she has
    // to make sure that there is no-aliasing. Here it is done
    // by implementing a swap-buffer. The swap-buffering could
    // be also managed as part of the framework class.
    class SwapBuffer {
    private:
        float y1[VEC_LEN];
        float y2[VEC_LEN];
        
        bool which = false;
        
    public:
        // Returns available buffer
        float* getActiveBuffer() {
            if(which) return y1;
            else return y2;
        }
        
        float* getOtherBuffer() {
            if(which) return y2;
            else return y1;
        }
        
        // Swap buffers
        void swap() {
            which = !which;
        }
    };
    
public:
    UME_NEVER_INLINE void computeSomething() {
        
        SwapBuffer y_swap; 
        SwapBuffer x_swap;

        int steps = STEPS; // Number of time steps to calculate
        float timestep = 0.01f;

        // Set initial values
        std::random_device rd;
        std::mt19937 gen(rd());
        
        for(int i = 0; i < VEC_LEN; i++) {
            y_swap.getActiveBuffer()[i] = randomValue(gen);
            y_swap.getOtherBuffer()[i] = randomValue(gen);
            x_swap.getActiveBuffer()[i] = randomValue(gen);
            x_swap.getOtherBuffer()[i] = randomValue(gen);
        }

        // Some function defined by the user
        auto userFunction = [](auto X, auto Y) { return X * X + Y; };
        
        for(int i = 0; i < steps; i++) {
            // Bind the buffers to the UME::VECTOR objects.
            UME::VECTOR::Vector<float, STRIDE, VEC_LEN> y_vec(y_swap.getActiveBuffer());
            UME::VECTOR::Vector<float, STRIDE, VEC_LEN> result_vec(y_swap.getOtherBuffer());
            UME::VECTOR::Vector<float, STRIDE, VEC_LEN> x_vec(x_swap.getActiveBuffer());
            UME::VECTOR::Vector<float, STRIDE, VEC_LEN> next_x_vec(x_swap.getOtherBuffer());
            UME::VECTOR::Scalar<float, STRIDE> timestep_s(timestep);
            
            // Calculate the derivative
            framework.rk4(
                result_vec,
                x_vec,
                y_vec,
                timestep,
                userFunction);

            // Increment x with the timestep
            next_x_vec = x_vec + timestep_s;

            /* 
            // Useful for debugging
            std::cout << "Iteration: " << i << "\n";
            for (int i = 0; i < 5; i++) {
                std::cout << 
                    "    x(" << x_vec.elements[i] << ") "
                    "y("     << y_vec.elements[i] << ") "
                    "res("   << result_vec.elements[i] << ")\n";
            }*/
            
            // Swap the buffers
            y_swap.swap();
            x_swap.swap(); 
        }

        // In the scalar case swapping buffer is not necessary, however we
        // might want to preserve previous results.
        for (int i = 0; i < steps; i++) {
            // Bind the buffers to the UME::VECTOR objects.
            float* y_vec = y_swap.getActiveBuffer();
            float* result_vec = y_swap.getOtherBuffer();
            float* x_vec = x_swap.getActiveBuffer();

            for (int j = 0; j < VEC_LEN; j++)
            {
                // Calculate the derivative
                result_vec[j] = framework.rk4_scalar(
                    x_vec[j],
                    y_vec[j],
                    timestep,
                    userFunction);
            }

            // Increment x with the timestep
            x_vec[i] = x_vec[i] + timestep;

            /*
            // Useful for debugging
            std::cout << "Iteration: " << i << "\n";
            for (int j = 0; j < 5; i++) {
                std::cout <<
                    "    x(" << x_vec[i] << ") "
                    "y(" << y_vec[i] << ") "
                    "res(" << result_vec[i] << ")\n";
            }
            */
            // Swap only the y buffer. X already holds new value.
            y_swap.swap();
        }
    }

};



int main()
{
    UserClass c1;

    c1.computeSomething();

    return 0;
}