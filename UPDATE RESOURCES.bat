:: 
:: This script updates the /resources folder in all builds
:: Resources/resources is the master
:: 




@echo on




:: Delete old files and folders
rmdir /s /q "Release/resources"
rmdir /s /q "Debug/resources"
rmdir /s /q "PelletQuest/resources"


:: Copy new ones in
xcopy "Resources" "Release" /s /e /v
xcopy "Resources" "Debug" /s /e /v
xcopy "Resources" "PelletQuest" /s /e /v