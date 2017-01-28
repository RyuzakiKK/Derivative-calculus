/***********************************************************************\
*	Elaborato_ASD
*
*	Programmers ---> Eugenio - Mauro - Ludovico
*
*	Functions.cpp
\***********************************************************************/


#include <Functions.h>


bool read_file(string& input_string, string input_file) { // Legge il file di input e scrive la stringa su input_string
	ifstream fileToRead;
	fileToRead.open(input_file);
	if( !fileToRead.is_open() ) return 1; // Controlla se il file è stato aperto correttamente 
	fileToRead >> input_string; // Scrive il contenuto del file nella stringa
	fileToRead.close(); // Chiude il file
	return 0;
}

bool write_file(string output_string, string output_file) { // Crea il file di output
	ofstream fileToWrite;
	fileToWrite.open(output_file);
	if( !fileToWrite.is_open() ) return 1; // Controlla se il file è stato aperto correttamente
	fileToWrite << output_string; // Scrive il contenuto della stringa sul file di output
	fileToWrite.close();
	return 0;
}

void getNumber(int* choice){ // Prende un numero necessario alla scelta del menù (main)
	bool flag;
	do
	{
		flag = 0;
		if(!scanf_s("%d", choice, 1)) // Verifica il valore inserito dall'utente
		{
			flag = 1;
			cout << "\nScelta non valida! Riprovare. \n#: ";
		}
		while(getchar() != '\n'); // getchar usato per evitare il loop del ciclo while
	} while (flag);
}

size_t find_comma(string input_string){ // Cerca la virgola tra 2 operandi della stessa funzione
	int flag = 1;
	size_t ii, ji = 0;
	for(ii = 0; ii < input_string.length() && flag; ii++){
		if(input_string[ii] == '(') {
			ji++;
		}
		else if(input_string[ii] == ')'){
			ji--;
		}
		if(ji == 0 && input_string[ii] == ','){ // Controlla se il carattere corrente una virgola solo se il numero di parentesi aperte e chiuse è uguale
			flag = 0;
		}
		else if(ji < 0){ // Se ci sono più parentesi chiuse che aperte segnala un errore
			ii = 0;
			flag = 0;
		}
	}
	if(ii == input_string.length()){ // Se non è stato possibile trovare la virgola
		return 0;
	}
	ii--;
	return ii;
}

