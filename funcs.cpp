//https://contest.yandex.ru/contest/27844/problems/H/

#include "funcs.h"
#include <bits/stdc++.h>

//! @brief Index of last true. If everything is false return 0
template<typename F1, typename F2>
unsigned long long binSearchLowerBound(F1 valueGenerate,
                           F2 valueCheck,
                                       unsigned long long left, unsigned long long right){
    while (left<right){
        unsigned long long cur = (left + right + 1)/2;
        auto value = valueGenerate(cur);
        if(valueCheck(value)){
            left = cur;
        } else {
            right = cur-1;
        }
    }
    return right;
}

unsigned long long countGroups(
        const std::vector<unsigned long long > & people,
        unsigned long long groupSize,
        unsigned long long d){
    unsigned long long count = 0;
    for(size_t i = 0; i < people.size() + 1 - groupSize; ++i){
        if(people[i+groupSize-1] - people[i] <= d){
            ++count;
            i+=groupSize-1;
        }
    }
    return count;
}

void parseFile(std::istream & input, std::ostream & output){

    unsigned long long n, groups, groupSize;
    input >> n >> groups >> groupSize;

    std::vector<unsigned long long> people(n);
    std::copy_n(std::istream_iterator<unsigned long long >(input), n, people.begin());

    std::sort(people.begin(),people.end());

    unsigned long long left = 0, right = people.back() - *people.begin();
    auto d = binSearchLowerBound(
            [](unsigned long long d){return d;},
                [&people, &groups, &groupSize](unsigned long long d){
                    return countGroups(people,groupSize,d) < groups;
                },
                    left, right);
    if(countGroups(people,groupSize,d) < groups)++d;
    output << d;
}
