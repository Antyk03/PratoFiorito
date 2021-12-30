#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>
using namespace std;
const char E = 130;
const char aAS = 201; // angolo in alto a sinistra
const char aAD = 187; // angolo in alto a destra 
const char aBS = 200; // angolo in basso a sinistra
const char aBD = 188; // angolo in basso a destra
const char verticale = 186; // colonna
const char orizziontale = 205; // riga
const char casella = 127;
const char bomba = 15;
const char faccina = 1;
const char segnato = 5;
const int MAX = 20;
struct mappa {
    int valore;
    bool scoperta;
};
struct posizione {
    int x;
    int y;
};
struct tabella {
    int indicatoreX;
    int indicatoreY;
    mappa matrice[MAX][MAX];  
};
void azzeramentoTabella(tabella& t) {
    for (int i = 0; i < t.indicatoreX; i++) {
        for (int j = 0; j < t.indicatoreY; j++) {
            t.matrice[i][j].valore = 0;
            t.matrice[i][j].scoperta = false;
        }
    }
}
void convalidaIntero(int& intero, int min, int max, string frase) {
	cout << frase;
	cin >> intero;
	while (intero < min || intero > max) {
		cout << "Errore " << endl << frase;
		cin >> intero;
	}
}
int menu() {
    int scelta;
    cout << aAS << setw(28) << setfill(orizziontale)<< aAD << endl;
    cout << verticale << "Inserisci la tua scelta :  " << verticale << endl;
	cout << verticale << setw(28) << setfill(' ')<< verticale << endl;
    cout << verticale << setw(28) << setfill(' ')<< verticale << endl;
    cout << verticale << "1. Inizia il gioco.        " << verticale << endl;
    cout << verticale << "2. Spiega le regole.       " << verticale << endl;
    cout << verticale << "0. Esci.                   " << verticale << endl;
    cout << aBS << setw(28) << setfill(orizziontale)<< aBD << endl;
    convalidaIntero(scelta, 0, 2, "Inserisci numero: ");
    system ("cls");
    return scelta;
}
void scopriVicine(tabella& t, posizione input) {
    int cont = 0;
    int maxI = 2;
    int maxJ = 2;
    int minI = -1;
    int minJ = -1;
    if (input.x == 0) {
        minI = 0;
    } else if (input.x == t.indicatoreX) {
        maxI = 1;
    }
    if (input.y == 0) {
        minJ = 0;
    }
    else if (input.x == t.indicatoreX) {
        maxJ = 1;
    }
    for (int i = minI; i < maxI; i++) {
        for (int j = minJ; j < maxJ; j++) {
            if (t.matrice[input.x+i][input.y+j].valore != -1) {
                t.matrice[input.x+i][input.y+j].scoperta = true; 
            }
        }
    }
}
void stampaTabella(tabella t) {
    cout << "\n   ";
    for (int o = 1; o < t.indicatoreY + 1; o++) {
        cout << o << " ";
    }
    cout << endl;
    for (int i = 0; i < t.indicatoreX; i++) {
        if (i > 8) {
            cout << i + 1 << " ";
        } else {
            cout << i + 1 << "  ";
        }
        for (int j = 0; j < t.indicatoreY; j++) {
            if (t.matrice[i][j].scoperta == true) {
                if (t.matrice[i][j].valore == -1) {
                    cout << bomba << " ";
                } else {
                    cout << t.matrice[i][j].valore << " ";
                }
            } else {
                if (t.matrice[i][j].valore > 8) {
                    cout << segnato << " ";
                } else {
                    cout << casella << " ";
                }
            } if (j > 8) {
               cout << " ";
            }
        }
        cout << endl;
    }
    cout << "\n\n";  
}
void stampaTabellaPosizione(tabella t, posizione p) {
    cout << "\n   ";
    for (int o = 1; o < t.indicatoreY + 1; o++) {
        cout << o << " ";
    }
    cout << endl;
    for (int i = 0; i < t.indicatoreX; i++) {
        if (i > 8) {
            cout << i + 1 << " ";
        } else {
            cout << i + 1 << "  ";
        }
        for (int j = 0; j < t.indicatoreY; j++) {
            if (t.matrice[i][j].scoperta == true) {
                if (t.matrice[i][j].valore == -1) {
                    cout << bomba << " ";
                } else {
                    cout << t.matrice[i][j].valore << " ";
                }
            } else {
                if (i == p.x && j == p.y) {
                    cout << faccina << " ";
                } else if (t.matrice[i][j].valore > 8) {
                    cout << segnato << " ";
                } else {
                    cout << casella << " ";
                }
            } if (j > 8) {
               cout << " ";
            }
        }
        cout << endl;
    }
    cout << "\n\n";
}
bool verificaRisposta(string frase) {
    string risposta;
    int dimRis;
    cout << frase << endl;
    cin >> risposta;
    if (risposta == "1") {
        return true;
    } else {
        dimRis = risposta.size();
        for (int i = 0; i < dimRis; i++) {
            risposta[i] = toupper(risposta[i]);
        }
        if (risposta == "SI" || risposta == "S") {
            return true;
        }
    }
    return false;
}
int numeroMine (tabella t) {
    return (t.indicatoreX * t.indicatoreY) / ((t.indicatoreX + t.indicatoreY)/2);
}
void dimensioniTabella(tabella& t) {
    bool vero = false;
    while (!vero) {
        cout << "Inserisci le dimensioni della tabella: \n" << endl;
        convalidaIntero(t.indicatoreX, 3, MAX, "Inserisci le righe della tabella: " );
        convalidaIntero(t.indicatoreY, 3, MAX, "Inserisci le colonne della tabella: ");
        cout << endl << endl;
        stampaTabella(t);
        cout << "Le mine in questa tabella sono: " << numeroMine(t) << endl;
        vero = verificaRisposta("Le dimensioni sono corrette? (si / no)");
    }
}
void creazioneMine(tabella& t, posizione m[MAX]) {
    int mine = numeroMine(t);
    for (int i = 0; i < mine; i++) {
        m[i].x = rand() % t.indicatoreX;
        m[i].y = rand() % t.indicatoreY;
        if (t.matrice[m[i].x][m[i].y].valore == 0) {
            t.matrice[m[i].x][m[i].y].valore = -1;
        } else {
            i--;
        }
    }
}
int contaSegnati(tabella t) {
    int cont = 0;
    for (int i = 0; i < t.indicatoreX; i++) {
        for (int j = 0; j < t.indicatoreY; j++) {
            if (t.matrice[i][j].valore > 8) {
                cont++;
            }
        }
    } 
    return cont;
}
void scoprire(tabella& t, posizione input, bool& scelta) {
    t.matrice[input.x][input.y].scoperta = true;
    if (t.matrice[input.x][input.y].valore == 0) {
        scopriVicine(t, input);
    }
    scelta = false;
}
void segnare(tabella& t, posizione input, bool& scelta) {
    if (contaSegnati(t) == numeroMine(t)) {
        cout << "Impossibile segnare un numero di caselle maggiore delle mine! " << endl;
        scelta = false;
        return;
    } else if (t.matrice[input.x][input.y].scoperta) {
        cout <<"Errore la casella " << E <<" scoperta, selezionare un'altra casella " << endl;
        scelta = false;
        return; 
    }
    t.matrice[input.x][input.y].valore += 10;
    scelta = false;
}
void desegnare(tabella& t, posizione input, bool& scelta) {
    if (t.matrice[input.x][input.y].valore < 8) {
        cout <<"Errore la casella non " << E <<" segnata, selezionare un'altra casella " << endl;
        scelta = false;
        return; 
    }
    t.matrice[input.x][input.y].valore -= 10;
    scelta = false;
}
void sceltaUtente(tabella& t, posizione& input) {
    bool scelta = true;
    bool vero = false;
    while (!vero) {
        stampaTabella(t);
        convalidaIntero(input.y, 1, t.indicatoreY, "Inserisci la x della posizione scelta: ");
        input.y--;
        convalidaIntero(input.x, 1, t.indicatoreX, "Inserisci la y della posizione scelta: ");
        input.x--;
        if (t.matrice[input.x][input.y].scoperta) {
            cout << "Casella scoperta" << endl; 
            continue;
        }
        cout <<"\nLe posizioni scelte sono: " << input.x + 1<<" " << input.y + 1<< endl;
        stampaTabellaPosizione(t, input);
        vero = true;
    }
    while (scelta) {
        cout << "Vuoi scoprire (1), segnare una mina (2) o desegnare una mina (3)? " << endl;
        string risposta;
        int dimRis;
        cin >> risposta;
        if (risposta == "1") {
            scoprire(t, input, scelta);
        } else if (risposta == "2") {
            segnare(t, input, scelta);
        } else if (risposta == "3") {
            desegnare (t, input, scelta);
        } else {
            dimRis = risposta.size();
            for (int i = 0; i < dimRis; i++) {
                risposta[i] = toupper(risposta[i]);
            }
            if (risposta == "SCOPRIRE") {
                scoprire(t, input, scelta);
            } else if (risposta == "SEGNARE") {
                segnare(t, input, scelta);
            } else if (risposta == "DESEGNARE") {
                desegnare (t, input, scelta);
            }
        }
    }
}
bool verificaMina(posizione input, tabella t) {
    if (input.x == -1) {
        return false;
    }
    for (int i = 0; i < MAX; i++) {
        if(t.matrice[input.x][input.y].valore == -1 && t.matrice[input.x][input.y].scoperta == true) {
            return true;
        }
    }
    return false;
}
int contaIntorno(tabella t, int pi, int pj) {
    int cont = 0;
    int maxI = 2;
    int maxJ = 2;
    int minI = -1;
    int minJ = -1;
    if (pi == 0) {
        minI = 0;
    } else if (pi == t.indicatoreX) {
        maxI = 1;
    }
    if (pj == 0) {
        minJ = 0;
    }
    else if (pi == t.indicatoreX) {
        maxJ = 1;
    }
    for (int i = minI; i < maxI; i++) {
        for (int j = minJ; j < maxJ; j++) {
            if (t.matrice[pi+i][pj+j].valore == -1) {
                cont++;
            }
        }
    }
    return cont;
}

