/*#include <string>
using namespace std;

bool somePredicate(string s);
bool allTrue(const string a[], int n);
int countTrue(const string a[], int n);
int firstTrue(const string a[], int n);
bool contains(const string a1[], int n1, const string a2[], int n2);

bool somePredicate(string s)
{
    return s.empty();
}*/

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
    if (n <= 0)
    {
        return true;
    }
    else if (n == 1) // BASE CASE
    {
        return somePredicate(a[0]);
    }
    else
    {
        return somePredicate(a[0]) && allTrue(a + 1, n - 1); // "THE FIRST AND THE REST" APPROACH
    } 
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const string a[], int n)
{
    if (n <= 0)
    {
        return 0;
    }
    else if (n == 1) // BASE CASE
    {
        return somePredicate(a[0]);
    }
    else
    {
        return somePredicate(a[0]) + countTrue(a + 1, n - 1); // "THE FIRST AND THE REST" APPROACH
    }
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const string a[], int n)
{
    if (n <= 0)
    {
        return -1;
    }

    if (somePredicate(a[0])) // BASE CASE
    {
        return 0;
    }

    if (firstTrue(a + 1, n - 1) == -1) // BASE CASE
    {
        return -1;
    }

    return firstTrue(a + 1, n - 1) + 1;
}

// Return the subscript of the first string in the array that is >= all
// strings in the array (i.e., return the smallest subscript m such
// that a[m] >= a[k] for all k from 0 to n-1).  If the function is told
// that no strings are to be considered to be in the array, return -1.
int positionOfMax(const string a[], int n)
{
    if (n <= 0)
    {
        return -1;
    }
    if (n == 1) // BASE CASE
    {
        return 0;
    }

    int max = 1 + positionOfMax(a + 1, n - 1);

    if (a[0] >= a[max])
    {
        return 0;
    }

    return max;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "john" "sonia" "elena" "ketanji" "sonia" "elena" "samuel"
// then the function should return true if a2 is
//    "sonia" "ketanji" "samuel"
// or
//    "sonia" "elena" "elena"
// and it should return false if a2 is
//    "sonia" "samuel" "ketanji"
// or
//    "john" "ketanji" "ketanji"
bool contains(const string a1[], int n1, const string a2[], int n2)
{
    if (n2 <= 0)
    {
        return true;
    }

    if (n2 > n1)
    {
        return false;
    }
    
    if (a1[0] == a2[0])
    {
        return contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1); // Check the remaining elements in a1 and a2
    }

    return contains(a1 + 1, n1 - 1, a2, n2);  // Check the remaining elements of a1 with the current element of a2
}

/*#include <iostream>
#include <cassert>

int main()
{
    string a[] = { "", "" };
    assert(allTrue(a, 2) == true);
    string aa[] = { "abcdefg", "", "" };
    assert(allTrue(aa, 3) == false);
    assert(countTrue(aa, 3) == 2);
    assert(firstTrue(aa, 3) == 1);
    string aaa[] = { "A", "B", "C" };
    assert(positionOfMax(aaa, 3) == 2);
    string aaaa[] = { "BB", "AB", "BA", "AA" };
    assert(positionOfMax(aaaa, 4) == 0);

    string a1[] = { "john", "sonia", "elena", "ketanji", "sonia", "elena", "samuel" };
    string a2[] = { "sonia", "ketanji", "samuel" };
    string a3[] = { "sonia", "elena", "elena" };
    string a4[] = { "sonia", "samuel", "ketanji" };
    string a5[] = { "john", "ketanji", "ketanji" };
    assert(contains(a1, 7, a2, 3) == 1);
    assert(contains(a1, 7, a3, 3) == 1);
    assert(contains(a1, 7, a4, 3) == 0);
    assert(contains(a1, 7, a5, 3) == 0);

    cout << "Passed all test cases" << endl;

    return 0;
}*/