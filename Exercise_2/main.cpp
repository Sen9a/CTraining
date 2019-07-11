#include <string>
#include <locale>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <climits>
#include <list>

using namespace std;

struct nodes {
    int start_node;
    int end_node;
    int distance;
};

struct table {
    int vertex;
    int distance;
    int previos_vector;
};


vector<int> create_set_of_values_from_file(const vector<nodes> &all_data){
    vector<int> set_of_values = {};
    for(int i=0; i < all_data.size(); ++i){
        if(find(set_of_values.begin(), set_of_values.end(), all_data[i].start_node) == set_of_values.end()){
            set_of_values.push_back(all_data[i].start_node);
        }
    }
    return set_of_values;
}

vector<table> create_table_from_file(const vector<int> &set_of_values, int start_node){
    vector<table> result_table = {};
    table row = {};
    for (int i=0;i <set_of_values.size(); ++i) {
        if (set_of_values[i] == start_node) {
            row = {set_of_values[i], 0, INT_MAX};
        } else {
            row = {set_of_values[i], INT_MAX, INT_MAX};
        }
        result_table.push_back(row);
    }
    return result_table;
}

vector<nodes> read_from_file(const string &file){
    string text;
    vector<nodes> graph = {};
    nodes node = {};
    ifstream open_file(file);
    if (!open_file){
        cout << "File do not exists"<< endl;
        return graph;
    }
    while(open_file>>node.start_node>>node.end_node>>node.distance){
        graph.push_back(node);
    }
    return graph;
}

table find_min_vector(const vector<int> &list_of_visited_nodes, vector<table> &main_table){
    table min_value_node = {};
    int min_value = INT_MAX;
    for(int i = 0;i< main_table.size(); ++i){
        if (find(list_of_visited_nodes.begin(), list_of_visited_nodes.end(), main_table[i].vertex) ==
        list_of_visited_nodes.end() && main_table[i].distance < min_value){
            min_value = main_table[i].distance;
            min_value_node = main_table[i];
        }
    }
    return min_value_node;
}

void set_values_to_table(table current_node,
                         const vector<nodes> &graph,
                         vector<table> &main_table,
                         vector<int> visited){
    for(int i = 0; i < graph.size(); ++i){
        for(int j = 0; j < main_table.size(); ++j){
            if(current_node.vertex == graph[i].start_node
               && find(visited.begin(), visited.end(), graph[i].end_node) == visited.end()
               && graph[i].end_node == main_table[j].vertex
               && current_node.distance+graph[i].distance < main_table[j].distance){
                main_table[j].distance = graph[i].distance + current_node.distance;
                main_table[j].previos_vector = graph[i].start_node;
            }
        }
    }
}

list<table> shortest_path(const table &first_element, vector<table> &result_table, int start_node, int end_node){
    list<table> graph_path = {};
    int i = 0;
    while(end_node != start_node){
        if(result_table[i].vertex == end_node){
            graph_path.push_front(result_table[i]);
            end_node = result_table[i].previos_vector;
            i=0;
        }else{
            ++i;
        }
    }
    graph_path.push_front(first_element);
    return graph_path;
}


table fill_up_result_table(const vector<int> &unvisited_vector,
                           vector<table> &result_table,
                           vector<nodes> &graph
                           ){
    vector<int> visited_vector = {};
    table current_vertex = {};
    table first_element = {};
    int size = unvisited_vector.size();
    while (visited_vector.size() != size) {
        current_vertex = find_min_vector(visited_vector, result_table);
        if (visited_vector.empty()) {
            first_element = current_vertex;
        }
        visited_vector.push_back(current_vertex.vertex);
        set_values_to_table(current_vertex, graph, result_table, visited_vector);
    }
    return first_element;
}

int check_input(vector<int> set_of_values, bool start) {
    int node = 0;
    string display;
    if(start){
        display = "Start node: ";
    }else{
        display = "End node: ";
    }
    while (cout << display){
        if (cin>>node){
            if(find(set_of_values.begin(), set_of_values.end(), node) != set_of_values.end()){
                break;
            }else{
                cout << node<< " there is no such node, please try again"<<endl;
            }
        }else{
            cout << "You have wrote bad input, please type number "<< endl;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    return node;
}


int main(int args, char **argv){
    if(args==2){
        vector<nodes> graph = read_from_file(argv[1]);
        if (graph.empty()){
            return EXIT_FAILURE;
        }
        vector<int> set_of_values = create_set_of_values_from_file(graph);
        int start_node = check_input(set_of_values, true);
        int end_node = check_input(set_of_values, false);
        auto result_table = create_table_from_file(set_of_values, start_node);
        table first_element = fill_up_result_table(set_of_values, result_table, graph);
        list<table> finish = shortest_path(first_element, result_table, start_node, end_node);
        for(auto node_number: finish){
            if(finish.back().vertex != node_number.vertex) {
                cout << node_number.vertex << "-->";
            }else{
                cout << node_number.vertex << " total distance is "<< node_number.distance << endl;
            }
        }
        return EXIT_SUCCESS;
    }
    cout << "Please give path to the file as 1 parameter"<<endl;
    return EXIT_FAILURE;
}