void controlloBombeVicine(tabella& t, posizione m) {
    for (int i = 0; i < t.indicatoreX; i++) {
        for (int j = 0; j < t.indicatoreY; j++) {
            if (t.matrice[i][j].valore != -1) {
                t.matrice[i][j].valore = contaIntorno(t, i, j);
            }
        }
    }
}
int contaScoperti (tabella t) {
    int cont = 0;
    for (int i = 0; i < t.indicatoreX; i++) {
        for (int j = 0; j < t.indicatoreY; j++) {
            if (t.matrice[i][j].scoperta) {
                cont++;
            }
        }
    } 
    return cont;
}
bool tuttiPositivi(tabella t) {
    for (int i = 0; i < t.indicatoreX; i++) {
        for (int j = 0; j < t.indicatoreY; j++) {
            if (t.matrice[i][j].valore < 0) {
                return false;
            }
        }
    }
    return true;
}
bool controlloVittoria(tabella t) {
    return (contaScoperti(t) == numeroMine(t) || tuttiPositivi(t));
}
void partita (tabella t, posizione input, posizione mine[MAX]) {
    dimensioniTabella(t);
    creazioneMine(t, mine); 
    controlloBombeVicine(t, input);
    input.x = -1;
    input.y = -1;
    while(!verificaMina(input, t)) {
        sceltaUtente(t,input);
        if (controlloVittoria(t)) {

        }
        stampaTabella(t);
    }
    cout << "PARTITA FINITA " << endl;
    cout <<"\n\n HAI PERSO !\n\n" << endl;
    system("pause");
}
void regolamento() {
    cout << aAS << setw(88) << setfill(orizziontale)<< aAD << endl;
    cout << verticale << "REGOLAMENTO DI PRATO FIORITO                                                           " << verticale << endl;
    cout << aBS << setw(88) << setfill(orizziontale)<< aBD << endl;
    cout << aAS << setw(88) << setfill(orizziontale)<< aAD << endl;
    cout << verticale << "Lo scopo principale del gioco " << E <<" non prendere bombe.                                    " << verticale << endl;
    cout << verticale << "inserendo 1 nel menu potrai scegliere la dimensione della mappa,                       " << verticale << endl;
    cout << verticale << "successivamente dovrai inserire le coordinate di una casella nella mappa               " << verticale << endl;
    cout << verticale << "e scegliere una delle opzioni:                                                         " << verticale << endl;
    cout << verticale << "- Scopri casella                                                                       " << verticale << endl;
    cout << verticale << "- Segna come mina                                                                      " << verticale << endl;
    cout << verticale << "- Desegna                                                                              " << verticale << endl;
    cout << verticale << "scoprendo una casella " << verticale << casella << " potresti perdere se becchi una mina,                          " << verticale << endl;
    cout << verticale << "quindi fa attenzione!                                                                  " << verticale << endl;
    cout << verticale << "scoprendo tutte le caselle, non scoprendo nemmeno una mina vinci                       " << verticale << endl;
    cout << verticale << "le caselle scoperte si trasformano in numeri in base a quante mine hanno vicino        " << verticale << endl;
    cout << verticale << "per rendere il gioco piu' interessante le caselle con numero 0 rivelano                " << verticale << endl;
    cout << verticale << "automaticamente le caselle vicine, ma devi prima trovarne una !                        " << verticale << endl;
    cout << verticale << "segnalare le mine non ti fa perdere o vincere a meno che segnali tutte le mine!        " << verticale << endl;
    cout << verticale << "ovviamente puoi segnalare tante caselle pari al numero di mine                         " << verticale << endl;
    cout << verticale << "le segnalazioni appaiono con il simbolo "<< segnato << "                                              " << verticale << endl;
    cout << verticale << "hai sbagliato a mettere una segnalazione non preoccuparti puoi desegnare una casella   " << verticale << endl;
    cout << verticale << "la che desegni torna ad essere "<< casella << "                                                       "<< verticale << endl;
    cout << verticale << "Simboli che possono essere utili:                                                      " << verticale << endl;
    cout << verticale << casella <<" - casella                                                                            " << verticale << endl;
    cout << verticale << bomba << " - mina                                                                               " << verticale << endl;
    cout << verticale << segnato << " - casella segnata                                                                    " << verticale << endl;
    cout << aBS << setw(88) << setfill(orizziontale)<< aBD << endl;
    system("pause");
}
int main() {
    srand(time(NULL));
    int scelta;
    tabella t;
    posizione mine[MAX];
    posizione input;
    t.indicatoreX = MAX;
    t.indicatoreY = MAX;
    while (true) {
        azzeramentoTabella(t);
        system("cls");
    	scelta = menu();
    	if (scelta == 0) {
    		break;
    	} else if (scelta == 1) {
            partita(t, input, mine);
    	} else if (scelta == 2) {
    		regolamento();
    	}
    }
}