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

#include "BattleEventListenerInfo.h"
#include "TrapEventListenerInfo.h"
#include "ChestEventListenerInfo.h"
#include "AltarEventListenerInfo.h"
#include "ReviveEventListenerInfo.h"
#include "NpcEventListenerInfo.h"

using namespace std;

struct Coordinate {
    int x, y;

    Coordinate () {};

    Coordinate (const int x_, const int y_) {
        x = x_;
        y = y_;
    }

    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Coordinate& other) const {
        return !(*this == other);
    }
    
    Coordinate operator+(const Coordinate& other) const {
        return Coordinate(x + other.x, y + other.y);
    }

    Coordinate operator-(const Coordinate& other) const {
        return Coordinate(x - other.x, y - other.y);
    }

    bool operator<(const Coordinate& other) const {
        return x == other.x ? y < other.y : x < other.x;
    }

    friend ostream& operator<<(ostream& os, const Coordinate& point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }
};

using AdjacencyMap = map<Coordinate, map<Coordinate, pair<bool, vector<Coordinate> > > >;

struct Rectangle {
    Coordinate topLeft, bottomRight;
};

class DungeonGraph {
private:
    AdjacencyMap graph;

    bool isConnectedWithoutPoint(const Coordinate& exclude) {
        if (graph.empty()) return false;

        map<Coordinate, bool> visited;
        Coordinate start = graph.begin()->first;
        if (start == exclude) {
            start = (++graph.begin())->first;
        }

        int visitedCount = 0;
        dfs(start, exclude, visited, visitedCount);

        return visitedCount == (graph.size() - (exclude == start ? 0 : 1));
    }

    void dfs(Coordinate current, const Coordinate& exclude, map<Coordinate, bool>& visited, int& visitedCount) {
        if (current == exclude || visited[current]) return;
        visited[current] = true;
        visitedCount++;

        for (auto& neighbor : graph[current]) {
            if (!visited[neighbor.first] && neighbor.first != exclude && neighbor.second.first) {
                dfs(neighbor.first, exclude, visited, visitedCount);
            }
        }
    }

public:
    void addDungeon(const Coordinate& dungeon) {
        graph[dungeon];
    }

    void addPathExist(const Coordinate& from, const Coordinate& to, bool exists) {
        graph[from][to].first = exists;
        graph[to][from].first = exists;
    }

    void addPath(const Coordinate& from, const Coordinate& to, vector<Coordinate>& path) {
        graph[from][to].second = path;
        graph[to][from].second = path;
    }

    void addDrawnPath(const Coordinate& from, const Coordinate& to, vector<Coordinate> path) {
        graph[from][to].second = path;
        reverse(path.begin(), path.end());
        graph[to][from].second = path;
    }

    bool hasPath(const Coordinate& from, const Coordinate& to) {
        if (graph.find(from) != graph.end() && graph[from].find(to) != graph[from].end()) {
            return graph[from][to].first;
        }
        return false;
    }

    bool drawnPath(const Coordinate& from, const Coordinate& to) {
        return hasPath(from, to) && !(graph[from][to].second).empty();
    }

    bool dungeonExists(const Coordinate& dungeon) {
        return graph.find(dungeon) != graph.end();
    }

    int countPathsFromDungeon(const Coordinate& dungeon) {
        int count = 0;
        if (graph.find(dungeon) != graph.end()) {
            for (const auto& path : graph[dungeon]) {
                if (path.second.first) {
                    count++;
                }
            }
        }
        return count;
    }

    vector<Coordinate> getVertices(const AdjacencyMap& graph) {
        vector<Coordinate> vertices;
        for (const auto& node : graph) {
            vertices.push_back(node.first);
        }
        return vertices;
    }

    Coordinate findBossDungeon() {
        vector<Coordinate> vertices = Randomizer::randomShuffle(getVertices(graph));
        for (auto& vertice : vertices) {
            if (graph[vertice].size() < 4 && isConnectedWithoutPoint(vertice)) {
                return vertice;
            }
        }
        return Coordinate(-1, -1);
    }

    const AdjacencyMap& getGraph() const {
        return graph;
    }

    void printGraph() {
        for (const auto& node : graph) {
            std::cout << "Dungeon at (" << node.first.x << ", " << node.first.y << ") has paths to: ";
            for (const auto& edge : node.second) {
                if (edge.second.first) {
                    std::cout << "(" << edge.first.x << ", " << edge.first.y << ") ";
                }
            }
            std::cout << std::endl;
        }
    }
};

