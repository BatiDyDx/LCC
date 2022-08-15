## SOPA DE LETRAS

# Implementacion en C y Python
Para compilar el generador del archivo descripcion utilizamos

```
gcc src/main.c src/generador_descripcion.c -o generador_desc
```

Una vez que tenemos el generador lo utilizamos de la forma

```
./generador_desc <archivo_lemario> <tamaño> <cantidad_palabras> <complejidad>
```

El programa nos pedirá el nombre del archivo de salida para la descripcion
generada. Supongamos que elegimos para el nombre `descripcion.txt`.

Ahora podemos correr el generador de sopas de letras en python, pasandole como
entrada el nombre de nuestro archivo descripcion

```
python src/sopa_letras.py descripcion.txt
```

# Compilar y ejecutar archivos de pruebas

Para correr las pruebas en python requerimos de la libreria pytest.

Las pruebas en python las ejecutamos como sigue:

```
pytest tests/test_sopa_letras.py
```

Para compilar el archivo de pruebas en c hacemos

```
gcc src/generador_descripcion.c tests/test_generador.c -o test_generador
```

Una vez que ejecutemos la salida anterior, deberiamos ver un mensaje que diga
"Todas las pruebas pasan"