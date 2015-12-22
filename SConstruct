#!/bin/python

import os

env = Environment()
env.Append(CPPFLAGS = '-Wall')
env.Append(CPPPATH = ['src',
                      ])

sources = [
    Glob('src/*.cc'),
]

defaultBuild = env.Program(target = 'mipsdecode', source = sources)
Default(defaultBuild)
