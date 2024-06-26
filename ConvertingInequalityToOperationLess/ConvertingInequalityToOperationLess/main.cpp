#include <QCoreApplication>
#include "Functions.h"
#include "Error.h"
#include "Tree.h"
#include "Tests.h"

int main(int argc, char *argv[])
{
    runTests();
    QCoreApplication a(argc, argv);

    return a.exec();
}
