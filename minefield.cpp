#include "Minefield.h"
#include "Mine.h"
#include <random>

Minefield::Minefield(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("MineSweeper");
    setFixedSize(300, 300);
    createField();
}

Minefield::~Minefield()
{

}

void Minefield::restartGame()
{
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(centralWidget()->layout());

    // Reset all buttons on QGridLayout
    for (int row = 0; row < this->GRIDSIZE; ++row)
    {
        for (int col = 0; col < this->GRIDSIZE; ++col)
        {
            // Create new buttons according to row and col value
            Mine *mine = qobject_cast<Mine *>(gridLayout->itemAtPosition(row, col)->widget());
            mine->setText("");
            mine->setMine(false);
            mine->setEnabled(true);
        }
    }

    // Replant mines in different locations
    plantMine();
}

void Minefield::createField()
{
    // Create gridLayout
    gridLayout = new QGridLayout();

    // Setting up Central widget with grid layout
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(gridLayout);
    setCentralWidget(centralWidget);

    gridLayout->setSpacing(0);

    // Create buttons according to row and col value for minefield
    for (int row = 0; row < this->GRIDSIZE; row++)
    {
        for (int col = 0; col < this->GRIDSIZE; col++)
        {
            Mine *mine = new Mine(row, col, false, this);
            mine->setFixedSize(28, 28);
            gridLayout->addWidget(mine, row, col);
        }
    }

    plantMine();
}

void Minefield::plantMine()
{
    int count = 0;      // Represents the number of mines planted
    while(count < this->MINECOUNT){

        // Used to generate random numbers at each runtime
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> intDist(0, 99);
        int row = intDist(gen) % this->GRIDSIZE;
        int col = intDist(gen) % this->GRIDSIZE;

        Mine *tempMine = qobject_cast<Mine*>(gridLayout->itemAtPosition(row, col)->widget());
        // Check for mines at the location
        if(tempMine->checkMine())
        {
            // Try again if you already have mines
            continue;
        }

        /* Remove the button in the corresponding location and create a new one */

        // Remove Bench
        QLayoutItem *item = gridLayout->itemAtPosition(row, col);
        if(item)
        {
            QLayoutItem *widgetItem = gridLayout->takeAt(gridLayout->indexOf(item));
            delete widgetItem->widget();
            delete widgetItem;
        }

        // Create Bench
        Mine *newMine = new Mine(row, col, true, this);
        newMine->setFixedSize(28, 28);
        gridLayout->addWidget(newMine, row, col);
        count++;
    }

    // Calculate the number of neighboring mines for each button
    for(int row = 0; row < this->GRIDSIZE; row++)
    {
        for (int col = 0; col < this->GRIDSIZE; col++)
        {
            calculateNeighborMineCount(row, col);
        }
    }
}

void Minefield::calculateNeighborMineCount(int row, int col)
{
    int count = 0;

    // Get corresponding button
    Mine *mine = qobject_cast<Mine *>(gridLayout->itemAtPosition(row, col)->widget());
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < GRIDSIZE && newCol >= 0 && newCol < GRIDSIZE)
            {
                Mine *tempButton = qobject_cast<Mine *>(gridLayout->itemAtPosition(newRow, newCol)->widget());

                // Check mine status of relevant button
                if(tempButton->checkMine())
                {
                    count++;
                }
            }
        }
    }

    mine->setValue(count);
}
