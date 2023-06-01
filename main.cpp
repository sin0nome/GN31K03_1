// 課題の為非推奨な関数を使用している
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

int main(void) {
	WSADATA		wsaData;
	const WORD version = MAKEWORD(2, 2);	// version
	const auto status = WSAStartup(version, &wsaData);

	// winsock2の初期化
	if(status == SOCKET_ERROR) {
		puts("reset winsock faild");
		return -1;
	}

	// 要求したバージョンを利用可能か確認
	const WORD requiredVersion = MAKEWORD(2, 2);
	if(requiredVersion != wsaData.wVersion) {
		MessageBox(nullptr, L"version error", L"WINSOCK ERROR!!", MB_OK);
		return 1;
	}

	// ホスト名の表示
	char hostname[256];
	gethostname(hostname, (int)sizeof(hostname));
	printf_s("host name:%s\n", hostname);

	printf_s("\nドメイン名を入力してください\n");


	char dommainName[256];
	rewind(stdin);
	const int res = scanf_s("%s", dommainName, 255);

	// ドメイン名からホスト情報を獲得
	HOSTENT* const lphe = gethostbyname(dommainName);
	if(lphe != nullptr) {
		printf_s("ホスト名: %s \n", lphe->h_name);

		for(int i = 0; lphe->h_aliases[i] != nullptr; ++i) {
			printf_s("(%02d) 別名 : %s \n", i, lphe->h_aliases[i]);
		}
		printf_s("アドレスタイプ :%d\n", lphe->h_addrtype);
		printf_s("アドレス長    :%d\n", lphe->h_length);

		in_addr address;
		for(int i = 0; lphe->h_addr_list[i] != NULL; ++i) {
			memset(&address, 0, sizeof(address));
			memcpy_s(&address, sizeof(decltype(address)), lphe->h_addr_list[i], lphe->h_length);
			printf_s("IP Address[%d]:%s\n", i, inet_ntoa(address));
		}

	} else {
		printf_s("error\n");
	}

	WSACleanup();

	return 0;
}

