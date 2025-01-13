#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <stack>
#include <limits>
#include <utility> 
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;

template <typename T> // the template allows the weight of an edge to take any numeric data type (denoted by T).
class Graph {

	public:
        
        /* define your data structure to represent a weighted undirected graph */

        vector<string> vertices;
        vector<tuple<string, string, T>> edges;
       

        /* test1 */
		Graph(); // the contructor function.
		~Graph(); // the destructor function.
		size_t num_vertices(); // returns the total number of vertices in the graph.
		size_t num_edges(); // returns the total number of edges in the graph.

        /* test2 */
        void add_vertex(const string&); // adds a vertex to the graph -- every vertex uses a string as its unique identifier.
        bool contains(const string&); // checks if a vertex is in the graph -- returns true if the graph contains the given vertex; otherwise, returns false.
        
        /* test3 */
        vector<string> get_vertices(); // returns a vector of all the vertices in the graph.

        /* test4 */
        void add_edge(const string&, const string&, const T&); // adds a weighted edge to the graph -- the two strings represent the incident vertices; the third parameter represents the edge's weight.
        bool adjacent(const string&, const string&); // check if there is an edge between the two vertices in the graph -- returns true if the edge exists; otherwise, returns false.
		
        /* test5 */
        vector<pair<string,string>> get_edges(); // returns a vector of all the edges in the graph -- each edge is represented by a pair of vertices incident to the edge.
        
        /* test6 */
        vector<string> get_neighbours(const string&); // returns a vector of all the vertices, each of which is directly connected with the given vertex by an edge.
        size_t degree(const string&); // returns the degree of a vertex.

        /* test7 */
		void remove_edge(const string&, const string&); // removes the edge between two vertices, if it exists.
        
        /* test8 */
        void remove_vertex(const string&); // delete the given vertex from the graph -- note that, all incident edges of the vertex should be deleted as well.

        /* test9 */
		vector<string> depth_first_traversal(const string&); // returns a vector of all the vertices in the visiting order of a depth-first traversal from the given vertex.
		
        /* test10 */
        vector<string> breadth_first_traversal(const string&); // returns a vector of all the vertices in the visiting order of a breadth-first traversal from the given vertex.
        
        /* test11 */
		bool contain_cycles(); // check if the graph contains any cycle -- returns true if there exists a path from a vertex to itself; otherwise, return false.
        
        /* test12 */
		Graph<T> minimum_spanning_tree(); // returns a spanning tree of the graph -- the returned tree is preferably a minimum spanning tree.
		
        bool visited_test(vector<char> v, char u) {  // Returns whether or not the vertice is in the vector 
            for (int i = 0; i < v.size(); i++) {
                if (v.at(i) == u) {
                    return true;
                } 
            }

            return false;
        };
};

/* test1 */

template <typename T>
Graph<T>::Graph() {
    vertices = {};
    edges = {};
    //Constructs empty vectors
}

template <typename T>
Graph<T>::~Graph() {
}


template <typename T>
size_t Graph<T>::num_vertices() {
    return vertices.size();
    //Uses the vector size function to get the number for vertices
}

template <typename T>
size_t Graph<T>::num_edges() {
    return edges.size();
    //Uses the vector size function to get the number for edges
}

/* test2 */

template <typename T>
void Graph<T>::add_vertex(const string& u) {
    vertices.push_back(u);
    //Uses c++ push_back function to add strings to the vector    
}

template <typename T>
bool Graph<T>::contains(const string& u) {
    //The for loop cycles through every element in the vector 
    for (int i = 0; i < vertices.size(); i++) {
        //Returns true if any element is equal to that of the string u
        if (vertices.at(i) == u) return true;
    }
    return false; //returns false if the loop fails
}

/* test3 */

template <typename T>
vector<string> Graph<T>::get_vertices() {
    return vertices; //returns the vertices vector
}

/* test4 */

template <typename T>
void Graph<T>::add_edge(const string& u, const string& v, const T& weight) {
    if (u != v) { // The if statement ensures that there are no edges to itself
    edges.push_back(tuple(u, v, weight)); // Inserts u, v, and weight in a tuple which is then added to the vector edges
    }
}

template <typename T>
bool Graph<T>::adjacent(const string& u, const string& v) { // The for loop goes through all of edges
    for (int i = 0; i < edges.size(); i++) { // The if statement checks each edge if there exists an adjacent between u and v
        // The or ensures that the order of u and v doesnt matter
        if (get<0>(edges[i]) == u && get<1>(edges[i])  == v && v != u || get<0>(edges[i])  == v && get<1>(edges[i])  == u && v != u ) {
            return true;
        }

    }
    return false;
}

