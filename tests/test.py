#!/usr/bin/env python

import _ashell as ash

s = ash.World.new_system()
s.init()
s.run(10)
