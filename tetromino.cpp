#include "tetromino.hpp"
#include "painter.hpp"

Tetromino::Tetromino(Name name): name_(name), 
				 angel_(0), 
				 x_(3),
				 y_(0), size_(20) {}
void Tetromino::draw(Painter &p) const
{
  p.setColor(static_cast<Painter::Color>(name_));
  for (int y = 0; y < 4; ++y)
    for (int x = 0; x < 4; ++x)
      if (map(x, y))
	p.rect((x + x_) * size_ + 1, 
	       (y + y_) * size_ + 1,
	       (x + x_ + 1) * size_ - 1, 
	       (y + y_ + 1) * size_ - 1);
}

bool Tetromino::map(int x, int y) const
{
  static const char *SHAPES[] = 
    {
      "  1 " // I
      "  1 "
      "  1 "
      "  1 ", 

      "  1 " // J
      "  1 "
      " 11 "
      "    ", 

      " 1  " // L
      " 1  "
      " 11 "
      "    ", 

      "    " // O
      " 11 "
      " 11 "
      "    ", 

      "  1 " // S
      " 11 "
      " 1  "
      "    ", 

      " 1  " // Z
      " 11 "
      "  1 "
      "    ", 

      "    " // T
      " 111"
      "  1 "
      "    " 
    };
  static const struct 
  {
    int x, y;
  } ROTATE[][16] = {
    {
      { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, 
      { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, 
      { 2, 0 }, { 2, 1 }, { 2, 2 }, { 2, 3 }, 
      { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 } 
    },
    {
      { 3, 0 }, { 2, 0 }, { 1, 0 }, { 0, 0 }, 
      { 3, 1 }, { 2, 1 }, { 1, 1 }, { 0, 1 }, 
      { 3, 2 }, { 2, 2 }, { 1, 2 }, { 0, 2 }, 
      { 3, 3 }, { 2, 3 }, { 1, 3 }, { 0, 3 } 
    },
    {
      { 3, 3 }, { 3, 2 }, { 3, 1 }, { 3, 0 }, 
      { 2, 3 }, { 2, 2 }, { 2, 1 }, { 2, 0 }, 
      { 1, 3 }, { 1, 2 }, { 1, 1 }, { 1, 0 }, 
      { 0, 3 }, { 0, 2 }, { 0, 1 }, { 0, 0 } 
    },
    {
      { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 }, 
      { 0, 2 }, { 1, 2 }, { 2, 2 }, { 3, 2 }, 
      { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 }, 
      { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } 
    }
  };
  return SHAPES[name_]
    [ROTATE[angel_][y * 4 + x].y * 4 +
     ROTATE[angel_][y * 4 + x].x] != ' ';
}

void Tetromino::move(int dx, int dy)
{
  x_ += dx;
  y_ += dy;
}

void Tetromino::rotate(Direction d)
{
  angel_ = (angel_ + d + 4) % 4;
}

