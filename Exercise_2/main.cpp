#include <string>
#include <locale>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <unordered_set>
#include <climits>
#include <list>


struct edge {
    int start_node;
    int end_node;
    int distance;
};

struct table {
    int vertex;
    int distance;
    int previos_vector;
};


std::unordered_set<int> gather_node_indices(const std::vector<edge> &all_data){
    std::unordered_set<int> values;
    std::transform(all_data.cbegin(), all_data.cend(),
                   std::inserter(values, values.end()),
                   [](const auto& node) { return node.start_node; });
    return values;
}

std::vector<table> create_table_from_file(const std::unordered_set<int> &set_of_values,int start_node){
    std::vector<table> result_table = {};
    std::transform(set_of_values.cbegin(), set_of_values.cend(),
                   std::back_inserter(result_table),
                   [start_node](const auto& row){table a = {row,0, std::numeric_limits<int>::max()};
                                                 table b = {row,  std::numeric_limits<int>::max(),
                                                            std::numeric_limits<int>::max()};
                   return (start_node == row)?a:b;});
    return result_table;
}

std::vector<edge> read_from_file(const std::string &file){
    std::vector<edge> graph = {};
    edge node = {};
    std::ifstream open_file(file);
    if (!open_file){
        std::cout << "File do not exists"<< std::endl;
        return graph;
    }
    while(open_file>>node.start_node>>node.end_node>>node.distance){
        graph.push_back(node);
    }
    return graph;
}


bool check_if_value_is_in_container(const std::vector<int> &m_vector, int value){
    return find(m_vector.begin(), m_vector.end(), value) == m_vector.end();
}


bool min_value_condition(const std::vector<int> &list_of_visited_nodes,const table &row, int min_value){
    return check_if_value_is_in_container(list_of_visited_nodes, row.vertex) && row.distance < min_value;
}

table find_min_vector(const std::vector<int> &list_of_visited_nodes,const std::vector<table> &main_table){
    table min_value_node = {};
    int min_value = std::numeric_limits<int>::max();
    for(auto &table_entry:main_table){
        if (min_value_condition(list_of_visited_nodes, table_entry, min_value)){
            min_value = table_entry.distance;
            min_value_node = table_entry;
        }
    }
    return min_value_node;
}

bool check_if_make_changes_to_main_column(const edge &graph_data,
                                          const table &main_table_row,
                                          const table &current_node,
                                          const std::vector<int> &visited){
    return current_node.vertex == graph_data.start_node
           && check_if_value_is_in_container(visited, graph_data.end_node)
           && graph_data.end_node == main_table_row.vertex
           && current_node.distance + graph_data.distance < main_table_row.distance;
}

void set_values_to_table(table current_node,
                         const std::vector<edge> &graph,
                         std::vector<table> &main_table,
                         const std::vector<int> &visited){
    for(const auto &graph_entry : graph){
        for(auto &table_entry : main_table){
            if(check_if_make_changes_to_main_column(graph_entry,table_entry,current_node,visited)){
                table_entry.distance = graph_entry.distance + current_node.distance;
                table_entry.previos_vector = graph_entry.start_node;
            }
        }
    }
}

std::list<table> shortest_path(const table &first_element,
                               const std::vector<table> &result_table,
                               int start_node,
                               int end_node){
    std::list<table> graph_path = {};
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


table fill_up_result_table(const std::unordered_set<int> &unvisited_vector,
                           std::vector<table> &result_table,
                           std::vector<edge> &graph
                           ){
    std::vector<int> visited_vector = {};
    table current_vertex = {};
    table first_element = {};
    std::size_t size = unvisited_vector.size();
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

int check_input(const std::unordered_set<int> &set_of_values, const std::string& prompt) {
    int node = 0;
    while (std::cout << prompt){
        if (std::cin>>node){
            const auto it = set_of_values.find(node);
            if(it != set_of_values.end()){
                return node;
            }else{
                std::cout << node<< " there is no such node, please try again"<<std::endl;
            }
        }else{
            std::cout << "You have wrote bad input, please type number "<< std::endl;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return node;
}


int main(int args, char **argv){
    if(args==2){
        std::vector<edge> graph = read_from_file(argv[1]);
        if (graph.empty()){
            return EXIT_FAILURE;
        }
        auto set_of_values = gather_node_indices(graph);
        int start_node = check_input(set_of_values, "Start node: ");
        int end_node = check_input(set_of_values, "End Node: ");
        auto result_table = create_table_from_file(set_of_values, start_node);
        table first_element = fill_up_result_table(set_of_values, result_table, graph);
        auto finish = shortest_path(first_element, result_table, start_node, end_node);
        for(auto node_number: finish){
            if(finish.back().vertex != node_number.vertex) {
                std::cout << node_number.vertex << "-->";
            }else{
                std::cout << node_number.vertex << " total distance is "<< node_number.distance << std::endl;
            }
        }
        return EXIT_SUCCESS;
    }
    std::cout << "Please give path to the file as 1 parameter"<<std::endl;
    return EXIT_FAILURE;
}