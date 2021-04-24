#ifndef BH_QUEUE_H
#define BH_QUEUE_H

#include <iostream>
#include <queue>

#include "Bitboard.h"

class DirNode
{
public:


    DirNode(const DirTuple &tuple, const int weight, bool none = false)
    : tuple(tuple), weight(weight), none(none)
    {}

    void operator =(const DirNode &node)
    {
        tuple = node.tuple;
        weight = node.weight;
    }

    

    DirTuple tuple;
    int weight;
    bool none;
};

bool operator<(const DirNode& n1, const DirNode& n2)
{
    return n1.weight < n2.weight;
}

std::ostream &operator<<(std::ostream &cout, const DirNode &node)
{
    cout << "{ " << node.tuple << " , weight: " << node.weight << " } ";
    return cout;
}

class BH_Queue
{
public:
    BH_Queue()
    {}

    int len() const { return queue_.size(); }
    bool empty() const { return queue_.empty(); }
    DirNode top() const { return queue_.top(); }
    DirNode pop() 
    {
        DirNode ret = queue_.top(); 
        queue_.pop(); 
        return ret;
    }
    

    void insert(const DirTuple &tuple, const int weight)
    {
        queue_.push(DirNode(tuple, weight));
    }

private:
    std::priority_queue< DirNode > queue_;

};

std::ostream &operator<<(std::ostream &cout, BH_Queue queue)
{
    cout << "[ ";
    for (int i = 0; !queue.empty(); ++i)
    {
        if (i % 3 == 0 && i > 0) cout << ",\n  ";
        else if (i < queue.len() && i > 0) cout << ", ";
        cout << queue.top();
        queue.pop();
    
    }
    cout << " ]";

    return cout;
}

#endif