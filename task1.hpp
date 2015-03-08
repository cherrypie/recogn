#ifndef TASK1_H
#define TASK1_H

#include <vector>
#include <list>
#include <iostream>

class edge_end{
public:
    edge_end(double, int, int);

    double weight;
    int from_obj;
    int from_label;
};

class label{
public:
    label();

    double weight;

    std::list <edge_end> in;
};

class object{
public:
    object(int m);

    std::vector <label> labels;
};

class solver{
private:
    void solve(void (solver::*proc)(std::vector<label>::iterator));

    void procPlus(std::vector<label>::iterator);
    void procMin(std::vector<label>::iterator);

public:
    solver(int n, int m);

    std::vector <object> objects;

    void setInitObject(object * in);
    void setEdge(double, int, int, int, int);

    void solveMin();
    void solvePlus();

    double getWeight(int, int);    
    std::pair <int, int> getMinPrev(int, int);

    int getMaxPlus(int obj = -1);
    std::list <std::pair <int, int> > getMinPath(int, int);
};

#endif // TASK1_H

