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
#include <chrono>
#include <math.h>
#include <time.h>
#include <omp.h>
#include <boost/format.hpp>

// Definitions
// -----------------------------------------------------
#define MIN_RANGE 1
#define MAX_RANGE 1000000000
#define MAX_THREADS 10

// Enums definitions
// -----------------------------------------------------
enum OutputType {
	NONE = 0,
    TIME = 1,
    LIST = 2,
    ALL  = 3
};

// Structs definitions
// -----------------------------------------------------
struct Result {
    std::chrono::duration<double> processTime;
    std::set<int> lstPrimes;
};

// Functions declarations
// -----------------------------------------------------
int readUpperLimit();
OutputType readOutputType();
Result findPrimesSequential(int);
Result findPrimesParallel(int, int);
bool isPrime(int num);
void printResult(OutputType, Result);
void printTimeOutputType(Result);
void printListOutputType(Result);

// main Function
// -----------------------------------------------------
int main(int argc, char *argv[]) {
//	int upperLimit = readUpperLimit();
//	OutputType outputType = readOutputType();

	int upperLimit = 1000;


	// Check Sequential
	Result result = findPrimesSequential(upperLimit);
//	printResult(outputType, result);
	std::cout << std::endl << std::flush;
	std::cout << std::endl << std::flush;

	double timeSeq = result.processTime.count();

	// STATIC
            std::cout << "--- STATIC ---" << std::endl;
    for (int i = 80; i >= 20; i -= 60) {
        int chunkSize = upperLimit * (i / 100.0);
        omp_set_schedule(omp_sched_static, chunkSize);
        for (int j = 1; j <= MAX_THREADS; ++j) {
            result = findPrimesParallel(upperLimit, j);
//            printResult(outputType, result);

            double timePar = result.processTime.count();
            double speedup = timeSeq / timePar;
            std::cout << "[Threads:" << j << "];"
            			 "[ChunkSize:" << chunkSize << "];"
            			 "[Scheduler:" << "static" << "];"
            			 "[tserial:" << (boost::format("%7.6f") % (timeSeq)).str() << "];"
            			 "[Time:" << (boost::format("%7.6f") % (timePar)).str() << "];"
            			 "[Speedup:" << (boost::format("%7.6f") % (speedup)).str() << "];"
						 "[Eficiency:" << (boost::format("%7.6f") % (speedup / j)).str() << "]" << std::endl;
        }
    }
    std::cout << std::endl << std::flush;
    std::cout << std::endl << std::flush;

    // DYNAMIC
            std::cout << "--- DYNAMIC ---" << std::endl;
    for (int i = 80; i >= 20; i -= 60) {
            int chunkSize = upperLimit * (i / 100.0);
        omp_set_schedule(omp_sched_dynamic, chunkSize);
        for (int j = 1; j <= MAX_THREADS; ++j) {
            result = findPrimesParallel(upperLimit, j);
//            printResult(outputType, result);

            double timePar = result.processTime.count();
            double speedup = timeSeq / timePar;
            std::cout << "[Threads:" << j << "];"
            			 "[ChunkSize:" << chunkSize << "];"
            			 "[Scheduler:" << "static" << "];"
            			 "[tserial:" << (boost::format("%7.6f") % (timeSeq)).str() << "];"
            			 "[Time:" << (boost::format("%7.6f") % (timePar)).str() << "];"
            			 "[Speedup:" << (boost::format("%7.6f") % (speedup)).str() << "];"
						 "[Eficiency:" << (boost::format("%7.6f") % (speedup / j)).str() << "]" << std::endl;
        }
    }
    std::cout << std::endl << std::flush;
    std::cout << std::endl << std::flush;

    // GUIDED
            std::cout << "--- GUIDED ---" << std::endl;
    for (int i = 80; i >= 20; i -= 60) {
        int chunkSize = upperLimit * (i / 100.0);
        omp_set_schedule(omp_sched_guided, chunkSize);
        for (int j = 1; j <= MAX_THREADS; ++j) {
            result = findPrimesParallel(upperLimit, j);
//            printResult(outputType, result);


            double timePar = result.processTime.count();
            double speedup = timeSeq / timePar;
            std::cout << "[Threads:" << j << "];"
            			 "[ChunkSize:" << chunkSize << "];"
            			 "[Scheduler:" << "static" << "];"
            			 "[tserial:" << (boost::format("%7.6f") % (timeSeq)).str() << "];"
            			 "[Time:" << (boost::format("%7.6f") % (timePar)).str() << "];"
            			 "[Speedup:" << (boost::format("%7.6f") % (speedup)).str() << "];"
						 "[Eficiency:" << (boost::format("%7.6f") % (speedup / j)).str() << "]" << std::endl;
        }
    }
    std::cout << std::endl << std::flush;
	return EXIT_SUCCESS;
}

// Function implementations
// -----------------------------------------------------
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
	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
	startTime = std::chrono::system_clock::now();
    for (int i = 2; i < upperLimit; i++) {
        if (isPrime(i)) {
            result.lstPrimes.insert(i);
        }
    }
	endTime = std::chrono::system_clock::now();
	result.processTime = endTime - startTime;
	return result;
}

bool isPrime(int num) {
	int srqtNum = floor(sqrt(num));
	for (int i = 2; i <= srqtNum; ++i) {
		if (num % i == 0) {
		    return false;
		}
	}
	return true;
}

Result findPrimesParallel(int upperLimit, int numThreads) {
    Result result;
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    startTime = std::chrono::system_clock::now();
    #pragma omp parallel for num_threads(numThreads) scheduler(runtime) shared(upperLimit, result)
        for (int i = 2; i < upperLimit; i++) {
            if (isPrime(i)) {
                # pragma omp critical {
                    result.lstPrimes.insert(i);
                }
            }
    endTime = std::chrono::system_clock::now();
    result.processTime = endTime - startTime;
    return result;
}

void printResult(OutputType outputType, Result result) {
    std::cout << std::endl;
	switch (outputType) {
		case TIME:
		    printTimeOutputType(result);
			break;
		case LIST:
		    printListOutputType(result);
			break;
		case ALL:
		    printTimeOutputType(result);
		    std::cout << std::endl;
		    printListOutputType(result);
			break;
		default:
			break;
	}
}

void printTimeOutputType(Result result) {
    std::cout <<  (boost::format("%7.6f") % (result.processTime.count())).str() << std::flush;
}

void printListOutputType(Result result) {
    for (std::set<int>::iterator element = result.lstPrimes.begin(); element != result.lstPrimes.end(); element++) {
        std::cout << *element << " " << std::flush;
    }
}
