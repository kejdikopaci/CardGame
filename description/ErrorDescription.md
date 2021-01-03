### Fehlermeldungen mit Programmende (Errors)

##### Falsche Anzahl an Parameter bei Programmaufruf

Wird das Programm mit einer falschen Anzahl von Parameter aufgerufen, soll das Programm mit  **-2** beenden (Oop::RETURN_ERROR_ARGUMENT) und folgende Fehlermeldung ausgeben:

```
Usage: ./game <config-file>
```

##### Configfile ungültig

Ist das [Config-File] ungültig endet das Programm mit  **-3** und folgende Fehlermeldung wird ausgeben:

```
[ERROR] Invalid config file!\n
```

##### Out of Memory

Wenn kein dynamischer Speicher mehr zur Verfügung steht, wird das Programm mit dem Rückgabewert **-1** (Oop::RETURN_ERROR_ALLOC) beenden und folgende Fehlermeldung ausgeben:

```
[ERROR] Memory error!\n
```

##### Command ungültig

Der Command wurde nicht erkannt. (zB. sett 5 to 3, Attak 2 with 3, ...)

```
[INFO] Unknown command!\n
```

##### Falsche Parameter bei Command

Der  Command wurde erkannt, jedoch sind die Parameter außerhalb des vorgegebenen Wertebereichs (zB. set 4 to 22, attack 8 with 1, ....)

```
[INFO] Invalid command parameter!\n
```

##### Command kann nicht ausgeführt werden

Ist der Command gültig und sind die Parameter richtig, kann es sein, dass der Command trotzdem nicht ausgeführt werden kann, weil  z.B.

- eine bestehende Kreatur dabei überschrieben werden würde
- keine Kreatur auf dieser Stelle existiert (Handkarten oder Spielfeld)
-  `set 4 to 2` , jedoch habe ich nur 2 Karten auf der Hand

In diesem Fall wird diese Fehlermeldung ausgegeben:

```
[INFO] Execution not possible!\n
```


##### Schilder müssen zuerst zerstört werden

Beim Angriff müssen zuerst **IMMER** alle Schild-Kreaturen des Gegners eliminiert werden, bevor der Gegner direkt oder eine Nicht-Schild-Kreatur des Gegners angegriffen werden kann.

Passiert jedoch ein Angriff auf den Gegner oder eine Nicht-Schild-Kreatur des Gegners, obwohl noch eine Schild-Kreatur auf dem Spielfeld des Gegners liegt, wird diese Fehlermeldung ausgegeben:

```
[INFO] Destroy all shields first!\n
```

Es müssen also zuerst immer **ALLE** Schild-Kreaturen des Gegners vernichtet werden, damit andere Kreaturen (oder der Spieler) angegriffen werden können.


##### Nicht genügend Mana vorhanden

Ist für einen Zug nicht genügend Mana vorhanden, wird folgende Fehlermeldung ausgegeben.

```
[INFO] Not enough mana for this move!\n
```



##### Rebirth kann nicht ausgeführt werden

Ist der Friedhof leer oder die eigene Spielfeldhälfte voll mit Kreaturen, wird keine Kreatur wiederbelebt. Die Karte gilt dennoch als ausgespielt und folgende Fehlermeldung wird ausgegeben:

```
[INFO] Rebirth unsuccessful\n
```

