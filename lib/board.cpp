#include "board.h"

namespace GameField {
bool Board::IsShipKilled(const Coordinates &shot) {
  for (uint64_t x = shot.x; shot.x - x < 4; --x) {
    if (alive_ship_coordinates_.find({x, shot.y}) !=
        alive_ship_coordinates_.end()) {
      return false;
    }
    if (ship_coordinates_.find({x, shot.y}) == ship_coordinates_.end() ||
        x == 0) {
      break;
    }
  }

  for (uint64_t x = shot.x; x - shot.x < 4 && x < width_; ++x) {
    if (alive_ship_coordinates_.find({x, shot.y}) !=
        alive_ship_coordinates_.end()) {
      return false;
    }
    if (ship_coordinates_.find({x, shot.y}) == ship_coordinates_.end()) {
      break;
    }
  }

  for (uint64_t y = shot.y; shot.y - y < 4; --y) {
    if (alive_ship_coordinates_.find({shot.x, y}) !=
        alive_ship_coordinates_.end()) {
      return false;
    }
    if (ship_coordinates_.find({shot.x, y}) == ship_coordinates_.end() ||
        y == 0) {
      break;
    }
  }

  for (uint64_t y = shot.y; y - shot.y < 4 && y < height_; ++y) {
    if (alive_ship_coordinates_.find({shot.x, y}) !=
        alive_ship_coordinates_.end()) {
      return false;
    }
    if (ship_coordinates_.find({shot.x, y}) == ship_coordinates_.end()) {
      break;
    }
  }

  return true;
}

std::string Board::GetShot(const Coordinates &shot) {
  if (ship_coordinates_.find(shot) != ship_coordinates_.end()) {
    alive_ship_coordinates_.erase(shot);
    if (IsShipKilled(shot)) {
      return "kill";
    }
    return "hit";
  }

  return "miss";
}

void Board::SetShipOnBoard(int length, bool is_horizontal,
                           const Coordinates &coordinate) {
  if (is_horizontal) {
    for (int i = 0; i < length; ++i) {
      ship_coordinates_.insert({coordinate.x + i, coordinate.y});
      alive_ship_coordinates_.insert({coordinate.x + i, coordinate.y});
    }
  } else {
    for (int i = 0; i < length; ++i) {
      ship_coordinates_.insert({coordinate.x + i, coordinate.y});
      alive_ship_coordinates_.insert({coordinate.x, coordinate.y + i});
    }
  }

  AddShipInfo(length, is_horizontal, coordinate);
}

void Board::SetShipsCombination() {
  uint64_t setted_ships[4]{};

  AddBoardInfo();

  uint64_t x = 0;
  uint64_t y = 0;

  int current_length = 4;
  while (current_length > 0 && ships_count_[current_length - 1] == 0) {
    --current_length;
  }
  if (current_length == 0) {
    return;
  }

  if (width_ > height_) {
    for (y = 0; y < height_; y += 2) {
      for (x = 0; x <= width_ - current_length; ++x) {
        while (setted_ships[current_length - 1] ==
               ships_count_[current_length - 1]) {
          --current_length;
          if (current_length == 0) {
            return;
          }
        }

        if (current_length == 0) {
          return;
        }

        if (setted_ships[current_length - 1] <
            ships_count_[current_length - 1]) {
          SetShipOnBoard(current_length, true, {x, y});
          x += current_length;
          ++setted_ships[current_length - 1];
        }
      }

      for (int length = current_length - 1; length > 0; --length) {
        if (x <= width_ - length &&
            setted_ships[length - 1] < ships_count_[length - 1]) {
          SetShipOnBoard(length, true, {x, y});
          ++setted_ships[length - 1];
        }
      }
    }
  } else {
    for (x = 0; x < width_; x += 2) {
      for (y = 0; y <= height_ - current_length; ++y) {
        while (setted_ships[current_length - 1] ==
               ships_count_[current_length - 1]) {
          --current_length;
          if (current_length == 0) {
            return;
          }
        }

        if (current_length == 0) {
          return;
        }

        if (setted_ships[current_length - 1] <
            ships_count_[current_length - 1]) {
          SetShipOnBoard(current_length, false, {x, y});
          y += current_length;
          ++setted_ships[current_length - 1];
        }
      }

      for (int length = current_length - 1; length > 0; --length) {
        if (y <= height_ - length &&
            setted_ships[length - 1] < ships_count_[length - 1]) {
          SetShipOnBoard(length, false, {x, y});
          ++setted_ships[length - 1];
          break;
        }
      }
    }
  }
}

void Board::LoadFromFile(const std::string &path) {
  std::ifstream fin;
  fin.open(path);

  fin >> width_ >> height_;

  AddBoardInfo();

  std::string ship_info;
  std::getline(fin, ship_info);
  while (std::getline(fin, ship_info)) {
    std::vector<std::string> info = SplitString(ship_info);

    SetShipOnBoard(std::stoi(info[0]), (info[1][0] == 'h'),
                   {std::stoull(info[2]), std::stoull(info[3])});
  }

  fin.close();
}

void Board::AddBoardInfo() {
  info_.push_back(std::to_string(width_) + " " + std::to_string(height_));
}

void Board::AddShipInfo(int length, bool is_horizontal,
                        const Coordinates &coordinate) {
  std::string ship_info = std::to_string(length) + " ";
  if (is_horizontal) {
    ship_info.push_back('h');
  } else {
    ship_info.push_back('v');
  }

  ship_info +=
      " " + std::to_string(coordinate.x) + " " + std::to_string(coordinate.y);

  info_.push_back(ship_info);
}

void Board::DumpInfo(const std::string &path) {
  std::ofstream fout;
  fout.open(path);

  for (uint64_t i = 0; i < info_.size(); ++i) {
    fout << info_[i] << std::endl;
  }

  fout.close();
}

uint64_t Board::GetWidth() { return width_; }

void Board::SetWidth(uint64_t width) { width_ = width; }

uint64_t Board::GetHeight() { return height_; }

void Board::SetHeight(uint64_t height) { height_ = height; }

uint64_t Board::GetShipAmount(size_t size) { return ships_count_[size]; }

void Board::SetShipAmount(size_t size, uint64_t count) {
  ships_count_[size] = count;
}

uint64_t Board::GetShipAmount() { return ship_amount_; }

void Board::SetShipAmount(uint64_t count) { ship_amount_ = count; }

bool Board::AreShipAlive() { return !alive_ship_coordinates_.empty(); }
} // namespace GameField
