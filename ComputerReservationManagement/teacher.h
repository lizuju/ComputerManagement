#pragma once
#include <iostream>
#include "Identity.h"
using namespace std;
#include <string>
#include "orderFile.h"
#include <vector>
#include <vector>

// 教師類設計
class Teacher: public Identity
{
public:
    // 默認構造
    Teacher();

    // 有參構造
    Teacher(int empId, string name, string ped);

    // 菜單界面
    virtual void operMenu();

    // 查看所有預約
    void showAllOrder();

    // 審核預約
    void validOrder();

    // 職工號
    int m_EmpId;

};