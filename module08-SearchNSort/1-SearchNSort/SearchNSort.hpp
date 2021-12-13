#pragma once

#include <algorithm>
#include <ctime>
#include <doctest.h>
#include <random>
#include <utility>

/*-----------------------------------------------------------------------------
 * class definition
 *---------------------------------------------------------------------------*/

/**
 * @brief CMP 246 Module 8 templated class with searching and sorting methods.
 * 
 * This class provides a series of static methods for the following operations:
 * 
 * - searches: linearSearch and binarySearch
 * 
 * - quadratic sorts: bubbleSort, insertionSort, selectionSort
 * 
 * - n lg n sorts: mergeSort, quickSort
 */
template <class T> class SearchNSort {
public:
  /**
   * @brief Perform a binary search on an array.
   * 
   * @param pArr Pointer to the first element of the array to search. The array
   * must be sorted in ascending order.
   * @param n Number of elements in the array.
   * @param key Key value to search for
   * @param compare Pointer to a function used to compare two elements. This 
   * must return a negative value if x < y, zero if x == y, or positive if 
   * x > y.
   * @return int Index of an occurrence of key in pArr, or -1 if the key 
   * was not found in the array.
   */
  static int binarySearch(const T *pArr, size_t n, const T &key,
                          int (*compare)(const T &x, const T &y));

  /**
   * @brief Sort an array using the bubble sort algorithm.
   * 
   * @param pArr Pointer to the first element of the array to search.
   * @param n Size of the array.
   * @param compare Pointer to a function used to compare two elements. This 
   * must return a negative value if x < y, zero if x == y, or positive if 
   * x > y.
   */
  static void bubbleSort(T *pArr, size_t n,
                         int (*compare)(const T &x, const T &y));

  /**
   * @brief Sort an array using the insertion sort algorithm.
   * 
   * @param pArr Pointer to the first element of the array to search.
   * @param n Size of the array.
   * @param compare Pointer to a function used to compare two elements. This 
   * must return a negative value if x < y, zero if x == y, or positive if 
   * x > y.
   */
  static void insertionSort(T *pArr, size_t n,
                            int (*compare)(const T &x, const T &y));

  /**
   * @brief Perform a linear search on an array.
   * 
   * @param pArr Pointer to the first element of the array to search.
   * @param n Number of elements in the array.
   * @param key Key value to search for
   * @param compare Pointer to a function used to compare two elements. This 
   * must return a negative value if x < y, zero if x == y, or positive if 
   * x > y.
   * @return int Index of the first occurrence of key in pArr, or -1 if the key
   * was not found in the array.
   */
  static int linearSearch(const T *pArr, size_t n, const T &key,
                          int (*compare)(const T &x, const T &y));

  /**
   * @brief Sort an array using the merge sort algorithm.
   * 
   * @param pArr Pointer to the first element of the array to search.
   * @param n Size of the array.
   * @param compare Pointer to a function used to compare two elements. This 
   * must return a negative value if x < y, zero if x == y, or positive if 
   * x > y.
   */
  static void mergeSort(T *pArr, size_t n,
                        int (*compare)(const T &x, const T &y));

  /**
   * @brief Sort an array using the quicksort algorithm.
   * 
   * @param pArr Pointer to the first element of the array to search.
   * @param n Size of the array.
   * @param compare Pointer to a function used to compare two elements. This 
   * must return a negative value if x < y, zero if x == y, or positive if 
   * x > y.
   */
  static void quickSort(T *pArr, size_t n,
                        int (*compare)(const T &x, const T &y)) {

    quickSort(pArr, 0, n - 1, compare);
  }

  /**
   * @brief Sort an array using the selection sort algorithm.
   * 
   * @param pArr Pointer to the first element of the array to search.
   * @param n Size of the array.
   * @param compare Pointer to a function used to compare two elements. This 
   * must return a negative value if x < y, zero if x == y, or positive if 
   * x > y.
   */
  static void selectionSort(T *pArr, size_t n,
                            int (*compare)(const T &x, const T &y));

private:
  /**
   * @brief Merge two sorted portions of an array together.
   * 
   * @param pA Array containing two sorted portions
   * @param pB Scratch array destination
   * @param left left index of left sorted portion
   * @param right one past right index of right sorted portion
   * @param mid start of right sorted portion
   * @param compare Pointer to a function used to compare two elements. This 
   * must return a negative value if x < y, zero if x == y, or positive if 
   * x > y.
   */
  static void merge(T *pA, T *pB, size_t left, size_t right, size_t mid,
                    int (*compare)(const T &x, const T &y));

  /**
   * @brief Recursive helper function for mergeSort
   * 
   * @param pA Pointer to first element of the array to sort
   * @param pB Pointer to first element of scratch array
   * @param left Index of leftmost element in the section to be sorted
   * @param right One past index of rightmost element in the section to be 
   * sorted
   * @param compare Pointer to a function used to compare two elements. This 
   * must return a negative value if x < y, zero if x == y, or positive if 
   * x > y.
   */
  static void mergeSort(T *pA, T *pB, size_t left, size_t size_t,
                        int (*compare)(const T &x, const T &y));

  /**
   * @brief Partitioning helper function for quickSort
   * 
   * @param pArr Pointer to first element of the array to sort.
   * @param lo Leftmost index in range being sorted.
   * @param hi Rightmost index in range being sorted.
   * @param compare Pointer to a function used to compare two elements. This 
   * must return a negative value if x < y, zero if x == y, or positive if 
   * x > y.
   * @return int index in [lo, hi] such that everything to the left is less
   * than or equal to everything in the right.
   */
  static size_t partition(T *pArr, size_t lo, size_t hi,
                       int (*compare)(const T &x, const T &y));

  /**
   * @brief Recursive helper function for quickSort.
   * 
   * @param pArr Pointer to first element of the array to sort. 
   * @param lo Index of the leftmost element in range being sorted.
   * @param hi Index of the rightmost element in range being sorted.
   * @param compare Pointer to a function used to compare two elements. This 
   * must return a negative value if x < y, zero if x == y, or positive if 
   * x > y.
   */
  static void quickSort(T *pArr, size_t lo, size_t hi,
                        int (*compare)(const T &x, const T &y));
};

