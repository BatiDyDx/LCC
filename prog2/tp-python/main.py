import random
from typing import Dict, Iterable, List, Optional, Set, Tuple

########### INPUT ######################

def obtener_dist_maxima() -> float:
    """
    obtener_dist_maxima : None -> Float
    obtener_dist_maxima pide al usuario introducir un numero,
    que se usará como distancia maxima para realizar las batallas
    entre ciudades
    """
    return float(input("Ingrese la distancia maxima: "))


def obtener_archivos() -> List[str]:
    archivos = ("jugadores", "distancias", "jugadas")
    nombre_archivos = []
    for archivo in archivos:
        nombre_defecto = archivo + ".txt"
        nombre_archivo = input(f"Ingrese un nombre para el archivo de {archivo} (por defecto es {nombre_defecto}): ")
        # Si el usuario no introduce ningun valor, retornamos el valor por defecto
        nombre_archivo = nombre_archivo if nombre_archivo != "" else nombre_defecto
        nombre_archivos.append(nombre_archivo)

    return nombre_archivos

#########################################


####### FUNCIONES AUXILIARES ############

def crear_jugador(linea: str) -> Tuple[str, int, str]:
    """
    crear_jugador : String -> Tuple(String, Int, String)
    crear_jugador toma una linea de texto, con formato
    nombre,edad,localidad; y devuelve una tupla de la forma
    (nombre, edad, localidad)
    """
    nombre, edad, localidad = linea.split(',')
    # Quitamos el caracter \n de localidad
    localidad = localidad.strip()
    # Convertimos la edad a un int
    edad = int(edad)
    return (nombre, edad, localidad)


def crear_dist_localidades(linea: str) -> Tuple[str, str, float]:
    """
    crear_dist_localidades : String -> Tuple(String, String, Float)
    crear_dist_localidades toma una linea de texto, con formato
    localidad1, localidad2, distancia_entre_localidades, y devuelve
    una tupla de la forma (localidad1, localidad2, distancia_entre_localidades)
    """
    localidad1, localidad2, distancia = linea.split(',')
    # Dado el formato de distancias.txt, debemos quitar el primer
    # caracter de localidad2, ya que es un espacio en blanco
    localidad2 = localidad2.strip()
    # Convertimos la distancia a float
    distancia = float(distancia)
    par_ciudades = sorted([localidad1, localidad2])
    par_ciudades.append(distancia)
    return tuple(par_ciudades)


def generar_jugadores(archivo: str, ciudades: Set[str]) -> Tuple[Dict[str, List[str]], Dict[str, List[str]]]:
    jugadores_ciudad_mayores = { ciudad: list() for ciudad in ciudades }
    jugadores_ciudad_menores = { ciudad: list() for ciudad in ciudades }
    
    EDAD_ADULTOS = 18

    with open(archivo, 'r') as f:
        # Para cada linea del archivo de entrada leemos
        for linea in f.readlines():
            # Pasamos la linea leida del archivo a la funcion crear_jugador
            jugador = crear_jugador(linea)
            # Agreagamos al jugador a la lista
            if jugador[1] < EDAD_ADULTOS:
                jugadores_ciudad_menores[jugador[2]].append(jugador[0])
            else:    
                jugadores_ciudad_mayores[jugador[2]].append(jugador[0])
    return (jugadores_ciudad_mayores, jugadores_ciudad_menores)


def obtener_ciudades_distancias(archivo: str) -> Tuple[Set[str], Dict[Tuple[str, str], float]]:
    ciudades = set()
    dict_ciudades_distancia = dict()
    with open(archivo, 'r') as f:
        # Para cada linea del archivo de entrada leemos
        for linea in f.readlines():
            # Pasamos la linea leida del archivo a la funcion generadora
            # la cual se debe encargar de interpretar el string linea y
            # generar una tupla de la forma (localidad1, localidad2, distancia)
            tupla_ciudades_distancia = crear_dist_localidades(linea)
            # El par_ciudades es una tupla (localidad1, localidad2) ordenada
            # alfabeticamente
            par_ciudades = tupla_ciudades_distancia[:2]
            #Agregamos las ciudades al set de nombres de ciudades
            ciudades.add(par_ciudades[0])
            ciudades.add(par_ciudades[1])
            # Agregamos como llave al diccionario la tupla par_ciudades,
            # cuyo valor es la distancia correspondiente
            dict_ciudades_distancia[par_ciudades] = tupla_ciudades_distancia[2]
    return ciudades, dict_ciudades_distancia


def obtener_dist_localidades(
    dict_ciudades_distancias: Dict[Tuple[str, str], float],
    localidad1: str, localidad2: str
    ) -> float:
    """
    obtener_dist_localidades : Dict(Tuple(String, String) : Float) String String -> Float
    obtener_dist_localidades recibe un diccionario (que representa las distancias entre las ciudades), 
    y dos ciudades, y retorna la distancia entre estas
    """
    # Si las localidades a comparar son la misma, la distancia entre
    # ellas es trivialmente 0
    if localidad1 == localidad2:
        return 0.0
    else:
        # Definimos una tupla ordenada con los nombres de las ciudades
        par_localidades = tuple(sorted((localidad1, localidad2)))
        try:
            # Probamos si la tupla se encuentra en el diccionario
            distancia = dict_ciudades_distancias[par_localidades]
        except KeyError:
            # Si la tupla no está en el diccionario, significa que la distancia
            # entre ambas ciudades no fue declarada en el archivo de texto proveido
            # como input del programa, por lo que levantamos un error
            msg_error = "El par de ciudades "
            msg_error += str(par_localidades)
            msg_error += " no se encuentra en el archivo de distancias proveido,"
            msg_error += " por lo que no se puede conocer la distancia entre ellas"
            raise RuntimeError(msg_error)
        else:
            # Retornamos el valor del diccionario correspondiente a la tupla,
            # la cual sabemos que debe estar, ya que las llaves en el diccionario
            # distancias estan ordenadas
            return distancia


