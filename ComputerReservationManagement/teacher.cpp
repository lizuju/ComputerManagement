#include "teacher.h"

// 默認構造
Teacher::Teacher()
{

}

// 有參構造
Teacher::Teacher(int empId, string name, string pwd)
{
    // 初始化屬性
    this->m_EmpId = empId;
    this->m_Name = name;
    this->m_Pwd = pwd;
}

// 菜單界面
void Teacher::operMenu()
{
    cout << "歡迎教師: " << this -> m_Name << "登陸! " << endl;
    cout << "\t\t -------------------------------\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          1.查看所有預約          |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          2.審核預約             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          0.注銷登陸             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t -------------------------------\n";
    cout << "請選擇您的操作: " << endl;
}

// 查看所有預約
void Teacher::showAllOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "無預約記錄" << endl;
        Clear();
        return;
    }

    for (int i = 0; i < of.m_Size; i++)
    {
        cout << i + 1 << ", ";
        cout << "預約日期: 周" << of.m_orderData[i]["date"];
        cout << "時間段 : " << (of.m_orderData[i]["interval"] == "1" ? "上午" : " 下午");
        cout << "學號: " << of.m_orderData[i]["stuId"];
        cout << "姓名: " << of.m_orderData[i]["stuName"];
        cout << "機房編號: " << of.m_orderData[i]["roomId"];
        string status = " 狀態: ";
        // 1, 審核中 2, 已預約 -1, 預約失敗 0, 取消預約
        if (of.m_orderData[i]["status"] == "1")
        {
            status += "審核中";
        }
        else if (of.m_orderData[i]["status"] == "2")
        {
            status += "預約成功";
        }
        else if (of.m_orderData[i]["status"] == "-1")
        {
            status += "預約失敗, 審核未通過";
        }
        else
        {
            status += "預約已取消";
        }
        cout << status << endl;
    }

    Clear();
}

// 審核預約
void Teacher::validOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "無預約記錄" << endl;
        Clear();
        return;
    }

    vector<int> v;
    int index = 0;
    cout << "待審核的預約記錄如下: " << endl;

    for (int i = 0; i < of.m_Size; i++)
    {
        if (of.m_orderData[i]["status"] == "1")
        {
            v.push_back(i);
            cout << ++index << ", ";
            cout << "預約日期: 周" << of.m_orderData[i]["date"];
            cout << " 時間段: " << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
            cout << " 學生姓名: " << of.m_orderData[i]["stuName"];
            cout << " 機房編號: " << of.m_orderData[i]["roomId"];
            string status = " 狀態: 審核中 ";
            cout << status << endl;
        }
    }

    cout << "請輸入審核的預約記錄, 0代表返回" << endl;
    int select = 0; // 接受用戶選擇的預約記錄
    int ret = 0;

    while (true)
    {
        cin >> select;
        if (select >= 0 && select <= v.size())
        {
            if (select == 0)
            {
                break;
            } else
            {
                cout << "請輸入審核結果" << endl;
                cout << "1, 通過" << endl;
                cout << "2, 不通過" << endl;
                cin >> ret;
                if (ret == 1)
                {
                    // 通過情況
                    of.m_orderData[v[select - 1]]["status"] = "2";
                }
                else
                {
                    // 不通過情況
                    of.m_orderData[v[select - 1]]["status"] = "-1";
                }
                of.updateOrder();   // 更新預約記錄
                cout << "審核完畢" << endl;
                break;
            }
        }
        cout << "輸入有誤, 請重新輸入! " << endl;
    }
    Clear();
}