//-----------------------------------------------------------------------------
// function implementations
//-----------------------------------------------------------------------------

/*
 * Implementation of iterative binarySearch() function.
 */
template <class T>
int SearchNSort<T>::binarySearch(const T *pArr, size_t n, const T &key,
                                 int (*comp)(const T &x, const T &y)) {
  size_t i = 0, j = n - 1, mid;
  while (i <= j) {
    mid = (i + j) / 2;
    int res = comp(pArr[mid], key);
    if (res == 0) {
      return mid;
    } else if (res > 0) {
      j = mid - 1;
    } else {
      i = mid + 1;
    }
  }
  return -1;
}

// doctest unit test for binarySearch
TEST_CASE("testing SearchNSort::binarySearch") {
  // make array for searching; make sure it does not have 0, but does have 1
  int pA[100];
  std::mt19937_64 prng(time(0));
  std::uniform_int_distribution<int> dist(-100, 100);
  for(size_t i = 0; i < 100; i++) {
    int v = dist(prng);
    pA[i] = v == 0 ? 1 : v;
  }
  pA[17] = 1;

  // sort the array
  std::sort(pA, pA + 100);

  // lambda function for comparing elements for the search
  auto cmp = [](const int &a, const int &b) { return a - b; };

  // search for 1 should work
  int idx = SearchNSort<int>::binarySearch(pA, 100, 1, cmp);
  CHECK(-1 != idx);
  // search for 0 should not work
  idx = SearchNSort<int>::binarySearch(pA, 100, 0, cmp);
  CHECK(-1 == idx);
}

/*
 * Implementation of bubbleSort() function.
 */
template <class T>
void SearchNSort<T>::bubbleSort(T *pArr, size_t n,
                                int (*comp)(const T &x, const T &y)) {

  do {
    size_t newN = 0u;
    for (size_t i = 1u; i < n; i++) {
      if (comp(pArr[i - 1], pArr[i]) > 0) {
        std::swap(pArr[i - 1], pArr[i]);
        newN = i;
      }
    }
    n = newN;
  } while (n != 0u);
}

// doctest unit test for bubbleSort
TEST_CASE("testing SearchNSort::bubbleSort") {
  // make two arrays for sorting
  int pA[100], pB[100];
  std::mt19937_64 prng(time(0));
  std::uniform_int_distribution<int> dist(-100, 100);
  for(size_t i = 0; i < 100; i++) {
    pA[i] = pB[i] = dist(prng);
  }

  // lambda function for comparing elements for the sort
  auto cmp = [](const int &a, const int &b) { return a - b; };

  // sort using bubbleSort
  SearchNSort<int>::bubbleSort(pA, 100, cmp);

  // sort using std::sort
  std::sort(pB, pB + 100);

  // check elements are the same
  for(size_t i = 0; i < 100; i++) {
    CHECK(pA[i] == pB[i]);
  }
}

