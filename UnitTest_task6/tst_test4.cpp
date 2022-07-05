#include <QtTest>
#include "/Users/y.dyba/Desktop/task_6.cpp"

// add necessary includes here

class test4 : public QObject
{
    Q_OBJECT

public:
    test4();
    ~test4();

private slots:
    void test_case1_dfs();

};

test4::test4()
{

}

test4::~test4()
{

}

void test4::test_case1_dfs()
{
 bool result = dfs(6);
 QCOMPARE(result, true);
}

QTEST_APPLESS_MAIN(test4)

#include "tst_test4.moc"
