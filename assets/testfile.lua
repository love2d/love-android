engine.log("logginf from FIIILLLEEEE")
engine.set_color (1., 0., 0.)

function on_touch(x, y)
  engine.log ("got touch at " .. tostring(x) .. "," .. tostring(y))
  engine.set_color (0., 1., 0.)
end
