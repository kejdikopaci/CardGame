# Framework


## Aufbau des Repositories

```
config/     (Stellt die ConfigFiles für das Spiel bereit)
	config01.json
description/  (Die Spielanleitung aufgeteilt auf mehrere .md File zur besseren Übersicht)
	ErrorDescription.md
	FrameworkDescription.md
	GameField.md
	SpellCardDescription.md
rapidjson/   (RapidJson Framework für das Einlesen des ConfigFiles)
    ...
Interface.cpp
Interface.hpp
main.cpp
Makefile
Random.cpp
Random.hpp
README.md
```

Das folgende Framework (`Interface.hpp`, `Interface.cpp`, `Random.hpp`, `Random.cpp`, <mark>**`main.cpp`**</mark> ) wurde zur Verfügung gestellt.

## Makefile

Zum Kompilieren und Ausführen kann das bereitgestellte Makefile verwendet werden:

-----------------------------------------------------------------------------------------------------
|$ make												|
|													|
|- Kompiliert das Programm										|
|													|
|$ make clean												|
|													|
|- Entfernt alle temporären Dateien (inklusive executable).						|
|													|
|$ make run												|
|													|
|- Führt das Programm aus und verwendet das Config-File *config/config01.json*			|
-----------------------------------------------------------------------------------------------------

