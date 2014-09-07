GPurityLuaManager:doFile("scenes/init/playerMovement.lua")

LEFT = false
RIGHT = false
UP = false

function eventHandler(event)  
    if (event.type == Purity.EventType.KeyPressed) then
        if (event.keyEvent.code == Purity.Keyboard.Left or event.keyEvent.code == Purity.Keyboard.A) then
            LEFT = true
        elseif (event.keyEvent.code == Purity.Keyboard.Right or event.keyEvent.code == Purity.Keyboard.D) then
            RIGHT = true
        else
            UP = true
        end
	elseif (event.type == Purity.EventType.KeyReleased) then
        if (event.keyEvent.code == Purity.Keyboard.Left or event.keyEvent.code == Purity.Keyboard.A) then
            LEFT = false
        elseif (event.keyEvent.code == Purity.Keyboard.Right or event.keyEvent.code == Purity.Keyboard.D) then
            RIGHT = false
        else
            UP = false
        end
    end
end
