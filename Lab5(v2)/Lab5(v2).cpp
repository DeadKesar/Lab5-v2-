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
	std::cout << "Лабораторная работа №5. \nПо теме: \"Разработка ПО в стиле ООП. Работа с файлами и потоками ввода/вывода.\"\n" <<
		"Вариант №13 \nВыполнил: Порядин В.С." << std::endl;
	std::mt19937 engine;
	engine.seed(time(nullptr));

	int const SIZE = 100000000;//количество сортируемых чисел
	int const RANGE = 1000000; // диапазон значений
	std::vector<int> vecSTD;
	Vector* myVector = new Vector();
	clock_t timer = clock();
	for (size_t i = 0; i < SIZE; i++)
	{
		vecSTD.push_back(engine() % RANGE);
	}
	clock_t curent = clock();

	clock_t timer2 = clock();
	FillArray(myVector, SIZE, RANGE, engine);
	clock_t curent2 = clock();
	double stdVectorTime = static_cast<double>(curent - timer) / CLOCKS_PER_SEC;
	double myVectorTime = static_cast<double>(curent2 - timer2) / CLOCKS_PER_SEC;
	std::cout << stdVectorTime << " - время генерации стандартного вектора" << std::endl;
	std::cout << myVectorTime << " - время генерации самодельного вектора" << std::endl;
	vecSTD.clear();

	if (stdVectorTime > myVectorTime)
	{
		std::cout << "при заполнении структуры Вектора, моя ревлизация по какой то причине оказалась быстрее на " <<stdVectorTime - myVectorTime<< " c." << std::endl;
	}
	else
	{
		std::cout << "при заполнении структуры Вектора, стандартная реализация оказалась быстрее на " << myVectorTime - stdVectorTime << " c." << std::endl;
	}


	timer = clock();
	myVector->MergeSort(0, myVector->Length());
	curent = clock();
	double mergeTime = static_cast<double>(curent - timer) / CLOCKS_PER_SEC;
	std::cout << mergeTime << " - время cортировки слиянием" << std::endl;
	myVector->Clear();

	FillArray(myVector, SIZE, RANGE, engine);
	timer = clock();
	myVector->AlternativeMergeSort(0, myVector->Length());
	curent = clock();
	double altMergeTime = static_cast<double>(curent - timer) / CLOCKS_PER_SEC;
	std::cout << altMergeTime << " - время альтернативной сортировки слиянием (без слияния)" << std::endl;
	myVector->Clear();


	FillArray(myVector, SIZE, RANGE, engine);
	timer = clock();
	myVector->RadixSort(RANGE);
	curent = clock();
	double radixTime = static_cast<double>(curent - timer) / CLOCKS_PER_SEC;
	std::cout << radixTime << " - время поразрядной сортировки" << std::endl;
	myVector->Clear();

	int range = RANGE;
	if (RANGE >= 2100000000)
		range = 2100000000;
	FillArray(myVector, SIZE, range, engine);
	timer = clock();
	myVector->BlockSort(range);
	curent = clock();
	double blockTime = static_cast<double>(curent - timer) / CLOCKS_PER_SEC;
	std::cout << blockTime << " - время блочной сортировки" << std::endl;
	myVector->Clear();


	FillArray(myVector, SIZE, RANGE, engine);
	timer = clock();
	myVector->BlockSortUseSTD(RANGE);
	curent = clock();
	double stdBlockTime = static_cast<double>(curent - timer) / CLOCKS_PER_SEC;
	std::cout << stdBlockTime << " - время блочной сортировки на STD::vector" << std::endl;
	myVector->BobleSortTest(myVector->Length());
	myVector->Clear();

	int faster = 0;
	double sortsTime[] = { mergeTime ,altMergeTime,radixTime,blockTime,stdBlockTime };
	for (int i = 1; i < 5; i++)
	{
		if (sortsTime[i] < sortsTime[i - 1])
			faster = i;
	}
	switch (faster)
	{
	case (0):
		std::cout <<  "самая быстрая сортировка при заданной конфигурации - слиянием" << std::endl;
		break;
	case (1):
		std::cout <<  "самая быстрая сортировка при заданной конфигурации - слиянием(Альтернативная)" << std::endl;
		break;
	case (2):
		std::cout <<  "самая быстрая сортировка при заданной конфигурации - поразрядная" << std::endl;
		break;
	case (3):
		std::cout <<  "самая быстрая сортировка при заданной конфигурации - блочная сортировка" << std::endl;
		break;
	case (4):
		std::cout <<  "самая быстрая сортировка при заданной конфигурации - блочная сортировка на STD::vector" << std::endl;
		break;
	default:
		break;
	}




	//FillArray(myVector, SIZE, RANGE, engine);
	//timer = clock();
	//myVector->BobleSort(myVector->Length());
	//curent = clock();
	//std::cout << static_cast<double>(curent - timer) / CLOCKS_PER_SEC << "время сортировки пузырьком" << std::endl;



	//myVector->BobleSortTest(myVector->Length());

}

void FillArray(Vector* vec, const int SIZE, const int RANGE, std::mt19937 engine)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		vec->Push(engine() % RANGE);
	}
}