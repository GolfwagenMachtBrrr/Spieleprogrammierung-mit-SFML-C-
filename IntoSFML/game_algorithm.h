#pragma once
#include "SFML/Graphics.hpp"

#include <queue>
#include <stack>
#include <vector>
#include <set>

#include <iostream>

#include "Tile.h"
#include "MapGenerator.h"

struct Cell
{
    Cell(){}
    Cell(int row, int column) : coordinateX(row), coordinateY(column){}
	int coordinateX, coordinateY;
    bool visited = false; 
	double f, g, h;
};


class Algorithms
{
protected:
    sf::Vector2f GetDirectionVector()
    {
        std::vector<std::vector<Cell>> path; 
    }

private:
    bool isValid(const Cell &cell) const
    {
        return (cell.coordinateX >= 0) && 
               (cell.coordinateX < m_rows) && 
               (cell.coordinateY >= 0) && 
               (cell.coordinateY < m_columns);
    }

	bool Compare(const Cell& a, const Cell& b) const
	{
		return std::max(a.f, b.f); 
	}

    bool isUnBlocked(const MapGenerator& map, Cell coordinate) const
    {
        if (map.p_tileMap[coordinate.coordinateX][coordinate.coordinateY].occupied == true) {
            return false;
        }
        return true;

    }

    bool isDestination(const Cell& start, const Cell& target) const 
    {
        if (start.coordinateX == target.coordinateX && start.coordinateY == target.coordinateY) {
            return true;
        }
        else {
            return false;
        }
    }

    double CalculateDistance(const Cell start, Cell target) const
    {
        return ((double)sqrt((start.coordinateX - target.coordinateX) * (start.coordinateX - target.coordinateX) +
            (start.coordinateY - target.coordinateY) * (start.coordinateY - target.coordinateY)));
    }


