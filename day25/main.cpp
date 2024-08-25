#include "parse.h"
#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

const int GRAPH_SIZE = 2000;
int key_idx = 0;

int getNodeNumber(map<string, int> &keys, string node) {

  if (keys.find(node) == keys.end()) {
    // Assign the node name to a row, and increment
    keys[node] = key_idx;
    key_idx++;
    return key_idx - 1;
  } else {
    return keys[node];
  }
}

int main() {

  srand(time(NULL));
  fstream inputFile("aoc.txt");

  if (!inputFile.is_open()) {
    cout << "Error opening file" << endl;
    return -1;
  }

  char graph[GRAPH_SIZE][GRAPH_SIZE];

  // Initialize to 0's
  for (int i = 0; i < GRAPH_SIZE; i++) {
    for (int j = 0; j < GRAPH_SIZE; j++) {
      graph[i][j] = 0;
    }
  }

  map<string, int> keyMap;

  while (inputFile.good()) {
    string buffer;
    getline(inputFile, buffer);
    if (inputFile.eof()) {
      continue;
    }
    vector<string> tokens = splitString(buffer, ' ');

    auto tok_itr = tokens.begin();

    string root = (*tok_itr).substr(0, (*tok_itr).length() - 1);
    tok_itr++;

    int rootNum = getNodeNumber(keyMap, root);

    while (tok_itr != tokens.end()) {
      string node = *tok_itr;
      if (node.length() < 3) {
        break;
      }
      int colNum = getNodeNumber(keyMap, node);

      // Add in both directions.
      graph[rootNum][colNum] = 1;
      graph[colNum][rootNum] = 1;
      tok_itr++;
    }
  }

  short edges = 0;

  map<int, string> keyMapCopy;

  char graphCopy[GRAPH_SIZE][GRAPH_SIZE];

  bool loopOK = true;
  while (edges != 3 || loopOK == false) {

    keyMapCopy.clear();
    // Begin mutating a copy of the graph

    // Deep copy of graph

    for (int i = 0; i < GRAPH_SIZE; i++) {
      for (int j = 0; j < GRAPH_SIZE; j++) {
        graphCopy[i][j] = graph[i][j];
      }
    }

    // Deep copy of keyset.

    for (auto pear : keyMap) {
      keyMapCopy[pear.second] = pear.first;
    }

    loopOK = true;
    // go until only 2 nodes remain
    while (keyMapCopy.size() > 2) {
      // collapsing node algorithm

      // Step 1: Select a node at random
      int key = rand() % keyMapCopy.size();

      auto key_iter = keyMapCopy.begin();

      for (int i = 0; i < key; i++) {
        key_iter++;
      }

      int growingNode = key_iter->first;
      string grNodeName = key_iter->second;

      // Step 2: Get list of adjacent nodes
      vector<int> linkedNodes;

      for (int i = 0; i < GRAPH_SIZE; i++) {
        if (graphCopy[growingNode][i] > 0) {
          linkedNodes.push_back(i);
        }
      }

      if (linkedNodes.size() == 0) {
        // We split the world somehow? Restart
        loopOK = false;
        break;
      }

      // Step 3: Select linked node at random

      key = rand() % linkedNodes.size();

      int erasingNode = linkedNodes.at(key);

      // Fold erasing node into growing node
      for (int i = 0; i < GRAPH_SIZE; i++) {
        graphCopy[growingNode][i] += graphCopy[erasingNode][i];
        graphCopy[i][growingNode] += graphCopy[i][erasingNode];
        graphCopy[i][i] = 0;
        graphCopy[erasingNode][i] = 0;
        graphCopy[i][erasingNode] = 0;
      }

      // Step 4: find the key of the erasing nodes
      string erNodeName = keyMapCopy[erasingNode];

      //    cout << "Merging " << erNodeName << " into " << grNodeName << endl;

      keyMapCopy[growingNode] = grNodeName + "," + erNodeName;

      keyMapCopy.erase(erasingNode);

      /* cout << "==============================" << endl;
       for (auto pear : keyMapCopy) {
         cout << pear.first << " -> " << pear.second << endl;
       }
       cout << "==============================" << endl;*/
    }

    int keys[2];
    int idx = 0;

    for (auto thing : keyMapCopy) {
      keys[idx] = thing.first;
      idx++;
    }

    edges = graphCopy[keys[0]][keys[1]];
  }

  auto kmcItr = keyMapCopy.begin();

  vector<string> nodeNamesFirst = splitString(kmcItr->second, ',');

  kmcItr++;

  vector<string> nodeNamesSecond = splitString(kmcItr->second, ',');

  cout << "result: " << nodeNamesFirst.size() * nodeNamesSecond.size() << endl;

  // End graph mutation.

  /******
   * PRINTING THE GRAPH
   **/
  /*cout << "========================================" << endl << "     ";
  for (int i = 0; i < GRAPH_SIZE; i++) {
    cout << setw(4) << i;
  }
  cout << endl;
  for (int row = 0; row < GRAPH_SIZE; row++) {
    cout << setw(4) << row << ":";
    for (int col = 0; col < GRAPH_SIZE; col++) {
      cout << setw(4) << graphCopy[row][col];
    }
    cout << endl;
  }
  cout << endl;
  cout << "========================================" << endl;
*/
  /*for (auto pear : keyMap) {
    cout << pear.first << " -> " << pear.second << endl;
  }*/

  return 0;
}
