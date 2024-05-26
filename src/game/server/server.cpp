#include <game/server/connection.h>
#include <algorithm>
#include <game/server/server.h>

#include <random>

#include <models/game.h>

GameServer::GameServer() {
    static auto dev = std::random_device();
    static auto gen = std::mt19937{dev()};
    static auto dist = std::uniform_int_distribution(0,1);
    this->going_one = dist(gen) == 0;
}

GameServer::~GameServer() {
    delete this->player_one;
    delete this->player_two;
}

void GameServer::on_handshake(ServerConnection* player, std::vector<Ship> ships) {
    bool was = this->player_one_validated && this->player_two_validated;
    if (was) return player->send_error(ALREADY_HANDSHAKE);

    if (this->player_one == player) {
        if (this->player_one_validated) return player->send_error(ALREADY_HANDSHAKE);

        this->player_one_field.ships = ships;
        if (this->player_one_field.validate_ships())
            this->player_one_validated = true;
        else
            return player->send_error(BAD_HANDSHAKE);
    }

    if (this->player_two == player) {
        if (this->player_two_validated) return player->send_error(ALREADY_HANDSHAKE);

        this->player_two_field.ships = ships;
        if (this->player_two_field.validate_ships())
            this->player_two_validated = true;
        else
            return player->send_error(BAD_HANDSHAKE);
    }

    if (!was && this->player_one_validated && this->player_two_validated) {
        send_update();
    }
}

void GameServer::on_step(ServerConnection* player, int xx, int yy) {
    if (game_over) return;
    if (player == player_one && !this->player_one_validated) return player->send_error(ErrorCode::NO_HANDSHAKE);
    if (player == player_two && !this->player_two_validated) return player->send_error(ErrorCode::NO_HANDSHAKE);

    if (!Field::are_in_bounds(xx) || !Field::are_in_bounds(yy)) return player->send_error(ErrorCode::BAD_STEP);
    Field* selected_field = &player_one_field;
    bool selected = false;

    if (player == player_one && going_one) {
        selected_field = &player_two_field;
        selected = true;
    } else if (player == player_two && !going_one) {
        selected = true;
    }

    if (!selected) return player->send_error(ErrorCode::BAD_STEP);

    if (selected_field->field[yy][xx] != FieldElement::NOT_CHECKED)
        return player->send_error(ErrorCode::BAD_STEP);

    for (auto& ship : selected_field->ships) {
        if (ship.is_horizontal) {
            for (int x = ship.x; x < ship.x + ship.length; x++) {
                if (ship.y != yy || x != xx) continue;

                selected_field->field[yy][xx] = FieldElement::EXPOLSION_CHECKED;
                if (is_covered(*selected_field, ship))
                    cover_ship(*selected_field, ship);

                check_game_over();
                send_update();
                return;
            }
        } else {
            for (int y = ship.y; y < ship.y + ship.length; y++) {
                if (y != yy || ship.x != xx) continue;

                selected_field->field[yy][xx] = FieldElement::EXPOLSION_CHECKED;
                if (is_covered(*selected_field, ship))
                    cover_ship(*selected_field, ship);

                check_game_over();
                send_update();
                return;
            }
        }
    }

    selected_field->field[yy][xx] = FieldElement::EMPTY_CHECKED;
    going_one = !going_one;
    send_update();
}

void GameServer::on_surrender(ServerConnection* player) {
    if (game_over) return;
    if (player == player_one && !this->player_one_validated) return player->send_error(ErrorCode::NO_HANDSHAKE);
    if (player == player_two && !this->player_two_validated) return player->send_error(ErrorCode::NO_HANDSHAKE);

    if (player == player_one) {
        this->game_over = true;
        this->winning_reason = SURRENDER;
        this->player_one_won = false;

        send_update();
    } else if (player == player_two) {
        this->game_over = true;
        this->winning_reason = SURRENDER;
        this->player_one_won = true;

        send_update();
    }
}

void GameServer::check_game_over() {
    if (game_over || !this->player_one_validated || !this->player_two_validated) return;

    bool all_player_one = true;
    for (auto& ship : this->player_one_field.ships) {
        if (!is_covered(this->player_one_field, ship)) {
            all_player_one = false;
            break;
        }
    }

    if (all_player_one) {
        this->game_over = true;
        this->player_one_won = false;
        this->winning_reason = FAIR;

        return;
    }

    bool all_player_two = true;
    for (auto& ship : this->player_two_field.ships) {
        if (!is_covered(this->player_two_field, ship)) {
            all_player_two = false;
            break;
        }
    }

    if (all_player_two) {
        this->game_over = true;
        this->player_one_won = true;
        this->winning_reason = FAIR;
    }
}

