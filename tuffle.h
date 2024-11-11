#include <string>
#include <vector>

#include "dictionary.h"
#include "gamestate.h"

class TuffleGame {
 public:
  TuffleGame(Dictionary dict)
      : dictionary_(dict), game_state_(dict.GetRandomTuffle()) {}
  GameState GetGameState() { return game_state_; }
  // Called by the Tuffle frontend when the user clicks "Next Tuffle".
  void NewGame();
  // Called by the Tuffle frontend when the user enters a letter.
  void LetterKeyPressed(char key);
  // Called by the Tuffle frontend when the user submits a guess.
  void EnterKeyPressed();
  // Called by the Tuffle frontend when the presses backspace.
  void DeleteKeyPressed();

 private:
  void CleanUpGameState();
  GameState game_state_;
  Dictionary dictionary_;
};
