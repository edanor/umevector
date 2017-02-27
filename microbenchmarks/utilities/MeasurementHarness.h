#pragma once


#include <time.h>
#include <string>

#include <umesimd/UMESimd.h>
#include "TimingStatistics.h"

#include <list>


// The test shouldn't allocate large memory buffers before initialize is called.
class Test {
public:
    TimingStatistics stats;

    // All the member functions are forced to never inline,
    // so that the compiler doesn't make any opportunistic guesses.
    // Since the cost consuming part of the benchmark, contained
    // in 'benchmarked_code' is measured all at once, the 
    // measurement offset caused by virtual function call should be
    // negligible.
    UME_NEVER_INLINE virtual void initialize() = 0;
    UME_NEVER_INLINE virtual void benchmarked_code() = 0;
    UME_NEVER_INLINE virtual void cleanup() = 0;
    UME_NEVER_INLINE virtual void verify() = 0;
    UME_NEVER_INLINE virtual std::string get_test_identifier() = 0;
};

class BenchmarkHarness {
private:
    std::list<Test*> tests;

public:

    void registerTest(Test *newTest) {
        tests.push_back(newTest);
    }

    void runAllTests(int RUNS) {

        for (auto iter = tests.begin(); iter != tests.end(); iter++) {
            Test* test = *iter;

            unsigned long long start, end;
            for (int i = 0; i < RUNS; i++) {

                // Initialization phase is skipped, as the
                // overhead of memory allocations is not
                // interesting for us
                test->initialize();

                // Start measurement
                start = get_timestamp();
                    // The critical fragment of the code being benchmarked
                    test->benchmarked_code();
                end = get_timestamp();

                test->cleanup();

                test->stats.update(end - start);
            }

            std::cout << test->get_test_identifier()
                << " Elapsed: " << (unsigned long long) test->stats.getAverage() << "\n";
        }
    }


};