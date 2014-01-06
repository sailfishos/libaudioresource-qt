
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


#include "player.h"


Player::Player()
    : QIODevice()
    , m_audio_resource(this, AudioResourceQt::AudioResource::MediaType)
    , m_audio_output(0)
{
    setOpenMode(QIODevice::ReadOnly);

    QObject::connect(&m_audio_resource, SIGNAL(acquiredChanged()),
                     this, SLOT(onAcquiredChanged()));
}

Player::~Player()
{
    delete m_audio_output;
}

qint64
Player::readData(char *data, qint64 maxSize)
{
    // Generate a sine wave
    static float pos = 0.f;
    short *d = (short *)(data);

    for (int i=0; i<maxSize / sizeof(short); i++) {
        *d++ = SHRT_MAX * sinf(pos) * 0.5;
        pos += 0.1;
    }

    return maxSize;
}

qint64
Player::writeData(const char *data, qint64 maxSize)
{
    return 0;
}

void
Player::play()
{
    m_audio_resource.acquire();
}

void
Player::onAcquiredChanged()
{
    bool acquired = m_audio_resource.isAcquired();

    qDebug() << __func__ << "->" << acquired;

    delete m_audio_output;
    m_audio_output = 0;

    if (acquired) {
        QAudioFormat format;
        format.setSampleRate(22050);
        format.setSampleSize(sizeof(short) * 8);
        format.setSampleType(QAudioFormat::SignedInt);
        format.setChannelCount(1);

        m_audio_output = new QAudioOutput(format);
        m_audio_output->start(this);
    }
}
