#include <algorithm>
#include <fstream>
#include "graph.h"

#include <iostream>
using namespace std;

Node::Node(unsigned int id, void *data, unsigned int data_len)
{
    this->id = id;
    this->data = data;
    this->data_len = data_len;
    return;
}

void Node::insert_edge(Node *to, string relation)
{
    if ((this->edges[relation]).end() == std::find((this->edges[relation]).begin(), (this->edges[relation]).end(), to))
        (this->edges[relation]).push_back(to);
    return;
}

unsigned int Node::get_id()
{
    return this->id;
}

NodeVector Node::get(string relation)
{
    return (this->edges)[relation];
}

void Node::persist(ofstream &persist_file)
{
    persist_file.write((const char*)(&(this->id)), sizeof(this->id));
    persist_file.write((const char*)(&(this->data_len)), sizeof(this->data_len));
    persist_file.write((const char*)(data), this->data_len);

    unsigned int edges_nr;

    edges_nr = (this->edges).size();
    persist_file.write((const char*)(&(edges_nr)), sizeof(edges_nr));

    map<string, NodeVector>::reverse_iterator iter;
    for (iter=(this->edges).rbegin(); iter!=(this->edges).rend(); iter++) {
        string relation = iter->first;
        NodeVector nexts = iter->second;
        for (int i=0; i<nexts.size(); i++) {
            unsigned int from = this->id;
            unsigned int to = nexts[i]->id;
            unsigned int len = relation.length();
            const char *str = relation.c_str();

            persist_file.write((const char*)(&from), sizeof(from));
            persist_file.write((const char*)(&to), sizeof(to));
            persist_file.write((const char*)(&len), sizeof(len));
            persist_file.write((const char*)(str), len);
        }
    }
    return;
}

//void Node::persist_node(ofstream &persist_file)
//{
    //persist_file.write((const char*)(&(this->id)), sizeof(this->id));
    //persist_file.write((const char*)(&(this->data_len)), sizeof(this->data_len));
    //persist_file.write((const char*)(data), this->data_len);
    //return;
//}

//void Node::persist_edge(ofstream &persist_file)
//{
    //map<string, NodeVector>::reverse_iterator iter;
    //for (iter=(this->edges).rbegin(); iter!=(this->edges).rend(); iter++) {
        //string relation = iter->first;
        //NodeVector nexts = iter->second;
        //for (int i=0; i<nexts.size(); i++) {
            //unsigned int from = this->id;
            //unsigned int to = nexts[i]->id;
            //unsigned int len = relation.length();
            //const char *str = relation.c_str();

            //persist_file.write((const char*)(&from), sizeof(from));
            //persist_file.write((const char*)(&to), sizeof(to));
            //persist_file.write((const char*)(&len), sizeof(len));
            //persist_file.write((const char*)(str), len);
        //}
    //}

    //return;
//}

Graph::Graph()
{}

Node* Graph::insert_node(unsigned int id, void *data, unsigned int data_len)
{
    Node *new_node = new Node(id, data, data_len);
    (this->nodes)[id] = new_node;
    (this->nodes_unpersist).push_back(new_node);
    return new_node;
}

void Graph::insert_edge(unsigned int from, unsigned int to, string relation)
{
    Node *from_node = nodes[from];
    Node *to_node = nodes[to];

    from_node->insert_edge(to_node, relation);
    return;
}

void Graph::delete_node(unsigned int id)
{
    /* delete node, edges */
}

NodeVector Graph::get_node(unsigned int id)
{
    NodeVector tmp;
    tmp.push_back(nodes[id]);
    return tmp;
}

void Graph::persist(ofstream &persist_file)
{

    /* 1. Persist nodes. */
    //unsigned int nodes_nr = (this->nodes).size();
    //persist_file.write((const char*)(&(nodes_nr)), sizeof(nodes_nr));
    //for (int i=0; i<(this->nodes_unpersist).size(); i++) {
       //(this->nodes_unpersist)[i]->persist_node(persist_file); 
    //}

    /* 2. Persist edges. */
    //for (int i=0; i<(this->nodes_unpersist).size(); i++) {
        //(this->nodes_unpersist)[i]->persist_edge(persist_file);        
    //}
    for (int i=0; i<(this->nodes_unpersist).size(); i++) {
        (this->nodes_persist)[(this->nodes_unpersist)[i]->get_id()] = persist_file.tellp();
        (this->nodes_unpersist)[i]->persist(persist_file);
    }

    (this->nodes_unpersist).clear();
    return;
}

void Graph::write_node(unsigned int id, ofstream &persist_file)
{
    Node *node = (this->nodes)[id];
    node->persist(persist_file);
    return;
}

Node* Graph::read_node(unsigned int id, ifstream &persist_file)
{
    unsigned int id_;
    unsigned int data_len;
    unsigned int edges_nr;
    char *data = nullptr;
    unsigned int pos = (this->nodes_persist)[id];

    persist_file.seekg(pos);
    persist_file.read((char*)&id_, sizeof(id_));
    persist_file.read((char*)&data_len, sizeof(data_len));
    data = new char[data_len];
    persist_file.read((char*)data, data_len);
    Node *node = insert_node(id, (void*)data, data_len);

    persist_file.read((char*)(&edges_nr), sizeof(edges_nr));
    for (int i=0; i<edges_nr; i++) {
        unsigned int from;
        unsigned int to;
        unsigned int len;
        char *str = nullptr;
        
        persist_file.read((char*)&from, sizeof(from));
        persist_file.read((char*)&to, sizeof(to));
        persist_file.read((char*)&len, sizeof(len));

        str = new char[len+1];
        persist_file.read((char*)str, len);

        insert_edge(from, to, str);
    }
    return node;
}

void Graph::recover(ifstream &persist_file)
{
    //while (!persist_file.eof()) {
        //unsigned int id;
        //unsigned int data_len;
        //char *data = nullptr;

        //persist_file.read((char*)&id, sizeof(id));
        //persist_file.read((char*)&data_len, sizeof(data_len));

        //data = new char[data_len];
        //persist_file.read((char*)data, data_len);

        //insert_node(id, (void*)data, data_len);

    //}

    //unsigned int nodes_nr;
    //persist_file.read((char*)&nodes_nr, sizeof(nodes_nr));
    //for (int i=0; i<nodes_nr; i++) {
        //unsigned int id;
        //unsigned int data_len;
        //char *data = nullptr;

        //persist_file.read((char*)&id, sizeof(id));
        //persist_file.read((char*)&data_len, sizeof(data_len));

        //data = new char[data_len];
        //persist_file.read((char*)data, data_len);

        //insert_node(id, (void*)data, data_len);
    //}

    //while (!persist_file.eof()) {
        //unsigned int from;
        //unsigned int to;
        //unsigned int len;
        //char *str = nullptr;
        
        //persist_file.read((char*)&from, sizeof(from));
        //persist_file.read((char*)&to, sizeof(to));
        //persist_file.read((char*)&len, sizeof(len));

        //str = new char[len+1];
        //persist_file.read((char*)str, len);

        //insert_edge(from, to, str);
    //}
    return;
}

