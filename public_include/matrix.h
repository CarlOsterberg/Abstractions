/**
 * @file matrix.h
 * @brief Implementation of a mathematical matrix and its operations.
 */

#ifndef MATRICES_LIBRARY_H
#define MATRICES_LIBRARY_H

#include <array>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <type_traits>

/**
 * @class Matrix
 * @brief MxN matrix implementation for arithmetic c++ types.
 */
template <typename T>
concept Number = std::is_arithmetic_v<T>;

template <Number T, uint32_t M, uint32_t N>
class Matrix
{
public:
    /**
    * @brief Empty matrix constructor.
    */
    Matrix() : m_matrix(std::array<std::array<T, N>, M>{})
    {
    }

    /**
    * @brief Predefined matrix constructor.
    * @param a_matrix Array to construct a matrix out of.
    */
    Matrix(std::array<std::array<T, N>, M> a_matrix) : m_matrix(a_matrix) // NOLINT
    {
    }

    /**
    * @brief Print a formatted string of the matrix.
    */
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
                ss << std::to_string(m_matrix[m][n]);
                if (n == N - 1)
                {
                    ss << '|';
                }
            }
            ss << '\n';
        }
        std::cout << ss.str();
    }

    /**
    * @brief Boolean equals implementation for a matrix.
    * @param a_rhs other matrix to compare.
    * @returns true if all elements at the same indexes match.
    */
    constexpr bool operator==(const Matrix& a_rhs) const
    {
        for (uint32_t m = 0; m < M; m++)
        {
            for (uint32_t n = 0; n < N; n++)
            {
                if (m_matrix[m][n] != a_rhs.m_matrix[m][n])
                {
                    return false;
                }
            }
        }
        return true;
    }

    /**
    * @brief Boolean not equals implementation for a matrix.
    * @param a_rhs other matrix to compare.
    * @returns true if any element at the same indexes doesn't match.
    */
    constexpr bool operator!=(const Matrix& a_rhs) const
    {
        return not(*this == a_rhs);
    }

    /**
    * @brief Matrix addition implementation.
    * @param a_rhs other matrix to add.
    * @returns a matrix where each index has the values added together.
    */
    constexpr Matrix operator+(const Matrix& a_rhs) const
    {
        Matrix matrix;
        for (uint32_t m = 0; m < M; m++)
        {
            for (uint32_t n = 0; n < N; n++)
            {
                matrix.m_matrix[m][n] = m_matrix[m][n] + a_rhs.m_matrix[m][n];
            }
        }
        return std::move(matrix);
    }

    /**
    * @brief Matrix subtraction implementation.
    * @param a_rhs other matrix to subtract.
    * @returns a matrix where each index has rhs subtracted from rhs.
    */
    constexpr Matrix operator-(const Matrix& a_rhs) const
    {
        Matrix matrix;
        for (uint32_t m = 0; m < M; m++)
        {
            for (uint32_t n = 0; n < N; n++)
            {
                matrix.m_matrix[m][n] = m_matrix[m][n] - a_rhs.m_matrix[m][n];
            }
        }
        return std::move(matrix);
    }

    /**
    * @brief Matrix transpose implementation.
    * @returns a transposed matrix where the dimensions have been swapped from MxN to NxM.
    */
    constexpr Matrix<T, N, M> transpose() const
    {
        std::array<std::array<T, M>, N> array{};
        for (uint32_t m = 0; m < M; m++)
        {
            for (uint32_t n = 0; n < N; n++)
            {
                array[n][m] = m_matrix[m][n];
            }
        }
        return {array};
    }

    constexpr Matrix operator*(T a_scalar) const
    {
        std::array<std::array<T, N>, M> array{};
        for (uint32_t m = 0; m < M; m++)
        {
            for (uint32_t n = 0; n < N; n++)
            {
                array[m][n] = m_matrix[m][n] * a_scalar;
            }
        }
        return {array};
    }

    friend constexpr Matrix operator*(T a_scalar, Matrix a_matrix)
    {
        std::array<std::array<T, N>, M> array{};
        for (uint32_t m = 0; m < M; m++)
        {
            for (uint32_t n = 0; n < N; n++)
            {
                array[m][n] = a_matrix.m_matrix[m][n] * a_scalar;
            }
        }
        return {array};
    }

    template <uint32_t P>
    constexpr Matrix<T, M, P> operator*(Matrix<T, N, P> a_rhx) const
    {
        std::array<std::array<T, P>, M> array{};
        for (uint32_t m = 0; m < M; m++)
        {
            for (uint32_t p = 0; p < P; p++)
            {
                for (uint32_t n = 0; n < N; n++)
                {
                    array[m][p] += m_matrix[m][n] * a_rhx.m_matrix[n][p];
                }
            }
        }

        return {array};
    }

    constexpr Matrix<T, M - 1, N> deleteRow(uint32_t a_idx)
    {
        if (a_idx >= M)
        {
            throw std::invalid_argument("a_idx has to be less then matrix dimension M");
        }
        std::array<std::array<T, N>, M - 1> array{};
        uint32_t idxCorrection{0};
        for (uint32_t m = 0; m < M; m++)
        {
            if (a_idx == m)
            {
                idxCorrection = 1;
                continue;
            }
            for (uint32_t n = 0; n < N; n++)
            {
                array[m - idxCorrection][n] = m_matrix[m][n];
            }
        }
        return {array};
    }

    constexpr Matrix<T, M, N - 1> deleteColumn(uint32_t a_idx)
    {
        if (a_idx >= N)
        {
            throw std::invalid_argument("a_idx has to be less then matrix dimension N");
        }
        std::array<std::array<T, N - 1>, M> array{};
        uint32_t idxCorrection{0};
        for (uint32_t n = 0; n < N; n++)
        {
            if (a_idx == n)
            {
                idxCorrection = 1;
                continue;
            }
            for (uint32_t m = 0; m < M; m++)
            {
                array[m][n - idxCorrection] = m_matrix[m][n];
            }
        }
        return {array};
    }

    constexpr T det() const
    {
        static_assert(M == N);
        static_assert(M >= 2);
        if constexpr (M == 2)
        {
            return m_matrix[0][0] * m_matrix[1][1] - m_matrix[1][0] * m_matrix[0][1];
        }
        else
        {
            T value{0};
            for (uint32_t n = 0; n < N; n++)
            {
                Matrix matrix = *this;
                value += sign(n) * m_matrix[0][n] * matrix.deleteRow(0).deleteColumn(n).det();
            }
            return value;
        }
    }

    static constexpr uint32_t sign(uint32_t a_value)
    {
        if (a_value % 2 == 0)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    std::array<std::array<T, N>, M> m_matrix{};
};

#endif //MATRICES_LIBRARY_H
