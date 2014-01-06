
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


#ifndef LIBAUDIORESOURCEQT_AUDIORESOURCE_QT_H
#define LIBAUDIORESOURCEQT_AUDIORESOURCE_QT_H

#include <QObject>

#if defined(LIBAUDIORESOURCEQT_LIBRARY)
#  define AUDIORESOURCEQT_EXPORT Q_DECL_EXPORT
#else
#  define AUDIORESOURCEQT_EXPORT Q_DECL_IMPORT
#endif


namespace AudioResourceQt {

class AudioResourcePriv;

class AUDIORESOURCEQT_EXPORT AudioResource : public QObject {
    Q_OBJECT
    Q_ENUMS(ResourceType)

public:
    enum ResourceType {
        InvalidType = 0,
        GameType = 1,
        MediaType = 2,
    };

    explicit AudioResource(QObject *parent=0, enum AudioResource::ResourceType type=AudioResource::InvalidType);
    ~AudioResource();

    Q_PROPERTY(bool acquired READ isAcquired NOTIFY acquiredChanged)
    Q_PROPERTY(enum AudioResource::ResourceType resourceType READ resourceType WRITE setResourceType NOTIFY resourceTypeChanged)

    bool isAcquired();
    enum AudioResource::ResourceType resourceType();

signals:
    void acquiredChanged();
    void resourceTypeChanged();

public slots:
    bool acquire();
    bool release();
    void setResourceType(enum AudioResource::ResourceType type);

private:
    AudioResourcePriv *d;

    friend class AudioResourcePriv;
};

}; /* namespace AudioResourceQt */

#endif /* LIBAUDIORESOURCEQT_AUDIORESOURCE_QT_H */
