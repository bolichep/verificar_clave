# Verificar clave
## Propósito:
Verifica que la clave de un usuario en particular no esté siendo utilizada.
En caso afirmativo, se informa mediante un mensaje al inicio de sesión,
notificado en el escritorio.
Por defecto verifica el usuario ```alumno``` y la clave de usuario ```alumno```


### Uso:
```bash 
/usr/bin/verificar_clave
```
Soporta los siguientes parámetros para solapar los valores por defecto:

```-u``` para indicar el nombre de **usuario**.

```-c``` para indicar la **clave** de usuario.

Ej.

```bash
validar_clave -u pepe -c fg851la
```
En caso que el usuario *pepe* utilice la clave *fg851la* se mostrará un
mensaje de alerta, en caso contrario no se mostrará ningún mensaje.


### Compilar:
```bash
cmake -DCMAKE_BUILD_TYPE=Release . && make
```

### Instalar:
Se instalan dos archivos, ```verificar_clave``` en ```/usr/bin``` y el archivo
```verificar_clave.desktop``` en ```/etc/xdg/autostart```

```bash
make install
```

### Depencencias:
- GCC 4.8 o superior o cualquier compilador que soporte C99
- GTK+-2.0
- libpam
- libnotify

### Nota para administradores.
Si utiliza ```systemd``` puede ver el *log* del programa utilizando ```journalctl -f```



