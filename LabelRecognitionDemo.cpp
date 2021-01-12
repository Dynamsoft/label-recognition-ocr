#include <stdio.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <conio.h>
#include <io.h>
#else
#include <dirent.h>
#include <sys/time.h>
#include <cstdlib>
#endif

#include "include/DynamsoftLabelRecognition.h"
#include "include/DynamsoftCommon.h"
using namespace std;
using namespace dynamsoft::dlr;

char* read_file_text(const char* filename) {
	FILE *fp = fopen(filename, "r"); 
    size_t size;
    char *text = NULL;
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
	}
	else {
		printf("Fail to open file\n");
		return NULL;
	}

	rewind(fp);
	text = (char *)calloc((size + 1), sizeof(char));
	if (text == NULL) {fputs ("Memory error",stderr); return NULL;}
	
	char c;
	char *tmp = text;
	do {
      c = fgetc (fp);
      *tmp = c;
	  tmp++;
    } while (c != EOF);
	fclose (fp);
	return text;
}

bool GetImagePath(char* pImagePath)
{
	char pszBuffer[512] = { 0 };
	bool bExit = false;
	size_t iLen = 0;
	FILE* fp = NULL;
	while (1)
	{
		printf("\r\n>> Step 1: Input your image file's full path:\r\n");
#if defined(_WIN32) || defined(_WIN64)
		gets_s(pszBuffer, 512);
#else
		fgets(pszBuffer, 512, stdin);
		strtok(pszBuffer, "\n");
#endif
		iLen = strlen(pszBuffer);
		if (iLen > 0)
		{
			if (strlen(pszBuffer) == 1 && (pszBuffer[0] == 'q' || pszBuffer[0] == 'Q'))
			{
				bExit = true;
				break;
			}

			memset(pImagePath, 0, 512);
			if ((pszBuffer[0] == '\"' && pszBuffer[iLen - 1] == '\"') || (pszBuffer[0] == '\'' && pszBuffer[iLen - 1] == '\''))
				memcpy(pImagePath, &pszBuffer[1], iLen - 2);
			else
				memcpy(pImagePath, pszBuffer, iLen);

#if defined(_WIN32) || defined(_WIN64)
			int err = fopen_s(&fp, pImagePath, "rb");
			if (err == 0)
			{
				fclose(fp);
				break;
			}
#else
			fp = fopen(pImagePath, "rb");
			if (fp != NULL)
			{
				break;
			}
#endif
		}
		printf("Please input a valid path.\r\n");
	}
	return bExit;
}

bool GetIfAutoDetectRegion(bool& autoRegion)
{
	char pszBuffer[512] = { 0 };
	bool bExit = false;
	size_t iLen = 0;
	FILE* fp = NULL;
	while (1)
	{
		printf("\r\n>> Step 2: Do you want the program to auto detect region? [Y/n]:");
#if defined(_WIN32) || defined(_WIN64)
		gets_s(pszBuffer, 512);
#else
		fgets(pszBuffer, 512, stdin);
		strtok(pszBuffer, "\n");
#endif
		iLen = strlen(pszBuffer);
		if (iLen > 0)
		{
			if (strlen(pszBuffer) == 1 && (pszBuffer[0] == 'q' || pszBuffer[0] == 'Q'))
			{
				bExit = true;
				break;
			}
			if (strlen(pszBuffer) == 1 && (pszBuffer[0] == 'y' || pszBuffer[0] == 'Y' || pszBuffer[0] == '1'))
			{
				autoRegion = true;
				break;
			}
			else if (strlen(pszBuffer) == 1 && (pszBuffer[0] == 'n' || pszBuffer[0] == 'N' || pszBuffer[0] == '0'))
			{
				autoRegion = false;
				break;
			}
		}
		else
		{
			autoRegion = true;
			printf("yes (default)\r\n");
			break;
		}
		printf("Please input a valid value.\r\n");
	}
	printf("\r\n");
	return bExit;
}

bool GetRegion(tagDLRPoint* region)
{
	char pszBuffer[512] = { 0 };
	bool bExit = false;
	size_t iLen = 0;
	FILE* fp = NULL;
	char nums[512] = { 0 };
	while (1)
	{
		printf(">> Step 3: Set Set four points (in pixel, seperated by comma) of your region:\r\n");
		int numCount = 0;

		char strPoints[4][10] = { "first", "second", "third", "fourth" };

		int m = 0;
		for (; m < 4;++m)
		{
			printf(">>>> Set the %s point of your region (e.g: (0,0)):", strPoints[m]);
#if defined(_WIN32) || defined(_WIN64)
			gets_s(pszBuffer, 512);
#else
			fgets(pszBuffer, 512, stdin);
			strtok(pszBuffer, "\n");
#endif
			iLen = strlen(pszBuffer);
			if (iLen > 0)
			{
				if (strlen(pszBuffer) == 1 && (pszBuffer[0] == 'q' || pszBuffer[0] == 'Q'))
				{
					bExit = true;
					break;
				}
				int n = 0;
				char temp[512] = "";
				for (int i = 0; i < iLen; ++i)
				{
					if (pszBuffer[i] != ' ')
					{
						temp[n] = pszBuffer[i];
						++n;
					}
				}
				if (temp[0] == '(' && temp[n - 1] == ')')
				{
					memcpy(nums, &temp[1], n - 2);
					nums[n - 2] = '\0';
					int num = 0;
					int flag = 0;
					for (int i = 0; i < n - 2; ++i)
					{
						if (nums[i] == ',')
						{
							region[m].x = num;
							num = 0;
							continue;
						}
						if (nums[i] > '9' || nums[i] < '0')
						{
							flag = 1;
							break;
						}
						num = num * 10 + (nums[i] - '0');
						if(i == n-3)
							region[m].y = num;
					}
					if (flag)
					{
						printf("Please input a valid value.");
						--m;
						continue;
					}
				}
				else
				{
					printf("Please input a valid value.");
					--m;
					continue;
				}

			}
		}
		if (m == 4)
		{
			break;
		}
		if (bExit)
		{
			break;
		}
	}
	return bExit;
}

