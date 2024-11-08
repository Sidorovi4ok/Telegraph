QT += testlib
QT -= gui

CONFIG += c++2a
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_ringbuffer.cpp

include(../../RingBuffer.pri)
