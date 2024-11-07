#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#include <iostream>
#include <vector>
using namespace std;

struct edge
{
  int capacity;
  int flow = 0;
  string u; //starting verticy
  string v; //ending verticy
  int rc(){ //returns residual capacity of the edge
   return capacity - flow;
  }


};

struct node{
  string name;
  vector<node *> kids;
};

#endif

