#pragma once

#include <cinttypes>
#include <cstddef>
#include <cstdint>
#include <iostream>

#include "board.h"
#include "strategy.h"

namespace GameField {
class Game {
public:
  void Start();
  void Stop();

  virtual bool SetWidth(uint64_t width) = 0;
  uint64_t GetWidth();
  virtual bool SetHeight(uint64_t height) = 0;
  uint64_t GetHeight();

  virtual bool SetShipsCount(int type, uint64_t count) = 0;
  uint64_t GetShipsCount(int type);

  bool SetStrategy(std::string &strategy_type);

  Coordinates GetNextShot();

  bool SetShotResult(std::string &result);

  std::string GetDamage(const Coordinates &shot);

  std::string IsGameFinished();
  std::string IsWin();
  std::string IsLose();

  void DumpBoard(std::string &path);
  void LoadBoard(std::string &path);

  virtual void SetParameters() = 0;

protected:
  bool is_game_started_ = false;
  Board board_;

  bool is_strategy_custom_ = false;
  Strategy *strategy_;
};

class MasterGame : public Game {
public:
  MasterGame() {}
  ~MasterGame() = default;
  MasterGame &operator=(MasterGame &other) {
    this->is_game_started_ = other.is_game_started_;
    this->board_ = other.board_;
    this->is_strategy_custom_ = other.is_strategy_custom_;
    this->strategy_ = other.strategy_;
    return *this;
  }

  MasterGame(const MasterGame &other) {
    this->is_game_started_ = other.is_game_started_;
    this->board_ = other.board_;
    this->is_strategy_custom_ = other.is_strategy_custom_;
    this->strategy_ = other.strategy_;
  }

  bool SetWidth(uint64_t width) override;
  bool SetHeight(uint64_t height) override;
  bool SetShipsCount(int type, uint64_t count) override;

  void SetParameters() override;
};

class SlaveGame : public Game {
public:
  SlaveGame() {}
  ~SlaveGame() = default;
  SlaveGame &operator=(SlaveGame &other) {
    this->is_game_started_ = other.is_game_started_;
    this->board_ = other.board_;
    this->is_strategy_custom_ = other.is_strategy_custom_;
    this->strategy_ = other.strategy_;
    return *this;
  }
  SlaveGame(const SlaveGame &other) {
    this->is_game_started_ = other.is_game_started_;
    this->board_ = other.board_;
    this->is_strategy_custom_ = other.is_strategy_custom_;
    this->strategy_ = other.strategy_;
  }

  bool SetWidth(uint64_t width) override;
  bool SetHeight(uint64_t height) override;
  bool SetShipsCount(int type, uint64_t count) override;

  void SetParameters() override;
};
} // namespace GameField
