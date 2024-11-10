# World Format
### This file contains all information needed to build a working world, with start and end, using our A7 sprite editor

## Color Assignments:
#00000000: Air
#FF000000: Ground
#FF969696: Wall
#FF00FF00: Start
#FFFF0000: End
#FF0000FF: Gem

## JSON Format:
levelSize: Int
levelGemCount: Int
levelAuthor: String
levelTitle: String
levelType: String
levelData: [
    [x: Int, y: Int, tileType: String]
]
levelObjectives: String 
levelDescription: String
levelPreWrittenCode: String
levelHints: String
levelLineLimit: Int
levelInstructionLimit: Int
levelTimeLimit: Int
