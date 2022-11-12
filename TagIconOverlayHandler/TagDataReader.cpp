#include "stdafx.h"
#include "TagDataReader.h"
#include "CryptDictionary.h"

CTagDataReader::CTagDataReader() : dwSectorsPerCluster(0), dwBytesToRead(0)
{
}

CTagDataReader::~CTagDataReader()
{
}

/**
	检测指定文件是否包含水印信息（仅考虑 cryptMode==2）
**/
bool CTagDataReader::detectTagData(PCWSTR pwszPath)
{
	wchar_t pwszRootPath[3] = { pwszPath[0], L':', 0 };
	GetDiskFreeSpace(pwszRootPath, &dwSectorsPerCluster, &dwBytesToRead, NULL, NULL);
	HANDLE hFile;
	try {
		hFile = CreateFile(pwszPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == (HANDLE)-1) throw(-1);

		PLARGE_INTEGER pli = new LARGE_INTEGER();
		if (GetFileSizeEx(hFile, pli) == 0) throw(-1);
		// 水印文件的大小一定大于一个簇
		if (pli->QuadPart == 0 || pli->LowPart <= 4096 || pli->QuadPart % dwBytesToRead > 0) throw(-1);
		DWORD dwBytesRead = 0;
		BYTE lpBuffer[1020];
		// 从文件结尾向后读取一个扇区的字节数
		SetFilePointer(hFile, -(LONG)dwBytesToRead, NULL, FILE_END);
		ReadFile(hFile, lpBuffer, dwBytesToRead, &dwBytesRead, NULL);

		if (dwBytesRead != dwBytesToRead) throw(-1);
		// LONGLONG dwRemainingBytes = pli->QuadPart - (LONGLONG)dwBytesToRead;
		// 512 << 4 == 32
		// 4096 << 4 == 256
		DWORD counter = dwBytesToRead >> 4;
		BYTE* lpByte = lpBuffer;
		if (counter)
		{
			while (counter > 0)
			{
				decrypt16bytes(v2cryptKeyCommonDict, lpByte, lpByte);
				lpByte = (BYTE*)&(((DWORD*)lpByte)[4]);
				counter--;
			}
		}
		if (!checkWatermark(&lpBuffer[137])) throw(-1);
		CloseHandle(hFile);
		pli = NULL;
		return true;
	}
	catch (int e)
	{
		CloseHandle(hFile);
		return false;
	}
}

/**
	检测指定数据是否包含水印信息（仅考虑 cryptMode==2）
**/
bool CTagDataReader::checkWatermark(BYTE* lpBytes)
{
	// 第1个 .SJZ
	if (lpBytes[0] == 46 && lpBytes[1] == 83 && lpBytes[2] == 74 && lpBytes[3] == 90) {
		// 第2个 .SJZ
		if (lpBytes[371] == 46 && lpBytes[372] == 83 && lpBytes[373] == 74 && lpBytes[374] == 90) {
			return true;
		}
		return false;
	}
	if (lpBytes[371] == 46 && lpBytes[372] == 83 && lpBytes[373] == 74 && lpBytes[374] == 90) {
		return true;
	}
	return false;
}

