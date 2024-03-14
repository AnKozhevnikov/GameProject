#include "Randomizer.h"
#include "Cell.h"
#include "NewEventListenerInfo.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <random>
#include <tuple>

using namespace std;
using Coordinates = pair<int, int>;
using AdjacencyMap = map<Coordinates, map<Coordinates, bool> >;

class DungeonGraph {
private:
    AdjacencyMap graph;

public:
    void addDungeon(const Coordinates& dungeon) {
        graph[dungeon];
    }

    void addPath(const Coordinates& from, const Coordinates& to, bool exists) {
        graph[from][to] = exists;
        graph[to][from] = exists;
    }

    bool hasPath(const Coordinates& from, const Coordinates& to) {
        if (graph.find(from) != graph.end() && graph[from].find(to) != graph[from].end()) {
            return graph[from][to];
        }
        return false;
    }

    bool dungeonExists(const Coordinates& dungeon) {
        return graph.find(dungeon) != graph.end();
    }

    int countPathsFromDungeon(const Coordinates& dungeon) {
        int count = 0;
        if (graph.find(dungeon) != graph.end()) {
            for (const auto& path : graph[dungeon]) {
                if (path.second) {
                    count++;
                }
            }
        }
        return count;
    }

    void printGraph() {
        for (const auto& node : graph) {
            std::cout << "Dungeon at (" << node.first.first << ", " << node.first.second << ") has paths to: ";
            for (const auto& edge : node.second) {
                if (edge.second) {
                    std::cout << "(" << edge.first.first << ", " << edge.first.second << ") ";
                }
            }
            std::cout << std::endl;
        }
    }
};

namespace DungeonGenerator {
void drawRoad(vector<vector<int> >& field,  Coordinates startDungeon, Coordinates endDungeon) {
    if (startDungeon.first != endDungeon.first) {
        int xIncrement = startDungeon.first < endDungeon.first ? 1 : -1;
        for (int x = startDungeon.first + 2 * xIncrement; x != (endDungeon.first - xIncrement); x += xIncrement) {
            field[x][startDungeon.second] = 2;
        }
    } else if (startDungeon.second != endDungeon.second) {
        int yIncrement = startDungeon.second < endDungeon.second ? 1 : -1;
        for (int y = startDungeon.second + 2 * yIncrement; y != (endDungeon.second - yIncrement); y += yIncrement) {
            field[startDungeon.first][y] = 2;
        }
    }
}

std::pair<std::vector<std::vector<Cell>>, std::pair<int, int>> generateDungeons(int height, int width, int count,  int shift_distance=8) {
    vector<vector<int> > field(height, vector<int>(width, 0));

    vector<Coordinates> potentialPositions;
    vector<Coordinates> directions;
    Coordinates newDungeon;
    DungeonGraph dg;

    directions.push_back(make_pair(0, shift_distance));
    directions.push_back(make_pair(shift_distance, 0));
    directions.push_back(make_pair(0, -shift_distance));
    directions.push_back(make_pair(-shift_distance, 0));

    int firstX = Randomizer::getRandom(height / 3) + height / 3;
    int firstY = Randomizer::getRandom(width / 3) + width / 3;

    Coordinates startDungeon = make_pair(firstX, firstY);

    for (int X = firstX - 1; X <= firstX + 1; ++X) {
        for (int Y = firstY - 1; Y <= firstY + 1; ++Y) {
            field[X][Y] = 3;
        }
    }
    field[firstX][firstY] = 1;

    dg.addDungeon(startDungeon);

    for (auto& dir : directions) {
        int newX = firstX + dir.first;
        int newY = firstY + dir.second;

        newDungeon = make_pair(newX, newY);
        potentialPositions.push_back(newDungeon);
        dg.addDungeon(newDungeon);
        dg.addPath(startDungeon, newDungeon, true);
        drawRoad(field, startDungeon, newDungeon);

        for (int X = newX - 1; X <= newX + 1; ++X) {
            for (int Y = newY - 1; Y <= newY + 1; ++Y) {
                field[X][Y] = 3;
            }
        }
        field[newX][newY] = 1;

        count--;
    }

    while (count > 1 && !potentialPositions.empty()) {
        int posIndex = Randomizer::getRandom(potentialPositions.size());
        auto& pos = potentialPositions[posIndex];
        bool placed = false;

        Randomizer::randomShuffle(directions);

        for (auto& dir : directions) {

            int k = !Randomizer::getRandom(7) ? 2 : 1;
            int newX = pos.first + dir.first * k;
            int newY = pos.second + dir.second * k;

            newDungeon = make_pair(newX, newY);
            
            if (newX >= 1 && newX < (height - 1) && newY >= 1 && newY < (width - 1) && !dg.hasPath(pos, newDungeon) && dg.countPathsFromDungeon(newDungeon) <= (Randomizer::getRandom(2) + 1) && dg.countPathsFromDungeon(pos) <= (Randomizer::getRandom(2) + 1) && field[newX][newY] != 2 && field[newX - (k / 2) * dir.first][newY - (k / 2) * dir.second] != 2 && !(k == 2 && field[newX - dir.first][newY - dir.second] == 1)) {
                drawRoad(field, pos, newDungeon);
                dg.addPath(pos, newDungeon, true);

                if (field[newX][newY] == 0) {
                    for (int X = newX - 1; X <= newX + 1; ++X) {
                        for (int Y = newY - 1; Y <= newY + 1; ++Y) {
                            field[X][Y] = 3;
                        }
                    }
                    field[newX][newY] = 1;
                    potentialPositions.push_back(newDungeon);
                    dg.addDungeon(newDungeon);
                    dg.addPath(pos, newDungeon, true);
                    placed = true;
                    count--;
                    break;
                }
            }
        }

        if (dg.countPathsFromDungeon(pos) > 2 || !placed) {
            potentialPositions.erase(potentialPositions.begin() + posIndex);
        }
    }

    std::vector<std::vector<Cell>> cells(height, std::vector<Cell>(width));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (field[i][j] == 0) {
                cells[i][j] = Cell(NewEventListenerInfo(), "void");
            }
            else if (field[i][j] == 1) {
                cells[i][j] = Cell(NewEventListenerInfo(), "room");
            }
            else if (field[i][j] == 2) {
                cells[i][j] = Cell(NewEventListenerInfo(), "corridor");
            }
            else if (field[i][j] == 3) {
                cells[i][j] = Cell(NewEventListenerInfo(), "roomborder");
            }
        }
    }

    return make_pair(cells, startDungeon);
}
}