#include <tuple>
#include <gtest/gtest.h>
#include <fp_comparison.h>

namespace {

class FPCompTest1 : public ::testing::Test
{
protected:
    //virtual void SetUp() override {}
    //virtual void TearDown() override {}

    bool IsConsistent(float a, float b)
    {
        /*
            case [eq] [abs] [rel] [gt] [lt] [gte] [lte]
            (1)   0    0     0     0    1    0     1
            (2)   0    0     0     1    0    1     0
            (3)   1    0     1     0    0    1     1
            (4)   1    1     0     0    0    1     1
            (5)   1    1     1     0    0    1     1
        */
        const auto eq  = IsApproximatelyEqualTo(a, b, ABS_TOLERANCE, REL_TOLERANCE);
        const auto abs = AreCloseWithinAbsoluteTolerance(a, b, ABS_TOLERANCE);
        const auto rel = AreCloseWithinRelativeTolerance(a, b, REL_TOLERANCE);
        const auto gt  = IsDefinitelyGreaterThan(a, b, ABS_TOLERANCE, REL_TOLERANCE);
        const auto lt  = IsDefinitelyLessThan(a, b, ABS_TOLERANCE, REL_TOLERANCE);
        const auto gte = IsGreaterThanOrApproximatelyEqualTo(a, b, ABS_TOLERANCE, REL_TOLERANCE);
        const auto lte = IsLessThanOrApproximatelyEqualTo(a, b, ABS_TOLERANCE, REL_TOLERANCE);

        if(eq){
            return (abs || rel) && !gt && !lt && gte && lte;
        }
        else if(gt){
            return !abs && !rel && !lt && gte && !lte;
        }
        else if(lt){
            return !abs && !rel && !gt && !gte && lte;
        }
        return false;
    }

protected:
    const float ABS_TOLERANCE = 1e-7f;
    const float REL_TOLERANCE = 1e-6f;   // 1e-5f > rel > 1e-6f

    enum class DataElement{
        LHS,
        RHS,
        AreCloseWithinAbsoluteTolerance,
        AreCloseWithinRelativeTolerance,
        IsApproximatelyEqualTo,
        IsDefinitelyGreaterThan,
        IsDefinitelyLessThan,
        IsGreaterThanOrApproximatelyEqualTo,
        IsLessThanOrApproximatelyEqualTo
    };
    using Data = std::tuple<float, float, bool, bool, bool, bool, bool, bool, bool>;

