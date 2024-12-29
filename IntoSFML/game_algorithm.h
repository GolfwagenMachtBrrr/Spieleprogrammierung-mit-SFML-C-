#pragma once
#include "Common.h"
#include "nGameData.h"



namespace Algorithms
{
	struct tile
	{
		int x, y;
		float g, h, f; 

		bool enabled;
		bool IsInOpenList; 

		sf::RectangleShape box;
	};

	class MazeGenaration
	{
	public:
		// Prims
		// https://www.youtube.com/watch?v=Y37-gB83HKE

		enum globdir
		{
			North = 0,
			South = 1,
			West = 2,
			East = 3,
		};

		void GenerateMaze(std::vector<std::vector<tile>>& grid)
		{
			int width = grid.size(), height = grid[0].size();
			for (auto& i : grid) { for (auto& j : i) { j.enabled = true; j.box.setFillColor(sf::Color::Black); } }
			sf::Vector2f start((int)(width * (rand() / (RAND_MAX + 1.0))), (int)(height * (rand() / (RAND_MAX + 1.0))));

			grid[(int)start.x][(int)start.y].enabled = false;
			grid[(int)start.x][(int)start.y].box.setFillColor(sf::Color::White);

			std::vector<sf::Vector2i> directions = { sf::Vector2i(0,-1), sf::Vector2i(0,1), sf::Vector2i(-1, 0), sf::Vector2i(1,0) };

			std::vector<std::vector<bool>> visited(width, std::vector<bool>(height, false));
			std::stack<tile> path;

			path.push(grid[start.x][start.y]);
			int visitedCells = 0;
			while (visitedCells < width * height) {

				std::vector<int> neighbours;
				tile& currenttile = path.top();


				for (int index = 0; index < 4; index++) {
					int x = currenttile.x + directions[index].x, y = currenttile.y + directions[index].y;

					if (x < 0 || y < 0) { continue; }
					if (x >= width || y >= height) { continue; }
					if (visited[x][y] == true) { continue; }

					neighbours.push_back(index);
				}

				if (!neighbours.empty())
				{
					int nextcell = neighbours[rand() % neighbours.size()];
					std::cout << nextcell << std::endl;
					int x = currenttile.x, y = currenttile.y;
					// am switch statement erkennt man dass das nicht mein Code ist. Ein echter Jan benutzt keinen Switch!
					switch (nextcell)
					{
					case North:
						visited[x + directions[North].x][y + directions[North].y] = true;
						path.push(grid[x + directions[North].x][y + directions[North].y]);
						grid[x + directions[North].x][y + directions[North].y].enabled = false;
						grid[x + directions[North].x][y + directions[North].y].box.setFillColor(sf::Color::White);
						break;
					case South:
						visited[x + directions[South].x][y + directions[South].y] = true;
						path.push(grid[x + directions[South].x][y + directions[South].y]);
						grid[x + directions[South].x][y + directions[South].y].enabled = false;
						grid[x + directions[South].x][y + directions[South].y].box.setFillColor(sf::Color::White);
						break;
					case West:
						visited[x + directions[West].x][y + directions[West].y] = true;
						path.push(grid[x + directions[West].x][y + directions[West].y]);
						grid[x + directions[West].x][y + directions[West].y].enabled = false;
						grid[x + directions[West].x][y + directions[West].y].box.setFillColor(sf::Color::White);
						break;
					case East:
						visited[x + directions[East].x][y + directions[East].y] = true;
						path.push(grid[x + directions[East].x][y + directions[East].y]);
						grid[x + directions[East].x][y + directions[East].y].enabled = false;
						grid[x + directions[East].x][y + directions[East].y].box.setFillColor(sf::Color::White);
						break;
					}

					visitedCells++;
				}
				else
				{

					path.pop();

				}

			}
		}
	};

	class BFS
	{
	private: 
		std::array<sf::Vector2f, 8> directions = {sf::Vector2f(1, 0), sf::Vector2f(-1, 0), sf::Vector2f(0, 1), sf::Vector2f(0, -1),
												 sf::Vector2f(1, -1), sf::Vector2f(-1, 1), sf::Vector2f(1, 1), sf::Vector2f(-1, -1)};

	protected:
		std::vector<sf::Vector2f> Search(sf::Vector2f start, sf::Vector2f dest, MapGenerator* map)
		{
			// Oft wiederholt sollte das ausbessern* 
			start.x /= (float)GameData::_TileSize.x, start.y /= (float)GameData::_TileSize.y;
			dest.x /= (float)GameData::_TileSize.x, dest.y /= (float)GameData::_TileSize.y;

			std::vector<sf::Vector2f> path; //path.push_back(sf::Vector2f(0, 0)); 
			int width = map->GetMapSize().x, height = map->GetMapSize().y;

			// Setup
			if (start.x == dest.x && start.y == dest.y) {
				return path;
			}
			std::vector<std::vector<bool>> visited(width, std::vector<bool>(height));

			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {
					visited[i][j] = false;
				}
			}
			std::stack<sf::Vector2f> stack;

			bool reached_end = false;

			stack.push(start);
			visited[start.x][start.y] = true;

			sf::Vector2f cords;


