/*by:千里扯淡
简单的闹钟
代码写的乱死
ver 1.0
估计也不会出2.0*/
#pragma comment(lib,"winmm.lib")
#include <iostream>
#include <Windows.h>
#include "mmsystem.h"
#include <fstream>
#include <string>
#include <tchar.h>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
using namespace std;
wchar_t* str;//提醒信息
string music;//音乐的string变量
string tmp;//string类型的提醒信息
wchar_t* mus;//音乐名称
void setting()//设置界面
{
	cout << "当前铃声:(M修改,不支持空格,仅支持.wav)" << music << endl;
	cout << "当前提示信息:(M修改,不支持空格)" << tmp << endl;
	cout << "E键退出" << endl;
	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 'm')
			{
				fstream file;
				file.open("config.ini", ios::out);
				cin >> music;
				file<<music;
				file << "\n";
				cin >> tmp;
				file << tmp;
				cout << "设置完成,已退出" << endl;
				break;
			}
			else if (_getch() == 'e')
			{
				cout << "已退出" << endl;
				break;
			}
		}
	}
}
void read()//读取配置
{
	fstream file;
	file.open("config.ini",ios::in);//打开config.ini
	if (file.fail())
	{
		ofstream ini("config.ini");//如果找不到config.ini就新建一个
		read();
	}
	getline(file, music);//读取文件
	getline(file, tmp);
	file.close();
}
void tclo()//计时器
{
	int h, min, s;
	int sl;
	cout << "请输入时间:" << endl;
	cout << "时:";
	cin >> h;
	cout << "分:";
	cin >> min;
	cout << "秒:";
	cin >> s;
	sl = (h * 60 * 60) + (min * 60) + s;
	int c=sl;
	for (int i=sl; i > 0; i--)
	{
		cout << c << endl;
		Sleep(1000);
		c--;
	}
	PlaySound(mus, NULL, SND_FILENAME | SND_ASYNC);//播放音乐
	HWND hwnd=NULL;
	MessageBox(hwnd, str,_T("闹 钟"), MB_OK);//弹出窗口
	exit(1);
}
void clo()//普通的闹钟
{
	int h, min;
	cout << "小时:";
	cin >> h;
	cout << "分钟:";
	cin >> min;
	while (1)
	{
		tm t;
		time_t now;
		time(&now);
		localtime_s(&t, &now);
		if (t.tm_hour == h)
		{
			if (t.tm_min == min)
			{
				PlaySound(mus, NULL, SND_FILENAME | SND_ASYNC);
				HWND hwnd = NULL;
				MessageBox(hwnd, str, _T("闹 钟"), MB_OK);
				exit(1);
			}
		}
	}
}
int main()
{
	setlocale(LC_ALL, "chs");
	read();
	const char* temp = music.c_str();
	char* temp1 = const_cast<char*>(temp);//const char*转char*再转wchar_t* ヽ(´ー`)ﾉ
	size_t len = strlen(temp1) + 1;
	size_t converted = 0;
	mus = (wchar_t*)malloc(len * sizeof(wchar_t));
	mbstowcs_s(&converted, mus, len, temp1, _TRUNCATE);
	const char* temp2 = tmp.c_str();
	char* temp3 = const_cast<char*>(temp2);//再次const char*转char*再转wchar_t* ヽ(´ー`)ﾉ
	size_t len1 = strlen(temp3) + 1;
	size_t converted1 = 0;
	str = (wchar_t*)malloc(len * sizeof(wchar_t));
	mbstowcs_s(&converted1, str, len1, temp3, _TRUNCATE);//我tm上面写的是啥???我自己都看不懂
	cout << "S键进入设置界面" << endl;
	cout << "T键设置倒计时闹钟" << endl;
	cout << "C键设置普通闹钟" << endl;
	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 's')
			{
				setting();
			}
			else if (_getch() == 't')
			{
				tclo();
			}
			else if (_getch() == 'c')
			{
				clo();
			}
		}
	}
	return 0;
}