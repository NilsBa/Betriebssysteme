#define A3

#ifdef A0
#include <iostream>
#include <ctime>
#include <cmath> 

volatile int count = 0;

int main()
{
	// Zeit initialisieren
	clock_t start, end;

	long iterations = pow(10, 8);
	
	// Zeit starten
	start = clock();

	for (long i = iterations; i > 0; i--) {
		count++;
	}

	for (long i = iterations; i > 0; i--) {
		count++;
	}

	// Zeit stoppen
	end = clock();
	//Vergangene Zeit berechnen
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

	std::cout << "Number: " << count << "\n";
	std::cout << "Execution time: " << time_taken << " secs\n";

	return 0;
}
#endif

#ifdef A1

#include <iostream>
#include <mutex>
#include <pthread.h>
#include <ctime>
#include <cmath> 

std::mutex mutex;
volatile int count = 0;

// Kritischer Abschnitt, Indeterminismus ohne Mutexes
void* countToX(void* arg) {
	long length = (long)arg;
	for (long i = length; i > 0; i--) {
		//mutex.lock();
		count++;
		//mutex.unlock();
	}
	return NULL;
}

int main()
{
	clock_t start, end;

	long iterations = pow(10, 8);
	pthread_t thread1, thread2;

	// Threads mit Namen, Attributen(Leer), Funktion und Argument initialisieren
	pthread_create(&thread1, NULL, countToX, (void*)iterations);
	pthread_create(&thread2, NULL, countToX, (void*)iterations);

	start = clock();

	// Threads starten
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

	std::cout << "Number: " << count << "\n";
	std::cout << "Execution time: " << time_taken << " secs\n";

	return 0;
}
#endif


#ifdef A2

#include <iostream>
#include <mutex>
#include <pthread.h>
#include <atomic>
#include <ctime>

typedef struct mutex_t {
	std::atomic<int> lock;
} mutex_t;

// yielden, Anderen den Vortritt lassen
int pthread_yield(void) {
	return sched_yield();
}

// Werte atomar austauschen
int testAndSet(std::atomic<int> *ptr, int new_val) {
	return std::atomic_exchange(ptr, new_val);
}

// Mutex initiliasieren
void init_mutex(mutex_t* mutex_t) {
	mutex_t->lock = 0;
}

// Mutex anfordern
void mutex_lock(mutex_t* mtx) {
	while (testAndSet(&(mtx->lock), 1) == 1)
		pthread_yield();
}

// Mutex freigeben
void mutex_unlock(mutex_t* mtx) {
	mtx->lock = 0;
}

volatile int count = 0;
mutex_t mutex;

void* countToX(void* arg) {
	long length = (long)arg;
	for (long i = length; i > 0; i--) {
		mutex_lock(&mutex);
		count++;
		mutex_unlock(&mutex);
	}
	return NULL;
}

int main()
{
	clock_t start, end;
	
	long iterations = pow(10, 8);
	init_mutex(&mutex);
	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, countToX, (void*)iterations);
	pthread_create(&thread2, NULL, countToX, (void*)iterations);

	start = clock();

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	
	std::cout << "Number: " << count << "\n";
	std::cout << "Execution time: " << time_taken << " secs\n";

	return 0;
}
#endif


#ifdef A3

#include <iostream>
#include <pthread.h>
#include <atomic>
#include <ctime>

//atomar inkrementeller Zähler
std::atomic<int> count = 0;

void* countToX(void* arg) {
	long length = (long)arg;
	for (long i = length; i > 0; i--) {
		count++;
	}
	return NULL;
}

int main()
{
	clock_t start, end;

	long iterations = pow(10, 8);
	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, countToX, (void*)iterations);
	pthread_create(&thread2, NULL, countToX, (void*)iterations);

	start = clock();

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

	std::cout << "Number: " << count << "\n";
	std::cout << "Execution time: " << time_taken << " secs\n";

	return 0;
}
#endif
