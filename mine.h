#ifndef MINE_H
#define MINE_H

#include <QApplication>
#include <QPushButton>
#include <QMouseEvent>
#include <QMessageBox>

class Mine : public QPushButton
{
    Q_OBJECT

public:

    /**
     * @brief The MineButtonStatus enum     Represents button status
     */
    enum MineButtonStatus{
        available,              // empty
        flag,                   // !
        uncertain               // ?
    };

    /**
     * @brief Mine          Represents constructor of Mine class
     * @param row           Row value of corresponding button
     * @param col           Col value of corresponding button
     * @param mineStatus    Mine status of button
     * @param parent        Represents parent
     */
    Mine(int row, int col, bool mineStatus, QWidget *parent = nullptr);

    /**
     * @brief Mine          Represents destructor of Mine class
     */
    ~Mine();

    /**
     * @brief checkMine     This function gets mine status of corresponding button
     * @return              Mine status
     */
    bool checkMine();

    /**
     * @brief setMine       This function sets the mine status of the corresponding button
     * @param mineStatus    Mine status
     */
    void setMine(bool mineStatus);

    /**
     * @brief setValue      Sets the number of mines that will be written on the button
     * @param value         Number of neighboring mines
     */
    void setValue(int value);

protected:

    /**
     * @brief mousePressEvent       Used to revise right click and left click functions
     * @param event                 Represents event
     */
    void mousePressEvent(QMouseEvent *event) override;

private:

    /**
     * @brief getStatus     This function gets button status
     * @return              Button status
     */
    MineButtonStatus getStatus();

    /**
     * @brief setStatus     This function sets button status
     * @param newStatus     New button status
     */
    void setStatus(MineButtonStatus newStatus);

    int row;                    // Row value of corresponding button
    int col;                    // Col value of corresponding button
    int value;                  // The number to write on the button
    bool isMine;                // Mine status
    MineButtonStatus status;    // Button status

};

#endif // MINE_H
