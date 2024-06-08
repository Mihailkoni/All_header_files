#pragma once
#include <iostream>
#include <vector> 
#include <string> 
using namespace std;

void bubble_Sort(vector<key>& arr, long& n) {
    bool swapped;
    key temp;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].app.number_app > arr[j + 1].app.number_app) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (swapped == false) {
            break; // If there was no exchange, then the array has already been sorted
        }
    }
}

int increment(long inc[], long& size) { // for Shell Sort
    int p1, p2, p3, s;

    p1 = p2 = p3 = 1;
    s = -1;
    do {
        if (++s % 2) {
            inc[s] = 8 * p1 - 6 * p2 + 1;
        }
        else {
            inc[s] = 9 * p1 - 9 * p3 + 1;
            p2 *= 2;
            p3 *= 2;
        }
        p1 *= 2;
    } while (3 * inc[s] < size);

    return s > 0 ? --s : 0;
}

void shell_Sort(vector<key>& arr, long& size) {
    long inc, i, j, seq[40];
    int s;
    key temp;
    s = increment(seq, size);
    while (s >= 0) {
        inc = seq[s--];
        for (i = inc; i < size; i++) {
            temp = arr[i];
            for (j = i - inc; (j >= 0) && (arr[j].app.number_app > temp.app.number_app); j -= inc)
                arr[j + inc] = arr[j];
            arr[j + inc] = temp;
        }
    }
}