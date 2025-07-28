#pragma once

#include <cinttypes>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <queue>
#include <set>

#include "coordinates.h"

namespace GameField {
class Strategy {
public:
  virtual Coordinates GetShotCoordinates() = 0;
  virtual void SetShotResult(std::string &result) = 0;

  uint64_t GetWidth();
  void SetWidth(uint64_t width);

  uint64_t GetHeight();
  void SetHeight(uint64_t height);

  uint64_t GetShipAmount();
  void SetShipAmount(uint64_t ship_amount);

protected:
  uint64_t width_;
  uint64_t height_;
  Coordinates last_shot_;
  bool is_first_shot_ = true;
  bool need_to_kill_ = false;
  bool was_last_successful_;
  uint64_t ship_amount_;
};

class OrderedStrategy : public Strategy {
public:
  OrderedStrategy() {}
  ~OrderedStrategy() = default;
  OrderedStrategy(const OrderedStrategy &other) {
    this->width_ = other.width_;
    this->height_ = other.height_;
    this->last_shot_ = other.last_shot_;
    this->is_first_shot_ = other.is_first_shot_;
    this->need_to_kill_ = other.need_to_kill_;
    this->was_last_successful_ = other.was_last_successful_;
    this->ship_amount_ = other.ship_amount_;
  }
  OrderedStrategy &operator=(const OrderedStrategy &other) {
    this->width_ = other.width_;
    this->height_ = other.height_;
    this->last_shot_ = other.last_shot_;
    this->is_first_shot_ = other.is_first_shot_;
    this->need_to_kill_ = other.need_to_kill_;
    this->was_last_successful_ = other.was_last_successful_;
    this->ship_amount_ = other.ship_amount_;
    return *this;
  }

  Coordinates GetShotCoordinates() override;
  void SetShotResult(std::string &result) override;
};

class CustomStrategy : public Strategy {
public:
  CustomStrategy() {}
  ~CustomStrategy() = default;
  CustomStrategy(const CustomStrategy &other) {
    this->width_ = other.width_;
    this->height_ = other.height_;
    this->last_shot_ = other.last_shot_;
    this->is_first_shot_ = other.is_first_shot_;
    this->need_to_kill_ = other.need_to_kill_;
    this->was_last_successful_ = other.was_last_successful_;
    this->ship_amount_ = other.ship_amount_;
    this->need_to_shot_ = other.need_to_shot_;
    this->unusual_shot_ = other.unusual_shot_;
    this->last_ordinary_shot_ = other.last_ordinary_shot_;
  }
  CustomStrategy &operator=(const CustomStrategy &other) {
    this->width_ = other.width_;
    this->height_ = other.height_;
    this->last_shot_ = other.last_shot_;
    this->is_first_shot_ = other.is_first_shot_;
    this->need_to_kill_ = other.need_to_kill_;
    this->was_last_successful_ = other.was_last_successful_;
    this->ship_amount_ = other.ship_amount_;
    this->need_to_shot_ = other.need_to_shot_;
    this->unusual_shot_ = other.unusual_shot_;
    this->last_ordinary_shot_ = other.last_ordinary_shot_;
    return *this;
  }

  Coordinates GetShotCoordinates() override;
  void SetShotResult(std::string &result) override;

private:
  std::queue<Coordinates> need_to_shot_;
  std::set<Coordinates> unusual_shot_;
  Coordinates last_ordinary_shot_;
  int d_coord_ = 0;
};
} // namespace GameField
