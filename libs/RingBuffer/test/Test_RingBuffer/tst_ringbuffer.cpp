#include <QtTest>
#include <QRandomGenerator>

// add necessary includes here
#include <RingBuffer.h>

class TestRingBuffer : public QObject
{
    Q_OBJECT

public:
    TestRingBuffer();
    ~TestRingBuffer();

private slots:
    void test_resize();
    void test_readWrite();
    void test_correctData();
    void test_stress();
};

TestRingBuffer::TestRingBuffer()
{

}

TestRingBuffer::~TestRingBuffer()
{

}

void TestRingBuffer::test_resize()
{
    RingBuffer ringBuffer;

    QCOMPARE(ringBuffer.size(), 0);

    ringBuffer.resize(1000);
    QCOMPARE(ringBuffer.size(), 1000);

    ringBuffer.resize(2000);
    QCOMPARE(ringBuffer.size(), 2000);
}

void TestRingBuffer::test_readWrite()
{
    RingBuffer ringBuffer;

    ringBuffer.resize(1000);

    QCOMPARE(ringBuffer.readCount(), 0);
    QCOMPARE(ringBuffer.writeCount(), 1000);

    std::vector<float> data; data.resize(100);

    // Тест записи
    QCOMPARE(ringBuffer.write(data), true);
    QCOMPARE(ringBuffer.readCount(), data.size());
    QCOMPARE(ringBuffer.writeCount(), ringBuffer.size() - data.size());

    // Тест чтения
    QCOMPARE(ringBuffer.read(data), true);
    QCOMPARE(ringBuffer.readCount(), 0);
    QCOMPARE(ringBuffer.writeCount(), ringBuffer.size());


    data.resize(600);

    QCOMPARE(ringBuffer.write(data), true);
    QCOMPARE(ringBuffer.readCount(), data.size());
    QCOMPARE(ringBuffer.writeCount(), ringBuffer.size() - data.size());

    QCOMPARE(ringBuffer.read(data), true);
    QCOMPARE(ringBuffer.readCount(), 0);
    QCOMPARE(ringBuffer.writeCount(), ringBuffer.size());

    QCOMPARE(ringBuffer.write(data), true);
    QCOMPARE(ringBuffer.readCount(), data.size());
    QCOMPARE(ringBuffer.writeCount(), ringBuffer.size() - data.size());

    QCOMPARE(ringBuffer.read(data), true);
    QCOMPARE(ringBuffer.readCount(), 0);
    QCOMPARE(ringBuffer.writeCount(), ringBuffer.size());

}

void TestRingBuffer::test_correctData()
{
    RingBuffer ringBuffer;
    ringBuffer.resize(1000);

    std::vector<float> dataSrc1; dataSrc1.resize(600);
    std::vector<float> dataSrc2; dataSrc2.resize(300);
    std::vector<float> dataSrc3; dataSrc3.resize(500);

    std::vector<float> dataDst;

    for (auto &sample : dataSrc1)
        sample = QRandomGenerator::global()->generate();

    for (auto &sample : dataSrc2)
        sample = QRandomGenerator::global()->generate();

    for (auto &sample : dataSrc3)
        sample = QRandomGenerator::global()->generate();

    ringBuffer.write(dataSrc1);
    ringBuffer.write(dataSrc2);

    dataDst.resize(dataSrc1.size());
    ringBuffer.read(dataDst);

    bool correct {true};
    for (std::size_t i {0}; i < dataSrc1.size(); ++i) {
        correct &= qFuzzyCompare(dataSrc1.at(i), dataDst.at(i)); // Логическое умножение
    }
    QCOMPARE(correct, true);

    ringBuffer.write(dataSrc3);
    dataDst.resize(dataSrc2.size());
    ringBuffer.read(dataDst);

    correct = true;
    for (std::size_t i {0}; i < dataSrc2.size(); ++i) {
        correct &= qFuzzyCompare(dataSrc2.at(i), dataDst.at(i)); // Логическое умножение
    }
    QCOMPARE(correct, true);

    dataDst.resize(dataSrc3.size());
    ringBuffer.read(dataDst);

    correct = true;
    for (std::size_t i {0}; i < dataSrc3.size(); ++i) {
        correct &= qFuzzyCompare(dataSrc3.at(i), dataDst.at(i)); // Логическое умножение
    }
    QCOMPARE(correct, true);
}

void TestRingBuffer::test_stress()
{
    RingBuffer ringBuffer;
    ringBuffer.resize(1000);

    std::vector<float> dataSrc; dataSrc.resize(1001);
    QCOMPARE(ringBuffer.read(dataSrc), false);
    QCOMPARE(ringBuffer.write(dataSrc), false);

    dataSrc.resize(600);
    QCOMPARE(ringBuffer.write(dataSrc), true);

    dataSrc.resize(400);
    QCOMPARE(ringBuffer.read(dataSrc), true);
    QCOMPARE(ringBuffer.read(dataSrc), false);

    dataSrc.resize(200);
    QCOMPARE(ringBuffer.read(dataSrc), true);
}

QTEST_APPLESS_MAIN(TestRingBuffer)

#include "tst_ringbuffer.moc"
