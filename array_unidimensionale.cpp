
// Andres Coronado [Unige]
// Studio algoritmi relativi all'implementazione di liste con array


#include <iostream>
using namespace std;

//Costante globale grandezza dell'array, modificabile qua:
const int size = 10;

//variabili utilizzate a scopo di studio del costo degli algoritmi:
int cicli = 0;
int scambi = 0;
int confronti = 0;

/* Dichiaro una struttura lista costituita da un array 
grande come size (la variabile globale) e un valore occupied
che sta a indicare quanti elementi di questo array sono utilizzati */
struct lista{
	int array[size];
	int occupied=0;
};

//prototipi di moduli e funzioni
void menu(); 					// il menu
void stampaLista(lista& a); 	// mostra la lista
bool randomArray(lista& a);		// random array
bool isFull(lista& a); 			// se e` vero significa che l'array e` pieno
bool append(lista& a, int val); // inserimento in coda
bool insert(lista& a, int& pos, int& val); // inserimento in posizione
bool trim(lista& a); 			// elimina ultimo elemento
bool del(lista& a, int pos);	// elimina elemento nella posizione pos
bool swap(lista& a, int pos1, int pos2);	// elimina elemento nella posizione pos
bool selectionSort(lista& a);   //ordina l'array con selection sort
bool insertionSort(lista& a); 	//ordina l'array con insertion sort
bool bubbleSort(lista& a); 		//ordina l'array con bubble sort
int ricercaSequenziale(lista& a, int& key); //ricerca sequenziale
int ricercaBinaria(lista& a, int& key); 	//ricerca binaria in un array ordinato

/* ritorna la posizione del valore minimo valore nell'array a partire da 
array[index] fino a array[occupied-1], utile per selection sort */
int minIndex(lista& a,int index); 

