import os

class FileHandler:

    def __init__(self):
        pass

    def readFile(self, file):
        linii = []
        if(os.path.isfile(file)):
            try:
                with open(file) as file:
                    linii = [linie.rstrip() for linie in file]
            except IOError as e:
                print("Fisierul nu a putut fi deschis.")
                exit(0)
        else:
            print('{} :Fisierul nu a fost gasit in calea specificata.'.format(caleFisier))
            exit(0)
        return linii

    def parseFile(self, linii):
        ''' Linia 1: Stari Totale
            Linia 2: Simboluri de Cuvinte de Intrare
            Linia 3: Simboluri de Stiva
            Linia 4: Simbol Initial de Stare
            Linia 5: Simbol Initial de Stiva
            Linia 6: Lista Stari Finale
            Linia 7 si urmatoarele: Productii in forma
                    (Stare Curenta, Simbol de Intrare Curent, Varful Curent al Stivei, Starea Urmatoare, Simbol Operatie Impins/Extras)
            '''
        stari = linii[0].rstrip().split()
        simboluri_intrare = linii[1].rstrip().split()
        simboluri_stiva = linii[2].rstrip().split()
        stare_initiala = linii[3][0]
        stiva_initiala = linii[4][0]
        stari_finale = linii[5].rstrip().split()
        productii = linii[6:]
        for i in range(len(productii)):
            productii[i] = productii[i].rstrip().split()

        linii_parsate = {'stari': stari,
                         'simboluri_intrare': simboluri_intrare,
                         'simboluri_stiva': simboluri_stiva,
                         'stare_initiala': stare_initiala,
                         'stiva_initiala': stiva_initiala,
                         'stari_finale': stari_finale,
                         'productii': productii}
        return linii_parsate