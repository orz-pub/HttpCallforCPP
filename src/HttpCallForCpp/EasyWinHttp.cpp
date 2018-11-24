#include "pch.h"

#include "EasyWinHttp.h"

std::string EasyWinHttp::Post(const std::wstring& url, const std::wstring& header, const std::wstring& body)
{
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	LPSTR pszOutBuffer;
	BOOL  bResults = FALSE;
	HINTERNET  hSession = NULL, hConnect = NULL, hRequest = NULL;

	URL_COMPONENTS urlComp;

	// Initialize the URL_COMPONENTS structure.
	ZeroMemory(&urlComp, sizeof(urlComp));
	urlComp.dwStructSize = sizeof(urlComp);

	// Set required component lengths to non-zero 
	// so that they are cracked.
	urlComp.dwSchemeLength = (DWORD)-1;
	urlComp.dwHostNameLength = (DWORD)-1;
	urlComp.dwUrlPathLength = (DWORD)-1;
	urlComp.dwExtraInfoLength = (DWORD)-1;

	if (!WinHttpCrackUrl(url.c_str(), (int)url.length(), 0, &urlComp))
	{
		printf("Error %u in WinHttpCrackUrl.\n", GetLastError());
		return false;
	}

	std::wstring hostName(urlComp.lpszHostName, urlComp.dwHostNameLength);
	std::wstring urlPath(urlComp.lpszUrlPath, urlComp.dwUrlPathLength);

	// Use WinHttpOpen to obtain a session handle.
	hSession = WinHttpOpen(L"WinHTTP Example/1.0",
							WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
							WINHTTP_NO_PROXY_NAME,
							WINHTTP_NO_PROXY_BYPASS, 0);

	// Specify an HTTP server.
	if (hSession)
	{
		hConnect = WinHttpConnect(hSession, hostName.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
	}

	// Create an HTTP request handle.
	if (hConnect)
	{
		hRequest = WinHttpOpenRequest(hConnect, 
									L"POST",
									urlPath.c_str(),
									NULL, WINHTTP_NO_REFERER,
									WINHTTP_DEFAULT_ACCEPT_TYPES,
									WINHTTP_FLAG_SECURE);
	}

	// Send a request.
	if (hRequest)
	{
		std::string d(body.begin(), body.end());

		bResults = WinHttpSendRequest(hRequest,
			header.c_str(), (int)header.length(),
			(LPVOID)d.c_str(), (int)d.length(),
			(int)d.length(),
			0);
	}

	// End the request.
	if (bResults)
	{
		bResults = WinHttpReceiveResponse(hRequest, NULL);
	}

	std::string result = "";

 	if (bResults)
	{
		do
		{
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
			{
				printf("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());
			}

			pszOutBuffer = new char[dwSize + 1];
			if (!pszOutBuffer)
			{
				printf("Out of memory\n");
				dwSize = 0;
			}
			else
			{
				// Read the data.
				ZeroMemory(pszOutBuffer, dwSize + 1);

				if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded))
				{
					printf("Error %u in WinHttpReadData.\n", GetLastError());
				}

				result += pszOutBuffer;

				delete[] pszOutBuffer;
			}
		} while (dwSize > 0);
	}

	// Report any errors.
	if (!bResults)
	{
		printf("Error %d has occurred.\n", GetLastError());
	}

	// Close any open handles.
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);

	return result;
}