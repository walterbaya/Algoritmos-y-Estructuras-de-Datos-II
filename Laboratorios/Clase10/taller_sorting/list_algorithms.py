from glob import glob
from collections import defaultdict
import inspect
import os


class presentar(object):
    def __init__(self, f):
        self.f = f

    def __call__(self, lista):
        tmp = range(len(lista))
        return self.f(lista)


# - Devuelve un diccionario de grupo -> lista de algoritmos.
# - La lista de algoritmos son las funciones que tengan "@presentar" arriba.
# - El nombre del grupo lo saca de una variable global "grupo" en el archivo .py que contiene algoritmos con el
#   @presentar, sino usa el nombre del archivo.
# - Los posibles algoritmos los busca en todos los archivos .py en el mismo directorio o en la subcarpeta
#   sorting_algorithms si es que existe
def find_sorting_algorithms():
    here = os.path.abspath(os.path.dirname(__file__))
    here = os.path.curdir

    # este caso es para cuando hacemos la expo
    algorithms_dir = os.path.join(here, 'sorting_algorithms')
    fromlist = [os.path.join(here, 'sorting_algorithms')]
    module_template = 'sorting_algorithms.%s'
    if not os.path.exists(algorithms_dir):
        # este caso es para cuando los alumnos estan probando en el labo
        algorithms_dir = here
        fromlist = None
        module_template = '%s'

    res = defaultdict(list)

    for fname in glob('%s/*.py' % algorithms_dir):
        module_name = os.path.basename(fname).replace('.py', '')
        if module_name == '__init__': continue
        module = __import__(module_template % module_name, fromlist=fromlist)

        if hasattr(module, 'grupo'):
            group_name = getattr(module, 'grupo')
        else:
            group_name = module_name

        for member_name, member in inspect.getmembers(module):
            if type(member).__name__ == presentar.__name__:
                res[group_name].append((member_name, member))

    return dict(res)
    

