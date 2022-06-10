#pragma once

class Cell
{
private:
  int value_;
  int passedCount_;

public:
  Cell(int value)
    : value_(value)
    , passedCount_(0)
  {
  }

  void setValue(int value) { value_ = value; }

  int getValue() { return value_; }

  int getPassedCount() { return passedCount_; }

  int passCell()
  {
    int cellValue = value_;
    value_ = 0;
    ++passedCount_;
    return cellValue;
  }
};