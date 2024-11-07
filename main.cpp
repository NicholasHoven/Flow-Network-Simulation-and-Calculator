#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "ford_fulkerson.h"

using namespace std;

int main(){
  const string INPUT_FILE_I = "network1.txt";
  const string INPUT_FILE_II = "network2.txt";

  cout << "Input File: " << INPUT_FILE_I << "\n" << "\n";
  vector<edge> G = fill_array(INPUT_FILE_I);
  ford_fulkerson(G);

  cout << "Input File: " << INPUT_FILE_II << "\n" << "\n";
  G = fill_array(INPUT_FILE_II);
  ford_fulkerson(G);

  return 0;
}


