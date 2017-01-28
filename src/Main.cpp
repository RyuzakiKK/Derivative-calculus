/*************************************************************************************\
*	Elaborato_ASD 
*
*	Programmers ---> Eugenio - Mauro - Ludovico
*
*	Main.cpp
\*************************************************************************************/


#include <Functions.h>


int main(){
	string input_string;
	string output_string;
	string input_file;
	string output_file;
	int menu_choice = 0;
	int flagError = 1;
															
	cout << "===============================================================================\n";
	cout << "Elaborato di Algoritmi e Strutture Dati\nCALCOLO DELLA DERIVATA DI UNA FUNZIONE AD UNA VARIABILE\nProgrammatori: Eugenio Severi - Mauro Valmori - Ludovico De Nittis\n";
	cout << "===============================================================================\n\n";
	cout << "Selezionare un metodo di acquisizione della funzione:\n\t1) File 'input.txt' nella cartella dell'eseguibile\n\t2) File specificato dall'utente\n\t (il percorso deve contenere / al posto delle \\,ad es. C:/funzione.txt)\n\t3) Inserimento da tastiera\n#: ";
	 

	getNumber(&menu_choice);
										/* Ciclo che contolla eventuali errori nella fase di input / elaborazione */
	while (flagError){
		cout << "\n";
		switch(menu_choice) { // Gestione del primo menù del programma
		case 1: // Viene aperto il file di "default" nella cartella dell'eseguibile
			if(read_file(input_string, "input.txt")) { // Legge il file input.txt e lo salva sulla stringa input_string, inoltre controlla un'eventuale presenza di errori
				cout << "Impossibile aprire il file 'input.txt'\n";
				system("pause>nul");
				return 1;
			}
			if(derivative(input_string, output_string)) { // Esegue e controlla lo stato della funzione che calcola la derivata
				cout << "Impossibile derivare, possibile errore nel file di input\n";
				system("pause>nul");
				return 1;
			}
			flagError = 0;
			break;
		case 2: // Viene aperto il file specificato dall'utente
			cout << "Inserire il percorso del file: ";
			getline(cin, input_file);
			if(read_file(input_string, input_file)) { // Legge il file input.txt e lo salva sulla stringa input_string, inoltre controlla un'eventuale presenza di errori
				cout << "Impossibile aprire il file 'input.txt'\n";
				system("pause>nul");
				return 1;
			}
			if(derivative(input_string, output_string)) { // Funzione che calcola la derivata
				cout << "Impossibile derivare, possibile errore nel file di input\n";
				system("pause>nul");
				return 1;
			}
			flagError = 0;
			break;
		case 3: // Viene considerata la stringa immessa dall'utente senza l'ausilio di file
			cout << "Inserire l'espressione: ";
			cin >> input_string;
			if(derivative(input_string, output_string)) { // Funzione che calcola la derivata
				cout << "Impossibile derivare, possibile errore nell'input\n";
				system("pause>nul");
				return 1;
			}
			flagError = 0;
			break;
		default:
			cout << "Scelta non valida! Riprovare. \n#: ";
			getNumber(&menu_choice);
			break;
		}
	} // Fine della gestione del primo menù del programma

	menu_choice = 0;
	cout << "\nLa derivata della funzione e' stata calcolata correttamente.\nSelezionare un metodo di visualizzazione dell'output:\n\t1) Salvare in 'output.txt' nella cartella dell'eseguibile\n\t2) Salvare in un file specificato dall'utente\n\t (il percorso deve contenere / al posto delle \\,ad es. C:/funzione.txt)\n\t3) Visualizzazione su schermo\n#: ";
	getNumber(&menu_choice);
	flagError = 1;

												/* Ciclo che contolla eventuali errori nella fase di output */
	while (flagError){
		cout << "\n";
		switch(menu_choice) { // Gestione del secondo menù
		case 1: // Viene creato il file di "default" nella cartella dell'eseguibile
			if(write_file(output_string, "output.txt")) { // Scrive la stringa output_string sul file output.txt e controlla un'eventuale presenza di errori
				cout << "Impossibile creare o aprire il file 'output.txt'\n";
				system("pause>nul");
				return 1;
			}
			cout << "File di output scritto correttamente.\n";
			flagError = 0;
			break;
		case 2: // Viene creato il file nel percorso scelto dall'utente
			cout << "Inserire il percorso del file: ";
			cin >> output_file;
			if(write_file(output_string, output_file)) { // Scrive la stringa output_string sul file output.txt e controlla un'eventuale presenza di errori
				cout << "Impossibile creare o aprire il file 'output.txt'\n";
				system("pause>nul");
				return 1;
			}
			cout << "File di output scritto correttamente.\n";
			flagError = 0;
			break;
		case 3: // La stringa in output viene visualizzata a video
			cout << output_string;
			flagError = 0;
			break;
		default:
			cout << "Scelta non valida! Riprovare. \n#: ";
			getNumber(&menu_choice);
			break;
		}
	} // Fine gestione del secondo menù
	cout << "\n\nProgramma terminato correttamente. Premere un tasto per uscire..\n\n";
	system("pause>nul");
	return 0;
}