    const Data data[7] = {
        //              LHS,       RHS,        ABS,   REL,   ==,    >,     <,     >=.    <=
        std::make_tuple(0.000000f, 0.0000001f, true,  false, true,  false, false, true,  true ),
        std::make_tuple(1.000000f, 1.000001f,  false, true,  true,  false, false, true,  true ),
        std::make_tuple(10.00000f, 10.00001f,  false, true,  true,  false, false, true,  true ),
        std::make_tuple(100.0000f, 100.0001f,  false, true,  true,  false, false, true,  true ),
        std::make_tuple(1000.000f, 1000.001f,  false, true,  true,  false, false, true,  true ),
        std::make_tuple(10000.00f, 10000.01f,  false, true,  true,  false, false, true,  true ),
        //std::make_tuple(100000.0f, 100000.1f,  false, true,  true,  false, false, true,  true),
        std::make_tuple(100000.0f, 100000.1f,  false, false, false, false, true,  false, true )
    };
};

TEST_F(FPCompTest1, AreCloseWithinAbsoluteTolerance)
{
    constexpr auto lhs = static_cast<std::underlying_type<DataElement>::type>(DataElement::LHS);
    constexpr auto rhs = static_cast<std::underlying_type<DataElement>::type>(DataElement::RHS);
    constexpr auto tc  = static_cast<std::underlying_type<DataElement>::type>(DataElement::AreCloseWithinAbsoluteTolerance);

    auto target = &data[0];
    EXPECT_EQ(std::get<tc>(*target), AreCloseWithinAbsoluteTolerance(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE));
    target = &data[1];
    EXPECT_EQ(std::get<tc>(*target), AreCloseWithinAbsoluteTolerance(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE));
    target = &data[2];
    EXPECT_EQ(std::get<tc>(*target), AreCloseWithinAbsoluteTolerance(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE));
    target = &data[3];
    EXPECT_EQ(std::get<tc>(*target), AreCloseWithinAbsoluteTolerance(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE));
    target = &data[4];
    EXPECT_EQ(std::get<tc>(*target), AreCloseWithinAbsoluteTolerance(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE));
    target = &data[5];
    EXPECT_EQ(std::get<tc>(*target), AreCloseWithinAbsoluteTolerance(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE));
    target = &data[6];
    EXPECT_EQ(std::get<tc>(*target), AreCloseWithinAbsoluteTolerance(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE));
}

TEST_F(FPCompTest1, AreCloseWithinRelativeTolerance)
{
    constexpr auto lhs = static_cast<std::underlying_type<DataElement>::type>(DataElement::LHS);
    constexpr auto rhs = static_cast<std::underlying_type<DataElement>::type>(DataElement::RHS);
    constexpr auto tc = static_cast<std::underlying_type<DataElement>::type>(DataElement::AreCloseWithinRelativeTolerance);

    auto target = &data[0];
    EXPECT_EQ(std::get<tc>(*target), AreCloseWithinRelativeTolerance(std::get<lhs>(*target), std::get<rhs>(*target), REL_TOLERANCE));
    target = &data[1];
    EXPECT_EQ(std::get<tc>(*target), AreCloseWithinRelativeTolerance(std::get<lhs>(*target), std::get<rhs>(*target), REL_TOLERANCE));
    target = &data[2];
    EXPECT_EQ(std::get<tc>(*target), AreCloseWithinRelativeTolerance(std::get<lhs>(*target), std::get<rhs>(*target), REL_TOLERANCE));
    target = &data[3];
    EXPECT_EQ(std::get<tc>(*target), AreCloseWithinRelativeTolerance(std::get<lhs>(*target), std::get<rhs>(*target), REL_TOLERANCE));
    target = &data[4];
    EXPECT_EQ(std::get<tc>(*target), AreCloseWithinRelativeTolerance(std::get<lhs>(*target), std::get<rhs>(*target), REL_TOLERANCE));
    target = &data[5];
    EXPECT_EQ(std::get<tc>(*target), AreCloseWithinRelativeTolerance(std::get<lhs>(*target), std::get<rhs>(*target), REL_TOLERANCE));
    target = &data[6];
    EXPECT_EQ(std::get<tc>(*target), AreCloseWithinRelativeTolerance(std::get<lhs>(*target), std::get<rhs>(*target), REL_TOLERANCE));
}

TEST_F(FPCompTest1, IsApproximatelyEqualTo)
{
    constexpr auto lhs = static_cast<std::underlying_type<DataElement>::type>(DataElement::LHS);
    constexpr auto rhs = static_cast<std::underlying_type<DataElement>::type>(DataElement::RHS);
    constexpr auto tc = static_cast<std::underlying_type<DataElement>::type>(DataElement::IsApproximatelyEqualTo);

    auto target = &data[0];
    EXPECT_EQ(std::get<tc>(*target), IsApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[1];
    EXPECT_EQ(std::get<tc>(*target), IsApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[2];
    EXPECT_EQ(std::get<tc>(*target), IsApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[3];
    EXPECT_EQ(std::get<tc>(*target), IsApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[4];
    EXPECT_EQ(std::get<tc>(*target), IsApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[5];
    EXPECT_EQ(std::get<tc>(*target), IsApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[6];
    EXPECT_EQ(std::get<tc>(*target), IsApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
}

TEST_F(FPCompTest1, IsDefinitelyGreaterThan)
{
    constexpr auto lhs = static_cast<std::underlying_type<DataElement>::type>(DataElement::LHS);
    constexpr auto rhs = static_cast<std::underlying_type<DataElement>::type>(DataElement::RHS);
    constexpr auto tc = static_cast<std::underlying_type<DataElement>::type>(DataElement::IsDefinitelyGreaterThan);

    auto target = &data[0];
    EXPECT_EQ(std::get<tc>(*target), IsDefinitelyGreaterThan(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[1];
    EXPECT_EQ(std::get<tc>(*target), IsDefinitelyGreaterThan(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[2];
    EXPECT_EQ(std::get<tc>(*target), IsDefinitelyGreaterThan(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[3];
    EXPECT_EQ(std::get<tc>(*target), IsDefinitelyGreaterThan(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[4];
    EXPECT_EQ(std::get<tc>(*target), IsDefinitelyGreaterThan(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[5];
    EXPECT_EQ(std::get<tc>(*target), IsDefinitelyGreaterThan(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[6];
    EXPECT_EQ(std::get<tc>(*target), IsDefinitelyGreaterThan(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
}

TEST_F(FPCompTest1, IsDefinitelyLessThan)
{
    constexpr auto lhs = static_cast<std::underlying_type<DataElement>::type>(DataElement::LHS);
    constexpr auto rhs = static_cast<std::underlying_type<DataElement>::type>(DataElement::RHS);
    constexpr auto tc = static_cast<std::underlying_type<DataElement>::type>(DataElement::IsDefinitelyLessThan);

    auto target = &data[0];
    EXPECT_EQ(std::get<tc>(*target), IsDefinitelyLessThan(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[1];
    EXPECT_EQ(std::get<tc>(*target), IsDefinitelyLessThan(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[2];
    EXPECT_EQ(std::get<tc>(*target), IsDefinitelyLessThan(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[3];
    EXPECT_EQ(std::get<tc>(*target), IsDefinitelyLessThan(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[4];
    EXPECT_EQ(std::get<tc>(*target), IsDefinitelyLessThan(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[5];
    EXPECT_EQ(std::get<tc>(*target), IsDefinitelyLessThan(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[6];
    EXPECT_EQ(std::get<tc>(*target), IsDefinitelyLessThan(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
}

TEST_F(FPCompTest1, IsGreaterThanOrApproximatelyEqualTo)
{
    constexpr auto lhs = static_cast<std::underlying_type<DataElement>::type>(DataElement::LHS);
    constexpr auto rhs = static_cast<std::underlying_type<DataElement>::type>(DataElement::RHS);
    constexpr auto tc = static_cast<std::underlying_type<DataElement>::type>(DataElement::IsGreaterThanOrApproximatelyEqualTo);

    auto target = &data[0];
    EXPECT_EQ(std::get<tc>(*target), IsGreaterThanOrApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[1];
    EXPECT_EQ(std::get<tc>(*target), IsGreaterThanOrApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[2];
    EXPECT_EQ(std::get<tc>(*target), IsGreaterThanOrApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[3];
    EXPECT_EQ(std::get<tc>(*target), IsGreaterThanOrApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[4];
    EXPECT_EQ(std::get<tc>(*target), IsGreaterThanOrApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[5];
    EXPECT_EQ(std::get<tc>(*target), IsGreaterThanOrApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[6];
    EXPECT_EQ(std::get<tc>(*target), IsGreaterThanOrApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
}

TEST_F(FPCompTest1, IsLessThanOrApproximatelyEqualTo)
{
    constexpr auto lhs = static_cast<std::underlying_type<DataElement>::type>(DataElement::LHS);
    constexpr auto rhs = static_cast<std::underlying_type<DataElement>::type>(DataElement::RHS);
    constexpr auto tc = static_cast<std::underlying_type<DataElement>::type>(DataElement::IsLessThanOrApproximatelyEqualTo);

    auto target = &data[0];
    EXPECT_EQ(std::get<tc>(*target), IsLessThanOrApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[1];
    EXPECT_EQ(std::get<tc>(*target), IsLessThanOrApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[2];
    EXPECT_EQ(std::get<tc>(*target), IsLessThanOrApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[3];
    EXPECT_EQ(std::get<tc>(*target), IsLessThanOrApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[4];
    EXPECT_EQ(std::get<tc>(*target), IsLessThanOrApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[5];
    EXPECT_EQ(std::get<tc>(*target), IsLessThanOrApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
    target = &data[6];
    EXPECT_EQ(std::get<tc>(*target), IsLessThanOrApproximatelyEqualTo(std::get<lhs>(*target), std::get<rhs>(*target), ABS_TOLERANCE, REL_TOLERANCE));
}

TEST_F(FPCompTest1, IsConsistent)
{
    constexpr auto lhs = static_cast<std::underlying_type<DataElement>::type>(DataElement::LHS);
    constexpr auto rhs = static_cast<std::underlying_type<DataElement>::type>(DataElement::RHS);

    auto target = &data[0];
    EXPECT_EQ(true, IsConsistent(std::get<lhs>(*target), std::get<rhs>(*target)));
    target = &data[1];
    EXPECT_EQ(true, IsConsistent(std::get<lhs>(*target), std::get<rhs>(*target)));
    target = &data[2];
    EXPECT_EQ(true, IsConsistent(std::get<lhs>(*target), std::get<rhs>(*target)));
    target = &data[3];
    EXPECT_EQ(true, IsConsistent(std::get<lhs>(*target), std::get<rhs>(*target)));
    target = &data[4];
    EXPECT_EQ(true, IsConsistent(std::get<lhs>(*target), std::get<rhs>(*target)));
    target = &data[5];
    EXPECT_EQ(true, IsConsistent(std::get<lhs>(*target), std::get<rhs>(*target)));
    target = &data[6];
    EXPECT_EQ(true, IsConsistent(std::get<lhs>(*target), std::get<rhs>(*target)));
}

}