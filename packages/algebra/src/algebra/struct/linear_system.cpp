// File: linear_system.cpp
#include <cassert>
#include <concepts>
#include <cstdio>

#include <tgmath.h>
#include <type_traits>


/* Need to adapt the following theoretical concepts:
    - [ ]: The Euclidean space of N-dimension has a <'N-by-N Identity Matrix'>
    - [ ]: The Identity Matrix represents the identity function for whatever <'Basis'> was chosen/used
    - [ ]: A vector space can have more than one Bases, but all Bases must have the same number of elements
    - [ ]: The number of elements in any given Basis is the property <'Dimension'> | <'AlgebraicDimension'> of the Vector Space
    - [ ]: <'LinearBasis'> : <'Basis'> is a set of vectors; however, must all exhibits 'linear independence'. 
    - [ ]: <linear independence> is thus a property of LinearBasis; of which 
    "   n vectors in R^n are linearly independent **if and only if** the determinant of the matrix A, det(A),
        formed by taking the vectors as its columns is non-zero.    "
        => To find all a LinearBasis in a VectorSpace of FiniteDimension, we must:
*/

/* Commented out because clangd is not recognising-? concept; might compile though */

    // The operators +, -, *, and / for a number are assumed to follow the usual mathematical rules
    // axiom(T a, T b) { a + b == b + a; a - a == 0; a * (b + c) == a * b + a * c; /*...*/ }

namespace UnaryOperations 
{
    template<typename T>
    concept Addable = requires (T x) { x + x ; };

    template<typename T>
    concept Invertible = requires (T x) { x + (- x) = 0 ; };
};

namespace BinaryOperations
{
    template<typename T>
    concept SupportsArithmetic = requires (T a, T b)
    {
        { a + b } -> std::convertible_to<T>;
        { a * b } -> std::convertible_to<T>;
        { a - b } -> std::convertible_to<T>;
        { a / b } -> std::convertible_to<T>;
    };
    
    template<typename T>
    concept Commutable = requires (T a, T b) 
    {
        std::is_swappable<T> (a, b) &&
        assert(a + b == b + a);
    };
    
};