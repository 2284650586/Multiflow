import QtQuick 2.0

Item {
  id: card
  property alias content: contentItem // Directly expose the contentItem for adding children
  property int padding: 10
  property color borderColor: 'black'
  property int borderWidth: 1
  property real radius: 5

  // Use a Loader to dynamically create the content
  Loader {
    id: contentLoader
    onLoaded: {
      // Update the size of the card based on the content
      card.width = item.width + (card.padding * 2) + (card.borderWidth * 2)
      card.height = item.height + (card.padding * 2) + (card.borderWidth * 2)
    }
  }

  // This rectangle is the border and background of the card
  Rectangle {
    id: background
    anchors.fill: card
    border.color: card.borderColor
    border.width: card.borderWidth
    radius: card.radius
    color: 'white'

    // The actual content of the card will be set here
    Item {
      id: contentItem
      width: parent.width - (card.padding * 2) - (card.borderWidth * 2)
      height: parent.height - (card.padding * 2) - (card.borderWidth * 2)
    }
  }
}
