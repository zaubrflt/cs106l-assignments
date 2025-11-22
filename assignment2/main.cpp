/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <algorithm>

std::string kYourName = "Zane Cheng"; // Don't forget to change this!
const int STUDENT_CNT = 1000;

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::unordered_set<std::string> get_applicants(std::string filename) {
  std::ifstream file(filename);
  std::unordered_set<std::string> all_applicants;
  if (!file) {
    std::cerr << "parse_csv: Failed to open file " << filename << std::endl;
    return all_applicants;
  }
  all_applicants.reserve(STUDENT_CNT);

  std::string line;
  while (std::getline(file, line)) {
    // std::cout << "read: " << line << std::endl;
    if (!line.empty()) {
      all_applicants.insert(std::move(line));
    }
  }

  return all_applicants;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::unordered_set<std::string>& students) {
    std::queue<const std::string*> matches_queue;

    // name must be "First Last"
    auto pos = name.find(' ');
    if (pos == std::string::npos) return matches_queue;

    char first_initial = name[0];
    char last_initial  = name[pos + 1];

    for (const auto& student : students) {
        auto p = student.find(' ');
        if (p == std::string::npos) continue;

        if (student[0] == first_initial && student[p + 1] == last_initial) {
            matches_queue.push(&student);
        }
    }

    return matches_queue;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  while (!matches.empty()) {
    auto name = matches.front();
    matches.pop();
    if ((*name).size() == kYourName.size()) {
      std::cout << "return: " << *name << std::endl;
      return *name;
    }
  }

  return "NO MATCHES FOUND.";
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
