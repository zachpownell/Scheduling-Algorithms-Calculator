using namespace::std;

#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <vector>
#include <algorithm>
#include "task.h"

vector <Task> threads;

void fillThreads(char *fileName);

int main(int argc, char** argv) {

    cout << "CS 433 Programming Assignment 3" << endl;
    cout << "Author: Zach Pownell" << endl;
    cout << "Date: 03/28/2022" << endl;
    cout << "Course: CS433 (Operating Systems)" << endl;
    cout << "Description : Priority Scheduler" << endl;
    cout << "=================================" << endl;

    // Call the fillThreads function to fill the threads vector from given file.
    fillThreads(argv[1]);

    // Priority implementation.

    // Organize our tasks in threads vector based on their priorities.
    sort(threads.begin(), threads.end(), [](const Task& lhs, const Task& rhs) {
        return lhs.priority < rhs.priority;
    });

    // Keep track of the time.
    int current_time = 0;

    // Use these later to calculate the average.
    int total_turn_around_time = 0, total_waiting_time = 0;

    // For loop to iterate through each task in our threads vector.
    for (const Task& task : threads) {

        // Increment the current time by the task's burst time.
        current_time += task.burst;

        int turn_around_time = current_time;
        int waiting_time = turn_around_time - task.burst;

        total_turn_around_time += turn_around_time;
        total_waiting_time += waiting_time;

        cout << task.name << " turn around time = " << turn_around_time << ", waiting time = " << waiting_time << endl;

    }

    // Display the average turn-around and waiting times by taking their totals and dividing by the number of threads.
    cout << "Average turn-around time = " << (total_turn_around_time / threads.size()) << ", Average waiting time = " << (total_waiting_time / threads.size()) << endl;






//    int current_time = 0;
//
//    // Use these later to calculate the average.
//    int total_turn_around_time = 0, total_waiting_time = 0;
//
//    // For loop to iterate through each task in our threads vector.
//    for (const Task& task : threads) {
//
//        // Increment the current time by the task's burst time.
//        current_time += task.burst;
//
//        int turn_around_time = current_time;
//        int waiting_time = turn_around_time - task.burst;
//
//        total_turn_around_time += turn_around_time;
//        total_waiting_time += waiting_time;
//
//        cout << task.name << " turn around time = " << turn_around_time << ", waiting time = " << waiting_time << endl;
//
//    }
//
//    // Display the average turn-around and waiting times by taking their totals and dividing by the number of threads.
//    cout << "Average turn-around time = " << (total_turn_around_time / threads.size()) << ", Average waiting time = " << (total_waiting_time / threads.size()) << endl;

    return 0;
}



void fillThreads(char *fileName) {

    // Check if a file was specified when executing our program. If not, terminate the program.
    if (fileName == nullptr) {
        cout << "No file specified. Terminating." << endl;
        exit(1);
    }

    // Create our Input File Stream and open it.
    ifstream fin;
    fin.open(fileName);

    // Check if the specified file exists. If not, terminate the program.
    if (!fin) {
        cout << "File '" << fileName << "' does not exist. Terminating." << endl;
        exit(1);
    }

    cout << "Found file: " << fileName << ". Reading. " << endl;

    // Create a string named line to store each read line from the file.
    string line;

    // While loop to iterate through each line in the file.
    while (getline(fin, line)) {

        // Remove any commas.
        line.erase(remove(line.begin(), line.end(), ','), line.end());

        // Create a new task for current line.
        Task task;

        // Create istringstream to read each word in the line, word to store the current word, and pointer to keep track
        // of the word's location in the line.
        istringstream iss(line);
        string word;
        int pointer = 0;

        // While loop to iterate through each word in the line. If the word's location is 0, assign the task's name
        // to the current word. If location is 1, assign it to the priority. If location is 2, assign it to the burst.
        while (iss >> word) {

            if (pointer % 3 == 0) task.name = word; // If the word's location is 0, assign task's name to the word.
            else if (pointer % 3 == 1) task.priority = stoi(word);
            else if (pointer % 3 == 2) task.burst = stoi(word);

            // Increment the location
            pointer ++;

        }

        // Add our task to the threads vector.
        threads.push_back(task);

    } // End of while loop.

}