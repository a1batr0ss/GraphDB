#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <map>
#include <vector>
#include <string>
#include "gdb_vector.h"

using namespace std;

class Node {
  private:
    unsigned int id;
    void *data;
    unsigned int data_len;
    map<string, NodeVector> edges;
  
  public:
    Node(unsigned int id, void *data, unsigned int data_len);
    void insert_edge(Node *to, string relation);
    unsigned int get_id();
    NodeVector get(string relation);

    void persist(ofstream &persist_file);
    //void persist_node(ofstream &persist_file);
    //void persist_edge(ofstream &persist_file);
};

class Graph {
  private:
    map<unsigned int, Node*> nodes;
    map<unsigned int, unsigned int> nodes_persist;
    vector<Node*> nodes_unpersist;

  public:
    Graph();
    Node* insert_node(unsigned int id, void *data, unsigned int data_len);
    void insert_edge(unsigned int from, unsigned int to, string relation);
    void delete_node(unsigned int id);
    NodeVector get_node(unsigned int id);

    void write_node(unsigned int id, ofstream &persist_file);
    Node* read_node(unsigned int id, ifstream &persist_file);
    void persist(ofstream &persist_file);
    void recover(ifstream &persist_file);
};

#endif

