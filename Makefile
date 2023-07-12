build:
	D:/Software/UE_5.2/Engine/Build/BatchFiles/Build.bat TinyShooterEditor Win64 Development -Project="D:\Projects\gamedev\TinyShooter\TinyShooter.uproject" -WaitMutex -FromMsBuild

editor:
	D:/Software/UE_5.2/Engine/Binaries/Win64/UnrealEditor.exe "D:\Projects\gamedev\TinyShooter\TinyShooter.uproject" -skipcompile

