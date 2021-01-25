#ifndef BRAIN_H
#define BRAIN_H

class Heuristic
{};

class Brain
{
public:
    Brain(Heuristic* heuristic = NULL)
    {
        heuristic_ = heuristic;
    }

    virtual void print() { std::cout << "this is a brain" << std::endl; }
    virtual int make_move() const = 0;
private:
    Heuristic* heuristic_;
};

class Random: public Brain
{
public:
    Random()
    :Brain(NULL)
    {}

    void print() { std::cout << "this is a random brain" << std::endl; }

    int make_move() const
    {
        std::cout << "making move with random" << std::endl;
        return 0;
    }
};

class User: public Brain
{
public:
    User()
    :Brain(NULL)
    {}

    void print() { std::cout << "this is a random brain" << std::endl; }
    
    int make_move() const
    {
        std::cout  << "user is taking his turn" << std::endl;
        return 0;
    }
};



#endif
