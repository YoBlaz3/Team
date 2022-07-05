#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>

//using namespace std;

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::getline;

int n;
vector<vector<int>> graph;          // Граф
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

    cin >> n;
    getline(cin, skip); // Пропуск управляющего символа

    rack.assign(n, {});

    // В цикле считываем смежные вершины для каждой вершины и конструируем граф
    for (int j = 0; j < n; j++) {
        string bufStr;
        vector<int> bufVerts;
        vector<string> tokens;

        getline(cin, bufStr);
        split(bufStr, tokens, " ");

        for (string str : tokens) {
            bufVerts.push_back(stoi(str) - 1);
        }

        graph.push_back(bufVerts);
    }
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
        for (int v = cycle_end; v != cycle_st; v = p[v]) {
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
    cout << endl;
}

void printChords() {
    cout << "mnozestvo hord: ";
    for (auto chord : chords) {
        cout << "e" << chord[0] + 1 << "-" << chord[1] + 1 << ", ";
    }
    cout << endl << endl;
}

void printFSC() {
    cout << "fyndamentalnaya systema ciklov:" << endl;
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
        for (auto edge : cut) {
            cout << "e" << edge[0] + 1 << "-" << edge[1] + 1 << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {

    init();

    // Берем текущее ребро, проверяем на фунд. цикл, если есть - добавляем в фсц, иначе берем след. ребро, а текущее добавляем в каркас
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            int neighbour = graph[i][j];
            vector<int> cycle;
            isExistCycle(cycle, i, neighbour);
            if (!cycle.size()) {
                rack[i].push_back(neighbour);
                rack[neighbour].push_back(i);
                showRack.push_back({ i, neighbour });
            }
            else {
                // Если фунд. цикл найден, то добавляем его в фсц, а ребро в мн-во хорд
                chords.push_back({ i, neighbour });
                fsc.push_back(cycle);
            }
        }
    }

    // Заполняем массив фундаментальных разрезов
    for (auto edge : showRack) {
        vector<vector<int>> buf;
        buf.push_back(edge);
        for (auto chord : chords)
            buf.push_back(chord);
        fcuts.push_back(buf);
    }

    // Вывод требуемых в задаче данных
    printRack();
    printChords();
    printFSC();
    printFcuts();
}