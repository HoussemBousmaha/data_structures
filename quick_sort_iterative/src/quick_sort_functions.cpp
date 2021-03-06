#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#include <bits\stdc++.h>
#include "../lib/quick_sort_functions.hpp"

using namespace std;

pair<pair<int, int>, pair<int, int>> partition(vector<int> &array, int l, int r)
{
    bool j_turn = true;
    int i = l, j = r;

    while (i < j)
    {
        while (array[i] < array[j])
        {
            if (j_turn)
                j--;
            else
                i++;
        }

        // exchange
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;

        // flip the turns
        j_turn = !j_turn;
    }

    pair<pair<int, int>, pair<int, int>> boundries;

    if (j_turn)
    {
        // boundries of first part of array
        boundries.first.first = l;
        boundries.first.second = j - 1;
        // boundries of second part of the array
        boundries.second.first = j + 1;
        boundries.second.second = r;
    }
    else
    {
        // boundries of first part of array
        boundries.first.first = l;
        boundries.first.second = i - 1;
        // boundries of second part of the array
        boundries.second.first = i + 1;
        boundries.second.second = r;
    }

    return boundries;
}


// iterative verstion of quick_sort (hard)

void qs(vector<int> &arr)
{
    stack<pair<int, int>> stack;

    pair<int, int> initial;

    initial.first = 0;
    initial.second = arr.size() - 1;
    stack.push(initial);

    int l, r;

    pair<pair<int, int>, pair<int, int>> boundries;

    do
    {
        l = stack.top().first;
        r = stack.top().second;
        stack.pop();
        // cout << l << r << endl;

        while (r > l) // step4
        {
            // step2
            boundries = partition(arr, l, r);

            // step3
            if (boundries.first.second - boundries.first.first > boundries.second.second - boundries.second.first)
            {
                stack.push(boundries.first);
                l = boundries.second.first;
                r = boundries.second.second;
            }
            else
            {
                stack.push(boundries.second);
                l = boundries.first.first;
                r = boundries.first.second;
            }
            // cout << l << r << endl;
        }
    } while (stack.empty() == false); // step5
}