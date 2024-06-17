#pragma once
#include "Circular_Doubly_Linked_List.h"
#include "Array_Sort.h"
#include <iostream>
#include <vector>
#include <queue> 
#include <string>
#include <stack> 
#include <limits>
using namespace std;

class Graph {
private:
    vector<Circle*> My_Graph;
    int num_v;

    void for_depth_search(int v, vector<bool>& visited) {
        stack<int> stack; 
        stack.push(v); 

        while (!stack.empty()) { 
            int vertex = stack.top();
            stack.pop(); 

            if (!visited[vertex]) { 
                cout << vertex << " "; 
                visited[vertex] = true; 
            }

            Circle* node = My_Graph[vertex];

            if (node != nullptr) { 
                vector<int> neighbors;
                do {
                    if (!visited[node->vertex]) {
                        neighbors.push_back(node->vertex);
                    }
                    node = node->next;
                } while (node != My_Graph[vertex]); 
                long n = neighbors.size();
                bubble_Sort(neighbors, n);
                for (int neighbor : neighbors) {
                    stack.push(neighbor);
                }
            }
        }
    }

    void for_breadth_search(int start_vertex, vector<bool>& visited) {
        queue<int> q;
        q.push(start_vertex); 

        while (!q.empty()) {
            int vertex = q.front(); 
            q.pop(); 

            if (!visited[vertex]) { 
                cout << vertex << " "; 
                visited[vertex] = true; 
            }

            Circle* node = My_Graph[vertex];

            if (node != nullptr) { 
                vector<int> neighbors;
                do {
                    if (!visited[node->vertex]) {
                        neighbors.push_back(node->vertex);
                    }
                    node = node->next;
                } while (node != My_Graph[vertex]);
                long n = neighbors.size();
                bubble_Sort(neighbors, n);
                for (int neighbor : neighbors) {
                    q.push(neighbor); 
                }

            }
        }
        cout << "\n";
    }
public:

    Graph(int v) : num_v(v), My_Graph(v, nullptr) {} 

    ~Graph() { 
        for (int i = 0; i < num_v; ++i) {
            delete_List(My_Graph[i]);
        }

    }

    void delete_vertex(int vertex) { 
        if (vertex >= num_v) {
            return;
        }

        for (int i = 0; i < num_v; ++i) {
            delete_from_list(My_Graph[i], vertex);
        }

        delete_List(My_Graph[vertex]); 
        My_Graph.erase(My_Graph.begin() + vertex);
        num_v--;


        for (int i = 0; i < num_v; ++i) {
            Circle* current = My_Graph[i];
            if (current) {
                do {
                    if (current->vertex > vertex) {
                        current->vertex--;
                    }
                    current = current->next;
                } while (current != My_Graph[i]);
            }
        }
    }

    void add_edge(int first, int second, int weight) { 
        add_to_list(My_Graph[first], second, weight);
        add_to_list(My_Graph[second], first, weight);
    }

    void delete_edge(int first, int second) { 
        delete_from_list(My_Graph[first], second);
        delete_from_list(My_Graph[second], first);
    }

    void print_graph() { 
        for (int i = 0; i < num_v; ++i) {
            cout << "Vertex " << i << ": ";
            print_list(My_Graph[i]);
        }
    }


    void depth_search(int start_vertex) {  
        vector<bool> visited(num_v, false); 
        for_depth_search(start_vertex, visited);
        cout << "\n";
    }

    void breadth_search(int start_vertex) {
        vector<bool> visited(num_v, false); 
        for_breadth_search(start_vertex, visited);
        cout << "\n";
    }

    void algorithm_Prim() {
        int V = num_v; 
        vector<int> minimal_tree(V, -1);  
        vector<int> key(V, numeric_limits<int>::max()); 
        vector<bool> in_minimal_tree(V, false);  

        key[0] = 0; 
        minimal_tree[0] = -1;  

        for (int i = 0; i < V - 1; i++) {
            int u = -1;
            int min_path = numeric_limits<int>::max();
            for (int j = 0; j < V; j++) {
                if ((!in_minimal_tree[j]) && (key[j] < min_path)) {
                    min_path = key[j];
                    u = j;
                }
            }

            in_minimal_tree[u] = true;

            Circle* node = My_Graph[u];
            if (node != nullptr) {
                do {
                    int v = node->vertex;
                    int weight = node->weight;
                    if ((!in_minimal_tree[v]) && (weight < key[v])) {
                        minimal_tree[v] = u;
                        key[v] = weight;
                    }
                    node = node->next;
                } while (node != My_Graph[u]);
            }
        }

        cout << "Edge \tWeight\n";
        int total_weight = 0;
        for (int i = 1; i < V; ++i) {
            cout << minimal_tree[i] << " - " << i << " \t" << key[i] << " \n";
            total_weight += key[i];
        }
        cout << "Total weight: " << total_weight << "\n";
    }

};
