# ProgrammingGame.pro
#
# Builds the whole project
# Warning: This file will give you a headache, it's a self admitited mess, but
# it's my mess I guess.
#
# Author: Gavin Kerr

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20 file_copies

# This may seem like a bad idea but it removes the warnings generated
# by luacpp, its purely because these warnings are driving me crazy
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-function \
    -Wunused-parameter

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    codeeditor.cpp \
    level.cpp \
    levelentity.cpp \
    levelcomplete.cpp \
    libs/Box2D/Collision/Shapes/b2ChainShape.cpp \
    libs/Box2D/Collision/Shapes/b2CircleShape.cpp \
    libs/Box2D/Collision/Shapes/b2EdgeShape.cpp \
    libs/Box2D/Collision/Shapes/b2PolygonShape.cpp \
    libs/Box2D/Collision/b2BroadPhase.cpp \
    libs/Box2D/Collision/b2CollideCircle.cpp \
    libs/Box2D/Collision/b2CollideEdge.cpp \
    libs/Box2D/Collision/b2CollidePolygon.cpp \
    libs/Box2D/Collision/b2Collision.cpp \
    libs/Box2D/Collision/b2Distance.cpp \
    libs/Box2D/Collision/b2DynamicTree.cpp \
    libs/Box2D/Collision/b2TimeOfImpact.cpp \
    libs/Box2D/Common/b2BlockAllocator.cpp \
    libs/Box2D/Common/b2Draw.cpp \
    libs/Box2D/Common/b2Math.cpp \
    libs/Box2D/Common/b2Settings.cpp \
    libs/Box2D/Common/b2StackAllocator.cpp \
    libs/Box2D/Common/b2Timer.cpp \
    libs/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
    libs/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
    libs/Box2D/Dynamics/Contacts/b2CircleContact.cpp \
    libs/Box2D/Dynamics/Contacts/b2Contact.cpp \
    libs/Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
    libs/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
    libs/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
    libs/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
    libs/Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
    libs/Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
    libs/Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
    libs/Box2D/Dynamics/Joints/b2GearJoint.cpp \
    libs/Box2D/Dynamics/Joints/b2Joint.cpp \
    libs/Box2D/Dynamics/Joints/b2MotorJoint.cpp \
    libs/Box2D/Dynamics/Joints/b2MouseJoint.cpp \
    libs/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
    libs/Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
    libs/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
    libs/Box2D/Dynamics/Joints/b2RopeJoint.cpp \
    libs/Box2D/Dynamics/Joints/b2WeldJoint.cpp \
    libs/Box2D/Dynamics/Joints/b2WheelJoint.cpp \
    libs/Box2D/Dynamics/b2Body.cpp \
    libs/Box2D/Dynamics/b2ContactManager.cpp \
    libs/Box2D/Dynamics/b2Fixture.cpp \
    libs/Box2D/Dynamics/b2Island.cpp \
    libs/Box2D/Dynamics/b2World.cpp \
    libs/Box2D/Dynamics/b2WorldCallbacks.cpp \
    libs/Box2D/Rope/b2Rope.cpp \
    libs/lua5.4/src/lapi.c \
    libs/lua5.4/src/lzio.c \
    libs/lua5.4/src/lauxlib.c \
    libs/lua5.4/src/lbaselib.c \
    libs/lua5.4/src/lcode.c \
    libs/lua5.4/src/lcorolib.c \
    libs/lua5.4/src/lctype.c \
    libs/lua5.4/src/ldblib.c \
    libs/lua5.4/src/ldebug.c \
    libs/lua5.4/src/ldo.c \
    libs/lua5.4/src/ldump.c \
    libs/lua5.4/src/lfunc.c \
    libs/lua5.4/src/lgc.c \
    libs/lua5.4/src/linit.c \
    libs/lua5.4/src/liolib.c \
    libs/lua5.4/src/llex.c \
    libs/lua5.4/src/lmathlib.c \
    libs/lua5.4/src/lmem.c \
    libs/lua5.4/src/loadlib.c \
    libs/lua5.4/src/lobject.c \
    libs/lua5.4/src/lopcodes.c \
    libs/lua5.4/src/loslib.c \
    libs/lua5.4/src/lparser.c \
    libs/lua5.4/src/lstate.c \
    libs/lua5.4/src/lstring.c \
    libs/lua5.4/src/lstrlib.c \
    libs/lua5.4/src/ltable.c \
    libs/lua5.4/src/ltablib.c \
    libs/lua5.4/src/ltm.c \
    libs/lua5.4/src/lundump.c \
    libs/lua5.4/src/lutf8lib.c \
    libs/lua5.4/src/lvm.c \
    libs/luacpp/src/LuaContext.cpp \
    libs/luacpp/src/LuaMetaObject.cpp \
    libs/luacpp/src/LuaVersion.cpp \
    libs/luacpp/src/Engine/LuaState.cpp \
    libs/luacpp/src/Engine/LuaTBoolean.cpp \
    libs/luacpp/src/Engine/LuaTNil.cpp \
    libs/luacpp/src/Engine/LuaTNumber.cpp \
    libs/luacpp/src/Engine/LuaTString.cpp \
    libs/luacpp/src/Engine/LuaTTable.cpp \
    libs/luacpp/src/Engine/LuaTUserData.cpp \
    libs/luacpp/src/Engine/LuaType.cpp \
    libs/luacpp/src/Registry/LuaRegistry.cpp \
    libs/luacpp/src/Registry/LuaCFunction.cpp \
    libs/luacpp/src/Registry/LuaCodeSnippet.cpp \
    libs/luacpp/src/Registry/LuaCompiler.cpp \
    libs/luacpp/src/Registry/LuaLibrary.cpp \
    gamemodel.cpp \
    main.cpp \
    gamewindow.cpp \
    player.cpp \
    tile.cpp

