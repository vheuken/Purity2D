local startup = true


dofile("scenes/init/servercfg.lua")

function onPhysicsUpdate()
    if startup == true then
        print("Local IP Address: " .. GPurityNetwork:getLocalAddress())
        print("Public IP Address: " .. GPurityNetwork:getPublicAddress())
        print("Port: " .. port)
        
        if isServer then
            print("Running as a server...")
            GPurityNetwork:initializeServer(port)
        else
            print("Running as a client...")
            GPurityNetwork:initializeClient()
            GPurityNetwork:setPort(port)
            GPurityNetwork:connectToServer(server)
        end
         
        startup = false
    end
end
