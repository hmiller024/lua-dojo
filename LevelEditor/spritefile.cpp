#include "spritefile.h"

SpriteFile::SpriteFile()
{

    // Initalize default data
    height = DEFAULT_HEIGHT;
    width = DEFAULT_WIDTH;
    numberOfFrames = 0;
    isValid = true;

    levelAuthor = levelTitle = levelType = "";
    levelTimeLimit = 0;

    // Add default frame
    addFrame();

}

SpriteFile::SpriteFile(int height, int width)
{

    // Initalize default data
    this->height = height;
    this->width = width;
    numberOfFrames = 0;
    isValid = true;

    levelAuthor = levelTitle = levelType = "";
    levelTimeLimit = 0;

    // Add default frame
    addFrame();

}

void SpriteFile::setHeight(int height)
{
    this->height = height;
}

void SpriteFile::setWidth(int width)
{
    this->width = width;
}

int SpriteFile::getHeight()
{
    return height;
}

int SpriteFile::getWidth()
{
    return width;
}

int SpriteFile::getFrameCount()
{
    return frames.size();
}

void SpriteFile::setLevelData(QString author, QString title, QString type, int timeLimit)
{

    levelAuthor = author;
    levelTitle = title;
    levelType = type;
    levelTimeLimit = timeLimit;

}

void SpriteFile::addFrame()
{

    // Increment frames, add frame, push back
    numberOfFrames++;
    QImage tempFrame(height, width, QImage::Format_ARGB32);
    tempFrame.fill(QColor(0, 0, 0, 0));
    frames.push_back(tempFrame);

}

void SpriteFile::addFrame(QImage &newImage)
{

    // Increment frames, add referenced frame
    numberOfFrames++;
    frames.push_back(newImage);
}

void SpriteFile::cloneFrame(int frameNum) {
    numberOfFrames++;
    QImage copy = frames.at(frameNum).copy();
    frames.insert(frames.begin() + frameNum, copy);
}

bool SpriteFile::removeFrame(int frameNum)
{

    // Check to see if frame can be removed
    if (frameNum < numberOfFrames) {

        numberOfFrames--;
        frames.erase(frames.begin() + frameNum);
        return true;

    }

    return false;

}

QImage &SpriteFile::getFrame(int frameNum)
{

    return frames.at(frameNum);

}

void SpriteFile::read(const QJsonObject &json)
{

    // Read each element of the QJsonObject into the object
    if (json.contains("height") && json["height"].isDouble()) {
        height = json["height"].toInt();
    } else {
        isValid = false;
    }

    if (json.contains("width") && json["width"].isDouble()) {
        width = json["width"].toInt();
    } else {
        isValid = false;
    }

    if (json.contains("numberOfFrames") && json["numberOfFrames"].isDouble()) {
        numberOfFrames = json["numberOfFrames"].toInt();
    } else {
        isValid = false;
    }

    // Check for "frames" array if all other data has been found
    if (json.contains("frames") && json["frames"].isObject() && isValid) {

        // Set vector to default state
        frames.clear();

        /// Valid array found, load data into vector
        /// This ignores the size of the array's in the json file, instead
        /// it just imports the pixel size as defined above. Technically
        /// safer than trying to load an array that won't fit in an image.
        for (int i = 0; i < numberOfFrames; i++) {

            QImage tempImage(height, width, QImage::Format_ARGB32);
            QJsonArray frameJson = json["frames"]["frame" + QString::number(i)].toArray();

            // Loop through entire height of the image
            for (int j = 0; j < height; j++) {

                // Loop through width of image
                for (int k = 0; k < width; k++) {
                    QJsonArray pixelJson = frameJson[j].toArray().at(k).toArray();
                    tempImage.setPixelColor(j, k, QColor(pixelJson[0].toInt(),
                                            pixelJson[1].toInt(), pixelJson[2].toInt(),
                                            pixelJson[3].toInt()));
                }

            }

            // Add frame to vector
            frames.push_back(tempImage);

        }

    } else {
        isValid = false;
    }

}

