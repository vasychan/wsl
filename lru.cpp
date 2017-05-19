/*
 * =====================================================================================
 *
 *       Filename:  lru.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01.04.2017 16:06:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "heap.hpp"
#include <time.h>
#include <unordered_map>
struct time_node
{
    time_node() { start_time = time(NULL); };
    time_t start_time;

    bool operator <= (time_node& right)
    {
        if ( right.start_time <= this->start_time ) 
            return true;
        return false;
    }

    std::ostream& operator << ( std::ostream& os, const time_node& node )
    {
        os << node.start_time;
        return os;
    }
};

template<typename N, typename T>
struct lru_cache
{
    int max_count_nodes;
    time_t m_ttl;
    
    wsl::heap<N> queue;
    std::unordered_map<int, T> data;

    lru_cache(int count_nodes, time_t ttl) : max_count_nodes(count_nodes), m_ttl(ttl) {};

    void push(const T& value)
    {
        N node;

        queue.insert(node);
        size_t key = queue.size();
        data.emplace(key, value);

        //data.emplace(lnode.id, lnode);
    }

    void print()
    {
        for (auto&& i : data)
        {
            std::cout << i.first << " => " << i.second << " , " ;
        }
        std::cout << "\n";
    }
};

int main()
{

lru_cache<time_node, std::string>* lru = new lru_cache<time_node, std::string>(3, 10);

lru->push("x");
lru->push("xx");
lru->push("xxx");
lru->push("xxxx");
lru->push("xxxxx");

lru->print();
lru->queue.print_tree();
return 0;
}