/* test5 */

template <typename T>
vector<pair<string,string>> Graph<T>::get_edges() {
    vector<pair<string, string>> edges_P; // Creates a vector of pairs
    for (int i = 0 ; i < edges.size() ; i++) {   // The for loop goes though each element of the edges vector and then adds the first two elements of the tuples into a pair
        edges_P.push_back(pair(get<0>(edges[i]), get<1>(edges[i])));
    }
    return edges_P;
}

/* test6 */

template <typename T>
vector<string> Graph<T>::get_neighbours(const string& u) {
    
    vector<string> neighbours = {}; // Creates a vector of strings
    
    for (int i = 0 ; i < edges.size(); i++)  // The for loop goes through each element of edges
    {
        // The if statements look for the string u in the vector and then adds the oppositing string to the neighbours vector
        if (get<0>(edges[i]) == u) {
            neighbours.push_back(get<1>(edges[i]));
            
        }
        else if (get<1>(edges[i]) == u) {
            neighbours.push_back(get<0>(edges[i]));
            
        }
    }

    return neighbours;
}

template <typename T>
size_t Graph<T>::degree(const string& u) {
    int degree = 0; // The for loop finds the total number of adjacent strings to the string u
    for (int i = 0; i < get_neighbours(u).size(); i++) {
        degree++;
    }
    return degree;
}

/* test7 */

template <typename T>
void Graph<T>::remove_edge(const string& u, const string& v) { // The for loop looks through every element of edges
    for (int i = 0; i < edges.size(); i++) { // The if statement looks for u and v in the vector bothways
        if (get<0>(edges[i]) == u && get<1>(edges[i]) == v || get<0>(edges[i]) == v && get<1>(edges[i]) == u) {
            edges.erase(edges.begin() + i); // Erases the the element from the edges array 
        }
    }	
}

/* test8 */

template <typename T>
void Graph<T>::remove_vertex(const string& u) { // Looks for the vertex and removes it from the vector
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i] == u) {
            vertices.erase(vertices.begin() + i);
        }
    }
    
    for (int i = 0; i < edges.size(); i++) { // Looks for the vertex and removes any edges that contain it
        if (get<0>(edges[i]) == u  || get<1>(edges[i]) == u) {
            edges.erase(edges.begin() + i);
            i--;
        }    
    }
}

/* test9 */

template <typename T>
vector<string> Graph<T>::depth_first_traversal(const string& u) {
    vector<string> dft = {}; // Creates a vector for the dft
    stack<char> s; // Creates a stack for the dft

    vector<char> visited;
    
    char current_ch ;
    string current_str;

    s.push(u.at(0)); // Pushes starting number to the to stack s

    while (!s.empty()) {
        current_ch = s.top();
        s.pop();
        if (!visited_test(visited, current_ch)) { //checks if the number has been visited
            visited.push_back(current_ch); // Adds number to visited 
            current_str.push_back(current_ch);  // adds number to the queue 
            dft.push_back(current_str); // adds number to the stack
            for (int i = 0; i < get_neighbours(current_str).size(); i++) { 
                s.push( get_neighbours(current_str).at(i).at(0) ); // Looks through all adj vertices
            }  
        }
        current_str = "";
    }
    return dft;
}

/* test10 */

template <typename T>
vector<string> Graph<T>::breadth_first_traversal(const string& u) {
    vector<string> bft = {};
    queue<char> q; // queue used for breadth first traversal
    
    vector<char> visited;

    char current_ch ;
    string current_str;


    q.push(u.at(0));

    while (!q.empty()) {
        current_ch = q.front();
        q.pop();
        if (!visited_test(visited, current_ch)) { //checks if the number has been visited
            visited.push_back(current_ch); // Adds number to visited 
            current_str.push_back(current_ch); // adds number to the queue 
            bft.push_back(current_str); // adds number to the vector 
            for (int i = 0; i < get_neighbours(current_str).size(); i++) {
                q.push( get_neighbours(current_str).at(i).at(0) ); // Looks through all adj vertices
            }  
        }
        current_str = "";
    }
    return bft; // returns the bft vertex
}

/* test11 */

template <typename T>
bool Graph<T>::contain_cycles() {
    return false;
}

/* test12 */

template <typename T>
Graph<T> Graph<T>::minimum_spanning_tree() {
    return Graph<T>();
}

 
    

