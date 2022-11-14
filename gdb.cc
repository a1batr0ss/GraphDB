#include <iostream>
#include "gdb.h"

using namespace std;

GraphDatabase::GraphDatabase()
{
    return;
}

void GraphDatabase::insert_node(unsigned int id, void *data, unsigned int data_len)
{
    this->G.insert_node(id, data, data_len);
    return;
}

void GraphDatabase::insert_edge(unsigned int from, unsigned int to, string relation)
{
    this->G.insert_edge(from, to, relation);
    return;
}

void GraphDatabase::delete_node(unsigned int id)
{
    this->G.delete_node(id);
    return;
}

NodeVector GraphDatabase::get_node(unsigned int id)
{
    return this->G.get_node(id);
}

void GraphDatabase::persist()
{
    (this->persist_file).open("gdb1.gdb", ios::out|ios::binary);
    (this->G).persist(this->persist_file);
    return;
}

void GraphDatabase::recover()
{
    ifstream f;
    
    f.open("./gdb1.gdb", ios::in|ios::binary);
    if (!f.is_open()) {
        cout << "File open failed!" << endl;
        return;
    }

    (this->G).recover(f);
    
    f.close();
}

GraphDatabase::~GraphDatabase()
{
    (this->persist_file).close();
    return;
}