void GameServer::send_update() {
    Game p1_game;
    p1_game.reason = this->winning_reason;
    p1_game.youre_going = going_one;
    p1_game.own_field = player_one_field;
    p1_game.enemy_field = player_two_field;
    p1_game.enemy_field.ships.clear();
    std::copy_if(player_two_field.ships.begin(), player_two_field.ships.end(),
                 std::back_inserter(p1_game.enemy_field.ships),
                 [&](Ship sh){return is_covered(player_two_field, sh);});
    p1_game.game_over = this->game_over;
    p1_game.youre_winner = this->player_one_won;

    player_one->send_update(p1_game);

    Game p2_game;
    p2_game.reason = this->winning_reason;
    p2_game.youre_going = !going_one;
    p2_game.own_field = player_two_field;
    p2_game.enemy_field = player_one_field;
    p2_game.enemy_field.ships.clear();
    std::copy_if(player_one_field.ships.begin(), player_one_field.ships.end(),
                 std::back_inserter(p2_game.enemy_field.ships),
                 [&](Ship sh){return is_covered(player_one_field, sh);});
    p2_game.game_over = this->game_over;
    p2_game.youre_winner = !this->player_one_won;

    player_two->send_update(p2_game);
}

bool GameServer::is_covered(Field& field, Ship& ship) {
    if (ship.is_horizontal) {
        for (int x = ship.x; x < ship.x + ship.length; x++)
            if (field.field[ship.y][x] != FieldElement::EXPOLSION_CHECKED) return false;
    } else {
        for (int y = ship.y; y < ship.y + ship.length; y++)
            if (field.field[y][ship.x] != FieldElement::EXPOLSION_CHECKED) return false;
    }

    return true;
}

void GameServer::cover_ship(Field& field, Ship& ship) {
    if (ship.is_horizontal) {
        for (int x = ship.x; x < ship.x + ship.length; x++) {
            if (Field::are_in_bounds(ship.y - 1) && Field::are_in_bounds(x)) field.field[ship.y - 1][x] = FieldElement::EMPTY_CHECKED;
            if (Field::are_in_bounds(ship.y + 1) && Field::are_in_bounds(x)) field.field[ship.y + 1][x] = FieldElement::EMPTY_CHECKED;
            if (Field::are_in_bounds(ship.y - 1) && Field::are_in_bounds(x - 1)) field.field[ship.y - 1][x- 1] = FieldElement::EMPTY_CHECKED;
            if (Field::are_in_bounds(ship.y - 1) && Field::are_in_bounds(x + 1)) field.field[ship.y - 1][x + 1] = FieldElement::EMPTY_CHECKED;
            if (Field::are_in_bounds(ship.y + 1) && Field::are_in_bounds(x + 1)) field.field[ship.y + 1][x + 1] = FieldElement::EMPTY_CHECKED;
            if (Field::are_in_bounds(ship.y + 1) && Field::are_in_bounds(x - 1)) field.field[ship.y + 1][x - 1] = FieldElement::EMPTY_CHECKED;
        }

        if (Field::are_in_bounds(ship.y) && Field::are_in_bounds(ship.x - 1)) field.field[ship.y][ship.x - 1] = FieldElement::EMPTY_CHECKED;
        if (Field::are_in_bounds(ship.y) && Field::are_in_bounds(ship.x + ship.length)) field.field[ship.y][ship.x + ship.length] = FieldElement::EMPTY_CHECKED;
    } else {
        for (int y = ship.y; y < ship.y + ship.length; y++) {
            if (Field::are_in_bounds(y) && Field::are_in_bounds(ship.x + 1)) field.field[y][ship.x + 1] = FieldElement::EMPTY_CHECKED;
            if (Field::are_in_bounds(y) && Field::are_in_bounds(ship.x - 1)) field.field[y][ship.x - 1] = FieldElement::EMPTY_CHECKED;
            if (Field::are_in_bounds(y - 1) && Field::are_in_bounds(ship.x - 1)) field.field[y - 1][ship.x- 1] = FieldElement::EMPTY_CHECKED;
            if (Field::are_in_bounds(y - 1) && Field::are_in_bounds(ship.x + 1)) field.field[y - 1][ship.x + 1] = FieldElement::EMPTY_CHECKED;
            if (Field::are_in_bounds(y + 1) && Field::are_in_bounds(ship.x + 1)) field.field[y + 1][ship.x + 1] = FieldElement::EMPTY_CHECKED;
            if (Field::are_in_bounds(y + 1) && Field::are_in_bounds(ship.x - 1)) field.field[y + 1][ship.x - 1] = FieldElement::EMPTY_CHECKED;
        }

        if (Field::are_in_bounds(ship.y - 1) && Field::are_in_bounds(ship.x)) field.field[ship.y - 1][ship.x] = FieldElement::EMPTY_CHECKED;
        if (Field::are_in_bounds(ship.y + ship.length) && Field::are_in_bounds(ship.x)) field.field[ship.y + ship.length][ship.x] = FieldElement::EMPTY_CHECKED;
    }
}
