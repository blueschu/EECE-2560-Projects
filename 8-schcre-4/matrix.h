/**
 * 2D grid for project 4.
 *
 * Authors: Brian Schubert  <schubert.b@northeastern.edu>
 *          Chandler Cree   <cree.d@northeastern.edu>
 * Date:    2020-11-14
 *
 * References
 * ===========
 *  [1] https://en.cppreference.com/w/cpp/iterator/iterator_traits
 *  [2] https://en.cppreference.com/w/cpp/named_req/Container
 *  [3] https://stackoverflow.com/questions/856542/
 *  [4] https://stackoverflow.com/questions/4178175/
 */

#ifndef EECE_2560_PROJECTS_MATRIX_H
#define EECE_2560_PROJECTS_MATRIX_H

#include <stdexcept>            // for std::out_of_range
#include <sstream>              // for std::ostring_stream
#include <utility>              // for std::pair
#include <vector>               // for std::vector

/// Exception raised upon accessing a non-existent matrix entry.
struct MatrixIndexError : std::out_of_range {
    // Use parent class constructor.
    using std::out_of_range::out_of_range;
};

/**
 * Aggregate representing a two-dimensional square matrix of elements.
 * Not intended for linear algebra.
 *
 * @tparam T Type of elements to be stored.
 * @tparam N The number of rows/columns in the matrix.
 */
template<typename T, std::size_t N>
struct Matrix {
    /// Container type used to storage matrix elements.
    using Storage = std::array<T, N * N>;

    // Type aliases for C++ container [2].
    using value_type = typename Storage::value_type;
    using reference = typename Storage::reference;
    using const_reference = typename Storage::const_reference;
    using iterator = typename Storage::iterator;
    using const_iterator = typename Storage::const_iterator;
    using difference_type = typename Storage::difference_type;
    using size_type = typename Storage::size_type;

    /// Type used to access matrix elements using a coordinate pair.
    using Coordinate = std::pair<size_type, size_type>;

    /**
     * Consecutive storage of matrix elements.
     *
     * This data member is public so that Matrix can be an aggregate [4].
     */
    Storage m_entries;

    /// Returns the dimension of this matrix.
    [[nodiscard]] constexpr static size_type dim() noexcept { return N; }

    /// Returns the size of this matrix.
    [[nodiscard]] constexpr static size_type size() noexcept { return N * N; }

    // Returns the entry at the Nth position, counting left-to-right,
    // top-to-bottom, where N=index.
    reference operator[](size_type index)
    {
        // Safely delegate to const implementation [3].
        return const_cast<reference>(
            static_cast<const Matrix*>(this)->operator[](index)
        );
    }

    // Returns the entry at the position (i,j), where both i and j
    // are 0-based indices.
    reference operator[](Coordinate coord)
    {
        // Safely delegate to const implementation [3].
        return const_cast<reference>(
            static_cast<const Matrix*>(this)->operator[](coord)
        );
    }

    // Returns the entry at the Nth position, counting left-to-right,
    // top-to-bottom.
    const_reference operator[](size_type index) const
    {
        if (index >= N * N) {
            throw MatrixIndexError("invalid matrix index");
        }
        return m_entries[index];
    }

    // Returns the entry at the position (i,j), where both i and j
    // are 0-based indices.
    const_reference operator[](Coordinate index) const
    {
        const auto[row, col] = index;
        // size_type is an unsigned integer [2], so we only need to check the upper bounds.
        if (row >= N || col >= N) {
            throw MatrixIndexError("invalid matrix index");
        }
        return m_entries[row * N + col];
    }

    /// Returns an iterator to the first (top left) entry of this matrix.
    [[nodiscard]] iterator begin() noexcept { return std::begin(m_entries); }

    /// Returns an iterator to the first (top left) entry of this matrix.
    [[nodiscard]] const_iterator begin() const noexcept { return std::begin(m_entries); }

    /// Returns an iterator to the last (bottom right) entry of this matrix.
    [[nodiscard]] iterator end() noexcept { return std::end(m_entries); }

    /// Returns an iterator to the last (bottom right) entry of this matrix.
    [[nodiscard]] const_iterator end() const noexcept { return std::end(m_entries); }

    /**
     * Returns the matrix coordinate corresponding to the given iterator position.
     *
     * @param pos Iterator position.
     * @return Matrix coordinate.
     */
    constexpr Coordinate coordinate_of(const_iterator pos) const
    {
        // Cast pos to const_iterator so that this function can be used on
        // ColumnIterators.
        const auto index = std::distance(begin(), pos);
        return {static_cast<size_type>(index) / N, static_cast<size_type>(index) % N};
    }

};

/// Ensure that Matrix is an aggregate.
static_assert(std::is_aggregate_v<Matrix<int, 1>>);

#endif //EECE_2560_PROJECTS_MATRIX_H
