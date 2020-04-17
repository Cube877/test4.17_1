// test4.17_1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("E:\\Picture\\rim.png");
	Mat grayMat;
	Mat srcMat_b;
	Mat labels, stats, centroids;
	cvtColor(srcMat, grayMat, COLOR_BGR2GRAY);
	threshold(grayMat, srcMat_b, 100, 255, THRESH_OTSU);
	int height = srcMat_b.rows;
	int width = srcMat_b.cols;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			srcMat_b.at<uchar>(j, i) = 255 - srcMat_b.at<uchar>(j, i);
		}
	}
	Mat dst = srcMat.clone();
	int t = connectedComponentsWithStats(srcMat_b, labels, stats, centroids);
	for (int i = 1; i < t; i++)
	{
		Rect bndbox;
		bndbox.x = stats.at<int>(i, 0);
		bndbox.y = stats.at<int>(i, 1);
		bndbox.width = stats.at<int>(i, 2);
		bndbox.height = stats.at<int>(i, 3);
		double p = bndbox.width / bndbox.height;
		if (p > 0.9 && p < 1.1 && stats.at<int>(i, 4) > 1000 && stats.at<int>(i, 4) < 10000)
		{
			rectangle(dst, bndbox, CV_RGB(255, 0, 0), 1, 8, 0);
		}
	}

	imshow("srcMat", srcMat);
	imshow("srcMat_b", srcMat_b);
	imshow("dst", dst);
	waitKey();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
