

#ifndef PROJECT_Q4_H
#define PROJECT_Q4_H

#include <iostream>
#include <string>
#include "graphtypes.h"
#include "queue.h"
#include "set.h"
#include "console.h"
#include "vector.h"
#include <fstream>
#include "filelib.h"
using namespace std;

/* Function prototypes */

void initiateGraph(SimpleGraph & g);
void writeGraph(const SimpleGraph & g, ostream & out);
void addFlight(SimpleGraph & airline, string c1, string c2, int miles);
void addNode(SimpleGraph & g, string name);
void addArc(SimpleGraph & g, Node *n1, Node *n2, double cost);
bool pathExistsBFS(Node *n1, Node *n2);
bool pathExistsDFS(Node *n1, Node *n2);
bool pathExistsVisitedDFS(Node *n1, Node *n2, Set<Node *> & visited, Vector<Node *> path);
void printPath(Vector<Node *> path);
void printResult(bool resD, bool resB, string const start, string const end);

/* Main program */

void P4() {
    //First construct a simple graph and print it out
    // by iteratively accessing all edges
    SimpleGraph airline;
    initiateGraph(airline);

    ofstream outfile;
    promptUserForFile(outfile, "Graph description Output file: "); //Required to be like "Descrip.txt"
    //Write the description into the output file
    writeGraph(airline, outfile);

    //User input the start position (airport name, For example, “Altanta”)
    // and the end position (airport name, for example, “Denver”)
    cout << "Starting city: ";
    string start;
    getline(cin, start);
    cout << "Ending city: ";
    string end;
    getline(cin, end);
    cout << endl;

    //do BFS and DFS search and print out the path if there exists
    cout << "Breadth-first search path: " << endl;
    bool resB = pathExistsBFS(airline.nodeMap[start], airline.nodeMap[end]);
    cout << "Depth-first search path: " << endl;
    bool resD = pathExistsDFS(airline.nodeMap[start], airline.nodeMap[end]);

    //print out total paths number - conclusion
    printResult(resD, resB, start, end);

}

/*
 * Function: printAdjacencyLists
 * Usage: printAdjacencyLists(g);
 * ------------------------------
 * Prints the adjacency list for each city in the graph.
 */

void writeGraph(const SimpleGraph & g, ostream & out) {
    for (Node *node : g.nodes) {
        out << node->name << " -> ";
        bool first = true;
        for (Arc *arc : node->arcs) {
            if (!first) out << ", ";
            out << arc->finish->name;
            first = false;
        }
        out << endl;
    }
}

/*
 * Function: initAirlineGraph
 * Usage: initAirlineGraph(airline);
 * ---------------------------------
 * Initializes the airline graph to hold the flight data from Figure 18-2.
 * In a real application, the program would almost certainly read this
 * information from a data file.
 */

void initiateGraph(SimpleGraph & g) {
    addNode(g, "Atlanta");
    addNode(g, "Boston");
    addNode(g, "Chicago");
    addNode(g, "Dallas");
    addNode(g, "Denver");
    addNode(g, "Los Angeles");
    addNode(g, "New York");
    addNode(g, "Portland");
    addNode(g, "San Francisco");
    addNode(g, "Seattle");
    addFlight(g, "Atlanta", "Chicago", 599);
    addFlight(g, "Atlanta", "Dallas", 725);
    addFlight(g, "Atlanta", "New York", 756);
    addFlight(g, "Boston", "New York", 191);
    addFlight(g, "Boston", "Seattle", 2489);
    addFlight(g, "Chicago", "Denver", 907);
    addFlight(g, "Dallas", "Denver", 650);
    addFlight(g, "Dallas", "Los Angeles", 1240);
    addFlight(g, "Dallas", "San Francisco", 1468);
    addFlight(g, "Denver", "San Francisco", 954);
    addFlight(g, "Portland", "San Francisco", 550);
    addFlight(g, "Portland", "Seattle", 130);
}

/*
 * Function: addFlight
 * Usage: addFlight(airline, c1, c2, miles);
 * -----------------------------------------
 * Adds an arc in each direction between the cities c1 and c2.
 */

void addFlight(SimpleGraph & airline, string c1, string c2, int miles) {
    Node *n1 = airline.nodeMap[c1];
    Node *n2 = airline.nodeMap[c2];
    addArc(airline, n1, n2, miles);
    addArc(airline, n2, n1, miles);
}

/*
 * Function: addNode
 * Usage: addNode(g, name);
 * ------------------------
 * Adds a new node with the specified name to the graph.
 */

void addNode(SimpleGraph & g, string name) {
    Node *node = new Node;
    node->name = name;
    g.nodes.add(node);
    g.nodeMap[name] = node;
}

/*
 * Function: addArc
 * Usage: addArc(g, n1, n2, cost);
 * -------------------------------
 * Adds a directed arc to the graph connecting n1 to n2.
 */

void addArc(SimpleGraph & g, Node *n1, Node *n2, double cost) {
    Arc *arc = new Arc;
    arc->start = n1;
    arc->finish = n2;
    arc->cost = cost;
    g.arcs.add(arc);
    n1->arcs.add(arc);
}


// The pathExistsDFS function is a wrapper for pathExistsVisited,
// which takes an extra parameters to record the set of visited nodes.
bool pathExistsDFS(Node *n1, Node *n2) {
    Set<Node *> visited;
    Vector<Node *> path;
    return pathExistsVisitedDFS(n1, n2, visited, path);
}

//recursively call to find a DFS path
bool pathExistsVisitedDFS(Node *n1, Node *n2, Set<Node *> & visited, Vector<Node *> path) {
    if (n1 == n2) {
        visited.add(n1);
        path.add(n1);
        printPath(path);
        return true;
    }
    if (visited.contains(n1)) return false;
    visited.add(n1);
    path.add(n1);
    for (Arc *arc : n1->arcs) //Recurrsive for all the vertices adjacent to current vertex
    {   if (!visited.contains(arc->finish)){
            if (pathExistsVisitedDFS(arc->finish, n2, visited, path)) return true;
        }
    }
    path.remove(path.size()-1);
    return false;
}


bool pathExistsBFS(Node *n1, Node *n2){
    //create a set which stores nodes that have already visited
    Set<Node *> visited;
    //create a queue which stores the paths
    Queue<Vector<Node *>> queue;
    //path vector to store the current path
    Vector<Node *> path;
    path.push_back(n1);
    queue.enqueue(path);
    while (!queue.isEmpty()) {
        path = queue.front();
        queue.dequeue();
        Node *node = path[path.size()-1];
        if (node == n2){
            printPath(path);
            return true;
        }
        if (!visited.contains(node)) {
            visited.add(node);
            for (Arc *arc : node->arcs) {
                Vector<Node *> newpath(path);
                newpath.push_back(arc->finish);
                queue.enqueue(newpath);
            }
        }
    }
    return false;
}


void printPath(Vector<Node *> path) {
    int size = path.size();
    for (int i = 0; i < size; i++)
        cout << path[i]->name << " -> ";
    if (size == 0){
        cout << "NONE" << endl;
    }else cout << "FINISH" << endl;
}


void printResult(bool resD, bool resB, string const start, string const end){
    if (resD && resB) {
        cout << "There are two paths from " << start << " to " << end << "." << endl;
    }else if (!resD && !resB) {
        cout << "There is no paths from " << start << " to " << end << "!" << endl;
    }else cout << "There are only one paths from " << start << " to " << end << "." << endl;
}


#endif