from main import *


def test_crear_jugador():
    assert crear_jugador("JOSE DELGADO,51,Rosario\n") == ("JOSE DELGADO", 51, "Rosario")
    assert crear_jugador("MANUEL JIMENEZ,46,Villa Maria\n") == ("MANUEL JIMENEZ", 46, "Villa Maria")
    assert crear_jugador("NORA DURAN,28,CABA\n") == ("NORA DURAN", 28, "CABA")


def test_crear_dist_localidades():
    assert crear_dist_localidades("Cordoba, Villa Gobernador Galvez, 410.3") == ("Cordoba", "Villa Gobernador Galvez", 410.3)
    assert crear_dist_localidades("Santa Fe, Villa Maria, 302.7") == ("Santa Fe", "Villa Maria", 302.7)
    assert crear_dist_localidades("Rio Cuarto, Serodino, 388.7") == ("Rio Cuarto", "Serodino", 388.7)


def test_generar_lista_jugadores():
    jugadores = (
        {
            "Serodino": ["MARIA EUGENIA PORRAS", "FERNANDO CORRALES"],
            "Santa Fe": ["CARMEN CORRALES"]
        },
        {
            "Rio Cuarto": ["ROXANA MARIA MIRANDA"],
            "Rosario": ["MARTA VILLALTA"],
            "Santa Fe": ["JORGE ARTURO MUNOZ"]
        }
    )

    assert generar_jugadores("jugadores_test.txt") == jugadores


def test_generar_dict_distancias():
    ciudades = {"CABA", "Cordoba", "Rio Cuarto", "Rosario"}
    dict_ciudades_distancia = {
        ("CABA", "Cordoba"): 696.4,
        ("CABA", "Rio Cuarto"): 617.8,
        ("CABA", "Rosario"): 299.9
    }
    assert obtener_ciudades_distancias("distancias_test.txt") == (ciudades, dict_ciudades_distancia)


def test_obtener_dist_localidades():
    dict_dist = {
        ("CABA", "Cordoba"): 696.4, 
        ("Santa Fe", "Villa Constitucion"): 228.3, 
        ("CABA", "Rosario"): 299.9
    }
    assert obtener_dist_localidades(dict_dist, "CABA", "Cordoba") == 696.4
    assert obtener_dist_localidades(dict_dist, "Rosario", "CABA") == 299.9
    assert obtener_dist_localidades(dict_dist, "Villa Constitucion", "Santa Fe") == 228.3