HEADERS += \
    codeeditor.h \
    level.h \
    levelentity.h \
    levelcomplete.h \
    libs/Box2D/Box2D.h \
    libs/Box2D/Collision/Shapes/b2ChainShape.h \
    libs/Box2D/Collision/Shapes/b2CircleShape.h \
    libs/Box2D/Collision/Shapes/b2EdgeShape.h \
    libs/Box2D/Collision/Shapes/b2PolygonShape.h \
    libs/Box2D/Collision/Shapes/b2Shape.h \
    libs/Box2D/Collision/b2BroadPhase.h \
    libs/Box2D/Collision/b2Collision.h \
    libs/Box2D/Collision/b2Distance.h \
    libs/Box2D/Collision/b2DynamicTree.h \
    libs/Box2D/Collision/b2TimeOfImpact.h \
    libs/Box2D/Common/b2BlockAllocator.h \
    libs/Box2D/Common/b2Draw.h \
    libs/Box2D/Common/b2GrowableStack.h \
    libs/Box2D/Common/b2Math.h \
    libs/Box2D/Common/b2Settings.h \
    libs/Box2D/Common/b2StackAllocator.h \
    libs/Box2D/Common/b2Timer.h \
    libs/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h \
    libs/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h \
    libs/Box2D/Dynamics/Contacts/b2CircleContact.h \
    libs/Box2D/Dynamics/Contacts/b2Contact.h \
    libs/Box2D/Dynamics/Contacts/b2ContactSolver.h \
    libs/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h \
    libs/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h \
    libs/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h \
    libs/Box2D/Dynamics/Contacts/b2PolygonContact.h \
    libs/Box2D/Dynamics/Joints/b2DistanceJoint.h \
    libs/Box2D/Dynamics/Joints/b2FrictionJoint.h \
    libs/Box2D/Dynamics/Joints/b2GearJoint.h \
    libs/Box2D/Dynamics/Joints/b2Joint.h \
    libs/Box2D/Dynamics/Joints/b2MotorJoint.h \
    libs/Box2D/Dynamics/Joints/b2MouseJoint.h \
    libs/Box2D/Dynamics/Joints/b2PrismaticJoint.h \
    libs/Box2D/Dynamics/Joints/b2PulleyJoint.h \
    libs/Box2D/Dynamics/Joints/b2RevoluteJoint.h \
    libs/Box2D/Dynamics/Joints/b2RopeJoint.h \
    libs/Box2D/Dynamics/Joints/b2WeldJoint.h \
    libs/Box2D/Dynamics/Joints/b2WheelJoint.h \
    libs/Box2D/Dynamics/b2Body.h \
    libs/Box2D/Dynamics/b2ContactManager.h \
    libs/Box2D/Dynamics/b2Fixture.h \
    libs/Box2D/Dynamics/b2Island.h \
    libs/Box2D/Dynamics/b2TimeStep.h \
    libs/Box2D/Dynamics/b2World.h \
    libs/Box2D/Dynamics/b2WorldCallbacks.h \
    libs/Box2D/Rope/b2Rope.h \
    libs/lua5.4/src/lua.h \
    libs/lua5.4/src/lapi.h \
    libs/lua5.4/src/lauxlib.h \
    libs/lua5.4/src/lcode.h \
    libs/lua5.4/src/lctype.h \
    libs/lua5.4/src/ldebug.h \
    libs/lua5.4/src/ldo.h \
    libs/lua5.4/src/lfunc.h \
    libs/lua5.4/src/lgc.h \
    libs/lua5.4/src/ljumptab.h \
    libs/lua5.4/src/llex.h \
    libs/lua5.4/src/llimits.h \
    libs/lua5.4/src/lmem.h \
    libs/lua5.4/src/lobject.h \
    libs/lua5.4/src/lopcodes.h \
    libs/lua5.4/src/lopnames.h \
    libs/lua5.4/src/lparser.h \
    libs/lua5.4/src/lprefix.h \
    libs/lua5.4/src/lstate.h \
    libs/lua5.4/src/lstring.h \
    libs/lua5.4/src/ltable.h \
    libs/lua5.4/src/ltm.h \
    libs/lua5.4/src/luaconf.h \
    libs/lua5.4/src/lualib.h \
    libs/lua5.4/src/lundump.h \
    libs/lua5.4/src/lvm.h \
    libs/lua5.4/src/lzio.h \
    libs/luacpp/src/Lua.hpp \
    libs/luacpp/src/LuaContext.hpp \
    libs/luacpp/src/LuaCpp.hpp \
    libs/luacpp/src/LuaMetaObject.hpp \
    libs/luacpp/src/LuaVersion.hpp \
    libs/luacpp/src/Engine/LuaType.hpp \
    libs/luacpp/src/Engine/LuaState.hpp \
    libs/luacpp/src/Engine/LuaTBoolean.hpp \
    libs/luacpp/src/Engine/LuaTNil.hpp \
    libs/luacpp/src/Engine/LuaTNumber.hpp \
    libs/luacpp/src/Engine/LuaTString.hpp \
    libs/luacpp/src/Engine/LuaTTable.hpp \
    libs/luacpp/src/Engine/LuaTUserData.hpp \
    libs/luacpp/src/Registry/LuaRegistry.hpp \
    libs/luacpp/src/Registry/LuaCFunction.hpp \
    libs/luacpp/src/Registry/LuaCodeSnippet.hpp \
    libs/luacpp/src/Registry/LuaCompiler.hpp \
    libs/luacpp/src/Registry/LuaLibrary.hpp \
    gamemodel.h \
    gamewindow.h \
    player.h \
    tile.h

FORMS += \
    gamewindow.ui

# Copy levels to build folder depending on platform
macx: {

    levelsMac.files += \
        res/levels/$$files(*.level) \
        luaFunctions.lua

    levelsMac.path = Contents/MacOS/res/levels

    # macOS Specific copy levels
    QMAKE_BUNDLE_DATA += levelsMac

}

win32:  {

    system("rmdir /s /q \"$$OUT_PWD/res\"")
    levelsWin.files += $$files(res/levels/*)
    luaWin.files += luaFunctions.lua

    levelsWin.path = res/levels/
    luaWin.path = res/levels/

    # Windows just copy files to where program runs, not into package
    COPIES += levelsWin
    COPIES += luaWin

}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Add Include Path for libs
INCLUDEPATH += $$PWD/libs
INCLUDEPATH += $$PWD/libs/lua5.4/src
INCLUDEPATH += $$PWD/libs/lualib/src

# Thanks Apple. Think Different.
macx: {
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15
}

RESOURCES += \
    resources.qrc

DISTFILES += \
    luaFunctions.lua \
    res/levels/solutions.txt
