#include "Clear.h"

// 清屏
void Clear::Pause()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); // 等待用户按下 Enter 键
    std::system("clear"); // 使用 clear 命令清屏
}