/*
   SPDX-FileCopyrightText: 2020 (c) Matthieu Gallien <matthieu_gallien@yahoo.fr>

   SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include "viewconfigurationdata.h"

class ViewConfigurationDataPrivate
{
public:
    ViewConfigurationDataPrivate()
    = default;

    // Grid/List views
    ViewConfigurationDataPrivate(ElisaUtils::FilterType filterType, int expectedDepth,
                                 QString mainTitle, QString secondaryTitle,
                                 QUrl imageUrl, ElisaUtils::PlayListEntryType dataType,
                                 QAbstractItemModel *model, QAbstractProxyModel *associatedProxyModel,
                                 QUrl viewDefaultIcon, DataTypes::DataType dataFilter,
                                 int sortRole, QList<int> sortRoles, QList<QString> sortRoleNames,
                                 Qt::SortOrder sortOrder, QList<QString> sortOrderNames,
                                 ViewManager::ViewCanBeRated viewShowRating,
                                 ViewManager::DelegateUseSecondaryText viewDelegateDisplaySecondaryText,
                                 ViewManager::ViewStyle viewStyle)
        : mFilterType(filterType)
        , mExpectedDepth(expectedDepth)
        , mMainTitle(std::move(mainTitle))
        , mSecondaryTitle(std::move(secondaryTitle))
        , mImageUrl(std::move(imageUrl))
        , mDataType(dataType)
        , mModel(model)
        , mAssociatedProxyModel(associatedProxyModel)
        , mViewDefaultIcon(std::move(viewDefaultIcon))
        , mDataFilter(std::move(dataFilter))
        , mViewShowRating(viewShowRating)
        , mViewDelegateDisplaySecondaryText(viewDelegateDisplaySecondaryText)
        , mSortRole(sortRole)
        , mSortRoles(std::move(sortRoles))
        , mSortRoleNames(std::move(sortRoleNames))
        , mSortOrder(sortOrder)
        , mSortOrderNames(std::move(sortOrderNames))
        , mViewStyle(viewStyle)
    {
    }

    // Track views
    ViewConfigurationDataPrivate(ElisaUtils::FilterType filterType, int expectedDepth,
                                 QString mainTitle, QString secondaryTitle,
                                 QUrl imageUrl, ElisaUtils::PlayListEntryType dataType,
                                 QAbstractItemModel *model, QAbstractProxyModel *associatedProxyModel,
                                 DataTypes::DataType dataFilter,
                                 int sortRole, QList<int> sortRoles, QList<QString> sortRoleNames,
                                 Qt::SortOrder sortOrder, QList<QString> sortOrderNames,
                                 ViewManager::AlbumCardinality displaySingleAlbum,
                                 ViewManager::AlbumViewStyle showDiscHeaders)
        : mFilterType(filterType)
        , mExpectedDepth(expectedDepth)
        , mMainTitle(std::move(mainTitle))
        , mSecondaryTitle(std::move(secondaryTitle))
        , mImageUrl(std::move(imageUrl))
        , mDataType(dataType)
        , mModel(model)
        , mAssociatedProxyModel(associatedProxyModel)
        , mDataFilter(std::move(dataFilter))
        , mSortRole(sortRole)
        , mSortRoles(std::move(sortRoles))
        , mSortRoleNames(std::move(sortRoleNames))
        , mSortOrder(sortOrder)
        , mSortOrderNames(std::move(sortOrderNames))
        , mDisplaySingleAlbum(displaySingleAlbum)
        , mShowDiscHeaders(showDiscHeaders)
    {
    }

    ElisaUtils::FilterType mFilterType;

    int mExpectedDepth;

    QString mMainTitle;

    QString mSecondaryTitle;

    QUrl mImageUrl;

    ElisaUtils::PlayListEntryType mDataType;

    QAbstractItemModel * mModel;

    QAbstractProxyModel * mAssociatedProxyModel;

    QUrl mViewDefaultIcon;

    DataTypes::DataType mDataFilter;

    ViewManager::ViewCanBeRated mViewShowRating;

    ViewManager::DelegateUseSecondaryText mViewDelegateDisplaySecondaryText;

    int mSortRole;

    QList<int> mSortRoles;

    QList<QString> mSortRoleNames;

    Qt::SortOrder mSortOrder;

    QList<QString> mSortOrderNames;

    ViewManager::AlbumCardinality mDisplaySingleAlbum;

    ViewManager::AlbumViewStyle mShowDiscHeaders;

    ViewManager::ViewStyle mViewStyle = ViewManager::ListStyle;
};

ViewConfigurationData::ViewConfigurationData(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<ViewConfigurationDataPrivate>())
{
}

// Grid/List views
ViewConfigurationData::ViewConfigurationData(ElisaUtils::FilterType filterType, int expectedDepth,
                                             QString mainTitle, QString secondaryTitle,
                                             QUrl imageUrl, ElisaUtils::PlayListEntryType dataType,
                                             QAbstractItemModel *model, QAbstractProxyModel *associatedProxyModel,
                                             QUrl viewDefaultIcon, DataTypes::DataType dataFilter,
                                             int sortRole, QList<int> sortRoles, QList<QString> sortRoleNames,
                                             Qt::SortOrder sortOrder, QList<QString> sortOrderNames,
                                             ViewManager::ViewCanBeRated viewShowRating,
                                             ViewManager::DelegateUseSecondaryText viewDelegateDisplaySecondaryText,
                                             ViewManager::ViewStyle viewStyle,
                                             QObject *parent)
    : QObject(parent)
    , d(std::make_unique<ViewConfigurationDataPrivate>(filterType, expectedDepth, std::move(mainTitle),
                                                       std::move(secondaryTitle), std::move(imageUrl),
                                                       dataType, model, associatedProxyModel,
                                                       std::move(viewDefaultIcon), std::move(dataFilter),
                                                       sortRole, std::move(sortRoles), std::move(sortRoleNames),
                                                       sortOrder, std::move(sortOrderNames),
                                                       viewShowRating, viewDelegateDisplaySecondaryText,
                                                       viewStyle))
{
}

// Track views
ViewConfigurationData::ViewConfigurationData(ElisaUtils::FilterType filterType, int expectedDepth,
                                             QString mainTitle, QString secondaryTitle,
                                             QUrl imageUrl, ElisaUtils::PlayListEntryType dataType,
                                             QAbstractItemModel *model, QAbstractProxyModel *associatedProxyModel,
                                             DataTypes::DataType dataFilter,
                                             int sortRole, QList<int> sortRoles, QList<QString> sortRoleNames,
                                             Qt::SortOrder sortOrder, QList<QString> sortOrderNames,
                                             ViewManager::AlbumCardinality displaySingleAlbum,
                                             ViewManager::AlbumViewStyle showDiscHeaders,
                                             QObject *parent)
    : QObject(parent)
    , d(std::make_unique<ViewConfigurationDataPrivate>(filterType, expectedDepth, std::move(mainTitle),
                                                       std::move(secondaryTitle), std::move(imageUrl),
                                                       dataType, model, associatedProxyModel, std::move(dataFilter),
                                                       sortRole, std::move(sortRoles), std::move(sortRoleNames),
                                                       sortOrder, std::move(sortOrderNames), displaySingleAlbum, showDiscHeaders))
{
}

ElisaUtils::FilterType ViewConfigurationData::filterType() const
{
    return d->mFilterType;
}

int ViewConfigurationData::expectedDepth() const
{
    return d->mExpectedDepth;
}

QString ViewConfigurationData::mainTitle() const
{
    return d->mMainTitle;
}

QString ViewConfigurationData::secondaryTitle() const
{
    return d->mSecondaryTitle;
}

QUrl ViewConfigurationData::imageUrl() const
{
    return d->mImageUrl;
}

ElisaUtils::PlayListEntryType ViewConfigurationData::dataType() const
{
    return d->mDataType;
}

QAbstractItemModel *ViewConfigurationData::model() const
{
    return d->mModel;
}

QAbstractProxyModel *ViewConfigurationData::associatedProxyModel() const
{
    return d->mAssociatedProxyModel;
}

QUrl ViewConfigurationData::viewDefaultIcon() const
{
    return d->mViewDefaultIcon;
}

DataTypes::DataType ViewConfigurationData::dataFilter() const
{
    return d->mDataFilter;
}

ViewManager::ViewCanBeRated ViewConfigurationData::viewShowRating() const
{
    return d->mViewShowRating;
}

ViewManager::DelegateUseSecondaryText ViewConfigurationData::viewDelegateDisplaySecondaryText() const
{
    return d->mViewDelegateDisplaySecondaryText;
}

int ViewConfigurationData::sortRole() const
{
    return d->mSortRole;
}

QList<int> ViewConfigurationData::sortRoles() const
{
    return d->mSortRoles;
}

QList<QString> ViewConfigurationData::sortRoleNames() const
{
    return d->mSortRoleNames;
}

Qt::SortOrder ViewConfigurationData::sortOrder() const
{
    return d->mSortOrder;
}

QList<QString> ViewConfigurationData::sortOrderNames() const
{
    return d->mSortOrderNames;
}

ViewManager::AlbumCardinality ViewConfigurationData::displaySingleAlbum() const
{
    return d->mDisplaySingleAlbum;
}

ViewManager::AlbumViewStyle ViewConfigurationData::showDiscHeaders() const
{
    return d->mShowDiscHeaders;
}

ViewManager::ViewStyle ViewConfigurationData::viewStyle() const
{
    return d->mViewStyle;
}

ViewConfigurationData::~ViewConfigurationData() = default;

#include "moc_viewconfigurationdata.cpp"
