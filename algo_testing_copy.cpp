#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <fstream>
#include <list>
#include <algorithm>
#include <chrono>
#include <random>
enum {TEST_QUANTITY = 30};

using std::vector, std::set, std::priority_queue, std::ifstream, std::mt19937, std::random_device,\
std::list, std::cout, std::cin, std::endl, std::find, std::set_difference, std::uniform_int_distribution, \
std::set_union, std::inserter, std::string, std::ofstream, std::ws, std::chrono::high_resolution_clock, \
std::chrono::microseconds, std::chrono::duration_cast;


struct LexCompare {
    bool operator() (const set<int>& a, const set<int>& b) const {
        return lexicographical_compare(b.begin(), b.end(), a.begin(), a.end());
    }
};

using Graph =  vector<set<int> >;
using MISet = set<int>;
using PriorityQueue = priority_queue<MISet, vector<MISet>, LexCompare>;
using SetOfSets = std::set<std::set<int> >;

bool containsSet(const SetOfSets& setOfSets, const std::set<int>& set) {
    return setOfSets.find(set) != setOfSets.end();
}


void Print_MISet(const MISet& set_inp){
    for (int vertex : set_inp) {
        cout << vertex << " ";
    }
    cout << endl;
}


void GenerateTest(const string& filename, int n){
    ofstream file(filename);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, n - 1);

    for (int i = 0; i < (n * (n - 1))  / 2; ++i) {
        int random_number1 = distrib(gen);
        int random_number2 = distrib(gen);

        file << random_number1 << " " << random_number2 << endl;
    }
}


inline bool IsIn(const set<int>&set_inp, int v_inp){
    return set_inp.find(v_inp) != set_inp.end();
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
    SetOfSets already_printed;
    ofstream file_outp;
    file_outp.open("output8.txt");

    for(int k = 0; k < 400; k++){
        int n = 0;
        for(int rep = 0; rep < TEST_QUANTITY; rep++) {
            GenerateTest("input.txt", n);
            ifstream file_inp;
            file_inp.open("input.txt");

            Graph G(n);

            int v1, v2;
            while (file_inp >> v1) {
                if (file_inp >> v2) {
                    G[v1].insert(v2);
                    G[v2].insert(v1);
                }
            }
            file_inp.close();

            for (size_t i = 0; i < G.size(); ++i) {
                cout << "Вершина " << i << ": ";
                for (int adjVertex: G[i]) {
                    cout << adjVertex << " ";
                }
                cout << endl;
            }
            std::ofstream file("output8.txt", ofstream::app);

            MISet S_first, S;
            S_first = FindFirstMIS(G, n, S_first);
            PriorityQueue Q;
            Q.push(S_first);
            auto start = high_resolution_clock::now();
            while (!Q.empty()) {
                S = Q.top();
                Print_MISet(S);
                Q.pop();
                start = high_resolution_clock::now();
                for (int j = 0; j < n; ++j) { // перебираем j до масимальной вершны в С
                    bool flag = false;
                    for (int neighbour: G[j]) { //перебираем н из соседей j
                        if (IsIn(S, neighbour) && neighbour < j) {
                            flag = true;
                        }
                    }
                    if (flag) {
                        MISet Sj = FirstJVertices(S, j), Sjtmp;
                        set_difference(Sj.begin(), Sj.end(), G[j].begin(), G[j].end(), inserter(Sjtmp, Sjtmp.begin()));
                        Sjtmp.insert(j);
                        if (IsMaximal(Sjtmp, G, j)) {
                            MISet T = FindFirstMIS(G, n, Sjtmp);
                            if (!containsSet(already_printed, T)) {
                                Q.push(T);
                                already_printed.insert(T);
                            }
                        }
                    }
                }
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                file << duration.count() << "," << n << endl;
                cout << "Время выполнения: " << duration.count() << " микросекунд, n = " << n << endl;
            }
            n += 1;
        }
    }
    file_outp.close();
    return 0;
}
