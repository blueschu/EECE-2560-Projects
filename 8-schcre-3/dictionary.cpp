/**
 * Dictionary definitions for project 3.
 *
 * Authors: Brian Schubert  <schubert.b@northeastern.edu>
 *          Chandler Cree   <cree.d@northeastern.edu>
 * Date:    2020-10-22
 *
 * References
 * ==========
 *  [1] https://en.cppreference.com/w/cpp/iterator/istream_iterator
 *
 */

#include "dictionary.h"

#include <algorithm>        // for std::transform
#include <cctype>           // for std::tolower
#include <fstream>          // for std::ifstream
#include <iterator>         // for std::istream_iterator

#include "algo_util.h"
#include "heap.h"
#include "eece2560_io.h"

Dictionary Dictionary::read_file(const char* file_name, SortingAlgorithm algorithm)
{
    std::ifstream in_stream(file_name);
    in_stream.exceptions(std::ios::badbit);

    std::vector<std::string> words;

    std::copy(
        std::istream_iterator<std::string>(in_stream),
        std::istream_iterator<std::string>(),
        std::back_inserter(words)
    );

    return Dictionary(std::move(words), algorithm);
}

void Dictionary::sort_words(Dictionary::SortingAlgorithm algorithm)
{
    switch (algorithm) {
        case SortingAlgorithm::SelectionSort: {
            eece2560::selection_sort(std::begin(m_words), std::end(m_words));
            break;
        }
        case SortingAlgorithm::QuickSort: {
            eece2560::quicksort_unstable(std::begin(m_words), std::end(m_words));
            break;
        }
        case SortingAlgorithm::HeapSort: {
            heap_sort_unstable(std::begin(m_words), std::end(m_words));
            break;
        }
    }

}

std::ostream& operator<<(std::ostream& out, const Dictionary& dictionary)
{
    eece2560::print_sequence(out, std::begin(dictionary.m_words), std::end(dictionary.m_words));
    return out;
}

void Dictionary::normalize_word()
{
    for (auto& word : m_words) {
        std::transform(std::begin(word), std::end(word), std::begin(word),
            [](char c) { return std::tolower(c); }
        );
    }
}

bool Dictionary::contains(const std::string_view key) const
{
    const auto result = eece2560::binary_search(std::begin(m_words), std::end(m_words), key);
    return static_cast<bool>(result);
}
