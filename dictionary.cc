#include "dictionary.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

Dictionary::Dictionary(const std::string& valid_tuffles_filename,
                       const std::string& valid_guesses_filename) {
  // Read from the file containing all valid secret
  // tuffles, and insert them into the valid_tuffles_ vector.
  std::ifstream tuffles_file(valid_tuffles_filename);
  std::string word;
  while (tuffles_file >> word) {
    valid_tuffles_.push_back(word);
  }

  // Read from the file containing all valid guesses,
  // and insert them into the valid_guesses_ set.
  std::ifstream guesses_file(valid_guesses_filename);
  while (guesses_file >> word) {
    valid_guesses_.insert(word);
  }
  srand(time(NULL));
}

bool Dictionary::IsValidGuess(const std::string& word) const {
  return valid_guesses_.find(word) != valid_guesses_.end();
}

const std::string& Dictionary::GetRandomTuffle() const {
  int random_index = rand() % valid_tuffles_.size();
  return valid_tuffles_.at(random_index);
}