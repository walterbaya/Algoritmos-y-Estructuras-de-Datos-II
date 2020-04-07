#-*- coding: utf8 -*-
import matplotlib.pyplot as plt

plt.style.use('ggplot')

# Grafico gauss
with open('gauss.txt', 'r') as f:
    s = [int(l) for l in f] 
    plt.figure()
    plt.hist(s, bins=20)
    plt.title('Claves gaussianas')
    plt.savefig('gauss.pdf')


# Grafico uniforme
with open('uniforme.txt', 'r') as f:
    s = [int(l) for l in f] 
    plt.figure()
    plt.hist(s, bins=20)
    plt.title('Claves uniformes')
    plt.savefig('uniforme.pdf')


# Grafico libretas
with open('libretas.txt', 'r') as f:
    s = [int(l) for l in f] 
    plt.figure()
    plt.hist(s, bins=20)
    plt.title('Claves libretas como ints')
    plt.savefig('libretas.pdf')

    plt.figure()
    plt.hist([int(str(x)[-2:]) for x in s])
    plt.title(u'Distribución de números de las libretas')
    plt.savefig('libretas_nums.pdf')
   
    plt.figure()
    plt.hist([int(str(x)[:-2]) for x in s])
    plt.title(u'Distribución de años de las libretas')
    plt.savefig('libretas_años.pdf')
