#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "data_structures.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

//Description: converts file input to a vector of edges
//Preconditions: file is not empty
//Postconditions: vector<edge> is filled
vector<edge> fill_array(const string FILE_NAME){
  ifstream file;
  file.open (FILE_NAME);
  vector<edge> graph;
  string str;
  edge line;
  int i = 0; //measures iteration of second while loop
  while (getline(file, str)){
    i = 0; //resets iteration value
    //cout << str << "\n";
    stringstream s_stream(str); //create string stream from the string
   while(s_stream.good()) {
      string substr;
      getline(s_stream, substr, ','); //get first string delimited by comma
      //cout << substr << "\n";
      if(i == 0){
        line.u = substr;
      }
      if(i == 1){
        line.v = substr;
      }
      if(i == 2){
        line.capacity = stoi(substr);
      }
      i++;
    }
   graph.push_back(line);
  }
  file.close();
  return graph;
}

//Description: checks to see if a certain edge exists in a list of edges
//Preconditions: G.size() > 0
//Postconditions: returns true or false
bool exists_in_list(edge e, vector<edge> G){
  for(int i = 0; i < int(G.size()); i++){
    if((e.u == G[i].u)&&(e.v == G[i].v)&&(e.capacity = G[i].capacity)){
      return true;
    }
  }
  return false;
}

//Description: checks to see if a node already exits in a list
//Preconditions: n.size() > 0
//Postconditions: returns true or false
bool duplicate_node(node x, vector<node> n){
  for(int i = 0; i < int(n.size()); i++){
    if(x.name == n[i].name){
      return true;
    }
  }
  return false;
}

//Description: checks to see if two paths are equal
//Preconditions: both paths have a size more than zero
//Postconditions: returns true or false
bool path_equals_path(vector<node> pathI, vector<node> pathII){
  if(pathI.size() == pathII.size()){
    for(int i = 0; i < int(pathI.size()); i++){
      if(pathI[i].name != pathII[i].name){
        return false;
      }
    }
  }else{
    return false;
  }
  return true;
}

//Description: checks to see if a path already exists in the path list
//Preconditions: both lists have a size over zero
//Postconditions: returns true or false
bool path_exists_in_list(vector<node> path, vector<vector<node>> path_list){
  for(int i = 0; i < int(path_list.size()); i++){
    if(path_equals_path(path, path_list[i])){
      return true;
    }
  }
  return false;
}

//Description: prints graph
//Preconditions:  G.size() > 0
//Postconditions: none
void print_graph(vector<edge> G){
  for(int i = 0; i < int(G.size()); i++){
    cout << G[i].u << "," << G[i].v << "  flow: " << G[i].flow << "/" << G[i].capacity << "\n";
  }
}

//Description: builds a list of nodes
//Preconditions: G.size() > 0
//Postconditions: returns the list of nodes
vector<node> create_nodes_list(vector<edge> G){
  node temp;
  node start;
  start.name = "s";
  vector<node> node_list;
  node_list.push_back(start); //adds source
  for(int i  = 0; i < int(G.size()); i++){
      temp.name = G[i].v;
      if(duplicate_node(temp, node_list) == false){
        node_list.push_back(temp);
      }
  }
  for(int x = 0; x < int(node_list.size()); x++){
    for(int i  = 0; i < int(G.size()); i++){
      if(G[i].v == node_list[x].name){ //checks to see if node is a parent
         for(int a = 0; a < int(node_list.size()); a++){
           if(G[i].u == node_list[a].name){ //checks to find children
            node_list[x].kids.push_back(& node_list[a]);
           }
         }
      }
    }
  }
  return node_list;
}

//Description: prints all nodes in list for debug purposes
//Preconditions: list length is more than zero
//Postconditions: none
void print_nodes(vector<node> n){
  for(int i = 0; i < int(n.size()); i++){
    cout << "NODE: " << n[i].name << "\n";
    for(int x = 0; x < int(n[i].kids.size()); x++){
      cout << n[i].kids[x]->name << " ";
    }
    cout << "\n";
  }
}

