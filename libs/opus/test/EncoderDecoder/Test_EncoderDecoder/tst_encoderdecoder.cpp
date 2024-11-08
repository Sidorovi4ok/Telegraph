#include <QtTest>

// add necessary includes here
#include <copus.h>
#include <PortAudioWraper.h>

class EncoderDecoder : public QObject
{
    Q_OBJECT

public:
    EncoderDecoder();
    ~EncoderDecoder();

private slots:
    void test_init();
    void test_encoderDecoder();

};

EncoderDecoder::EncoderDecoder()
{

}

EncoderDecoder::~EncoderDecoder()
{

}

void EncoderDecoder::test_init()
{
    opus::encoder t_encoder;
    QCOMPARE(t_encoder.init(48000, 1, opus::AudioMode::VoIP), true);
    QCOMPARE(t_encoder.isInit(), true);

    opus::decoder t_decoder;
    QCOMPARE(t_decoder.init(48000, 1), true);
    QCOMPARE(t_decoder.isInit(), true);
}

void EncoderDecoder::test_encoderDecoder()
{
    opus::encoder t_encoder;
    QCOMPARE(t_encoder.init(48000, 1, opus::AudioMode::VoIP), true);

    std::vector<float> src1; src1.resize(960);

    for (auto &data : src1)
        data = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);

    std::vector<std::uint8_t> dst1; dst1.resize(130);

    auto resEncoder = t_encoder.procces(src1, dst1);

    opus::decoder t_decoder;
    QCOMPARE(t_decoder.init(48000, 1), true);

    std::vector<float> dst2; dst2.resize(src1.size());

    auto resDecoder = t_decoder.procces(dst1, dst2);
}

QTEST_APPLESS_MAIN(EncoderDecoder)

#include "tst_encoderdecoder.moc"
