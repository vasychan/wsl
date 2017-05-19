/*
 * =====================================================================================
 *
 *       Filename:  map.cpp
 *
 *    Description:  tread safe map, realized as balanced tree (without color).  
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

#define WDEBUG 1

    
template<typename K, typename T>
Node<K, T>& Node<K,T>::operator = (const Node<K, T>& right)
    {
    if ( *this != right )
        {
        Node<K, T>* new_node(right);
        this = new_node; 
        }
    return *this;
    }

template<typename K, typename T>
Node<K, T> Node<K,T>::operator * ()
    {
    return *this;
    }

template<typename K, typename T>
bool Node<K,T>::operator != (Node<K,T> right)
    {
    //std::cout << " operator != " << this->m_parent << " curr " << this->m_left << "  val " << this->m_value << " next " << this->m_right << "\n";
    //std::cout << " operator rigth != " << right.m_parent << " curr " << right.m_left << "  val " << right.m_value << " next " << right.m_right << "\n";
    if ( right.m_key != this->m_key )
        return true;
    return false;
    }

template<typename K, typename T>
Node<K, T>& Node<K,T>::operator ++ ()
    {
    if ( this->m_left )
        {
        //std::cout << " operator ++  go left " << this->m_left->m_key << "\n";
        auto tmp = this->m_left;
        this->m_left = tmp->m_left;
        this->m_right = tmp->m_right;
        this->m_parent = tmp->m_parent;
        this->m_key = tmp->m_key;
        this->m_value = tmp->m_value;
        return *this;
        }
    else if (this->m_right)
        {
        //std::cout << " operator ++  go right " << this->m_right->m_key << "\n";
        auto tmp = this->m_right;
        this->m_left = tmp->m_left;
        this->m_right = tmp->m_right;
        this->m_parent = tmp->m_parent;
        this->m_key = tmp->m_key;
        this->m_value = tmp->m_value;
        return *this;
        }
    //std::cout << " after operator ++  prev " << this->m_parent << " curr " << this->m_left << "  val " << this->m_value << " next " << this->m_right << "\n";
    return *this;
    }

template<typename K, typename T>
Node<K, T> Node<K, T>::operator ++ (int)
    {
    std::cout << " call prefix ++ " <<  "\n";
    Node<K,T> tmp(*this);
    operator ++();
    return tmp; 
    }

template<typename K, typename T>
Node<K, T> Node<K, T>::operator == (const Node<K,T>& right)
    {
    if ( right.m_key == this->m_key )
        return true;
    return false;
    }

template<typename K, typename T>
bool Node<K, T>::operator < (const Node<K,T>& right)
    {
    //std::cout << " operator < " << this->m_key << " < " << right.m_key << " \n "; 
    if (this->m_key < right.m_key )
        return true;
    return false;
    }

template<typename K, typename T>
bool Node<K, T>::operator > (const Node<K,T>& right)
    {
    //std::cout << " operator > " << this->m_key << " > " << right.m_key << " \n "; 
    if (this->m_key > right.m_key )
        return true;
    return false;
    }

// not thread safe function 
template <typename K, typename T>
std::pair<typename map<K,T>::iterator, bool> map<K,T>::insert(const std::pair<K, T>& data )
    {
    auto key = data.first;
    auto val = data.second;

    auto node = new Node<K,T>(key, val);
    _node*  parent_node = nullptr;

    if ( m_root == nullptr ) //first value in the map
        {
        m_root = node;
        }
    else
        {
        _node* current_node = nullptr;
        current_node = m_root;
        while ( current_node )
            {
            parent_node = current_node;
            if ( *node > *current_node )
                {
                //m_root = current_node;
                current_node = current_node->m_right;
                }
            else if (*node < *current_node)
                {
                //m_root = node;
                current_node = current_node->m_left;
                }
            //else if ( *node == *current_node)
            else
                {
                // delete node
                delete node;
                node = nullptr;
                //TODO: check for leack
                return std::make_pair(iterator(current_node), false);
                }
            }
        if ( *node < *parent_node )
            {
            parent_node->m_left = node;
            }
        else
            {
            parent_node->m_right = node;
            }
        delete current_node;
        current_node = nullptr;
        }
    _size++; // increment size
    return std::make_pair(iterator(node), true);
    }

template <typename K, typename T>
typename map<K,T>::iterator map<K,T>::find(const K& key) const
    {
    _node_ptr search_node(new _node(key));	
    _node* current_node = m_root;
    #ifdef WDEBUG
        size_t count_iteration = 0;
    #endif
    while(current_node)
        {
        #ifdef WDEBUG
            count_iteration++;
        #endif
        if ( *search_node > *current_node)
            {
            current_node = current_node->m_right;
            } 
        else if (*search_node < *current_node)
            {
            current_node = current_node->m_left;
            }
        else
            {
            #ifdef WDEBUG
            std::cout << "find:: iteration count  " << count_iteration << " key " << current_node->m_key << "\n"; 
            #endif
            break;
            }
        }
    return iterator(current_node);
    }

template <typename K, typename T>
void map<K,T>::print_in_order(_node *root) const 
    {
    if ( root)
        {
        print_in_order(root->m_left);
        std::cout << " ====> " << root->m_key << " -> " << root->m_value << " \n";
        print_in_order(root->m_right);
        }
    }

//TODO: cause seqfault
template <typename K, typename T>
bool map<K,T>::check_bst(_node* root) const
    {
    static _node* tmp = nullptr;
    if (root != nullptr)
        {
        if (!check_bst(root->m_left))
           return false;
        if (tmp != nullptr && root->m_key < tmp->m_key)
           return false;
        tmp = root;
        return check_bst(root->m_right);
        }
    return true;	
    }


template <typename K, typename T>
T& map<K,T>::operator [] (const K& key)
    {
    
    }

template <typename K, typename T>
typename map<K,T>::iterator map<K,T>::thr_safe_set(const K& key, const T& value)
    {
     
    return true;
    }

template <typename K, typename T>
void map<K,T>::delete_all(_node *root) 
    {
    if ( root)
        {
        delete_all(root->m_left);
        delete_all(root->m_right);
        delete root;
        root = nullptr;
        }
    }

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
void fill_random_map(T& tmap)
    {
    for (int i = 0; i < 100; i++)
        {
        int r = std::rand() % 1000;
        tmap.insert(std::pair<int, int>(r, i));
        //std::cout << std::this_thread::get_id() << " insert " << r << " -> " << i << "\n"; 
        }
    }


#include <assert.h>
int main()
{
std::srand(unsigned(std::time(0)));

// defaut constructor
map<int, int> testmap;
fill_random_map(testmap);

print_map_info<map<int,int>>(testmap);
//testmap.print_in_order(testmap.root());

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
//for ( auto& i : testmap )
/*int j = 0;
for ( map<int,int>::iterator it = testmap.begin(); j < 9; it++, j++)
    {
    std::cout << " key " << (*it).m_key <<  "  val " << (*it).m_value  << "\n";
    }
*/
std::cout << "\n\n ===== threads ==== " << "\n";
map<int, int> thread_map;
std::thread threads[2];

for (int i = 0; i < 2; i++)
    {
    threads[i] = std::thread(fill_random_map<map<int,int>>, std::ref(thread_map));
    }

for (auto&& i : threads)
    {
    i.join();
    }
print_map_info<map<int,int>>(thread_map);

std::cout << "\n\n ===== test insert with equal values ==== " << "\n";
map<int, int> insertmap;
for (int i = 0; i < 10; i++)
    {
    auto it = insertmap.insert(std::pair<int, int>(i, i*2));
    assert(it.second);
    }

auto it = insertmap.insert(std::pair<int, int>(5, 6000));
assert(!it.second);
//testmap.print_in_order(insertmap.root());

std::cout << "\n\n ===== test thread safe insert  ==== " << "\n";
return 0;
}
