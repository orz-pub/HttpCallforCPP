#include "pch.h"
#include <iostream>
#include <chrono>
#include <ctime>

#include "EasyWinHttp.h"

#pragma warning(disable : 4996)

int main()
{
	std::wstring url = L"https://hooks.slack.com/services/..."; // slack webhook url.
	std::wstring header = L"Content-Type: application/json";
	std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string nowS = std::ctime(&t);
	std::wstring now(nowS.begin(), nowS.end());

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

	std::cout << "===== result =====" << std::endl;
	std::cout << result << std::endl;
	std::cout << "==================" << std::endl;
}