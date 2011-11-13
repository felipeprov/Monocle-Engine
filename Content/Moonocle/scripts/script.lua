print("Moonocle Engine" .. version);
print("Scripting Monocle with Lua ");
print("Getting start with Lua Scripting")


gameScene = GameScene.GetCurrentScene();

function Entity:ResetPosition(x, y)
	self:setPosition(x,y)
end

ent = Entity.new()
ent:ResetPosition(200,300);
gameScene:Add(ent)

ent = Entity.new()
ent:ResetPosition(500,200);
gameScene:Add(ent)

ent = Entity.new()
ent:ResetPosition(100,300);
gameScene:Add(ent)