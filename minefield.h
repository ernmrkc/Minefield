#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <QMainWindow>
#include <QGridLayout>
#include <QDebug>

class Minefield : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief    Constructor of Minefield class
     */
    Minefield(QWidget *parent = nullptr);

    /**
     * @brief    Destructor of Minefield class
     */
    ~Minefield();

public slots:

    /**
     * @brief restartGame   This function resets the game when the game is over.
     */
    void restartGame();

private:

    /**
     * @brief createField   This function creates a minefield when the game starts
     */
    void createField();

    /**
     * @brief plantMine     This function randomly places mines
     */
    void plantMine();

    /**
     * @brief calculateNeighborMineCount    This function calculates the number of neighboring mines
     * @param row                           Row value of corresponding mine
     * @param col                           Col value of corresponding mine
     */
    void calculateNeighborMineCount(int row, int col);

    const int MINECOUNT = 25;               // Represents the total number of mines
    const int GRIDSIZE = 10;                // Represents grid size e.g. 10x10

    QGridLayout *gridLayout;                // Used to place related buttons

};
#endif // MINEFIELD_H
