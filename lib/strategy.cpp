#include "strategy.h"

namespace GameField {
uint64_t Strategy::GetWidth() { return width_; }

void Strategy::SetWidth(uint64_t width) { width_ = width; }

uint64_t Strategy::GetHeight() { return height_; }

void Strategy::SetHeight(uint64_t height) { height_ = height; }

uint64_t Strategy::GetShipAmount() { return ship_amount_; }

void Strategy::SetShipAmount(uint64_t ship_amount) {
  ship_amount_ = ship_amount;
}

Coordinates OrderedStrategy::GetShotCoordinates() {
  if (is_first_shot_) {
    is_first_shot_ = false;
    last_shot_ = {0, 0};
    return last_shot_;
  }

  if (last_shot_.x < width_ - 1) {
    ++last_shot_.x;
  } else {
    ++last_shot_.y;
    last_shot_.x = 0;
  }

  return last_shot_;
}

Coordinates CustomStrategy::GetShotCoordinates() {
  if (is_first_shot_) {
    is_first_shot_ = false;
    last_ordinary_shot_ = {0, 0};
    last_shot_ = last_ordinary_shot_;
    return last_shot_;
  }

  if (need_to_kill_ && was_last_successful_) {
    if (last_shot_.x < width_ - 1) {
      need_to_shot_.push({last_shot_.x + 1, last_shot_.y});
    }
    if (last_shot_.x > 0 && last_shot_.x == last_ordinary_shot_.x) {
      need_to_shot_.push({last_shot_.x - 1, last_shot_.y});
    }
    if (last_shot_.y < height_ - 1) {
      need_to_shot_.push({last_shot_.x, last_shot_.y + 1});
    }
    if (last_shot_.y > 0 && last_shot_.y == last_ordinary_shot_.y) {
      need_to_shot_.push({last_shot_.x, last_shot_.y - 1});
    }
  }

  if (!need_to_shot_.empty()) {
    last_shot_ = need_to_shot_.front();
    unusual_shot_.insert(last_shot_);
    need_to_shot_.pop();
    return last_shot_;
  }

  if (last_ordinary_shot_.x < width_ - 2) {
    last_ordinary_shot_.x += 2;
  } else {
    if (last_ordinary_shot_.y < height_ - 1) {
      ++last_ordinary_shot_.y;
      last_ordinary_shot_.x = (last_ordinary_shot_.y + d_coord_) & 1;
    } else {
      d_coord_ = 1;
      last_ordinary_shot_ = {1, 0};
      if (width_ == 1) {
        last_ordinary_shot_ = {0, 1};
      }
    }
  }
  last_shot_ = last_ordinary_shot_;

  if (unusual_shot_.find(last_shot_) != unusual_shot_.end()) {
    GetShotCoordinates();
  }
  return last_shot_;
}

void OrderedStrategy::SetShotResult(std::string &result) {
  if (result == "kill") {
    --ship_amount_;
  }
}

void CustomStrategy::SetShotResult(std::string &result) {
  if (result == "hit") {
    need_to_kill_ = true;
    was_last_successful_ = true;
  }
  if (result == "kill") {
    need_to_kill_ = false;
    was_last_successful_ = true;
    --ship_amount_;
  }
  if (result == "miss") {
    was_last_successful_ = false;
  }
}
} // namespace GameField