/* MAIN */
int main(){
	menu();
}
void menu(){//launcher delle varie funzioni 
	lista a;
	int scelta = 100;
	while (scelta != 0 ){ // main menu loop
	cout << "\t***Benvenuto***\nQuesto programma esegue operazioni base su una lista di \n[" << size << "] elementi ed e` stato creato da Andres Coronado.\n[per superare l'esame di Introduzione alla programmazione {UniGe}]\n";
	cout << "\n\nAl momento ci sono [ "<< a.occupied <<" ] " << "elementi occupati nell'array\n\n";
	cout << "[1]\tInizializza l'array con numeri random\n";
	cout << "[2]\tVisualizza la lista\n";
	cout << "[3]\tInserisci in coda\n";
	cout << "[4]\tInserisci in posizione\n";
	cout << "[5]\tElimina in coda\n";
	cout << "[6]\tElimina in posizione\n";
	cout << "[7]\tScambia 2 elementi\n";
	cout << "[8]\tOrdina con Selection Sort\n";
	cout << "[9]\tOrdina con Insertion Sort\n";
	cout << "[10]\tOrdina con Bubble Sort\n";
	cout << "[11]\tRicerca Sequenziale\n";
	cout << "[12]\tRicerca Binaria\n";
	cout << "\n\n\n[0]\tEsci\n";
	cout << "\n\n\nDigita il numero desiderato seguito dal tasto Enter : ";
	cin >> scelta;
	switch (scelta){
		int value;
		int posiz2;
		int posiz;
		int key;
		case 1:
			randomArray(a);
			stampaLista(a);
			break;
		
		case 3:
			cout << " Inserisci il valore da inserire seguito da <return>:";
			cin >> value;
			append(a,value);
			cout << "\n\n";
			stampaLista(a);
			
			break;

		case 2:
			cout << "\n\n";
			stampaLista(a);
			break;

		case 4:
			cout << "[AGGIUNGI] Inserisci la posizione nell'array seguito da <return> :";
			cin >> posiz;
			cout << "Inserisci il valore da inserire seguito da <return> :";
			cin >> value;
			if (!insert(a,posiz,value)) cout << "\n**************IMPOSSIBILE************\n";
			cout << "\n\n";
			stampaLista(a);
			break;

		case 5:
			trim(a);
			cout << "\n\n";
			stampaLista(a);
			break;

		case 6:
			cout << "[ELIMINA] Inserisci la posizione nell'array seguito da <return> :";
			cin >> posiz;
			del(a,posiz);
			stampaLista(a);
			break;

		case 7:
			cout << "\n\n";
			stampaLista(a);
			cout << "\n\n";
			cout << "[SCAMBIA] Inserisci la prima posizione nell'array seguito da <return> :";
			cin >> posiz;
			cout << "[SCAMBIA] Inserisci la seconda posizione nell'array seguito da <return> :";
			cin >> posiz2;
			swap(a, posiz,posiz2);
			cout << "\n\n";
			stampaLista(a);
			break;

		case 8:
			cout << "\n\nSto ordinando con selection Sort...";
			selectionSort(a);
			cout << "\n\n";
			stampaLista(a);
			break;

		case 9:
			cout << "\n\nSto ordinando con insertion Sort...";
			insertionSort(a);
			cout << "\n\n";
			stampaLista(a);
			break;

		case 10:
			cout << "\n\nSto ordinando con bubble Sort...";
			bubbleSort(a);
			cout << "\n\n";
			stampaLista(a);
			break;

		case 11:
			cout << "\n\n\n[RICERCA SEQUENZIALE] Inserisci la chiave da cercare seuita <return> : ";
			cin >> key;
			posiz = ricercaSequenziale(a,key); 
			if (posiz >= 0)
			cout << "[RICERCA SEQUENZIALE] la chiave [" << key << "] si trova alla posizione [" << posiz <<"]\n";
			else cout << "[RICERCA SEQUENZIALE] la chiave [" << key << "] non si trova nell'array\n";
			cout << "[RICERCA SEQUENZIALE] la ricerca ha impiegato [" << confronti << "] confronti\n\n\n";
			break;

		case 12:
			cout << "\n\n\n[RICERCA BINARIA] Inserisci la chiave da cercare seuita <return> : ";
			cin >> key;
			posiz = ricercaBinaria(a,key); 
			if (posiz >= 0)
			cout << "[RICERCA BINARIA] la chiave [" << key << "] si trova alla posizione [" << posiz <<"]\n";
			else cout << "[RICERCA BINARIA] la chiave [" << key << "] non si trova nell'array\n";
			cout << "[RICERCA BINARIA] la ricerca ha impiegato [" << confronti << "] confronti\n\n\n";
			break;
		}
		//cout << "\033[2J\033[1;1H";
	} 
}

bool randomArray(lista& a){// random array
	//auto random_integer = uni(rng);
	a.occupied=0;
	for(int i=0;i<size;++i){
		a.array[i]=rand() % 100;
		++a.occupied;
	}
	return true; 
}

bool swap(lista& a, int pos1, int pos2){//scambia di posizione due elementi
	int aux; // variabile temporanea di supporto allo scambio
	if (((pos1<a.occupied)&&(pos1>=0))&&((pos2<a.occupied)&&(pos2>=0))&&(pos1!=pos2)){
		aux=a.array[pos1];
		a.array[pos1] = a.array[pos2];
		a.array[pos2] = aux;
		scambi+=1;
		return true;
	}
	return false;
}

bool trim(lista& a){// elimina ultimo elemento
	if (a.occupied == 0) return false;
	--a.occupied;
	return true; 
}

bool del(lista& a, int pos){ // elimina elemento in pos
	if ((pos<a.occupied)&&(pos>=0)){
		for (int i=pos;i<a.occupied+1;i++){
			a.array[i]=a.array[i+1];
		}
		--a.occupied;
		return true;
	}
	if (pos == a.occupied){
		trim(a);
		return true;	
	}
	return false; 
}

