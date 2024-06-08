#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Array_Sort.h" // не забыть подключить
using namespace std;

bool Sentinel_Linear_Search(vector<key>arr, key& answer, int search_key, int& steps, int n) {
    if (arr.empty()) {
        return false;
    }
    int temp = arr[n - 1].app.number_app;
    arr[n - 1].app.number_app = search_key;

    int i = 0;
    if (arr[i].app.number_app == search_key) {
        steps++;
        answer = arr[i];
        return true;
    }
    while (arr[i].app.number_app != search_key) {
        i++;
        steps++;
    }

    arr[n - 1].app.number_app = temp;
    if ((i < n - 1) || (arr[i].app.number_app == search_key)) {
        steps++;
        answer = arr[i];
        return true;
    }
    else {
        return false;
    }
}

int for_pow(int num, int exp) {
    int res = 1;
    for (int i = 0; i < exp; i++) {
        res *= num;
    }
    return res;
}

void steps_table(vector<int>& arr, int n) {
    int j = 1;
    while (((n + for_pow(2, j - 1)) / for_pow(2, j)) > 0) {
        arr.push_back((n + for_pow(2, j - 1)) / (for_pow(2, j)));
        j++;
    }
}

bool Homogeneous_Binary_Search(vector<key>& arr, key& answer, int search_key, int& steps, int n) {
    int m = n / 2;
    vector<int> b_step;
    steps_table(b_step, m);
    int j = 0;
    while (!b_step.empty()) {
        steps++;

        if ((m >= 0) && (m < n) && (arr[m].app.number_app == search_key)) {
            answer = arr[m];
            return true;
        }
        else if ((m >= 0) && (m < n) && (arr[m].app.number_app < search_key)) {
            m += b_step[j];
        }
        else {
            m -= b_step[j];
        }
        if (j < b_step.size() - 1) {
            j++;
        }
        else {
            b_step.pop_back();
            j = 0;
        }
    }
    return false;
}