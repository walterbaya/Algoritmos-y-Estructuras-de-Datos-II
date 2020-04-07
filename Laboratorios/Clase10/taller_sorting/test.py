import sys
from math import log
from random import shuffle
from itertools import chain
import optparse

from list_algorithms import find_sorting_algorithms
from list import List

def main():
    parser = optparse.OptionParser("usage: %prog algoritmo [options]")
    parser.prog= __file__

    parser.add_option('-l', '--listita', dest='listita', default=False, action='store_true', help='ejecuta tu algoritmo con una lista chiquita')
    parser.add_option('-L', '--listota', dest='listota', default=False, action='store_true', help='ejecuta tu algoritmo con una lista grandota')
    parser.add_option('-g', '--grupo', dest='group_name', help='En caso de ambiguedad, el nombre del grupo')
    parser.add_option('-e', '--estimar-constantes', default=False, action='store_true', dest='estimate_constants', help='Si tu algoritmo es n*log(n) o n^2, trata de estimar la constante')
    #### agregado por partu ##
    parser.add_option('-c', '--lcustom', dest='lcustom', default=False, action='store', type="string", help='ejecuta tu algoritmo con una lista arbitraria pasada por parametro')
    ##########################
    

    available_algorithms= find_sorting_algorithms()

    options, args = parser.parse_args(sys.argv[1:])
    fail= len(args) == 0
    matches= 0
    selected_sorting_algorithm= None
    if not fail:
        selected_algorithm= args[0]
        for group_name, algorithms in list(available_algorithms.items()):
            if options.group_name is not None and options.group_name != group_name: continue
            for name, sorting_algorithm in algorithms:
                if name == selected_algorithm:
                    matches+= 1
                    selected_sorting_algorithm= sorting_algorithm

    fail= fail or matches != 1

    if matches == 0:
        print()
        print("Falta el nombre del algoritmo (o pifiaste escribiendo)!")
    elif matches > 1:            
        print()
        print("Hay muchos grupos con ese algoritmo, usa -g")

    if fail:
        print("Estan definidos estos:\n")
        for group_name, algorithms in list(available_algorithms.items()):
            print("\tGrupo: %s" % group_name)
            for name, sorting_algorithm in algorithms:
                print("\t\t%s" % name)
        print() 
        parser.print_help()
        return

    if not any([options.listita, options.listota, options.lcustom, options.estimate_constants]):
        parser.error("te falta elegir la opcion!")
        parser.print_help()

    if options.listita:
        l= list(range(10)); shuffle(l)
        l= List(l)
        apply(l, selected_sorting_algorithm)
    
    elif options.listota:
        l= list(range(5000)); shuffle(l)
        l= List(l)
        apply(l, selected_sorting_algorithm)

    ### Agregado por partu ####
    elif options.lcustom:
        l = strToList(options.lcustom)
        print(l)
        apply(l, selected_sorting_algorithm)
    ######################################

    elif options.estimate_constants:
        print()
        print("Bueno, parece que tu algoritmo es O(%s) con constante %.02f" % estimate_constants(selected_sorting_algorithm))
        print()

def apply(l, sorting_algorithm):
    shuffle(l)
    orig_l= l[:]
    solution= sorted(orig_l)
    l= sorting_algorithm(l)

    if l == solution:
        print("Anduvo! =D")
    elif len(l) < 20: #Si fala y la lista es "mostrable"
        print("nop, algo fallo")
        print("la lista original era: %s" % orig_l)
        print("tu algoritmo la dejo asi: %s" % l)
    else:
        print("no anduvo =(")
        print("la lista es muy grande, si queres ver que paso, podes probar con -l")


def estimate_constants(sorting_algorithm):
    candidates= [('n^2', lambda x:x**2), ('n*log(n)', lambda x:x*log(x,2))]

    dots= generate_dots(sorting_algorithm)
    results= []
    for name, candidate in candidates:
        constants= []
        for x,y in dots:
            c= float(y)/candidate(x)
            constants.append(c)
        avg= sum(constants)/len(constants)

        error= sum(abs(avg*candidate(x)-y) for x,y in dots)
        results.append((name, avg, error))

    best= min(results, key=lambda x:x[2])
    return best[0], best[1]



def generate_dots(sorting_algorithm):
    res= []
    print("Ejecutando el algoritmo...")
    for i in range(50, 300, 10):
        l = list(range(i))
        shuffle(l)
        l= List.from_list(l) 
        sorting_algorithm(l)

        res.append((i, l.counter.cnt))

    return res

######## agregado por partu ############
def strToList(s):
    #asumo que el string representa una lista bien formada.
    s = s.replace(' ', '')
    if len(s) < 3:
        raise Exception('Ingresaste una lista vacia... :\'(')
    l = list(map(int,s[1:-1].split(',')))
    return List.from_list(l)
########################################



        

if __name__ == '__main__':
    main()
