@echo off

echo symlink library folder to the arduino folder
echo must be exect as admin

REM set arduino_lib_path="C:\Users\axxca\Documents\Arduino\libraries"
REM set project_lib_path="C:\gitprojects\rollout-makers\Libraries"

set arduino_lib_path="C:\Users\acatoire\Documents\Arduino\libraries"
set project_lib_path="C:\perso\projets\rollout-makers\Libraries"

mklink /D %arduino_lib_path%\RGB-matrix-Panel-master %project_lib_path%\RGB-matrix-Panel-master
mklink /D %arduino_lib_path%\json-streaming-parser %project_lib_path%\json-streaming-parser
mklink /D %arduino_lib_path%\Adafruit_GFX_Library %project_lib_path%\Adafruit_GFX_Library
mklink /D %arduino_lib_path%\Blynk %project_lib_path%\Blynk



pause