/*
 * Implementation of insertionSort() function.
 */
template <class T>
void SearchNSort<T>::insertionSort(T *pArr, size_t n,
                                   int (*comp)(const T &x, const T &y)) {

  for (size_t i = 1u; i < n; i++) {
    size_t j = i;
    while (j > 0u && comp(pArr[j - 1], pArr[j]) > 0) {
      std::swap(pArr[j], pArr[j - 1]);
      j--;
    }
  }
}

// doctest unit test for insertionSort
TEST_CASE("testing SearchNSort::insertionSort") {
  // make two arrays for sorting
  int pA[100], pB[100];
  std::mt19937_64 prng(time(0));
  std::uniform_int_distribution<int> dist(-100, 100);
  for(size_t i = 0; i < 100; i++) {
    pA[i] = pB[i] = dist(prng);
  }

  // lambda function for comparing elements for the sort
  auto cmp = [](const int &a, const int &b) { return a - b; };

  // sort using insertionSort
  SearchNSort<int>::insertionSort(pA, 100, cmp);

  // sort using std::sort
  std::sort(pB, pB + 100);

  // check elements are the same
  for(size_t i = 0; i < 100; i++) {
    CHECK(pA[i] == pB[i]);
  }
}

/*
 * Implementation of linearSearch() function.
 */
template <class T>
int SearchNSort<T>::linearSearch(const T *pArr, size_t n, const T &key,
                                 int (*comp)(const T &x, const T &y)) {

  for (size_t i = 0u; i < n; i++) {
    if (comp(pArr[i], key) == 0) {
      return i;
    }
  }

  // not found? Return -1 flag value
  return -1;
}

// doctest unit test for linearSearch
TEST_CASE("testing SearchNSort::linearSearch") {
  // make array for searching; make sure it does not have 0, but does have 1
  int pA[100];
  std::mt19937_64 prng(time(0));
  std::uniform_int_distribution<int> dist(-100, 100);
  for(size_t i = 0; i < 100; i++) {
    int v = dist(prng);
    pA[i] = v == 0 ? 1 : v;
  }
  pA[17] = 1;

  // lambda function for comparing elements for the search
  auto cmp = [](const int &a, const int &b) { return a - b; };

  // search for 1 should work
  int idx = SearchNSort<int>::linearSearch(pA, 100, 1, cmp);
  CHECK(-1 != idx);
  // search for 0 should not work
  idx = SearchNSort<int>::linearSearch(pA, 100, 0, cmp);
  CHECK(-1 == idx);
}

/*
 * Implementation of private merge() function.
 */
template <class T>
void SearchNSort<T>::merge(T *pA, T *pB, size_t left, size_t right, size_t mid,
                           int (*comp)(const T &x, const T &y)) {

  size_t i = left, j = mid;

  for (size_t k = left; k < right; k++) {
    if (i < mid && (j >= right || comp(pA[i], pA[j]) <= 0)) {
      pB[k] = pA[i++];
    } else {
      pB[k] = pA[j++];
    }
  }
}

/*
 * Implementation of public mergeSort() function.
 */
template <class T>
void SearchNSort<T>::mergeSort(T *pArr, size_t n,
                               int (*comp)(const T &x, const T &y)) {
  // create temporary array
  T *pB = new T[n];

  // do the sorting
  mergeSort(pArr, pB, 0, n, comp);

  // free temporary array
  delete[] pB;
}

// doctest unit test for mergeSort
TEST_CASE("testing SearchNSort::mergeSort") {
  // make two arrays for sorting
  int pA[100], pB[100];
  std::mt19937_64 prng(time(0));
  std::uniform_int_distribution<int> dist(-100, 100);
  for(size_t i = 0; i < 100; i++) {
    pA[i] = pB[i] = dist(prng);
  }

  // lambda function for comparing elements for the sort
  auto cmp = [](const int &a, const int &b) { return a - b; };

  // sort using mergeSort
  SearchNSort<int>::mergeSort(pA, 100, cmp);

  // sort using std::sort
  std::sort(pB, pB + 100);

  // check elements are the same
  for(size_t i = 0; i < 100; i++) {
    CHECK(pA[i] == pB[i]);
  }
}

