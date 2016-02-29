// Demo project and test code for the TailKeeper class.
// By John D. Cook, http://www.JohnDCook.com

#include "TailKeeper.h"
#include "FixedSizeHeapTester.h"
#include <algorithm>
#include <assert.h>

#include<windows.h>
#include<time.h>
int main()
{


	//��ȷ�� 0.000001���� ===============================
	LARGE_INTEGER litmp;
	LONGLONG start, end;
	double dft, dff, dfm;
	QueryPerformanceFrequency(&litmp);//���ʱ��Ƶ��
	dff = (double) litmp.QuadPart;
	
	///////////////////////////////////////////////////////////////////////////
	// Test the heap class used in the implementation of TailKeeper.
	// An assert statement will throw an exception if a test fails.
	FixedSizeHeapTester t;
	t.Test();

	///////////////////////////////////////////////////////////////////////////
	// Generate a list of random integers.
	int length = 100000000;
	std::vector<int> data(length);
	data[0] = 137; // arbitrary seed
	for (int i = 1; i != length; ++i)
	{
		// This is George Marsaglia's "CONG" random number generator.
		data[i] = 69069*data[i-1] + 1234567;
	}

	///////////////////////////////////////////////////////////////////////////
	// Find the 50th smallest and 40th largest elements using TailKeeper.
	int lower = 50, upper = 40;
	TailKeeper<int, int> tk(lower, upper);


	QueryPerformanceCounter(&litmp);//��ó�ʼֵ
	start = litmp.QuadPart; 

	for (int i = 0; i != length; ++i)
		tk.AddSample( data[i] );
	int leftTailTK = tk.GetMaxLeftTail();
	int rightTailTK = tk.GetMinRightTail();

	QueryPerformanceCounter(&litmp);//�����ֵֹ
	end = litmp.QuadPart;
	dfm = (double) (end - start);
	dft = dfm / dff;//��ö�Ӧ��ʱ��ֵ,��λ��
	printf("%lf����\n",dfm/dff*1000);

	///////////////////////////////////////////////////////////////////////////
	// Find the same values directly by sorting the entire list.
	QueryPerformanceCounter(&litmp);//��ó�ʼֵ
	start = litmp.QuadPart; 

	std::sort(data.begin(), data.end());
	int leftTailSort = data[lower-1];
	int rightTailSort = data[length - upper];

	QueryPerformanceCounter(&litmp);//�����ֵֹ
	end = litmp.QuadPart;
	dfm = (double) (end - start);
	dft = dfm / dff;//��ö�Ӧ��ʱ��ֵ,��λ��
	printf("%lf����\n",dfm/dff*1000);

	///////////////////////////////////////////////////////////////////////////
	// Compare the results.
	assert(leftTailTK == leftTailSort);
	assert(rightTailTK == rightTailSort);


#ifdef _DEBUG
	// If we haven't thrown an exception by now, all tests pass.
	std::cout << "All TailKeeper tests pass\n";
#endif

	getchar();
	return 0;
}