//Description: prints node paths used for debug
//Preconditions: list length is more than zero
//Postconditions: none
void print_path(vector<node> n){
  for(int i = 0; i < int(n.size()); i++){
    cout << n[i].name << " ";
  }
  cout << "\n";
}

//Description: calculates a path from "s" to "t"
//Preconditions: path length more than zero
//Postconditions: path values are changed
void calculate_path(node n, vector<node> & path){
  path.push_back(n);
  if(n.name != "s"){
    int random_value = rand() % n.kids.size();
    if(duplicate_node(* n.kids[random_value], path) == false){
      calculate_path(* n.kids[random_value], path);
    }
  }
}

//Description: calculates all possible paths of the graph
//Preconditions: none
//Postconditions: a vector of all possible paths is returned
vector<vector<node>> calculate_all_paths(node n){ //n represents the root node, in the case of this assignment it would be t
  vector<vector<node>> total_paths;
  vector<node> path;
  for(int i = 0; i < 2000; i++){
    path.clear();
    calculate_path(n, path);
    if(path_exists_in_list(path, total_paths) == false){
      if(path[path.size() - 1].name == "s"){
        total_paths.push_back(path);
      }
    }
  }
  return total_paths;
}

//Description: converts a list of nodes to edges
//Preconditions: vectors have size more than zero
//Postconditions: a list of edges is returned
vector<edge> convert_path_to_edges(vector<node> path, vector<edge> G){
  vector<edge> edge_path;
  for(int i = int(path.size()) - 1; i > 0; i--){
    for(int x = 0; x < int(G.size()); x++){
      if((path[i].name == G[x].u)&&(path[i-1].name == G[x].v)){
        edge_path.push_back(G[x]);
      }
    }
  }
  return edge_path;
}

//Description: converts all nodes paths to edges
//Preconditions: lists have sizes more than zero
//Postconditions: returns list of all edge paths
vector<vector<edge>> convert_all_paths_to_edges(vector<vector<node>> paths, vector<edge> G){
  vector<vector<edge>> total_edge_paths;
  for(int i = 0; i < int(paths.size()); i++){
    total_edge_paths.push_back(convert_path_to_edges(paths[i], G));
  }
  return total_edge_paths;
}

//Description: prints all node paths
//Preconditions: list has a size more than zero
//Postconditions: none
void print_paths(vector<vector<node>> a){
  for(int i = 0; i < int(a.size()); i++){
    cout << "PATH " << i << "\n";
    for(int x = 0; x < int(a[i].size()); x++){
      cout << a[i][x].name << " ";
    }
    cout << "\n";
  }
}

//Description: calculates the capacity if the path
//Preconditions: path size is more than zero
//Postconditions: the total capacity is returned
int calculate_path_capacity(vector<edge> path){
  int cap = 0;
  for(int i = 0; i < int(path.size()); i++){
    cap += int(path[i].capacity);
  }
  return cap;
}

//Description: calculates the total flow of the path
//Preconditions: path size is more than zero
//Postconditions: returns the total flow
int calculate_path_flow(vector<edge> path){
  int f = 0;
  for(int i = 0; i < int(path.size()); i++){
    f += int(path[i].flow);
  }
  return f;
}

//Description: calculates the flow that can be added to a path
//Preconditions: path size is more than zero
//Postconditions: returns true or false
bool flow_available(vector<edge> path){
  for(int i = 0; i < int(path.size()); i++){
    if(path[i].rc() <= 0){
      return false;
    }
  }
  return true;
}

//Description: prints all paths
//Preconditions: list size is more than zero
//Postconditions: none
void print_edge_paths(vector<vector<edge>> G){
  for(int i = 0; i < int(G.size()); i++){
    cout << "PATH " << i << " Capacity: " << calculate_path_capacity(G[i]) << " Flow: " << calculate_path_flow(G[i]) << "\n";
    for(int x = 0; x < int(G[i].size()); x++){
      cout << G[i][x].u << "-" << G[i][x].v << " ";
    }
    cout << "\n";
  }
}

