#include <stdio.h>
#include <string.h>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgcodecs.hpp"

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
using namespace cv;

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


void showImage(string windowName, Mat &img, double hScale, double wScale, int imgWidth, int imgHeight)
{
	if (hScale >= wScale && hScale > 1)
	{
		Mat newImage;
		resize(img, newImage, Size(int(imgWidth / hScale), int(imgHeight / hScale)));
		imshow(windowName, newImage);
		imwrite(windowName + ".jpg", newImage);
	}
	else if (hScale <= wScale && wScale > 1)
	{
		Mat newImage;
		resize(img, newImage, Size(int(imgWidth / wScale), int(imgHeight / wScale)));
		imshow(windowName, newImage);
		imwrite(windowName + ".jpg", newImage);
	}
	else 
	{
		imshow(windowName, img);
		imwrite(windowName + ".jpg", img);
	}

}

void destroyWindow()
{
	waitKey(0);
	destroyAllWindows();
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
	const char* windowName = "Dynamsoft Label Recognition";

	printf("*************************************************\r\n");
	printf("Welcome to Dynamsoft Label Recognition Demo\r\n");
	printf("*************************************************\r\n");
	printf("Hints: Please input 'Q' or 'q' to quit the application.\r\n");

	CLabelRecognition dlr;
	int ret = dlr.InitLicense(license);
	printf("License initialization: %d\n\n", ret);

	int maxWidth = 800, maxHeight = 800, padding = 5;

	while (1)
	{
		double hScale = 1.0, wScale = 1.0;

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

		// Read an image
		Mat img = imread(pszImageFile);
		int imgHeight = img.rows, imgWidth = img.cols;
		int thickness = 2;
		Scalar color(0, 255, 0);

		if (imgHeight > maxHeight) 
		{
			hScale = imgHeight * 1.0 / maxHeight;
			thickness = 6;
		}
			

		if (imgWidth > maxWidth)
		{
			wScale = imgWidth * 1.0 / maxWidth;
			thickness = 6;
		}

		DLRImageData data = {img.step.p[0] * imgHeight, img.data, imgWidth, imgHeight, img.step.p[0], DLR_IPF_RGB_888};
		TickMeter tm;
		tm.start();
		errorCode = dlr.RecognizeByBuffer(&data, "");
		tm.stop();
		costTime = tm.getTimeSec();

		if (errorCode != DLR_OK)
			printf("\r\nFailed to recognize label : %s\r\n", dlr.GetErrorString(errorCode));
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
						int x1 = points[0].x, y1 = points[0].y;
						int minX = x1, minY = y1;
						int x2 = points[1].x, y2 = points[1].y;
						minX = minX < x2 ? minX : x2;
						minY = minY < y2 ? minY : y2;
						int x3 = points[2].x, y3 = points[2].y;
						minX = minX < x3 ? minX : x3;
						minY = minY < y3 ? minY : y3;
						int x4 = points[3].x, y4 = points[3].y;
						minX = minX < x4 ? minX : x4;
						minY = minY < y4 ? minY : y4;
						line( img, Point(x1, y1), Point(x2, y2), cv::Scalar(255, 0, 0), thickness);
						line( img, Point(x2, y2), Point(x3, y3), cv::Scalar(255, 0, 0), thickness);
						line( img, Point(x3, y3), Point(x4, y4), cv::Scalar(255, 0, 0), thickness);
						line( img, Point(x4, y4), Point(x1, y1), cv::Scalar(255, 0, 0), thickness);
						putText(img, result->lineResults[li]->text, Point(minX, minY - 10), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 1, LINE_AA);
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

		showImage(windowName, img, hScale, wScale, imgWidth, imgHeight);
		destroyWindow();
	}

	return 0;
}
