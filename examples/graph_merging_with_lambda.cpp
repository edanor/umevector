#include "../UMEVector.h"

#include <random>

float randomValue(std::mt19937 & generator) {
    //std::uniform_real_distribution<float> dist(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
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
    template<typename UserLambda>
    UME_NEVER_INLINE void rk4(
        UME::VECTOR::Vector<float, 4, 1000> & result, 
        UME::VECTOR::Vector<float, 4, 1000> & x,
        UME::VECTOR::Vector<float, 4, 1000> & y,
        float dx,
        UserLambda & f)
    {
        // All scalars have to be mapped to special type to
        // make sure they are not destroyed before they are actually needed.
        UME::VECTOR::Scalar<float, 4> dx_s(dx);
        UME::VECTOR::Scalar<float, 4> halfdx_s(dx * 0.5f);
        UME::VECTOR::Scalar<float, 4> two(2.0f);
        UME::VECTOR::Scalar<float, 4> sixth(1.0f / 6.0f);

        // Implement RK4 algorithm - very straightforward process.
        // the user function is here attached as a fragment of computation
        // graph, and it can be optimized for each 'k' independantly.
        auto k1 = dx_s * f(x, y);
        auto k2 = dx_s * f(x + halfdx_s, y + k1 * halfdx_s);
        auto k3 = dx_s * f(x + halfdx_s, y + k2 * halfdx_s);
        auto k4 = dx_s * f(x + dx_s, y + k3 * dx_s);
            
        // Merge into full computational graph and start evaluation.
        result = y + sixth * (k1 + two * k2 + two * k3 + k4);
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
        float y1[1000];
        float y2[1000];
        
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
    void computeSomething() {
        
        SwapBuffer y_swap; 
        SwapBuffer x_swap;

        int steps = 777; // Number of time steps to calculate
        float timestep = 0.01f;

        // Set initial values
        std::random_device rd;
        std::mt19937 gen(rd());
        
        for(int i = 0; i < 1000; i++) {
            y_swap.getActiveBuffer()[i] = randomValue(gen);
            y_swap.getOtherBuffer()[i] = randomValue(gen);
            x_swap.getActiveBuffer()[i] = randomValue(gen);
            x_swap.getOtherBuffer()[i] = randomValue(gen);
        }

        // Some derivative function defined by the user
        auto userFunction = [](auto & X, auto & Y) { return X * X + Y; };
        
        for(int i = 0; i < steps; i++) {
            // Bind the buffers to the UME::VECTOR objects.
            UME::VECTOR::Vector<float, 4, 1000> y_vec(y_swap.getActiveBuffer());
            UME::VECTOR::Vector<float, 4, 1000> result_vec(y_swap.getOtherBuffer());
            UME::VECTOR::Vector<float, 4, 1000> x_vec(x_swap.getActiveBuffer());
            UME::VECTOR::Vector<float, 4, 1000> next_x_vec(x_swap.getOtherBuffer());
            UME::VECTOR::Scalar<float, 4> timestep_s(timestep);
            
            // Calculate the derivative
            framework.rk4(
                result_vec,
                x_vec,
                y_vec,
                timestep,
                userFunction);

            // Increment x with the timestep            
            next_x_vec = x_vec + timestep_s;
            
            // Swap the buffers
            y_swap.swap();
            x_swap.swap(); 
        }
    }
    

};



int main()
{
    UserClass c1;

    c1.computeSomething();

    return 0;
}