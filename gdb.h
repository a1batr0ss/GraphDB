#ifndef __GDB_H__
#define __GDB_H__

#include <string>
#include <fstream>
#include "graph.h"

using namespace std;

class GraphDatabase {
  private:
    Graph G;
    ofstream persist_file;
    ifstream persist_file_r;

  public:
    GraphDatabase();
    void insert_node(unsigned int id, void *data, unsigned int data_len);
    void insert_edge(unsigned int from, unsigned int to, string relation);
    void delete_node(unsigned int id);
    NodeVector get_node(unsigned int id);

    Node* read_node(unsigned int id);
    void persist();
    void recover();
    ~GraphDatabase();
};

#endif

