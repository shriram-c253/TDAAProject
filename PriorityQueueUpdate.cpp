#include "PriorityQueueUpdate.hpp"

template <class key, class mapped, class comparator>
bool mapped_priority_queue<key,mapped,comparator>::isempty()
{
    return m.size()==0;
}

template <class key, class mapped, class comparator>
void mapped_priority_queue<key,mapped,comparator>::push(key _key,mapped _map)
{
    m[_key]=_map;
    pq.push({_map,_key});
}

template <class key, class mapped, class comparator>
void mapped_priority_queue<key,mapped,comparator>::pop()
{
    assert(m.size()!=0);
    removejunk();
    assert(pq.size()!=0);

    m.erase(pq.top().second);
    pq.pop();
}

template <class key, class mapped, class comparator>
std::pair<key,mapped> mapped_priority_queue<key,mapped,comparator>::top()
{
    assert(m.size()!=0);
    removejunk();
    assert(pq.size()!=0);

    return {pq.top().second,pq.top().first};
}

template <class key, class mapped, class comparator>
int mapped_priority_queue<key,mapped,comparator>::size()
{
    return m.size();
}

template <class key, class mapped, class comparator>
bool mapped_priority_queue<key,mapped,comparator>::present(key k)
{
    return m.find(k)!=m.end();
}

template <class key, class mapped, class comparator>
void mapped_priority_queue<key,mapped,comparator>::update(key k, mapped m1)
{
    assert(m.find(k)!=m.end());
    push(k,m1);
}

template <class key, class mapped, class comparator>
void mapped_priority_queue<key,mapped,comparator>::erase(key k)
{
    m.erase(k);
}

template <class key, class mapped, class comparator>
mapped mapped_priority_queue<key,mapped,comparator>::operator[](key k)
{
    assert(m.find(k)!=m.end());
    return m[k];
}

template <class key, class mapped, class comparator>
void mapped_priority_queue<key,mapped,comparator>::removejunk()
{
    while(pq.size()!=0 && (m.find(pq.top().second)==m.end() || m[pq.top().second]!=pq.top().first))
    {
        pq.pop();
    }
}



// int main()
// {
// 	mapped_priority_queue<int,int,std::greater<std::pair<int,int>>> p;
//     p.push(1,2);
//     p.push(2,3);
//     p.push(1,4);

//     while(p.size()!=0)
//     {
//         std::cout << p.top().first << ' ' << p.top().second << std::endl;
//         p.pop();
//     }
// }