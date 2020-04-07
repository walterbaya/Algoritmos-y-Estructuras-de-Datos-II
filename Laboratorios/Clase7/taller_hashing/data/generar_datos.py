#-*- coding: utf-8 -*-
'''Script que genera las claves para usar en el taller de hash.'''
import sys
import random

random.seed("ALGORITMOS_2")

SAMPLE_SIZE = 5000

def gaussiana():
    'Generador de un sample de una distribución gausseana'
    v = -1
    while v < 0:
        v = int(random.gauss(100000, 5000))
    return v


def libretas():
    'Generador de un sample de una distribución (inventada) de libretas'
    ano = -1
    while ano < 0:
        ano = 15 - 1 * int(random.paretovariate(6))
    num = int(random.uniform(1, 5000))
    return '{:0>2}{:0>4}'.format(ano, num)


def uniforme():
    'Generador un sample de una distribución uniorme'
    return int(random.uniform(0, 6378277))


def generador(f, sample_size=SAMPLE_SIZE):
    def __gen__():
        s = set()
        r = sample_size
        while len(s) < sample_size:
            l = [f() for x in xrange(sample_size - len(s))]
            ns = set(l)
            s = s.union(ns)

        return s
    return __gen__


def crear_archivo_datos(nombre, generador):
    with open(nombre, 'w') as f:
        for v in generador():
            f.write('{}\n'.format(v))


if len(sys.argv) < 2:
    print 'Usage: {} nombre_dataset'.format(sys.argv[0])
    exit()

nombre_dataset = sys.argv[1]

if nombre_dataset == 'libretas':
    crear_archivo_datos('libretas.txt', generador(libretas))
elif nombre_dataset == 'gauss':
    crear_archivo_datos('gauss.txt', generador(gaussiana))
elif nombre_dataset == 'uniforme':
    crear_archivo_datos('uniforme.txt', generador(uniforme))
