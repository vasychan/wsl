/*
 * =====================================================================================
 *
 *       Filename:  heap.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01.04.2017 16:29:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
#include "heap.hpp"


int main()
{
std::vector<int> rawvec({1,7,3,4,6,2,78,23,22,79,100});
wsl::heap<int>* newheap = new wsl::heap<int>();

newheap->build_new(rawvec);

//newheap->print();

//newheap->print_tree();
//newheap->insert(80);
//newheap->insert(220);
newheap->print();

newheap->print_tree();
// HEAPSORT 
auto tmp = newheap->heapsort();

for ( auto&& i : tmp)
{
    std::cout << i << ",";
}
std::cout <<"\n";

//newheap->print();
newheap->run_by_forward_order(0);

return 0;
}
