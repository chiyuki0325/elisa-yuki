/*
   SPDX-FileCopyrightText: 2016 (c) Matthieu Gallien <matthieu_gallien@yahoo.fr>
   SPDX-FileCopyrightText: 2019 (c) Nate Graham <nate@kde.org>

   SPDX-License-Identifier: LGPL-3.0-or-later
 */

import QtQuick 2.10
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQml.Models 2.2
import QtQuick.Layouts 1.2
import QtGraphicalEffects 1.0
import org.kde.kirigami 2.12 as Kirigami
import org.kde.elisa 1.0

FocusScope {
    id: topItem

    property int databaseId: 0
    property var trackType
    property alias title: titleLabel.text
    property string albumName: ''
    property string artistName: ''
    property url albumArtUrl: ''
    property url fileUrl: ''
    property int albumId
    property string albumArtist: ''

    signal openArtist()
    signal openAlbum()

    readonly property bool nothingPlaying: albumName.length === 0
                                        && artistName.length === 0
                                        && albumArtUrl.toString.length === 0
                                        && title.length === 0
                                        && fileUrl.toString.length === 0

    TrackContextMetaDataModel {
        id: metaDataModel

        manager: ElisaApplication.musicManager
    }

    ColumnLayout {
        anchors.fill: parent

        spacing: 0

        // Header with title
        HeaderFooterToolbar {
            Layout.fillWidth: true
            toolbarType: HeaderFooterToolbar.ToolbarType.Header
            contentItems: [
                Image {
                    id: mainIcon
                    source: elisaTheme.nowPlayingIcon

                    Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
                    Layout.preferredWidth: Kirigami.Units.iconSizes.medium
                    Layout.preferredHeight: Kirigami.Units.iconSizes.medium
                    sourceSize.height: Layout.preferredHeight
                    sourceSize.width: Layout.preferredWidth

                    fillMode: Image.PreserveAspectFit
                    asynchronous: true

                },
                Item {
                    id: spacer
                    width: Kirigami.Units.largeSpacing
                },
                LabelWithToolTip {
                    id: viewTitle
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                    text: i18nc("Title of the context view related to the currently playing track", "Now Playing")

                    level: 1
                }
            ]
        }

        // Container to hold both the blurred background and the scrollview
        // We can't make the scrollview a child of the background item since then
        // everything in the scrollview will be blurred and transparent too!
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            // Blurred album art background
            Image {
                id: albumArtBackground
                anchors.fill: parent

                visible: !topItem.nothingPlaying

                source: albumArtUrl.toString() === '' ? Qt.resolvedUrl(elisaTheme.defaultAlbumImage) : albumArtUrl

                sourceSize.width: topItem.width
                sourceSize.height: topItem.height

                asynchronous: true

                fillMode: Image.PreserveAspectCrop

                layer.enabled: true
                opacity: 0.2
                layer.effect: FastBlur {
                    source: albumArtBackground
//                     anchors.fill: parent
                    radius: 40
                }
            }

            // Scrollview to hold all the content
            ScrollView {
                id: scrollView
                anchors.fill: parent
                clip: true

                visible: !topItem.nothingPlaying

                contentHeight: content.height

                // This Item holds only the content layout so we can center the
                // ColumnLayout within it to provide appropriate margins. We
                // can't do this if the ColumnLayout is directly inside the
                // ScrollView
                Item {
                    width: scrollView.width - scrollView.ScrollBar.vertical.width

                    // Layout holding the Title + metadata + lyrics labels
                    ColumnLayout {
                        id: content

                        anchors.top: parent.top
                        anchors.topMargin: Kirigami.Units.largeSpacing
                        anchors.left: parent.left
                        anchors.leftMargin: Kirigami.Units.largeSpacing * 2
                        anchors.right: parent.right
                        anchors.rightMargin: Kirigami.Units.largeSpacing * 2
                        // No bottom anchors so it can grow

                        // Grid layout to hold the song, artist, and album names
                        // This is so we can vertically align the icons
                        GridLayout {
                            id: gridlayout
                            Layout.minimumWidth: Kirigami.Units.gridUnit * 12
                            Layout.alignment: Qt.AlignHCenter

                            columns: 2

                            // Row 1: Song stuff
                            // -----------------
                            // Column 1: Song icon
                            Image {
                                source: "image://icon/view-media-track"
                                Layout.preferredWidth: sourceSize.width
                                Layout.preferredHeight: sourceSize.height
                                sourceSize {
                                    width: Kirigami.Units.iconSizes.smallMedium
                                    height: Kirigami.Units.iconSizes.smallMedium
                                }
                            }
                            // Column 2: Song title
                            LabelWithToolTip {
                                id: titleLabel
                                Layout.maximumWidth: gridlayout.width
                                Layout.alignment: Qt.AlignLeft

                                level: 1

                                elide: Text.ElideNone
                                wrapMode: Text.Wrap
                                horizontalAlignment: Text.AlignLeft
                            }

                            // Row 2: Artist stuff
                            // -----------------
                            // Column 1: Artist icon
                            Image {
                                source: "image://icon/view-media-artist"
                                visible: artistName !== ''
                                Layout.preferredWidth: sourceSize.width
                                Layout.preferredHeight: sourceSize.height
                                sourceSize {
                                    width: Kirigami.Units.iconSizes.smallMedium
                                    height: Kirigami.Units.iconSizes.smallMedium
                                }
                            }
                            // Column 2: Artist name
                            Kirigami.LinkButton {
                                Layout.maximumWidth: gridlayout.width
                                Layout.alignment: Qt.AlignLeft
                                text: artistName !== '' ? artistName : ""
                                opacity: 0.6
                                visible: artistName !== ''
                                elide: Text.ElideNone
                                wrapMode: Text.Wrap
                                horizontalAlignment: Text.AlignLeft
                                font.pointSize: Math.round(Kirigami.Theme.defaultFont.pointSize * 1.20)
                                font.bold: true
                                color: Kirigami.Theme.textColor
                                onClicked: {
                                    openArtist();
                                }
                            }

                            // Row 3: Album stuff
                            // -----------------
                            // Column 1: Album icon
                            Image {
                                source: "image://icon/view-media-album-cover"
                                visible: albumName !== ''
                                Layout.preferredWidth: sourceSize.width
                                Layout.preferredHeight: sourceSize.height
                                sourceSize {
                                    width: Kirigami.Units.iconSizes.smallMedium
                                    height: Kirigami.Units.iconSizes.smallMedium
                                }
                            }
                            // Column 2: Album name
                            Kirigami.LinkButton {
                                Layout.maximumWidth: gridlayout.width
                                Layout.alignment: Qt.AlignLeft
                                text: albumName !== '' ? albumName : ""
                                opacity: 0.6
                                visible: albumName !== ''
                                elide: Text.ElideNone
                                wrapMode: Text.Wrap
                                horizontalAlignment: Text.AlignLeft
                                font.pointSize: Math.round(Kirigami.Theme.defaultFont.pointSize * 1.20)
                                font.bold: true
                                color: Kirigami.Theme.textColor
                                onClicked: {
                                    openAlbum();
                                }
                            }
                        }

                        // Horizontal line separating title and subtitle from metadata
                        Kirigami.Separator {
                            Layout.fillWidth: true
                            Layout.leftMargin: Kirigami.Units.largeSpacing* 5
                            Layout.topMargin: Kirigami.Units.largeSpacing
                            Layout.rightMargin: Kirigami.Units.largeSpacing * 5
                            Layout.bottomMargin: Kirigami.Units.largeSpacing
                        }

                        // Metadata
                        ColumnLayout {
                            id: allMetaData

                            spacing: 0
                            Layout.fillWidth: true
                            //Layout.leftMargin:Kirigami.Units.largeSpacing
                            //Layout.rightMargin:Kirigami.Units.largeSpacing

                            Repeater {
                                id: trackData

                                model: metaDataModel

                                delegate: MetaDataDelegate {
                                    index: model.index
                                    name: model.name
                                    display: model.display
                                    type: model.type

                                    Layout.fillWidth: true
                                }
                            }
                        }

                        // Horizontal line separating metadata from lyrics
                        Kirigami.Separator {
                            Layout.fillWidth: true
                            Layout.leftMargin: Kirigami.Units.largeSpacing * 5
                            Layout.rightMargin: Kirigami.Units.largeSpacing * 5
                            Layout.topMargin: Kirigami.Units.largeSpacing
                            Layout.bottomMargin: Kirigami.Units.largeSpacing

                            visible: metaDataModel.lyrics !== ""
                        }

                        // Lyrics
                        Label {
                            text: metaDataModel.lyrics

                            wrapMode: Text.WordWrap

                            horizontalAlignment: Label.AlignHCenter

                            Layout.fillWidth: true
                            Layout.bottomMargin: Kirigami.Units.largeSpacing * 2
                            visible: metaDataModel.lyrics !== ""

                        }
                    }
                }
            }

            // "Nothing Playing" message
            Kirigami.PlaceholderMessage {
                anchors.centerIn: parent
                width: parent.width - (Kirigami.Units.largeSpacing * 4)
                visible: topItem.nothingPlaying
                text: i18n("Nothing playing")
            }
        }

        // Footer with file path label
        HeaderFooterToolbar {
            visible: !topItem.nothingPlaying
            toolbarType: HeaderFooterToolbar.ToolbarType.Footer
            Layout.fillWidth: true
            Layout.preferredHeight: Kirigami.Units.gridUnit * 2
            contentLayoutSpacing: Kirigami.Units.largeSpacing
            contentItems: [
                LabelWithToolTip {
                    id: fileNameLabel

                    Layout.fillWidth: true

                    text: metaDataModel.fileUrl
                    elide: Text.ElideLeft
                },
                ToolButton {
                    icon.name: "document-open-folder"
                    text: i18n("Show In Folder")
                    onClicked: {
                        ElisaApplication.showInFolder(metaDataModel.fileUrl)
                    }
                }
            ]
        }
    }

    onDatabaseIdChanged: {
        if (ElisaApplication.musicManager && trackType !== undefined && databaseId !== 0) {
            metaDataModel.initializeByIdAndUrl(trackType, databaseId, fileUrl)
        }
    }

    onTrackTypeChanged: {
        if (ElisaApplication.musicManager && trackType !== undefined && databaseId !== 0) {
            metaDataModel.initializeByIdAndUrl(trackType, databaseId, fileUrl)
        }
    }

    Connections {
        target: ElisaApplication

        function onMusicManagerChanged() {
            if (ElisaApplication.musicManager && trackType !== undefined && databaseId !== 0) {
                metaDataModel.initializeByIdAndUrl(trackType, databaseId, fileUrl)
            }
        }
    }

    Component.onCompleted: {
        if (ElisaApplication.musicManager && trackType !== undefined && databaseId !== 0) {
            metaDataModel.initializeByIdAndUrl(trackType, databaseId, fileUrl)
        }
    }
}
