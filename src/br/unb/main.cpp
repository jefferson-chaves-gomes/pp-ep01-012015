/*
 ============================================================================
 Name        : main.cpp
 Author      : Jefferson Chaves Gomes
 Version     : 1.0.0
 Copyright   : Academic Program
 Description : EP 01 in C++
 ============================================================================
 */

#include <stdlib.h>
#include <iostream>
#include <omp.h>

/**
 * Hello OpenMP World prints the number of threads and the current thread id
 */

bool isPrime(int num) {
	for (int i = 2; i < num; ++i) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}


int main(void) {

	int num = 2;
	std::cout << "Informe um número natural maior que 1: ";
	std::cin >> num;

	int primesSize = 0;
	int primesArray[num];
	for (int i = 2; i < num; i++) {
		if (isPrime(i)) {
			primesArray[primesSize++] = i;
		}
	}

	for (int i = 0; i < primesSize; i++) {
		std::cout << primesArray[i] << " - ";
	}

	return EXIT_SUCCESS;
}

