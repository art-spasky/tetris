#include "well.hpp"
#include "painter.hpp"
#include "tetromino.hpp"

Well::Well():size_(20)
{
  for (int y = 0; y < HEIGHT; ++y)
    for (int x = 0; x < WIDTH; ++x)
      map_[y][x] = false;
}

void Well::draw(Painter &p) const
{
  p.setColor(Painter::WHITE);
  for (int y = 0; y < HEIGHT; ++y)
    for (int x = 0; x < WIDTH; ++x)
      if (map_[y][x])
	p.rect(x * size_ + 1, y * size_ + 1,
	       (x + 1) * size_ - 1, (y + 1) * size_ - 1);
      else
	p.rect(x * size_ + 8, y * size_ + 8,
	       (x + 1) * size_ - 9, (y + 1) * size_ - 9);
}

bool Well::isCollision(const Tetromino &t) const
{
  for (int y = 0; y < 4; ++y)
    for (int x = 0; x < 4; ++x)
      if (t.map(x, y))
      {
	int wx = x + t.x();
	int wy = y + t.y();
	if (wx < 0 ||
	    wx >= WIDTH ||
	    wy < 0 ||
	    wy >= HEIGHT)
	  return true;
	if (map_[wy][wx])
	  return true;
      }
  return false;
}

void Well::unite(const Tetromino &t)
{
  for (int y = 0; y < 4; ++y)
    for (int x = 0; x < 4; ++x)
    {
      int wx = x + t.x();
      int wy = y + t.y();
      if (wx >= 0 &&
	  wx < WIDTH &&
	  wy >= 0 &&
	  wy < HEIGHT)
	map_[wy][wx] = map_[wy][wx] || t.map(x, y);
    }
}

int Well::removeSolidLines()
{
  int res = 0;
  for (int y = 0; y < HEIGHT; ++y)
  {
    bool solid = true;
    for (int x = 0; x < WIDTH; ++x)
      if (!map_[y][x])
      {
	solid = false;
	break;
      }
    if (solid)
    {
      ++res;
      for (int yy = y - 1; yy >= 0; --yy)
	for (int x = 0; x < WIDTH; ++x)
	  map_[yy + 1][x] = map_[yy][x];
    }
    for (int x = 0; x < WIDTH; ++x)
      map_[0][x] = false;
  }
  return res;
}
