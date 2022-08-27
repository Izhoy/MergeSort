#include <iostream>
#include <random>

using namespace std;

template <typename T>
ostream& operator<<(ostream&, vector<T>); // Перегрузка выходного потока

vector<int> fillRandom(vector<int>, int, int, int); // Заполнение вектора случайными числами
vector<double> fillRandom(vector<double>, int, int, int);

template <typename T>
vector<T> MergeSort(vector<T>); // Сортировка слиянием

template <typename T>
vector<T> Merge(vector<T>, vector<T>); // Слияние двух векторов

int main() {
	constexpr int MIN = 0; // MIN и MAX - диапазон случайных чисел
	constexpr int MAX = 10;
	constexpr int AMOUNT = 16; // Количество случайных чисел

	vector<int> Numbers = fillRandom(Numbers, AMOUNT, MIN, MAX); // Заполняем вектор случайными числами
	cout << Numbers << endl;

	cout << MergeSort(Numbers) << endl; // Осуществляем сортировку от меньшего к большему

	return EXIT_SUCCESS;
}

// Перегрузка выходного потока
template<typename T>
ostream& operator<<(ostream& out, vector<T> numbers)
{
	for (size_t i = 0; i < numbers.size(); ++i) {
		out << numbers.at(i) << '\t';
	}
	
	return out;
}

// Сортировка слиянием
template<typename T>
vector<T> MergeSort(vector<T> Numbers){
	if (Numbers.size() < 2) return Numbers; // Два базовых случая
	else if (Numbers.size() == 2) {
		if (Numbers.at(0) > Numbers.at(1)) swap(Numbers.at(0), Numbers.at(1));
		return Numbers;
	}
	else { // Рекурсивный случай
		vector<T> A, B;
		for (size_t i = 0; i < Numbers.size()/2; ++i) { // Разбиваем набор чисел на 2 половины
			A.push_back(Numbers.at(i));
			B.push_back(Numbers.at(i + Numbers.size() / 2));
		}
		// В случае если количество чисел нечётно 
		// добавляем во вторую половину последний элемент из исходного вектора
		if (Numbers.size() % 2 != 0) B.push_back(Numbers.back()); 
		// Рекурсивная сортировка
		A = MergeSort(A);
		B = MergeSort(B);
		// Объединение двух векторов
		Numbers = Merge(A, B);
	}
	return Numbers;
}

// Слияние двух векторов
template<typename T>
vector<T> Merge(vector<T> A, vector<T> B){
	vector<T> C;
	/*Проходим два отсортированных вектора по порядку
	и заполняем выходной вектор в отсортированном виде
	В случае, когда натыкаемся на конец одного из векторов,
	выходной вектор заполняем оставшимся вектором*/
	size_t i = 0, j = 0;
	for (size_t k = 0; k < A.size() + B.size(); ++k) {
		if (i > A.size() - 1) {
			C.push_back(B.at(j));
			++j;
		}
		else if (j > B.size() - 1) {
			C.push_back(A.at(i));
			++i;
		}
		else {
			if (A.at(i) < B.at(j)) {
				C.push_back(A.at(i));
				++i;
			}
			else {
				C.push_back(B.at(j));
				++j;
			}
		}
	}

	return C;
}

// Функция заполнения вектора целочисленными случайными числами
vector<int> fillRandom(vector<int> Numbers, int amount, int min, int max){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>dist(min, max);

	for (size_t i = 0; i < amount; ++i) {
		Numbers.push_back(dist(gen));
	}

	return Numbers;
}

// Функция заполнения вектора действительными случайными числами
vector<double> fillRandom(vector<double> Numbers, int amount, int min, int max){
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<>dist(min, max);

	for (size_t i = 0; i < amount; ++i) {
		Numbers.push_back(dist(gen));
	}

	return Numbers;
}