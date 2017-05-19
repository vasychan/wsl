/*
 * =====================================================================================
 *
 *       Filename:  test_map.cpp
 *
 *    Description:  tests for thread_safe map 
 *
 *        Version:  1.0
 *        Created:  17.05.2017 19:44:45
 *       Revision:  none
 *       Compiler:  g++ 4.9
 *
 *         Author:  Max Korchagin aka Vasy,  <vasy.chan@gmail.com>
 *
 * =====================================================================================
 */

#include "map.hpp"
/*
template <typename T>
void print_map_info(T& tmap)
    {
    std::cout << " ======== map info ========== " << "\n";
    std::cout << " root is " << tmap.root()->m_key << "\n";
    std::cout << " size is " << tmap.size() << "\n";
    std::cout << " size is (kbytes) " <<  "\n";
	//if (tmap.check_bst(tmap.root()))
//		std::cout << "yes";
    std::cout << " BST status " <<   "\n";
    std::cout << " ======== map info ========== " << "\n";
    }

template<typename T>
void fill_map(T& tmap)
    {
    for (int i = 0; i < 10; i++)
        {
        int r = std::rand() % 10000;
        tmap.insert(std::pair<int, int>(r, i));
        //std::cout << std::this_thread::get_id() << " insert " << r << " -> " << i << "\n"; 
        }
    }
*/
int main()
    {
    std::srand(unsigned(std::time(0)));

    // defaut constructor
    map<int, int> testmap;
 /*   fill_map(testmap);

    print_map_info<map<int,int>>(testmap);
    testmap.print_in_order(testmap.root());

    // test for find
    for (int i = 0; i < 100; i++)
        {
        int r = std::rand() % 10000;
        //std::cout << " take key = " << r << " " ;
        map<int,int>::iterator it = testmap.find(r);
        if ( it != testmap.end() )
            {
            std::cout << " found key in the map " <<  (*it).m_key << " " << (*it).m_value << "\n ";
            }
        }
    */
    //for ( auto& i : testmap )
    /*int j = 0;
    for ( map<int,int>::iterator it = testmap.begin(); j < 9; it++, j++)
        {
        std::cout << " key " << (*it).m_key <<  "  val " << (*it).m_value  << "\n";
        }
    */

/*
    std::cout << " ===== threads ==== " << "\n";
    map<int, int> thread_map;
    std::thread threads[2];

    for (int i = 0; i < 2; i++)
        {
        threads[i] = std::thread(fill_map<map<int,int>>, std::ref(thread_map));
        }

    for (auto&& i : threads)
        {
        i.join();
        }
    print_map_info<map<int,int>>(thread_map);
    */
    /*
    map<int>::iterator test_it = testmap.begin();
    test_it++;
    test_it++;

    testmap.insert(test_it, 200);

    std::cout << " ========================== \n";

    */

    /*
    int count =0;
    while(++count < 9)
    {
        
    }
    //for ( auto&& i : testmap )
     int i = 0;
    for ( Map<int,int>::iterator it = testmap.begin(); i < 9; it++, i++)
    {
        //std::cout << " prev " << *(i).m_parent << " self " << i.m_left << " key " << i.m_key <<  "  val " << i.m_value << " next " << i.m_right << "\n";
        auto lnode = *it;
        std::cout << " key " << lnode.m_key <<  "  val " << lnode.m_value  << "\n";
    }
    */
    return 0;
}
