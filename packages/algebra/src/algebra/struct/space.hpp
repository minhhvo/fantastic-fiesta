// File: space.hpp
#pragma once
#include <vector>

class FiniteDimSpace {
private:
    int dim;
    FiniteDimSpace(int dimension) : dim(dimension) {}

public:
    static FiniteDimSpace& getInstance(int dimension = 3) {
        static FiniteDimSpace instance(dimension);
        return instance;
    }

    FiniteDimSpace(const FiniteDimSpace&) = delete;
    FiniteDimSpace& operator=(const FiniteDimSpace&) = delete;

    int dimensionality() const { return dim; }
};

class Point {
private:
    int ordered_norm;
    std::vector<double> coordinates; // Safely handles its own memory

public:
    Point(const int n = 0) : ordered_norm(n) {
        int space_dim = FiniteDimSpace::getInstance().dimensionality();
        coordinates.resize(space_dim, 0.0);
    }
    ~Point() = default;
};

class GeoObjectFactory {
public:
    GeoObjectFactory() = default;
    GeoObjectFactory(const GeoObjectFactory&) = delete;
    GeoObjectFactory& operator=(const GeoObjectFactory&) = delete;

    Point createOrigin() const { return Point(); }
};