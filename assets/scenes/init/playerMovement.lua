GPurityLuaManager:doFile("scenes/init/servercfg.lua")

local animationFrame = 0
local timer = Purity.Timer()

function moveRight (player)
    if isServer then
        player:setLinearVelocity(10, player:getLinearVelocityY())
	
	if timer:getElapsedTime() > 50 then
	    timer:restart()
	    if animationFrame >= 8 then
		animationFrame = 0
	    else
		animationFrame = animationFrame + 1
	    end
	end

	player:setAnimationFrame(animationFrame)
    else
        GPurityNetwork:sendAction(player:getName(), "moveRight")
    end
end

function moveLeft (player)
    if isServer then
        player:setLinearVelocity(-10, player:getLinearVelocityY())
    else
        GPurityNetwork:sendAction(player:getName(), "moveLeft")
        print("H")
    end
end

function jump (player)
    if isServer then
        player:setLinearVelocity(player:getLinearVelocityX(), -7)
    else
        GPurityNetwork:sendAction(player:getName(), "jump")
    end
end
