// File: main.cpp
#include <iostream>

#include "shape.hpp"
#include "algebra.hpp" 


// --- 1. Algebra Testing Suite ---
void test_linear_algebra() 
{
    std::cout << "--- Testing Algebra ---" << std::endl;

    // 1. Define 'x' in the Domain (e.g., a 2D Point)
    ColumnVector<2> x = {4.0, 0.0}; 

    // 2. Define 'A' (e.g., A Transformation mapping 2D -> 3D)
    // 3 Rows (Range), 2 Columns (Domain)
    Matrix<3, 2> A = {
        {1.0, 2.0},
        {0.0, 1.0},
        {1.0, 1.0}
    };

    // 3. Execute the Transformation (Ax = b)
    auto b = A * x;

    std::cout << "Mapped to 3D Range (b): " 
              << b[0] << ", " << b[1] << ", " << b[2] << "\n\n";
}

// --- 2. Geometry Testing Suite ---
void test_geometry() 
{
    std::cout << "--- Testing Geometry ---" << std::endl;
    using namespace GeoObject;
    
    // Create a polygon with 4 sides and the name "Rectangle"
    RegularPolygon rectangle(4, "Rectangle");

    // Check number of sides
    std::cout << rectangle.GetShapeName() << " has " 
              << rectangle.GetNumVertices() << " sides." << std::endl;

    // Change number of sides to 3 and rename to "Triangle"
    rectangle.SetNumVertices(3);
    rectangle.SetShapeName("Triangle");

    std::cout << rectangle.GetShapeName() << " now has " 
              << rectangle.GetNumVertices() << " sides." << std::endl;
}


int main(int argc, char *argv[]) 
{
    std::cout << "Starting Engine Tests...\n\n";
    
    test_linear_algebra();
    test_geometry();

    std::cout << "\nAll tests completed successfully." << std::endl;
    
    return 0;
}