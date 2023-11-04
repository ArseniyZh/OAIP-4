#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <map>

class Ship {
public:
    int width;
    int height;

    Ship(int w, int h) : width(w), height(h) {}
};

std::vector<std::vector<int>> createField() {
    int m, n;
    std::cin >> m >> n;

    std::vector<std::vector<int>> field;

    for (int i = 0; i < m; ++i) {
        std::string row;
        std::cin >> row;

        std::vector<int> rowValues;
        for (char c : row) {
            rowValues.push_back(c - '0');
        }

        field.push_back(rowValues);
    }

    return field;
}

std::vector<Ship> findShips(std::vector<std::vector<int>>& field) {
    std::vector<Ship> ships;

    while (true) {
        bool found = false;

        for (int i = 0; i < field.size(); ++i) {
            for (int j = 0; j < field[i].size(); ++j) {
                if (field[i][j] == 1) {
                    found = true;

                    int width = 0, height = 0;
                    for (int x = i; x < field.size() && field[x][j] == 1; ++x) {
                        height++;
                        for (int y = j; y < field[x].size() && field[x][y] == 1; ++y) {
                            field[x][y] = 0;
                            width = y - j + 1;
                        }
                    }

                    ships.push_back(Ship(width, height));
                    if (width + height != 2) {
                        ships.push_back(Ship(height, width));
                    }
                }
            }
        }

        if (!found) {
            break;
        }
    }

    return ships;
}

int main() {
    std::vector<std::vector<int>> field = createField();
    std::vector<Ship> ships = findShips(field);
    std::map<std::pair<int, int>, int> shipsDict;

    for (const Ship ship : ships) {
        std::pair<int, int> key(ship.width, ship.height);
        shipsDict[key] = shipsDict[key] + 1;
    }

    for (const auto item : shipsDict) {
        const std::pair<int, int> key = item.first;
        int count = item.second;

        if (key.first >= key.second) {
            std::cout << key.first << " " << key.second << " " << count << std::endl;
        }
    }

    return 0;
}
