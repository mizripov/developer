#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QXmlStreamReader>
#include <QRegularExpression>

struct HighlightingRule
{
    QRegularExpression pattern;
    QTextCharFormat format;
};

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    QXmlStreamReader xmlStream;
    QString fileExspression;

    explicit Highlighter(QTextDocument *parent, const QVector<HighlightingRule>&);
    void setCommentStartExspression(const QString&);
    void setCommentEndExspression(const QString&);

protected:
    void highlightBlock(const QString&) override;

private:
    QVector<HighlightingRule> highlightingRules;
    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;
    QTextCharFormat multiLineCommentFormat;

};

#endif // HIGHLIGHTER_H
