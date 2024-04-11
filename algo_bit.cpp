#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <stdexcept>
#include <fstream>
#include <list>
#include <algorithm>
#include <bitset>

using std::vector, std::set, std::priority_queue, std::ifstream, std::runtime_error, std::out_of_range, \
std::exception, std:: invalid_argument, std::list, std::cout, std::cin, std::endl, std::find, std::set_difference, \
std::set_union, std::inserter, std::string, std::ofstream, std::ws, std::bitset;

enum {SIZE = 32};

class BitSet {
private:
    bitset<SIZE> bits;
public:
    BitSet(const std::set<int>& set) {
        for (int elem : set) {
            if (elem >= 0 && elem < 32) {
                bits.set(elem);
            }
        }
    }


    bool test(int pos) const {
        return bits.test(pos);
    }

    // Вывод множества
    void print() const {
        for (int i = 0; i < 32; ++i) {
            if (bits[i]) {
                std::cout << i << " ";
            }
        }
        std::cout << std::endl;
    }
    void printprint() const {
        std::cout << bits << std::endl;
    }


    // Функция, возвращающая множество (set) из битсета
    std::set<int> toSet() const {
        std::set<int> resultSet;
        for (int i = 0; i < 32; ++i) {
            if (bits[i]) {
                resultSet.insert(i);
            }
        }
        return resultSet;
    }
};


struct BitSetCompare {
    bool operator()(const BitSet& a, const BitSet& b) const {
        for (int i = 0; i < 32; ++i) {
            if (a.test(i) != b.test(i)) {
                return a.test(i) < b.test(i);
            }
        }
        return false; // Если все биты равны, считаем множества равными
    }
};

using Graph = vector<set<int> >;
using MISet = set<int>;
using PriorityQueue = priority_queue<BitSet, vector<BitSet>, BitSetCompare>;
using SetOfSets = std::set<std::set<int> >;


void Print_MISet(const MISet& set_inp){
    for (int vertex : set_inp) {
        cout << vertex << " ";
    }
    cout << endl;
}


void Print_MISetToFile(const MISet& set_inp, const string& filename){
    std::ofstream file(filename, ofstream::app);
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

        int numVertices;
        (file_inp >> numVertices);

        Graph G (numVertices);

        int v1, v2;
        while (file_inp >> v1) {
            if (file_inp >> v2) {
                G[v1].insert(v2);
                G[v2].insert(v1);
            }
        }
        file_inp.close();

        ofstream file_outp;
        file_outp.open("output.txt");


        MISet S_first, S;
        S_first = FindFirstMIS(G, numVertices, S_first);
        BitSet S_first_bit = BitSet(S_first);
        PriorityQueue Q;
        Q.push(S_first_bit);
        while (!Q.empty()){
            S = (Q.top()).BitSet::toSet();
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
                            BitSet T_bit = BitSet(T);
                            Q.push(T_bit);
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