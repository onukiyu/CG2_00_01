#pragma once

#include <windows.h>
//#include <wrl.h>

// WindowsAPI
class WinApp
{
public: // 静的メンバ関数
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: //メンバ関数
	//初期化
	void Intialize();
	// 更新
	void Update();
};