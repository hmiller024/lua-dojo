-- luaFunctions.lua
--
-- This file contains basic functions used to be passed a LuaContext
-- within the ProgrammingGame. Each function should return a string
-- for it's respective action
-- 
-- Author: Gavin Kerr
-- Date: April 19, 2023

-- Make table for actions

actions = {}

function moveForward()
    table.insert(actions, "forward");
end

function turnRight()
    table.insert(actions, "right");
end

function turnLeft()
    table.insert(actions, "left")
end

function collectGem()
    table.insert(actions, "gem")
end

function sleep(time)
    table.insert(actions, "sleep:"..time)
end
