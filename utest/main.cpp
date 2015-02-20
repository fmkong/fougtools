#include <QtCore/QCoreApplication>
#include <QtCore/QList>
#include <QtCore/QtDebug>

#include "test_cpptools.h"
#include "test_qttools_core.h"
#include "test_qttools_gui.h"
#include "test_qttools_script.h"
#ifdef FOUGTOOLS_OCCTOOLS
# include "test_occtools.h"
#endif // FOUGTOOLS_OCCTOOLS

#include <iostream>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    Q_UNUSED(app);

    // Parse command line
    QStringList argList;
    for (int i = 0; i < argc; ++i)
        argList.append(QString(argv[i]));

    // Run tests
    QList<QObject*> testObjects;
    testObjects << new TestCppTools
                << new TestQtToolsCore
                << new TestQtToolsGui
                << new TestQtToolsScript;
#ifdef FOUGTOOLS_OCCTOOLS
    testObjects << new TestOccTools;
#endif // FOUGTOOLS_OCCTOOLS

    int exitCode = 0;
    foreach (QObject* iTestObject, testObjects)
        exitCode += QTest::qExec(iTestObject, argList);

    if (exitCode != 0)
        std::cout << exitCode << " failed" << std::endl;
    qDeleteAll(testObjects);
    return exitCode;
}
