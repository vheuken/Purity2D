dofile("scenes/init/servercfg.lua")

function moveRight (player)
    if isServer then
        player:setLinearVelocity(10, player:getLinearVelocityY())
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
