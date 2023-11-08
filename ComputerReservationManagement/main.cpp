#include <iostream>
using namespace std;
#include "Identity.h"
#include <fstream>
#include <string>
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
#include "Clear.h"

// 進入學生子菜單界面
void studentMenu(Identity* &student)
{
    while (true)
    {
        // 調用學生子菜單
        student->operMenu();

        Student* stu = (Student* ) student;

        int select = 0;
        cin >> select;  // 接受用戶選擇

        if (select == 1)    // 申請預約
        {
            stu->applyOrder();
        }
        else if (select == 2)   // 查看自身預約
        {
            stu->showMyOrder();
        }
        else if (select == 3)   // 查看所有人預約
        {
            stu->showAllOrder();
        }
        else if (select == 4)   // 取消預約
        {
            stu->cancelOrder();
        }
        else
        {
            // 注銷登陸
            delete student;
            cout << "注銷成功" << endl;
            Clear();
            return;

        }
    }
}

// 進入教師子菜單界面
void teacherMenu(Identity* &teacher)
{
    while (true)
    {
        // 調用子菜單界面
        teacher->operMenu();

        Teacher* tea = (Teacher*)teacher;

        int select = 0; // 接受用戶選擇

        cin >> select;

        if (select == 1)    // 查看所有預約
        {
            tea->showAllOrder();
        }
        else if (select == 2)   // 審核預約
        {
            tea->validOrder();
        } else
        {
            delete teacher;
            cout << "注銷成功" << endl;
            Clear();
            return;
        }
    }
}

// 進入管理員子菜單界面
void managerMenu(Identity* &manager)
{
    while (true)
    {
        // 調用管理員子菜單
        manager -> operMenu();

        // 將父類指針 轉為子類指針, 調用子類裡其他接口
        Manager* man = (Manager*)manager;

        int select = 0;
        // 接受用戶選擇
        cin >> select;

        if (select == 1)    // 添加賬號
        {
//            cout << "添加賬號" << endl;
            man -> addPerson();
        }
        else if (select == 2)   // 查看賬號
        {
//            cout << "查看賬號" << endl;
            man -> showPerson();
        }
        else if (select == 3)   // 查看機房
        {
//            cout << "查看機房" << endl;
            man -> showComputer();
        }
        else if (select == 4)   // 清空預約
        {
//            cout << "清空預約" << endl;
            man -> cleanFile();
        }
        else
        {
            // 注銷
            delete manager; // 銷毀掉堆區對象
            cout << "注銷成功" << endl;
            Clear();
            return;
        }
    }
}

// 登錄功能 參數1 操作文件名   參數2 操作身份類型
void LogIn(string fileName, int type)
{
    // 父類指針, 用於指向子類對象
    Identity* person = NULL;

    // 讀文件
    ifstream ifs;
    ifs.open(fileName, ios::in);

    // 判斷文件是否存在
    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }

    // 准備接受用戶的信息
    int id = 0;
    string name;
    string pwd;

    // 判斷身份
    if (type == 1)  // 學生身份
    {
        cout << "請輸入你的學號: " << endl;
        cin >> id;
    }
    else if (type == 2)
    {
        cout << "請輸入您的職工號: " << endl;
        cin >> id;
    }

    cout << "請輸入用戶名: " << endl;
    cin >> name;

    cout << "請輸入密碼: " << endl;
    cin >> pwd;

    if (type == 1)
    {
        // 學生身份驗證
        int fId;    // 從文件中讀取的id號
        string fName;   // 從文件中獲取的姓名
        string fPwd;    // 從文件中獲取密碼
        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            // 與用戶輸入的信息做對比
            if (fId == id && fName == name && fPwd == pwd)
            {
                cout << "學生驗證登錄成功! " << endl;
                Clear();
                person = new Student(id, name, pwd);
                // 進入學生身份的子菜單
                studentMenu(person);
                return;
            }
        }
    }
    else if (type == 2)
    {
        // 教師身份驗證
        int fId;    // 從文件中獲取的id號
        string fName;   // 從文件中獲取的姓名
        string fPwd;    // 從文件中獲取的密碼
        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if (fId == id && fName == name && fPwd == pwd)
            {
                cout << "教師驗證登錄成功! " << endl;
                Clear();
                person = new Teacher(id, name, pwd);
                // 進入教師子菜單
                teacherMenu(person);
                return;
            }
        }
    }
    else if (type == 3)
    {
        // 管理員身份驗證
        string fName;   // 從文件中獲取姓名
        string fPwd;    // 從文件中獲取密碼

        while (ifs >> fName && ifs >> fPwd)
        {
            if (name == fName && pwd == fPwd)
            {
                cout << "管理員驗證登錄成功! " << endl;
                Clear();

                person = new Manager(name, pwd);

                // 進入管理員子菜單界面
                managerMenu(person);

                return;
            }
        }
    }

    cout << "驗證登錄失敗! " << endl;
    Clear();

    return;
}

int main()
{
    int select = 0; // 用於接受用戶的選擇

    while (true)
    {
        cout << "======================  欢迎来到传智播客机房预约系统  ======================" << endl;
        cout << endl << "请输入您的身份" << endl;
        cout << "\t\t -------------------------------\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          1.学生代表             |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          2.老   師             |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          3.管 理 員            |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          0.退   出             |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t -------------------------------\n";
        cout << "输入您的选择: ";

        cin >> select; // 接受用戶選擇

        switch (select) // 根據用戶選擇 實現不同接口
        {
            case 1: // 學生身份
                LogIn(STUDENT_FILE, 1);
                break;
            case 2: // 老師身份
                LogIn(TEACHER_FILE, 2);
                break;
            case 3: // 管理員身份
                LogIn(ADMIN_FILE, 3);
                break;
            case 0: // 退出系統
                cout << "歡迎下一次使用" << endl;
                Clear();
                return 0;
                break;
            default:
                cout << "輸入有誤, 請重新選擇!" << endl;
                Clear();
                break;
        }
    }



    Clear();
    return 0;
}