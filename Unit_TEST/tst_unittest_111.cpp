#include <QtTest>
#include "functions.h"
// add necessary includes here

class UnitTest_111 : public QObject
{
    Q_OBJECT

public:
    UnitTest_111();
    ~UnitTest_111();

private slots:
    void test_parsing_auth();

};

UnitTest_111::UnitTest_111()
{

}

UnitTest_111::~UnitTest_111()
{

}

void UnitTest_111::test_parsing_auth()
{
QString s = "auth&user&user";
QCOMPARE(parsing(s),"Authorized");
}

QTEST_APPLESS_MAIN(UnitTest_111)

#include "tst_unittest_111.moc"
