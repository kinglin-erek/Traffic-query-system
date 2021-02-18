#include"Traffic.h"

int main()
{
    int choice, type;
    string City_a, City_b, traffic;
    TrafficSystem Graph;
    Graph.ReadInFile();

    while (1) {
        cout << " ------欢迎进入交通查询系统-------" << endl;
        cout << "|      输入1:查询最优路线         |" << endl;
        cout << "|      输入2:新增路线             |" << endl;
        cout << "|      输入3:删除路线             |" << endl;
        cout << "|      输入4:输出火车时间表       |" << endl;
        cout << "|      输入5:输出飞机时间表       |" << endl;
        cout << "|      输入其他数字:退出系统      |" << endl;
        cout << " ---------------------------------" << endl;
        cin >> choice;
        switch (choice)
        {
        case 4:
            Graph.print(Graph.Train);
            break;
        case 5:
            Graph.print(Graph.Plane);
            break;
        case 1:
            while (true) {
                cout << " ---------------------------------------------------------" << endl;
                cout << "|请依次输入:起点站 终点站 1或2(时间/费用最少) 飞机/火车   |" << endl;
                cout << "|例如:上海 北京 1 飞机                                    |" << endl;
                cout << "|输入0返回上一级菜单                                      |" << endl;
                cout << " ---------------------------------------------------------" << endl;
                cin >> City_a; cin.ignore();
                if (City_a == "0") break;
                cin >> City_b >> type >> traffic;
                Graph.Solution(City_a, City_b, type, traffic);
            }
            break;
        case 2:
            while (true)
            {
                cout << " ------------------------" << endl;
                cout << "|输入1:增加一个城市      |" << endl;
                cout << "|输入2:增加一条火车路线  |" << endl;
                cout << "|输入3:增加一条飞机路线  |" << endl;
                cout << "|输入其他数字:返回上一层 |" << endl;
                cout << " ------------------------" << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    cout << "输入增加的城市名字:";
                    cin >> City_a;
                    Graph.insertcity(City_a);
                    cout << endl;
                    break;
                case 2:
                    cout << " ---------------------------------------------------" << endl;
                    cout << "|请输入:车次号 起点 终点 发车时间 到达时间 票价(元) |" << endl;
                    cout << "|例如:T221 成都 广州 07:46 02:26 310                |" << endl;
                    cout << " ---------------------------------------------------" << endl;
                    Graph.AddEdge(Graph.Train);
                    cout << endl;
                    break;
                case 3:
                    cout << " ---------------------------------------------------" << endl;
                    cout << "|请输入:航班号 起点 终点 起飞时间 落地时间 票价(元) |" << endl;
                    cout << "|例如:J476 天津 乌鲁木齐 19:51 05:28 1560           |" << endl;
                    cout << " ---------------------------------------------------" << endl;
                    Graph.AddEdge(Graph.Plane);
                    cout << endl;
                    break;
                default:
                    goto END;
                }
            }
            break;
        case 3:
            while (true)
            {
                cout << " ----------------------" << endl;
                cout << "|输入1:删除一个城市    |" << endl;
                cout << "|输入2:删除一条火车路线|" << endl;
                cout << "|输入3:删除一条飞机路线|" << endl;
                cout << "|其他数字:返回上一层   |" << endl;
                cout << " ----------------------" << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    cout << "输入删除的城市名字:";
                    cin >> City_a;
                    Graph.DeleteCity(City_a);
                    cout << endl;
                    break;
                case 2:
                    cout << " -----------------------" << endl;
                    cout << "|请输入:车次号 起点 终点|" << endl;
                    cout << "|例如:C249 贵阳 呼和浩特|" << endl;
                    cout << " -----------------------" << endl;
                    Graph.DeleteEdge(Graph.Train);
                    cout << endl;
                    break;
                case 3:
                    cout << " ---------------------------" << endl;
                    cout << "|请输入:航班号 起始站 终点站|" << endl;
                    cout << "|例子:A102 长春 天津       |" << endl;
                    cout << " ---------------------------" << endl;
                    Graph.DeleteEdge(Graph.Plane);
                    cout << endl;
                    break;
                default:
                    goto END;
                }
            }END:
            break;

        default:
            goto over;
        }
    }over:
    cout << "感谢您的使用，再见！" << endl;
    return 0;
}