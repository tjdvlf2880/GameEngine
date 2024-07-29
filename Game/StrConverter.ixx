module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
export module StrConverter;
import std;

export std::string WStringToString(const std::wstring& wstr ,UINT codepage = CP_UTF8)
{
	// 필요한 버퍼 크기 계산
	int size_needed = WideCharToMultiByte(codepage, 0, wstr.c_str(), static_cast<int>(wstr.size()), NULL, 0, NULL, NULL);
	if (size_needed <= 0) {
		throw std::runtime_error("Failed to calculate buffer size");
	}

	// 버퍼를 할당하고 변환 수행
	std::string str(size_needed, 0);
	WideCharToMultiByte(codepage, 0, wstr.c_str(), static_cast<int>(wstr.size()), &str[0], size_needed, NULL, NULL);
	return str;
}
export std::wstring StringToWString(const std::string& str, UINT codepage = CP_UTF8)
{
	// 필요한 버퍼 크기 계산
	int size_needed = MultiByteToWideChar(codepage, 0, str.c_str(), static_cast<int>(str.size()), NULL, 0);
	if (size_needed <= 0) {
		throw std::runtime_error("Failed to calculate buffer size");
	}

	// 버퍼를 할당하고 변환 수행
	std::wstring wstr(size_needed, 0);
	MultiByteToWideChar(codepage, 0, str.c_str(), static_cast<int>(str.size()), &wstr[0], size_needed);
	return wstr;
}

export std::wstring Utf8ToWString(const std::string& str)
{
	// 필요한 버퍼 크기 계산
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), NULL, 0);
	if (size_needed <= 0) {
		throw std::runtime_error("Failed to calculate buffer size");
	}

	// 버퍼를 할당하고 변환 수행
	std::wstring wstr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), &wstr[0], size_needed);
	return wstr;
}
