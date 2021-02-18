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
    struct Vertex {                                                                     //��ͨ����Ķ��㣬Ҳ���ǳ���
        int num, Distance, nowtime;                                                     //num���б��;Distance ·;�����ڼ������Ȩֵ;nowtime��ǰʱ��(һ������Ҳ����кܶ������ʱ��)
        bool operator < (const Vertex& b)const { return this->Distance < b.Distance; }  //����һ�´���С�ں�
        bool operator > (const Vertex& b)const { return this->Distance > b.Distance; }
    };
    struct Edge {                                                                       //��㡢�յ㡢��š���ʼ��ֹʱ�䡢�ķѣ�ʱ�䡢·�ѣ�
        string Start, End, Number;              
        int startpoint, endpoint, begintime, endtime, Distance, cost;
        int change(string s) {                                                          //���ڶ��ļ����ʱ��
            int res = ((s[0] - '0') * 10 + (s[1] - '0')) * 60;
            res += ((s[3] - '0') * 10 + (s[4] - '0'));
            return res;
        }
        Edge() :Start(""), End(""), Number(""), startpoint(0), 
            endpoint(0), begintime(0), endtime(0), Distance(0), cost(0) {} //��ʼ��
        Edge(string num, string a, string b, string c, string d, int s, int t, int p) : //�ߵĹ��캯��
            Number(num), Start(a), End(b), 
            begintime(change(c)), endtime(change(d)), startpoint(s), endpoint(t), cost(p) {}
        void PrintTime(int t) { printf("%02d:%02d", t / 60, t % 60); }                  //��ӡ�����ߵĳ���/����ʱ��
        void print() {                                                                  //��ӡ·����Ϣ
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
    int PassTime(int x, int y, bool f);                                                 //���ڼ���·;ʱ��
    int Scheme(Edge k, int type, Vertex intemp, int startpoint, int Distance);          //�������������ٵ�ʱ��/����
    void PrintPath(int startpoint, int v, Edge path[]);                                 //��ӡ·��
    void Conversion(int Time);                                                          //��ӡʱ��
    void ShortestPath(int startpoint, int endpoint, vector<Edge> edge[], int type);     //�����·����Dijkstra�㷨
    void AddEdge(vector<Edge> edge[]);                                                  //����һ��·��
    void DeleteEdge(vector<Edge> edge[]);                                               //ɾ��һ��·��
    void Solution(string a, string b, int type, string traffic);                        //ͨ�����з�ʽ���ṩ���·
    void ReadInFile();                                                                  //���ļ������г�ʱ�̱������
    void insertcity(string a) { Network[a] = ++Total; }                                 //���һ������
    void DeleteCity(string a);                                                          //ɾ��һ������
    void print(vector<Edge> edge[]);                                                    //��ӡ����·��
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

int TrafficSystem::Scheme(Edge k, int type, Vertex intemp, int startpoint, int Distance) {//1 for ʱ�����,2 for ·������
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
    printf("%dСʱ%d��", h, m);
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
    if (traffic == "��")
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
        cout << "δ���ҵ�����·�ߣ�����ѡ��༭�Ӷ���������·�ߣ�" << endl;
        return;
    }

    if (type == 1) {
        cout << "����ʱ�����:"; Conversion(Distance[endpoint]); cout << endl;
        cout << "ѡ�����·���:" << endl;
        PrintPath(startpoint, endpoint, path);
    }
    else if (type == 2) {
        cout << "���з�������:" << Distance[endpoint] << "Ԫ" << endl;
        cout << "ѡ�����·���:" << endl;
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