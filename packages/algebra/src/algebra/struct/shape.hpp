// File: shape.h
// target C++ version: 20
#pragma once
#include <string>


class AbstractShape /* Abstract class for geometric shapes; Base class is Polygon for all shapes */
{
private:
    int num_faces; // Should strictly-equal the dimension of the space it locates within

protected:
    std::string base = "Shape"; // Name of the shape, default is "Shape"
    const volatile static int instance_count; // Static member to keep track of the number of Concrete Shape subclasses and their instances

public:
    virtual ~AbstractShape() = default; // Virtual destructor to ensure proper cleanup of derived classes

    virtual double GetArea() const = 0;
    virtual double GetPerimeter() const = 0;
    
    virtual void SimulateShapeRepresentation() const = 0;

};

namespace GeoObject {

class Polygon : public AbstractShape {
protected:
    int num_vertices;
    int num_edges;
    std::string shape_name;

public:
    Polygon(const int vertices, const std::string& name);
    ~Polygon() override = default;

    int GetNumVertices() const;
    void SetNumVertices(const int vertices);
    
    int GetNumEdges() const;
    
    const std::string& GetShapeName() const;
    void SetShapeName(const std::string& name);
};

class RegularPolygon : public Polygon {
protected:
    const double edge_length = 1.0;

public:
    RegularPolygon(const int vertices, const std::string& name);
    ~RegularPolygon() override = default;
    
    double GetArea() const override;
    double GetPerimeter() const override;
    void SimulateShapeRepresentation() const override;
};

class IrregularPolygon : public Polygon {
public:
    IrregularPolygon(const int vertices, const std::string& name);
    ~IrregularPolygon() override = default;

    double GetArea() const override;
    double GetPerimeter() const override;
    void SimulateShapeRepresentation() const override;
};

} // namespace GeoObject