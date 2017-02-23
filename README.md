UME::VECTOR is an expression template based vectorization library. The library defines an interface for arbitrary-sized vectors. This library is based on UME::SIMD interface and requires it to work.

This piece of code was developed as part of ICE-DIP project at CERN.

 "ICE-DIP is a European Industrial Doctorate project funded by the 
 European Community's 7th Framework programme Marie Curie Actions under grant
 PITN-GA-2012-316596".

 All questions should be submitted using the bug tracking system:


   >   [bug tracker](https://bitbucket.org/edanor/vector/issues)


or by sending e-mail to:


   >   przemyslaw.karpinski@cern.ch


```
#!c

This is just an introductory document. It will be extended when possible.

// ***************************************************************************
// I. INTRODUCTION
// ***************************************************************************

I will assume that you are familiar with UME::SIMD (https://bitbucket.org/edanor/umesimd/overview). 
If not, please get familiar with it. To understand UME::VECTOR it is critical
to understand explicit vectorization and the problems related to it.

In order to use this library the environment needs to know localization of
UME::SIMD in the build system. There is no installation required and the library
can be used by simply including:

#include <UMEVector.h>

 
Let's look at a simple example of array addition in C++:

//--------------------------------------------
  float a[10], b[10], c[10];

  for(int i = 0; i < 10; i++) {
   c[i] = a[i] + b[i];
  }
//--------------------------------------------

One of the major problems in UME::SIMD approach is, that it is only possible to
use vectors of some restricted lengths. Vectors of these specific lengths map
well to hardware registers (or worker threads) and allow the user to achieve
higher performance. It is however troublesome to work with such fixed length
vectors, especially when our algorithm requires some more exotic values. With
UME::SIMD alone (or some other explicit vectorization library), user can
manually split the longer vector into short vectors of 2^k lengths:


//--------------------------------------------
  float a[10], b[10], c[10];

  UME::SIMD::SIMDVec<float, 8> a0_7, b0_7, c0_7;  
  UME::SIMD::SIMDVec<float, 2> a8_9, b8_9, c8_9;  
  
  a0_7.load(&a[0]);
  b0_7.load(&b[0]);
  a8_9.load(&a[8]);
  b8_9.load(&b[8]);

  c0_7 = a0_7 + b0_7;
  c8_9 = a8_9 + b8_9;

  c0_7.store(&c[0]);
  c8_9.store(&c[8]);
  
//--------------------------------------------

This approach allows stricter control over the compiler generated code:
* SIMD instruction generation is guaranteed.
* loop is guaranteed to be removed 
* instructions are intertwined which might result in better ILP.

Obviously this code is not very readable and looks more like an inline assembly.
The same piece of code in UME::VECTOR:

//--------------------------------------------
  float a[10], b[10], c[10];

  UME::VECTOR::Vector<float, 10, 8> A(a), B(b), C(c);
  
  C = A + B;
//--------------------------------------------

Doesn't that look simpler? Let's analyze this piece of code.

The declaration of UME::VECTOR::Vector class defines 3 'computational
primitives'. Each of those primitives will represent some memory
fragment, represented also by arrays 'a','b' and 'c'. Three template
parameters are passed to this object:

- **scalar type** (float) - a type used for internal representation of each value
- **vector length** (10) - number of elements in an array.
- **SIMD stride** (8) - the maximum simd vector length that should be used by the 
                    computational engine. This parameter has to be equal or less to 
                    **vector length**. You can ommit this value to rely on library
                    supplied defaults. In some situations it might be necessary to
                    handle this value manually.


// ***************************************************************************
// II. DYNAMIC VS. STATIC VECTORS
// ***************************************************************************

Obvious problem: user might want to use length that is not known at compile time.
For convenience the library provides some defaults for the later two parameters.
It is possible to transform above piece of code into:

//--------------------------------------------
  float a[10], b[10], c[10];

  UME::VECTOR::Vector<float> A(10, a), B(10, b), C(10, c);
  
  C = A + B;
//--------------------------------------------

In this case the vectorization engine assumes some internally
predefined value for SIMD stride (might be unoptimal on some platforms).
The length of the vector can be passed as a run-time parameter, but for 
performance reasons needs to be present at vector initialization. We will
be calling these two representations of vectors:
- **static vector** or **compile time vector** for the version using templated
  vector length
- **dynamic vector** or **runtime vector** for the version with parameter passed
  during initialization.

In general static vectors can benefit more from compiler optimizations and for
that reason it is advised to use them whenever dynamic vectors are not critical.


// ***************************************************************************
// III. EXPRESSION TEMPLATE APPROACH
// ***************************************************************************

Let us now consider more advanced example which shows a true power of this library.

//--------------------------------------------
  float a[1000000], b[1000000], c[1000000], d[1000000];

  UME::VECTOR::Vector<float, 1000000, 8> A(a), B(b), C(c), D(d);
  
  D = A + B + C;
//--------------------------------------------

As mentioned before, the vector types are only computational primitives.
Let's assume that a vector is a container, similar to **std::array**.
First of all initialization would require copying of at least A, B, and C arrays. 
For very long arrays this would not only double the memory requirement of a program 
(if the stack even allows such big objects), but also mess up the cache system. 
The cache behavior would look like this:

1. load 'a' into cache, perform an iterative copy and send back to local storage of 'A'
2. load 'b' into cache, perform an iterative copy and send back to local storage of 'B'
3. load 'c' into cache, perform an iterative copy and send back to local storage of 'C'
4. load A and B to perform iterative A + B and store result in some temporary (possibly in main memory)
5. load temporary(t0) and C and perform iterative t0 + C and store result in D

Because the data arrays are so large, the data for each of them might not be available
in the cache, and would require additional memory transfer, which is more costly than the
computation carried here.

A fast implementation would do two things:
1. avoid copying the original memory to the vector containers
2. evaluate full expression for small chunks of data from A, B and C. Something like:

//--------------------------------------------
   for(i = 0 ; i < 1000000; i += SIMD_STRIDE) {
     d[i:i+SIMD_STRIDE] = a[i:i+SIMD_STRIDE] + b[i:i+SIMD_STRIDE] + c[i:i+SIMD_STRIDE];
   }
//--------------------------------------------

Because the computations carried between different indices of arrays are not dependent,
it is possible to **evaluate** full **expression** for small chunks of data, preferably
using SIMD instructions. This would limit data reads to only one per data element, and
for that reason result in better cache utilization. This is exactly what UME::VECTOR is doing!

You can try and debug through following piece of code:
//--------------------------------------------
  float a[1000000], b[1000000], c[1000000], d[1000000];

  UME::VECTOR::Vector<float, 1000000, 8> A(a), B(b), C(c), D(d); (1)
  
  auto t0 = A + B + C; (2)
  D = t0; (3)
//--------------------------------------------
What happens is as follows:
(1) Define vector primitives. No memory is copied during initialization, 
    only memory pointers are remembered in each primitive.

(2) Does not perform any run-time computation. All that is being done is
    creation of a compile-time **expression template**. Because an 'auto' variable
    is used, there is no evaluation. 

(3) Evaluation happens whenever an assignment to a vector primitive happens.
    During this phase the expression is evaluated for small chunks of the 
    data, without the user even noticing it. Due to compiler optimizations
    it is possible to exploit very high level of performance.

Usage of 'auto' in above code is critical. What the C++ language does here is
to create a recursive type:

    UME::VECTOR::ArithmeticADDExpression<float,8,
        UME::VECTOR::ArithmeticADDExpression<float,8,
            UME::VECTOR::FloatVector<float,1000000,8>,
            UME::VECTOR::FloatVector<float,1000000,8> >,
        UME::VECTOR::FloatVector<float,1000000,8>

This type essentially represents the sequence of operations that is mapped
to a 't0' object. Not going into details: this representation is necessary to
deffer actual expression evaluation until the moment when a full expression is known.
It is also possible to re-write above code into a sequence of 'auto' assignments:

//--------------------------------------------
  auto t0 = A + B;
  auto t1 = t0 + C;
  D = t1;
//--------------------------------------------

Again, the evaluation is deferred until the actual assignment to D happens. This 
splitting mechanism allows the user to perform multi-line expression construction.

// ***************************************************************************
// IV. SCALARS
// ***************************************************************************
In certain situations we would like to use some scalar variables to be mixed 
with vector variables. Consider following:

//--------------------------------------------
  float a[1000000], b[1000000], c[1000000], d[1000000];

  UME::VECTOR::Vector<float, 1000000, 8> A(a), B(b), C(c); (1)
  
  auto t0 = A*2.0f;
  auto t1 = B*3.0f;
  C = t0 + t1;
//--------------------------------------------

In order to handle the expressions containing scalars, a special wrapper type
UME::VECTOR::Scalar<float, 8> has to be created. This is necessary for the
library to handle the scalars in semanticaly correct way. From the user
perspective awareness of this type might be useful during debugging. Since this
type is an expression type, it can be used in a similar way as Vector<> type is
used at the user level:

UME::VECTOR::Scalar<float, 8> two(2.0f);

auto t0 = A*two;
...

The difference is purely syntactic.

// ***************************************************************************
// V. COMPATIBILITY WITH UME::SIMD INTERFACE
// ***************************************************************************

UME::SIMD offers a very broad spectrum of highly efficient vector operations.
These can be accessed using MFI (Member Function Interface):

//--------------------------------------------
  float a[1000000], b[1000000], c[1000000], d[1000000];

  UME::VECTOR::Vector<float, 1000000, 8> A(a), B(b), C(c);
  
  auto t0 = A.mul(2.0f); // MFI call to 'MUL'
  auto t1 = B.mul(3.0f); 
  C = t0.add(t1);        // MFI also works on all intermediate expressions
//--------------------------------------------
 
One of the reasons for existence of MFI is masking. Because masking can
reduce number of branching, it can positively affect performance. Since
in SIMD world there is no other way to perform conditional operations than
by using masking, it is also necessary for any vectorization interface.
Following example shows usage of a mask:

//--------------------------------------------
  float a[100], b[100], c[100], d[100];
  bool m[100];

  UME::VECTOR::Vector<float, 100, 8> A(a), B(b), C(c); 
  UME::VECTOR::MaskVector<100, 8> M(m); // Mask vectors use 'bool' as scalar type
  auto t0 = A.mul(m, 2.0f);
  auto t1 = B.mul(3.0f); 
  C = t0.add(m, t1);
//--------------------------------------------

Effectively above code performs:

  if(mask[i] == true)
    C[i] = A[i]*2.0f + B[i]*3.0f;
  else
    C[i] = A[i];

Mask operand is always first operand of an MFI function.

```













