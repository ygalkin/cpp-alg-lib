#ifndef _SORT_SANDBOX_
#define _SORT_SANDBOX_

namespace sort {
    namespace sandbox {

        // DO NOT USE THIS FUNCTION. It's used for benchmark only.
        // It use two loops (forward and reverse) instead of one loop. Works little bit slower than cocktail_shaker_sort.
        template< class IterT >
        inline void cocktail_shaker_sort_2(IterT first, IterT last) {
            if (first == last)
                return;

            auto is_swapped{ true };
            for (auto begin{ first }, end{ std::prev(last) }; is_swapped; ++begin, --end) {
                // forward pass
                is_swapped = false;
                // for [first, last - 1)
                for (auto i = begin; i != end; ++i) {
                    const auto next_i{ std::next(i) };
                    if (*i > *next_i) {
                        std::iter_swap(i, next_i);
                        is_swapped = true;
                    }
                }

                if (!is_swapped)
                    break;

                // reverse pass
                is_swapped = false;
                // for [last - 1, first)
                for (auto j = end; j != begin; --j) {
                    const auto prev_j{ std::prev(j) };
                    if (*j < *prev_j) {
                        std::iter_swap(prev_j, j);
                        is_swapped = true;
                    }
                }
            }
        }

        template< class IterT >
        inline void selection_sort_2(IterT first, IterT last) {
            for (auto i = first; i != last; ++i)
                std::iter_swap(i, std::min_element(i, last));
        }

        // DO NOT USE THIS FUNCTION. It's used for benchmark only. 
        // The same as selection_sort2() but "find min element" self-implemented loop is used instead of std::min_element
        template< class IterT >
        inline void selection_sort_3(IterT first, IterT last) {
            if (first == last)
                return;

            // for [first, last-1)
            const auto end = std::prev(last);
            for (auto i = first; i != end; ++i) {
                auto min = i;
                // find min element [i + 1, last)
                for (auto j = std::next(i); j != last; ++j) {
                    if (*j < *min)
                        min = j;
                }

                std::iter_swap(i, min);
            }
        }

        // DO NOT USE THIS FUNCTION. It's used for benchmark only.
        // It swaps elements using std::iter_swap instead of moving them using std::move. It works very slow.
        template <typename IterT>
        inline void insertion_sort_2(IterT first, IterT last) {
            if (first == last)
                return;

            // for [first + 1, last)
            for (auto i = std::next(first); i != last; ++i) {
                for (auto j = i, prev_j = std::prev(i); *prev_j > *j; --prev_j, --j) {
                    std::iter_swap(prev_j, j);
                    if (prev_j == first)
                        break;
                }
            }
        }

        // DO NOT USE THIS FUNCTION. It's used for benchmark only. 
        // It use self-implemented partitioning algorithm instead of std::partition that works much faster.
        template< class IterT >
        inline void quick_sort_2(IterT first, IterT last) {
            if (first == last)
                return;

            //const auto pivot = *(first + (std::distance(first, last) / 2));

            // Partitioning. Hoare partition scheme
            // TODO:

            //quick_sort_2(first, left);
            //quick_sort_2(right, last);
        }

        // DO NOT USE THIS FUNCTION. It's used for benchmark only. 
        // ! Stack overflow on a SORTED large array ~ 4000 elements. Lomuto’s partition scheme replaced by Hoare partition scheme
        // You can use it as Lomuto’s partition scheme reference code. 
        template< class IterT >
        inline void quick_sort_3(IterT first, IterT last) {
            if (first == last)
                return;

            // Partitioning. Lomuto’s partition scheme
            const auto pivot = std::prev(last); // pivot element is a last element
            auto bound = std::partition(first, last, [&pivot](const auto& i) { return i < *pivot; });
            std::iter_swap(bound, pivot);

            quick_sort_3(first, bound);
            quick_sort_3(std::next(bound), last);
        }

        // DO NOT USE THIS FUNCTION. It's used for benchmark only. 
        // ! Stack overflow on a SORTED large array ~ 4000 elements. Lomuto’s partition scheme replaced by Hoare partition scheme
        // You can use it as Lomuto’s partition scheme reference code.  
        template< class IterT >
        inline void quick_sort_4(IterT first, IterT last) {
            if (first == last)
                return;

            // Partitioning. Lomuto’s partition scheme
            const auto pivot = std::prev(last); // pivot element is a last element
            auto bound = first;
            // for [first, last)
            for (auto i = first; i != last; ++i) {
                if (*i < *pivot) {
                    std::iter_swap(bound, i);
                    ++bound;
                }
            }
            std::iter_swap(bound, pivot);

            quick_sort_4(first, bound);
            quick_sort_4(std::next(bound), last);
        }
    }
}

#endif