			while (stack.size() > 0) {

				cords = stack.top();
				stack.pop();

				if (cords == dest) {
					reached_end = true;
					break;
				}

				for (int i = 0; i < 8; i++)
				{
					sf::Vector2f tmp;
					tmp.x = cords.x + directions[i].x;
					tmp.y = cords.y + directions[i].y;

					if (tmp.x < 0 or tmp.y < 0) { continue; }
					if (tmp.x >= width or tmp.x >= height or tmp.y >= width or tmp.y >= height) { continue; }

					if (visited[tmp.x][tmp.y]) { continue; }
					if (map->p_tileMap[tmp.x][tmp.y].occupied) { continue; }

					stack.push(tmp);
					visited[tmp.x][tmp.y] = true;
				}
			}

			return path;
		}
	};

	class Astar
	{
	public:
		void Update(std::vector<std::vector<tile>>& grid, sf::RenderWindow& window)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (auto& i : grid)
				{
					for (auto& j : i) {
						if (j.box.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window))) {
							j.enabled = true; 
							j.box.setFillColor(sf::Color::Black); 
						}
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				for (auto& i : grid)
				{
					for (auto& j : i) {
						if (j.box.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window))) {
							j.enabled = false;
							j.box.setFillColor(sf::Color::White);
						}
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			{
				src = dst; 
			}
		}

		void Search(tile& A, tile& B, std::vector<std::vector<tile>>& grid, sf::RenderWindow &window)
		{
			src = A; dst = B; 
			int width = grid.size(), height = grid[0].size();
			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++) {
					window.draw(grid[x][y].box);
				}
			}

			std::vector<std::vector<bool>> visited(width, std::vector<bool>(height, false));

			std::stack<tile> open; 
			open.push(src);

			while (!open.empty())
			{
				tile current = open.top();
				open.pop(); 

				int x = current.x, y = current.y;
				visited[x][y] = true; 

				if (src.x == dst.x && src.y == dst.y) {
					std::cout << "success - Manual" << std::endl;
					reset(grid, window);
					return;
				}

				if (current.x == dst.x && current.y == dst.y) {
					std::cout << "success" << std::endl;
					reset(grid, window); 
					return; 
				}

				float minFval = FLT_MAX, minHval = FLT_MAX; 
				tile nexttile = current; 

				for (int i = 0; i < 8; i++) 
				{
					int xnew = x + directions[i].x, ynew = y + directions[i].y; 
				
					if (xnew < 0 || ynew < 0)			 { continue; }
					if (xnew >= width || ynew >= height) { continue; }

					if (visited[xnew][ynew])			 { continue; }
					if (grid[xnew][ynew].enabled)        { continue; }

					// Die Werte für H, G und F berechnen
					grid[xnew][ynew].h = CalculateDistance(sf::Vector2i(xnew, ynew), sf::Vector2i(B.x, B.y));
					grid[xnew][ynew].g = CalculateDistance(sf::Vector2i(xnew, ynew), sf::Vector2i(A.x, A.y));
					grid[xnew][ynew].f = grid[xnew][ynew].g + grid[xnew][ynew].h; 

					// Schlechter Code
					if (minFval > grid[xnew][ynew].f) {
						nexttile = grid[xnew][ynew];
						grid[xnew][ynew].box.setFillColor(sf::Color::Yellow);
						minHval = std::min(minHval, grid[xnew][ynew].h);
					}
					else if (minFval == grid[xnew][ynew].f) {
						if (minHval > grid[xnew][ynew].h)
						{
							nexttile = grid[xnew][ynew];
							grid[xnew][ynew].box.setFillColor(sf::Color::Yellow);
						}
					}
					minFval = std::min(minFval, grid[xnew][ynew].f);
					
					open.push(nexttile); 

					Update(grid, window); 

					window.clear(); 

					for (int x = 0; x < width; x++) {
						for (int y = 0; y < height; y++) {
							window.draw(grid[x][y].box);
						}
					}
					window.display(); 

				}
			}
		}

		void reset(std::vector<std::vector<tile>>& grid, sf::RenderWindow& window)
		{
			for (auto& tiles : grid)
			{
				for (auto& tile : tiles) {
					tile.IsInOpenList = false;
				}
			}
			mg.GenerateMaze(grid); 
			int width = grid.size(), height = grid[0].size(); 

			sf::Vector2f start((int)(width * (rand() / (RAND_MAX + 1.0))),(int)(height * (rand() / (RAND_MAX + 1.0))));
			sf::Vector2f dest((int)(width * (rand() / (RAND_MAX + 1.0))), (int)(height * (rand() / (RAND_MAX + 1.0))));

			src.x = start.x, src.y = start.y; 
			dst.x = dest.x, dst.y = dest.y;

			grid[(int)start.x][(int)start.y].box.setFillColor(sf::Color::Green);
			grid[(int)dest.x][(int)dest.y].box.setFillColor(sf::Color::Red);

			grid[(int)start.x][(int)start.y].enabled = true; 
			grid[(int)dest.x][(int)dest.y].enabled = false;

			Search(src, dst, grid, window); 
		}

	private:
		float CalculateDistance(sf::Vector2i src, sf::Vector2i dst)
		{
			float a = abs(dst.x - src.x);
			float b = abs(dst.y - src.y);

			return (float)sqrt(a * a + b * b);
		}
		
	private:
		tile src, dst; 

		MazeGenaration mg; 

		std::vector<sf::Vector2i> directions = { sf::Vector2i(1, 0), sf::Vector2i(-1, 0), sf::Vector2i(0, 1), sf::Vector2i(0, -1),
												 sf::Vector2i(1, -1), sf::Vector2i(-1, 1), sf::Vector2i(1, 1), sf::Vector2i(-1, -1) }; 
	};

	
}

