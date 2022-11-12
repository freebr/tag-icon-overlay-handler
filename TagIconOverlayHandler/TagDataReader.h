#pragma once

class CTagDataReader
{
public:
	CTagDataReader();
	~CTagDataReader();

	/**
		检测指定文件是否包含水印信息（仅考虑 cryptMode==2）
	**/
	bool detectTagData(PCWSTR pwszPath);

private:
	DWORD dwSectorsPerCluster;
	DWORD dwBytesToRead;

	/**
		检测指定数据是否包含水印信息（仅考虑 cryptMode==2）
	**/
	bool checkWatermark(BYTE* lpBytes);
	/**
		对指定的 16 字节数据进行解密运算
	**/
	void decrypt16bytes(DWORD* keyDict, BYTE* lpInput, BYTE* lpOutput);
};

