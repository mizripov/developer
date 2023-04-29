#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QPainter>

#include "notepad.h"

class CodeEdit;
class LineNumberArea;

class CodeEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEdit(QWidget *parent = nullptr);
    int lineNumberAreaWidth();
    void lineNumberAreaPaintEvent(QPaintEvent*);

protected:
    void resizeEvent(QResizeEvent*) override;

private slots:
    void updateLineNumberAreaWidth();
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect&, int);

private:
    QWidget *lineNumberArea;
};

class LineNumberArea : public QWidget
{
public:
    explicit LineNumberArea(CodeEdit*);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent*) override;

private:
    CodeEdit *codeEdit;
};

#endif // LINENUMBERAREA_H
