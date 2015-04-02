/*
 ============================================================================
 Name        : main.cpp
 Author      : Jefferson Chaves Gomes
 Version     : 1.0.0
 Copyright   : Academic Program
 Description : EP 01 in C++
 ============================================================================
 */

#include <iostream>
#include <set>
#include <iterator>
#include <time.h>
#include <omp.h>

// Definitions
#define MIN_RANGE 1
#define MAX_RANGE 1000000000

// Enums definitions
enum OutputType {
	NONE = 0,
    TIME = 1,
    LIST = 2,
    ALL = 3
};

// Strutcs definitions
struct Result {
    long processTime;
    std::set<int> lstPrimes;
};

// Functions declarations
int readUpperLimit();
OutputType readOutputType();
Result findPrimesSequential(int);
bool isPrime(int num);
void printResult(OutputType, Result);

// Global variables
int processTime = -1;

int main(int argc, char *argv[]) {
	int upperLimit = readUpperLimit();
	OutputType outputType = readOutputType();
	Result result = findPrimesSequential(upperLimit);
	printResult(outputType, result);



//
//	for (int i = 2; i < num; i++) {
//		if (isPrime(i)) {
//			primesArray[primesSize++] = i;
//		}
//	}
//	for (int i = 0; i < primesSize; i++) {
//		std::cout << primesArray[i] << " - ";
//	}

	return EXIT_SUCCESS;
}

int readUpperLimit() {
	int num = 0;
	std::cout << std::endl << "Informe um limite superior da lista de primos a ser impressa: " << std::flush;
	std::cin >> num;
	while (!(std::cin.good()) && !(num > MIN_RANGE && num <= MAX_RANGE)) {
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "Por favor. Informe um numero natural maior que " << MIN_RANGE << " e menor ou igual a " << MAX_RANGE << ": " << std::flush;
		std::cin >> num;
	}
	return num;
}

OutputType readOutputType() {
	std::cout << std::endl << "Informe o tipo de saida a ser impressa: " << std::endl << std::flush;
	std::cout << "Digite: time (para imprimir somente o tempo de processamento)" << std::endl << std::flush;
	std::cout << "Digite: list (para imprimir somente a lista de numeros primos)" << std::endl << std::flush;
	std::cout << "Digite: all  (para imprimir o tempo e a lista citados acima)" << std::endl << std::flush;
	OutputType outputType = NONE;
	std::string input = "";
	while(true) {
		std::cin >> input;
		if (input == "time") {
			outputType = TIME;
		} else if (input == "list") {
			outputType = LIST;
		} else if (input == "all") {
			outputType = ALL;
		}
		if (outputType != NONE) {
			break;
		}
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "Valor incorreto! Informe novamente:" << std::endl << std::flush;
	}
	return outputType;
}

Result findPrimesSequential(int upperLimit) {
	Result result;
	clock_t startTime = clock();
	for (int i = 2; i < upperLimit; i++) {
		if (isPrime(i)) {
			result.lstPrimes.insert(i);
		}
	}
	clock_t endTime = clock();
	result.processTime = (endTime - startTime) / CLOCKS_PER_SEC;
	return result;
}

bool isPrime(int num) {
	for (int i = 2; i < num; ++i) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

void printResult(OutputType outputType, Result result) {
	switch (outputType) {
		case TIME:

			break;
		case LIST:
			for (std::set<int>::iterator element = result.lstPrimes.begin(); element != result.lstPrimes.end(); element++) {
				std::cout << *element << " ";
			}
			break;
		case ALL:

			break;
		default:
			break;
	}
}
