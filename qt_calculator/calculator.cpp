#include <cmath>

#include "calculator.h"

Calculator::Calculator(QWidget *parent)
    : QWidget(parent), sumSoFar(0.0)
    , factorSoFar(0.0), waitingForOperand(true)
{
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    standart = new QGridLayout();
    engineer = new QGridLayout();
    all = new QGridLayout();
    initButtons();

    twoBtn = new QVBoxLayout();
    radio_button_standart = new QRadioButton(tr("Обычный"));
    radio_button_engineer = new QRadioButton(tr("Инженерный"));

    connect(radio_button_standart, SIGNAL(toggled(bool)),
            this                 , SLOT  (switch_type()));

    radio_button_standart->setChecked(true);
    twoBtn->addWidget(radio_button_standart);
    twoBtn->addWidget(radio_button_engineer);

    forRadioBtn = new QHBoxLayout();
    forRadioBtn->addLayout(twoBtn, 10);
    createButton(forRadioBtn, "C", SLOT(clearAll()));

    forButtons = new QHBoxLayout();
    forButtons->addLayout(engineer);
    forButtons->addLayout(standart);

    qvb = new QVBoxLayout();
    qvb->addWidget(display);
    qvb->addLayout(forRadioBtn, 1);
    qvb->addLayout(forButtons, 5);

    setLayout(qvb);
}

void Calculator::switch_type()
{
    if (radio_button_standart->isChecked()) {
        for(int i = 0; i < 4; ++i)
        {
            for(int j = 0; j < 4; ++j)
            {
                engineer->itemAtPosition(i, j)->widget()->hide();
            }
        }

        setWindowTitle("Калькулятор(Обычный)");
    } else {
        for(int i = 0; i < 4; ++i)
        {
            for(int j = 0; j < 4; ++j)
            {
                engineer->itemAtPosition(i, j)->widget()->show();
            }
        }
        setWindowTitle("Калькулятор(Инженерный)");
    }
}

void Calculator::digitClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (display->text() == "0" && digitValue == 0.0)
        return;

    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    display->setText(display->text() + QString::number(digitValue));
}

void Calculator::piClicked()
{
    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    display->setText(QString::number(M_PI));
}

void Calculator::unaryOperatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    //
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;

    if (clickedOperator == "sqrt") {
        if (operand < 0.0) {
            clearAll();
            return;
        }
        result = std::sqrt(operand);
    } else if (clickedOperator == "1/x") {
        if (operand == 0.0) {
            clearAll();
            return;
        }
        result = 1/ operand;
    } else if (clickedOperator == "sinh") {
        result = std::sinh(operand);
    } else if (clickedOperator == "sin") {
        result = std::sin(operand);
    } else if (clickedOperator == "exp") {
        result = std::exp(operand);
    } else if (clickedOperator == "x^2") {
        result = std::pow(operand, 2);
    } else if (clickedOperator == "cosh") {
        result = std::cosh(operand);
    } else if (clickedOperator == "cos") {
        result = std::cos(operand);
    } else if (clickedOperator == "ln") {
        result = std::log(operand);
    } else if (clickedOperator == "x^3") {
        result = std::pow(operand, 3);
    } else if (clickedOperator == "tanh") {
        result = std::tanh(operand);
    } else if (clickedOperator == "tan") {
        result = std::tan(operand);
    } else if (clickedOperator == "tan") {
        result = std::tanh(operand);
    } else if (clickedOperator == "log") {
        result = std::log10(operand);
    } else if (clickedOperator == "n!") {
        result = std::tgamma(operand + 1);
    } else if (clickedOperator == "x^1/3") {
        result = std::pow(operand, 1.0 / 3.0);
    }

    display->setText(QString::number(result));
    waitingForOperand = true;
}

void Calculator::additiveOperatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton)
        return;
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            clearAll();
            return;
        }
        display->setText(QString::number(factorSoFar));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            clearAll();
            return;
        }
        display->setText(QString::number(sumSoFar));
    } else {
        sumSoFar = operand;
    }
    pendingAdditiveOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::multiplicativeOperatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton)
        return;
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            clearAll();
            return;
        }
        display->setText(QString::number(factorSoFar));
    } else {
        factorSoFar = operand;
    }
    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::equalClicked()
{
    double operand = display->text().toDouble();
    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            clearAll();
            return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            clearAll();
            return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand;
    }
    display->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}

