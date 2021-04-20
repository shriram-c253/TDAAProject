 
#ifndef MAPPQ
#define MAPPQ
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <cassert>

template <class key, class mapped, class comparator = std::greater<std::pair<mapped,key>>>
class mapped_priority_queue
{
    public:
    bool isempty();
    void push(key _key,mapped _map);
    void pop();
    std::pair<key,mapped> top();
    int size();
    bool present(key k);
    void update(key k, mapped m1);
    void erase(key k);
    mapped operator[](key k);

    private:
    std::map<key,mapped> m;
    std::priority_queue <std::pair<mapped,key>,std::vector<std::pair<mapped,key>>,comparator> pq;
    void removejunk();
};

#endif