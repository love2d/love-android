engine.log("Log Message from Lua ;D")
engine.set_color (1., 0., 0.)

function on_touch(x, y)
  engine.log ("got touch at " .. tostring(x) .. "," .. tostring(y))
  engine.set_color (0., 1., 0.)
end

function update(dt)
  r,g,b = engine.get_color()

  r = math.max(0., r - dt * 0.4)
  g = math.max(0., g - dt * 0.4)
  b = math.max(0., b - dt * 0.4)
  
  engine.set_color (r, g, b)
end