//Description: returns the minimum residual capacity of all the edges in the path
//Preconditions: path size is more than zero
//Postconditions: returns the flow that can be added to the path
int calculate_min_cf(vector<edge> path){
  int min = path[0].rc();
  for(int i = 0; i < int(path.size()); i++){
    if(path[i].rc() < min){
      min = path[i].rc();
    }
  }
  return min;
}

//Description: calculates the total flow of the graph
//Preconditions: G size is more than zero
//Postconditions: the total flow is returned
int calculate_total_flow(vector<edge> G){
  int total = 0;
  for(int i = 0; i < int(G.size()); i++){
    if(G[i].v == "t"){
      total += G[i].flow;
    }
  }
  return total;
}

//Description: updates the graph with new values
//Preconditions: list sizes are more than zero
//Postconditions: none
void update_graph(vector<edge> & path, vector<edge> & G){
  for(int r = 0; r < int(path.size()); r++){ //updates parent list
    for(int c = 0; c < int(G.size()); c++){
      if((path[r].u == G[c].u)&&(path[r].v == G[c].v)){
        G[c] = path[r];
      }
    }
  }
}

//Description: creates a new edge
//Preconditions: none
//Postconditions: none
edge create_edge(string u, string v, int f, int c){
   edge e;
   e.u = u;
   e.v = v;
   e.flow = f;
   e.capacity = c;
   return e;
}

//Description: updates the residual graph
//Preconditions: lists have sizes more than zero
//Postconditions: none
void update_residual_graph(vector<edge> G, vector<edge> & Gf){
  Gf.clear();
  for(int i = 0; i < int(G.size()); i++){
    if(G[i].rc() > 0){ //case pipe not full
      Gf.push_back(G[i]);
      Gf.push_back(create_edge(G[i].v, G[i].u, G[i].rc(), G[i].capacity));
    }
    if(G[i].rc() == 0){ //case pipe is full
      Gf.push_back(create_edge(G[i].v, G[i].u, G[i].rc(), G[i].capacity));
    }
  }
}

int calculate_source_flow(vector<edge> G){
  int sum = 0;
  for(int i = 0; i < int(G.size()); i++){
    if(G[i].u == "s"){
      sum += G[i].flow;
    }
  }
  return sum;
}

//Description: finsd the opposite direction edge position in the graph
//Preconditions: G size is more than zero
//Postconditions: returns the position in the list
int find_opposite_index(edge e, vector<edge> G){
  int index = 0;
  for(int i = 0; i < int(G.size()); i++){
    if((e.u == G[i].v)&&(e.v == G[i].u)){
        index = i;
    }
  }
  return index;
}

//Description: finds the root node in the list
//Preconditions: list size is more than zero
//Postconditions: the root node position is returned
int find_t_index(vector<node> nodes){
  int index = 0;
  for(int i = 0; i < int(nodes.size()); i++){
    if(nodes[i].name == "t"){
      index = i;
    }
  }
  return index;
}

//Description: prints the paths
//Preconditions: path size is more than zero
//Postconditions: none
void print_path(vector<edge> path){
  for(int i = 0; i < int(path.size()); i++){
    cout << path[i].u << "," << path[i].v << " ";
  }
  cout << "\n";
}

//Description: calculates all possible paths in the residual graph
//Preconditions: Gf size is more than zero
//Postconditions: returns a list of all possible paths
vector<vector<edge>> calculate_all_residual_paths(vector<edge> Gf){
 vector<vector<edge>> Gf_paths;
 vector<node> nodes;
 vector<vector<node>> node_paths;
 nodes = create_nodes_list(Gf);
 node_paths = calculate_all_paths(nodes[find_t_index(nodes)]);
 Gf_paths = convert_all_paths_to_edges(node_paths, Gf);
 return Gf_paths;
}

#endif
