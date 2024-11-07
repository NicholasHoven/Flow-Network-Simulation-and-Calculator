#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#include "helper_functions.h"
#include <cassert>

//Description: algorithm calculates the max flow in the network
//Precondtions: G.size() > 0
//Postcondtions: the max flow in the system is calculated 
void ford_fulkerson(vector<edge> G){
  assert(G.size() > 0); //PRECONDITION Asserts that the the given graph is not empty
  vector<node> nodes;
  vector<edge> current_path;
  vector<edge> Gf; //represents the residual graph
  vector<vector<edge>> Gf_paths;
  vector<vector<node>> node_paths;
  nodes = create_nodes_list(G);
  node_paths = calculate_all_paths(nodes[nodes.size()-1]);
  Gf_paths = convert_all_paths_to_edges(node_paths, G);
  int path_rc;

  cout << "Input:" << "\n";
  for(int i = 0; i < int(G.size()); i++){
    cout << G[i].u << "," << G[i].v << "," << G[i].capacity << "\n";
  }
  cout << "\n";

  while(1 == 1){
    for(int i = 0; i < int(Gf_paths.size()); i++){ //finds path p in residual network
      if(flow_available(Gf_paths[i]) == true){
        current_path = Gf_paths[i];
        break;
      }
    }
    if(current_path.size() > 0){
     path_rc = calculate_min_cf(current_path); //returns the residual capacity of the current path
    }else{
      break;
    }
    assert(current_path.size() > 0); //LOOP INVARIENT
    for(int i = 0; i < int(current_path.size()); i++){
      if(exists_in_list(current_path[i], G)){
        current_path[i].flow += path_rc;
      }
      else{
        G[find_opposite_index(current_path[i], G)].flow -= path_rc;
      }
    }
    update_graph(current_path, G);
    update_residual_graph(G, Gf);
    Gf_paths = calculate_all_residual_paths(Gf);
    if(Gf_paths.size() < 1){
      break;
    }
    current_path.clear();
  }
  print_graph(G);
  cout << "\n" << "Max flow in this network is " <<  calculate_total_flow(G) << "\n" << "\n";
  //assert(calculate_source_flow(G) == calculate_total_flow(G)); //POSTCONDITION: Asserts that the source flow is equal to the sink flow
}

#endif
