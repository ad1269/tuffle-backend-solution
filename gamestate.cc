#include "gamestate.h"

#include <string>

inline const std::string kDefaultAnswer = "tuffy";
inline const std::string kDefaultKeyboardColors = "BBBBBBBBBBBBBBBBBBBBBBBBBB";
inline const std::string kDefaultGameStatus = "active";

GameState::GameState(const std::string& answer)
    : answer_(answer),
      letter_colors_(kDefaultKeyboardColors),
      game_status_(kDefaultGameStatus),
      error_message_("") {}
