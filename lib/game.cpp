#include "game.h"

namespace GameField {
void Game::Start() {
  if (!is_strategy_custom_) {
    strategy_ = new OrderedStrategy();
  } else {
    strategy_ = new CustomStrategy();
  }

  strategy_->SetWidth(board_.GetWidth());
  strategy_->SetHeight(board_.GetHeight());

  if (board_.GetShipAmount() == 0) {
    for (int i = 0; i < 4; ++i) {
      board_.SetShipAmount(board_.GetShipAmount() + board_.GetShipAmount(i));
    }
  }

  strategy_->SetShipAmount(board_.GetShipAmount());
  is_game_started_ = true;

  if (!board_.AreShipAlive()) {
    board_.SetShipsCombination();
  }
}

void Game::Stop() { is_game_started_ = false; }

void SlaveGame::SetParameters() { return; }

void MasterGame::SetParameters() {
  board_.SetWidth(3);
  board_.SetHeight(3);
  board_.SetShipAmount(0, 4);
  board_.SetShipAmount(4);

  board_.SetShipsCombination();
}

bool MasterGame::SetWidth(uint64_t width) { return false; }

bool SlaveGame::SetWidth(uint64_t width) {
  board_.SetWidth(width);

  return true;
}

uint64_t Game::GetWidth() { return board_.GetWidth(); }

bool MasterGame::SetHeight(uint64_t height) { return false; }

bool SlaveGame::SetHeight(uint64_t height) {
  board_.SetHeight(height);

  return true;
}

uint64_t Game::GetHeight() { return board_.GetHeight(); }

bool MasterGame::SetShipsCount(int type, uint64_t count) { return false; }

bool SlaveGame::SetShipsCount(int type, uint64_t count) {
  board_.SetShipAmount(type - 1, count);
  return true;
}

uint64_t Game::GetShipsCount(int type) {
  return board_.GetShipAmount(type - 1);
}

bool Game::SetStrategy(std::string &strategy_type) {
  if (strategy_type == "custom") {
    is_strategy_custom_ = true;
  } else {
    is_strategy_custom_ = false;
  }

  return true;
}

Coordinates Game::GetNextShot() { return strategy_->GetShotCoordinates(); }

bool Game::SetShotResult(std::string &result) {
  strategy_->SetShotResult(result);

  return true;
}

std::string Game::GetDamage(const Coordinates &shot) {
  return board_.GetShot(shot);
}

std::string Game::IsGameFinished() {
  if (!is_game_started_ || !board_.AreShipAlive() ||
      strategy_->GetShipAmount() == 0) {
    return "yes";
  }
  return "no";
}

std::string Game::IsWin() {
  if (board_.AreShipAlive() && strategy_->GetShipAmount() == 0) {
    return "yes";
  }
  return "no";
}
std::string Game::IsLose() {
  if (!board_.AreShipAlive() && strategy_->GetShipAmount() != 0) {
    return "yes";
  }
  return "no";
}

void Game::DumpBoard(std::string &path) { board_.DumpInfo(path); }

void Game::LoadBoard(std::string &path) { board_.LoadFromFile(path); }
} // namespace GameField
