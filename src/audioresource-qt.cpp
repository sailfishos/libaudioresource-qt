
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


#include "audioresource-qt.h"
#include "audioresource.h"

namespace AudioResourceQt {

static audioresource_type_t
atype_from_qttype(enum AudioResource::MediaType type)
{
    switch (type) {
        case AudioResource::Invalid:
            return AUDIO_RESOURCE_INVALID;
        case AudioResource::Game:
            return AUDIO_RESOURCE_GAME;
        case AudioResource::Media:
            return AUDIO_RESOURCE_MEDIA;
    }

    return AUDIO_RESOURCE_INVALID;
}

class AudioResourcePriv {
public:
    AudioResourcePriv()
        : type(AudioResource::Invalid)
        , atype(atype_from_qttype(type))
        , acquired(false)
        , audioresource(0)
    {
    }

    ~AudioResourcePriv()
    {
        if (audioresource) {
            audioresource_free(audioresource);
        }
    }

    static void acquired_cb(audioresource_t *audio_resource,
            bool acquired, void *user_data);

    enum AudioResource::MediaType type;
    enum audioresource_type_t atype;
    bool acquired;
    audioresource_t *audioresource;
};

void
AudioResourcePriv::acquired_cb(audioresource_t *audio_resource,
        bool acquired, void *user_data)
{
    AudioResource *resource = static_cast<AudioResource *>(user_data);
    resource->setAcquired(acquired);
}


AudioResource::AudioResource(QObject *parent, enum AudioResource::MediaType type)
    : QObject(parent)
    , d(new AudioResourcePriv())
{
    setMediaType(type);
}

AudioResource::~AudioResource()
{
    delete d;
}

bool
AudioResource::acquire()
{
    if (d->audioresource) {
        audioresource_acquire(d->audioresource);
        return true;
    }

    return false;
}

bool
AudioResource::release()
{
    if (d->audioresource) {
        audioresource_release(d->audioresource);
        return true;
    }

    return false;
}

bool
AudioResource::acquired()
{
    return d->acquired;
}

void
AudioResource::setAcquired(bool acquired)
{
    if (acquired != d->acquired) {
        d->acquired = acquired;
        emit acquiredChanged();
    }
}

enum AudioResource::MediaType
AudioResource::mediaType()
{
    return d->type;
}

void
AudioResource::setMediaType(enum AudioResource::MediaType type)
{
    if (d->type == type && (type == AudioResource::Invalid || d->audioresource)) {
        // No need to change anything
        return;
    }

    bool oldAcquired = acquired();

    if (d->audioresource) {
        audioresource_free(d->audioresource);
        setAcquired(false);
    }

    d->type = type;
    d->atype = atype_from_qttype(d->type);

    if (d->atype != AUDIO_RESOURCE_INVALID) {
        d->audioresource = audioresource_init(d->atype,
                AudioResourcePriv::acquired_cb, this);

        if (oldAcquired) {
            // Re-acquire audio resource
            acquire();
        }
    }

    emit mediaTypeChanged();
}

}; /* namespace AudioResourceQt */
