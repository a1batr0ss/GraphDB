#ifndef __GDB_VECTOR_H__
#define __GDB_VECTOR_H__

#include <vector>
#include <string>

using namespace std;

class Node;

class NodeVector : public std::vector<Node*> {
  private:
    vector<string> query_chain;

  public:
    NodeVector get(string relation);
    NodeVector& lazy_get(string relation);
    NodeVector query();
};

#endif

