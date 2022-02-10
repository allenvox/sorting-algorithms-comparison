#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#define MAXIMUM 100000 // максимальное число в массиве

void swap(int *a, int *b) { // перемена мест
    int t;
    t = *b;
    *b = *a;
    *a = t;
}

double wtime() { // время
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void insertionSort(int *array, int n) { // сортировка вставками
    for (int i = 1; i < n; i++) // i = 1, т.к. первый элемент считается
    {                           // уже отсортированной последовательностью
        for (int j = i; j>0 && array[j-1] > array[j]; j--) { // пока j>0 и (j-1)>j,
            swap( &array[j-1], &array[j] );                    // элементы j-1 и j меняются местами
        }
    }
}

void countingSort(int *array, int n, int *counters, int max){ // сортировка подсчётом
    for (int i=0; i<n; i++) {
        counters[array[i]]++;
    }
    int element = 0;
    for (int i = 0; i <= max; i++){
        int count = counters[i];
        for (int j = 0; j < count; j++){
            array[element] = i;
            element++;
        }
    }
}

void quickSort(int *array, int n) { // быстрая сортировка
    int left = 0; // точка в начале массива
    int right = n-1; // точка в конце массива
    int middle = array[n/2]; // точка в центре массива

    do {
        // поиск элементов для переноса в другую часть массива
        while(array[left] < middle) {
            left++; // пропуск элементов, которые меньше центрального
        }

        while(array[right] > middle) {
            right--; // пропуск элементов, которые больше центрального
        }

        if (left <= right) { // если нашли, меняем местами
            swap(&array[left], &array[right]);
            left++;
            right--;
        }

    } while (left <= right);

    //рекурсивные вызовы для оставшихся элементов
    if(right > 0) {                  // левая часть массива
        quickSort(array, right + 1); // (если существует - запускаем сортировку)
    }

    if(left < n) {                         // правая часть массива
        quickSort(&array[left], n - left); // (если существует - запускаем)
    }
}

int getMax(int *array, int n) { // нахождение максимального элемента массива
    int max = 0;
    for (int i=0; i<n; i++){
        if(array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

int getRand(int min, int max) { // получение псевдослучайного числа в заданном диапазоне
    return (double)rand() / (RAND_MAX + 1.0)*(max+1 - min) + min;
}

void fillArray(int *array, int n) { // заполнение массива
    for (int i = 0; i < n; i++) {
        array[i] = getRand(0, MAXIMUM);
    }
}

void printArray(int *array, int n) { // вывод содержимого массива
    printf("\n{");

    for (int i = 0; i < n; i++) {
        printf(" %d ", array[i]);
    }

    printf("}\n");
}

int main(){
    for (int i = 0; i < 3; i++) {
        char *method = malloc(20);
        for(int N = 50000; N <= 1000000; N += 50000) { // цикл по размерам массива от 50 тыс. до 1 млн. элементов
            int *a = (int*)malloc(N*sizeof(int));
            fillArray(a, N);
            
            int max = getMax(a, N);
            int *counters = (int*)malloc(max*sizeof(int));

            double startTime = wtime();
            switch (i) {
            case 0:
                strcpy(method, "counting");
                countingSort(a, N, counters, max);
                break;
            case 1:
                strcpy(method, "insertion");
                insertionSort(a, N);
                break;
            case 2:
                strcpy(method, "quicksort");
                quickSort(a, N);
                break;
            }
            double endTime = wtime();
            double elapsedTime = endTime - startTime;
            printf("%d elements - %f seconds elapsed\n", N, elapsedTime);
        }
        printf("Method: %s ^\n\n", method);
    }

    return 0;
}