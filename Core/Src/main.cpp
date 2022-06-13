#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Program.hpp"

int
main()
{
  std::ifstream in("Furnica.in");

  if (!in) {
    std::cout << "File opening error." << std::endl;
    return 0;
  }

  int n;
  in >> n;

  Program program;
  std::string line;
  std::getline(in, line);
  std::getline(in, line);
  std::string delimiter = " ";
  size_t pos;
  while ((pos = line.find(delimiter)) != std::string::npos) {
    program.addStep(std::stoi(line.substr(0, pos)));
    line.erase(0, pos + delimiter.length());
  }
  program.addStep(std::stoi(line.substr(0, pos)));
  in.close();
  program.initTable(n);

  while (true) {
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "                                              -==< Meniu >==-" << std::endl;
    std::cout << "1.  Extinde drumul furnicii, descris in fisierul Furnica.in, cu o noua directie" << std::endl;
    std::cout << "2.  Exclude din drumul furnicii, descris in filul Furnica.in, ultima directie" << std::endl;
    std::cout << "3.  Initializeaza matricea patratica A, aplicand formula A[i, j] = ( i + j ) % 6" << std::endl;
    std::cout << "4.  Determina frecventa cifrelor din multimea { 0, 1, 2, 3, 4, 5 } in cadrul matricei A"  << std::endl;
    std::cout << "5.  Afiseaza pe ecran elementele unui rand a matricei A, ordonate crescator prin metoda selectiei"  << std::endl;
    std::cout << "6.  Creaza fisierul UnZero.txt prin copiere din fisierul Furnica.in a liniilor care contin doar un singur zero"  << std::endl;
    std::cout << "7.  Gaseste in matricea A o submatrice patratica de dimensiune maximala ce nu contine cifra 1." << std::endl
              << "    Afiseaza-i coordonatele punctului stanga-sus si dimensiunea ei" << std::endl;
    std::cout << "8.  Determina valoarea totala a firmiturilor mancate de furnica & numarul maximal de treceri printr-un oarecare patratel" << std::endl;
    std::cout << "9.  Afisarea datelor" << std::endl;
    std::cout << "10. Iesire din program" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Alege o varianta: ";
    int selection;
    std::cin >> selection;
    std::cout << std::endl;

    switch (selection) {
      case 1:
        std::cout << "Directia: ";
        int direction;
        std::cin >> direction;

        if (direction >= 1 && direction <= 8) {
          program.addStep(direction);
          std::cout << "Directia a fost adaugata" << std::endl;
        } else {
          std::cout << "Directia introdusa este invalida" << std::endl;
        }
        break;

      case 2:
        program.deleteLastStep();
        std::cout << "Ultima directie a fost stearsa" << std::endl;
        break;
      
      case 3:
        program.initTable(n);
        std::cout << "Tabla cu farmituri a fost initializata" << std::endl;
        break;
      
      case 4:
        program.showNumberFrequency();
        break;

      case 5:
        std::cout << "Indexul randului care va fi afisat: ";
        int row;
        std::cin >> row;
        program.showSortedRow(row);
        break;
      
      case 6:
        program.exportOneZeroRows();
        break;

      case 7:
        program.showSubMatrix();
        break;

      case 8:
        program.followPath();
        break;
      
      case 9:
        std::cout << "Tabla:" << std::endl;
        program.showTable();
        std::cout << "Directiile:" << std::endl;
        program.showSteps();
        break;
      
      case 10:
        return 0;
        break;

      default:
        std::cout << "Comanda necunoscuta" << std::endl;
        break;
    }
  }

  return 0;
}
