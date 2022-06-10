#pragma once

#include <fstream>
#include <iostream>
#include <vector>

#include "Cell.hpp"

class Program
{
private:
  std::vector<std::vector<Cell>> table;
  std::vector<int> steps;

private:
  void showRow(std::vector<Cell> row)
  {
    for (Cell cell : row) {
      std::cout << cell.getValue() << " ";
    }
    std::cout << std::endl;
  }

  std::vector<Cell> selectionSort(std::vector<Cell> array)
  {
    int minIndex;
    const size_t size = array.size();

    for (size_t i = 0; i < size - 1; i++) {
      minIndex = i;

      for (size_t j = i + 1; j < size; j++) {
        if (array[j].getValue() < array[minIndex].getValue()) {
          minIndex = j;
        }
      }
      std::swap(array[i], array[minIndex]);
    }

    return array;
  }

  bool doesHaveOnlyOneZero(std::vector<Cell>& row)
  {
    int zeroCount = 0;

    for (Cell cell : row) {
      if (cell.getValue() == 0) {
        ++zeroCount;
      }
    }

    return (zeroCount == 1 ? true : false);
  }

public:
  void showTable()
  {
    for (std::vector<Cell> row : table) {
      showRow(row);
    }
  }

  void showSteps()
  {
    for (int step : steps) {
      std::cout << step << " ";
    }
    std::cout << std::endl;
  }

  void addStep(int step) { steps.push_back(step); }

  void deleteLastStep() { steps.pop_back(); }

  void initTable(int dimensions)
  {
    for (int i = 0; i < dimensions; ++i) {
      std::vector<Cell> row;

      for (int j = 0; j < dimensions; ++j) {
        row.push_back(Cell((i + j + 2) % 6));
      }

      table.push_back(row);
    }
  }

  void showNumberFrequency()
  {
    int frequency[6] = { 0, 0, 0, 0, 0, 0 };

    for (std::vector<Cell> row : table) {
      for (Cell cell : row) {
        frequency[cell.getValue()]++;
      }
    }

    std::cout << "Frecventa cifrelor: " << std::endl;
    for (int i = 0; i < 6; ++i) {
      std::cout << i << ": " << frequency[i] << std::endl;
    }
  }

  void showSortedRow(int index) { showRow(selectionSort(table[index])); }

  void exportOneZeroRows()
  {
    std::ofstream out("UnZero.out");

    for (std::vector<Cell> row : table) {
      if (doesHaveOnlyOneZero(row)) {
        for (Cell cell : row) {
          out << cell.getValue() << " ";
        }
        out << std::endl;
      }
    }

    out.close();

    std::cout << "Randurile au fost exportate" << std::endl;
  }

  void showSubMatrix()
  {
    std::cout << "Coltul stanga-sus: [0, 0]" << std::endl;
    std::cout << "Dimensiunea matricei: ";
    if (table.size() >= 3) {
      std::cout << "3" << std::endl;
    } else {
      std::cout << table.size() << std::endl;
    }
  }

  void followPath()
  {
    int indexX = 0, indexY = 0;
    int sum = table[indexY][indexX].getValue();

    for (int step : steps) {
      switch (step) {
        case 1:
          --indexY;
          break;

        case 2:
          ++indexX;
          --indexY;
          break;

        case 3:
          ++indexX;
          break;

        case 4:
          ++indexX;
          ++indexY;
          break;

        case 5:
          ++indexY;
          break;

        case 6:
          ++indexY;
          --indexX;
          break;

        case 7:
          --indexX;
          break;

        case 8:
          --indexX;
          --indexY;
          break;
      }

      sum += table[indexY][indexX].passCell();
    }

    int maxPassBy = 0;
    for (std::vector<Cell> row : table) {
      for (Cell cell : row) {
        const int cellPassBy = cell.getPassedCount();
        if (cellPassBy > maxPassBy) {
          maxPassBy = cellPassBy;
        }
      }
    }

    std::ofstream out("Furnica.out");
    out << sum << " " << maxPassBy << std::endl;
    out.close();

    std::cout << "Nr. de farmituri mancate: " << sum << std::endl;
    std::cout << "Nr. maxim de treceri printr-o celula: " << maxPassBy
              << std::endl;
  }
};