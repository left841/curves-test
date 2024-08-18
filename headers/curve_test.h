#ifndef __CURVE_TEST_H__
#define __CURVE_TEST_H__

#include <iostream>

#ifdef _WIN32
#ifdef curves_EXPORTS
#define DYN_POLICY __declspec(dllexport)
#else
#define DYN_POLICY __declspec(dllimport)
#endif // curves_EXPORTS
#else
#define DYN_POLICY
#endif // _WIN32

namespace crv
{
    const double pi = 3.14159265358979323846;

    class DYN_POLICY point_3d
    {
    private:
        double x = 0.0, y = 0.0, z = 0.0;

    public:
        point_3d() = default;
        point_3d(const point_3d& src) = default;
        point_3d& operator=(const point_3d& src) = default;
        point_3d(point_3d&& src) noexcept = default;
        point_3d& operator=(point_3d&& src) noexcept = default;
        ~point_3d() = default;
        point_3d(double _x, double _y, double _z);

        double get_x() const;
        void set_x(double value);
        double get_y() const;
        void set_y(double value);
        double get_z() const;
        void set_z(double value);

        point_3d operator+(const point_3d& other) const;
        bool operator<(const point_3d& other) const;
    };

    DYN_POLICY std::ostream& operator<<(std::ostream& out, const point_3d& point);

    class DYN_POLICY vector_3d
    {
    private:
        point_3d initial, terminal;

    public:
        vector_3d() = default;
        vector_3d(const vector_3d& src) = default;
        vector_3d& operator=(const vector_3d& src) = default;
        vector_3d(vector_3d&& src) noexcept = default;
        vector_3d& operator=(vector_3d&& src) noexcept = default;
        ~vector_3d() = default;
        vector_3d(const point_3d& _initial, const point_3d& _terminal);

        const point_3d& get_initial() const;
        void set_initial(const point_3d& value);
        const point_3d& get_terminal() const;
        void set_terminal(const point_3d& value);

        double magnitude() const;
    };

    DYN_POLICY std::ostream& operator<<(std::ostream& out, const vector_3d& vect);

    class DYN_POLICY curve
    {
    public:
        virtual ~curve() = default;

        virtual point_3d get_point(double t) const = 0;
        virtual point_3d get_first_derivative(double t) const = 0;
        virtual vector_3d get_derivative_vector(double t) const = 0;
    };

    class DYN_POLICY circle: public curve
    {
    private:
        point_3d centre;
        double radius = 0.0;

    public:
        circle() = default;
        circle(const circle& src) = default;
        circle& operator=(const circle& src) = default;
        circle(circle&& src) noexcept = default;
        circle& operator=(circle&& src) noexcept = default;
        ~circle() = default;
        explicit circle(double _radius);
        circle(const point_3d& _centre, double _radius);

        point_3d get_point(double t) const override;
        point_3d get_first_derivative(double t) const override;
        vector_3d get_derivative_vector(double t) const override;

        const point_3d& get_centre() const;
        void set_centre(const point_3d& value);
        double get_radius() const;
        void set_radius(double value);
    };

    class DYN_POLICY ellipse: public curve
    {
    private:
        point_3d centre;
        double radius_x = 0.0, radius_y = 0.0;

    public:
        ellipse() = default;
        ellipse(const ellipse& src) = default;
        ellipse& operator=(const ellipse& src) = default;
        ellipse(ellipse&& src) noexcept = default;
        ellipse& operator=(ellipse&& src) noexcept = default;
        ~ellipse() = default;
        ellipse(double _radius_x, double _radius_y);
        ellipse(const point_3d& _centre, double _radius_x, double _radius_y);

        point_3d get_point(double t) const override;
        point_3d get_first_derivative(double t) const override;
        vector_3d get_derivative_vector(double t) const override;

        const point_3d& get_centre() const;
        void set_centre(const point_3d& value);
        double get_radius_x() const;
        void set_radius_x(double value);
        double get_radius_y() const;
        void set_radius_y(double value);
    };

    class DYN_POLICY helix: public curve
    {
    private:
        point_3d centre;
        double radius = 0.0, step = 0.0;

    public:
        helix() = default;
        helix(const helix& src) = default;
        helix& operator=(const helix& src) = default;
        helix(helix&& src) noexcept = default;
        helix& operator=(helix&& src) noexcept = default;
        ~helix() = default;
        helix(double _radius, double _step);
        helix(const point_3d& _centre, double _radius, double _step);

        point_3d get_point(double t) const override;
        point_3d get_first_derivative(double t) const override;
        vector_3d get_derivative_vector(double t) const override;

        const point_3d& get_centre() const;
        void set_centre(const point_3d& value);
        double get_radius() const;
        void set_radius(double value);
        double get_step() const;
        void set_step(double value);
    };
}

#endif // __CURVE_TEST_H__
