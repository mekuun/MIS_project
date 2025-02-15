# Результаты тестирования алгоритма на корректность

### Unit-тестирование функций

#### Ограничение множества до j-й вершинами

```cpp
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
```

| Тест                     | Результат                                               |
| ------------------------ | ------------------------------------------------------- |
| S `{1, 3, 4}`<br/>j `0`  | <span style="color:rgba(16,185,129,1)">{}</span>        |
| S `{1, 3, 4}` <br/>j `1` | <span style="color:rgba(16,185,129,1)">{1}</span>       |
| S `{1, 3, 4}` <br/>j `2` | <span style="color:rgba(16,185,129,1)">{1}</span>       |
| S `{1, 3, 4}`<br/>j `3`  | <span style="color:rgba(16,185,129,1)">{1, 3}</span>    |
| S `{1, 3, 4}`<br/>j `4`  | <span style="color:rgba(16,185,129,1)">{1, 3, 4}</span> |
| S `{1, 3, 4}`<br/>j `10` | <span style="color:rgba(16,185,129,1)">{1, 3, 4}</span> |





#### Проверка на максимальность независимого множества до вершины j

Здесь и далее граф представлен в виде списка смежности.

```cpp
bool IsMaximal(const set<int>&set_inp, const vector<set<int> >&graph_inp, int j){
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
```

| Описание                                   | Тест                                                                                                                 | Результат                                           |
| ------------------------------------------ | -------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------- |
| Пустой граф, пустое множество              | graph_inp  `0:{}1:{} 2:{} 3:{} 4:{} 0:{}` <br/>set_inp `{}`<br/>j `4`                                                | <span style="color:rgba(16,185,129,1)">false</span> |
| Пустой граф, 3/4 рёбер                     | graph_inp `0:{} 1:{} 2:{} 3:{} 4:{}`<br/>set_inp  `{0 1 2 3}` <br/>j  `4`                                            | <span style="color:rgba(16,185,129,1)">false</span> |
| Пустой граф, все рёбра                     | graph_inp  `0:{} 1:{} 2:{} 3:{} 4:{}` <br/>set_inp `{0 1 2 3 4}`  <br/>j `4`                                         | <span style="color:rgba(16,185,129,1)">true</span>  |
| Пустой граф до 3 в., все вершины до 3      | graph_inp `0:{} 1:{} 2:{} 3:{} 4:{}`  <br/>set_inp `{0 1 2 3}`<br/>j `3`                                             | <span style="color:rgba(16,185,129,1)">true</span>  |
| Пустой граф до 1 в., пустое множество      | graph_inp `0:{} 1:{} 2:{} 3:{} 4:{}`<br/>set_inp `{0}`<br/> j `1`                                                    | <span style="color:rgba(16,185,129,1)">false</span> |
| Пустой граф до 0 в., вершина 1             | graph_inp `0:{} 1:{} 2:{} 3:{} 4:{}` <br/>set_inp `{1}`<br/>j `0`                                                    | <span style="color:rgba(16,185,129,1)">false</span> |
| Пустой граф до 0 в., вершина 0             | graph_inp `0:{} 1:{} 2:{} 3:{} 4:{}` <br/>set_inp `{0}`<br/>j `0`                                                    | <span style="color:rgba(16,185,129,1)">true</span>  |
| Максимальное н. множество данного графа    | graph_inp `0:{3, 4} 1:{2} 2:{1, 4} 3:{0} 4:{0, 2}`<br/>set_inp `{0, 1}` <br/>j `4`                                   | <span style="color:rgba(16,185,129,1)">true</span>  |
| Не максимальное н. множество данного графа | graph_inp  `0:{3, 4} 1:{2} 2:{1, 4} 3:{0} 4:{0, 2}`<br/>set_inp `{1, 2}`<br/>j `4`                                   | <span style="color:rgba(16,185,129,1)">false</span> |
| Полный граф, пустое множество              | graph_inp  `0:{1, 2, 3, 4} 1:{0, 2, 3, 4} 2:{0, 1, 3, 4} 3:{0, 1, 2, 4} 4:{0, 1, 2, 3}`<br/>set_inp `{}` <br/>j `4`  | <span style="color:rgba(16,185,129,1)">false</span> |
| Полный граф, одна вершина                  | graph_inp   `0:{1, 2, 3, 4} 1:{0, 2, 3, 4} 2:{0, 1, 3, 4} 3:{0, 1, 2, 4} 4:{0, 1, 2, 3}`<br/>set_inp `{1}`<br/>j `4` | <span style="color:rgba(16,185,129,1)">true</span>  |





