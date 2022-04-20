#include "Vector.h"
#include <vector>

//Private:
void Vector::RestructVector(int newSize)
{
	if (newSize < 8)
		newSize = 8;
	int* temp = new int[newSize];
	for (int i = 0; i < length; i++)
	{
		temp[i] = this->array[i];
	}
	delete[] this->array;
	this->array = temp;
	this->size = newSize;
}

void Vector::MoreMemory()
{
	if (size < 256)
	{
		RestructVector(size * 2);
	}
	else
	{
		if (size % 256 != 0)
		{
			size += size % 256;
		}
		RestructVector(size * 2);
	}
}
void Vector::MoreMemory(int size)
{
	if (this->size < size)
	{
		if (size > 256)
		{
			RestructVector(size + (256 - size % 256));
		}
		else
		{
			RestructVector(size);
		}
	}
}
void Vector::LessMemory()
{
	if (size > 8)
	{
		if (size < 256)
		{
			while (size / 2 > length)
			{
				size /= 2;
			}
			RestructVector(size);
		}
		else
		{
			RestructVector(length);
		}
	}
}
//public:
Vector::Vector() : size(8), length(0)
{
	this->array = new int[size];
}
Vector::Vector(int arr[], int length)
{
	this->array = new int[length];
	for (int i = 0; i < length; i++)
	{
		array[i] = arr[i];
	}
	this->length = length;
	this->size = length;
}
Vector::Vector(const Vector& vec)
{
	this->size = vec.size;
	this->length = vec.length;
	this->array = new int[this->size];
	for (int i = 0; i < length; i++)
	{
		this->array[i] = vec.array[i];
	}
}
Vector::~Vector()
{
	delete[] this->array;
}
int& Vector::operator[](const int index)
{
	if (index > length)
	{
		throw "index out of range";
	}
	return this->array[index];
}
void Vector::Push(int elem)
{
	if (this->size < length + 1)
	{
		this->MoreMemory();
	}
	this->array[length] = elem;
	length++;
}
int Vector::Pop()
{
	if (length <= 0)
	{
		throw "Vector is empty";
	}
	int temp = array[length - 1];
	if (((size < 256 && size / 2 >length) || (size - length > 256)) && (size > 8))
	{
		LessMemory();
	}
	length--;
	return temp;
}
void Vector::Clear()
{
	delete[] array;
	array = new int[8];
	size = 8;
	length = 0;
}
void Vector::Insert(int num, int index)
{
	if (index <= length)
	{
		if (size < length + 1)
		{
			MoreMemory();
		}
		int* temp = new int[this->size];
		for (int i = 0; i < index; i++)
		{
			temp[i] = this->array[i];
		}
		temp[index] = num;
		for (int i = index + 1; i < length + 1; i++)
		{
			temp[i] = this->array[i - 1];
		}
		length++;
		delete[] this->array;
		array = temp;
	}
	else
	{
		throw "Index out of range";
	}
}
void Vector::Replace(int num, int index)
{
	if (index < length)
	{
		this->array[index] = num;
	}
	else
	{
		throw "Index out of range";
	}
}
void Vector::AddRange(int* arr, int length)
{
	int point = this->length;
	if (this->size < this->length + length)
	{
		MoreMemory(this->length + length);
	}
	this->length += length;
	for (int i = point, j = 0; i < this->length; i++, j++)
	{
		this->array[i] = arr[j];
	}
}
int Vector::Length()
{
	return this->length;
}
void Vector::PrintArr(int size, const int NUMBERS_IN_STRING)
{
	if (size > this->length)
		size = length;
	for (int i = 0; i < size; i++)
	{
		std::cout << std::setw(5) << this->array[i] << "| ";
		if ((i + 1) % NUMBERS_IN_STRING == 0)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}
void Vector::MergeSort(int start, int length)
{
	if (length > 1)
	{
		MergeSort(start, length / 2);	//идём влево
		MergeSort(start + length / 2, length - length / 2); //идём вправо
		SortPath(start, length);
	}
}
void Vector::SortPath(int start, int length)
{
	int* tempArr = new int[length];
	for (int tempIndex = 0, leftIndex = start, rightIndex = start + length / 2;
		tempIndex < length; tempIndex++)
	{
		if (array[leftIndex] <= array[rightIndex])
		{
			tempArr[tempIndex] = array[leftIndex];
			leftIndex++;
		}
		else
		{
			tempArr[tempIndex] = array[rightIndex];
			rightIndex++;
		}
		if (leftIndex >= start + length / 2)
		{
			tempIndex++;
			FillTempArr(tempArr, rightIndex, tempIndex, length);
			break;
		}
		if (rightIndex >= start + length && tempIndex < length)
		{
			tempIndex++;
			FillTempArr(tempArr, leftIndex, tempIndex, length);
			break;
		}
	}
	for (int baseIndex = start, tempIndex = 0; tempIndex < length;
		baseIndex++, tempIndex++)
	{
		array[baseIndex] = tempArr[tempIndex];
	}
	delete[] tempArr;
}
// заполняем временный масив если один из индексов достиг конца.
void Vector::FillTempArr(int tempArr[], int baseIndex, int tempIndex, int length)
{
	for (; tempIndex < length; tempIndex++)
	{
		tempArr[tempIndex] = this->array[baseIndex];
		baseIndex++;
	}
}
void Vector::AlternativeMergeSort(int start, int length)
{
	for (int curentLength = 2; curentLength < length; curentLength *= 2)
	{
		for (int i = 0; (i + 1) * curentLength - 1 < length; i++)
		{
			AlternativeSortPath(i * curentLength, i * curentLength + curentLength / 2, curentLength);
		}
		//сортируем хвост
		AlternativeSortPath(length - length % curentLength, length - length % curentLength / 2, length % curentLength);
		if (curentLength * 2 < length && length % curentLength != 0)
		{
			AlternativeSortPath(length - length % curentLength - curentLength, length - length % curentLength, curentLength + length % curentLength);
		}
		// финальная сортировка
		if (curentLength * 2 >= length)
		{
			AlternativeSortPath(start, curentLength, length);
		}
	}
}
// сортировка слиянием по индексам
void Vector::AlternativeSortPath(int leftIndex, int rightIndex, int length)
{
	if (length == 1)
		return;
	const int start = leftIndex, leftStop = rightIndex;
	int* tempArr = new int[length];
	for (int tempIndex = 0; tempIndex < length; tempIndex++)
	{
		if (array[leftIndex] <= array[rightIndex])
		{
			tempArr[tempIndex] = array[leftIndex];
			leftIndex++;
		}
		else
		{
			tempArr[tempIndex] = array[rightIndex];
			rightIndex++;
		}
		if (leftIndex >= leftStop)
		{
			tempIndex++;
			FillTempArr(tempArr, rightIndex, tempIndex, length);
			break;
		}
		if (rightIndex >= start + length && tempIndex < length)
		{
			tempIndex++;
			FillTempArr(tempArr, leftIndex, tempIndex, length);
			break;
		}
	}
	for (int baseIndex = start, tempIndex = 0; tempIndex < length;
		baseIndex++, tempIndex++)
	{
		array[baseIndex] = tempArr[tempIndex];
	}
	delete[] tempArr;
}
void Vector::BobleSort(int size)
{
	int temp = 0;
	bool isSorted = true;
	for (int i = 0; i < size; i++)
	{
		isSorted = true;
		for (int j = 0; j < size - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				isSorted = false;
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
				//std::cout << temp << "hoop!";
			}
		}
		if (isSorted)
		{
			break;
		}
	}
}
void Vector::RadixSort(int RANGE)
{
	int counter = 0, range = RANGE;
	while (range > 0)
	{
		counter++;
		range /= 10;
	}
	Vector vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7, vec8, vec9;
	Vector vectors[] = { vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7, vec8, vec9 };
	for (int i = 0; i < counter; i++)
	{
		for (int j = 0; j < length; j++)
		{
			vectors[(array[j] / (int)std::pow(10, i)) % 10].Push(array[j]);
		}
		this->Clear();
		for (int j = 0; j < 10; j++)
		{
			this->AddRange(vectors[j].array, vectors[j].Length());
			vectors[j].Clear();
		}
	}
}

