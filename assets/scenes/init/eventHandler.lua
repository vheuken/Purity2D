GPurityLuaManager:doFile("scenes/init/playerMovement.lua")

function eventHandler(event)
    if (event.type == Purity.EventType.KeyPressed) then
        if (event.keyEvent.code == Purity.Keyboard.Left or event.keyEvent.code == Purity.Keyboard.A) then
            GPurityActionManager:enableAction("MOVE_LEFT")
        elseif (event.keyEvent.code == Purity.Keyboard.Right or event.keyEvent.code == Purity.Keyboard.D) then
            GPurityActionManager:enableAction("MOVE_RIGHT")

        else
            GPurityActionManager:enableAction("MOVE_UP")
        end
	elseif (event.type == Purity.EventType.KeyReleased) then
        if (event.keyEvent.code == Purity.Keyboard.Left or event.keyEvent.code == Purity.Keyboard.A) then
            GPurityActionManager:disableAction("MOVE_LEFT")
        elseif (event.keyEvent.code == Purity.Keyboard.Right or event.keyEvent.code == Purity.Keyboard.D) then
            GPurityActionManager:disableAction("MOVE_RIGHT")
        else
            GPurityActionManager:disableAction("MOVE_UP")
        end
    end
end
