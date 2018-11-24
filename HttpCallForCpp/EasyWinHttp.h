#pragma once

class EasyWinHttp
{
public:
	EasyWinHttp() = default;
	virtual ~EasyWinHttp() = default;

	std::string Post(std::wstring url, std::wstring header, std::wstring body);
};