#### Поиск лексикографически первого МНМ (в частности, содержащего в себя заданное множество)

```cpp
MISet FindFirstMIS(const Graph& G, int n, MISet set_inp) {
    vector<bool> availability_status(n, true);

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
```

| Описание                                                               | Тест                                                                                                     | Результат                                                     |
| ---------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------- |
| Пустой граф, подмножество пустое                                       | graph_inp `0:{} 1:{} 2:{} 3:{} 4:{}`<br/>set_inp `{}`                                                    | <span style="color:rgba(16,185,129,1)">{0, 1, 2, 3, 4}</span> |
| Пустой граф, подмножество из нескольких вершин                         | graph_inp `0:{} 1:{} 2:{} 3:{} 4:{}`<br/>set_inp `{1, 2}`                                                | <span style="color:rgba(16,185,129,1)">{0, 1, 2, 3, 4}</span> |
| Граф с последовательно соединёнными вершинами, пустое подмножество     | graph_inp `0:{1} 1:{2} 2:{3} 3:{4} 4:{0}`<br/>set_inp {}                                                 | <span style="color:rgba(16,185,129,1)">{0, 2}</span>          |
| Граф с последовательно соединёнными вершинами, подмножество -- вершина | graph_inp `0:{1} 1:{2} 2:{3} 3:{4} 4:{0}`<br/>set_inp `{4}`                                              | <span style="color:rgba(16,185,129,1)">{1, 4}</span>          |
| Граф, подмножество -- изолированная вершина                            | graph_inp `0:{1, 2, 3} 1:{0} 2:{0} 3:{0} 4:{}`<br/>set_inp {4}                                           | <span style="color:rgba(16,185,129,1)">{0, 4}</span>          |
| Граф, подмножество -- вершина соединена со всеми остальными            | graph_inp `0:{1, 2, 3, 4} 1:{0} 2:{0} 3:{0} 4:{0}`<br/>set_inp `{0}`                                     | <span style="color:rgba(16,185,129,1)">{0}</span>             |
| Граф, изначальное подмножество -- уже МНМ (лекс. первое)               | graph_inp `0:{} 1:{3} 2:{3} 3:{1, 2, 4} 4:{3}`<br/>set_inp `{0, 1, 2, 4}`                                | <span style="color:rgba(16,185,129,1)">{0, 1, 2, 4}</span>    |
| Граф, изначальное подмножество -- уже МНМ (не лекс. первое)            | graph_inp `0:{} 1:{3} 2:{3} 3:{1, 2, 4} 4:{3}`<br/>set_inp `{0, 3}`                                      | <span style="color:rgba(16,185,129,1)">{0, 3}</span>          |
| Полный граф, пустое подмножество                                       | graph_inp  `0:{1, 2, 3, 4} 1:{0, 2, 3, 4} 2:{0, 1, 3, 4} 3:{0, 1, 2, 4} 4:{0, 1, 2, 3}`<br/>set_inp `{}` | <span style="color:rgba(16,185,129,1)">{0}</span>             |
| Полный граф, подмножество -- одна вершина                              | graph_inp `0:{1, 2, 3, 4} 1:{0, 2, 3, 4} 2:{0, 1, 3, 4} 3:{0, 1, 2, 4} 4:{0, 1, 2, 3}`<br/>set_inp `{3}` | <span style="color:rgba(16,185,129,1)">{3}</span>             |



#### Ввод графа



```cpp
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
            if (v1 != v2){
                G[v1].insert(v2);
                G[v2].insert(v1);

            }
        }
        else throw invalid_argument("Invalid argument number");
    }
    file_inp.close();

    ofstream file_outp;
    file_outp.open("output.txt");
    if (!file_outp.is_open()) {
        throw runtime_error("Couldn't open output file");
    }
    }
    catch (const exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
```

