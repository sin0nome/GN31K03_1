// �ۑ�̈ה񐄏��Ȋ֐����g�p���Ă���
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

int main(void) {
	WSADATA		wsaData;
	const WORD version = MAKEWORD(2, 2);	// version
	const auto status = WSAStartup(version, &wsaData);

	// winsock2�̏�����
	if(status == SOCKET_ERROR) {
		puts("reset winsock faild");
		return -1;
	}

	// �v�������o�[�W�����𗘗p�\���m�F
	const WORD requiredVersion = MAKEWORD(2, 2);
	if(requiredVersion != wsaData.wVersion) {
		MessageBox(nullptr, L"version error", L"WINSOCK ERROR!!", MB_OK);
		return 1;
	}

	// �z�X�g���̕\��
	char hostname[256];
	gethostname(hostname, (int)sizeof(hostname));
	printf_s("host name:%s\n", hostname);

	printf_s("\n�h���C��������͂��Ă�������\n");


	char dommainName[256];
	rewind(stdin);
	const int res = scanf_s("%s", dommainName, 255);

	// �h���C��������z�X�g�����l��
	HOSTENT* const lphe = gethostbyname(dommainName);
	if(lphe != nullptr) {
		printf_s("�z�X�g��: %s \n", lphe->h_name);

		for(int i = 0; lphe->h_aliases[i] != nullptr; ++i) {
			printf_s("(%02d) �ʖ� : %s \n", i, lphe->h_aliases[i]);
		}
		printf_s("�A�h���X�^�C�v :%d\n", lphe->h_addrtype);
		printf_s("�A�h���X��    :%d\n", lphe->h_length);

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

