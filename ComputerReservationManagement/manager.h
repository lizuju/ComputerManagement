#pragma once
#include <iostream>
#include "Identity.h"
using namespace std;
#include <string>
#include <fstream>
#include "globalFile.h"
#include <vector>
#include "student.h"
#include "teacher.h"
#include <algorithm>
#include "computerRoom.h"

class Manager: public Identity
{
public:

    // 默認構造
    Manager();

    // 有參構造
    Manager(string name, string pwd);

    // 菜單界面
    virtual void operMenu();

    // 添加賬號
    void addPerson();

    // 查看賬號
    void showPerson();

    // 查看機房信息
    void showComputer();

    // 清空預約記錄
    void cleanFile();

    // 初始化容器
    void initVector();

    // 檢測重復 參數1 檢測學號/ 職工號 參數2 檢測類型
    bool checkRepeat(int id, int type);

    // 學生容器
    vector<Student> vStu;

    // 教師容器
    vector<Teacher> vTea;

    // 機房信息容器
    vector<ComputerRoom>vCom;
};