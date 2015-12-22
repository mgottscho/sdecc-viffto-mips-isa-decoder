#!/bin/python

import platform
os_info = platform.platform()

if os_info.find('NT') >= 0: # native Windows build
    env = Environment(MSVC_USE_SCRIPT = 'C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\bin\\x86_amd64\\vcvarx86_amd64.bat', MSVC_BATCH = 1)
    env.Append(CPPFLAGS = ['/c',
                           '/nologo',
                           '/W3',
                           '/WX-',
                           '/O2',
                           ])

elif os_info.find('Linux') >= 0: # Linux build
    env = Environment()
    env.Append(CPPFLAGS = '-Wall')
    env.Append(CPPPATH = ['src',
                         ])
else:
    print 'unknown platform, exiting'
    exit(1);

sources = [
    Glob('src/*.cc'),
]

defaultBuild = env.Program(target = 'mipsdecode', source = sources)
Default(defaultBuild)
