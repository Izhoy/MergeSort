#include <iostream>
#include <random>

using namespace std;

template <typename T>
ostream& operator<<(ostream&, vector<T>); // ���������� ��������� ������

vector<int> fillRandom(vector<int>, int, int, int); // ���������� ������� ���������� �������
vector<double> fillRandom(vector<double>, int, int, int);

template <typename T>
vector<T> MergeSort(vector<T>); // ���������� ��������

template <typename T>
vector<T> Merge(vector<T>, vector<T>); // ������� ���� ��������

int main() {
	constexpr int MIN = 0; // MIN � MAX - �������� ��������� �����
	constexpr int MAX = 10;
	constexpr int AMOUNT = 16; // ���������� ��������� �����

	vector<int> Numbers = fillRandom(Numbers, AMOUNT, MIN, MAX); // ��������� ������ ���������� �������
	cout << Numbers << endl;

	cout << MergeSort(Numbers) << endl; // ������������ ���������� �� �������� � ��������

	return EXIT_SUCCESS;
}

// ���������� ��������� ������
template<typename T>
ostream& operator<<(ostream& out, vector<T> numbers)
{
	for (size_t i = 0; i < numbers.size(); ++i) {
		out << numbers.at(i) << '\t';
	}
	
	return out;
}

// ���������� ��������
template<typename T>
vector<T> MergeSort(vector<T> Numbers){
	if (Numbers.size() < 2) return Numbers; // ��� ������� ������
	else if (Numbers.size() == 2) {
		if (Numbers.at(0) > Numbers.at(1)) swap(Numbers.at(0), Numbers.at(1));
		return Numbers;
	}
	else { // ����������� ������
		vector<T> A, B;
		for (size_t i = 0; i < Numbers.size()/2; ++i) { // ��������� ����� ����� �� 2 ��������
			A.push_back(Numbers.at(i));
			B.push_back(Numbers.at(i + Numbers.size() / 2));
		}
		// � ������ ���� ���������� ����� ������� 
		// ��������� �� ������ �������� ��������� ������� �� ��������� �������
		if (Numbers.size() % 2 != 0) B.push_back(Numbers.back()); 
		// ����������� ����������
		A = MergeSort(A);
		B = MergeSort(B);
		// ����������� ���� ��������
		Numbers = Merge(A, B);
	}
	return Numbers;
}

// ������� ���� ��������
template<typename T>
vector<T> Merge(vector<T> A, vector<T> B){
	vector<T> C;
	/*�������� ��� ��������������� ������� �� �������
	� ��������� �������� ������ � ��������������� ����
	� ������, ����� ���������� �� ����� ������ �� ��������,
	�������� ������ ��������� ���������� ��������*/
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

// ������� ���������� ������� �������������� ���������� �������
vector<int> fillRandom(vector<int> Numbers, int amount, int min, int max){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>dist(min, max);

	for (size_t i = 0; i < amount; ++i) {
		Numbers.push_back(dist(gen));
	}

	return Numbers;
}

// ������� ���������� ������� ��������������� ���������� �������
vector<double> fillRandom(vector<double> Numbers, int amount, int min, int max){
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<>dist(min, max);

	for (size_t i = 0; i < amount; ++i) {
		Numbers.push_back(dist(gen));
	}

	return Numbers;
}