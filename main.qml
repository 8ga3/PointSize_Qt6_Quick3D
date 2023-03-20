import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import QtQuick3D
import QtQuick3D.Helpers
import PointCloudCube

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Point Size")
    color: Qt.rgba(0.95, 1.0, 1.0, 1.0)

    View3D {
        id: mainView3d
        anchors.fill: parent
        camera: cameraPerspective

        PerspectiveCamera {
            id: cameraPerspective
            clipNear: 0.1
            position: Qt.vector3d(0, 0, 300)
        }

        OrthographicCamera {
            id: cameraOrthographic
            clipNear: 0.1
            position: Qt.vector3d(0, 0, 300)
            scale: Qt.vector3d(0.5, 0.5, 0.5)
        }

        WasdController {
            id: wasdController
            controlledObject: cube
            keysEnabled: true
            ySpeed: 1
            xSpeed: 1
        }

        Model {
            id: cube
            scale: Qt.vector3d(20, 20, 20)
            geometry: PointCloudCubeGeometry {
                pointCount: _sliderPoints.value
            }
            materials: [
                DefaultMaterial {
                    lighting: DefaultMaterial.NoLighting
                    pointSize: _sliderSize.value * Screen.devicePixelRatio
                }
            ]
        }
    }

    ColumnLayout {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        opacity: 0.75

        Label {
            property var profile: ["", " Core", " Compat"]
            property var api: ["", " API:Software", " API:OpenVG", " API:OpenGL", " API:Direct3D11", " API:Vulkan", " API:Metal", " API:Null"]
            text: "OpenGL: " + GraphicsInfo.majorVersion + '.' + GraphicsInfo.minorVersion + profile[GraphicsInfo.profile] + api[GraphicsInfo.api]
        }

        RowLayout {
            spacing: 4

            RadioButton {
                checked: true
                text: qsTr("Perspective")
                onCheckedChanged: mainView3d.camera = cameraPerspective
            }

            RadioButton {
                text: qsTr("Orthographic")
                onCheckedChanged: mainView3d.camera = cameraOrthographic
            }
        }

        RowLayout {
            spacing: 4

            Slider {
                id: _sliderPoints
                Layout.fillWidth: true
                Layout.maximumWidth: 600
                snapMode: RangeSlider.SnapAlways
                value: 10000
                stepSize: 10000
                from: 10000
                to: 1000000
            }

            Text {
                Layout.minimumWidth: 120
                Layout.maximumWidth: 120
                verticalAlignment: Text.AlignVCenter
                text: _sliderPoints.value.toFixed(0)
                font.pixelSize: 24
            }
        }

        RowLayout {
            spacing: 4

            Slider {
                id: _sliderSize
                Layout.fillWidth: true
                Layout.maximumWidth: 600
                snapMode: RangeSlider.SnapAlways
                value: 1
                stepSize: 1
                from: 1
                to: 32
            }

            Text {
                Layout.minimumWidth: 120
                Layout.maximumWidth: 120
                verticalAlignment: Text.AlignVCenter
                text: _sliderSize.value.toFixed(0)
                font.pixelSize: 24
            }
        }
    }
}
