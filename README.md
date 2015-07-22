# Verificar clave
## Propósito:
Verifica que la clave de un usuario en particular no esté siendo utilizada.
En caso afirmativo, se informa mediante un mensaje al inicio de sesión,
notificado en el escritorio.

## Compilar:
```bash
cmake -DCMAKE_BUILD_TYPE=Release . && make
```bash

## Instalar:
Se instalan dos archivos, ```verificar_clave``` en ```/usr/bin``` y el archivo
```verificar_clave.desktop``` en ```/etc/xdg/autostart```

```bash
make install
```bash


## Depencencias:
- GCC 4.8 o superior o cualquier compilador que soporte C99
- GKT+-2.0
- libpam
- libnotify



