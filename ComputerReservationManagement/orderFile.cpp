#include "orderFile.h"

// 構造函數
OrderFile::OrderFile()
{
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);

    string data;    // 日期
    string interval;    // 時間段
    string stuId;   // 學生編號
    string stuName; //  學生姓名
    string roomId;  // 機房編號
    string status;  // 預約狀態

    this->m_Size = 0;   // 記錄條數

    while (ifs >> data && ifs >> interval && ifs
        >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
    {
//        cout << data << endl;
//        cout << interval << endl;
//        cout << stuId << endl;
//        cout << stuName << endl;
//        cout << roomId << endl;
//        cout << status << endl;
//        cout << endl;

        // data: 1
        string key;
        string value;
        map<string, string> m;

        int pos = data.find(":");   // 4
        if (pos != -1)
        {
            key = data.substr(0, pos);
            value = data.substr(pos+1, data.size()); // size = 9  pos = 4  size - pos = 5 - 1

            m.insert(make_pair(key, value));
        }

//        cout << "key = " << key << endl;
//        cout << "value = " << value << endl;

        // 截取時間段
        pos = interval.find(":");   // 4
        if (pos != -1)
        {
            key = interval.substr(0, pos);
            value = interval.substr(pos+1, interval.size()); // size = 9  pos = 4  size - pos = 5 - 1

            m.insert(make_pair(key, value));
        }

        // 截取學號
        pos = stuId.find(":");   // 4
        if (pos != -1)
        {
            key = stuId.substr(0, pos);
            value = stuId.substr(pos+1, stuId.size()); // size = 9  pos = 4  size - pos = 5 - 1

            m.insert(make_pair(key, value));
        }

        // 截取姓名
        pos = stuName.find(":");   // 4
        if (pos != -1)
        {
            key = stuName.substr(0, pos);
            value = stuName.substr(pos+1, stuName.size()); // size = 9  pos = 4  size - pos = 5 - 1

            m.insert(make_pair(key, value));
        }

        // 截取機房號
        pos = roomId.find(":");   // 4
        if (pos != -1)
        {
            key = roomId.substr(0, pos);
            value = roomId.substr(pos+1, roomId.size()); // size = 9  pos = 4  size - pos = 5 - 1

            m.insert(make_pair(key, value));
        }

        // 截取預約段
        pos = status.find(":");   // 4
        if (pos != -1)
        {
            key = status.substr(0, pos);
            value = status.substr(pos+1, status.size()); // size = 9  pos = 4  size - pos = 5 - 1

            m.insert(make_pair(key, value));
        }

        // 將小的map容器放入到大的map容器中
        this->m_orderData.insert(make_pair(this->m_Size, m));
        this->m_Size++;
    }

    ifs.close();

    // 測試最大map容器
//    for (map<int, map<string, string>>::iterator it = m_orderData.begin(); it != m_orderData.end(); it++)
//    {
//        cout << "條數為 = "  << it->first << " value = " << endl;
//        for (map<string, string>::iterator mit = (*it).second.begin(); mit != it->second.end(); mit++)
//        {
//            cout << " key = " << mit->first << " value = " << mit->second << " ";
//        }
//        cout << endl;
//    }
}

// 更新預約記錄
void OrderFile::updateOrder()
{
    if (this->m_Size == 0)
    {
        return; // 預約記錄0條, 直接return
    }

    ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
    for (int i = 0; i < this->m_Size; i++)
    {
        ofs << "date:" << this->m_orderData[i]["date"] << " ";
        ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
        ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
        ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
        ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
        ofs << "status:" << this->m_orderData[i]["status"] << " ";
    }

    ofs.close();

    Clear();
}