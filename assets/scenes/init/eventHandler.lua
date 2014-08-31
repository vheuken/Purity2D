GPurityLuaManager:doFile("scenes/init/playerMovement.lua")

function eventHandler(event)  
    player = GEntityManager:getMovableEntityByName(playerName)

    if (event.type == Purity.EventType.KeyPressed) then
        if (event.keyEvent.code == Purity.Keyboard.Left or event.keyEvent.code == Purity.Keyboard.A) then
            moveLeft(player)
        elseif (event.keyEvent.code == Purity.Keyboard.Right or event.keyEvent.code == Purity.Keyboard.D) then
            moveRight(player)
        else
            jump(player)
        end
    end
   
end
