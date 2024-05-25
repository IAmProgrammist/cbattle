#pragma once

#include <game/client/client.h>
#include <models/field.h>
#include <QDebug>
#include <random>

class BotGameClient : public GameClient {
public:
    BotGameClient() : GameClient() {
    }

    void on_update(Game g) {
        if (!g.youre_going) return;

        while (true) {
            static auto dev = std::random_device();
            static auto gen = std::mt19937{dev()};
            static auto dist = std::uniform_int_distribution(0, GAME_SIZE - 1);

            int y = dist(gen), x = dist(gen);
            if (g.enemy_field.field[y][x] == FieldElement::NOT_CHECKED) {
                this->on_step(x, y);
                break;
            }
        }
    }

    void init() {
        auto data = Field::generate_random();
        this->on_handshake(data.ships);
    }
};
