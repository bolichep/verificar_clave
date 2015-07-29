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

```-m``` para indicar el mensaje informativo.

```-t``` para indicar el titulo del mensaje (generalmente de mayor tamaño y en negritas).

```-a``` para indicar la alarma, formato = segundos:repetir

```-h``` muestra un resumen de ayuda.


Ej.

```bash
verificar_clave -u pepe -c fg851la
```

En caso que el usuario *pepe* utilice la clave *fg851la* se mostrará un
mensaje de alerta, en caso contrario no se mostrará ningún mensaje.

Cualquier usuario:

```bash
verificar_clave -u $(whoami) -c fg851la
```

Alarma:
Repetir el mensaje 8 veces cada 60 segundos.

```bash
verificar_clave -u pepe -c fg851la -a 60:8
```

Repetir una sóla vez a los 8 segundos.

```bash
verificar_clave -u pepe -c fg851la -a 8
```


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



