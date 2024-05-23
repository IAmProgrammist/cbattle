#include <models/field.h>

#include <random>

#include <models/ship.h>

Field Field::generate_random() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_game_size(0, GAME_SIZE - 1);
    std::uniform_int_distribution<std::mt19937::result_type> dist_bool(0, 1);
    Field result;

    while (1) {
        bool should_keep_going = true;
        result.ships.clear();
        for (int i = 0; i < ONE_SHIP && should_keep_going; i++) {
            result.ships.push_back(Ship(dist_bool(rng) == 1 ? true : false,
                                        1,
                                        dist_game_size(rng), dist_game_size(rng)));

            if (!result.validate_ships()) should_keep_going = false;;
        }

        for (int i = 0; i < TWO_SHIP && should_keep_going; i++) {
            result.ships.push_back(Ship(dist_bool(rng) == 1 ? true : false,
                                        2,
                                        dist_game_size(rng), dist_game_size(rng)));

            if (!result.validate_ships()) should_keep_going = false;
        }

        for (int i = 0; i < THREE_SHIP && should_keep_going; i++) {
            result.ships.push_back(Ship(dist_bool(rng) == 1 ? true : false,
                                        3,
                                        dist_game_size(rng), dist_game_size(rng)));

            if (!result.validate_ships()) should_keep_going = false;
        }

        for (int i = 0; i < FOUR_SHIP && should_keep_going; i++) {
            result.ships.push_back(Ship(dist_bool(rng) == 1 ? true : false,
                                        4,
                                        dist_game_size(rng), dist_game_size(rng)));

            if (!result.validate_ships()) should_keep_going = false;
        }

        if (should_keep_going) break;
    }


    return result;
}

bool Field::validate_ships() {
    std::vector<std::vector<int>> test_field(GAME_SIZE, std::vector(GAME_SIZE, 0));

    for (auto& ship : ships) {
        if (ship.is_horizontal) {
            if (!are_in_bounds(ship.y)) return false;

            for (int x = ship.x; x < ship.x + ship.length; x++) {
                if (!are_in_bounds(x)) return false;

                if (test_field[ship.y][x] != 0) return false;
                test_field[ship.y][x] = 2;

                if (are_in_bounds(ship.y - 1) && are_in_bounds(x)) test_field[ship.y - 1][x] = 1;
                if (are_in_bounds(ship.y + 1) && are_in_bounds(x)) test_field[ship.y + 1][x] = 1;
                if (are_in_bounds(ship.y - 1) && are_in_bounds(x - 1)) test_field[ship.y - 1][x- 1] = 1;
                if (are_in_bounds(ship.y - 1) && are_in_bounds(x + 1)) test_field[ship.y - 1][x + 1] = 1;
                if (are_in_bounds(ship.y + 1) && are_in_bounds(x + 1)) test_field[ship.y + 1][x + 1] = 1;
                if (are_in_bounds(ship.y + 1) && are_in_bounds(x - 1)) test_field[ship.y + 1][x - 1] = 1;
            }

            if (are_in_bounds(ship.y) && are_in_bounds(ship.x - 1)) test_field[ship.y][ship.x - 1] = 1;
            if (are_in_bounds(ship.y) && are_in_bounds(ship.x + ship.length)) test_field[ship.y][ship.x + ship.length] = 1;
        } else {
            if (!are_in_bounds(ship.x)) return false;

            for (int y = ship.y; y < ship.y + ship.length; y++) {
                if (!are_in_bounds(y)) return false;

                if (test_field[y][ship.x] != 0) return false;
                test_field[y][ship.x] = 2;

                if (are_in_bounds(y) && are_in_bounds(ship.x + 1)) test_field[y][ship.x + 1] = 1;
                if (are_in_bounds(y) && are_in_bounds(ship.x - 1)) test_field[y][ship.x - 1] = 1;
                if (are_in_bounds(y - 1) && are_in_bounds(ship.x - 1)) test_field[y - 1][ship.x- 1] = 1;
                if (are_in_bounds(y - 1) && are_in_bounds(ship.x + 1)) test_field[y - 1][ship.x + 1] = 1;
                if (are_in_bounds(y + 1) && are_in_bounds(ship.x + 1)) test_field[y + 1][ship.x + 1] = 1;
                if (are_in_bounds(y + 1) && are_in_bounds(ship.x - 1)) test_field[y + 1][ship.x - 1] = 1;
            }

            if (are_in_bounds(ship.y - 1) && are_in_bounds(ship.x)) test_field[ship.y - 1][ship.x] = 1;
            if (are_in_bounds(ship.y + ship.length) && are_in_bounds(ship.x)) test_field[ship.y + ship.length][ship.x] = 1;
        }
    }

    return true;
}