    std::vector<std::vector<Cell>> aStarSearch(const MapGenerator& map, const Cell& start, const Cell& target)
    {

        if (isValid(start) == false || isValid(target)) {
            return;
        }

        if (isUnBlocked(map, start) == false || isUnBlocked(map, target) == false) {
            return;
        }

        if (isDestination(target, target) == true) {
            return;
        }

        std::vector<std::vector<bool>> closedlist = std::vector<std::vector<bool>>(100, std::vector<bool>(100));;
        std::vector<std::vector<Cell>> cellinfo;

        for (int i = 0; i < m_rows; i++) {
            for (int j = 0; j < m_columns; j++) {
                cellinfo[i][j].f = FLT_MAX;
                cellinfo[i][j].g = FLT_MAX;
                cellinfo[i][j].h = FLT_MAX;
                cellinfo[i][j].coordinateX = -1;
                cellinfo[i][j].coordinateY = -1;
            }
        }

        int x = start.coordinateX, y = start.coordinateY;
        cellinfo[x][y].f = 0.0;
        cellinfo[x][y].g = 0.0;
        cellinfo[x][y].h = 0.0;
        cellinfo[x][y].coordinateX = x;
        cellinfo[x][y].coordinateY = y;

        std::vector<std::pair<double, Cell>> openlist;
        openlist.push_back(std::make_pair(0, Cell(x, y)));

        bool foundDest = false;

        while (!openlist.empty()) {

            std::pair<double, Cell> p = openlist[0];
            openlist.erase(openlist.begin());

            x = p.second.coordinateX;
            y = p.second.coordinateY;
            closedlist[x][y] = true;

            /*
             Generating all the 8 successor of this cell

                 N.W   N   N.E
                   \   |   /
                    \  |  /
                 W----Cell----E
                      / | \
                    /   |  \
                 S.W    S   S.E

             Cell-->Popped Cell (i, j)
             N -->  North       (i-1, j)
             S -->  South       (i+1, j)
             E -->  East        (i, j+1)
             W -->  West           (i, j-1)
             N.E--> North-East  (i-1, j+1)
             N.W--> North-West  (i-1, j-1)
             S.E--> South-East  (i+1, j+1)
             S.W--> South-West  (i+1, j-1)*/

            double gNew, hNew, fNew;

            // North
            if (isValid(Cell(x - 1, y)) == true) {
                if (isDestination(Cell(x - 1, y), target) == true) {
                    cellinfo[x - 1][y].coordinateX = x;
                    cellinfo[x - 1][y].coordinateY = y;
                    tracePath(cellinfo, target);
                    foundDest = true;
                    return cellinfo;
                }
                else if (cellinfo[x - 1][y].visited == false && isUnBlocked(map, Cell(x - 1, y)) == true) {
                    gNew = cellinfo[x][y].g + 1.0;
                    hNew = CalculateDistance(Cell(x - 1, y), target);
                    fNew = gNew + hNew;

                    if (cellinfo[x - 1][y].f == FLT_MAX || cellinfo[x - 1][y].f > fNew) {
                        openlist.push_back(std::make_pair(fNew, Cell(x - 1, y)));

                        cellinfo[x - 1][y].f = fNew;
                        cellinfo[x - 1][y].g = gNew;
                        cellinfo[x - 1][y].h = hNew;
                        cellinfo[x - 1][y].coordinateX = x;
                        cellinfo[x - 1][y].coordinateY = y;
                    }
                }
            }
            // south
            if (isValid(Cell(x + 1, y)) == true) {
                if (isDestination(Cell(x + 1, y), target) == true) {
                    cellinfo[x + 1][y].coordinateX = x;
                    cellinfo[x + 1][y].coordinateY = y;
                    tracePath(cellinfo, target);
                    foundDest = true;
                    return cellinfo;
                }

                else if (cellinfo[x + 1][y].visited == false && isUnBlocked(map, Cell(x + 1, y)) == true) {
                    gNew = cellinfo[x][y].g + 1.0;
                    hNew = CalculateDistance(Cell(x + 1, y), target);
                    fNew = gNew + hNew;

                    if (cellinfo[x + 1][y].f == FLT_MAX || cellinfo[x + 1][y].f > fNew) {
                        openlist.push_back(std::make_pair(fNew, Cell(x - 1, y)));

                        cellinfo[x + 1][y].f = fNew;
                        cellinfo[x + 1][y].g = gNew;
                        cellinfo[x + 1][y].h = hNew;
                        cellinfo[x + 1][y].coordinateX = x;
                        cellinfo[x + 1][y].coordinateY = y;
                    }
                }
            }
            // east
            if (isValid(Cell(x, y + 1)) == true) {
                if (isDestination(Cell(x + 1, y), target) == true) {
                    cellinfo[x][y + 1].coordinateX = x;
                    cellinfo[x][y + 1].coordinateY = y;
                    tracePath(cellinfo, target);
                    foundDest = true;
                    return cellinfo;
                }

                else if (cellinfo[x][y + 1].visited == false && isUnBlocked(map, Cell(x, y + 1)) == true) {
                    gNew = cellinfo[x][y + 1].g + 1.0;
                    hNew = CalculateDistance(Cell(x + 1, y), target);
                    fNew = gNew + hNew;

                    if (cellinfo[x][y + 1].f == FLT_MAX || cellinfo[x][y + 1].f > fNew) {
                        openlist.push_back(std::make_pair(fNew, Cell(x, y + 1)));

                        cellinfo[x][y + 1].f = fNew;
                        cellinfo[x][y + 1].g = gNew;
                        cellinfo[x][y + 1].h = hNew;
                        cellinfo[x][y + 1].coordinateX = x;
                        cellinfo[x][y + 1].coordinateY = y;
                    }
                }
            }
            // west
            if (isValid(Cell(x, y - 1)) == true) {
                if (isDestination(Cell(x, y - 1), target) == true) {
                    cellinfo[x][y - 1].coordinateX = x;
                    cellinfo[x][y - 1].coordinateY = y;
                    tracePath(cellinfo, target);
                    foundDest = true;
                    return cellinfo;
                }

                else if (cellinfo[x][y - 1].visited == false && isUnBlocked(map, Cell(x + 1, y)) == true) {
                    gNew = cellinfo[x][y - 1].g + 1.0;
                    hNew = CalculateDistance(Cell(x, y - 1), target);
                    fNew = gNew + hNew;

                    if (cellinfo[x][y - 1].f == FLT_MAX || cellinfo[x][y - 1].f > fNew) {
                        openlist.push_back(std::make_pair(fNew, Cell(x, y - 1)));

                        cellinfo[x][y - 1].f = fNew;
                        cellinfo[x][y - 1].g = gNew;
                        cellinfo[x][y - 1].h = hNew;
                        cellinfo[x][y - 1].coordinateX = x;
                        cellinfo[x][y - 1].coordinateY = y;
                    }
                }
            }
            // North-East
            if (isValid(Cell(x - 1, y + 1)) == true) {
                if (isDestination(Cell(x - 1, y + 1), target) == true) {
                    cellinfo[x - 1][y + 1].coordinateX = x;
                    cellinfo[x - 1][y + 1].coordinateY = y;
                    tracePath(cellinfo, target);
                    foundDest = true;
                    return cellinfo;
                }

                else if (cellinfo[x - 1][y + 1].visited == false && isUnBlocked(map, Cell(x - 1, y + 1)) == true) {
                    gNew = cellinfo[x - 1][y + 1].g + 1.0;
                    hNew = CalculateDistance(Cell(x - 1, y + 1), target);
                    fNew = gNew + hNew;

                    if (cellinfo[x - 1][y + 1].f == FLT_MAX || cellinfo[x - 1][y + 1].f > fNew) {
                        openlist.push_back(std::make_pair(fNew, Cell(x - 1, y + 1)));

                        cellinfo[x - 1][y + 1].f = fNew;
                        cellinfo[x - 1][y + 1].g = gNew;
                        cellinfo[x - 1][y + 1].h = hNew;
                        cellinfo[x - 1][y + 1].coordinateX = x;
                        cellinfo[x - 1][y + 1].coordinateY = y;
                    }
                }
            }
            // North-West
            if (isValid(Cell(x + 1, y - 1)) == true) {
                if (isDestination(Cell(x + 1, y - 1), target) == true) {
                    cellinfo[x + 1][y - 1].coordinateX = x;
                    cellinfo[x + 1][y - 1].coordinateY = y;
                    tracePath(cellinfo, target);
                    foundDest = true;
                    return cellinfo;
                }

                else if (cellinfo[x + 1][y - 1].visited == false && isUnBlocked(map, Cell(x + 1, y - 1)) == true) {
                    gNew = cellinfo[x + 1][y - 1].g + 1.0;
                    hNew = CalculateDistance(Cell(x + 1, y - 1), target);
                    fNew = gNew + hNew;

                    if (cellinfo[x + 1][y - 1].f == FLT_MAX || cellinfo[x + 1][y - 1].f > fNew) {
                        openlist.push_back(std::make_pair(fNew, Cell(x + 1, y - 1)));

                        cellinfo[x + 1][y - 1].f = fNew;
                        cellinfo[x + 1][y - 1].g = gNew;
                        cellinfo[x + 1][y - 1].h = hNew;
                        cellinfo[x + 1][y - 1].coordinateX = x;
                        cellinfo[x + 1][y - 1].coordinateY = y;
                    }
                }
            }
            // South - East
            if (isValid(Cell(x - 1, y - 1)) == true) {
                if (isDestination(Cell(x + 1, y - 1), target) == true) {
                    cellinfo[x - 1][y - 1].coordinateX = x;
                    cellinfo[x - 1][y - 1].coordinateY = y;
                    tracePath(cellinfo, target);
                    foundDest = true;
                    return cellinfo;
                }

                else if (cellinfo[x - 1][y - 1].visited == false && isUnBlocked(map, Cell(x - 1, y - 1)) == true) {
                    gNew = cellinfo[x - 1][y - 1].g + 1.0;
                    hNew = CalculateDistance(Cell(x - 1, y - 1), target);
                    fNew = gNew + hNew;

                    if (cellinfo[x - 1][y - 1].f == FLT_MAX || cellinfo[x - 1][y - 1].f > fNew) {
                        openlist.push_back(std::make_pair(fNew, Cell(x - 1, y - 1)));

                        cellinfo[x - 1][y - 1].f = fNew;
                        cellinfo[x - 1][y - 1].g = gNew;
                        cellinfo[x - 1][y - 1].h = hNew;
                        cellinfo[x - 1][y - 1].coordinateX = x;
                        cellinfo[x - 1][y - 1].coordinateY = y;
                    }
                }
            }
            // South-West
            if (isValid(Cell(x + 1, y + 1)) == true) {
                if (isDestination(Cell(x + 1, y + 1), target) == true) {
                    cellinfo[x + 1][y + 1].coordinateX = x;
                    cellinfo[x + 1][y + 1].coordinateY = y;
                    tracePath(cellinfo, target);
                    foundDest = true;
                    return cellinfo;
                }

                else if (cellinfo[x + 1][y + 1].visited == false && isUnBlocked(map, Cell(x + 1, y + 1)) == true) {
                    gNew = cellinfo[x + 1][y + 1].g + 1.0;
                    hNew = CalculateDistance(Cell(x + 1, y + 1), target);
                    fNew = gNew + hNew;

                    if (cellinfo[x + 1][y + 1].f == FLT_MAX || cellinfo[x + 1][y + 1].f > fNew) {
                        openlist.push_back(std::make_pair(fNew, Cell(x + 1, y + 1)));

                        cellinfo[x + 1][y + 1].f = fNew;
                        cellinfo[x + 1][y + 1].g = gNew;
                        cellinfo[x + 1][y + 1].h = hNew;
                        cellinfo[x + 1][y + 1].coordinateX = x;
                        cellinfo[x + 1][y + 1].coordinateY = y;
                    }
                }
            }

            return cellinfo;
        }
    }

protected:
	int m_rows, m_columns; 

private:
    std::vector<std::vector<Cell>> m_cellinfo; 


protected:
    //Endless hellfire of utility functions which are thrown into the trash after debugging

    // Just utillity (Printing out the Path)
    sf::Vector2f tracePath(std::vector<std::vector<Cell>> infocell, const Cell &position,const Cell& target)
    {
        int x = target.coordinateX;
        int y = target.coordinateY;

        std::vector<Cell> path; 

        while (!(infocell[x][y].coordinateX == x && infocell[x][y].coordinateY == y)) {
            path.push_back(Cell(x, y));
            int temp_row = infocell[x][y].coordinateX;
            int temp_col = infocell[x][y].coordinateY;
            x = temp_row;
            y = temp_col;
        }

        path.push_back(Cell(x, y));

        for (int i = 0; i < path.size(); i++) {
            std::cout << "Path: " << path[i].coordinateX << " " << path[i].coordinateY << std::endl;
        }

        return sf::Vector2f(path[0].coordinateX, path[0].coordinateY);
    }
};