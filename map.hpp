/*
 * =====================================================================================
 *
 *       Filename:  map.hpp
 *
 *    Description:  header of tread safe map, realized as balanced tree (without color).  
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

#include <iostream>
#include <algorithm>
#include <memory>
#include <iterator>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <mutex>
#include <thread>


template<typename K, typename T>
struct Node 
{
    using _node = Node<K,T>;

    Node<K,T>* m_parent = nullptr;
    Node<K,T>* m_left = nullptr;
    Node<K,T>* m_right = nullptr;
    K m_key;
    T m_value;

    Node() { }
    Node(K key, T value)
        :m_key(key),
        m_value(value) { }

    Node(K key)
        :m_key(key),
        m_value(T()) { }

    //TODO :statter, 110, make better 
    Node(const Node<K,T>& right)
        {
        try
            {
            this->m_parent = right.m_parent;
            this->m_left = right.m_left;
            this->m_right = right.m_right;
            this->m_key = right.m_key;
            this->m_value = right.m_value;
            }
        catch(...)
            {
            throw;
            }
        }

    Node<K, T>& operator = (const Node<K, T>& right);
    Node<K, T> operator * ();
    bool operator != (Node<K,T> right);
    Node<K, T>& operator ++ ();
    Node<K, T> operator ++ (int);
    Node<K, T> operator == (const Node<K,T>& right);
    bool operator < (const Node<K,T>& right);
    bool operator > (const Node<K,T>& right);
};

template <typename K, typename T>
class map 
{
public:
    using _node = Node<K,T>;
    using _node_ptr = std::shared_ptr<Node<K,T>>;
    typedef T mapped_type;

    class iterator : public std::iterator<std::input_iterator_tag, K>
    {
        private:
        _node* _impl;

        public:
        iterator():_impl(nullptr) {}
        iterator(_node* impl):_impl(impl) {}
        iterator(const iterator& new_it):_impl(new_it._impl) {}
        _node& get() { return *_impl; }
        _node& operator * () { return *_impl;}
        bool operator != (const iterator& right) { return right._impl != this->_impl; } 
        bool operator == (const iterator& right) { return right._impl == this->_impl; } 
        iterator& operator ++ () { ++(*_impl); return *this; }
        iterator operator ++ (int)
            {
            iterator tmp(*this);
            operator ++();
            return tmp; 
            }
    };

private: 
    std::mutex mutex; 
    size_t _size = 0;
    _node* m_root;

public:
    map():m_root(nullptr) {};
    ~map()
        {
        delete_all(m_root); 
        }
    inline _node* root() const { return m_root;};
    inline iterator begin() { return iterator(m_root); };
    inline iterator end() { return iterator(); };
    
    inline const size_t size() const { return _size; };

    std::pair<iterator,bool> insert(const std::pair<K, T>& data);
	iterator find(const K& key) const;
	void print_in_order(_node *root) const; 
	bool check_bst(_node* root) const;
    T& operator [] (const K& key); // TODO: need realization
    iterator thr_safe_set(const K& key, const T& value);

private:
	void delete_all(_node *root);
};

