//Усовершенствовать(или разработать) класс «динамический массив целых чисел».Реализовать функции сортировки такого массива.Взять не менее 3 различных алгоритмов.
//Сравнить их производительность на основе массива, содержащего не менее 100 миллионов чисел.
//Усложнение(+3 балла).Сравнить производительность добавления целых чисел в std::vector и в ваш.


#include "Vector.h"
#include <iostream>
#include <vector>

void FillArray(Vector* vec, const int SIZE, const int RANGE, std::mt19937 engine);

int main()
{
	setlocale(LC_ALL, "Russian");
	std::mt19937 engine;
	engine.seed(time(nullptr));

	int const START = 0; // начальный индекс сортировки
	int const SIZE = 100000000;//количество сортируемых чисел
	int const RANGE = INT_MAX; // диапазон значений INT_MAX
	std::vector<int> vecSTD;
	Vector* myVector = new Vector();
	//2147483647
	clock_t timer = clock();
	//for (size_t i = 0; i < SIZE; i++)
	//{
	//	vecSTD.push_back(engine() % RANGE);
	//}
	clock_t curent = clock();

	//clock_t timer2 = clock();
	//FillArray(myVector, SIZE, RANGE, engine);
	//clock_t curent2 = clock();

	//std::cout << static_cast<double>(curent - timer) / CLOCKS_PER_SEC << " - время генерации стандартного вектора" << std::endl;
	//std::cout << static_cast<double>(curent2 - timer2) / CLOCKS_PER_SEC << " - время генерации самодельного вектора" << std::endl;
	//vecSTD.clear();

	//timer = clock();
	//myVector->MergeSort(0, myVector->Length());
	//curent = clock();
	//std::cout << static_cast<double>(curent - timer) / CLOCKS_PER_SEC << " - время cортировки слиянием" << std::endl;
	//myVector->Clear();

	//FillArray(myVector, SIZE, RANGE, engine);
	//timer = clock();
	//myVector->AlternativeMergeSort(0, myVector->Length());
	//curent = clock();
	//std::cout << static_cast<double>(curent - timer) / CLOCKS_PER_SEC << " - время альтернативной сортировки слиянием (без слияния)" << std::endl;
	//myVector->Clear();


	//FillArray(myVector, SIZE, RANGE, engine);
	//timer = clock();
	//myVector->RadixSort(RANGE);
	//curent = clock();
	//std::cout << static_cast<double>(curent - timer) / CLOCKS_PER_SEC << " - время поразрядной сортировки" << std::endl;
	//myVector->Clear();

	int range = RANGE;
	if (RANGE >= 2000000000)
		range = 2100000000;


	FillArray(myVector, SIZE, range, engine);
	timer = clock();
	myVector->BlockSort(range);
	curent = clock();
	std::cout << static_cast<double>(curent - timer) / CLOCKS_PER_SEC << " - время блочной сортировки" << std::endl;
	//myVector->Clear();


	//FillArray(myVector, SIZE, RANGE, engine);
	timer = clock();
	myVector->BobleSort(myVector->Length());
	curent = clock();
	std::cout << static_cast<double>(curent - timer) / CLOCKS_PER_SEC << "время сортировки пузырьком" << std::endl;




}

void FillArray(Vector* vec, const int SIZE, const int RANGE, std::mt19937 engine)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		vec->Push(engine() % RANGE);
	}
}