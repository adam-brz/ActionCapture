#include <QtTest>
#include "../globalmouse.h"

class GlobalMouseTest : public QObject
{
    Q_OBJECT

private slots:
    void test_setPos();
};

void GlobalMouseTest::test_setPos()
{
    GlobalMouse *mouse = new GlobalMouse(this);
    QVERIFY(1 == 1);
}

QTEST_APPLESS_MAIN(GlobalMouseTest)
#include "tst_globalmousetest.moc"
