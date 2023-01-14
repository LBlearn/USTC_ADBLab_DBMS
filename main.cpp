#define _CRT_SECURE_NO_WARNINGS
#include "BMgr.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

extern int hit;
extern int miss;
extern int r;
extern int w;

int main()
{
	//初始化data.dbf文件
	FILE *filePtr = fopen(DBFFILENAME, "w");
	char bu[FRAMESIZE];
	memset(bu, 1, sizeof(bu));
	for (int i = 0; i < PAGESIZE; i++)
		fwrite(bu,sizeof(char),sizeof(bu), filePtr);
	fclose(filePtr);

	BMgr BufManager;
	cout << "begin test" << endl;
	hit = 0;
	miss = 0;
	r = 0;
	w = 0;
	FILE *file2 = fopen(REQUESTFILENAME, "r");

	int operation;
	int page_id;
	int frame_id;
	int i = 0;
	while (fscanf(file2, "%d,%d", &operation, &page_id) != EOF){
		i++;
		if (i % 100000 == 0)	cout << "The number of requests read in："<<i/1000<<",000" << endl;
		page_id -= 1;
		frame_id = BufManager.FixPage(page_id, 0);
		if (operation == 1)
			BufManager.SetDirty(frame_id);
		BufManager.UnfixPage(page_id);
	}
	BufManager.WriteDirtys();
	BufManager.CloseDSMge();
	cout << "total tests:" << i << "\nhit: " << hit << "\tmiss:" << miss << "\trage:" << 100.0 * hit / i<<"%"<<"\tread:" << r << "\twrite:" << w << endl;
	return 0;
}