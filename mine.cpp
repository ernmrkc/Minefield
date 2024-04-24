#include "Mine.h"
#include "Minefield.h"

Mine::Mine(int row, int col, bool mineStatus, QWidget *parent) : QPushButton(parent)
{
    this->status = available;
    this->row = row;
    this->col = col;
    this->isMine = mineStatus;
}

Mine::~Mine()
{

}

void Mine::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        switch(status){
        case available:
            this->status = flag;
            setText("!");
            break;
        case flag:
            this->status = uncertain;
            setText("?");
            break;
        case uncertain:
            this->status = available;
            setText("");
            break;
        default: ;
        }
    }else
    {
        if(this->status == available){
            if(this->checkMine())
            {
                setText("X");
                setEnabled(false);

                QMessageBox messageBox;
                messageBox.setWindowTitle("Game Over");
                messageBox.setIcon(QMessageBox::Warning);
                messageBox.setText("BOOM");

                // Get buttons and rename
                QPushButton* restartButton = messageBox.addButton(QMessageBox::Ok);
                QPushButton* cancelButton = messageBox.addButton(QMessageBox::Cancel);

                // Change button texts
                restartButton->setText("Restart");
                cancelButton->setText("Exit");

                // Bind quit event to CancelButton
                QObject::connect(cancelButton, &QPushButton::clicked, QApplication::instance(), &QApplication::quit);

                // Reach related parent object
                Minefield *field = qobject_cast<Minefield *>(this->parentWidget()->parentWidget());
                if (field)
                {
                    // Bind the restart function of the relevant object to the RestartButton
                    QObject::connect(restartButton, &QPushButton::clicked, field, &Minefield::restartGame);
                }

                messageBox.exec();

            }else
            {
                setText(QString::number(this->value));
                setEnabled(false);
            }
        }
    }
}

bool Mine::checkMine()
{
    return this->isMine;
}

void Mine::setMine(bool mineStatus)
{
    this->isMine = mineStatus;
}

void Mine::setValue(int value)
{
    this->value = value;
}

Mine::MineButtonStatus Mine::getStatus()
{
    return status;
}

void Mine::setStatus(MineButtonStatus newStatus)
{
    status = newStatus;
}