namespace DungeonGenerator {
bool isInBounds(const Coordinate& point, const Coordinate& topLeft, const Coordinate& bottomRight) {
    return point.x >= topLeft.x && point.x <= bottomRight.x &&
           point.y >= topLeft.y && point.y <= bottomRight.y;
}

bool isVisited(const Coordinate& point, const vector<Coordinate>& path) {
    for (const auto& p : path) {
        if (p == point) {
            return true;
        }
    }
    return false;
}

int distPoints(const Coordinate& p1, const Coordinate& p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

Coordinate selectNextStep(const Coordinate& current, const vector<Coordinate>& path, const Coordinate& topLeft, const Coordinate& bottomRight, const char direction) {
    Coordinate forwardMove;
    Coordinate leftMove;
    Coordinate rightMove;

    switch (direction) {
        case 'R':
        forwardMove = Coordinate(0, 1);
        leftMove = Coordinate(-1, 0);
        rightMove = Coordinate(1, 0);
        break;

        case 'L':
        forwardMove = Coordinate(0, -1);
        leftMove = Coordinate(1, 0);
        rightMove = Coordinate(-1, 0);
        break;

        case 'U':
        forwardMove = Coordinate(-1, 0);
        leftMove = Coordinate(0, -1);
        rightMove = Coordinate(0, 1);
        break;

        case 'D':
        forwardMove = Coordinate(1, 0);
        leftMove = Coordinate(0, 1);
        rightMove = Coordinate(0, -1);
        break;
        
        default:
            break;
    }

    Coordinate nextStep = current;
    Coordinate lastCell;
    bool pathSize = path.size() >= 3;

    if (path.size() >= 3) {
        lastCell = *(path.end() - 3);
    }

    do {
        int rand = Randomizer::getRandom(10);
        nextStep = current;

        if (rand <= 2) {
            nextStep = nextStep + leftMove;
        } else if (rand <= 5) {
            nextStep = nextStep +rightMove;
        } else {
            nextStep = nextStep + forwardMove;
        }

    } while (pathSize && distPoints(lastCell, nextStep) == 1 || !isInBounds(nextStep, topLeft, bottomRight));
    
    return nextStep;
}

void drawPathEvents(vector<vector<int> >& field, const vector<Coordinate>& path) {
    for (size_t i = 0; i < path.size(); ++i) {
        Coordinate current = path[i];
        int event = Randomizer::getRandom(100);

        if (event < 65) {
            field[current.x][current.y] = 2;
        } else if (event < 72){
            field[current.x][current.y] = 4;
        } else if (event < 79){
            field[current.x][current.y] = 8;
        } else if (event < 86){
            field[current.x][current.y] = 6;
        } else if (event < 93){
            field[current.x][current.y] = 10;
        } else {
            field[current.x][current.y] = 11;
        }
    }
}

void drawRoomEvents(vector<vector<int> >& field, DungeonGraph dg) {
    for (auto& dungeon : dg.getGraph()) {
        int event = Randomizer::getRandom(15);

        if (event < 4) {
            field[dungeon.first.x][dungeon.first.y] = 7;
        } else {
            field[dungeon.first.x][dungeon.first.y] = 9;
        }
    }

    Coordinate finalBoss = dg.findBossDungeon();
    field[finalBoss.x][finalBoss.y] = 5;
}

Rectangle getRectangleCoordinates(const Coordinate& cell1, const Coordinate& cell2) {
    Rectangle rect;
    if (cell1.y == cell2.y) {
        int minX = std::min(cell1.x, cell2.x);
        int maxX = std::max(cell1.x, cell2.x);

        rect.topLeft.x = minX;
        rect.topLeft.y = cell1.y - 0;
        rect.bottomRight.x = maxX;
        rect.bottomRight.y = cell1.y + 0;
    } else {
        int minY = std::min(cell1.y, cell2.y);
        int maxY = std::max(cell1.y, cell2.y);

        rect.topLeft.x = cell1.x - 0;
        rect.topLeft.y = minY;
        rect.bottomRight.x = cell1.x + 0;
        rect.bottomRight.y = maxY;
    }
    return rect;
}

vector<Coordinate> findPath(Coordinate start, Coordinate finish, Coordinate topLeft, Coordinate bottomRight, int maxLength) {
    Coordinate topRight = Coordinate(topLeft.x, bottomRight.y);
    Coordinate bottomLeft = Coordinate(bottomRight.x, topLeft.y);
    Coordinate finish_;
    vector<Coordinate> path;
    path.push_back(start);

    char direction;
    if (abs(start.x - finish.x) < abs(start.y - finish.y)) direction = start.y < finish.y ? 'R' : 'L';
    else direction = start.x < finish.x ? 'D' : 'U';

    switch (direction) {
    case 'R':
    path.push_back(start + Coordinate(0, 1));
    finish_ = finish - Coordinate(0, 1);
    break;

    case 'L':
    path.push_back(start + Coordinate(0, -1));
    finish_ = finish - Coordinate(0, -1);
    break;

    case 'U':
    path.push_back(start + Coordinate(-1, 0));
    finish_ = finish - Coordinate(-1, 0);
    break;

    case 'D':
    path.push_back(start + Coordinate(1, 0));
    finish_ = finish - Coordinate(1, 0);
    break;

    default:
        break;
    }
    
    while (path.size() < maxLength && path.back() != finish_) {
        Coordinate nextStep = selectNextStep(path.back(), path, topLeft, bottomRight, direction);
        if (isVisited(nextStep, path) || (nextStep == bottomRight) || (nextStep == topRight) || (nextStep == topLeft) || (nextStep == bottomLeft)) {
            break;
        }
        path.push_back(nextStep);
    }

    if (path.back() != finish_) return findPath(start, finish, topLeft, bottomRight, maxLength);

    path.push_back(finish);
    
    return path;
}

void drawSimplePath(vector<vector<int> >& field,  Coordinate startDungeon, Coordinate endDungeon) {
    if (startDungeon.x != endDungeon.x) {
        int xIncrement = startDungeon.x < endDungeon.x ? 1 : -1;
        for (int x = startDungeon.x + 2 * xIncrement; x != (endDungeon.x - xIncrement); x += xIncrement) {
            field[x][startDungeon.y] = 2;
        }
    } else if (startDungeon.y != endDungeon.y) {
        int yIncrement = startDungeon.y < endDungeon.y ? 1 : -1;
        for (int y = startDungeon.y + 2 * yIncrement; y != (endDungeon.y - yIncrement); y += yIncrement) {
            field[startDungeon.x][y] = 2;
        }
    }
}

std::shared_ptr<NewEventListenerInfo> generateEasyBattle(int depth) {
    return std::make_shared<NewEventListenerInfo>();
}

std::shared_ptr<NewEventListenerInfo> generateMediumBattle(int depth) {
    return std::make_shared<NewEventListenerInfo>();
}

std::shared_ptr<NewEventListenerInfo> generateBossBattle(int depth) {
    return std::make_shared<NewEventListenerInfo>();
}

std::shared_ptr<NewEventListenerInfo> generateTrap(int depth) {
    return std::make_shared<TrapEventListenerInfo>();
}

std::shared_ptr<NewEventListenerInfo> generateChest(int depth) {
    return std::make_shared<ChestEventListenerInfo>();
}

std::shared_ptr<NewEventListenerInfo> generateAltar(int depth) {
    return std::make_shared<AltarEventListenerInfo>();
}

std::shared_ptr<NewEventListenerInfo> generateRevive(int depth) {
    return std::make_shared<ReviveEventListenerInfo>();
}

pair<vector<vector<Cell>>, pair<int, int>> generateDungeons(int depth, int height, int width, int count,  int shift_distance=8) {
    vector<vector<int> > field(height, vector<int>(width, 0));

    vector<Coordinate> potentialPositions;
    vector<Coordinate> directions;
    Coordinate newDungeon;
    DungeonGraph dg;

    directions.push_back(Coordinate(0, shift_distance));
    directions.push_back(Coordinate(shift_distance, 0));
    directions.push_back(Coordinate(0, -shift_distance));
    directions.push_back(Coordinate(-shift_distance, 0));

    int firstX = Randomizer::getRandom(height / 3) + height / 3;
    int firstY = Randomizer::getRandom(width / 3) + width / 3;

    Coordinate startDungeon = Coordinate(firstX, firstY);

    for (int X = firstX - 1; X <= firstX + 1; ++X) {
        for (int Y = firstY - 1; Y <= firstY + 1; ++Y) {
            if (X == firstX && Y == firstY) field[X][Y] = 1;
            else field[X][Y] = 3;
        }
    }

    dg.addDungeon(startDungeon);

    for (auto& dir : directions) {
        int newX = firstX + dir.x;
        int newY = firstY + dir.y;

        newDungeon = Coordinate(newX, newY);
        potentialPositions.push_back(newDungeon);
        dg.addDungeon(newDungeon);
        dg.addPathExist(startDungeon, newDungeon, true);
        drawSimplePath(field, startDungeon, newDungeon);

        for (int X = newX - 1; X <= newX + 1; ++X) {
            for (int Y = newY - 1; Y <= newY + 1; ++Y) {
                if (X == newX && Y == newY) field[X][Y] = 1;
                else field[X][Y] = 3;
            }
        }

        count--;
    }

    while (count > 1 && !potentialPositions.empty()) {
        int posIndex = Randomizer::getRandom(potentialPositions.size());
        auto& pos = potentialPositions[posIndex];
        bool placed = false;

        for (auto& dir : Randomizer::randomShuffle(directions)) {

            int k = !Randomizer::getRandom(5) ? 2 : 1;
            int newX = pos.x + dir.x * k;
            int newY = pos.y + dir.y * k;

            newDungeon = Coordinate(newX, newY);
            
            if (newX >= 2 && newX < (height - 2) && newY >= 2 && newY < (width - 2) && !dg.hasPath(pos, newDungeon) && dg.countPathsFromDungeon(newDungeon) <= (Randomizer::getRandom(2) + 1) && dg.countPathsFromDungeon(pos) <= (Randomizer::getRandom(2) + 1) && field[newX][newY] != 2 && field[newX - (k / 2) * dir.x][newY - (k / 2) * dir.y] != 2 && !(k == 2 && field[newX - dir.x][newY - dir.y] == 1)) {
                drawSimplePath(field, pos, newDungeon);
                dg.addPathExist(pos, newDungeon, true);

                if (dg.countPathsFromDungeon(newDungeon) == 1) {
                    for (int X = newX - 1; X <= newX + 1; ++X) {
                        for (int Y = newY - 1; Y <= newY + 1; ++Y) {
                            if (X == newX && Y == newY) field[X][Y] = 1;
                            else field[X][Y] = 3;
                        }
                    }
                    potentialPositions.push_back(newDungeon);
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

    for (auto &row: field) {
        for (auto &item : row) {
            if (item == 2) {
                item = 0;
            }
        }
    }

    for (auto& fromNode : dg.getGraph()) {
        Coordinate fromDungeon = fromNode.first;
        for (auto& toNode : fromNode.second) {
            Coordinate toDungeon = toNode.first;
            Coordinate dirShift;

            if (fromDungeon.x == toDungeon.x) {
                dirShift = fromDungeon.y < toDungeon.y ? Coordinate(0, 2) : Coordinate(0, -2);
            } else {
                dirShift = fromDungeon.x < toDungeon.x ? Coordinate(2, 0) : Coordinate(-2, 0);
            }

            if (!dg.drawnPath(fromDungeon, toDungeon)) {
                Rectangle rect = getRectangleCoordinates(fromDungeon, toDungeon);
                vector<Coordinate> path = findPath(fromDungeon + dirShift, toDungeon - dirShift, rect.topLeft, rect.bottomRight, 2 * distPoints(fromDungeon + dirShift, toDungeon - dirShift));
                dg.addPath(fromDungeon, toDungeon, path);
                drawPathEvents(field, path);
            }
        }
    }

    drawRoomEvents(field, dg);
    field[firstX][firstY] = 1;

    vector<vector<Cell>> cells(height, vector<Cell>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (field[i][j] == 1) {
                cells[i][j] = Cell(std::make_shared<NewEventListenerInfo>(), "room", "void");
            } else if (field[i][j] == 2){
                cells[i][j] = Cell(std::make_shared<NewEventListenerInfo>(), "corridor", "void");
            } else if (field[i][j] == 3){
                cells[i][j] = Cell(std::make_shared<NewEventListenerInfo>(), "roomborder", "void");
            } else if (field[i][j] == 4){
                cells[i][j] = Cell(generateChest(depth), "corridor", "chest");
            } else if (field[i][j] == 5){
                cells[i][j] = Cell(generateBossBattle(depth), "room", "boss battle");
            } else if (field[i][j] == 6){
                cells[i][j] = Cell(generateTrap(depth), "corridor", "trap");
            } else if (field[i][j] == 7){
                cells[i][j] = Cell(generateAltar(depth), "room", "altar");
            } else if (field[i][j] == 8){
                cells[i][j] = Cell(generateMediumBattle(depth), "corridor", "battle");
            } else if (field[i][j] == 9){
                cells[i][j] = Cell(generateEasyBattle(depth), "room", "battle");
            } else if (field[i][j] == 10){
                cells[i][j] = Cell(generateRevive(depth), "corridor", "revive");
            } else if (field[i][j] == 11){
                cells[i][j] = Cell(generateRevive(depth), "corridor", "npc");
            } else {
                cells[i][j] = Cell(std::make_shared<NewEventListenerInfo>(), "void", "void");
            }
        }
    }

    return make_pair(cells, make_pair(firstX, firstY));
}
}