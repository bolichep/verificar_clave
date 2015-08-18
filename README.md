# Verificar clave
## Propósito:
Verifica que la clave de un usuario en particular no esté siendo utilizada.
En caso afirmativo, se informa mediante un mensaje al inicio de sesión,
notificado en el escritorio.

<a href="http://www.zimagez.com/zimage/verificarclave-20.php" target="_blank" title=""><img src="http://www.zimagez.com/miniature/verificarclave-20.png" alt="" /></a>


#### Usuario y clave:

La clave por defecto es ```alumno```.

Se detecta automáticamente el nombre de usuario, por lo tanto, por defecto
el nombre de usuario es de aquel que ejecute la aplicación y lo mismo para
el titulo, esto evita el uso de $(whoami) en la línea de parámetros.


#### Botón "Cambiar clave..."

Al realizar un click en el botón se intenta abrir el Administrador de Usuarios y
Grupos, el cual dependera del escritorio actual (XFCE, MATE, etc).


### Uso:
```bash 
/usr/bin/verificar_clave
```
Soporta los siguientes parámetros para solapar los valores por defecto:

```-u``` para indicar el nombre de **usuario**.

```-c``` para indicar la **clave** de usuario.

```-m``` para indicar el **mensaje** informativo.

```-t``` para indicar el **titulo** del mensaje (generalmente de mayor tamaño y en negritas).

```-a``` para indicar la **alarma**, formato = segundos:repetir

```-b``` **no** mostrar **botón** de acción, "Cambiar clave..."

```-p``` nombre del *programa* para Administrar Claves y Grupos.
        [Por defecto estos...](https://github.com/daltomi/verificar_clave#administradores-de-usuarios-y-grupos)

```-h``` muestra un resumen de ayuda.



Ejemplos:

- Algún usuario con alguna clave:

```bash
verificar_clave -u pepe -c fg851la
```

En caso que el usuario *pepe* utilice la clave *fg851la* se mostrará un
mensaje de alerta, en caso contrario no se mostrará ningún mensaje.

- Usuario actual con alguna clave:

```bash
verificar_clave -c fg851la
```

- Alarma

Repetir el mensaje 8 veces cada 60 segundos.

```bash
verificar_clave -c fg851la -a 60:8
```

Repetir una sóla vez a los 8 segundos.

```bash
verificar_clave -c fg851la -a 8
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

##### Administradores de Usuarios y Grupos:
- MATE  : mate-system-tools (mate-users-admin)
- XFCE  : mate-system-tools (mate-users-admin)
- GNOME : gnome-system-tools (users-admin)


### Archivo .desktop:
Si la contraseña de usuario tiene caracteres espciales(#%?...) utilice la
secuencia de escape: ```\```.
Por ejemplo, para la contraseña ```Yu%?``` debera utilizar la secuencia de
escape, asi: ```Yu\%\?```


### Nota para administradores.
Si utiliza ```systemd``` puede ver el *log* del programa utilizando ```journalctl -f```
