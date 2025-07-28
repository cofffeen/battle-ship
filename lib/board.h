#pragma once

#include <cinttypes>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "coordinates.h"
#include "split.h"

namespace GameField {
class Board {
public:
  Board() {}
  ~Board() = default;
  Board(const Board &other) {
    this->width_ = other.width_;
    this->height_ = other.height_;
    this->alive_ship_coordinates_ = other.alive_ship_coordinates_;
    this->ship_coordinates_ = other.ship_coordinates_;
    this->ship_amount_ = other.ship_amount_;
    this->info_ = other.info_;
  }
  Board &operator=(const Board &other) {
    this->width_ = other.width_;
    this->height_ = other.height_;
    this->alive_ship_coordinates_ = other.alive_ship_coordinates_;
    this->ship_coordinates_ = other.ship_coordinates_;
    this->ship_amount_ = other.ship_amount_;
    this->info_ = other.info_;
    return *this;
  }

  bool IsShipKilled(const Coordinates &shot);
  std::string GetShot(const Coordinates &shot);

  void SetShipOnBoard(int length, bool is_horizontal,
                      const Coordinates &coordinate);
  void SetShipsCombination();

  void LoadFromFile(const std::string &path);

  void AddBoardInfo();
  void AddShipInfo(int length, bool is_horizontal,
                   const Coordinates &coordinate);

  void DumpInfo(const std::string &path);

  uint64_t GetWidth();
  void SetWidth(uint64_t width);

  uint64_t GetHeight();
  void SetHeight(uint64_t height);

  uint64_t GetShipAmount(size_t size);
  void SetShipAmount(size_t size, uint64_t count);

  uint64_t GetShipAmount();
  void SetShipAmount(uint64_t count);

  bool AreShipAlive();

private:
  uint64_t width_ = 0;
  uint64_t height_ = 0;

  std::set<Coordinates> ship_coordinates_;
  std::set<Coordinates> alive_ship_coordinates_;

  uint64_t ship_amount_ = 0;
  uint64_t ships_count_[4]{};

  std::vector<std::string> info_;
};
} // namespace GameField
