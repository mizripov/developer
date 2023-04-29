#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QtWidgets>

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);

private slots:
    void switch_type();
    void digitClicked();
    void piClicked();
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void pointClicked();
    void clearAll();

private:
    QLineEdit   *display;

    QVBoxLayout *qvb;

    QHBoxLayout *forRadioBtn;
    QVBoxLayout *twoBtn;

    QHBoxLayout *forButtons;
    QGridLayout *standart;
    QGridLayout *engineer;
    QGridLayout *all;

    QRadioButton *radio_button_standart;
    QRadioButton *radio_button_engineer;

    void createButton(QHBoxLayout *lay, const QString& name, const char *slot);
    void createButton(QGridLayout *lay, const QString& name, const char *slot,
                      int raw, int column, int rawSpan = 1, int columnSpan = 1);
    void initButtons();
    bool calculate(double rightOperand, const QString &pendingOperator);

    double sumSoFar;
    double factorSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;
};
#endif
