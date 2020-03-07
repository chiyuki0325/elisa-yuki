/*
 * Copyright 2016 Matthieu Gallien <matthieu_gallien@yahoo.fr>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MANAGEHEADERBAR_H
#define MANAGEHEADERBAR_H

#include "elisaLib_export.h"

#include "elisautils.h"

#include <QObject>
#include <QPersistentModelIndex>
#include <QUrl>

class ELISALIB_EXPORT ManageHeaderBar : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPersistentModelIndex currentTrack
               READ currentTrack
               WRITE setCurrentTrack
               NOTIFY currentTrackChanged)

    Q_PROPERTY(int artistRole
               READ artistRole
               WRITE setArtistRole
               NOTIFY artistRoleChanged)

    Q_PROPERTY(int titleRole
               READ titleRole
               WRITE setTitleRole
               NOTIFY titleRoleChanged)

    Q_PROPERTY(int albumRole
               READ albumRole
               WRITE setAlbumRole
               NOTIFY albumRoleChanged)

    Q_PROPERTY(int albumArtistRole
               READ albumArtistRole
               WRITE setAlbumArtistRole
               NOTIFY albumArtistRoleChanged)

    Q_PROPERTY(int fileNameRole
               READ fileNameRole
               WRITE setFileNameRole
               NOTIFY fileNameRoleChanged)

    Q_PROPERTY(int imageRole
               READ imageRole
               WRITE setImageRole
               NOTIFY imageRoleChanged)

    Q_PROPERTY(int databaseIdRole
               READ databaseIdRole
               WRITE setDatabaseIdRole
               NOTIFY databaseIdRoleChanged)

    Q_PROPERTY(int trackTypeRole
               READ trackTypeRole
               WRITE setTrackTypeRole
               NOTIFY trackTypeRoleChanged)

    Q_PROPERTY(int albumIdRole
               READ albumIdRole
               WRITE setAlbumIdRole
               NOTIFY albumIdRoleChanged)

    Q_PROPERTY(int isValidRole
               READ isValidRole
               WRITE setIsValidRole
               NOTIFY isValidRoleChanged)

    Q_PROPERTY(QVariant artist
               READ artist
               NOTIFY artistChanged)

    Q_PROPERTY(QVariant title
               READ title
               NOTIFY titleChanged)

    Q_PROPERTY(QVariant album
               READ album
               NOTIFY albumChanged)

    Q_PROPERTY(QVariant albumArtist
               READ albumArtist
               NOTIFY albumArtistChanged)

    Q_PROPERTY(QUrl fileUrl
               READ fileUrl
               NOTIFY fileUrlChanged)

    Q_PROPERTY(QUrl image
               READ image
               NOTIFY imageChanged)

    Q_PROPERTY(qulonglong databaseId
               READ databaseId
               NOTIFY databaseIdChanged)

    Q_PROPERTY(ElisaUtils::PlayListEntryType trackType
               READ trackType
               NOTIFY trackTypeChanged)

    Q_PROPERTY(qulonglong albumId
               READ albumId
               NOTIFY albumIdChanged)

    Q_PROPERTY(bool isValid
               READ isValid
               NOTIFY isValidChanged)

public:

    explicit ManageHeaderBar(QObject *parent = nullptr);

    QPersistentModelIndex currentTrack() const;

    int artistRole() const;

    int titleRole() const;

    int albumRole() const;

    int albumArtistRole() const;

    int fileNameRole() const;

    int imageRole() const;

    int databaseIdRole() const;

    int trackTypeRole() const;

    int albumIdRole() const;

    int isValidRole() const;

    QVariant artist() const;

    QVariant title() const;

    QVariant album() const;

    QVariant albumArtist() const;

    QUrl fileUrl() const;

    QUrl image() const;

    qulonglong databaseId() const;

    ElisaUtils::PlayListEntryType trackType() const;

    qulonglong albumId() const;

    bool isValid() const;

Q_SIGNALS:

    void currentTrackChanged();

    void artistRoleChanged();

    void titleRoleChanged();

    void albumRoleChanged();

    void albumArtistRoleChanged();

    void fileNameRoleChanged();

    void imageRoleChanged();

    void databaseIdRoleChanged();

    void trackTypeRoleChanged();

    void albumIdRoleChanged();

    void isValidRoleChanged();

    void artistChanged();

    void titleChanged();

    void albumChanged();

    void albumArtistChanged();

    void fileUrlChanged();

    void imageChanged();

    void databaseIdChanged();

    void albumIdChanged();

    void trackTypeChanged();

    void isValidChanged();

public Q_SLOTS:

    void setCurrentTrack(const QPersistentModelIndex &currentTrack);

    void updateCurrentTrackData();

    void setArtistRole(int value);

    void setTitleRole(int value);

    void setAlbumRole(int value);

    void setAlbumArtistRole(int value);

    void setFileNameRole(int value);

    void setImageRole(int value);

    void setDatabaseIdRole(int databaseIdRole);

    void setTrackTypeRole(int trackTypeRole);

    void setAlbumIdRole(int albumIdRole);

    void setIsValidRole(int isValidRole);

private:

    void notifyArtistProperty();

    void notifyTitleProperty();

    void notifyAlbumProperty();

    void notifyAlbumArtistProperty();

    void notifyFileNameProperty();

    void notifyImageProperty();

    void notifyDatabaseIdProperty();

    void notifyTrackTypeProperty();

    void notifyAlbumIdProperty();

    void notifyIsValidProperty();

    QPersistentModelIndex mCurrentTrack;

    int mArtistRole = Qt::DisplayRole;

    int mTitleRole = Qt::DisplayRole;

    int mAlbumRole = Qt::DisplayRole;

    int mAlbumArtistRole = Qt::DisplayRole;

    int mFileNameRole = Qt::DisplayRole;

    int mImageRole = Qt::DisplayRole;

    int mDatabaseIdRole = Qt::DisplayRole;

    int mTrackTypeIdRole = Qt::DisplayRole;

    int mAlbumIdRole = Qt::DisplayRole;

    int mIsValidRole = Qt::DisplayRole;

    QVariant mOldArtist;

    QVariant mOldTitle;

    QVariant mOldAlbum;

    QVariant mOldAlbumArtist;

    QVariant mOldFileName;

    QVariant mOldImage;

    qulonglong mOldDatabaseId = 0;

    ElisaUtils::PlayListEntryType mOldTrackType = ElisaUtils::Unknown;

    qulonglong mOldAlbumId = 0;

    bool mOldIsValid = false;

};



#endif // MANAGEHEADERBAR_H
