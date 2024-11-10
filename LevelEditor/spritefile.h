/// spritefile.h
///
/// This file represents a model for any given save file of the SpriteEditor.
/// JSON Serializable/Deserializable
///
/// Author: Gavin Kerr, Hans Andersen, Hayden Miller, Solon Grover
/// Date: March 27, 2023

#ifndef SPRITEFILE_H
#define SPRITEFILE_H

// Qt imports
#include <QObject>
#include <QImage>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

// STD imports
#include <vector>
#include <string>

class SpriteFile
{

    Q_GADGET

public:

    /// Defaults used by the default constructor
    const static int DEFAULT_HEIGHT = 12;
    const static int DEFAULT_WIDTH = 12;

    /// @brief Default constructor for the JSON Object
    SpriteFile();


    /// @brief Create new SpriteFile with height and width
    /// @param height of the sprite
    /// @param width of the sprite
    SpriteFile(int height, int width);


    /// @brief Updates the height of the sprite
    /// @param height of the sprite
    void setHeight(int height);


    /// @brief Updates the width of the sprite
    /// @param width of the sprite
    void setWidth(int width);


    /// @brief Adds a new blank frame to the spritefile
    void addFrame();


    /// @brief Adds a frame to the sprite file from another QImage
    /// @param QImage to be added
    void addFrame(QImage& newImage);


    /// @brief Clones the frame number passed to the method and appends
    /// it to the end of the vector
    /// @param int Frame To Be Cloned
    void cloneFrame(int frame);

    /// @brief Removes a frame from the spritefile
    /// @param Number of frame to be removed
    /// @return if frame could be removed
    bool removeFrame(int frameNum);


    /// @brief Gives access to a given frame
    /// @param frame number
    /// @return reference to a frame
    QImage& getFrame(int frameNum);


    /// @brief Reads the data from the json object
    /// @param QJsonObject &json
    void read(const QJsonObject &json);


    /// @brief Writes the data back to a json object
    /// @param QJsonObject &json
    void write(QJsonObject &json) const;


    /// @brief Writes the data back to a jason object for a
    /// .level file
    /// @param QJsonObject &json) const;
    void writeLevel(QJsonObject &json) const;


    /// @brief Returns a string with some data from the
    /// spriteFile in an std::string
    /// @return file data
    std::string toString();


    /// @brief Returns the height of the sprite file
    /// @return project file height
    int getHeight();


    /// @brief Returns the width of the sprite file
    /// @return project file width
    int getWidth();


    /// @brief Returns the current number fo frames in the file
    /// @return current number of frames
    int getFrameCount();


    /// @brief Sets the level data for any given level
    /// @param levelAuthor
    /// @param levelTitle
    /// @param levelType
    /// @param levelTimeLimit
    void setLevelData(QString author, QString title, QString type, int timeLimit);

private:

    int height;
    int width;
    int numberOfFrames;
    std::vector<QImage> frames;

    QString levelAuthor;
    QString levelTitle;
    QString levelType;
    int levelTimeLimit;

    bool isValid;

};

#endif // SPRITEFILE_H
