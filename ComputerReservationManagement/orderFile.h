#pragma once
#include <iostream>
using namespace std;
#include "globalFile.h"
#include <fstream>
#include <map>
#include <string>
#include "Clear.h"

class OrderFile
{
public:

    // 構造函數
    OrderFile();

    // 更新預約記錄
    void updateOrder();

    // 記錄預約條數
    int m_Size;

    // 記錄所有預約信息的容器 key記錄條數 value具體記錄鍵值對信息
    map<int, map<string, string>> m_orderData;
};