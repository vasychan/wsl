/*
 * =====================================================================================
 *
 *       Filename:  list.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20.03.2017 11:44:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <iostream>

template<typename T>
struct Node 
{
    Node<T> *m_prev = nullptr;
    Node<T> *m_curr = nullptr;
    Node<T> *m_next = nullptr;
    T m_value;

    Node()
        :m_value(0)
        {
        m_curr = this;
        }

    Node(T value)
        :m_value(value)
        {
        m_curr = this;
        }

    Node<T> operator * ()
        {
        return *this;
        }

    bool operator != (Node<T> right)
        {
        //std::cout << " operator != " << this->m_prev << " curr " << this->m_curr << "  val " << this->m_value << " next " << this->m_next << "\n";
        //std::cout << " operator rigth != " << right.m_prev << " curr " << right.m_curr << "  val " << right.m_value << " next " << right.m_next << "\n";
        if ( right.m_value != this->m_value && right.m_curr != this->m_curr )
            return true;
        return false;
        }

    Node<T>& operator ++ ()
        {
        this->m_prev = this->m_curr;
        if ( this->m_next)
            {
            this->m_curr = this->m_next;
            this->m_value = this->m_next->m_value;
            if ( this->m_next->m_next ) 
                this->m_next = this->m_next->m_next;
            //std::cout << " after operator ++  prev " << this->m_prev << " curr " << this->m_curr << "  val " << this->m_value << " next " << this->m_next << "\n";
            }
        return *this;
        }

    Node<T> operator ++ (int)
        {
        //std::cout << " preincrement operatorn ++ \n";
        Node<T> tmp(*this);
        //std::cout << " tmp  prev " << tmp.m_prev << " curr " << tmp.m_curr << "  val " << tmp.m_value << " next " << tmp.m_next << "\n";
        operator ++();
        //std::cout << " tmp after do operator ++  prev " << tmp.m_prev << " curr " << tmp.m_curr << "  val " << tmp.m_value << " next " << tmp.m_next << "\n";
        return tmp; 
        }
};

template <typename T>
class List
{
    public:
    Node<T> *m_begin = nullptr;
    Node<T> *m_end = nullptr;

    typedef Node<T> iterator;
    Node<T> begin() { return *m_begin; };
    Node<T> end() { return *m_end; };

    Node<T>* test_begin() { return m_begin; };

    List<T>() {}; 

    void push_back(T val)
        {

        Node<T>* new_node = new Node<T>(val);
        if ( m_end != nullptr)
            m_end->m_next = new_node->m_curr;
        new_node->m_prev = m_end;

        if ( !m_begin ) // this is our first node
            {
            m_begin = new_node; 
            }
        m_end = new_node;
        }

    void insert(iterator it, T val)
        {
        Node<T>* new_node = new Node<T>(val);
        //m_begin++;
        //std::cout << " begin " <<  m_begin <<  " end " << m_end << " |  prev << " << it.m_prev  << " current = " << it->m_curr << " value " << m_end->m_value << " next >> " << m_end->m_next << "\n";
        // setup new node
        new_node->m_prev = it.m_curr;
        new_node->m_next = it.m_next;
        
        auto tmp = it.m_next;
        if (  tmp )
            {
            it.m_next = new_node;
            tmp->m_prev = new_node;
            }
        }
};

//template <typename T>
//Node<T> List<T>::iterator = nullptr;

int main()
{

// defaut constructor
List<int> testlist;
for (int i = 5; i <= 9; i++)
{
    testlist.push_back(i);
}

List<int>::iterator test_it = testlist.begin();
test_it++;
test_it++;

testlist.insert(test_it, 200);

std::cout << " ========================== \n";

for ( auto&& i : testlist )
{
    std::cout << " prev " << i.m_prev << " self " << i.m_curr << "  val " << i.m_value << " next " << i.m_next << "\n";
}

return 0;
}
