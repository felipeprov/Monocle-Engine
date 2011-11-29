print("Moonocle Engine" .. version);
print("Scripting Monocle with Lua ");
print("Getting start with Lua Scripting")


gameScene = GameScene.GetCurrentScene();

function Entity:ResetPosition(x, y)
	self:setPosition(x,y)
end
Entity.speed = 25;

function EntityUpdate(entity, dt)
	local rot = entity:getRotation()
	entity:setRotation(rot + entity.speed*dt)
end

--text = Text.new("Lua + Monocle = Moonocle Engine " .. version)
--text:ResetPosition(20,20)
--gameScene:Add(text)

text = Text.new("My first script")
text:ResetPosition(20,320)
gameScene:Add(text)

text = Text.new("Author: Felipe Provenzano")
text:ResetPosition(20,580)
gameScene:Add(text)

ent = Entity.new()
ent:ResetPosition(200,400)
gameScene:Add(ent)
ent:addScript("OnUpdate", "EntityUpdate")
ent.speed=300

ent = Entity.new()
ent:ResetPosition(500,200)
gameScene:Add(ent)
ent:addScript("OnUpdate", "EntityUpdate")

ent = Entity.new()
ent:ResetPosition(200,200)
gameScene:Add(ent)
ent:addScript("OnUpdate", "EntityUpdate")
ent.speed=-90