void Calculator::pointClicked()
{
    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains("."))
        display->setText(display->text() + ".");
    waitingForOperand = false;
}

void Calculator::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}

void Calculator::createButton(QHBoxLayout *lay, const QString& name, const char *slot)
{
    QPushButton *btn = new QPushButton(name);
    btn->setMinimumSize(40, 40);
    btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    lay->addWidget(btn, 1);
    connect(btn, SIGNAL(clicked()), this, slot);
}

void Calculator::createButton(QGridLayout *lay, const QString& name, const char *slot,
                  int raw, int column, int rawSpan, int columnSpan)
{
    QPushButton *btn = new QPushButton(name);
    btn->setMinimumSize(40, 40);
    btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    lay->addWidget(btn, raw, column, rawSpan, columnSpan);
    connect(btn, SIGNAL(clicked()), this, slot);
}

void Calculator::initButtons()
{
    QString e_name[] = { "sinh", "sin", "exp"  , "x^2",
                         "cosh", "cos", "ln"   , "x^3",
                         "tanh", "tan", "log"  , "x^y",
                         "n!"  , "pi" , "x^1/3", "x^1/y"
                       };

    const char* slot;
    for (int i = 0; i < 16; i++) {
        switch (i) {
            case 0 ... 10: // sinh, sin, exp, x^2, cosh, cos, ln, x^3, tanh, tan, log
            case 12:       // n!
            case 14:       // x^1/3
                slot = SLOT(unaryOperatorClicked());
                break;
            case 11:       // x^y
            case 15:       // x^1/y
                slot = SLOT(multiplicativeOperatorClicked());
                break;
            case 13:       // pi
                slot = SLOT(piClicked());
                break;
        }
        createButton(engineer, e_name[i], slot, i / 4, i % 4);
    }

    QString s_name[18] = { "7", "8", "9", "/", "sqrt",
                           "4", "5", "6", "*", "1/x",
                           "1", "2", "3", "-", "=",
                           "0", ".", "+"
                         };

    int raw, column, rawSpan, columnSpan;
    for (int i = 0; i <= 17; i++) {
        raw = i / 5;
        column = i % 5;
        rawSpan = 1;
        columnSpan = 1;
        switch (i) {
            case 0 ... 2:   // 7, 8, 9
            case 5 ... 7:   // 4, 5, 6
            case 10 ... 12: // 1, 2, 3
                slot = SLOT(digitClicked());
                break;
            case 3:         // '/'
            case 8:         // '*'
                slot = SLOT(multiplicativeOperatorClicked());
                break;
            case 13:        // '-'
                slot = SLOT(additiveOperatorClicked());
                break;
            case 4:         // sqrt
            case 9:         // 1/x
                slot = SLOT(unaryOperatorClicked());
                break;
            case 14:        // '='
                slot = SLOT(equalClicked());
                rawSpan = 2;
                columnSpan = 1;
                break;
            case 15:        // 0
                slot = SLOT(digitClicked());
                rawSpan = 1;
                columnSpan = 2;
                break;
            case 16:        // '.'
                slot = SLOT(pointClicked());
                raw = (i + 1) / 5;
                column = (i + 1) % 5;
                break;
            case 17:        // '+'
                slot = SLOT(additiveOperatorClicked());
                raw = (i + 1) / 5;
                column = (i + 1) % 5;
                break;
        }
        createButton(standart, s_name[i], slot, raw, column, rawSpan, columnSpan);
    }
}

bool Calculator::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == "/") {
        if (rightOperand == 0.0)
            return false;
        factorSoFar /= rightOperand;
    } else if (pendingOperator == "*") {
        factorSoFar *= rightOperand;
    } else if (pendingOperator == "+") {
        sumSoFar += rightOperand;
    } else if (pendingOperator == "-") {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == "x^y") {
        factorSoFar = std::pow(factorSoFar, rightOperand);
    } else if (pendingOperator == "x^1/y") {
        factorSoFar = std::pow(factorSoFar, 1.0 / rightOperand);
    }
    return true;
}
