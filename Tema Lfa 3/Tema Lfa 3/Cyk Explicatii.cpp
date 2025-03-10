Structura programului: Cum am gandit

1. Definirea funcțiilor de verificare:
   - Funcțiile `checkNTR`, `checkTR`, `checkPR` și `checkEle` sunt definite pentru a verifica dacă un simbol este un simbol de neterminal, un simbol de terminal, o regulă de producție validă și pentru a verifica dacă un anumit simbol există într-un șir.

2. Introducerea datelor de intrare:
   - Programul începe prin a solicita introducerea datelor de intrare pentru a defini gramatica de generare:
     - Numărul de reguli de producție și numărul de simboluri de neterminal sunt citite de la tastatură.
     - Apoi, utilizatorul introduce simbolurile de neterminal și numărul de producții pentru fiecare dintre acestea.
     - În final, utilizatorul introduce regulile de producție.

3. Verificare validitate date de intrare:
   - După ce toate datele de intrare sunt citite, acestea sunt verificate pentru a se asigura că sunt valide conform specificațiilor gramaticii definite.
   - Funcțiile de verificare sunt folosite pentru a asigura că simbolurile de neterminal sunt valide și că regulile de producție sunt scrise într-un format corect.

4. Citirea șirului de intrare din fișier:
   - Un șir de intrare este citit din fișierul `input.txt`.
   - Lungimea șirului este determinată pentru a inițializa tabla de derivare.

5. Inițializarea tablei de derivare:
   - Se inițializează tabla de derivare cu dimensiunea necesară pentru a stoca informațiile pe parcursul procesării.

6. Construirea tabelei de derivare:
   - Se construiește tabela de derivare conform algoritmului de derivare pentru gramatici context-libere.
   - Fiecare celulă a tablei de derivare este completată conform regulilor de producție și simbolurilor de neterminal citite anterior.
   - Acest proces are loc în două etape: o etapă pentru calcularea producțiilor pentru șirurile de lungime 1 și o etapă pentru calcularea producțiilor pentru șiruri de lungime mai mare.

7. Afișarea tablei de derivare:
   - După completarea tabelei de derivare, aceasta este afișată pentru a permite utilizatorului să urmărească procesul de derivare.

8. Verificarea dacă șirul este acceptat sau respins:
   - La final, se verifică dacă simbolul de start `S` este prezent în celula corespunzătoare primului și ultimului caracter al șirului.
   - Dacă este prezent, înseamnă că șirul este acceptat de gramatică; altfel, este respins.


Explicatii subprograme + program principal - Ce face fiecare

i SUBPROGRAME
1. Funcțiile de verificare (`checkNTR`, `checkTR`, `checkPR`, `checkEle`):

- checkNTR(char ch): Această funcție verifică dacă caracterul `ch` este un simbol de neterminal valid. Verifică dacă `ch` se găsește în vectorul `big`, care conține toate simbolurile de neterminal permise.

- checkTR(char ch): Similar cu `checkNTR`, această funcție verifică dacă caracterul `ch` este un simbol de terminal valid. Verifică dacă `ch` se găsește în vectorul `small`, care conține toate simbolurile de terminal permise.

- checkPR(const std::string& ch): Această funcție verifică dacă șirul `ch` reprezintă o regulă de producție validă conform unei gramatici context-libere în formă normală Chomsky. Verifică dacă șirul are o lungime validă (1 sau 2) și dacă simbolurile sunt fie toate terminale, fie două neterminale valide.

- checkEle(const std::string& El, char ch): Această funcție verifică dacă caracterul `ch` este prezent în șirul `El`.

II. Funcția principală `main()`:

1. Inițializarea datelor de intrare:

- Se afișează un mesaj de demo și se solicită introducerea datelor de intrare pentru definirea gramaticii.
- Numărul de reguli de producție și numărul de simboluri de neterminal sunt citite de la tastatură.
- Se cere introducerea simbolurilor de neterminal și a numărului de producții pentru fiecare dintre acestea.
- Utilizatorul introduce regulile de producție.

#### Verificarea validității datelor de intrare:

- Se verifică dacă simbolurile introduse sunt valide conform specificațiilor gramaticii.
- Se utilizează funcțiile de verificare `checkNTR`, `checkTR` și `checkPR` pentru a asigura validitatea datelor introduse de utilizator.

Citirea șirului de intrare din fișier:

- Se deschide fișierul `input.txt` și se citeste șirul de intrare.
- Se inițializează variabilele și tabelele necesare pentru procesarea ulterioară a șirului.

Construirea și afișarea tabelei de derivare:

- Se construiește tabela de derivare pentru șirul de intrare folosind regulile de producție și simbolurile de neterminal.
- Fiecare celulă a tablei este completată conform regulilor de producție și a simbolurilor de neterminal.
- După construirea tablei de derivare, aceasta este afișată pentru a permite utilizatorului să urmărească procesul de derivare.

Verificarea dacă șirul este acceptat sau respins:

- Se verifică dacă simbolul de start `S` este prezent în celula corespunzătoare primului și ultimului caracter al șirului.
- Dacă simbolul de start este prezent, șirul este acceptat; în caz contrar, este respins.

