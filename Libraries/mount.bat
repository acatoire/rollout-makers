@echo off

echo symlink library folder to the arduino folder
echo must be exect as admin

set arduino_lib_path="C:\Users\axxca\Documents\Arduino\libraries"
set project_lib_path="C:\gitprojects\rollout-makers\Libraries"

mklink /D %arduino_lib_path%\TrollOutLib %project_lib_path%\TrollOutLib
mklink /D %arduino_lib_path%\RGB-matrix-Panel-master %project_lib_path%\RGB-matrix-Panel-master
mklink /D %arduino_lib_path%\GoogleMapsApi %project_lib_path%\GoogleMapsApi
mklink /D %arduino_lib_path%\json-streaming-parser %project_lib_path%\json-streaming-parser



pause