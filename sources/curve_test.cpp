#include <cmath>
#include "curve_test.h"

namespace crv
{
    point_3d::point_3d(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
    {
    }

    double point_3d::get_x() const
    {
        return x;
    }

    void point_3d::set_x(double value)
    {
        x = value;
    }

    double point_3d::get_y() const
    {
        return y;
    }

    void point_3d::set_y(double value)
    {
        y = value;
    }

    double point_3d::get_z() const
    {
        return z;
    }

    void point_3d::set_z(double value)
    {
        z = value;
    }

    point_3d point_3d::operator+(const point_3d& other) const
    {
        return point_3d{ x + other.x, y + other.y, z + other.z };
    }

    bool point_3d::operator<(const point_3d& other) const
    {
        if (x != other.x)
            return x < other.x;
        if (y != other.y)
            return y < other.y;
        return z < other.z;
    }

    std::ostream& operator<<(std::ostream& out, const point_3d& point)
    {
        return out << '{' << point.get_x() << ',' << point.get_y() << ',' << point.get_z() << '}';
    }

    vector_3d::vector_3d(const point_3d& _initial, const point_3d& _terminal) : initial(_initial), terminal(_terminal)
    {
    }

    const point_3d& vector_3d::get_initial() const
    {
        return initial;
    }

    void vector_3d::set_initial(const point_3d& value)
    {
        initial = value;
    }

    const point_3d& vector_3d::get_terminal() const
    {
        return terminal;
    }

    void vector_3d::set_terminal(const point_3d& value)
    {
        terminal = value;
    }

    double vector_3d::magnitude() const
    {
        return std::sqrt((terminal.get_x() - initial.get_x()) * (terminal.get_x() - initial.get_x()) +
            (terminal.get_y() - initial.get_y()) * (terminal.get_y() - initial.get_y()) +
            (terminal.get_z() - initial.get_z()) * (terminal.get_z() - initial.get_z()));
    }

    std::ostream& operator<<(std::ostream& out, const vector_3d& vect)
    {
        return out << '{' << vect.get_initial() << ',' << vect.get_terminal() << '}';
    }

    circle::circle(double _radius): curve(), centre({ 0.0, 0.0, 0.0 }), radius(_radius)
    {
    }

    circle::circle(const point_3d& _centre, double _radius): curve(), centre(_centre), radius(_radius)
    {
    }

    point_3d circle::get_point(double t) const
    {
        point_3d result(radius * std::cos(t), radius * std::sin(t), 0.0);
        return result + centre;
    }

    point_3d circle::get_first_derivative(double t) const
    {
        return { -radius * std::sin(t), radius * std::cos(t), 0.0 };
    }

    vector_3d circle::get_derivative_vector(double t) const
    {
        point_3d init_point = get_point(t);
        return vector_3d{ init_point, init_point + get_first_derivative(t) };
    }

    const point_3d& circle::get_centre() const
    {
        return centre;
    }

    void circle::set_centre(const point_3d& value)
    {
        centre = value;
    }

    double circle::get_radius() const
    {
        return radius;
    }

    void circle::set_radius(double value)
    {
        radius = value;
    }

    ellipse::ellipse(double _radius_x, double _radius_y): curve(), centre({ 0.0, 0.0, 0.0 }), radius_x(_radius_x), radius_y(_radius_y)
    {
    }

    ellipse::ellipse(const point_3d& _centre, double _radius_x, double _radius_y): curve(), centre(_centre), radius_x(_radius_x), radius_y(_radius_y)
    {
    }

    point_3d ellipse::get_point(double t) const
    {
        point_3d result(radius_x * std::cos(t), radius_y * std::sin(t), 0.0);
        return result + centre;
    }

    point_3d ellipse::get_first_derivative(double t) const
    {
        return { -radius_x * std::sin(t), radius_y * std::cos(t), 0.0 };
    }

    vector_3d ellipse::get_derivative_vector(double t) const
    {
        point_3d init_point = get_point(t);
        return vector_3d{ init_point, init_point + get_first_derivative(t) };
    }

    const point_3d& ellipse::get_centre() const
    {
        return centre;
    }

    void ellipse::set_centre(const point_3d& value)
    {
        centre = value;
    }

    double ellipse::get_radius_x() const
    {
        return radius_x;
    }

    void ellipse::set_radius_x(double value)
    {
        radius_x = value;
    }

    double ellipse::get_radius_y() const
    {
        return radius_y;
    }

    void ellipse::set_radius_y(double value)
    {
        radius_y = value;
    }

    helix::helix(double _radius, double _step): curve(), centre({ 0.0, 0.0, 0.0 }), radius(_radius), step(_step)
    {
    }

    helix::helix(const point_3d& _centre, double _radius, double _step): curve(), centre(_centre), radius(_radius), step(_step)
    {
    }

    point_3d helix::get_point(double t) const
    {
        point_3d result(radius * std::cos(t), radius * std::sin(t), step * t / 2 / pi);
        return result + centre;
    }

    point_3d helix::get_first_derivative(double t) const
    {
        return { -radius * std::sin(t), radius * std::cos(t), step / 2 / pi };
    }

    vector_3d helix::get_derivative_vector(double t) const
    {
        point_3d init_point = get_point(t);
        return vector_3d{ init_point, init_point + get_first_derivative(t) };
    }

    const point_3d& helix::get_centre() const
    {
        return centre;
    }

    void helix::set_centre(const point_3d& value)
    {
        centre = value;
    }

    double helix::get_radius() const
    {
        return radius;
    }

    void helix::set_radius(double value)
    {
        radius = value;
    }

    double helix::get_step() const
    {
        return step;
    }

    void helix::set_step(double value)
    {
        step = value;
    }
}
