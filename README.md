ESP8266 mruby VM for Ironman 2020
===

## Reset Board

Open Monitor via PlatformIO

```
pio device monitor
```

Use `DTR` toggle to reset

```
Ctrl + T
Ctrl + D
# DTR inactive
Ctrl + T
Ctrl + D
# DTR active
# Reset Board
```

D1 mini didn't use `RST` to reset in this case.
