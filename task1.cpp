#ifndef TASK1_CPP
#define TASK1_CPP

#include "task1.hpp"

label::label()
{
    weight = 0;
}

object::object(int m)
{
    labels.resize(m);
}

edge_end::edge_end(double w, int obj, int lbl)
{
    weight = w;
    from_obj = obj;
    from_label = lbl;
}

solver::solver(int n, int m)
{
    objects.resize(n, object(m));
}

void solver::setInitObject(object * in)
{
    objects[0] = *in;
}

void solver::setEdge(double w, int from_obj, int from_label,
                               int dest_obj, int dest_label)
{
    objects[dest_obj].labels[dest_label].in.push_back(edge_end(w, from_obj, from_label));
}

double solver::getWeight(int i, int j)
{
    return objects[i].labels[j].weight;
}

void solver::procPlus(std::vector<label>::iterator label_it)
{
    std::list<edge_end>::iterator edge_it = (*label_it).in.begin();
    for(; edge_it != (*label_it).in.end(); ++edge_it)
        (*label_it).weight +=
                (*edge_it).weight *
                getWeight((*edge_it).from_obj, (*edge_it).from_label);
}

void solver::procMin(std::vector<label>::iterator label_it)
{
    std::list<edge_end>::iterator edge_it, min;
    min = edge_it = (*label_it).in.begin();
    for(edge_it++; edge_it != (*label_it).in.end(); ++edge_it)
        if((*min).weight > (*edge_it).weight)
            min = edge_it;

    (*label_it).weight *= (*min).weight;
}

void solver::solve(void (solver::*proc)(std::vector<label>::iterator))
{
    std::vector<object>::iterator obj_it;
    std::vector<label>::iterator label_it;

    obj_it = objects.begin();
    for(++obj_it; obj_it != objects.end(); ++obj_it)
    {
        label_it = (*obj_it).labels.begin();
        for(; label_it != (*obj_it).labels.end(); ++label_it)
        {
            if(! (*label_it).in.empty())
               (this->*proc)(label_it);
        }
    }
}

void solver::solvePlus()
{
    solve(&solver::procPlus);
}

void solver::solveMin()
{
    solve(&solver::procMin);
}

std::pair <int, int> solver::getMinPrev(int o, int l)
{
    std::list<edge_end>::iterator edge_it, min;
    min = edge_it = objects[o].labels[l].in.begin();
    for(edge_it++; edge_it != objects[o].labels[l].in.end(); ++edge_it)
        if((*min).weight > (*edge_it).weight)
            min = edge_it;

    return std::make_pair((*min).from_obj, (*min).from_label);
}

std::list <std::pair <int, int> > solver::getMinPath(int o, int l)
{
    std::list <std::pair <int, int> > result;
    result.push_back(std::make_pair(o, l));

    std::pair <int, int> buff;

    while(o != 0)
    {
        buff = getMinPrev(o, l);
        o = buff.first;
        l = buff.second;
        result.push_back(std::make_pair(o, l));
    }

    return result;
}

int solver::getMaxPlus(int obj)
{
    if(0 > obj || obj >= objects.size())
        obj = objects.size() - 1;

    size_t label_ind, max;

    max = label_ind = 0;
    for(++label_ind; label_ind < objects[obj].labels.size(); ++label_ind)
        if(objects[obj].labels[label_ind].weight >
           objects[obj].labels[max].weight)
            max = label_ind;

    return max;
}

#endif // TASK1_CPP
