
/**
 *
 * Copyright (C) 2013 Jolla Ltd.
 * Contact: Thomas Perl <thomas.perl@jolla.com>
 * All rights reserved.
 *
 * This file is part of libaudioresource-qt
 *
 * You may use this file under the terms of the GNU Lesser General
 * Public License version 2.1 as published by the Free Software Foundation
 * and appearing in the file COPYING.LGPL included in the packaging
 * of this file.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation
 * and appearing in the file license.lgpl included in the packaging
 * of this file.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 **/


#ifndef AUDIORESOURCEQT_EXAMPLE_PLAYER_H
#define AUDIORESOURCEQT_EXAMPLE_PLAYER_H

#include <QtCore>
#include <QtMultimedia>
#include <AudioResourceQt>


class Player : public QIODevice {
    Q_OBJECT

public:
    Player();
    ~Player();

    virtual qint64 readData(char *data, qint64 maxSize);
    virtual qint64 writeData(const char *data, qint64 maxSize);

    void play();

public slots:
    void onAcquiredChanged();

private:
    AudioResourceQt::AudioResource m_audio_resource;
    QAudioOutput *m_audio_output;
};

#endif /* AUDIORESOURCEQT_EXAMPLE_PLAYER_H */