/**
	对指定的 16 字节数据进行解密运算
**/
void CTagDataReader::decrypt16bytes(DWORD* keyDict, BYTE* lpInput, BYTE* lpOutput)
{
	DWORD v4, v5, v6, v7, v8, v9, v10;
	DWORD v11, v12, v13, v14, v15, v16, v17, v18, v19, v20;
	DWORD v21, v22, v23, v24, v25, v26, v27, v28, v29, v30;
	DWORD v31, v32, v33, v34, v35, v36, v37, v38, v39, v40;
	DWORD v41, v42, v43, v44, v45, v46, v47, v48, v49, v50;
	DWORD *v51, *v52, *v53;
	DWORD v54, v55, v56, v57, v58;

	//  第 1 组
	v38 = keyDict[64] ^ _byteswap_ulong(((DWORD*)lpInput)[0]);
	v4 = keyDict[65] ^ _byteswap_ulong(((DWORD*)lpInput)[1]);
	v17 = keyDict[66] ^ _byteswap_ulong(((DWORD*)lpInput)[2]);
	v25 = keyDict[67] ^ _byteswap_ulong(((DWORD*)lpInput)[3]);
	//  第 2 组
	v12 = v2DictDecrypt0[LOBYTE(v4)] ^ v2DictDecrypt1[((BYTE*)&v17)[1]] ^ v2DictDecrypt2[((BYTE*)&v25)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v38))] ^ keyDict[68];
	v33 = v2DictDecrypt0[LOBYTE(v17)] ^ v2DictDecrypt1[((BYTE*)&v25)[1]] ^ v2DictDecrypt2[((BYTE*)&v38)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v4))] ^ keyDict[69];
	v54 = v2DictDecrypt0[LOBYTE(v25)] ^ v2DictDecrypt1[((BYTE*)&v38)[1]] ^ v2DictDecrypt2[((BYTE*)&v4)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v17))] ^ keyDict[70];
	v46 = v2DictDecrypt0[LOBYTE(v38)] ^ v2DictDecrypt1[((BYTE*)&v4)[1]] ^ v2DictDecrypt2[((BYTE*)&v17)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v25))] ^ keyDict[71];
	//  第 3 组
	v39 = v2DictDecrypt0[LOBYTE(v33)] ^ v2DictDecrypt1[((BYTE*)&v54)[1]] ^ v2DictDecrypt2[((BYTE*)&v46)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v12))] ^ keyDict[72];
	v5 = v2DictDecrypt0[LOBYTE(v54)] ^ v2DictDecrypt1[((BYTE*)&v46)[1]] ^ v2DictDecrypt2[((BYTE*)&v12)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v33))] ^ keyDict[73];
	v18 = v2DictDecrypt0[LOBYTE(v46)] ^ v2DictDecrypt1[((BYTE*)&v12)[1]] ^ v2DictDecrypt2[((BYTE*)&v33)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v54))] ^ keyDict[74];
	v26 = v2DictDecrypt0[LOBYTE(v12)] ^ v2DictDecrypt1[((BYTE*)&v33)[1]] ^ v2DictDecrypt2[((BYTE*)&v54)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v46))] ^ keyDict[75];
	//  第 4 组
	v13 = v2DictDecrypt0[LOBYTE(v5)] ^ v2DictDecrypt1[((BYTE*)&v18)[1]] ^ v2DictDecrypt2[((BYTE*)&v26)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v39))] ^ keyDict[76];
	v34 = v2DictDecrypt0[LOBYTE(v18)] ^ v2DictDecrypt1[((BYTE*)&v26)[1]] ^ v2DictDecrypt2[((BYTE*)&v39)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v5))] ^ keyDict[77];
	v55 = v2DictDecrypt0[LOBYTE(v26)] ^ v2DictDecrypt1[((BYTE*)&v39)[1]] ^ v2DictDecrypt2[((BYTE*)&v5)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v18))] ^ keyDict[78];
	v47 = v2DictDecrypt0[LOBYTE(v39)] ^ v2DictDecrypt1[((BYTE*)&v5)[1]] ^ v2DictDecrypt2[((BYTE*)&v18)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v26))] ^ keyDict[79];
	//  第 5 组
	v40 = v2DictDecrypt0[LOBYTE(v34)] ^ v2DictDecrypt1[((BYTE*)&v55)[1]] ^ v2DictDecrypt2[((BYTE*)&v47)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v13))] ^ keyDict[80];
	v6 = v2DictDecrypt0[LOBYTE(v55)] ^ v2DictDecrypt1[((BYTE*)&v47)[1]] ^ v2DictDecrypt2[((BYTE*)&v13)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v34))] ^ keyDict[81];
	v19 = v2DictDecrypt0[LOBYTE(v47)] ^ v2DictDecrypt1[((BYTE*)&v13)[1]] ^ v2DictDecrypt2[((BYTE*)&v34)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v55))] ^ keyDict[82];
	v27 = v2DictDecrypt0[LOBYTE(v13)] ^ v2DictDecrypt1[((BYTE*)&v34)[1]] ^ v2DictDecrypt2[((BYTE*)&v55)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v47))] ^ keyDict[83];
	//  第 6 组
	v14 = v2DictDecrypt0[LOBYTE(v6)] ^ v2DictDecrypt1[((BYTE*)&v19)[1]] ^ v2DictDecrypt2[((BYTE*)&v27)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v40))] ^ keyDict[84];
	v35 = v2DictDecrypt0[LOBYTE(v19)] ^ v2DictDecrypt1[((BYTE*)&v27)[1]] ^ v2DictDecrypt2[((BYTE*)&v40)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v6))] ^ keyDict[85];
	v56 = v2DictDecrypt0[LOBYTE(v27)] ^ v2DictDecrypt1[((BYTE*)&v40)[1]] ^ v2DictDecrypt2[((BYTE*)&v6)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v19))] ^ keyDict[86];
	v48 = v2DictDecrypt0[LOBYTE(v40)] ^ v2DictDecrypt1[((BYTE*)&v6)[1]] ^ v2DictDecrypt2[((BYTE*)&v19)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v27))] ^ keyDict[87];
	//  第 7 组
	v41 = v2DictDecrypt0[LOBYTE(v35)] ^ v2DictDecrypt1[((BYTE*)&v56)[1]] ^ v2DictDecrypt2[((BYTE*)&v48)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v14))] ^ keyDict[88];
	v7 = v2DictDecrypt0[LOBYTE(v56)] ^ v2DictDecrypt1[((BYTE*)&v48)[1]] ^ v2DictDecrypt2[((BYTE*)&v14)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v35))] ^ keyDict[89];
	v20 = v2DictDecrypt0[LOBYTE(v48)] ^ v2DictDecrypt1[((BYTE*)&v14)[1]] ^ v2DictDecrypt2[((BYTE*)&v35)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v56))] ^ keyDict[90];
	v28 = v2DictDecrypt0[LOBYTE(v14)] ^ v2DictDecrypt1[((BYTE*)&v35)[1]] ^ v2DictDecrypt2[((BYTE*)&v56)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v48))] ^ keyDict[91];
	//  第 8 组
	v15 = v2DictDecrypt0[LOBYTE(v7)] ^ v2DictDecrypt1[((BYTE*)&v20)[1]] ^ v2DictDecrypt2[((BYTE*)&v28)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v41))] ^ keyDict[92];
	v36 = v2DictDecrypt0[LOBYTE(v20)] ^ v2DictDecrypt1[((BYTE*)&v28)[1]] ^ v2DictDecrypt2[((BYTE*)&v41)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v7))] ^ keyDict[93];
	v57 = v2DictDecrypt0[LOBYTE(v28)] ^ v2DictDecrypt1[((BYTE*)&v41)[1]] ^ v2DictDecrypt2[((BYTE*)&v7)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v20))] ^ keyDict[94];
	v49 = v2DictDecrypt0[LOBYTE(v41)] ^ v2DictDecrypt1[((BYTE*)&v7)[1]] ^ v2DictDecrypt2[((BYTE*)&v20)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v28))] ^ keyDict[95];
	//  第 9 组
	v42 = v2DictDecrypt0[LOBYTE(v36)] ^ v2DictDecrypt1[((BYTE*)&v57)[1]] ^ v2DictDecrypt2[((BYTE*)&v49)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v15))] ^ keyDict[96];
	v8 = v2DictDecrypt0[LOBYTE(v57)] ^ v2DictDecrypt1[((BYTE*)&v49)[1]] ^ v2DictDecrypt2[((BYTE*)&v15)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v36))] ^ keyDict[97];
	v21 = v2DictDecrypt0[LOBYTE(v49)] ^ v2DictDecrypt1[((BYTE*)&v15)[1]] ^ v2DictDecrypt2[((BYTE*)&v36)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v57))] ^ keyDict[98];
	v29 = v2DictDecrypt0[LOBYTE(v15)] ^ v2DictDecrypt1[((BYTE*)&v36)[1]] ^ v2DictDecrypt2[((BYTE*)&v57)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v49))] ^ keyDict[99];
	v51 = &keyDict[100];
	//  第 10 组
	v16 = v2DictDecrypt0[LOBYTE(v8)] ^ v2DictDecrypt1[((BYTE*)&v21)[1]] ^ v2DictDecrypt2[((BYTE*)&v29)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v42))] ^ keyDict[100];
	v37 = v2DictDecrypt0[LOBYTE(v21)] ^ v2DictDecrypt1[((BYTE*)&v29)[1]] ^ v2DictDecrypt2[((BYTE*)&v42)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v8))] ^ keyDict[101];
	v58 = v2DictDecrypt0[LOBYTE(v29)] ^ v2DictDecrypt1[((BYTE*)&v42)[1]] ^ v2DictDecrypt2[((BYTE*)&v8)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v21))] ^ keyDict[102];
	v50 = v2DictDecrypt0[LOBYTE(v42)] ^ v2DictDecrypt1[((BYTE*)&v8)[1]] ^ v2DictDecrypt2[((BYTE*)&v21)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v29))] ^ keyDict[103];
	if (keyDict[128] > 10)
	{
		//  第 11 组
		v43 = v2DictDecrypt0[LOBYTE(v37)] ^ v2DictDecrypt1[((BYTE*)&v58)[1]] ^ v2DictDecrypt2[((BYTE*)&v50)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v16))] ^ keyDict[104];
		v9 = v2DictDecrypt0[LOBYTE(v58)] ^ v2DictDecrypt1[((BYTE*)&v50)[1]] ^ v2DictDecrypt2[((BYTE*)&v16)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v37))] ^ keyDict[105];
		v22 = v2DictDecrypt0[LOBYTE(v50)] ^ v2DictDecrypt1[((BYTE*)&v16)[1]] ^ v2DictDecrypt2[((BYTE*)&v37)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v58))] ^ keyDict[106];
		v30 = v2DictDecrypt0[LOBYTE(v16)] ^ v2DictDecrypt1[((BYTE*)&v37)[1]] ^ v2DictDecrypt2[((BYTE*)&v58)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v50))] ^ keyDict[107];
		v51 = &keyDict[108];
		//  第 12 组
		v16 = v2DictDecrypt0[LOBYTE(v9)] ^ v2DictDecrypt1[((BYTE*)&v22)[1]] ^ v2DictDecrypt2[((BYTE*)&v30)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v43))] ^ keyDict[108];
		v37 = v2DictDecrypt0[LOBYTE(v22)] ^ v2DictDecrypt1[((BYTE*)&v30)[1]] ^ v2DictDecrypt2[((BYTE*)&v43)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v9))] ^ keyDict[109];
		v58 = v2DictDecrypt0[LOBYTE(v30)] ^ v2DictDecrypt1[((BYTE*)&v43)[1]] ^ v2DictDecrypt2[((BYTE*)&v9)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v22))] ^ keyDict[110];
		v50 = v2DictDecrypt0[LOBYTE(v43)] ^ v2DictDecrypt1[((BYTE*)&v9)[1]] ^ v2DictDecrypt2[((BYTE*)&v22)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v30))] ^ keyDict[111];
	}
	if (keyDict[128] > 12)
	{
		v52 = &v51[4];
		//  第 13 组
		v44 = v2DictDecrypt0[LOBYTE(v37)] ^ v2DictDecrypt1[((BYTE*)&v58)[1]] ^ v2DictDecrypt2[((BYTE*)&v50)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v16))] ^ v52[0];
		v10 = v2DictDecrypt0[LOBYTE(v58)] ^ v2DictDecrypt1[((BYTE*)&v50)[1]] ^ v2DictDecrypt2[((BYTE*)&v16)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v37))] ^ v52[1];
		v23 = v2DictDecrypt0[LOBYTE(v50)] ^ v2DictDecrypt1[((BYTE*)&v16)[1]] ^ v2DictDecrypt2[((BYTE*)&v37)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v58))] ^ v52[2];
		v31 = v2DictDecrypt0[LOBYTE(v16)] ^ v2DictDecrypt1[((BYTE*)&v37)[1]] ^ v2DictDecrypt2[((BYTE*)&v58)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v50))] ^ v52[3];
		v51 = &v52[4];
		//  第 14 组
		v16 = v2DictDecrypt0[LOBYTE(v10)] ^ v2DictDecrypt1[((BYTE*)&v23)[1]] ^ v2DictDecrypt2[((BYTE*)&v31)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v44))] ^ v51[0];
		v37 = v2DictDecrypt0[LOBYTE(v23)] ^ v2DictDecrypt1[((BYTE*)&v31)[1]] ^ v2DictDecrypt2[((BYTE*)&v44)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v10))] ^ v51[1];
		v58 = v2DictDecrypt0[LOBYTE(v31)] ^ v2DictDecrypt1[((BYTE*)&v44)[1]] ^ v2DictDecrypt2[((BYTE*)&v10)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v23))] ^ v51[2];
		v50 = v2DictDecrypt0[LOBYTE(v44)] ^ v2DictDecrypt1[((BYTE*)&v10)[1]] ^ v2DictDecrypt2[((BYTE*)&v23)[2]] ^ v2DictDecrypt3[HIBYTE(HIWORD(v31))] ^ v51[3];
	}
	v53 = &v51[4];
	//  第 15 组
	v45 = v2DictDecrypt4[LOBYTE(v37)] ^ (v2DictDecrypt4[((BYTE*)&v58)[1]] << 8) ^ (v2DictDecrypt4[((BYTE*)&v50)[2]] << 16) ^ v53[0] ^ (v2DictDecrypt4[HIBYTE(HIWORD(v16))] << 24);
	v11 = v2DictDecrypt4[LOBYTE(v58)] ^ (v2DictDecrypt4[((BYTE*)&v50)[1]] << 8) ^ (v2DictDecrypt4[((BYTE*)&v16)[2]] << 16) ^ v53[1] ^ (v2DictDecrypt4[HIBYTE(HIWORD(v37))] << 24);
	v24 = v2DictDecrypt4[LOBYTE(v50)] ^ (v2DictDecrypt4[((BYTE*)&v16)[1]] << 8) ^ (v2DictDecrypt4[((BYTE*)&v37)[2]] << 16) ^ v53[2] ^ (v2DictDecrypt4[HIBYTE(HIWORD(v58))] << 24);
	v32 = v2DictDecrypt4[LOBYTE(v16)] ^ (v2DictDecrypt4[((BYTE*)&v37)[1]] << 8) ^ (v2DictDecrypt4[((BYTE*)&v58)[2]] << 16) ^ v53[3] ^ (v2DictDecrypt4[HIBYTE(HIWORD(v50))] << 24);

	((DWORD*)lpOutput)[0] = _byteswap_ulong(v45);
	((DWORD*)lpOutput)[1] = _byteswap_ulong(v11);
	((DWORD*)lpOutput)[2] = _byteswap_ulong(v24);
	((DWORD*)lpOutput)[3] = _byteswap_ulong(v32);

	return;
}