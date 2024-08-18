#include "gtest/gtest.h"
#include "curve_test.h"

TEST(curve_tests, circle_point_per_param)
{
    crv::circle test_curve(5.0);

    crv::point_3d test_point(test_curve.get_point(1.3));

    ASSERT_NEAR(test_point.get_x(), 1.337494143, 0.000001);
    ASSERT_NEAR(test_point.get_y(), 4.817790927, 0.000001);
    ASSERT_NEAR(test_point.get_z(), 0, 0.000001);
}

TEST(curve_tests, circle_derivative_per_param)
{
    crv::circle test_curve(5.0);

    crv::point_3d test_point(test_curve.get_first_derivative(1.3));

    ASSERT_NEAR(test_point.get_x(), -4.817790927, 0.000001);
    ASSERT_NEAR(test_point.get_y(), 1.337494143, 0.000001);
    ASSERT_NEAR(test_point.get_z(), 0, 0.000001);
}

TEST(curve_tests, ellipse_point_per_param)
{
    crv::ellipse test_curve(8.0, 20.0);

    crv::point_3d test_point(test_curve.get_point(1.3));

    ASSERT_NEAR(test_point.get_x(), 2.139990628, 0.000001);
    ASSERT_NEAR(test_point.get_y(), 19.271163708, 0.000001);
    ASSERT_NEAR(test_point.get_z(), 0, 0.000001);
}

TEST(curve_tests, ellipse_derivative_per_param)
{
    crv::ellipse test_curve(8.0, 20.0);

    crv::point_3d test_point(test_curve.get_first_derivative(1.3));

    ASSERT_NEAR(test_point.get_x(), -7.708465483, 0.000001);
    ASSERT_NEAR(test_point.get_y(), 5.349976572, 0.000001);
    ASSERT_NEAR(test_point.get_z(), 0, 0.000001);
}

TEST(curve_tests, helix_point_per_param)
{
    crv::helix test_curve(5.0, 6.0);

    crv::point_3d test_point(test_curve.get_point(1.3));

    ASSERT_NEAR(test_point.get_x(), 1.337494143, 0.000001);
    ASSERT_NEAR(test_point.get_y(), 4.817790927, 0.000001);
    ASSERT_NEAR(test_point.get_z(), 1.241408556, 0.000001);
}

TEST(curve_tests, helix_derivative_per_param)
{
    crv::helix test_curve(5.0, 6.0);

    crv::point_3d test_point(test_curve.get_first_derivative(1.3));

    ASSERT_NEAR(test_point.get_x(), -4.817790927, 0.000001);
    ASSERT_NEAR(test_point.get_y(), 1.337494143, 0.000001);
    ASSERT_NEAR(test_point.get_z(), 0.954929658, 0.000001);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}