bool isFull(lista& a){// array pieno? 

	return (a.occupied==size); 
}

bool append(lista& a, int val){//aggiunge in coda
	if (isFull(a)) // non c'è piu' posto
 		return false;
	a.array[a.occupied] = val;
	++a.occupied;
	return true;
}

bool insert(lista& a, int& pos, int& val){//inserisce in pos
	if ((pos > a.occupied)||(pos<0)){
		return	false;
	}
	if (isFull(a)){
		return	false;
	}
	if (pos == a.occupied) {
	 append(a, val);
	 	return true;
	}
	for(int i=a.occupied;i > pos;i--){
		a.array[i]=a.array[i-1];
	}
	++a.occupied;
	a.array[pos]=val;
	return true ;
}

void stampaLista(lista& a) {//stampa la lista su schermo
	char pause;
	//cout << "\033[2J\033[1;1H";
	for(int i = 0;i < a.occupied;++i){
	cout << "[ELEMENTO : "<< i << "][ VALORE : "<< a.array[i] << "]\n";
	}
	cout << "\n\nL'ultimo ordinamento ha prodotto : ["<< cicli << " cicli ] ["<< scambi << " scambi]\n\n";
	//cout << "premi un tasto qualsiasi seguito da <return> per continuare... " << &endl;
 	//cin >> pause;
}

int minIndex(lista& a,int index){// trova il minimo in un range dell'array
	int minVal=a.array[index];
	int minPos=index;
	for(int i=minPos;i<a.occupied;i++){
		++cicli;
		if (a.array[i]<minVal){
			minVal=a.array[i];
			minPos=i;
		}
	}
	return minPos;
}

bool selectionSort(lista& a){ // selection sort, algoritmo adattivo //migliorabile!
	cicli=0;
	scambi=0;
	for(int j=0;j<a.occupied;++j){
		swap(a.array[j],a.array[minIndex(a,j)]);
		++cicli;
	}
	return true;
}
bool insertionSort(lista& a){ // insertion sort conviene se gli elementi sono quasi ordinati
	cicli=0;
	scambi=0;
	int key = 0;
	int sorted = 0;
	for(int i=0;i<a.occupied;i++){
		sorted = i;
		while(sorted > 0 && a.array[sorted] < a.array[sorted-1]){
			key = a.array[sorted];
			a.array[sorted]=a.array[sorted-1];
			a.array[sorted-1]=key;
			sorted--;
			cicli++;
			scambi+=1;
		}
		cicli++;
	}
	return true;	
}

bool bubbleSort(lista& a){// bubble sort
	cicli=0;
	scambi=0;
	bool swapped=false;
	for (int i;i<a.occupied;i++){
		swapped= false;
		for(int j=0;j<size-i-1;j++){
			if (a.array[j]>a.array[j+1]){
				swap(a,j,j+1);
				++scambi;
				swapped = true;
			} 
			++cicli;
			if (swapped=false) return true;
		}
		++cicli;
	}
}

int ricercaSequenziale(lista& a,int& key){//ricerca sequenziale
	confronti = 0;
	for(int i=0;i<a.occupied;i++){
		if (a.array[i] == key){
			return i;
		}
		++confronti;
	}
	return -1;
} 
int ricercaBinaria(lista& a,int& key){//ricerca binaria
	confronti = 0;
	int first=0;
	int last=a.occupied-1;
	int mid;
	bool found=false;
	if (key==a.array[first]){
		confronti++;
		return first;
	}
	if (key==a.array[last]){
		confronti++;
		return last;
	}

	while((first <= last)&&(!found)){
		mid=(first+last)/2;
		if (a.array[mid]==key){
			found=true;
			}
			else if (a.array[mid]>key){
				last=mid-1;
				}
				else first=mid+1;

		confronti+=1;
	}
	if (found==true) return mid;
	return -1;
}

