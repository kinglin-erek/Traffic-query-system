#ifndef _TRAFFICSYSTEM_
#define _TRAFFICSYSTEM_

#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<vector>
#include<queue>

#define Maxn 500
const int inf = 9999999;
using namespace std;

class TrafficSystem {
public:
    struct Vertex {                                                                     //交通网络的顶点，也就是城市
        int num, Distance, nowtime;                                                     //num城市编号;Distance 路途，用于计算边上权值;nowtime当前时间(一个城市也许会有很多个出发时间)
        bool operator < (const Vertex& b)const { return this->Distance < b.Distance; }  //重载一下大于小于号
        bool operator > (const Vertex& b)const { return this->Distance > b.Distance; }
    };
    struct Edge {                                                                       //起点、终点、编号、起始终止时间、耗费（时间、路费）
        string Start, End, Number;              
        int startpoint, endpoint, begintime, endtime, Distance, cost;
        int change(string s) {                                                          //用于读文件里的时间
            int res = ((s[0] - '0') * 10 + (s[1] - '0')) * 60;
            res += ((s[3] - '0') * 10 + (s[4] - '0'));
            return res;
        }
        Edge() :Start(""), End(""), Number(""), startpoint(0), 
            endpoint(0), begintime(0), endtime(0), Distance(0), cost(0) {} //初始化
        Edge(string num, string a, string b, string c, string d, int s, int t, int p) : //边的构造函数
            Number(num), Start(a), End(b), 
            begintime(change(c)), endtime(change(d)), startpoint(s), endpoint(t), cost(p) {}
        void PrintTime(int t) { printf("%02d:%02d", t / 60, t % 60); }                  //打印这条边的出发/到达时间
        void print() {                                                                  //打印路线信息
            cout << Number << " " << Start << " " << End << " ";
            PrintTime(begintime); cout << " ";
            PrintTime(endtime); cout << " " << cost << endl;
        }
    };

    int Total = 0;
    map<string, int> Network;
    string City[Maxn];
    vector<Edge>Plane[Maxn], Train[Maxn];

    TrafficSystem();
    int PassTime(int x, int y, bool f);                                                 //用于计算路途时间
    int Scheme(Edge k, int type, Vertex intemp, int startpoint, int Distance);          //根据需求获得最少的时间/费用
    void PrintPath(int startpoint, int v, Edge path[]);                                 //打印路径
    void Conversion(int Time);                                                          //打印时间
    void ShortestPath(int startpoint, int endpoint, vector<Edge> edge[], int type);     //求最短路径，Dijkstra算法
    void AddEdge(vector<Edge> edge[]);                                                  //加入一条路线
    void DeleteEdge(vector<Edge> edge[]);                                               //删除一条路线
    void Solution(string a, string b, int type, string traffic);                        //通过出行方式，提供最短路
    void ReadInFile();                                                                  //用文件读入列车时刻表，航班表
    void insertcity(string a) { Network[a] = ++Total; }                                 //添加一个城市
    void DeleteCity(string a);                                                          //删除一个城市
    void print(vector<Edge> edge[]);                                                    //打印所有路线
};

TrafficSystem::TrafficSystem() {
    Total = 0;
    Network.clear();
    for (int i = 0; i < Maxn; i++)  Plane[i].clear();
    for (int i = 0; i < Maxn; i++)  Train[i].clear();
}

int TrafficSystem::PassTime(int x, int y, bool f) {
    if (f) return 0;
    x = x % 1440;
    y = y % 1440;
    return (y - x + 1440) % 1440;
}

int TrafficSystem::Scheme(Edge k, int type, Vertex intemp, int startpoint, int Distance) {//1 for 时间最短,2 for 路费最少
    if (type == 1)
        return PassTime(k.begintime, k.endtime, 0) + PassTime(Distance, k.begintime, startpoint == intemp.num);
    else if (type == 2)
        return k.cost;
    else
        return 0;
}

void TrafficSystem::PrintPath(int startpoint, int v, Edge path[]) {
    if (v == startpoint)    return;
    PrintPath(startpoint, path[v].startpoint, path);
    path[v].print();
}

void TrafficSystem::Conversion(int Time) {
    int h = Time / 60, m = Time % 60;
    printf("%d小时%d分", h, m);
}

