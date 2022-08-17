/*
   SPDX-FileCopyrightText: 2016 (c) Matthieu Gallien <matthieu_gallien@yahoo.fr>
   SPDX-FileCopyrightText: 2021 (c) Devin Lin <espidev@gmail.com>

   SPDX-License-Identifier: LGPL-3.0-or-later
 */

import QtQuick 2.7
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.3
import org.kde.kirigami 2.5 as Kirigami
import org.kde.elisa 1.0

Slider {
    id: volumeSlider
    property bool muted

    from: 0
    to: 100

    enabled: !muted

    readonly property int wheelEffect: 5

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.NoButton
        onWheel: {
            // Can't use Slider's built-in increase() and decrease() functions here
            // since they go in increments of 0.1 when the slider's stepSize is not
            // defined, which is much too slow. And we don't define a stepSize for
            // the slider because if we do, it gets gets tickmarks which look ugly.
            if (wheel.angleDelta.y > 0) {
                // Increase volume
                volumeSlider.value = Math.min(volumeSlider.to, volumeSlider.value + wheelEffect);

            } else {
                // Decrease volume
                volumeSlider.value = Math.max(volumeSlider.from, volumeSlider.value - wheelEffect);
            }
        }
    }
}
