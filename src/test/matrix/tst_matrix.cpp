#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class TestMatrix : public QObject
{
    Q_OBJECT

public:
    TestMatrix();
    ~TestMatrix();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
    void test_case2();

};

TestMatrix::TestMatrix()
{

}

TestMatrix::~TestMatrix()
{

}

void TestMatrix::initTestCase()
{

}

void TestMatrix::cleanupTestCase()
{

}

void TestMatrix::test_case1()
{
    QCOMPARE(1, 1);
}

void TestMatrix::test_case2()
{
    QCOMPARE(1, 11);
}

QTEST_MAIN(TestMatrix)

#include "tst_matrix.moc"