def ciudad_cercana(
    ciudad: str, ciudades_disponibles: Set[str],
    distancias_localidades, distancia_maxima: float) -> Optional[float]:
    
    ciudades_disponibles.discard(ciudad)
    dist = float("inf")
    ciudad_proxima = ""
    for ciudad_proxima in ciudades_disponibles:
        if (dist_c_c2 := obtener_dist_localidades(distancias_localidades, ciudad, ciudad_proxima)) < dist:
            dist = dist_c_c2
            ciudad_proxima = ciudad_proxima
    if dist < distancia_maxima:
        return ciudad_proxima
    else:
        return None

##########################################


############ OUTPUT ######################

def escribir_output(
    output: str,
    enfrenamientos_mayores: List[Tuple[str, str]], enfrentamientos_menores: List[Tuple[str, str]],
    ganadores_mayores: List[str], ganadores_menores: List[str]):
    
    with open(output, 'w') as f:
        f.write("Ronda de mayores")
        for enfrentamiento in enfrenamientos_mayores:
            feed = enfrentamiento[0] + " eliminó a " + enfrentamiento[1]
            f.write(feed)
        if len(ganadores_mayores) == 1:
            f.write(f"El ganador es {ganadores_mayores[0]}\n")
        else:
            f.write(f"Los ganadores son {str(ganadores_mayores).strip('[]')}\n")

        f.write("Ronda de menores")
        for enfrentamiento in enfrentamientos_menores:
            feed = enfrentamiento[0] + " eliminó a " + enfrentamiento[1]
            f.write(feed)
        if len(ganadores_menores) == 1:
            f.write(f"El ganador es {ganadores_menores[0]}\n")
        else:
            f.write(f"Los ganadores son {str(ganadores_menores).strip('[]')}\n")
        f.write('\n')

#########################################

######### LOGICA DE JUEGO ###############

def jugar(jugadores_ciudades, distancias_localidades, distancia_maxima):
    # Realizar rondas por ciudades
    cant_enfrentamientos: int = 1
    enfrentamientos: List[Tuple[str, str]] = []
    ciudades: set[str] = set(jugadores_ciudades.keys())
    while cant_enfrentamientos > 0:
        cant_enfrentamientos = 0
        jugadores_excluidos = { ciudad: list() for ciudad in ciudades }

        for ciudad in ciudades:
            if len(jugadores_ciudades[ciudad]) <= 1:
                if jugadores_ciudades[ciudad] != []:
                    jugadores_excluidos[ciudad] = jugadores_ciudades[ciudad].pop()
                continue
            if len(jugadores_ciudades[ciudad]) % 2 == 1:
                jugadores_excluidos[ciudad] = jugadores_ciudades[ciudad].pop()

            jugadores_ciudad = jugadores_ciudades[ciudad]
            random.shuffle(jugadores_ciudad)
            ganadores = jugadores_ciudad[::2]
            perdedores = jugadores_ciudad[1::2]
            cant_enfrentamientos += len(ganadores)
            enfrentamientos_ciudad = zip(ganadores, perdedores)
            enfrentamientos.extend(enfrentamientos_ciudad)

        for ciudad in ciudades:

            if ciudad not in jugadores_excluidos.keys():
                continue

            ciudad_proxima = ciudad_cercana(ciudad, set(jugadores_excluidos.keys()), distancias_localidades, distancia_maxima)
            if ciudad_proxima is not None:
                loc_ganadora, loc_perdedora = random.sample([ciudad, ciudad_proxima], 2)
                ganador, perdedor = jugadores_excluidos[loc_ganadora], jugadores_excluidos[loc_perdedora]
                cant_enfrentamientos += 1
                # Agrego el enfrentamiento
                enfrentamientos.append((ganador, perdedor))
                # Agrego al ganador nuevamente a la lista de jugadores de su ciudad,
                # mientras que lo quito de jugadores excluidos
                jugadores_ciudades[loc_ganadora].append(jugadores_excluidos.pop(loc_ganadora))
                # Quito al perdedor de jugadores excluidos
                jugadores_excluidos.pop(loc_perdedora)

    ganadores: list[str] = []
    for ciudad, jugadores in jugadores_ciudad:
        if jugadores != []:
            ganadores.append[jugadores[0]]

    # Retorna una lista de nombres de los ganadores
    return enfrentamientos, ganadores


def main():
    # Se obtiene desde la terminal el nombre de los 
    # archivos de jugadores y distancias
    archivo_jugadores, archivo_distancias, archivo_output = obtener_archivos()

    # Obtenemos la distancia máxima a realizar los enfrentamientos
    distancia_maxima = obtener_dist_maxima()
    
    # Obtenemos el diccionario {(localidad1, localidad2) : distancia}
    ciudades, distancias_localidades = obtener_ciudades_distancias(archivo_distancias)

    jugadores_ciudad_mayores, jugadores_ciudad_menores = generar_jugadores(archivo_jugadores, ciudades)

    enfrentamientos_mayores, ganadores_mayores = jugar(jugadores_ciudad_mayores, distancias_localidades, distancia_maxima)
    enfrentamientos_menores, ganadores_menores = jugar(jugadores_ciudad_menores, distancias_localidades, distancia_maxima)

    escribir_output(archivo_output, enfrentamientos_mayores, enfrentamientos_menores, ganadores_mayores, ganadores_menores)
    
    # Avisamos que el output ha sido escrito
    print("El archivo " + archivo_output + " fue escrito.")

if __name__ == "__main__":
    main()