/*
 * Implementation of private mergeSort() helper function.
 */
template <class T>
void SearchNSort<T>::mergeSort(T *pA, T *pB, size_t left, size_t right,
                               int (*comp)(const T &x, const T &y)) {

  // array of size one or less is already sorted!
  if ((right - left) < 2) {
    return;
  }

  // otherwise, split, sort, and merge
  size_t mid = (left + right) / 2;
  mergeSort(pA, pB, left, mid, comp);
  mergeSort(pA, pB, mid, right, comp);
  merge(pA, pB, left, right, mid, comp);

  // copy from scratch back to original array
  for (size_t i = left; i < right; i++) {
    pA[i] = pB[i];
  }
}

/*
 * Implementation of partition() helper function.
 */
template <class T>
size_t SearchNSort<T>::partition(T *pArr, size_t lo, size_t hi,
                              int (*compare)(const T &x, const T &y)) {

  // arbitrarily choose first value in range as pivot value
  const T &pivot = pArr[lo];

  // indices to slide right and left
  size_t i = lo - 1;
  size_t j = hi + 1;

  while (true) {
    // slide i right until we find value >= pivot
    while (compare(pArr[++i], pivot) < 0)
      ; // empty loop body

    // slide j left until we find value <= pivot
    while (compare(pArr[--j], pivot) > 0)
      ; // empty loop body

    // if the indices have crossed, j is the pivot index
    if (i >= j) {
      return j;
    }

    // if not, swap the out of place elements and continue
    // sliding i and j
    std::swap(pArr[i], pArr[j]);
  }
}

/*
 * Implementation of recursive quickSort() helper function.
 */
template <class T>
void SearchNSort<T>::quickSort(T *pArr, size_t lo, size_t hi,
                               int (*compare)(const T &x, const T &y)) {

  // portion of size 0 or 1 is already sorted!
  if (lo < hi) {

    // array portion of array so pArr[lo, p - 1] is <= pArr[p],
    // and pArr[p + 1, hi) is >= pArr[p]
    size_t p = partition(pArr, lo, hi, compare);

    // recursively sort left and right halves
    quickSort(pArr, lo, p, compare);
    quickSort(pArr, p + 1, hi, compare);
  }
}

// doctest unit test for quickSort
TEST_CASE("testing SearchNSort::quickSort") {
  // make two arrays for sorting
  int pA[100], pB[100];
  std::mt19937_64 prng(time(0));
  std::uniform_int_distribution<int> dist(-100, 100);
  for(size_t i = 0; i < 100; i++) {
    pA[i] = pB[i] = dist(prng);
  }

  // lambda function for comparing elements for the sort
  auto cmp = [](const int &a, const int &b) { return a - b; };

  // sort using quickSort
  SearchNSort<int>::quickSort(pA, 100, cmp);

  // sort using std::sort
  std::sort(pB, pB + 100);

  // check elements are the same
  for(size_t i = 0; i < 100; i++) {
    CHECK(pA[i] == pB[i]);
  }
}

/*
 * Implementation of selectionSort() function.
 */
template <class T>
void SearchNSort<T>::selectionSort(T *pArr, size_t n,
                                   int (*comp)(const T &x, const T &y)) {
  size_t i, j, minIndex;

  for (i = 0u; i < n - 1u; i++) {

    minIndex = i;
    for (j = i + 1u; j < n; j++) {
      if (comp(pArr[j], pArr[minIndex]) < 0) {
        minIndex = j;
      }
    }

    if (minIndex != i) {
      std::swap(pArr[i], pArr[minIndex]);
    }
  }
}

// doctest unit test for selectionSort
TEST_CASE("testing SearchNSort::selectionSort") {
  // make two arrays for sorting
  int pA[100], pB[100];
  std::mt19937_64 prng(time(0));
  std::uniform_int_distribution<int> dist(-100, 100);
  for(size_t i = 0; i < 100; i++) {
    pA[i] = pB[i] = dist(prng);
  }

  // lambda function for comparing elements for the sort
  auto cmp = [](const int &a, const int &b) { return a - b; };

  // sort using selectionSort
  SearchNSort<int>::selectionSort(pA, 100, cmp);

  // sort using std::sort
  std::sort(pB, pB + 100);

  // check elements are the same
  for(size_t i = 0; i < 100; i++) {
    CHECK(pA[i] == pB[i]);
  }
}
