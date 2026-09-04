// File: shape.cpp
#include "shape.hpp"
#include <iostream>
#include <cmath>

#if defined(__cpp_lib_math_constants)
    #include <numbers>
    #define GEOMETRY_PI std::numbers::pi
#else
    #define GEOMETRY_PI M_PI
#endif

const volatile int AbstractShape::instance_count = 0;

namespace GeoObject {

// --- Polygon ---
Polygon::Polygon(const int vertices, const std::string& name)
    : num_vertices(vertices), num_edges(vertices), shape_name(name) {}

int Polygon::GetNumVertices() const { return num_vertices; }

void Polygon::SetNumVertices(const int vertices) { 
    num_vertices = vertices; 
    num_edges = vertices; // Fixed: Polygons have equal edges and vertices
}

int Polygon::GetNumEdges() const { return num_edges; }

const std::string& Polygon::GetShapeName() const { return shape_name; }
void Polygon::SetShapeName(const std::string& name) { shape_name = name; }

// --- RegularPolygon ---
RegularPolygon::RegularPolygon(const int vertices, const std::string& name) 
    : Polygon(vertices, name) {}

double RegularPolygon::GetArea() const {
    int n = GetNumEdges();
    return (n * std::pow(edge_length, 2)) / (4.0 * std::tan( GEOMETRY_PI / n));
}

double RegularPolygon::GetPerimeter() const {
    return GetNumVertices() * edge_length;
}

void RegularPolygon::SimulateShapeRepresentation() const {
    std::cout << "Simulating RegularPolygon with " << GetNumEdges() << " sides.\n";
}

// --- IrregularPolygon ---
IrregularPolygon::IrregularPolygon(const int vertices, const std::string& name) 
    : Polygon(vertices, name) {}

double IrregularPolygon::GetArea() const {
    return 0.0; // Placeholder for Shoelace Formula
}

double IrregularPolygon::GetPerimeter() const {
    return 0.0;
}

void IrregularPolygon::SimulateShapeRepresentation() const {
    std::cout << "Simulating IrregularPolygon with " << GetNumEdges() << " sides.\n";
}

} // namespace GeoObject