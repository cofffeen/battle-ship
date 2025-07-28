#include <lib/game.h>

#include <cinttypes>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

void ParseCommands() {
  GameField::Game *game;

  while (true) {
    std::string cmd;
    std::getline(std::cin, cmd);

    std::vector<std::string> cmd_splitted = SplitString(cmd);

    if (cmd_splitted[0] == "exit") {
      std::cout << "ok" << std::endl;
      return;
    } else if (cmd_splitted[0] == "ping") {
      std::cout << "pong" << std::endl;
    } else if (cmd_splitted[0] == "create") {
      if (cmd_splitted[1] == "master") {
        game = new GameField::MasterGame();
        game->SetParameters();
      } else {
        game = new GameField::SlaveGame();
      }

      std::cout << "ok" << std::endl;
    } else if (cmd_splitted[0] == "start") {
      game->Start();
      std::cout << "ok" << std::endl;
    } else if (cmd_splitted[0] == "stop") {
      game->Stop();
      std::cout << "ok" << std::endl;
    } else if (cmd_splitted[0] == "set") {
      bool is_setted_ok = false;
      if (cmd_splitted[1] == "width") {
        is_setted_ok = game->SetWidth(std::stoull(cmd_splitted[2]));
      } else if (cmd_splitted[1] == "height") {
        is_setted_ok = game->SetHeight(std::stoull(cmd_splitted[2]));
      } else if (cmd_splitted[1] == "count") {
        is_setted_ok = game->SetShipsCount(std::stoi(cmd_splitted[2]),
                                           std::stoull(cmd_splitted[3]));
      } else if (cmd_splitted[1] == "strategy") {
        is_setted_ok = game->SetStrategy(cmd_splitted[2]);
      } else if (cmd_splitted[1] == "result") {
        is_setted_ok = game->SetShotResult(cmd_splitted[2]);
      }

      if (is_setted_ok) {
        std::cout << "ok" << std::endl;
      } else {
        std::cout << "failed" << std::endl;
      }

    } else if (cmd_splitted[0] == "get") {
      if (cmd_splitted[1] == "width") {
        std::cout << game->GetWidth() << std::endl;
      } else if (cmd_splitted[1] == "height") {
        std::cout << game->GetHeight() << std::endl;
      } else if (cmd_splitted[1] == "count") {
        std::cout << game->GetShipsCount(std::stoi(cmd_splitted[2]))
                  << std::endl;
      }

    } else if (cmd == "shot") {
      std::cout << game->GetNextShot() << std::endl;
    } else if (cmd_splitted[0] == "shot") {
      std::cout << game->GetDamage({std::stoull(cmd_splitted[1]),
                                    std::stoull(cmd_splitted[2])})
                << std::endl;
    } else if (cmd == "finished") {
      std::cout << game->IsGameFinished() << std::endl;
    } else if (cmd == "win") {
      std::cout << game->IsWin() << std::endl;
    } else if (cmd == "lose") {
      std::cout << game->IsLose() << std::endl;
    } else if (cmd_splitted[0] == "dump") {
      game->DumpBoard(cmd_splitted[1]);
      std::cout << "ok" << std::endl;
    } else if (cmd_splitted[0] == "load") {
      game->LoadBoard(cmd_splitted[1]);
      std::cout << "ok" << std::endl;
    }
  }
}

int main() {
  ParseCommands();

  return 0;
}