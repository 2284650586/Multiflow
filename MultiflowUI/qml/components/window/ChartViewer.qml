import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts
import Multiflow.UI
import FluentUI
import Qt.labs.qmlmodels
import "qrc:/qml/components/widget/"
import "qrc:/qml/components/singleton/"

FluWindow {
    required property var category
    required property var yValueSerieses
    required property var xValueSerieses
    required property var yName
    required property var xName

    id: window
    width: 800
    height: 600
    title: "计算结果"
    visible: false

    Component.onCompleted: {
        window.title += ` - ${category}`
    }

    FluArea {
        anchors.fill: parent
        anchors.margins: 10
        border.color: Colors.border
        color: Colors.background
        radius: 8
        clip: true

        FluChart {
            anchors.fill: parent
            chartType: 'line'
            chartData: {
                const datasets = []
                const xValueLabels = xValueSerieses[0].map(x => `${x}`)
                for (let i = 0; i < xValueSerieses.length; ++i) {
                    const yValueSeries = yValueSerieses[i]
                    datasets.push({
                        label: yName,
                        fill: true,
                        backgroundColor: 'rgba(192,222,255,0.3)',
                        borderColor: 'rgba(128,192,255,255)',
                        data: yValueSeries,
                    })
                }
                return {
                    labels: xValueLabels,
                    datasets: datasets
                }
            }

            chartOptions: {
                return {
                    maintainAspectRatio: false,
                    responsive: true,
                    title: {
                        display: true,
                        text: category
                    },
                    tooltips: {
                        mode: 'index',
                        intersect: false,
                    },
                    hover: {
                        mode: 'nearest',
                        intersect: true
                    },
                    scales: {
                        xAxes: [
                            {
                                display: true,
                                scaleLabel: {
                                    display: true,
                                    labelString: xName
                                }
                            },
                        ],
                        yAxes: [
                            {
                                display: true,
                                scaleLabel: {
                                    display: true,
                                    labelString: yName
                                }
                            },
                        ]
                    }
                }
            }
        }
    }

    function show() {
        visible = true
    }
}
