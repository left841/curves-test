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
    std::uniform_real_distribution<double> distr_positive(0, max_positive);
    std::uniform_int_distribution<int> distr_for_type(0, 2);

    std::vector<std::shared_ptr<crv::curve>> vec;
    std::vector<std::shared_ptr<crv::curve>> circle_vec;

    for (size_t i = 0; i < max_vec_size; ++i)
    {
        int next_type = distr_for_type(gen_mt);

        crv::point_3d centre_point{ distr_ur(gen_mt), distr_ur(gen_mt), distr_ur(gen_mt) };

        switch (next_type)
        {
        case 0: // circle
            vec.push_back(std::make_shared<crv::circle>(centre_point, distr_positive(gen_mt)));
            circle_vec.push_back(vec.back());
            break;
        case 1: // ellipse
            vec.push_back(std::make_shared<crv::ellipse>(centre_point, distr_positive(gen_mt), distr_positive(gen_mt)));
            break;
        case 2: // helix
            vec.push_back(std::make_shared<crv::helix>(centre_point, distr_positive(gen_mt), distr_positive(gen_mt)));
            break;
        }
    }

    for (const auto& i : vec)
        std::cout << i->get_point(crv::pi / 4) << ' ';
    std::cout << std::endl;
    for (const auto& i : vec)
        std::cout << i->get_first_derivative(crv::pi / 4) << ' ';
    std::cout << std::endl;

    std::sort(circle_vec.begin(), circle_vec.end(),
        [](const std::shared_ptr<crv::curve>& a, const std::shared_ptr<crv::curve>& b)->bool
        {
            const crv::circle* a_ptr = dynamic_cast<const crv::circle*>(a.get());
            const crv::circle* b_ptr = dynamic_cast<const crv::circle*>(b.get());

            if (a_ptr->get_radius() != b_ptr->get_radius())
                return a_ptr->get_radius() < b_ptr->get_radius();
            return a_ptr->get_centre() < b_ptr->get_centre();
        });

    std::cout << std::endl;
    for (const auto& i: circle_vec)
        std::cout << dynamic_cast<const crv::circle*>(i.get())->get_radius() << ' ';
    std::cout << std::endl;

    if (number_of_threads > 0)
        omp_set_num_threads(number_of_threads);

    double sum_of_radii = 0.0;
    ptrdiff_t circle_vec_size = circle_vec.size();

    #pragma omp parallel for shared(circle_vec) reduction(+: sum_of_radii)
    for (ptrdiff_t i = 0; i < circle_vec_size; ++i)
    {
        sum_of_radii += dynamic_cast<const crv::circle*>(circle_vec[i].get())->get_radius();
    }

    std::cout << sum_of_radii << std::endl;

    return 0;
}
