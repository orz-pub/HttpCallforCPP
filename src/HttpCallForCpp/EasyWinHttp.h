#pragma once

class EasyWinHttp
{
public:
	EasyWinHttp() = default;
	virtual ~EasyWinHttp() = default;

	std::string Post(const std::wstring& url, const std::wstring& header, const std::wstring& body);
};