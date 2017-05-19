/*
 * =====================================================================================
 *
 *       Filename:  heap.hpp
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

namespace wsl
{
template<typename T>
struct heap
{
    std::vector<T> data;
    
    size_t size() { return data.size(); }

    void insert(T leaf)
    {
        auto heapsize = data.size() -1;
        data.push_back(leaf);

        auto parent = heapsize;
        if ( heapsize % 2 == 0 )
        {
            parent = (heapsize/2) -1;
        }
        else
        {
            parent = ((heapsize -1)/2) -1;
        }
        auto leaf_id = data.size()- 1;
        while ( parent != leaf_id && data[parent] <= leaf )
        {
            //std::cout << "leaf_id " << leaf_id << ", data[leaf_id] = " << data[leaf_id] << " === > parent id " << parent << " data[parent] = " << data[parent] << "\n";
            std::swap(data[parent], data[leaf_id]);
            leaf_id = parent;
            parent = parent / 2 -1;
            if ( parent > data.size() )
                parent = 0;
        }
    }
    
    void build_new(const std::vector<T>& new_data)
    {
        data = new_data;
        for (int i = data.size()-1 / 2; i >= 0; i-- )
            heapify(i);
    }

    // fist leaf = a[2i+1], second leaf = a[2i+2]
    void heapify( int i )
    {
        int left_leaf;
        int right_leaf;
        int largest_leaf;

        while ( true )
        {
            largest_leaf = i;
            left_leaf = 2 * i + 1;
            right_leaf = 2 * i + 2;
       
            if ( left_leaf < data.size() &&  data[left_leaf]  > data[largest_leaf] )
            {
                largest_leaf = left_leaf;
            }
            if ( right_leaf < data.size() &&data[right_leaf]  > data[largest_leaf] )
            {
                largest_leaf = right_leaf;
            }
            if ( largest_leaf == i ) 
                break;
            
            std::swap(data[i], data[largest_leaf]);
            i = largest_leaf;
        }
    }
    
    void run_by_forward_order(int node_id)
    {
        if ( node_id < data.size() )
        {
            std::cout << data[2 * node_id + 1] << " <- " << data[node_id] << " -> " << data[2 * node_id + 2] << "\n"; 
            run_by_forward_order(2 * node_id + 1);
            run_by_forward_order(2 * node_id + 2);
        }
    }
   
    std::vector<T> heapsort()
    {
        std::vector<T> tmp;
        std::vector<T> tdata = data;
        while(tdata.size() > 0 ) 
        {
            std::swap(tdata[0], tdata[tdata.size() -1 ]);
            tmp.push_back(tdata.back());
            tdata.pop_back();
            for (int i = tdata.size()-1 / 2; i >= 0; i-- )
            {
                heapify(i);
            }
        }
        return tmp;
    }
    void print_tree()
    {
        int level_count = 0; 
        for ( int i =0; i < data.size() -1; i++)
        {
            auto largest_leaf = data[i];
            auto left_leaf = data[2 * i + 1];
            auto right_leaf = data[2 * i + 2];
            /*
            if ( left_leaf > data.size())
                left_leaf= 0;
            else
                left_leaf = data[left_leaf];
             if ( right_leaf > data.size())
                right_leaf= 0;
            else
                right_leaf = data[left_leaf];
            */
            // print tab
            auto j = i;
            while( j < data.size() )
            {
                std::cout << " ";
                j++;
            }
            std::cout <<  largest_leaf << "\n" ;
             j = i;
            while( j < data.size() )
            {
                std::cout << " ";
                j++;
            }

            std::cout << "/ " << " \\ \n" ;
             j = i;
            while( j < data.size()-1 )
            {
                std::cout << " ";
                j++;
            }

            std::cout << left_leaf <<"     " << right_leaf ;
            std::cout << "\n";
        }
        //std::cout << "\n";
    }

    void print()
    {
        for ( auto&& i : data )
        {
            std::cout << i << ",";
        }
        std::cout << "\n";
    }

};
} // namespace wsl