| Описание                              | Тест            | Результат                                                                      |
| ------------------------------------- | --------------- | ------------------------------------------------------------------------------ |
| Нечётное число вершин                 | -               | <span style="color:rgba(16,185,129,1)">Error: Invalid argument number</span>   |
| Вершина вне диапазона                 | -               | <span style="color:rgba(16,185,129,1)">Error: Vertex index out of range</span> |
| Ошибка открытия файла для чтения      | -               | <span style="color:rgba(16,185,129,1)">Error: Couldn't open input file</span>  |
| Пустой ввод                           |                 | <span style="color:rgba(16,185,129,1)">Error: wrong format</span>              |
| Повторяющиеся пары рёбер              | `5 1 2 1 2`     | <span style="color:rgba(16,185,129,1)">0:{} 1:{2} 2:{1} 3:{} 4:{}</span>       |
| Рёбра не в лексикографическом порядке | `5 2 1 4 3 2 4` | <span style="color:rgba(16,185,129,1)">0:{} 1:{2} 2:{1,4} 3:{4} 4:{2,3}</span> |
| Ребро между вершинами с одним номером | `5 1 1 1 2`     | <span style="color:rgba(16,185,129,1)">0:{} 1:{2} 2:{1} 3:{} 4:{}</span>       |
| Пустой граф                           | `5`             | <span style="color:rgba(16,185,129,1)">0:{} 1:{} 2:{} 3:{} 4:{}</span>         |

