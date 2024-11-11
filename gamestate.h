#pragma once

#include <string>
#include <vector>

class GameState {
 public:
  GameState(const std::string& answer);

  const std::string& GetAnswer() const { return answer_; }
  void SetAnswer(const std::string& answer) { answer_ = answer; }

  std::vector<std::string>& GetBoardColors() { return board_colors_; }
  void SetBoardColors(std::vector<std::string> board_colors) {
    board_colors_ = board_colors;
  }

  std::vector<std::string>& GetGuessedWords() { return guessed_words_; }
  void SetGuessedWords(std::vector<std::string> guessed_words) {
    guessed_words_ = guessed_words;
  }

  std::string GetLetterColors() { return letter_colors_; }
  void SetLetterColors(std::string letter_colors) {
    letter_colors_ = letter_colors;
  }

  bool IsInactive() { return game_status_ != "active"; }
  std::string GetGameStatus() { return game_status_; }
  void SetGameStatus(std::string game_status) { game_status_ = game_status; }

  std::string GetErrorMessage() { return error_message_; }
  void SetErrorMessage(std::string error_message) {
    error_message_ = error_message;
  }

 private:
  // The secret Tuffle!
  std::string answer_;

  // Each string in board_colors_ represents the tile colors for
  // each character in a 5 letter guess that was made.
  // 'G': correct, 'Y': correct letter, wrong position, 'B': incorrect
  std::vector<std::string> board_colors_;

  // Each string in guessed_words_ represents a 5 letter guess.
  std::vector<std::string> guessed_words_;

  // Represents the colors of the keyboard, where index 0 is the color
  // of letter 'A', and index 25 is the color of letter 'Z.'
  // 'G': correct, 'Y': correct letter, wrong position, 'B': incorrect
  std::string letter_colors_;

  // Set to one of: "active", "win", or "lose".
  std::string game_status_;

  // When present, describes the error that occurred.
  std::string error_message_;
};
