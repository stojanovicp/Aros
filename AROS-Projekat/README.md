# AROS-projekat
Ime: Petar Stojanović

Tema projekta u okviru kursa Arhitektura Računara i Operativni Sistemi odnosi se na izradu aplikacije za međusobnu razmenu tekstualnih poruka između različitih procesa koristeći named pipe (imenovane cijevi) i semafore.

Kako da pokrenete program:

    Otvorite dva terminala.

    U terminalima se premestite u direktorijum gde se nalaze programski kodovi korišćenjem komande cd.

    Kompajlirajte izvorne kodove koristeći sledeće komande:
        gcc sender.c -o sender -lpthread
        gcc receiver.c -o receiver -lpthread

    Pokrenite programe u terminalima pomoću sledećih komandi:
        ./sender
        ./receiver