bool SetDetectRegion(CLabelRecognition& dlr, tagDLRPoint* region, char* errorMsg, int errorMsgLen)
{
	bool bError = false;
	int iRet = 0;
	DLRRuntimeSettings settings;
	dlr.GetRuntimeSettings(&settings);
	settings.referenceRegion.regionMeasuredByPercentage = 0;
	for (int i = 0; i < 4; ++i)
	{
		settings.referenceRegion.points[i] = region[i];
	}

	iRet = dlr.UpdateRuntimeSettings(&settings, errorMsg, errorMsgLen);
	if (iRet != DLR_OK)
		bError = true;
	return bError;
}

void OutputResult(CLabelRecognition& dlr, int errorcode, float time)
{
	if (errorcode != DLR_OK)
		printf("\r\nFailed to recognize label : %s\r\n", dlr.GetErrorString(errorcode));
	else
	{
		DLRResultArray* pDLRResults = NULL;
		dlr.GetAllDLRResults(&pDLRResults);
		if (pDLRResults != NULL)
		{
			int rCount = pDLRResults->resultsCount;
			printf("\r\nRecognized %d results\r\n", rCount);
			for (int ri = 0; ri < rCount; ++ri)
			{
				printf("\r\Result %d :\r\n", ri);
				DLRResult* result = pDLRResults->results[ri];
				int lCount = result->lineResultsCount;
				for (int li = 0; li < lCount; ++li)
				{
					printf("Line result %d: %s\r\n", li, result->lineResults[li]->text);
					DLRPoint *points = result->lineResults[li]->location.points;
					printf("x1: %d, y1: %d, x2: %d, y2: %d, x3: %d, y3: %d, x4: %d, y4: %d\r\n", points[0].x, 
					points[0].y, points[1].x, points[1].y, points[2].x, points[2].y, points[3].x, points[3].y);
				}
			}
		}
		else
		{
			printf("\r\nNo data detected.\r\n");
		}
		dlr.FreeDLRResults(&pDLRResults);
	}

	printf("\r\nTotal time spent: %.3f s\r\n", time);
}

int main(int argc, const char* argv[])
{
	if (argc < 2) {
		printf("Usage: BarcodeReader license.txt\n");
        return 0;
	}
	
	char* license = read_file_text(argv[1]);

	bool bExit = false;
	char szErrorMsg[512];
	char pszImageFile[512] = { 0 };
	bool autoRegion = false;
	tagDLRPoint region[4] = { {0,0},{100,0},{100,100},{0,100} };
#if defined(_WIN32) || defined(_WIN64)
	unsigned _int64 ullTimeBegin = 0;
	unsigned _int64 ullTimeEnd = 0;
#else
	struct timeval ullTimeBegin, ullTimeEnd;
#endif


	printf("*************************************************\r\n");
	printf("Welcome to Dynamsoft Label Recognition Demo\r\n");
	printf("*************************************************\r\n");
	printf("Hints: Please input 'Q' or 'q' to quit the application.\r\n");

	CLabelRecognition dlr;
	int ret = dlr.InitLicense(license);
	printf("License initialization: %d\n\n", ret);

	while (1)
	{
		dlr.ResetRuntimeSettings();

		bExit = GetImagePath(pszImageFile);
		if (bExit)
			break;

		bExit = GetIfAutoDetectRegion(autoRegion);
		if (bExit)
			break;
		
		if (!autoRegion)
		{
			bExit = GetRegion(region);
			if (bExit)
				break;

			if (SetDetectRegion(dlr, region, szErrorMsg, 512))
			{
				printf("\r\nSetDetectRegion Error: %s\r\n", szErrorMsg);
			}
		}

		float costTime = 0.0;
		int errorCode = 0;

#if defined(_WIN32) || defined(_WIN64)
		ullTimeBegin = GetTickCount();
		errorCode = dlr.RecognizeByFile(pszImageFile, "");
		ullTimeEnd = GetTickCount();
		costTime = ((float)(ullTimeEnd - ullTimeBegin)) / 1000;
#else
		gettimeofday(&ullTimeBegin, NULL);
		errorCode = dlr.RecognizeByFile(pszImageFile, "");
		gettimeofday(&ullTimeEnd, NULL);
		costTime = (float)((ullTimeEnd.tv_sec * 1000 * 1000 + ullTimeEnd.tv_usec) - (ullTimeBegin.tv_sec * 1000 * 1000 + ullTimeBegin.tv_usec)) / (1000 * 1000);
#endif

		OutputResult(dlr, errorCode, costTime);
		
	}

	return 0;
}
