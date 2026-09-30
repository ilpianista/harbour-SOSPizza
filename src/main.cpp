#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QtQml>

#include "calculator.h"

int main(int argc, char *argv[])
{
    qmlRegisterSingletonType<Calculator>("dev.scarpino.sospizza",
                                         1,
                                         0,
                                         "Calculator",
                                         [](QQmlEngine *, QJSEngine *) -> QObject * {
                                             return new Calculator;
                                         });
    return SailfishApp::main(argc, argv);
}
