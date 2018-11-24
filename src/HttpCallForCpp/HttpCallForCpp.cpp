#include "pch.h"
#include <iostream>
#include <chrono>
#include <ctime>

#include "EasyWinHttp.h"

#pragma warning(disable : 4996)		// ctime 워닝 끄기 위함.

int main()
{
	std::wstring url = L"https://hooks.slack.com/services/..."; // slack webhook url.
	std::wstring header = L"Content-Type: application/json";

	// 실행할 때마다 username을 바꾸기 위해 현재시간을 사용(username을 바꿔야 테스트 확인하기 좋음).
	std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string ctime = std::ctime(&t);
	std::wstring now(ctime.begin(), ctime.end());

	std::wstring data = L"{"
		LR"("username": ")" + now + LR"(",)"
		LR"("text": "MAIN TEXT",)"
		LR"("attachments": [)"
			LR"({"title": "ATT title", "text": "ATT text ~cancle~ *bold*, `mkdown`", "color": "#FF0000"},)"
			LR"({"text": "```multi line\nlong text\ntest....```", "color": "#00FF00"},)"
			LR"({"text": "```i have footer\nlong text....```", "color": "#0000FF", "footer": "footer: here: `test`"},)"
			LR"({"text": "<https://google.com|link(english only)>"})"
		LR"(],)"
		LR"("mkdown": true)"
	L"}";

	EasyWinHttp easyWinHttp;
	std::string result = easyWinHttp.Post(url, header, data);

	std::cout << "================== result ==================" << std::endl;
	std::cout << result << std::endl;
	std::cout << "============================================" << std::endl;
}