void SpriteFile::write(QJsonObject &json) const
{

    // Write back basic variables to file
    json["height"] = height;
    json["width"] = width;
    json["numberOfFrames"] = numberOfFrames;

    // Write Images back to file
    QJsonObject finalJsonArray;

    // I didn't use a foreach here because i needed the iterator number
    for (int i = 0; i < numberOfFrames; i++) {

        QJsonArray frameJsonArray;
        for (int j = 0; j < height; j++) {

            QJsonArray frameLineJsonArray;
            for (int k = 0; k < width; k++) {

                // Append color data in RGBA order
                QJsonArray pixelJsonArray;
                pixelJsonArray.push_back(frames.at(i).pixelColor(j, k).red());
                pixelJsonArray.push_back(frames.at(i).pixelColor(j, k).green());
                pixelJsonArray.push_back(frames.at(i).pixelColor(j, k).blue());
                pixelJsonArray.push_back(frames.at(i).pixelColor(j, k).alpha());
                frameLineJsonArray.push_back(pixelJsonArray);

            }

            // Append frame line to frame array
            frameJsonArray.push_back(frameLineJsonArray);

        }

        // Append frame to final array
        finalJsonArray.insert("frame" + QString::number(i), frameJsonArray);

    }

    // Write JsonArray to json
    json["frames"] = finalJsonArray;

}

void SpriteFile::writeLevel(QJsonObject &json) const
{

    // Store data we already know
    json["levelSize"] = height;
    json["levelTitle"] = levelTitle;
    json["levelAuthor"] = levelAuthor;
    json["levelType"] = levelType;


    // Get the first frame and match each color to a data type
    QImage frame = frames.at(0);
    QJsonArray levelTiles;

    int gemCount = 0;

    for (int x = 0; x < frame.width(); x++) {
        for (int y = 0; y < frame.height(); y++) {
            QString color = frame.pixelColor(x, y).name(QColor::HexArgb);

            // Check colors for rules
            QJsonArray tileArray;
            if (color == "#ff000000") {
                tileArray.push_back(x);
                tileArray.push_back(y);
                tileArray.push_back("ground");
            } else if (color == "#ff969696") {
                tileArray.push_back(x);
                tileArray.push_back(y);
                tileArray.push_back("wall");
            } else if (color == "#ff00ff00") {
                tileArray.push_back(x);
                tileArray.push_back(y);
                tileArray.push_back("start");
            } else if (color == "#ffff0000") {
                tileArray.push_back(x);
                tileArray.push_back(y);
                tileArray.push_back("end");
            } else if (color == "#ff0000ff") {
                tileArray.push_back(x);
                tileArray.push_back(y);
                tileArray.push_back("gem");
                gemCount++;
            }

            // Add tile to level tiles array
            if (!tileArray.isEmpty()) {
                levelTiles.append(tileArray);
            }

        }
    }

    // Write and Clean up
    json["levelGemCount"] = gemCount;
    json["levelData"] = levelTiles;

    // Write additional level flags but as default or empty for later
    // modification. It's a level editor, not an entire builder i guess

    // Data that needs to be filled in later
    json["levelObjectives"] = "LEVEL_OBJECTIVES_PLACEHOLDER";
    json["levelDescription"] = "LEVEL_DESCRIPTION_PLACEHOLDER";
    json["levelHints"] = "LEVEL_HINTS_PLACEHOLDER";
    json["levelPreWrittenCode"] = "LEVEL_PRE_WRITTEN_CODE_PLACEHOLDER";

    // "Optional" data
    json["levelTimeLimit"] = levelTimeLimit;
    json["levelLineLimit"] = 0;
    json["levelInstructionLimit"] = 0;

}

std::string SpriteFile::toString()
{

    std::string output;

    output += "height: " + std::to_string(height) + "\n";
    output += "width: " + std::to_string(width) + "\n";
    output += "numberOfFrames: " + std::to_string(numberOfFrames) + "\n";

    output += "frames:\n";
    for (int i = 0; i < numberOfFrames; i++) {
        output += std::to_string(frames.at(i).pixelColor(0, 0).red());
        output += "\n";
    }

    return output;

}
