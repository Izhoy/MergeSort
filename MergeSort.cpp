#include <iostream>
#include <random>

using namespace std;

template <typename T>
ostream& operator<<(ostream&, vector<T>); // Overload of the output stream

vector<int> fillRandom(vector<int>, int, int, int); // Filling a vector with random numbers
vector<double> fillRandom(vector<double>, int, int, int);

template <typename T>
vector<T> MergeSort(vector<T>); // Merge sorting

template <typename T>
vector<T> Merge(vector<T>, vector<T>); // merging of two vectors

int main() {
	constexpr int MIN = 0; // MIN и MAX - диапазон случайных чисел
	constexpr int MAX = 10;
	constexpr int AMOUNT = 16; // Amount of random numbers

	vector<int> Numbers = fillRandom(Numbers, AMOUNT, MIN, MAX); // Filling the vector with random numbers
	cout << Numbers << endl;

	cout << MergeSort(Numbers) << endl; // Performing merge sorting from smaller to larger

	return EXIT_SUCCESS;
}

// Overload of the output stream
template<typename T>
ostream& operator<<(ostream& out, vector<T> numbers)
{
	for (size_t i = 0; i < numbers.size(); ++i) {
		out << numbers.at(i) << '\t';
	}
	
	return out;
}

// Merge sorting
template<typename T>
vector<T> MergeSort(vector<T> Numbers){
	if (Numbers.size() < 2) return Numbers; // Base cases
	else if (Numbers.size() == 2) {
		if (Numbers.at(0) > Numbers.at(1)) swap(Numbers.at(0), Numbers.at(1));
		return Numbers;
	}
	else { // Recursion case
		vector<T> A, B;
		for (size_t i = 0; i < Numbers.size()/2; ++i) { // The set of numbers is dividing into 2 halves
			A.push_back(Numbers.at(i));
			B.push_back(Numbers.at(i + Numbers.size() / 2));
		}
		// If the number of numbers is odd
		// we add the last element from the original vector to the second half
		if (Numbers.size() % 2 != 0) B.push_back(Numbers.back()); 
		// Recursion sorting
		A = MergeSort(A);
		B = MergeSort(B);
		// Merging of 2 vectors
		Numbers = Merge(A, B);
	}
	return Numbers;
}

// Merging of 2 vectors
template<typename T>
vector<T> Merge(vector<T> A, vector<T> B){
	vector<T> C;
	/*We pass two sorted vectors in order
	and fill in the output vector in sorted form
	In the case when we come across the end of one of the vectors,
	we fill the output vector with the remaining vector*/
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

// The function of filling the vector with integer random numbers
vector<int> fillRandom(vector<int> Numbers, int amount, int min, int max){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>dist(min, max);

	for (size_t i = 0; i < amount; ++i) {
		Numbers.push_back(dist(gen));
	}

	return Numbers;
}

// The function of filling the vector with real random numbers
vector<double> fillRandom(vector<double> Numbers, int amount, int min, int max){
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<>dist(min, max);

	for (size_t i = 0; i < amount; ++i) {
		Numbers.push_back(dist(gen));
	}

	return Numbers;
}
