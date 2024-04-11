#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <stdexcept>
#include <fstream>
#include <list>
#include <algorithm>

using std::vector, std::set, std::priority_queue, std::ifstream, std::runtime_error, std::out_of_range, \
std::exception, std:: invalid_argument, std::list, std::cout, std::cin, std::endl, std::find, std::set_difference, \
std::set_union, std::inserter, std::string, std::ofstream, std::ws;



struct LexCompare {
    bool operator() (const set<int>& a, const set<int>& b) const {
        return lexicographical_compare(b.begin(), b.end(), a.begin(), a.end());
    }
};

using Graph =  vector<set<int> >;
using MISet = set<int>;
using PriorityQueue = priority_queue<MISet, vector<MISet>, LexCompare>;
using SetOfSets = std::set<std::set<int> >;


void Print_MISet(const MISet& set_inp){
    for (int vertex : set_inp) {
        cout << vertex << " ";
    }
    cout << endl;
}


void Print_MISetToFile(const MISet& set_inp, const string& filename){
    ofstream file(filename, ofstream::app);
    for (int vertex : set_inp) {
        file << vertex << " ";
    }
    file << endl;
}

inline bool IsIn(const set<int>&set_inp, int v_inp){
    return set_inp.find(v_inp) != set_inp.end();
}

bool containsSet(const SetOfSets& setOfSets, const std::set<int>& set) {
    return setOfSets.find(set) != setOfSets.end();
}


bool IsMaximal(const MISet &set_inp, const Graph &graph_inp, int j) {
    vector<bool> adjVec(j + 1, false);
    for (int v: set_inp) {
        if (v <= j ) {
            adjVec[v] = true; // Отметили вершину из Stmp
            for (int u: graph_inp[v]) {
                if (u <= j) adjVec[u] = true; // Отметили смежные вершины
            }
        }
    }
    for (int i = 0; i <= j; ++i) {
        if (!adjVec[i]) return false;
    }
    return true;
}

MISet FirstJVertices (const MISet &set_inp, int j){
    MISet Sj;
    for (int elem : set_inp) {
        if (elem <= j) {
            Sj.insert(elem);
        }
        else break;
    }
    return Sj;
}


MISet FindFirstMIS(const Graph& G, int n, MISet set_inp) {
    vector<bool> availabilityVec(n, true);

    for (int init_vertex : set_inp) {
        availabilityVec[init_vertex] = false;  // Сама вершина
        for (int neighbour : G[init_vertex]) {
            availabilityVec[neighbour] = false;  // Соседи
        }
    }
    for (int i = 0; i < n; ++i) {
        if (availabilityVec[i]) {
            set_inp.insert(i);
            for (int neighbour: G[i]) {
                availabilityVec[neighbour] = false;
            }
        }
    }
    return set_inp;
}



int main() {
    ifstream file_inp;
    SetOfSets already_printed;

    try {
        file_inp.open("input.txt");
        if (!file_inp.is_open()) {
            throw runtime_error("Couldn't open input file");
        }

        int numVertices;
        if (!(file_inp >> numVertices)) {
            throw runtime_error("Wrong format");
        }

        Graph G (numVertices);

        int v1, v2;
        while (file_inp >> v1) {
            if (file_inp >> v2) {
                if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices) {
                    throw out_of_range("Vertex index out of range");
                }
                G[v1].insert(v2);
                G[v2].insert(v1);
            }
            else throw invalid_argument("Invalid argument number");
        }
        file_inp.close();

        ofstream file_outp;
        file_outp.open("output.txt");
        if (!file_outp.is_open()) {
            throw runtime_error("Couldn't open output file");
        }

        // Вывод графа(отладка)
        /* for (size_t i = 0; i < G.size(); ++i) {
            cout << "Вершина " << i << ": ";
            for (int adjVertex: G[i]) {
                cout << adjVertex << " ";
            }
            cout << endl;
        }*/

        MISet S_first, S;
        S_first = FindFirstMIS(G, numVertices, S_first);
        PriorityQueue Q;
        Q.push(S_first);
        while (!Q.empty()){
            S = Q.top();
            Print_MISetToFile(S, "output.txt");
            Q.pop();
            for (int j = 0; j < numVertices; ++j){ // перебираем j до масимальной вершны в С
                bool flag = false;
                for (int neighbour : G[j]) { //перебираем н из соседей j
                    if (IsIn(S, neighbour) && neighbour < j) {flag = true; break;}
                }
                if (flag){
                    MISet Sj = FirstJVertices(S, j), Sjtmp;
                    set_difference(Sj.begin(), Sj.end(), G[j].begin(), G[j].end(), inserter(Sjtmp, Sjtmp.begin()));
                    Sjtmp.insert(j);
                    if (IsMaximal(Sjtmp, G, j)) {
                        MISet T = FindFirstMIS(G, numVertices, Sjtmp);
                        if (!containsSet(already_printed, T)){
                            Q.push(T);
                            already_printed.insert(T);
                        }
                    }
                }
            }
        }
        file_outp.close();
    }

    catch (const exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

