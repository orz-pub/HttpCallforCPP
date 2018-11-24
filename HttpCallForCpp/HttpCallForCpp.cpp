#include "pch.h"
#include <iostream>

#include "EasyWinHttp.h"

int main()
{
	std::wstring url = L"https://hooks.slack.com/services/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";	//slack api key
	std::wstring header = L"Content-Type: application/json";
	std::wstring data = L"{\"text\":\"Hello\nWorld!\"}";

	EasyWinHttp easyWinHttp;
	std::string result = easyWinHttp.Post(url, header, data);

	std::cout << "===== result =====" << std::endl;
	std::cout << result << std::endl;
	std::cout << "==================" << std::endl;
}