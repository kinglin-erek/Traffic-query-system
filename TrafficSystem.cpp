#include"Traffic.h"

int main()
{
    int choice, type;
    string City_a, City_b, traffic;
    TrafficSystem Graph;
    Graph.ReadInFile();

    while (1) {
        cout << " ------��ӭ���뽻ͨ��ѯϵͳ-------" << endl;
        cout << "|      ����1:��ѯ����·��         |" << endl;
        cout << "|      ����2:����·��             |" << endl;
        cout << "|      ����3:ɾ��·��             |" << endl;
        cout << "|      ����4:�����ʱ���       |" << endl;
        cout << "|      ����5:����ɻ�ʱ���       |" << endl;
        cout << "|      ������������:�˳�ϵͳ      |" << endl;
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
                cout << "|����������:���վ �յ�վ 1��2(ʱ��/��������) �ɻ�/��   |" << endl;
                cout << "|����:�Ϻ� ���� 1 �ɻ�                                    |" << endl;
                cout << "|����0������һ���˵�                                      |" << endl;
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
                cout << "|����1:����һ������      |" << endl;
                cout << "|����2:����һ����·��  |" << endl;
                cout << "|����3:����һ���ɻ�·��  |" << endl;
                cout << "|������������:������һ�� |" << endl;
                cout << " ------------------------" << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    cout << "�������ӵĳ�������:";
                    cin >> City_a;
                    Graph.insertcity(City_a);
                    cout << endl;
                    break;
                case 2:
                    cout << " ---------------------------------------------------" << endl;
                    cout << "|������:���κ� ��� �յ� ����ʱ�� ����ʱ�� Ʊ��(Ԫ) |" << endl;
                    cout << "|����:T221 �ɶ� ���� 07:46 02:26 310                |" << endl;
                    cout << " ---------------------------------------------------" << endl;
                    Graph.AddEdge(Graph.Train);
                    cout << endl;
                    break;
                case 3:
                    cout << " ---------------------------------------------------" << endl;
                    cout << "|������:����� ��� �յ� ���ʱ�� ���ʱ�� Ʊ��(Ԫ) |" << endl;
                    cout << "|����:J476 ��� ��³ľ�� 19:51 05:28 1560           |" << endl;
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
                cout << "|����1:ɾ��һ������    |" << endl;
                cout << "|����2:ɾ��һ����·��|" << endl;
                cout << "|����3:ɾ��һ���ɻ�·��|" << endl;
                cout << "|��������:������һ��   |" << endl;
                cout << " ----------------------" << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    cout << "����ɾ���ĳ�������:";
                    cin >> City_a;
                    Graph.DeleteCity(City_a);
                    cout << endl;
                    break;
                case 2:
                    cout << " -----------------------" << endl;
                    cout << "|������:���κ� ��� �յ�|" << endl;
                    cout << "|����:C249 ���� ���ͺ���|" << endl;
                    cout << " -----------------------" << endl;
                    Graph.DeleteEdge(Graph.Train);
                    cout << endl;
                    break;
                case 3:
                    cout << " ---------------------------" << endl;
                    cout << "|������:����� ��ʼվ �յ�վ|" << endl;
                    cout << "|����:A102 ���� ���       |" << endl;
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
    cout << "��л����ʹ�ã��ټ���" << endl;
    return 0;
}