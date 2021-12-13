#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "../1-SearchNSort/SearchNSort.hpp"

/**
 * @brief Class representing a task that takes two phases.
 * 
 */
class Task {
public:
    /**
     * @brief Construct a new Task object with empty values.
     * 
     */
    Task() : name(""), elapsed1(0), elapsed2(0) { }

    /**
     * @brief Name of the task.
     * 
     */
    std::string name;
    /**
     * @brief Elapsed time for phase 1.
     * 
     */
    size_t elapsed1;
    /**
     * @brief Elapsed time for phase 2. 
     * 
     */
    size_t elapsed2;

    /**
    * @brief Override of < for Task objects.
    * 
    * @param t Task to compare with this one.
    * @return If elapsed1 fields are equal, return elapsed2 < t.elapsed 2;
    * otherwise, return elapsed1 < t.elapsed1;
    */
    bool operator<(const Task &t) {
        if(elapsed1 == t.elapsed1) {
            return elapsed2 < t.elapsed2;
        } else {
            return elapsed1 < t.elapsed1;
        }
    }

    /**
    * @brief Override of > for Task objects.
    * 
    * @param t Task to compare with this one.
    * @return If elapsed1 fields are equal, return elapsed2 > t.elapsed 2;
    * otherwise, return elapsed1 > t.elapsed1;
    */
    bool operator>(const Task &t) {
        if(elapsed1 == t.elapsed1) {
            return elapsed2 > t.elapsed2;
        } else {
            return elapsed1 > t.elapsed1;
        }
    }

    /**
    * @brief Override of == for Task objects.
    * 
    * @param t Task to compare with this one.
    * @return If elapsed1 fields are equal, return elapsed2 == t.elapsed 2;
    * otherwise, return elapsed1 == t.elapsed1;
    */
    bool operator==(const Task &t) {
        if(elapsed1 == t.elapsed1) {
            return elapsed2 == t.elapsed2;
        } else {
            return elapsed1 == t.elapsed1;
        }
    }
};

/**
 * @brief Stream insertion override for Task objects.
 * 
 * @param out std::ostream to write to
 * @param t Task object to write
 * @return std::ostream& out for chaining
 */
std::ostream& operator<<(std::ostream &out, const Task &t) {
    out << t.name << ": (" << t.elapsed1 << ", " << t.elapsed2 << ")";
    return out;
}

/**
 * @brief Comparison function for two Task objects. 
 * 
 * Compares based on elapsed time of second phase of the task. 
 * 
 * @param a First Task object
 * @param b Second Task object
 * @return int negative if a < b, 0 if a == b, positive if a > b
 */
int compare(const Task &a, const Task &b) {
    return a.elapsed2 - b.elapsed2;
}

/**
 * @brief Application entry point
 */
int main() {

    // open data file an find out how many tasks there are
    std::ifstream inFile("times.txt");
    size_t n;
    inFile >> n;

    // fill an array of Task objects with data from the file
    Task tasks[n];
    std::string name;
    size_t s1, e1, s2, e2, idx = 0;
    while(inFile >> name >> s1 >> e1 >> s2 >> e2) {
        tasks[idx].name = name;
        tasks[idx].elapsed1 = (e1 - s1);
        tasks[idx].elapsed2 = (e2 - s2);
        idx++;
    }
    inFile.close();

    // print initial list of tasks
    std::cout << "There are " << n << " jobs to complete:" << std::endl;
    for(idx = 0; idx < n; idx++) {
        std::cout << tasks[idx] << std::endl;
    }

    // sort by phase 2 times
    SearchNSort<Task>::quickSort(tasks, n, compare);

    // print out suggested order of tasks
    std::cout << "\nTasks ordered by phase 2 time: " << std::endl;
    for(idx = 0; idx < n; idx++) {
        std::cout << tasks[idx] << std::endl;
    }

    return EXIT_SUCCESS;
}