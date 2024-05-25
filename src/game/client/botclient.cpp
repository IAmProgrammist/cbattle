#include <game/client/botclient.h>

#include <random>
#include <QDebug>

Suspicion::Suspicion() {}
Suspicion::Suspicion(int x, int y, Direction where) : x(x), y(y), where(where) {}

BotGameClient::BotGameClient() : GameClient() {
}

BotGameClient::~BotGameClient() {}

void BotGameClient::on_update(Game g) {
    this->game = g;
    if (g.game_over) return;
    if (!g.youre_going) {
        prev_step_mine = false;
        return;
    }

    if (prev_step_mine && prev_suspicion.where != UNKNOWN) {
        Suspicion sus;
        sus.where = prev_suspicion.where;
        sus.x = prev_suspicion.x + (sus.where == LEFT ? -1 : sus.where == RIGHT ? 1 : 0);
        sus.y = prev_suspicion.y + (sus.where == UP ? -1 : sus.where == DOWN ? 1 : 0);

        this->suspicions.push(sus);
    } else if (prev_step_mine) {
        std::vector<Suspicion> suses = {
            Suspicion(prev_x - 1, prev_y, LEFT),
            Suspicion(prev_x + 1, prev_y, RIGHT),
            Suspicion(prev_x, prev_y + 1, UP),
            Suspicion(prev_x, prev_y - 1, DOWN)
        };
        std::random_shuffle(suses.begin(), suses.end());
        for (auto& sus : suses) {
            this->suspicions.push(sus);
        }
    }

    if (!this->suspicions.empty()) {
        auto sus = suspicions.top();
        suspicions.pop();
        prev_suspicion = sus;
        prev_x = sus.x;
        prev_y = sus.y;

        prev_step_mine = true;
        this->on_step(sus.x, sus.y);

        return;
    }

    while (true) {
        static auto dev = std::random_device();
        static auto gen = std::mt19937{dev()};
        static auto dist = std::uniform_int_distribution(0, GAME_SIZE - 1);

        int y = dist(gen), x = dist(gen);
        if (g.enemy_field.field[y][x] == FieldElement::NOT_CHECKED) {
            prev_step_mine = true;
            prev_x = x;
            prev_y = y;
            prev_suspicion = Suspicion();

            this->on_step(x, y);

            return;
        }
    }
}

void BotGameClient::on_error(ErrorCode error) {
    switch (error) {
    case BAD_HANDSHAKE:
        break;
    case BAD_STEP:
        prev_step_mine = false;
        on_update(this->game);
        break;
    case NO_HANDSHAKE:
        init();
        break;
    case ALREADY_HANDSHAKE:
        break;
    }
}

void BotGameClient::init() {
    auto data = Field::generate_random();
    this->on_handshake(data.ships);
}
