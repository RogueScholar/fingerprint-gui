#ifndef I18NHELPER_H
#define I18NHELPER_H
#include <QLocale>
#include <QTranslator>
#include <QApplication>
#ifndef LOCALE_DIR
#define LOCALE_DIR "."
#endif

void loadTranslations(QApplication *app) {
    QTranslator t;
    if (t.load(QLocale(), QString(""), QString(""), QString(LOCALE_DIR)))
        app->installTranslator(&t);
}
#endif // I18NHELPER_H
