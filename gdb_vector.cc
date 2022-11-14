#include <iostream>
#include "gdb_vector.h"
#include "graph.h"

using namespace std;

NodeVector NodeVector::get(string relation)
{
    NodeVector res;

    for (int i=0; i<(*this).size(); i++) {
        NodeVector tmp = (*this)[i]->get(relation);

        res.reserve(res.size() + distance(tmp.begin(), tmp.end()));
        res.insert(res.end(), tmp.begin(), tmp.end());
    }
    return res;
}

NodeVector& NodeVector::lazy_get(string relation)
{
    (this->query_chain).push_back(relation);
    return *(this); 
}

NodeVector NodeVector::query()
{
    NodeVector *tmp = this;
    NodeVector tmp_res;

    for (int i=0; i<this->query_chain.size(); i++) {
        tmp_res = tmp->get(this->query_chain[i]);
        tmp = &tmp_res;
    }

    return tmp_res;
}

