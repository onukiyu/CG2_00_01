#pragma once
#include <string>
namespace StringUtility
{
	// stringをwstringに変換する
	std::wstring ConverString(const std::string& str);

	// wstringをstringに変換する
	std::string ConverString(const std::wstring& str);
};

