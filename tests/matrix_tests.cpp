#include <gtest/gtest.h>

#include <matrix.h>

TEST(MatrixTests, Addition)
{
    typedef Matrix<uint32_t, 1, 2> Matrix1x2;
    Matrix1x2 m1{{11, 0}};
    Matrix1x2 m2{{2, 3}};
    Matrix1x2 m3{m1 + m2};
    Matrix1x2 m4{{13, 3}};
    EXPECT_EQ(m4, m3);
}

TEST(MatrixTests, Subtraction)
{
    typedef Matrix<int32_t, 1, 2> MatrixFloat1x2;
    MatrixFloat1x2 m1{{11, 0}};
    MatrixFloat1x2 m2{{2, 3}};
    MatrixFloat1x2 m3{m1 - m2};
    MatrixFloat1x2 m4{{9, -3}};
    EXPECT_EQ(m4, m3);
}

TEST(MatrixTests, Transpose)
{
    typedef Matrix<int32_t, 1, 2> Matrix1x2;
    typedef Matrix<int32_t, 2, 1> Matrix2x1;
    typedef Matrix<int32_t, 2, 3> Matrix2x3;
    typedef Matrix<int32_t, 3, 2> Matrix3x2;
    Matrix1x2 m1{{11, 1}};
    Matrix2x1 m2{m1.transpose()};
    Matrix1x2 m3{m2.transpose()};
    EXPECT_EQ(m1, m3);

    typedef Matrix<uint32_t, 3, 5> Matrix3x5;
    typedef Matrix<uint32_t, 5, 3> Matrix5x3;
    Matrix5x3 m4{
        {
            {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9},
                {10, 11, 12},
                {13, 14, 15},
            }
        }
    };
    Matrix3x5 m5{m4.transpose()};
    Matrix5x3 m6{m5.transpose()};
    EXPECT_EQ(m4, m6);

    Matrix2x3 m7{
        {
            {
                {1, 2, 3},
                {0, -6, 7},
            }
        }
    };
    Matrix3x2 m8{
        {
            {
                {1, 0},
                {2, -6},
                {3, 7},
            }
        }
    };
    EXPECT_EQ(m7.transpose(), m8);
}

TEST(MatrixTests, Scalar)
{
    typedef Matrix<uint32_t, 5, 3> Matrix5x3;
    Matrix5x3 m1{
        {
            {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9},
                {10, 11, 12},
                {13, 14, 15},
            }
        }
    };
    Matrix5x3 m2{
        {
            {
                {2, 4, 6},
                {8, 10, 12},
                {14, 16, 18},
                {20, 22, 24},
                {26, 28, 30},
            }
        }
    };
    EXPECT_EQ(m1 * 2, m2);
    EXPECT_EQ(2 * m1, m2);
}

TEST(MatrixTests, Multiplication)
{
    typedef Matrix<uint32_t, 2, 3> Matrix2x3;
    typedef Matrix<uint32_t, 3, 2> Matrix3x2;
    typedef Matrix<uint32_t, 2, 2> Matrix2x2;
    Matrix2x3 A{
        {
            {
                {2, 3, 4},
                {1, 0, 0},
            }
        }
    };
    Matrix3x2 B{
        {
            {
                {0, 1000},
                {1, 100},
                {0, 10},
            }
        }
    };
    Matrix2x2 AB{
        {
            {
                {3, 2340},
                {0, 1000},
            }
        }
    };
    EXPECT_EQ(A*B, AB);
    static_assert(not std::is_same_v<decltype(A * B), decltype(B * A)>);
    Matrix2x2 C{
        {
            {
                {1, 2},
                {3, 4},
            }
        }
    };
    Matrix2x2 D{
        {
            {
                {0, 1},
                {0, 0},
            }
        }
    };
    Matrix2x2 E{
        {
            {
                {0, 1},
                {0, 3},
            }
        }
    };
    Matrix2x2 F{
        {
            {
                {3, 4},
                {0, 0},
            }
        }
    };
    EXPECT_EQ(C*D, E);
    EXPECT_NE(D*C, E);
    EXPECT_EQ(D*C, F);
    EXPECT_NE(C*D, F);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
