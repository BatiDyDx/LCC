from src.sopa_letras import *
import pytest


def test_direcciones_segun_complejidad():
    assert direcciones_por_complejidad(1) == {(1,0), (0,1), (1,1)}
    assert direcciones_por_complejidad(0) == {(1,0), (0,1)}
    assert direcciones_por_complejidad(3) == {(1,0), (0,1), (1,1),
                                            (-1,0), (0,-1), (1,-1),
                                            (-1,1), (-1,-1)}


def test_parsear_descripcion():
    dim = 10
    palabras = {
        "meteorizacion",
        "estamento",
        "razonar",
        "ahorrista",
        "trueno"
    }
    complejidad = 2
    assert parsear_descripcion("tests/descripcion_prueba.txt") == (dim, palabras, complejidad)


def test_validar_palabras():
    palabras = {
        "trujamanear",
        "jazarino",
        "amurallar",
        "desmultiplicar"
    }
    # Comprobamos que la funcion retorne
    assert validar_palabras(15, palabras, 2) is None
    assert validar_palabras(3, {"sol", "cae", "de", "ha"}, 3) is None
    # Comprobamos que la funcion levante un ValueError
    with pytest.raises(ValueError):
        validar_palabras(10, palabras, 0)
        validar_palabras(3, {"sol", "cae", "de", "ha"}, 1)


def test_modificar_sopa():
    sopa = [
        ["t", "e", "l", "a"], 
        ["_", "e", "_", "_"],
        ["d", "_", "_", "_"],
        ["_", "_", "_", "_"]
    ]

    resultado1 = [
        ["t", "e", "l", "a"],
        ["_", "e", "_", "g"],
        ["d", "_", "_", "u"],
        ["_", "_", "_", "a"]
    ]

    assert modificar_sopa(sopa, (3, 0), (0, 1), "agua", True) == (True, resultado1)
    assert modificar_sopa(sopa, (3, 0), (0, 1), "agua", False) == (False, sopa)


def test_hay_duplicados():
    sopa1 = [
        ["t", "e", "l", "a"],
        ["r", "e", "n", "g"],
        ["d", "m", "l", "u"],
        ["e", "o", "a", "a"]
    ]

    sopa2 = [
        ["t", "e", "l", "a"],
        ["r", "e", "n", "g"],
        ["d", "m", "m", "u"],
        ["e", "o", "a", "a"]
    ]
    assert hay_duplicados(sopa1, {"del", "agua", "tela"}) is True
    assert hay_duplicados(sopa2, {"del", "agua", "tela"}) is False


def test_obtener_filas():
    sopa = [
        ['a', 'b', 'c', 'd'],
        ['e', 'f', 'g', 'h'],
        ['i', 'j', 'k', 'l'],
        ['m', 'n', 'o', 'p']
    ]
    filas = obtener_filas(sopa)
    assert "efgh" in filas
    assert "ijkl" in filas


def test_obtener_columnas():
    sopa = [
        ['a', 'b', 'c', 'd'],
        ['e', 'f', 'g', 'h'],
        ['i', 'j', 'k', 'l'],
        ['m', 'n', 'o', 'p']
    ]
    columnas = obtener_columnas(sopa)
    assert "bfjn" in columnas
    assert "dhlp" in columnas


def test_obtener_diagonales():
    sopa = [
        ['a', 'b', 'c', 'd'],
        ['e', 'f', 'g', 'h'],
        ['i', 'j', 'k', 'l'],
        ['m', 'n', 'o', 'p']
    ]
    diagonales = obtener_diagonales(sopa)

    assert "afkp" in diagonales
    assert "ch" in diagonales
    assert "ejo" in diagonales
    assert "m" in diagonales
    assert "hkn" in diagonales
    assert "cfi" in diagonales
    assert "dgjm" in diagonales
    assert "p" in diagonales


def test_copiar_sopa():
    sopa = [
        ['a', 'b', 'c', 'd'],
        ['e', 'f', 'g', 'h'],
        ['i', 'j', 'k', 'l'],
        ['m', 'n', 'o', 'p']
    ]
    assert sopa == copiar_sopa(sopa)


def test_completar_espacios():
    sopa_incompleta = [
        ['_', '_', '_', 'r'],
        ['e', '_', 'f', 'h'],
        ['_', 'z', 'a', '_'],
        ['m', '_', 'o', '_']
    ]
    sopa_completa = completar_espacios(sopa_incompleta)
    for i in range(len(sopa_completa)):
        for j in range(len(sopa_completa)):
            assert sopa_completa[i][j] != '_'


def test_completar_sopa():
    sopa_incompleta = [
        ["o", "o", "r", "a", "j", "a", "p", "_"],
        ["_", "r", "g", "_", "_", "_", "_", "_"],
        ["_", "_", "e", "a", "_", "_", "_", "_"],
        ["o", "_", "_", "c", "t", "_", "_", "_"],
        ["r", "_", "_", "o", "a", "i", "_", "_"],
        ["r", "_", "_", "_", "t", "b", "t", "_"],
        ["e", "_", "_", "_", "_", "o", "a", "o"],
        ["p", "_", "_", "_", "_", "_", "m", "_"]
    ]
    palabras = {"pajaro", "abacero", "gatito", "perro", "moto"}
    sopa = completar_sopa(sopa_incompleta, palabras)

    for i in range(len(sopa)):
        for j in range(len(sopa)):
            assert sopa[i][j] != '_'

    assert hay_duplicados(sopa, palabras) is False
