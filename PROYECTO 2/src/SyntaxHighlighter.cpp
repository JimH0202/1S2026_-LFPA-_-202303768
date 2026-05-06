#include "SyntaxHighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument* parent)
    : QSyntaxHighlighter(parent) {

    // Formato para palabras clave
    keywordFormat.setForeground(Qt::blue);
    keywordFormat.setFontWeight(QFont::Bold);

    // Formato para strings
    stringFormat.setForeground(Qt::darkGreen);

    // Formato para números/fechas
    numberFormat.setForeground(Qt::darkRed);

    // Formato para delimitadores
    delimiterFormat.setForeground(Qt::darkMagenta);
    delimiterFormat.setFontWeight(QFont::Bold);

    // Formato para comentarios (si se implementan)
    commentFormat.setForeground(Qt::gray);
    commentFormat.setFontItalic(true);

    // Reglas de resaltado

    // Palabras clave principales
    QStringList keywords = {
        "TABLERO", "COLUMNA", "TAREA", "PRIORIDAD",
        "RESPONSABLE", "FECHA_LIMITE", "DESCRIPCION"
    };

    for (const QString& keyword : keywords) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression("\\b" + keyword + "\\b");
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // Valores de prioridad
    QStringList priorities = {"ALTA", "MEDIA", "BAJA"};
    for (const QString& priority : priorities) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression("\\b" + priority + "\\b");
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // Strings entre comillas dobles
    HighlightingRule stringRule;
    stringRule.pattern = QRegularExpression("\"[^\"]*\"");
    stringRule.format = stringFormat;
    highlightingRules.append(stringRule);

    // Números (fechas y enteros)
    HighlightingRule numberRule;
    numberRule.pattern = QRegularExpression("\\b\\d+\\b");
    numberRule.format = numberFormat;
    highlightingRules.append(numberRule);

    // Delimitadores
    QStringList delimiters = {"\\{", "\\}", "\\[", "\\]", ",", ":"};
    for (const QString& delimiter : delimiters) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(delimiter);
        rule.format = delimiterFormat;
        highlightingRules.append(rule);
    }
}

void SyntaxHighlighter::highlightBlock(const QString& text) {
    for (const HighlightingRule& rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    // Resaltado de comentarios de línea (si se implementan en el futuro)
    // QRegularExpression commentRegex("//[^\n]*");
    // setFormat para comentarios...
}