bool derivative(string input_string, string& output_string) { // CALCOLO DELLA DERIVATA
	int j, temp;
	string output_temp, output_temp2;
	
	if(input_string == "ASD"){ // EASTER EGG
		output_string = "          .--.\n        .' `. ',\n      .' `.  `. ',\n     / `.  `.  `. \\\n    /`.  `.  `.  `.\\\n   Y   `.  `.  `.   Y\n   |`.   `.  `.  `. |     de Nittis Ludovico\n   |  `.   `.  `.  '|\n   Y`.  `.   `.  `. Y\n    \\ `.  `.   `.  /\n     \\  `.  `.   `/\n      `.  `.  `..'\n        `.._`..'\n\n\n          .--.\n        .'    ',\n      .'        ',\n     /\\/\\/\\/\\/\\/\\/\\\n    /\\/\\/\\/\\/\\/\\/\\/\\\n   Y                Y\n   |/\\/\\/\\/\\/\\/\\/\\/\\|     Severi Eugenio\n   |\\/\\/\\/\\/\\/\\/\\/\\/|\n   Y                Y\n    \\/\\/\\/\\/\\/\\/\\/\\/\n     \\/\\/\\/\\/\\/\\/\\/\n      `.        .'\n        `..__..'\n\n\n          .--.\n        .'    ',\n      .'.*.*.*.*',\n     /            \\\n    /              \\\n   Y                Y\n   |.*.*.*.*.*.*.*.*|     Valmori Mauro\n   |.*.*.*.*.*.*.*.*|\n   Y                Y\n    \\              /\n     \\            /\n      `.*.*.*.*..'\n        `..__..'\n";
		return 0;
	}
	if(input_string == "x"){ // Se si tratta di una variabile tipo x allora la sua derivata è 1 
		output_string = "1";
		return 0;
	}
	stringstream convert(input_string.substr(0, input_string.length())); // Si converte la stringa in numero, stringstream usato per la conversione
	if ( convert >> temp ){ // Se è una costante allora la sua derivata è 0
		output_string = "0";
		return 0;
	}
	if(input_string[input_string.length()-1] != ')'){
		return 1;
	}
	if("sen" == input_string.substr(0,3) || "Sen" == input_string.substr(0,3)) { // SENO
		if(derivative(input_string.substr(4,input_string.length()-5), output_temp)){ // Richiama la funzione (ricorsione) e ne controlla i valori di ritorno per verificare la presenza di errori
			return 1; 
		}
		if(output_temp == "0") { // Seno di 0 è uguale a 0, quindi alla stringa di output le assegnamo il valore 0 
			output_string = "0";
			return 0;
		}
		else if(output_temp == "1") { // Se output_temp è uguale a 1 allora il risultato sarebbe  la moltiplicazione per 1, quindi si può omettere
			output_string = "Cos("+input_string.substr(4,input_string.length()-5)+")";
			return 0;
		}
		else output_string = "Times("+output_temp+",Cos("+input_string.substr(4,input_string.length()-5)+"))"; // Regola generale della derivazione del seno
		return 0;
	}
	if("cos" == input_string.substr(0,3) || "Cos" == input_string.substr(0,3)) { // COSENO
		if(derivative(input_string.substr(4,input_string.length()-5), output_temp)){ // Richiama la funzione (ricorsione) e ne controlla i valori di ritorno per verificare la presenza di errori		
			return 1;
		}
		if(output_temp == "0") { // Coseno di 0 è uguale a 0
			output_string = "0";
			return 0;
		}
		else if(output_temp == "1") { // Se output_temp è uguale a 1 allora il risultato sarebbe  la moltiplicazione per 1, quindi si può omettere 
			output_string = "Minus(Sen("+input_string.substr(4,input_string.length()-5)+"))";
			return 0;
		}
		else output_string = "Times("+output_temp+",Minus(0,Sen("+input_string.substr(4,input_string.length()-5)+")))"; // Regola generale per la derivazione del coseno
		return 0;
	}
	if("times" == input_string.substr(0,5) || "Times" == input_string.substr(0,5)){ // MOLTIPLICAZIONE
		j = find_comma(input_string.substr(6,input_string.length()-7)); // Assegno alla variabile j l'indice in cui si trova la virgola
		if(j == 0){ // Se c'è stato un errore durante la ricerca della virgola
			return 1;
		}
		if(derivative(input_string.substr(6, j), output_temp)){ // Richiama la funzione sul primo operando (ricorsione) e ne controlla i valori di ritorno per verificare la presenza di errori
			return 1;
		}
		if(derivative(input_string.substr(6+j+1, input_string.length()-6-j-2), output_temp2)){ // Richiama la funzione sul secondo operando (ricorsione) e ne controlla i valori di ritorno per verificare la presenza di errori
			return 1;
		}
		if(output_temp == "0" && output_temp2 == "0"){ // Se la derivata di entrambi gli operandi è uguale a 0, allora il risultato è 0
			output_string = "0";
			return 0;
		}
		else if(output_temp == "0" && output_temp2 == "1"){ // Se la prima derivata è 0 e la seconda è 1
			output_string = input_string.substr(6, j);
			return 0;
		}
		else if(output_temp == "1" && output_temp2 == "0"){ // Se la prima derivata è 1 e la seconda è 0
			output_string = input_string.substr(6+j+1, input_string.length()-6-j-2);
			return 0;
		}
		else if(output_temp == "0"){ // Se la prima derivata è 0
			output_string = "Times("+input_string.substr(6, j)+","+output_temp2+")";
			return 0;
		}
		else if(output_temp2 == "0"){ // Se la seconda derivata è 0
			output_string = "Times("+output_temp+","+input_string.substr(6+j+1, input_string.length()-6-j-2)+")";
			return 0;
		}
		else if(output_temp == "1" && output_temp2 == "1"){ // Se entrambe le derivate sono 1
			output_string = "Plus("+input_string.substr(6, j)+","+input_string.substr(6+j+1, input_string.length()-6-j-2)+")";
			return 0;
		}
		else if(output_temp == "1"){ // Se la prima derivata è 1
			output_string = "Plus(Times("+input_string.substr(6, j)+","+output_temp2+"),"+input_string.substr(6+j+1, input_string.length()-6+j-2)+")";
			return 0;
		}
		else if(output_temp2 == "1"){ // Se la seconda derivata è 1
			output_string = "Plus("+input_string.substr(6, j)+",Times("+output_temp+","+input_string.substr(6+j+1, input_string.length()-6-j-2)+"))";
			return 0;
		}
		else{ // Regola generele della moltiplicazione
			output_string = "Plus(Times("+input_string.substr(6, j)+","+output_temp2+"),Times("+output_temp+","+input_string.substr(6+j+1, input_string.length()-6-j-2)+"))";
			return 0;
		}
	}
	if("pow" == input_string.substr(0,3) || "Pow" == input_string.substr(0,3)){ // POTENZA
		j = find_comma(input_string.substr(4,input_string.length()-5)); // Assegna alla variabile j l'indice in cui si trova la virgola	
		if(j == 0){ // Se c'è stato un errore durante la ricerca della virgola
			return 1; 
		}
		if(input_string.substr(4, j) != "x"){ // Controlla se il primo operando è diverso da x
			stringstream convert(input_string.substr(4, j)); // Si converte la stringa in numero
			if ( !(convert >> temp) ) return 1; // Controllo se è realmente un numero			
			output_string = "0"; // Se è un numero la derivata è 0
			return 0;
		}
		if(input_string.substr(4+j+1, input_string.length()-4-j-2) == "0"){ // Se il secondo operando è 0 allora la derivata di 1 è 0
			output_string = "0";
			return 0;
		}
		if(input_string.substr(4+j+1, input_string.length()-4-j-2) == "1"){ // Se il secondo operando è 1 allora la derivata di x è 1
			output_string = "1";
			return 0;
		}
		if(input_string.substr(4+j+1, input_string.length()-4-j-2) == "2"){ // Se il secondo operando è 2 allora la derivata di x^2 è x senza pow
			output_string = "Times("+input_string.substr(4+j+1, input_string.length()-4-j-2)+","+input_string.substr(4, j)+")";
			return 0;
		}
		else{ // Regola generale di derivazione della funzione potenza
			stringstream convert(input_string.substr(4+j+1, input_string.length()-4-j-2)); // Si converte la stringa in numero per potergli sottrarre 1 e poi la si riconverte in stringa, stringstream usato per la conversione
			if ( !(convert >> temp) ) return 1; // Controllo dello stato della conversione
			temp = temp-1;
			stringstream returning; // Riconversione del numero in stringa
			returning << temp;
			output_temp = returning.str();
			output_string = "Times("+input_string.substr(4+j+1, input_string.length()-4-j-2)+",Pow("+input_string.substr(4, j)+","+output_temp+"))";
			return 0;																				
		}
	}
	if("plus" == input_string.substr(0,4) || "Plus" == input_string.substr(0,4)){ // SOMMA
		j = find_comma(input_string.substr(5,input_string.length()-6)); // Assegno alla variabile j l'indice in cui si trova la virgola
		if(j == 0){ // Se c'è stato un errore durante la ricerca della virgola
			return 1;
		}
		if(derivative(input_string.substr(5, j), output_temp)){ // Richiama la funzione sul primo operando (ricorsione) e ne controlla i valori di ritorno per verificare la presenza di errori
			return 1; 
		}
		if(derivative(input_string.substr(5+j+1, input_string.length()-5-j-2), output_temp2)){ // Richiama la funzione sul secondo operando (ricorsione) e ne controlla i valori di ritorno per verificare la presenza di errori
			return 1; 
		}
		if(output_temp == "0" && output_temp2 == "0"){ // Nel caso in cui tutti e due gli operandi siamo 0 allora il risultato della derivazione è 0
			output_string = "0";
			return 0;
		}
		else if(output_temp == "0"){ // Nel caso in cui il primo operando sia 0 allora il risultato della derivazione è la derivata del secondo operando						
			output_string = output_temp2;
			return 0;
		}
		else if(output_temp2 == "0"){ // Nel caso in cui il secondo operando sia 0 allora il risultato della derivazione è la derivata del primo operando
			output_string = output_temp;
			return 0;
		}
		else{ // Regola generale della derivazione della somma
			output_string = "Plus("+output_temp+","+output_temp2+")";
			return 0;
		}
	}
	if("minus" == input_string.substr(0,5) || "Minus" == input_string.substr(0,5)){ // SOTTRAZIONE
		j = find_comma(input_string.substr(6,input_string.length()-7));
		if(j == 0){ // Se c'è stato un errore durante la ricerca della virgola
			return 1; 
		}
		if(derivative(input_string.substr(6, j), output_temp)){ // Richiama la funzione sul primo operando (ricorsione) e ne controlla i valori di ritorno per verificare la presenza di errori
			return 1; 
		}
		if(derivative(input_string.substr(6+j+1, input_string.length()-6-j-2), output_temp2)){ // Richiama la funzione sul secondo operando (ricorsione) e ne controlla i valori di ritorno per verificare la presenza di errori
			return 1; 
		}
		if(output_temp == "0" && output_temp2 == "0"){ // Nel caso in cui tutti e due gli operandi siamo 0 allora il risultato della derivazione è 0
			output_string = "0";
			return 0;
		}
		else if(output_temp2 == "0"){ // Nel caso in cui il secondo operando sia 0 allora il risultato della derivazione è la derivata del primo operando
			output_string = output_temp;
			return 0;
		}
		else{ // Regola generale della derivazione della sottrazione (comprende anche il caso in cui output_temp == 0 e output_temp2 != 0)
			output_string = "Minus("+output_temp+","+output_temp2+")";
			return 0;
		}
	}
	if("div" == input_string.substr(0,3) || "Div" == input_string.substr(0,3)){ // DIVISIONE
		j = find_comma(input_string.substr(4,input_string.length()-5)); // Assegno alla variabile j l'indice in cui si trova la virgola
		if(j == 0){ // Se c'è stato un errore durante la ricerca della virgola
			return 1;
		}
		if(derivative(input_string.substr(4, j), output_temp)){ // Richiama la funzione sul primo operando (ricorsione) e ne controlla i valori di ritorno per verificare la presenza di errori
			return 1;
		}
		if(derivative(input_string.substr(4+j+1, input_string.length()-4-j-2), output_temp2)){ // Richiama la funzione sul secondo operando (ricorsione) e ne controlla i valori di ritorno per verificare la presenza di errori
			return 1;
		}
		if(input_string.substr(4+j+1, input_string.length()-4-j-2) == "0"){ // Se il secondo operando è 0, non si può dividere per 0
			output_string = "0";
			return 1;
		}
		if(output_temp == "0" && output_temp2 == "0"){ // Se entrambe le derivate degli operandi sono 0, il risultato è 0
			output_string = "0";
			return 0;
		}
		else if(output_temp == "0"){ // Se la derivata del primo operando è 0
			output_string = "Div(Minus(Times("+input_string.substr(4, j)+","+output_temp2+")),Pow("+input_string.substr(4+j+1, input_string.length()-4-j-2)+",2))";
			return 0;
		}
		else if(output_temp2 == "0"){ // Se la derivata del secondo operando è 0
			output_string = "Div(Times("+input_string.substr(4+j+1, input_string.length()-4-j-2)+","+output_temp+"),Pow("+input_string.substr(4+j+1, input_string.length()-4-j-2)+",2))";
			return 0;
		}
		else{ // Regola generale della derivazione della divisione
			output_string =  "Div(Minus(Times("+input_string.substr(4+j+1, input_string.length()-4-j-2)+","+output_temp+"),Times("+input_string.substr(4, j)+","+output_temp2+")),Pow("+input_string.substr(4+j+1, input_string.length()-4-j-2)+",2))";
			return 0;
		}
	}
	else return 1; // Se non è nessuno dei casi precedenti --> errore nell'input
}
