#include "manager.h"
#include "Clear.h"

// 默認構造
Manager::Manager()
{

}

// 有參構造
Manager::Manager(string name, string pwd)
{
    // 初始化管理員信息
    this -> m_Name = name;
    this -> m_Pwd = pwd;

    // 初始化容器 獲取到所有文件中 學生, 老師信息
    this->initVector();

    // 初始化機房信息
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);

    ComputerRoom com;
    while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
    {
        vCom.push_back(com);
    }
    ifs.close();
    cout << "機房的數量為: " << vCom.size() << endl;
}

// 菜單界面
void Manager::operMenu()
{
    cout << "歡迎管理員: " << this -> m_Name << "登陸! " << endl;
    cout << "\t\t -------------------------------\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          1.添加賬號             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          2.查看賬號             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          3.添加機房             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          4.清空預約             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          0.注銷登陸             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t -------------------------------\n";
    cout << "输入您的选择: " << endl;
}

// 添加賬號
void Manager::addPerson()
{
    cout << "請輸入添加賬號類型" << endl;
    cout << "1, 添加學生" << endl;
    cout << "2, 添加老師" << endl;

    string fileName;    // 操作文件名
    string tip; // 提示id號
    string errorTip; // 重復錯誤提示

    ofstream ofs;   // 文件操作對象

    int select = 0;
    cin >> select;  // 接受用戶的選項

    if (select == 1)
    {
        // 添加的是學生
        fileName = STUDENT_FILE;
        tip = "請輸入學號: ";
        errorTip = "學號重復, 請重新輸入";
    }
    else
    {
        fileName = TEACHER_FILE;
        tip = "請輸入職工編號: ";
        errorTip = "職工號重復, 請重新輸入";
    }

    // 利用追加的方式寫文件
    ofs.open(fileName, ios::out | ios::app);

    int id; // 學號 職工號
    string name;    // 姓名
    string pwd; // 密碼

    cout << tip << endl;

    while (true)
    {
        cin >> id;
        bool ret = checkRepeat(id, select);
        if (ret)    // 有重復
        {
            cout << errorTip << endl;
        } else
        {
            break;
        }
    }

    cout << "請輸入姓名: " << endl;
    cin >> name;

    cout << "請輸入密碼: " << endl;
    cin >> pwd;

    // 向文件中添加數據
    ofs << id << " " << name << " " << pwd << " " << endl;
    cout << "添加成功" << endl;

    Clear();

    ofs.close();

    // 調用初始化容器接口, 從新獲取文件中的數據
    this->initVector();
}

void printStudent(Student& s)
{
    cout << "學號: " << s.m_Id << " 姓名: " << s.m_Name << " 密碼: " << s.m_Pwd << endl;
}

void printTeacher(Teacher& s)
{
    cout << "學號: " << s.m_EmpId << " 姓名: " << s.m_Name << " 密碼: " << s.m_Pwd << endl;
}

// 查看賬號
void Manager::showPerson()
{
    cout << "請選擇查看內容: " << endl;
    cout << "1, 查看所有學生" << endl;
    cout << "2, 查看所有老師" << endl;

    int select = 0; // 接受用戶選擇
    cin >> select;

    if (select == 1)
    {
        // 查看學生
        cout << "所有學生信息如下: " << endl;
        for_each(vStu.begin(), vStu.end(), printStudent);
    }
    else
    {
        // 查看老師
        cout << "所有老師信息如下: " << endl;
        for_each(vTea.begin(), vTea.end(), printTeacher);
    }

    Clear();
}

// 查看機房信息
void Manager::showComputer()
{
    cout << "機房信息如下: " << endl;

    for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
    {
        cout << "機房編號: " << it->m_ComId << " 機房最大容量: " << it->m_MaxNum << endl;
    }
    Clear();
}

// 清空預約記錄
void Manager::cleanFile()
{
    ofstream ofs(ORDER_FILE, ios::trunc);
    ofs.close();

    cout << "清空成功! " << endl;
    Clear();
}

// 初始化容器
void Manager::initVector()
{
    // 確保容器清空狀態
    vStu.clear();
    vTea.clear();

    // 讀取信息 學生
    ifstream ifs;
    ifs.open(STUDENT_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "文件讀取失敗" << endl;
        return;
    }

    Student s;
    while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
    {
        vStu.push_back(s);
    }

    cout << "當前學生數量為: " << vStu.size() << endl;
    ifs.close();

    // 讀取信息 老師
    ifs.open(TEACHER_FILE, ios::in);
    Teacher t;
    while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
    {
        vTea.push_back(t);
    }

    cout << "當前老師數量為: " << vTea.size() << endl;
    ifs.close();
}

// 檢測重復 參數1 檢測學號/ 職工號 參數2 檢測類型
bool Manager::checkRepeat(int id, int type)
{
    if (type == 1)
    {
        // 檢測學生
        for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
        {
            if (id == it -> m_Id)
            {
                return true;
            }
        }
    }
    else
    {
        // 檢測老師
        for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
        {
            if (id == it -> m_EmpId)
            {
                return true;
            }
        }
    }

    return false;
}