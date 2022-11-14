#include <iostream>
#include "gdb.h"

using namespace std;

int main()
{
    GraphDatabase gdb;

    gdb.insert_node(0, (void*)"Tom", 3);
    gdb.insert_node(1, (void*)"Ria", 3);
    gdb.insert_node(2, (void*)"Jay", 3);
    gdb.insert_node(3, (void*)"Frank", 5);
    gdb.insert_edge(0, 1, "father");
    gdb.insert_edge(1, 2, "brother");
    gdb.insert_edge(1, 3, "brother");

    unsigned int res = gdb.get_node(0).get("father").get("brother")[0]->get_id();
    cout << res << endl;

    res = gdb.get_node(0).lazy_get("father").lazy_get("brother").query()[1]->get_id();
    cout << res << endl;

    gdb.persist();

    //gdb.recover();
    //unsigned int res = gdb.get_node(0).lazy_get("father").lazy_get("brother").query()[1]->get_id();
    //cout << res << endl;

    return 0;
}

