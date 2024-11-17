#include "Game.h"

int main() {
    Game game;

    while (game.running()) {
        game.updateGame();
        game.render();
    }
    return 0;
}