void Vector::BlockSort(int rangeOfValues)
{
	int buckets = this->length / 4;
	Vector* vectors = new Vector[buckets + 1];
	int range = rangeOfValues / buckets;
	if (range == 0)
		range = 1;
	for (int i = 0; i < this->length; i++)
	{
		vectors[this->array[i] / range].Push(this->array[i]);
		//if (i%1000 == 0)
		//std::cout << " " << i<< " " << this->array[i]<< std::endl;
	}
	for (int i = 0; i < buckets + 1; i++)
	{
		vectors[i].BobleSort(vectors[i].length);
	}
	for (int i = 0, count = 0; i < buckets + 1; i++)
	{
		for (int j = 0; j < vectors[i].length; j++)
		{
			this->array[count] = vectors[i].array[j];
			count++;
		}
	}

}
void Vector::BobleSortTest(int size)
{
	int temp = 0;
	bool isSorted = true;
	for (int i = 0; i < size; i++)
	{
		isSorted = true;
		for (int j = 0; j < size - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				isSorted = false;
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
				std::cout << temp << "hoop!";
			}
		}
		if (isSorted)
		{
			break;
		}
	}
}
void BobleSortForVector(int size, std::vector <int> vect)
{
	int temp = 0;
	bool isSorted = true;
	for (int i = 0; i < size; i++)
	{
		isSorted = true;
		for (int j = 0; j < size - i - 1; j++)
		{
			if (vect[j] > vect[j + 1])
			{
				isSorted = false;
				temp = vect[j];
				vect[j] = vect[j + 1];
				vect[j + 1] = temp;
				//std::cout << temp << "hoop!";
			}
		}
		if (isSorted)
		{
			break;
		}
	}
}