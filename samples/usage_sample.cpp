#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <utility>
#include <random>
#include <memory>
#include <vector>
#include <algorithm>
#include <limits>
#include "omp.h"
#include "curve_test.h"

int main(int argc, char** argv)
{
    size_t max_vec_size = 100;
    double min_distr_value = -100.0, max_distr_value = 100.0, max_positive = 100.0;
    int number_of_threads = 0;

    for (int i = 0; i < argc; ++i)
    {
        if (std::strcmp(argv[i], "-s") == 0)
        {
            max_vec_size = std::atoll(argv[++i]);
        }
        else if (std::strcmp(argv[i], "-min_d") == 0)
        {
            min_distr_value = std::atof(argv[++i]);
        }
        else if (std::strcmp(argv[i], "-max_d") == 0)
        {
            max_distr_value = std::atof(argv[++i]);
        }
        else if (std::strcmp(argv[i], "-max_p") == 0)
        {
            max_positive = std::atof(argv[++i]);
        }
        else if (std::strcmp(argv[i], "-t") == 0)
        {
            number_of_threads = std::atoi(argv[++i]);
        }
    }

    std::mt19937_64 gen_mt(std::time(nullptr));
    std::uniform_real_distribution<double> distr_ur(min_distr_value, max_distr_value);
    std::uniform_real_distribution<double> distr_positive(std::numeric_limits<double>::min(), max_positive);
    std::uniform_int_distribution<int> distr_for_type(0, 2);

    std::vector<std::shared_ptr<crv::curve>> vec;
    std::vector<std::shared_ptr<crv::circle>> circle_vec;

    // populating a vector with random parameters
    for (size_t i = 0; i < max_vec_size; ++i)
    {
        int next_type = distr_for_type(gen_mt);

        crv::point_3d centre_point{ distr_ur(gen_mt), distr_ur(gen_mt), distr_ur(gen_mt) };

        switch (next_type)
        {
        case 0: // circle
            vec.push_back(std::move(std::make_shared<crv::circle>(centre_point, distr_positive(gen_mt))));
            circle_vec.push_back(std::move(std::dynamic_pointer_cast<crv::circle>(vec.back())));
            break;
        case 1: // ellipse
            vec.push_back(std::move(std::make_shared<crv::ellipse>(centre_point, distr_positive(gen_mt), distr_positive(gen_mt))));
            break;
        case 2: // helix
            vec.push_back(std::move(std::make_shared<crv::helix>(centre_point, distr_positive(gen_mt), distr_positive(gen_mt))));
            break;
        }
    }

    // printing points and derivatives at t = pi / 4
    std::cout << "list of point coordinates for t = pi / 4:\n";
    for (const auto& i: vec)
        std::cout << i->get_point(crv::pi / 4) << ' ';
    std::cout << std::endl;
    std::cout << "list of first derivatives for t = pi / 4:\n";
    for (const auto& i: vec)
        std::cout << i->get_first_derivative(crv::pi / 4) << ' ';
    std::cout << std::endl;

    // sorting circles' container by radii
    std::sort(circle_vec.begin(), circle_vec.end(),
        [](const std::shared_ptr<crv::circle>& a, const std::shared_ptr<crv::circle>& b)->bool
        {
            if (a->get_radius() != b->get_radius())
                return a->get_radius() < b->get_radius();
            return a->get_centre() < b->get_centre();
        });

    std::cout << "list of circles\' radii after sorting:\n";
    for (const auto& i: circle_vec)
        std::cout << i->get_radius() << ' ';
    std::cout << std::endl;

    if (number_of_threads > 0)
        omp_set_num_threads(number_of_threads);

    // computing the total sum of radii
    double sum_of_radii = 0.0;
    ptrdiff_t circle_vec_size = circle_vec.size();

    #pragma omp parallel for shared(circle_vec) reduction(+: sum_of_radii)
    for (ptrdiff_t i = 0; i < circle_vec_size; ++i)
    {
        sum_of_radii += circle_vec[i]->get_radius();
    }

    std::cout << "sum of circles\' radii: " << sum_of_radii << std::endl;

    return 0;
}
