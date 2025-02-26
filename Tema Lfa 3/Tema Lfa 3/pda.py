from FileHandler import FileHandler
import time

class PDA:
    def __init__(self):
        self.stack = []

    def compute(self, inputString, parsedLines):
        #Retrieve all information
        inputString += 'e'
        initStackSymbol = parsedLines['stiva_initiala']
        self.stack.append(initStackSymbol)
        finalStates = parsedLines['stari_finale']
        initialState = parsedLines['stare_initiala']
        stackSymbols = parsedLines['simboluri_stiva']
        productions = parsedLines['productii']

        currentStackSymbol = initStackSymbol
        currentState = initialState

        print('Stare\tIntrare\tStiva\tMutare')
        print('{}\t {}\t {}\t ({}, {})'.format(currentState, '_', 'Z', currentStackSymbol, self.stack))
        for char in inputString:
            #print('Current TOS', currentStackSymbol)
            for production in productions:
                if ((production[0] == currentState) and (production[1] == char) and (production[2] == currentStackSymbol)):
                    currentState = production[3]
                    if(len(production[4]) == 2):
                        self.stack.append(char)
                    elif(len(production[4]) == 3):
                        self.stack.append(char)
                        self.stack.append(char)
                    elif ((production[4] == 'e') and (len(self.stack) != 1)):
                        self.stack.pop()
                        break
            previousStackSymbol = currentStackSymbol
            currentStackSymbol = self.stack[len(self.stack)-1]
            print('{}\t {}\t {}\t ({}, {})'.format(currentState, char, previousStackSymbol, currentStackSymbol, self.stack))
            #time.sleep(2)

        if(currentState in finalStates):
            print('sir acceptat de PDA.')
        else:
            print('sir respins de PDA.')

def main():
    fh = FileHandler()
    pda = PDA()
    automataFilePath = input('Introduceti calea fisierului pentru automata: ')
    lines = fh.readFile(automataFilePath)
    print('Citire fisier automata')
    #time.sleep(2)
    print('Fisier automata citit cu succes')
    #time.sleep(2)
    inputString = input('Introduceti sirul de intrare: ')
    inputString = inputString.rstrip()
    print('Se incarca detalii din fisierul automata: ')
    #time.sleep(3)
    parsedLines = fh.parseFile(lines)
    print('Stari: ', parsedLines['stari'])
    print('Simboluri de intrare: ', parsedLines['simboluri_intrare'])
    print('Simboluri de stiva: ', parsedLines['simboluri_stiva'])
    print('Stare initiala: ', parsedLines['stare_initiala'])
    print('Simbol initial de stiva: ', parsedLines['stiva_initiala'])
    print('Stari finale: ', parsedLines['stari_finale'])
    print('Lista de productii:')
    for production in parsedLines['productii']:
        print('\t', production)
    #time.sleep(2)
    pda.compute(inputString, parsedLines)

if __name__ == '__main__':
    main()