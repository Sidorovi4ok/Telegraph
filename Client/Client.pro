TEMPLATE = app      # Тип исполняемого файла
TARGET   = Client   # Название

# Подключение модулей QT6
QT += core quick network websockets

# Указываение стандарта c++
CONFIG += c++2a

# Дирректория куда помещается exe файл
DESTDIR = ../bin

# Установка иконки приложения
win32:RC_FILE = resources.rc

SOURCES += source/main.cpp

HEADERS += source/Kernel.h
SOURCES += source/Kernel.cpp

HEADERS += source/gui/MainWindow.h
SOURCES += source/gui/MainWindow.cpp

HEADERS += source/network/Network.h
SOURCES += source/network/Network.cpp

HEADERS += source/network/connection/Connection.h
SOURCES += source/network/connection/Connection.cpp

HEADERS += source/network/connection/message/Message.h
SOURCES += source/network/connection/message/Message.cpp

HEADERS += source/gui/storage/Storage.h
SOURCES += source/gui/storage/Storage.cpp

HEADERS += source/gui/wavreader/WavReader.h
SOURCES += source/gui/wavreader/WavReader.cpp

RESOURCES += resources/resources.qrc 