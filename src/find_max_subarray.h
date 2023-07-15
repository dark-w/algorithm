#pragma once

#include <vector>

class find_max_subarray_result {
    public:
        find_max_subarray_result(int begin, int end, int sum)
            : begin(begin),
                end(end),
                sum(sum) {}

        bool operator<(const find_max_subarray_result& rhs) const {
            if (this->sum < rhs.sum) {
                return true;
            }
            else {
                return false;
            }
        }

        bool operator>(const find_max_subarray_result& rhs) const {
            return !(*this < rhs);
        }

        bool operator<=(const find_max_subarray_result& rhs) const {
            if (this->sum <= rhs.sum) {
                return true;
            }
            else {
                return false;
            }
        }

        bool operator>=(const find_max_subarray_result& rhs) const {
            return !(*this <= rhs);
        }

        int begin;
        int end;
        int sum;
};

find_max_subarray_result
find_max_subarray(const std::vector<int> v);
