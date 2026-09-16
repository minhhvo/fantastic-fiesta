// @file: "MathLibrary.hpp"
#pragma once

#include <cmath>

namespace MathLibrary
{
    class Arithmetic
    {
    public:
        // Returns a + b
        static double Add(double a, double b);

        // Returns a - b
        static double Subtract(double a, double b);

        // Returns a * b
        static double Multiply(double a, double b);

        // Returns a / b
        static double Divide(double a, double b);
    };

    class Trigonometry
    {
    public:
        
        // std::function<double(double)>
        // sin(double A)
        // {
        //     double&& fref = std::sin(A);
        //     fptr(A) = fref;
        // };

        /* Returns the floating-point, ratiometric value 
        in arbitrary length-unit of the opposite side to the hypotenuse.
        */
        static double Sine(double& A)
        {
            return std::sin(A);
        }

        /* Returns the floating-point, ratiometric value 
        in arbitrary length-unit of the adjacent side to the hypotenuse.
        */
        static double Cosine(double& B)
        {
            return std::cos(B);
        };
        
        /* Returns the floating-point, ratiometric value 
        in arbitrary length-unit of the opposite side to the adjacent side.
        */
        static double Tangent(double& H) 
        {
            return std::tan(H);
        };

        static double tan(double& A, double& B) 
        {
            return double (std::sin(A) / std::cos(B));
        };
    };
}