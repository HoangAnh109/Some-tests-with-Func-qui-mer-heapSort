#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <fstream>

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
            auto SortFunctionVec = vec;

            auto start = chrono::high_resolution_clock::now();

            heapSort(heapSortVec);   
                  
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            out_put << duration.count() << "     ";

            start = chrono::high_resolution_clock::now();
            mergeSort(mergeSortVec, 0, n - 1);
            end = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::microseconds>(end - start);
            out_put  << duration.count() <<"     ";

            start = chrono::high_resolution_clock::now();
            quickSort(quickSortVec, 0, n - 1);
            end = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::microseconds>(end - start);
            out_put  << duration.count() <<"     ";

            start = chrono::high_resolution_clock::now();
            sort(SortFunctionVec.begin(), SortFunctionVec.end());
            end = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::microseconds>(end - start);
            out_put << duration.count() << endl;

            file.close();
        } 
        else {
            cerr << "Failed to open file: " << fileName << endl;
        }
    }

    out_put.close();
    return 0;
}
