#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <fstream>
#include <functional>
#include <iomanip>
using namespace std;

// function to sort vector using heap sort
void heapify(vector<double>& vec, int i, int n) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && vec[l] > vec[largest])
        largest = l;

    if (r < n && vec[r] > vec[largest])
        largest = r;

    if (largest != i) {
        swap(vec[i], vec[largest]);

        heapify(vec, largest, n);
    }
}

void heapSort(vector<double>& vec) {
    int n = vec.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(vec, i, n);

    for (int i = n - 1; i > 0; i--) {
        swap(vec[0], vec[i]);

        heapify(vec, 0, i);
    }
}

// function to sort vector using merge sort
void mergeSort(vector<double>& vec, int left, int right) {
    if(left < right) {
        int mid = (left + right) / 2;

        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);

        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<double> LHS(n1), RHS(n2);

        for (int i = 0; i < n1; i++)
            LHS[i] = vec[left + i];
        for (int i = 0; i < n2; i++)
            RHS[i] = vec[mid + 1 + i];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if(LHS[i] <= RHS[j])
                vec[k++] = LHS[i++];
            else
                vec[k++] = RHS[j++];
        }
        while (i < n1)
            vec[k++] = LHS[i++];
        while (j < n2)
            vec[k++] = RHS[j++];
    }
}

// function to sort vector using quick sort
void quickSort(vector<double>& vec, int left, int right) {
    int i = left, j = right;
    double pivot = vec[(left + right) / 2];

    while (i <= j) {
        while (vec[i] < pivot)
            i++;
        while (vec[j] > pivot)
            j--;
        if(i <= j) {
            swap(vec[i], vec[j]);
            i++;
            j--;
        }
    }

    if (left < j)
        quickSort(vec, left, j);
    if (i < right)
        quickSort(vec, i, right);
}

// function to check if vector is sorted
bool isSorted(vector<double> sorted, vector<double> check){
    if (sorted == check) return true;
    else return false;
}

// function to measure excution time of sort
double measure_execution_time(std::function<void()> code_block) {
    auto start_time = std::chrono::high_resolution_clock::now();
    code_block();
    auto end_time = std::chrono::high_resolution_clock::now();
    double execution_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    
    return execution_time;
}

int main() {
    ofstream out_put("out_put.txt");

    vector<string> fileNames = {"Nums_Test01.txt", "Nums_Test02.txt",
                                "Nums_Test03.txt", "Nums_Test04.txt",
                                "Nums_Test05.txt", "Nums_Test06.txt",
                                "Nums_Test07.txt", "Nums_Test08.txt",
                                "Nums_Test09.txt", "Nums_Test10.txt"};
    
    for (const auto& fileName : fileNames) {
        ifstream file(fileName);
        if (file.is_open()) {
            vector<double> vec;
            double num;

            while(file >> num) {
                vec.push_back(num);
            }

            int n = vec.size();

            auto heapSortVec = vec;
            auto mergeSortVec = vec;
            auto quickSortVec = vec;
            
            // Recording the time std::sort() sort vector
            double time = measure_execution_time([&vec]{
                sort(vec.begin(), vec.end());
            }) ;
            out_put << time <<"\t\t";
            
            // Recording the time heapsort sort vector
            time = measure_execution_time([&heapSortVec]{
                heapSort(heapSortVec);
            }) ;
            if (isSorted(vec, heapSortVec) &&  (int)time != 0)
                out_put << (int)time <<"\t\t";
            else {
                // check if vector isn't sorted
                cout << "Heapsort : " <<fileName << " isn't sorted\n";
                out_put << "error" <<"\t\t";
            }

            // Recording the time mergesort sort vector
            time = measure_execution_time([&mergeSortVec, n]{
                mergeSort(mergeSortVec, 0, n - 1);
            }) ;
            if (isSorted(vec, mergeSortVec) && (int)time != 0)
                out_put << (int)time <<"\t\t";
            else {
                // check if vector isn't sorted
                cout << "Mergesort : " << fileName << " isn't sorted\n";
                out_put << "error" <<"\t\t";
            }

            // Recording the time quicksort sort vector
            time = measure_execution_time([&quickSortVec, n]{
                quickSort(quickSortVec, 0, n - 1);
            }) ;
            if (isSorted(vec, quickSortVec) && (int)time != 0)
                out_put<< time <<"\n";
            else {
                // check if vector isn't sorted
                cout << "Quicksort : " <<fileName << " isn't sorted\n";
                out_put << "error" <<"\n";
            }

            file.close();
        } 
        else {
            cerr << "Failed to open file: " << fileName << endl;
        }
    }

    out_put.close();
    return 0;
}
