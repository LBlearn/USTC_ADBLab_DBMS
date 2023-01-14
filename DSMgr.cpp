#define _CRT_SECURE_NO_WARNINGS
#include "DSMgr.h"
#include <iostream>
#include <cstdio>
using namespace std;

int w = 0;
int r = 0;

DSMgr::DSMgr()
{
	cout << "MAXPAGES：" << MAXPAGES << "\t" << "FRAMESIZE：" << FRAMESIZE << "\t" << "DEFBUFSIZE：" << DEFBUFSIZE << endl;
	currFile = NULL;
	numPages = 0;
	for (int i = 0; i < MAXPAGES; i++)
	{
		pages[i] = 0;
	}
}

//打开文件函数，成功返回0
int DSMgr::OpenFile(string filename)
{
	currFile = fopen(filename.c_str(), "r+");
	if (currFile == NULL)
	{
		return -1;
	}
	return 0;
}

//关闭文件函数
int DSMgr::CloseFile()
{
	fclose(currFile);
	currFile = NULL;
	return 0;
}

//偏移文件指针
int DSMgr::Seek(int offset, int pos)
{
	if (fseek(currFile, (long)(pos + offset), SEEK_SET) == 0)
		return 0;
	else
		return -1;
}

//读取页到帧中
bFrame* DSMgr::ReadPage(int page_id)
{
	bFrame* tmpPage = (bFrame*)malloc(sizeof(bFrame));
	Seek(page_id * PAGESIZE, 0);
	//把第page_id页读到bFrame中
	if (fread(tmpPage, PAGESIZE, 1, currFile))
	{
		r += 1;
		return tmpPage;
	}
}

//将帧写到页中，w+1
int DSMgr::WritePage(int frame_id, bFrame frm)
{
	int tmpbytes;
	Seek(frame_id * FRAMESIZE, 0);
	tmpbytes = (int)fwrite(&frm, FRAMESIZE, 1, currFile);
	if (tmpbytes)
	{
		w += 1;
		return tmpbytes;
	}
	else
		return -1;
}

FILE* DSMgr::GetFile()
{
	return currFile;
}

//Page数+1
void DSMgr::IncNumPages()
{
	numPages += 1;
}

int DSMgr::GetNumPages()
{
	return numPages;
}

//设置第index页使用了use_bit
void DSMgr::SetUse(int index, int use_bit)
{
	pages[index] = use_bit;
}

int DSMgr::GetUse(int index)
{
	return pages[index];
}