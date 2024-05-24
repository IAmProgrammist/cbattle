#include "game/server/connection.h"
#include <future>
#include <game/server/server.h>

#include <random>

#include <models/game.h>

GameServer::GameServer() {
    static auto dev = std::random_device();
    static auto gen = std::mt19937{dev()};
    static auto dist = std::uniform_int_distribution(0,1);
    this->going_one = dist(gen) == 0;
}

void GameServer::on_handshake(ServerConnection* player, std::vector<Ship> ships) {
    bool was = this->player_one_validated && this->player_two_validated;
    if (was) return;

    if (this->player_one == player) {
        if (this->player_one_validated) return;

        this->player_one_field.ships = ships;
        if (this->player_one_field.validate_ships())
            this->player_one_validated = true;
    }

    if (this->player_two == player) {
        if (this->player_two_validated) return;

        this->player_two_field.ships = ships;
        if (this->player_two_field.validate_ships())
            this->player_two_validated = true;
    }

    if (!was && this->player_one_validated && this->player_two_validated) {
        send_update();
    }
}

void GameServer::on_step(ServerConnection* player, int xx, int yy) {
    if (player == player_one && !this->player_one_validated) return;
    if (player == player_two && !this->player_two_validated) return;

    if (!Field::are_in_bounds(xx) || !Field::are_in_bounds(yy)) return;
    Field* selected_field = &player_one_field;
    bool selected = false;

    if (player == player_one && going_one) {
        selected = true;
    } else if (player == player_two && !going_one) {
        selected_field = &player_two_field;
        selected = true;
    }

    if (!selected) return;

    if (selected_field->field[yy][xx] != FieldElement::NOT_CHECKED)
        return;

    for (auto& ship : selected_field->ships) {
        if (ship.is_horizontal) {
            for (int x = ship.x; x < ship.x + ship.length; x++) {
                if (ship.y != yy || x != xx) continue;

                selected_field->field[yy][xx] = FieldElement::EXPOLSION_CHECKED;
                if (is_covered(*selected_field, ship))
                    cover_ship(*selected_field, ship);

                send_update();
                return;
            }
        } else {
            for (int y = ship.y; y < ship.y + ship.length; y++) {
                if (y != yy || ship.x != xx) continue;

                player_one_field.field[yy][xx] = FieldElement::EXPOLSION_CHECKED;
                if (is_covered(*selected_field, ship))
                    cover_ship(*selected_field, ship);

                send_update();
                return;
            }
        }
    }

    selected_field->field[yy][xx] = FieldElement::EMPTY_CHECKED;
    going_one = !going_one;
    send_update();
}

void GameServer::send_update() {
    Game p1_game;
    p1_game.youre_going = going_one;
    p1_game.own_field = player_one_field;
    p1_game.enemy_field = player_two_field;

    player_one->send_update(p1_game);

    Game p2_game;
    p2_game.youre_going = !going_one;
    p2_game.own_field = player_two_field;
    p2_game.enemy_field = player_one_field;

    player_two->send_update(p2_game);
}

bool GameServer::is_covered(Field& field, Ship& ship) {
    if (ship.is_horizontal)
        for (int x = ship.x; x < ship.x + ship.length; x++)
            if (field.field[ship.y][x] != FieldElement::EXPOLSION_CHECKED) return false;
    else
        for (int y = ship.y; y < ship.y + ship.length; y++)
            if (field.field[y][ship.x] != FieldElement::EXPOLSION_CHECKED) return false;

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
