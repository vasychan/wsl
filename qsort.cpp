/*
 * =====================================================================================
 *
 *       Filename:  qsort.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  24.03.2017 20:24:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

//#include "list.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <ctime>

namespace wstl
{
    template <typename T>
    struct stack_node
    {
        stack_node() = delete;
        stack_node(int start, int end, int pivot):
                    m_start(start),
                    m_end(end),
                    m_pivot(pivot)
                    {};

       int m_start;
       int m_end;
       int m_pivot;
    };

    // for list
    template <typename T>
    void qsort(std::vector<T>& container)
    {
        std::stack<stack_node<T>> qstack;
        int pivot = container[container.size()>>1];       
        qstack.push(stack_node<T>(0, container.size()-1, pivot));
        while ( true )
        {
            auto node = qstack.top();
            qstack.pop();
             
            int l = 0;
            int r = node.m_end;
            //sort particulary
            do 
            { 
                while ( container[l] < node.m_pivot )
                {
                    l++;
                }
                while ( container[r] > node.m_pivot ) 
                {
                    r--;
                }
                if ( l <= r )
                {
                    std::swap(container[l], container[r]);
                    l++; r--;
                }
            }
            while ( l <= r );
            // if rigth ptr don't reach the end of vector
            if ( r < container.size() )
            {
                auto tmp = std::vector<T>(container.begin()+l, container.end());
                qstack.push(stack_node<T>(l, container.size()-1, tmp[container.size()>>1]));
            }
            if ( l > 0 ) 
            {
                auto tmp = std::vector<T>(container.begin(), container.begin() + l);
                qstack.push(stack_node<T>(0, l, tmp[container.size()>>1]));
            }
        for ( auto&& i : container)
        {
            std::cout << i << "," ;
        }
        std::cout << "\n";
        }
    }
} // namespace wstl

int main()
{
std::srand(unsigned(std::time(0)));
//std::vector<int> testlist({1,3,9,10,5,20,2});
std::vector<int> testlist;
testlist.reserve(100);
for ( int i = 0; i < 20; i++)
{
    testlist.push_back(std::rand() % 1000);
}
std::cout << "==================================================================== \n";
for ( auto&& i : testlist)
{
    std::cout << i << "," ;
}
std::cout << " \n";
std::cout << "==================================================================== \n";
wstl::qsort<int>(testlist);

for ( auto&& i : testlist)
{
    std::cout << i << "," ;
}
std::cout << "\n";
return 0;
}
