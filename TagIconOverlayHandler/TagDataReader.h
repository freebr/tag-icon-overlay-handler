#pragma once

class CTagDataReader
{
public:
	CTagDataReader();
	~CTagDataReader();

	/**
		���ָ���ļ��Ƿ����ˮӡ��Ϣ�������� cryptMode==2��
	**/
	bool detectTagData(PCWSTR pwszPath);

private:
	DWORD dwSectorsPerCluster;
	DWORD dwBytesToRead;

	/**
		���ָ�������Ƿ����ˮӡ��Ϣ�������� cryptMode==2��
	**/
	bool checkWatermark(BYTE* lpBytes);
	/**
		��ָ���� 16 �ֽ����ݽ��н�������
	**/
	void decrypt16bytes(DWORD* keyDict, BYTE* lpInput, BYTE* lpOutput);
};

