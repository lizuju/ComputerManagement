#include "student.h"

// 默認構造
Student::Student()
{

}

// 有參構造 參數: 學號, 姓名, 密碼
Student::Student(int id, string name, string pwd)
{
    // 初始化屬性
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;

    // 初始化機房信息
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);

    ComputerRoom com;
    while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
    {
        // 將讀取的信息放入到 容器中
        vCom.push_back(com);
    }

    ifs.close();
}


// 菜單界面
void Student::operMenu()
{
    cout << "歡迎學生代表: " << this -> m_Name << "登陸! " << endl;
    cout << "\t\t -------------------------------\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          1.申請預約             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          2.查看我的預約          |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          3.查看所有預約          |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          4.取消預約             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          0.注銷登陸             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t -------------------------------\n";
    cout << "输入您的选择: " << endl;
}

// 申請預約
void Student::applyOrder()
{
    cout << "機房開放的時間為周一至周五!" << endl;
    cout << "請輸入申請預約的時間: " << endl;
    cout << "1, 周一" << endl;
    cout << "2, 周二" << endl;
    cout << "3, 周三" << endl;
    cout << "4, 周四" << endl;
    cout << "5, 周五" << endl;

    int date = 0;   // 日期
    int interval = 0;   // 時間段
    int room = 0;   // 機房編號

    while (true)
    {
        cin >> date;
        if (date >= 1 && date <= 5)
        {
            break;
        }
        cout << "輸入有誤, 請重新輸入" << endl;
    }

    cout << "請輸入申請預約時間段: " << endl;
    cout << "1, 上午" << endl;
    cout << "2, 下午" << endl;

    while (true)
    {
        cin >> interval;
        if (interval >= 1 && interval <= 2)
        {
            break;
        }
        cout << "輸入有誤, 請重新輸入" << endl;
    }

    cout << "請選擇機房: " << endl;
    for (int i = 0; i <vCom.size(); i++)
    {
        cout << vCom[i].m_ComId << "號機房容量為: " << vCom[i].m_MaxNum << endl;
    }

    while (true)
    {
        cin >> room;
        if (room >= 1 && room <= 3)
        {
            break;
        }
        cout << "輸入有誤, 請重新輸入" << endl;
    }

    cout << "預約成功! 審核中" << endl;

    ofstream ofs;
    ofs.open(ORDER_FILE, ios::app);

    ofs << "date: " << date << " ";
    ofs << "interval: " << interval << " ";
    ofs << "stuId: " << this->m_Id << " ";
    ofs << "stuName: " << this->m_Name << " ";
    ofs << "roomId: " << room << " ";
    ofs << "status: " << 1 << endl;

    ofs.close();

    Clear();
}

// 查看自身預約
void Student::showMyOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "無預約記錄! " << endl;
        Clear();
        return;
    }

    for (int i = 0; i < of.m_Size; i++)
    {
        // string 轉 int
        // string 利用 .c_str() 轉 const char *
        // 利用atoi (const char*) 轉 int
        if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str())) // 找到自身預約
        {
            cout << "預約日期: 周" << of.m_orderData[i]["date"];
            cout << " 時間段: " << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
            cout << "機房號: " << of.m_orderData[i]["roomId"];
            string status = "狀態: ";
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
    }

    Clear();
}

// 查看所有預約
void Student::showAllOrder()
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
        cout << " 時間段: " << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
        cout << " 姓名: " << of.m_orderData[i]["stuName"];
        cout << " 機房編號: " << of.m_orderData[i]["roomId"];
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

// 取消預約
void Student::cancelOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "無預約記錄" << endl;
        Clear();
        return;
    }

    cout << "審核中或預約成功的記錄可以取消, 請輸入取消的記錄" << endl;
    vector<int>  v; // 存放在最大容器中的下標編號
    int index = 1;
    for (int i = 0; i < of.m_Size; i++)
    {
        // 先判斷是自身學號
        if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
        {
            // 再篩選狀態 審核中或預約成功
            if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
            {
                v.push_back(i);
                cout << index++ << ", ";
                cout << "預約日期: 周" << of.m_orderData[i]["date"];
                cout << " 時間段: " << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
                cout << " 機房編號: " << of.m_orderData[i]["roomId"];
                string status = " 狀態: ";
                if (of.m_orderData[i]["status"] == "1")
                {
                    status += "審核中";
                }
                else if (of.m_orderData[i]["status"] == "2")
                {
                    status += "預約成功";
                }
                cout << status << endl;
            }
        }
    }

    cout << "請輸入取消的記錄, 0代表返回" << endl;
    int select = 0;

    while (true)
    {
        cin >> select;

        if (select >= 0 && select <= v.size())
        {
            if (select == 0)
            {
                break;
            }
            else
            {
                of.m_orderData[v[select - 1]]["status"] = "0";

                of.updateOrder();

                cout << "已取消預約" << endl;
                break;
            }
        }

        cout << "輸入有誤, 請重新輸入" << endl;
    }

    Clear();
}