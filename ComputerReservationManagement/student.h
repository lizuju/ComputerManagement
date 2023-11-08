#pragma once
#include <iostream>
using namespace std;
#include "Identity.h"
#include <string>
#include <vector>
#include "computerRoom.h"
#include <fstream>
#include "globalFile.h"
#include "Clear.h"
#include "orderFile.h"

// 學生類
class Student: public Identity
{
public:

    // 默認構造
    Student();
    // 有參構造 參數: 學號, 姓名, 密碼
    Student(int id, string name, string pwd);

    // 菜單界面
    virtual void operMenu();

    // 申請預約
    void applyOrder();

    // 查看自身預約
    void showMyOrder();

    // 查看所有預約
    void showAllOrder();

    // 取消預約
    void cancelOrder();

    // 學生學號
    int m_Id;

    // 機房容器
    vector<ComputerRoom> vCom;
};