#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <clocale>
#include <sstream>


using namespace std;


int numVerts;                       // Кол-во вершин
int numEdges = 0;                   // Кол-во ребер
vector<vector<int>> graph;          // Граф
vector<vector<int>> workGraph;      // Граф для выявления наименьшего по весу ребра (удобнее обрабатывать)
vector<vector<int>> rack;           // Каркас 
vector<vector<int>> showRack;       // Каркас, предназначенный для вывода (удобнее обрабатывать)
vector<vector<int>> chords;         // Множество хорд
vector<vector<int>> fsc;            // Фундаментальная система циклов
vector<vector<vector<int>>> fcuts;  // Фундаментальные разрезы

vector<char> cl;                    // Массив цветов для алгоритма обхода в глубину
vector<int> p;                      // Массив предков для восстановления последовательности вершин фундаментального цикла при использовании алгоритма обхода в глубину
int cycle_st, cycle_end;            // Начальная и конечная вершины фундаментального цикла


void split(const string& str, vector<string>& tokens, const string& delimiters = " ")
{
    // Функция для считывания матрицы смежности

    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos = str.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos)
    {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}

void init() {
    // Функция инициализации

    string skip;

    cin >> numVerts;
    getline(cin, skip); // Пропуск управляющего символа

    rack.assign(numVerts, {});

    // В цикле считываем вес смежных вершин для каждой вершины и конструируем граф
    for (int j = 0; j < numVerts; j++) {
        string bufStr;
        vector<int> bufWeights;
        vector<string> tokens;

        getline(cin, bufStr);
        split(bufStr, tokens, " ");

        for (string str : tokens) { 
            int weight = stoi(str);
            bufWeights.push_back(weight);
            if (weight != -1) {
                numEdges++;
            }
        }

        graph.push_back(bufWeights);
    }

    // Копируем введенный граф в 'workGraph'
    for (int i = 0; i < numVerts; i++) {
        workGraph.push_back({});
        for (int j = 0; j < numVerts; j++) {
            workGraph[i].push_back(graph[i][j]);
        }
    }
    numEdges /= 2;
}

bool dfs(int v) {
    // Алгоритм обхода в глубину

    cl[v] = 'g';
    for (size_t i = 0; i < rack[v].size(); i++) {
        int to = rack[v][i];
        if (cl[to] == 'w') {
            p[to] = v;
            if (dfs(to)) return true;
        }
        // Если входим в вершину серого цвета и данная вершина не является предком предыдущей, то найден фунд. цикл
        else if (cl[to] == 'g' && p[v] != to) {
            cycle_end = v;
            cycle_st = to;
            return true;
        }
    }
    cl[v] = 'b';
    return false;
}

void isExistCycle(vector<int>& cycle, int v1, int v2) {
    // Функция проверки на существование фунд. цикла

    // Инициализируем необходимые массивы для работы алгоритма обхода в глубину
    cl.clear();
    p.clear();
    
    cl.assign(rack.size(), 'w');
    p.assign(rack.size(), -1);
    cycle_st = -1;
    cycle_end = -1;

    // Добавляем в каркас текущее ребро
    rack[v1].push_back(v2);
    rack[v2].push_back(v1);

    // Пытаемся найти цикл
    for (int i = 0; i < rack.size(); i++) {
        if (dfs(i)) break;
    }

    // Если цикл найден, то строим его и добавляем в фунд. систему циклов
    if (cycle_st != -1) {
        cycle.push_back(cycle_st);
        for (int v = cycle_end; v != cycle_st; v=p[v]) {
            cycle.push_back(v);
        }
        reverse(cycle.begin(), cycle.end());
    }

    // Удаляем текущее ребро из каркаса (примечание: если цикл не был найден, то текущее ребро добавится в каркас по выходу из текущей функции)
    rack[v1].pop_back();
    rack[v2].pop_back();
    
}

void printRack() {
    cout << "karkas: ";
    for (auto edge : showRack) {
        cout << "(" << edge[0] + 1 << ", " << edge[1] + 1 << "), ";
    }
    cout << endl << endl;
}

void printChords() {
    cout << "mnozestvo hord: ";
    for (auto chord : chords) {
        cout << "e" << chord[0] + 1 << "-" << chord[1] + 1 << ", ";
    }
    cout << endl << endl;
}

void printFSC() {
    cout << "fyndamentalnaya systema ciclov:" << endl;
    for (auto c : fsc) {
        for (auto v : c) {
            cout << "v" << v + 1;
        }
        cout << endl;
    }
    cout << endl << endl;
}

void printFcuts() {
    cout << "fyndamentalnie razrezi: " << endl;
    for (auto cut : fcuts) {
        for (auto edge: cut) {
            cout << "e" << edge[0] + 1 << "-" << edge[1] + 1 << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

void buildEdge(int v1, int v2) {
    vector<int> cycle;
    isExistCycle(cycle, v1, v2);
    if (!cycle.size()) {
        rack[v1].push_back(v2);
        rack[v2].push_back(v1);
        showRack.push_back({v1, v2});
    } else {
        // Если фунд. цикл найден, то добавляем его в фсц, а ребро в мн-во хорд
        chords.push_back({v1, v2});
        fsc.push_back(cycle);
    }
}

vector<int> chooseEdge() {
    // Функция для выбора минимального по весу ребра

    vector<int> edge = {0, 0};
    int minWeight = 100000000;
    
    for (int i = 0; i < numVerts; i++) {
        for (int j = 0; j < numVerts; j++) {
            int bufWeight = workGraph[i][j];
            if (bufWeight < minWeight && bufWeight != -1) {
                minWeight = bufWeight;
                edge[0] = i;
                edge[1] = j;
            }
        }
    }

    workGraph[edge[0]][edge[1]] = -1; 
    workGraph[edge[1]][edge[0]] = -1;

    return edge;
}

int main() {

    setlocale(LC_CTYPE, "rus");

    // Начальная инициализация
    init();

    // Берем текущее минимальное по весу ребро, проверяем на фунд. цикл, если есть - добавляем в фсц, иначе берем след. ребро, а текущее добавляем в каркас
    do {
        vector<int> edge = chooseEdge();
        buildEdge(edge[0], edge[1]);
        numEdges--;
    } while (numEdges);

    // Заполняем массив фундаментальных разрезов
    for (auto edge : showRack) {
        vector<vector<int>> buf;
        buf.push_back(edge);
        for (auto chord : chords)
            buf.push_back(chord);
        fcuts.push_back(buf);
    }

    // Вывод требуемых в задаче данных
    cout << endl;
    printRack();
    printChords();
    printFSC();
    printFcuts();
}