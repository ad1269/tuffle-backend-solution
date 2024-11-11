#include "tuffle.h"

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "gamestate.h"

// Returns the 5 letter color mask for the submitted guess.
//   "G" means that the letter is in the correct place.
//   "Y" means that the letter is in the wrong place.
//   "B" means that the letter is not in the answer.
std::string GetGuessColorMask(const std::string& guess, std::string answer) {
  std::string result = "BBBBB";
  // Check if the character is correct, and should be marked green.
  for (int i = 0; i < answer.size(); i++) {
    if (answer.at(i) == guess.at(i)) {
      result[i] = 'G';
      // Set to $ to prevent duplicate letters from being marked as yellow
      // later, if it's already been marked green here.
      answer[i] = '$';
    }
  }
  // Check for a correct letter in the wrong position
  for (int i = 0; i < answer.size(); i++) {
    if (answer.find(guess.at(i)) != std::string::npos) {
      int correctIndex = answer.find(guess.at(i));
      if (result.at(i) != 'G') {
        answer[correctIndex] = '$';
        result[i] = 'Y';
      }
    }
  }
  return result;
}

// Returns the 26 letter color mask for the keyboard letters.
//   "G" means that the letter is in the correct place.
//   "Y" means that the letter is in the wrong place.
//   "D" means the letter hasn't been submitted in a guess yet.
std::string GetKeyboardColorMask(const std::vector<std::string>& all_guesses,
                                 const std::string& answer) {
  // Maps from a letter to its color (G, Y, D)
  std::map<char, char> letter_states;

  for (const std::string& guess : all_guesses) {
    for (int pos = 0; pos < guess.size(); pos++) {
      char guessed_char = guess.at(pos);

      if (letter_states[guessed_char] == 'G') {
        continue;
      }

      // answer contains guessed_char
      if (answer.find(guessed_char) != std::string::npos) {
        for (int i = 0; i < answer.length(); i++) {
          if (i == pos && answer.at(i) == guessed_char) {
            letter_states[guessed_char] = 'G';
            break;
          }
          letter_states[guessed_char] = 'Y';
        }
      } else {
        letter_states[guessed_char] = 'D';
      }
    }
  }

  std::string alpha = "abcdefghijklmnopqrstuvwxyz";
  std::string letter_states_string = "";
  for (char c : alpha) {
    if (letter_states.count(c)) {
      letter_states_string += letter_states[c];
    } else {
      letter_states_string += "B";
    }
  }

  return letter_states_string;
}

void TuffleGame::NewGame() {
  game_state_ = GameState(dictionary_.GetRandomTuffle());
}

void TuffleGame::CleanUpGameState() { game_state_.SetErrorMessage(""); }

void TuffleGame::LetterKeyPressed(char key) {
  // If the game is over, do nothing
  if (game_state_.IsInactive()) {
    return;
  }
  CleanUpGameState();

  std::vector<std::string>& guessedWords = game_state_.GetGuessedWords();
  // If this is the start of the game, initialize an empty string
  if (guessedWords.size() == 0) {
    guessedWords.push_back("");
  }
  // Get the current guess
  int current_guess_index = guessedWords.size() - 1;
  std::string current_guess = guessedWords.at(current_guess_index);

  // We can only type 5 characters per row
  if (current_guess.length() != 5) {
    guessedWords[current_guess_index] = current_guess + key;
  }
}

void TuffleGame::EnterKeyPressed() {
  std::vector<std::string>& guessedWords = game_state_.GetGuessedWords();
  // If this is the start or end of the game, do nothing
  if (guessedWords.size() == 0 || game_state_.IsInactive()) {
    return;
  }
  CleanUpGameState();

  // Get the current guess
  int current_guess_index = guessedWords.size() - 1;
  std::string current_guess = guessedWords.at(current_guess_index);

  // There need to be 5 letters in this row to check guess
  if (current_guess.length() != 5) {
    game_state_.SetErrorMessage("Not enough letters!");
    return;
  } else if (!dictionary_.IsValidGuess(current_guess)) {
    game_state_.SetErrorMessage("Not a valid guess!");
    return;
  }

  // Code to calculate the keyboard and board colors
  std::string color_mask =
      GetGuessColorMask(current_guess, game_state_.GetAnswer());
  game_state_.GetBoardColors().push_back(color_mask);
  game_state_.SetLetterColors(
      GetKeyboardColorMask(guessedWords, game_state_.GetAnswer()));

  if (color_mask == "GGGGG") {
    game_state_.SetGameStatus("win");
  } else if (game_state_.GetGuessedWords().size() == 6) {
    game_state_.SetGameStatus("lose");
  }

  // We push the next empty guess onto the game state.
  if (!game_state_.IsInactive()) {
    guessedWords.push_back("");
  }
}

void TuffleGame::DeleteKeyPressed() {
  std::vector<std::string>& guessedWords = game_state_.GetGuessedWords();

  // If this is the start or end of the game, do nothing.
  if (guessedWords.size() == 0 || game_state_.IsInactive()) {
    return;
  }
  CleanUpGameState();

  // Get the current guess
  int current_guess_index = guessedWords.size() - 1;
  std::string current_guess = guessedWords.at(current_guess_index);

  // We can only type 5 characters per row
  if (current_guess.size() != 0) {
    guessedWords.at(current_guess_index) =
        current_guess.substr(0, current_guess.length() - 1);
  }
}