Важно отметить, что в функциях предполагается, что поступающие данные корректны (так как они автоматически генерируются программой и должны быть верны "по построению".



### Тестирование работы всей программы

Так как составление тестов, проверяющих работу программы целиком, вызывало трудности, мною было принято решение проверить программу сначала на простых тестах, где правильность ответа очевидна, и один раз на тесте среднего размера.



"Простыми" тестами послужили пустой и полный граф, граф, последовательно соединённый, а также совсем небольшие графы. В этих случаях было легко проверить на правильность.



В качестве более "сложного" теста был выбран такой граф из 8 рёбер. Мною был вручную проделан каждый шаг алгоритма из статьи и ответ сверен с ответом, полученным в ходе действия программы. К счастью, они совпали.

````
8
5 2
4 4
4 7
0 3
2 3
1 6
0 7
5 3
5 2
4 5
1 1
````



## Временная оценка работы алгоритмов

Важным критерием оценки также является время, за которое исполняется алгоритм. В теоретической части было подсчитано, что задержка между выводами может быть оценена как `O(n + m + log n)`~ `O(n^3)`.



Для того, чтобы точно оценить время работы, нужно было сгенерировать большое число тестов.

Для этого в исходный код были введены небольшие изменения: для того, чтобы не тратить вычислительные ресурсы, из алгоритма было удалено всё лишнее. Код с тестированием находится в репозитории GitHub под названием algo_testing_copy.cpp.

Была добавлена функция, генерирующая тесты. Это функция, получающая на вход число вершин графа и генерирующая в файл input.txt заданное число вершин.

```cpp
#include <random>
void GenerateTest(const string& filename, int n){
    ofstream file(filename);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, n - 1);

    for (int i = 0; i < (EDGE_NUMBER; ++i) {
        int random_number1 = distrib(gen);
        int random_number2 = distrib(gen);

        file << random_number1 << " " << random_number2 << endl;
    }
}
```



Время между выводами замерялось с помощью библиотеки chrono, после окончания цикла записывалось в файл output.txt, почле чего в строчку через запятую записывалось n.

```cpp
start = high_resolution_clock::now();
for (int j = 0; j < n; ++j) { 
    //цикл
}
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - start);
file << duration.count() << "," << n << endl;
```

Для визуализации была написана небольшая программа на Python, которая собирала пары чисел из файла и строила графики зависимости времени от n с помощью библиотеки matplotlib. Код находится в репозитории под названием Plot_algo.py.

Важно упомянуть, что полученная оценка -- это скорее верхняя граница, так как при её рассчёте выбирались наихудшие ситуации. Основная масса результатов распределена снизу кубической функции. Однако тенденция к кубическому росту всё равно должна пролеживаьтся по верхней границе этого множества точек.

Кроме этого, в каждом графике есть десятки точек, которые оказались выше найденной функции. Но этими результатами можно пренебречь, так как их число пренебрежимо мало по сравнению с миллионами результатов, подчиняющихся общему правилу.

### Результаты тестирования

Очевидным было то, что асимптотическая сложность работы алгоритма в основном зависела от плотности графа. Поэтому было принято решение протестировать программу на графах с разной плотностью. Для удобства проверялись графы с n от 1 до 30.



#### Разреженный граф (попытка 1)

В качестве разреженного графа мною изначально был выбран граф, для представления которого генерировалось n рёбер. Конечно, реальное количество уникальных рёбер было немного меньше из-за возможных повторов.

Было проведено три миллиона итераций и полученные файлы записаны в файл output0.txt, также находящийся в репозитории.




<img src="graphics/bi8H9H3oiacGY.png" alt="" height="312"/>



<img src="graphics/FlG0RM4LUfDPN.png" alt="" height="315"/>




Конечно, невозможно подобрать точные коэффициенты для функции, которая описывала бы полученные результаты, однако в этих графах видно визуально, что x^3 (второй график) лучше подходит для n < 20, а  рост в "хвосте" замедляется и становится ближе к x^3/2.

Это связано с тем, что предположение о том, что граф с n рёбрами разряжен -- неверно. В графе, где n = 3, такое число рёбер будет означать полноту, а в графе с 30 вершинами только 7% от максимального числа.

Поэтому более правильной оценкой плотности будет "процент заполненности", то есть процент числа рёбер в нашем графе от максимально возможного.



#### Разреженный граф, плотность 20%

В этом графе (n(n-1)/10) рёбер. По результату более миллиона итераций (output2.txt) был построен следующий график:


<img src="graphics/1XN3rS0AobNKk.png" alt="" height="312"/>




Видим, что основная масса точек ограничена графиком 5/2 x^3



#### Граф со средней плотностью 50%

В этом графе (n(n-1)/10) рёбер. По результату более миллиона итераций (output4.txt) был построен следующий график:


<img src="graphics/cOf2uHXiudSZl.png" alt="" height="313"/>


Видим, что основная масса точек ограничена графиком 5/2 x^3



#### Граф с плотностью 70%

В этом графе (n(n-1) * 7/20) рёбер. По результату нескольких десятков тысяч итераций (output5.txt) был построен следующий график:


<img src="graphics/4W9D6iRrxLSx8.png" alt="" height="303"/>




#### Практически полный граф, плотность стремится к 100%

В этом графе (n(n-1) /2) рёбер. По результату нескольких десятков тысяч (output8.txt) был построен следующий график:


<img src="graphics/V6lDSNZCKgMbZ.png" alt="" height="325"/>




#### Анализ данных

Можно заметить, что в графе со средней плотностью 20% время выполнения очередного шага цикла растёт с примерно кубичской скоростью, в то время, как в плотных графах асимптотическая оценка будет иметь гораздо меньший порядок. Кроме того, в плотных графиках каждый шаг алгоритма занимает в десятки раз меньше времени, чем в разреженных.

Этот феномен можно объяснить тем, что одна из самых времязатратных функций FindFirstMIS, временная оценка которой и давала кубическую сложность, стала занимать в разы меньше времени благодаря её внутреннему устройтсвту. Данные организованы в виде вектора вершин, из которых вычёркиваются те, которые уже смежны/были добавлены в построенное МНМ. А в очень плотных графах почти все вершины будут сразу вычеркнуты, так что функция будет анализировать только считанное число вершин и их соседей

Кроме того, хотя рёбер в плотном графе значительно больше, каждое найденное множество S имеет сравнительно небольшой размер, по сравнению со всем графом, так, например, в случае с почти полным графом размер найденных МНМ редко превышал 3 даже в графах с 30 вершинами, в связи с чем, перебор мог занимать меньше времени, что сделало прохождение по циклу значительно быстрее.

И важно не забывать про кэширование: повышенная локальность доступа к данным в плотных графах могла улучшить использование кэша процессора и, как следствие, сократить время выполнения.
