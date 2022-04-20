#pragma once
#include <exception> 
#include <iostream>
#include <iomanip>
#include <time.h>
#include <random>
#include <math.h>


class Vector
{
private:
	int* array;
	int size;
	int length;
	void RestructVector(int newSize);
	void MoreMemory();
	void MoreMemory(int size);
	void LessMemory();
	void SortPath(int start, int length);
	void FillTempArr(int tempArr[], int baseIndex, int tempIndex, int length);
public:
	Vector();
	Vector(int arr[], int length);
	Vector(const Vector& vec);
	~Vector();
	int& operator[](const int index);
	void Push(int elem);
	int Pop();
	void Clear();
	void Insert(int num, int index);
	void Replace(int num, int index);
	void AddRange(int* arr, int length);
	int Length();
	void PrintArr(int size, const int NUMBERS_IN_STRING = 10);

	void MergeSort(int start, int length);
	void AlternativeMergeSort(int start, int length);
	void AlternativeSortPath(int leftIndex, int rightIndex, int length);
	void BobleSort(int size);
	void BobleSortTest(int size);
	void RadixSort(int pow);
	void BlockSort(int rangeOfValues);
};