void TrafficSystem::ReadInFile() {
    string Number, startpoint, endpoint, sttime, edtime, kind;
    int p, N;    
    ifstream fin("data.txt");
    fin >> kind >> N;
    for (int i = 0; i < N; i++) {
        fin >> Number >> startpoint >> endpoint >> sttime >> edtime >> p;
        if (Network[startpoint] == 0) {
            Network[startpoint] = ++Total;
            City[Total] = startpoint;
        }
        if (Network[endpoint] == 0) {
            Network[endpoint] = ++Total;
            City[Total] = endpoint;
        }
        int S = Network[startpoint], E = Network[endpoint];
        Edge New(Number, startpoint, endpoint, sttime, edtime, S, E, p);
        Train[S].push_back(New);
    }
    fin >> kind >> N;
    for (int i = 0; i < N; i++) {
        fin >> Number >> startpoint >> endpoint >> sttime >> edtime >> p;
        if (Network[startpoint] == 0) {
            Network[startpoint] = ++Total;
            City[Total] = startpoint;
        }
        if (Network[endpoint] == 0) {
            Network[endpoint] = ++Total;
            City[Total] = endpoint;
        }
        int S = Network[startpoint], E = Network[endpoint];
        Edge New(Number, startpoint, endpoint, sttime, edtime, S, E, p);
        Plane[S].push_back(New);
    }
};

void TrafficSystem::DeleteEdge(vector<Edge> edge[]) {
    vector<Edge>::iterator It;
    string Number, startpoint, endpoint;
    cin >> Number >> startpoint >> endpoint;
   
    It = edge[Network[startpoint]].begin();
    for (It = edge[Network[startpoint]].begin(); It != edge[Network[startpoint]].end(); It++) {
        if (It->Number == Number) {
            edge[Network[startpoint]].erase(It);
            return;
        }
    }
}

void TrafficSystem::Solution(string a, string b, int type, string traffic) {
    if (traffic == "火车")
        ShortestPath(Network[a], Network[b], Train, type);
    else
        ShortestPath(Network[a], Network[b], Plane, type);
}

void TrafficSystem::ShortestPath(int startpoint, int endpoint, vector<Edge> edge[], int type) {
    bool Visit[Maxn];
    int Distance[Maxn], i, v;
    Edge path[Maxn];
    Vertex intemp{ startpoint,0,0 }, newtemp;
    priority_queue<Vertex, vector<Vertex>, greater<Vertex> > prior_queue;
    for (i = 1; i <= Total; i++) {
        Visit[i] = false;
        Distance[i] = inf;
    }
    Distance[startpoint] = 0;
    prior_queue.push(intemp);
    Visit[startpoint] = true;
    while (!prior_queue.empty()) {
        intemp = prior_queue.top();
        prior_queue.pop();
        Visit[intemp.num] = false;
        for (v = 0; v < edge[intemp.num].size(); v++) {
            Edge k = edge[intemp.num][v];
            if (Distance[k.endpoint] > Distance[intemp.num] + Scheme(k, type, intemp, startpoint, intemp.nowtime)) {
                Distance[k.endpoint] = Distance[intemp.num] + Scheme(k, type, intemp, startpoint, intemp.nowtime);
                path[k.endpoint] = k;
                if (Visit[k.endpoint] == false) {
                    Visit[k.endpoint] = true;
                    newtemp.nowtime = k.endtime;
                    newtemp.num = k.endpoint;
                    newtemp.Distance = Distance[k.endpoint];
                    prior_queue.push(newtemp);
                }
            }
        }
    }
    if (Distance[endpoint] == 0 || Distance[endpoint] >= inf/2) {
        cout << "未查找到这条路线，可以选择编辑从而新增这条路线！" << endl;
        return;
    }

    if (type == 1) {
        cout << "旅行时间最短:"; Conversion(Distance[endpoint]); cout << endl;
        cout << "选择如下方案:" << endl;
        PrintPath(startpoint, endpoint, path);
    }
    else if (type == 2) {
        cout << "旅行费用最少:" << Distance[endpoint] << "元" << endl;
        cout << "选择如下方案:" << endl;
        PrintPath(startpoint, endpoint, path);
    }
    else
        cout << endl;
}

void TrafficSystem::AddEdge(vector<Edge> edge[]) {
    string Number, startpoint, endpoint, sttime, edtime;
    int p;
    cin >> Number >> startpoint >> endpoint >> sttime >> edtime >> p;
    if (!Network[startpoint]) {
        Network[startpoint] = ++Total;
        City[Total] = startpoint;
    }
    if (!Network[endpoint]) {
        Network[endpoint] = ++Total;
        City[Total] = endpoint;
    }
    int S = Network[startpoint], E = Network[endpoint];
    Edge New(Number, startpoint, endpoint, sttime, edtime, S, E, p);
    edge[S].push_back(New);
}

void TrafficSystem::DeleteCity(string a) {
    Train[Network[a]].clear();
    Plane[Network[a]].clear();
    Network[a] = 0;
}

void TrafficSystem::print(vector<Edge> edge[]) {
    for (int i = 1; i <= Total; i++)
        for (int j = 0; j < edge[i].size(); j++)
            edge[i][j].print();
    cout << endl;
}
#endif