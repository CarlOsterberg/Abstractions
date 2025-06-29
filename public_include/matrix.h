#ifndef MATRICES_LIBRARY_H
#define MATRICES_LIBRARY_H

#include <array>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <type_traits>

template <typename T>
concept Number = std::is_arithmetic_v<T>;
template <Number T, uint32_t M, uint32_t N>
class Matrix
{
    static_assert(std::is_arithmetic_v<T>);

public:
    Matrix() : m_matrix(std::array<std::array<T, M>, N>{})
    {
    }

    Matrix(std::array<std::array<T, M>, N> a_matrix) : m_matrix(a_matrix)
    {
    }

    void print()
    {
        std::stringstream ss;
        ss << std::to_string(M) << " x " << std::to_string(N) << '\n';
        for (uint32_t m = 0; m < M; m++)
        {
            for (uint32_t n = 0; n < N; n++)
            {
                if (n == 0)
                {
                    ss << '|';
                }
                else
                {
                    ss << '\t';
                }
                ss << std::to_string(m_matrix[n][m]);
                if (n == N - 1)
                {
                    ss << '|';
                }
            }
            ss << '\n';
        }
        std::cout << ss.str();
    }

    constexpr bool operator==(const Matrix& rhs) const
    {
        for (uint32_t m = 0; m < M; m++)
        {
            for (uint32_t n = 0; n < N; n++)
            {
                if (m_matrix[n][m] != rhs.m_matrix[n][m])
                {
                    return false;
                }
            }
        }
        return true;
    }

    constexpr bool operator!=(const Matrix& rhs) const
    {
        return not (*this == rhs);
    }

    constexpr Matrix operator+(const Matrix& rhs) const
    {
        Matrix matrix;
        for (uint32_t m = 0; m < M; m++)
        {
            for (uint32_t n = 0; n < N; n++)
            {
                matrix.m_matrix[n][m] = m_matrix[n][m] + rhs.m_matrix[n][m];
            }
        }
        return std::move(matrix);
    }

    constexpr Matrix operator-(const Matrix& rhs) const
    {
        Matrix matrix;
        for (uint32_t m = 0; m < M; m++)
        {
            for (uint32_t n = 0; n < N; n++)
            {
                matrix.m_matrix[n][m] = m_matrix[n][m] - rhs.m_matrix[n][m];
            }
        }
        return std::move(matrix);
    }

    constexpr Matrix<T, N, M> transpose() const
    {
        std::array<std::array<T, N>, M> array;
        for (uint32_t m = 0; m < M; m++)
        {
            for (uint32_t n = 0; n < N; n++)
            {
                array[m][n] = m_matrix[n][m];
            }
        }
        return {array};
    }

    constexpr Matrix operator*(T scalar) const
    {
        std::array<std::array<T, M>, N> array;
        for (uint32_t m = 0; m < M; m++)
        {
            for (uint32_t n = 0; n < N; n++)
            {
                array[n][m] = m_matrix[n][m] * scalar;
            }
        }
        return {array};
    }

    friend constexpr Matrix operator*(T scalar, Matrix matrix)
    {
        std::array<std::array<T, M>, N> array;
        for (uint32_t m = 0; m < M; m++)
        {
            for (uint32_t n = 0; n < N; n++)
            {
                array[n][m] = matrix.m_matrix[n][m] * scalar;
            }
        }
        return {array};
    }

private:
    std::array<std::array<T, M>, N> m_matrix;
};

#endif //MATRICES_LIBRARY_H
