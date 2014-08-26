dofile("scenes/init/playerMovement.lua")

function eventHandler(event)
    
    player = GEntityManager:getMovableEntityByName(playerName)
    
    if (event.Type == Event.KeyPressed) then
        if (event.Key.Code == Keyboard.Left) then
            moveLeft(player)
        elseif (event.Key.Code == Keyboard.Right) then
            moveRight(player)
        else
            jump(player)
        end
    end
   
end
