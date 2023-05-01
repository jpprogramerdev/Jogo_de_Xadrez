// Jo�o Pedro Gerotto Fernandes
// 1840482212014

#include <iostream>
#include <iomanip>
#include <locale.h>
#include <string>
#include <cstdlib>

using namespace std;
// variaveis globais
char board[9][9] = {
		{' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
		{'1', 'T', 'C', 'B', 'Q', 'K', 'B', 'C', 'T'},
		{'2', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
		{'3', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{'4', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{'5', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{'6', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{'7', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
		{'8', 't', 'c', 'b', 'q', 'k', 'b', 'c', 't'}
	};

bool gameOver = false;

string vezJogador = "";

bool jogadaValida = true;

char pecasBrancas[6] = {'p', 't', 'c', 'b', 'q', 'k'};

char pecasPretas[6] = {'P', 'T', 'C', 'B', 'Q', 'K'};

// fun��o para explicar como o jogo funciona
void tutorialJogo(){
	setlocale(LC_ALL, "Portuguese");

	string confirmacao = "";

	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif

	cout << "1 - A pe�a s�o representadas por letras, onde as maiusculas s�o as pretas e as minusculas s�o as brancas: " << endl;
	cout << "	Pe�o - p,P" << endl;
	cout << "	Torre - t,T" << endl;
	cout << "	Bispo - b,B" << endl;
	cout << "	Cavalo - c,C" << endl;
	cout << "	Rainha - q,Q" << endl;
	cout << "	Rei - k,K" << endl<< endl;
	cout << "2 - Para escolher uma pe�a, voc� deve digitar o nome dela,exemplo: " << endl;
	cout << " Gostaria de jogar rei? Digite rei" << endl;
	cout << "	No caso do pe�o n�o digite com o acento ok? Digite peao" << endl<< endl;
	cout << "3 - O jogo ira fornecer para voc� as pe�as disponiveis em suas coordenadaas, exemplo: " << endl;
	cout << "	Caso voc� escolha pe�a, o jogo ir� apresentar da seguinte forma" << endl;
	cout << " 		7A" << endl;
	cout << " 		7B" << endl;
	cout << " E assim por diante" << endl<< endl;
	cout << "4 - Caso voc� queira voltar para a sele��o de pe�a, basta digitar VOLTAR" << endl<< endl;
	cout << "5 - Caso voc� erre um movimento, o jogo volta para voc� fazer o movimento certo" << endl<< endl;
	cout << "6 - Quando for escolher a pe�a que o peao deseje virar, digite o numero da pe�a ou seu nome"<<endl<<endl;
	
	do{
		cout << "Podemos come�ar a jogar?" << endl;
		cin >>confirmacao;

		for (int i = 0; i < confirmacao.length(); i++){
			confirmacao[i] = toupper(confirmacao[i]);
		}
	} while (confirmacao != "SIM");
}

// fun��o para saber em pe�as mais complicadas como bispo, se tem algo no caminho dele
bool temPecaNoCaminho(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, char board[9][9]){
	int dLinha = (linhaDestino - linhaOrigem > 0) ? 1 : ((linhaDestino - linhaOrigem < 0) ? -1 : 0);
	int dColuna = (colunaDestino - colunaOrigem > 0) ? 1 : ((colunaDestino - colunaOrigem < 0) ? -1 : 0);
	int linha = linhaOrigem + dLinha;
	int coluna = colunaOrigem + dColuna;

	while (linha != linhaDestino || coluna != colunaDestino){
		if (board[linha][coluna] != ' '){
			if ((linha == linhaDestino && coluna == colunaDestino) && ((isupper(board[linha][coluna]) && vezJogador == "Vez das pe�as brancas") || (islower(board[linha][coluna]) && vezJogador == "Vez das pe�as pretas"))){
				// pe�a adversaria no destino, jogada valida
				return false;
			}
			else{
				// h� uma pe�a no caminho, jogada invalida
				return true;
			}
		}
		linha += dLinha;
		coluna += dColuna;
	}

	// n�o h� pe�a no caminho, jogada valida
	return false;
}

//fun��o verifica se existe um dos reis no tabuleiro
bool temRei(){
	bool reiBranco = false, reiPreto = false;
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			if (board[i][j] == 'K'){
				reiBranco = true;
			}
			else if (board[i][j] == 'k'){
				reiPreto = true;
			}
		}
	}
	
	return reiBranco && reiPreto;
}

// a cada movimento, troca a vez do jogador
void trocaJogador(){
	if (vezJogador == "Vez das pe�as pretas"){
		vezJogador = "Vez das pe�as brancas";
		cout << vezJogador << endl<< endl;
	}
	else{
		vezJogador = "Vez das pe�as pretas";
		cout << vezJogador << endl<< endl;
	}
}

// fun��o para exbir a tabela toda vez que precisar
void exibeTab(){

	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			cout << setw(6) << board[i][j];
		}
		cout << endl;
	}
}

void rei(){
	string movimento = "";
	int colunaDestino = 0;
	int linhaDestino = 0;
	int linhaRei = 0;
	int colunaRei = 0;

	// Encontra em quem  posi��o o rei se encontra no tabuleiro
	for (int i = 0; i < 9; i++){
		for (int j = 1; j < 9; j++){
			if (vezJogador == "Vez das pe�as brancas" && board[i][j] == 'k'){
				linhaRei = i;
				colunaRei = j;
			}
			else if (vezJogador == "Vez das pe�as pretas" && board[i][j] == 'K'){
				linhaRei = i;
				colunaRei = j;
			}
		}
	}

	// Pergunta para onde o usuario deseja mover o rei
	cout << "Para onde deseja mover o rei " << linhaRei << char('A' + colunaRei - 1) << "?" << endl;

	do{
		cin >> movimento;
		for (int i = 0; i < movimento.length(); i++){
			movimento[i] = toupper(movimento[i]);
		}

		if (movimento == "VOLTAR"){
			jogadaValida = false;
			break;
		}

		linhaDestino = movimento[0] - '0';
		colunaDestino = movimento[1] - 'A' + 1;

		// Verifica��o do movimento do rei
		if ((abs(linhaDestino - linhaRei) <= 1) && (abs(colunaDestino - colunaRei) <= 1)){
			if (!temPecaNoCaminho(linhaRei, colunaRei, linhaDestino, colunaDestino, board)){
				board[linhaDestino][colunaDestino] = tolower(board[linhaRei][colunaRei]);
				board[linhaRei][colunaRei] = ' ';
				jogadaValida = true;
			}
			else{
				cout << "Movimento invalido, h� uma pe�a no caminho" << endl;
				jogadaValida = false;
			}
		}
		else{
			cout << "Movimento invalido" << endl;
			jogadaValida = false;
		}
	} while (!jogadaValida);
}

// movimento rainha
void rainha(){
	int cont;
	string cordenadaRainha = "";
	string movimento = "";
	int colunaDestino = 0;
	int linhaDestino = 0;
	int linhaRainha = 0;
	int colunaRainha = 0;

	setlocale(LC_ALL, "Portuguese");
	cout << "Qual torre deseja movimentar?" << endl;

	do{ 
		do{// ficar repetindo at� ter uma posi��o valida
			cont = 1;
			for (int i = 0; i < 9; i++){
				for (int j = 1; j < 9; j++){
					if (vezJogador == "Vez das pe�as brancas"){ // verificando qual jogador � vez
						if (board[i][j] == 'q'){
							char letraCol = board[0][j];
							cout << cont << " - " << i << letraCol << endl;
							cont++;
						}
					}
					else{
						if (board[i][j] == 'Q'){ // no caso das pe�aas pretas
							char letraCol = board[0][j];
							cout << cont << " - " << i << letraCol << endl;
							cont++;
						}
					}
				}
			}
	
			cin >> cordenadaRainha;
	
			for (int i = 0; i < cordenadaRainha.length(); i++){
				cordenadaRainha[i] = toupper(cordenadaRainha[i]);
			}
	
			if (cordenadaRainha == "VOLTAR"){
				jogadaValida = false;
				break;
			}
	
			linhaRainha = cordenadaRainha[0] - '0';
			colunaRainha = cordenadaRainha[1] - 'A' + 1;
		
			//Verific��o de pe�a existente
			if(vezJogador == "Vez das pe�as brancas"){
				if (board[linhaRainha][colunaRainha] != 'q'){
							cout << "Posi��o invaida, n�o h� um pe�a na posi��o " << cordenadaRainha << endl;
							jogadaValida = false;
				}else{
							jogadaValida = true;
				}
						
			}else{
				if (board[linhaRainha][linhaRainha] != 'Q'){
					cout << "Posi��o invaida, n�o h� um pe�a na posi��o " << cordenadaRainha << endl;
					jogadaValida = false;
				}else{
					jogadaValida = true;
				}
			}
		}while(!jogadaValida);

		cout << "Para onde deseja mover a rainha " << cordenadaRainha << "?" << endl;
		cin >> movimento;
		for (int i = 0; i < movimento.length(); i++){
			movimento[i] = toupper(movimento[i]);
		}

		linhaDestino = movimento[0] - '0';
		colunaDestino = movimento[1] - 'A' + 1;

		// verificando qual jogador � vez
		if (vezJogador == "Vez das pe�as brancas"){ // pe�as brancas
			// movimento em diagonal
			if (abs(linhaDestino - linhaRainha) == abs(colunaDestino - colunaRainha) && linhaDestino != linhaRainha && colunaDestino != colunaRainha && !temPecaNoCaminho(linhaRainha, colunaRainha, linhaDestino, colunaDestino, board)){
				if (temPecaNoCaminho(linhaRainha, colunaRainha, linhaDestino, colunaDestino, board)){
					cout << "Movimento invalido, h� uma pe�a no caminho" << endl;
					jogadaValida = false;
				}
				else{
					board[linhaDestino][colunaDestino] = 'q';
					board[linhaRainha][colunaRainha] = ' ';
					jogadaValida = true;
				}	
			}
			// Movimento vertical
			else if (colunaDestino == colunaRainha && linhaDestino != linhaRainha){
				if (!temPecaNoCaminho(linhaRainha, colunaRainha, linhaDestino, colunaDestino, board)){
					board[linhaDestino][colunaDestino] = 'q';
					board[linhaRainha][colunaRainha] = ' ';
					jogadaValida = true;
				}
				else{
					cout << "Movimento invalido, h� uma pe�a no caminho" << endl;
					jogadaValida = false;
				}
			}
			//movimento na horizontal
			else if (linhaDestino == linhaRainha && colunaDestino != colunaRainha){
				if (!temPecaNoCaminho(linhaRainha, colunaRainha, linhaDestino, colunaDestino, board)){
					board[linhaDestino][colunaDestino] = 'q';
					board[linhaRainha][colunaRainha] = ' ';
					jogadaValida = true;
				}
				else{
					cout << "Movimento invalido, h� uma pe�a no caminho" << endl;
					jogadaValida = false;
				}
			}
			else{
				cout << "Movimento invalido" << endl;
				jogadaValida = false;
			}
		}
		else{
			// verfica��o do movimento em diagonal
			if (abs(linhaDestino - linhaRainha) == abs(colunaDestino - colunaRainha) && linhaDestino != linhaRainha && colunaDestino != colunaRainha && !temPecaNoCaminho(linhaRainha, colunaRainha, linhaDestino, colunaDestino, board)){
				if (temPecaNoCaminho(linhaRainha, colunaRainha, linhaDestino, colunaDestino, board)){
					cout << "Movimento invalido, h� uma pe�a no caminho" << endl;
					jogadaValida = false;
				}
				else{
					board[linhaDestino][colunaDestino] = 'Q';
					board[linhaRainha][colunaRainha] = ' ';
					jogadaValida = true;
				}
			}
			
			// Movimento vertical
			else if (colunaDestino == colunaRainha && linhaDestino != linhaRainha){
				if (!temPecaNoCaminho(linhaRainha, colunaRainha, linhaDestino, colunaDestino, board)){
					board[linhaDestino][colunaDestino] = 'Q';
					board[linhaRainha][colunaRainha] = ' ';
					jogadaValida = true;
				}
				else{
					cout << "Movimento invalido, h� uma pe�a no caminho" << endl;
					jogadaValida = false;
				}
				
			}
			
			// Movimento horiizontal
			else if (linhaDestino == linhaRainha && colunaDestino != colunaRainha){
				if (!temPecaNoCaminho(linhaRainha, colunaRainha, linhaDestino, colunaDestino, board)){
					board[linhaDestino][colunaDestino] = 'Q';
					board[linhaRainha][colunaRainha] = ' ';
					jogadaValida = true;
				}
				else{
					cout << "Movimento invalido, h� uma pe�a no caminho" << endl;
					jogadaValida = false;
				}
			}
			else{
				cout << "Movimento invalido" << endl;
				jogadaValida = false;
			}
		}
	} while (!jogadaValida);
}

// movimento torre
void torre(){
	int cont;
	string cordenadaTorre = "";
	string movimento = "";
	int colunaDestino = 0;
	int linhaDestino = 0;
	int linhaTorre = 0;
	int colunaTorre = 0;

	setlocale(LC_ALL, "Portuguese");
	cout << "Qual torre deseja movimentar?" << endl;

	do{ // ficar repetindo at� ter uma posi��o valida
		do{
			cont = 1;
				for (int i = 0; i < 9; i++){
					for (int j = 1; j < 9; j++){
						if (vezJogador == "Vez das pe�as brancas"){ // verificando qual jogador � a vez
							if (board[i][j] == 't'){
								char letraCol = board[0][j];
								cout << cont << " - " << i << letraCol << endl;
								cont++;
							}
						}
						else{
							if (board[i][j] == 'T'){ // no caso das pe�a pretas
								char letraCol = board[0][j];
								cout << cont << " - " << i << letraCol << endl;
								cont++;
							}
						}
					}
				}
		
				cin >> cordenadaTorre;
		
				for (int i = 0; i < cordenadaTorre.length(); i++){
					cordenadaTorre[i] = toupper(cordenadaTorre[i]);
				}
		
				if (cordenadaTorre == "VOLTAR"){
					jogadaValida = false;
					break;
				}
		
				linhaTorre = cordenadaTorre[0] - '0';
				colunaTorre = cordenadaTorre[1] - 'A' + 1;
				
				//Verific��o de pe�a existente
				if(vezJogador == "Vez das pe�as brancas"){
					if (board[linhaTorre][colunaTorre] != 't'){
							cout << "Posi��o invaida, n�o h� um pe�a na posi��o " << cordenadaTorre << endl;
							jogadaValida = false;
					}else{
							jogadaValida = true;
					}
						
				}else{
					if (board[linhaTorre][colunaTorre] != 'T'){
							cout << "Posi��o invaida, n�o h� um pe�a na posi��o " << cordenadaTorre << endl;
							jogadaValida = false;
					}else{
							jogadaValida = true;
					}
				}
			}while(!jogadaValida);
		cout << "Para onde deseja mover a torre " << cordenadaTorre << "?" << endl;
		cin >> movimento;
		
		for (int i = 0; i < movimento.length(); i++){
			movimento[i] = toupper(movimento[i]);
		}

		linhaDestino = movimento[0] - '0';
		colunaDestino = movimento[1] - 'A' + 1;

		// verificando qual jogador � a vez
		if (vezJogador == "Vez das pe�as brancas"){ // pe�as brancas
			// caso o usuario digite a coordenada em diagonal
			if (abs(linhaDestino - linhaTorre) == abs(colunaDestino - colunaTorre)){
				cout << "Movimento invalido, n�o pode mover na diagonal" << endl;
				jogadaValida = false;
			}
			
			else if (temPecaNoCaminho(linhaTorre, colunaTorre, linhaDestino, colunaDestino, board)){
				cout << "Movimento invalido, h� uma pe�a no caminho" << endl;
				jogadaValida = false;
			}
			
			else{
				board[linhaDestino][colunaDestino] = 't';
				board[linhaTorre][colunaTorre] = ' ';
				jogadaValida = true;
			}
		}
		
		else{ // pe�a pretas
			// caso o usuario digite a coordenada em diagonal
			if (abs(linhaDestino - linhaTorre) == abs(colunaDestino - colunaTorre)){
				cout << "Movimento invalido, n�o pode mover na diagonal" << endl;
				jogadaValida = false;
			}
			
			else if (temPecaNoCaminho(linhaTorre, colunaTorre, linhaDestino, colunaDestino, board)){
				cout << "Movimento invalido, h� uma pe�a no caminho" << endl;
				jogadaValida = false;
			}
			
			else{
				board[linhaDestino][colunaDestino] = 'T';
				board[linhaTorre][colunaTorre] = ' ';
				jogadaValida = true;
			}
		}
	} while (!jogadaValida);
}

// movimento bispo
void bispo(){
	int cont;
	string cordenadaBispo = "";
	string movimento = "";
	int colunaDestino = 0;
	int linhaDestino = 0;
	int linhaBispo = 0;
	int colunaBispo = 0;
	
	setlocale(LC_ALL, "Portuguese");
	cout << "Qual bispo deseja movimentar?" << endl;

	do{ // ficar repetindo at� ter uma jogada valida
		do{
			cont = 1;
			for (int i = 1; i < 9; i++){
				for (int j = 0; j < 9; j++){
					if (vezJogador == "Vez das pe�as brancas"){ // verificando qual jogador � vez
						if (board[i][j] == 'b'){
							char letraCol = board[0][j];
							cout << cont << " - " << i << letraCol << endl;
							cont++;
						}
					}
					else{
						if (board[i][j] == 'B'){ // no caso das pe�as pretas
							char letraCol = board[0][j];
							cout << cont << " - " << i << letraCol << endl;
							cont++;
						}
					}
				}
			}
	
			cin >> cordenadaBispo;
	
			for (int i = 0; i < cordenadaBispo.length(); i++){
				cordenadaBispo[i] = toupper(cordenadaBispo[i]);
			}
	
			if (cordenadaBispo == "VOLTAR"){
				jogadaValida = false;
				break;
			}
	
			for (int i = 0; i < cordenadaBispo.length(); i++){
				cordenadaBispo[i] = toupper(cordenadaBispo[i]);
			}
	
			linhaBispo = cordenadaBispo[0] - '0';
			colunaBispo = cordenadaBispo[1] - 'A' + 1;
			
			if(vezJogador == "Vez das pe�as brancas"){
				if (board[linhaBispo][colunaBispo] != 'b'){
						cout << "Posi��o invaida, n�o h� um pe�a na posi��o " << cordenadaBispo << endl;
						jogadaValida = false;
					}
				else{
						jogadaValida = true;
				}
				
			}else{
				if (board[linhaBispo][colunaBispo] != 'B'){
						cout << "Posi��o invaida, n�o h� um pe�a na posi��o " << cordenadaBispo << endl;
						jogadaValida = false;
				}
				else{
						jogadaValida = true;
				}
			}
		}while(!jogadaValida);

		cout << "Para onde deseja mover o bispo " << cordenadaBispo << "?" << endl;
		cin >> movimento;
		for (int i = 0; i < movimento.length(); i++){
			movimento[i] = toupper(movimento[i]);
		}

		linhaDestino = movimento[0] - '0';
		colunaDestino = movimento[1] - 'A' + 1;

		// verfica��o do movimento em diagonal
		if (abs(linhaDestino - linhaBispo) == abs(colunaDestino - colunaBispo) && linhaDestino != linhaBispo && colunaDestino != colunaBispo && !temPecaNoCaminho(linhaBispo, colunaBispo, linhaDestino, colunaDestino, board)){
			// Atualiza a posi��o do bispo
			if (vezJogador == "Vez das pe�as brancas"){ // verificando qual pe�a � a vez para ver se tem alguma pe�a do time no lugar de destino
				for (int i = 0; i < 6; i++){
					if (board[linhaDestino][colunaDestino] == pecasBrancas[i]){
						cout << "Movimento invalido, o lugar de destino tem uma pe�a do seu time" << endl;
						jogadaValida = false;
						break;
					}
					else{
						board[linhaDestino][colunaDestino] = 'b';
						board[linhaBispo][colunaBispo] = ' ';
						jogadaValida = true;
						break;
					}
				}
			}
			else{
				for (int i = 0; i < 6; i++){
					if (board[linhaDestino][colunaDestino] == pecasPretas[i]){
						cout << "Movimento invalido, o lugar de destino tem uma pe�a do seu time" << endl;
						jogadaValida = false;
						break;
					}
					else{
						board[linhaDestino][colunaDestino] = 'B';
						board[linhaBispo][colunaBispo] = ' ';
						jogadaValida = true;
						break;
					}
				}
			}
		}
		else{
			cout << "Movimento invalido" << endl;
			jogadaValida = false;
		}
	} while (!jogadaValida);
}

// movimento cavalo
void cavalo(){
	int cont ;
	string cordenadaCavalo = "";
	string movimento = "";
	int colunaDestino = 0;
	int linhaDestino = 0;
	int linhaCavalo = 0;
	int colunaCavalo = 0;

	setlocale(LC_ALL, "Portuguese");
	cout << "Qual cavalo deseja movimentar?" << endl;

	// brancas
	if (vezJogador == "Vez das pe�as brancas"){ // Verificando qual jogados � a vez
		do{ // ficar repetindo at� ter uma jogada valida
			cont = 1;
			for (int i = 0; i < 9; i++){
				for (int j = 1; j < 9; j++){
					if (board[i][j] == 'c'){
						char letraCol = board[0][j];
						cout << cont << " - " << i << letraCol << endl;
						cont++;
					}
				}
			}
			
			cin >> cordenadaCavalo;

			for (int i = 0; i < cordenadaCavalo.length(); i++){
				cordenadaCavalo[i] = toupper(cordenadaCavalo[i]);
			}

			if (cordenadaCavalo == "VOLTAR"){
				jogadaValida = false;
				break;
			}

			linhaCavalo = cordenadaCavalo[0] - '0';
			colunaCavalo = cordenadaCavalo[1] - 'A' + 1;

			// verifica se tem um peao na posicao certa
			if (board[linhaCavalo][colunaCavalo] != 'c'){
				cout << "Posi��o invalida, n�o h� um pe�o na posi��o " << cordenadaCavalo << endl;
				jogadaValida = false;
			}
			else{
				jogadaValida = true;
			}
		} while (!jogadaValida);
		
		if (jogadaValida == true){
			do{
				cout << "Para onde deseja mover o cavalo " << cordenadaCavalo << "?" << endl;
				cin >> movimento;
				
				for (int i = 0; i < movimento.length(); i++){
					movimento[i] = toupper(movimento[i]);
				}
				
				if(movimento == "VOLTAR"){
						jogadaValida = false;
						break;
				}

				linhaDestino = movimento[0] - '0';
				colunaDestino = movimento[1] - 'A' + 1;

				if (abs(linhaDestino - linhaCavalo) == 2 && abs(colunaDestino - colunaCavalo) == 1 ||abs(linhaDestino - linhaCavalo) == 1 && abs(colunaDestino - colunaCavalo) == 2){
					for (int i = 0; i < 6; i++){
						// verifica se tem uma pe�a branca no lugar de destino
						if (board[linhaDestino][colunaDestino] == pecasBrancas[i]){
							cout << "Movimento invalido, o lugar de destino tem uma pe�a do seu time" << endl;
							jogadaValida = false;
							break;
						}
						else{
							// Atualiza a posi��o do cavalo
							board[linhaDestino][colunaDestino] = 'c';
							board[linhaCavalo][colunaCavalo] = ' ';
							jogadaValida = true;
							break;
						}
					}
				}
				else{
					cout << "Movimento invalido para o cavalo" << endl;
					jogadaValida = false;
				}
			} while (jogadaValida == false);
		}
	}

	// pretas
	else{
		do{ // ficar repetindo at� ter uma posi��o valida
			cont = 1;
			for (int i = 1; i <= 9; i++){
				for (int j = 0; j < 9; j++){
					if (board[i][j] == 'C'){
						char letraCol = board[0][j];
						cout << cont << " - " << i << letraCol << endl;
						cont++;
					}
				}
			}
			
			cin >> cordenadaCavalo;

			for (int i = 0; i < cordenadaCavalo.length(); i++){
				cordenadaCavalo[i] = toupper(cordenadaCavalo[i]);
			}

			if (cordenadaCavalo == "VOLTAR"){
				jogadaValida = false;
				break;
			}

			linhaCavalo = cordenadaCavalo[0] - '0';
			colunaCavalo = cordenadaCavalo[1] - 'A' + 1;

			// verifica se tem um peao na posicao certa
			if (board[linhaCavalo][colunaCavalo] != 'C'){
				cout << "Posi��o invalida, n�o h� um pe�a na posi��o " << cordenadaCavalo << endl;
				jogadaValida = false;
			}
			else{
				jogadaValida = true;
			}
		} while (!jogadaValida);

		if (jogadaValida == true){
			do{
				cout << "Para onde deseja mover o cavalo " << cordenadaCavalo << "?" << endl;
				cin >> movimento;
				
				for (int i = 0; i < movimento.length(); i++){
					movimento[i] = toupper(movimento[i]);
				}
				
				if(movimento == "VOLTAR"){
					jogadaValida = false;
					break;
				}

				linhaDestino = movimento[0] - '0';
				colunaDestino = movimento[1] - 'A' + 1;

				if (abs(linhaDestino - linhaCavalo) == 2 && abs(colunaDestino - colunaCavalo) == 1 ||abs(linhaDestino - linhaCavalo) == 1 && abs(colunaDestino - colunaCavalo) == 2){
					for (int i = 0; i < 6; i++){
						// verifica se tem uma pe�a preta no lugar de destino
						if (board[linhaDestino][colunaDestino] == pecasPretas[i]){
							cout << "Movimento invalido, o lugar de destino tem uma pe�a do seu time" << endl;
							jogadaValida = false;
							break;
						}
						else{
							// Atualiza a posi��o do cavalo
							board[linhaDestino][colunaDestino] = 'C';
							board[linhaCavalo][colunaCavalo] = ' ';
							jogadaValida = true;
							break;
						}
					}
				}
				else{
					cout << "Movimento invalido para o cavalo" << endl;
					jogadaValida = false;
				}
			} while (!jogadaValida);
		}
	}
}

// movimentos do pe�o
void peao(){
	int cont;
	string cordenadaPeao = "";
	string movimento = "";
	int colunaDestino = 0;
	int linhaDestino = 0;
	string trocaPeao = "";
	int idTrocaPeao = 0;
	int linhaPeao = 0;
	int colunaPeao = 0;
	
	setlocale(LC_ALL, "Portuguese");
	cout << "Qual pe�o deseja movimentar?" << endl;

	// brancas
	if (vezJogador == "Vez das pe�as brancas"){ // Verificando qual jogador � vez
		do{ // ficar repetindo at� terr uma posi��o valida
			cont = 1;
			for (int i = 0; i < 9; i++){
				for (int j = 0; j < 9; j++){
					if (board[i][j] == 'p'){
						char letraCol = board[0][j];
						cout << cont << " - " << i << letraCol << endl;
						cont++;
					}
				}
			}

			cin >> cordenadaPeao;
			
			for (int i = 0; i < cordenadaPeao.length(); i++){
				cordenadaPeao[i] = toupper(cordenadaPeao[i]);
			}

			linhaPeao = cordenadaPeao[0] - '0';
			colunaPeao = cordenadaPeao[1] - 'A' + 1;

			// verifica se tem um peao na posicao certa
			if (board[linhaPeao][colunaPeao] != 'p'){
				cout << "Posi��o invaida, n�o h� um pe�a na posi��o " << cordenadaPeao << endl;
				jogadaValida = false;
			}
			else{
				jogadaValida = true;
			}
		} while (!jogadaValida);

		// se o pe�o escolhido for valido, pode fazer os moviimentos
		if (jogadaValida == true){
			do{
				cout << "Para onde deseja mover o pe�o " << cordenadaPeao << "?" << endl;
				cin >> movimento;
				
				for (int i = 0; i < movimento.length(); i++){
					movimento[i] = toupper(movimento[i]);
				}
				
				//caso o usuario deseja trocar de pe�a
				if (movimento == "VOLTAR"){
					jogadaValida = false;
					break;
				}

				linhaDestino = movimento[0] - '0';
				colunaDestino = movimento[1] - 'A' + 1;

				// verifica se h� uma pe�a diretamente na frente do pe�o
				if (linhaDestino == linhaPeao - 1 && colunaDestino == colunaPeao && board[linhaDestino][colunaDestino] == ' ')
				{
					board[linhaPeao][colunaPeao] = ' ';
					board[linhaDestino][colunaDestino] = 'p';
					jogadaValida = true;

					// caso o peao chegue ao outro lado do tabuleiro
					if (linhaDestino == 1){
						cout << "Para que pe�a deseja trocar o pe�o?" << endl;
						cout << "1 - Torre" << endl
							 << "2 - Cavalo" << endl
							 << "3 - Bispo" << endl
							 << "4 - Rainha" << endl;
						
						do
						{
							cin >> trocaPeao;
							for(int i = 0;i < trocaPeao.length();i++){
								trocaPeao[i] =	toupper(trocaPeao[i]);
							}
							
							if(trocaPeao == "TORRE" || trocaPeao == "1"){
								idTrocaPeao = 1;
							}else if(trocaPeao == "CAVALO" || trocaPeao == "2"){
								idTrocaPeao = 2;
							}else if(trocaPeao == "BISPO"|| trocaPeao == "3"){
								idTrocaPeao = 3;
							}else if(trocaPeao == "RAINHA" || trocaPeao == "4"){
								idTrocaPeao = 4;
							}else{
								idTrocaPeao = 5;
							}
							
							switch(idTrocaPeao){
								case 1:board[linhaDestino][colunaDestino] = 't';break;
								case 2:board[linhaDestino][colunaDestino] = 'c';break;
								case 3:board[linhaDestino][colunaDestino] = 'b';break;
								case 4:board[linhaDestino][colunaDestino] = 'q';break;
								default: cout << "Pe�a invalida" << endl;break;
							}
							
						} while (idTrocaPeao > 4);
					}	
				}
				// se tiver uma pe�a na frente, a jogada n�o � valida
				else if (linhaDestino == linhaPeao - 1 && colunaDestino == colunaPeao && board[linhaDestino][colunaDestino] != ' '){
					cout << "Movimento invalida, tem uma pe�a no lugar" << endl;
					jogadaValida = false;

					
				}
				// verifica se a captura diagonal � permitida
				else if (linhaDestino == linhaPeao - 1 && abs(colunaDestino - colunaPeao) == 1 && board[linhaDestino][colunaDestino] != ' '){
					for (int i = 0; i < sizeof(pecasPretas); i++){
						if (board[linhaDestino][colunaDestino] == pecasPretas[i]){
							board[linhaPeao][colunaPeao] = ' ';
							board[linhaDestino][colunaDestino] = 'p';
							jogadaValida = true;
							break;
						}
						else{
							cout << "Movimento invalido, a pe�a em sua diagonal � uma pe�a do seu time" << endl;
							jogadaValida = false;
							break;
						}
					}
				}
				
				// verifica se o movimento escolhido  invalido
				else if (linhaDestino < (linhaPeao - 2) || (linhaPeao != 7 && linhaDestino < linhaPeao - 1))
				{
					cout << "Movimento invalido, lugar de destino invalido para o pe�o" << endl;
					jogadaValida = false;
				}
				// verifica se esta se movimentando para frente
				else if (colunaDestino != colunaPeao && linhaDestino != linhaPeao || linhaDestino > linhaPeao){
					cout << "Movimento invalido, n�o pode andar em diagonal ou para tras" << endl;
					jogadaValida = false;
				}
				
				//verifica se n�o est� se movimentando para o lugar que est�
				else if(colunaDestino == colunaPeao && linhaDestino == linhaPeao){
					cout<<"Movimento invalido, voce ja est� no lugar de destino"<<endl;
					jogadaValida = false;
					
				}
				
				//verifica se n�o est� andando na vertical
				else if(colunaDestino != colunaPeao && linhaPeao == linhaDestino){
					cout<<"Movimento invalido, n�o pode mover na vertical"<<endl;
					jogadaValida = false;
				}
				
				else{
					board[linhaPeao][colunaPeao] = ' ';
					board[linhaDestino][colunaDestino] = 'p';
					jogadaValida = true;
				}
			} while (jogadaValida == false);
		}
	}

	// pretas
	else
	{
		do{
			cont = 1;
			for (int i = 0; i < 9; i++){
				for (int j = 0; j < 9; j++){
					if (board[i][j] == 'P'){
						char letraCol = board[0][j];
						cout << cont << " - " << i << letraCol << endl;
						cont++;
					}
				}
			}

			cin >> cordenadaPeao;
			for (int i = 0; i < cordenadaPeao.length(); i++){
				cordenadaPeao[i] = toupper(cordenadaPeao[i]);
			}
			
			//caso o usuario deseja trocar de pe�a
			if (cordenadaPeao == "VOLTAR"){
				jogadaValida = false;
				break;
			}

			linhaPeao = cordenadaPeao[0] - '0';
			colunaPeao = cordenadaPeao[1] - 'A' + 1;

			// verifica se tem um peao na posicao certa
			if (board[linhaPeao][colunaPeao] != 'P'){
				cout << "Posi��o invalida, n�o h� um pe�a na posi��o " << cordenadaPeao << endl;
				jogadaValida = false;
			}
			else{
				jogadaValida = true;
			}
		} while (!jogadaValida);

		if (jogadaValida == true){
			do{
				cout << "Para onde deseja mover o pe�o" << cordenadaPeao << "?" << endl;
				cin >> movimento;
				
				for (int i = 0; i < movimento.length(); i++){
					movimento[i] = toupper(movimento[i]);
				}
				
				//caso o usuarioi deseja trocar de pe�a
				if (movimento == "VOLTAR"){
					jogadaValida = false;
					break;
				}
				
				linhaDestino = movimento[0] - '0';
				colunaDestino = movimento[1] - 'A' + 1;

				// verifica se h� uma pe�a diretamente na frente do pe�o
				if (linhaDestino == linhaPeao + 1 && colunaDestino == colunaPeao && board[linhaDestino][colunaDestino] == ' '){
					board[linhaPeao][colunaPeao] = ' ';
					board[linhaDestino][colunaDestino] = 'P';
					jogadaValida = true;

					// caso o peao chegue ao outro lado do tabuleiro
					if (linhaDestino == 8)
					{
						cout << "Para que pe�a deseja trocar o pe�o?" << endl;
						cout << "1 - Torre" << endl
							 << "2 - Cavalo" << endl
							 << "3 - Bispo" << endl
							 << "4 - Rainha" << endl;

						do
						{
							cin >> trocaPeao;
							
							for(int i = 0;i < trocaPeao.length();i++){
								trocaPeao[i] = toupper(trocaPeao[i]);
							}
							
							if(trocaPeao == "TORRE" || trocaPeao == "1"){
								idTrocaPeao = 1;
							}else if(trocaPeao == "CAVALO" || trocaPeao == "2"){
								idTrocaPeao = 2;
							}else if(trocaPeao == "BISPO"|| trocaPeao == "3"){
								idTrocaPeao = 3;
							}else if(trocaPeao == "RAINHA" || trocaPeao == "4"){
								idTrocaPeao = 4;
							}else{
								idTrocaPeao = 5;
							}
							
							switch(idTrocaPeao){
								case 1:board[linhaDestino][colunaDestino] = 'T';break;
								case 2:board[linhaDestino][colunaDestino] = 'C';break;
								case 3:board[linhaDestino][colunaDestino] = 'B';break;
								case 4:board[linhaDestino][colunaDestino] = 'Q';break;
								default: cout << "Pe�a invalida" << endl;break;
							}
							
						} while (idTrocaPeao > 4);
					}
					// se tiver uma pe�a na frente, a jogada n�o � valida
				}
				else if (linhaDestino == linhaPeao + 1 && colunaDestino == colunaPeao && board[linhaDestino][colunaDestino] != ' ')
				{
					cout << "Movimento invalido, tem uma pe�a no lugar" << endl;
					jogadaValida = false;

					// verifica se a captura diagonal � permitida
				}
				else if (linhaDestino == linhaPeao + 1 && abs(colunaDestino - colunaPeao) == 1 && board[linhaDestino][colunaDestino] != ' ')
				{
					for (int i = 0; i < sizeof(pecasBrancas); i++)
					{
						if (board[linhaDestino][colunaDestino] == pecasBrancas[i])
						{
							board[linhaPeao][colunaPeao] = ' ';
							board[linhaDestino][colunaDestino] = 'P';
							jogadaValida = true;
							break;
						}
						else
						{
							cout << "Movimento invalido, a pe�a em sua diagonal � uma pe�a do seu time" << endl;
							jogadaValida = false;
							break;
						}
					}
				}
				// verificar se o movimento � valido
				else if (linhaDestino > (linhaPeao + 2) || linhaPeao != 2 && (linhaDestino > linhaPeao + 1)){
					cout << "Movimento invalido, lugar de destino invalido para o pe�o" << endl;
					jogadaValida = false;
				}
				
				// verifica se esta se movimentando para frente
				else if (colunaDestino != colunaPeao && linhaDestino != linhaPeao || linhaDestino < linhaPeao){
					cout << "Movimento invalido, n�o pode andar em diagonal ou para tras" << endl;
					jogadaValida = false;
				}
				
				//verifica se j� n�o est� no lugar de destino
				else if(colunaDestino == colunaPeao && linhaDestino == linhaPeao){
					cout<<"Movimento invalido, voce ja est� no lugar de destino"<<endl;
					jogadaValida = false;
					
				}
				
				//verifica se n�o est� se movimentando na vertical
				else if (colunaDestino != colunaPeao && linhaDestino == linhaPeao){
					cout<<"Movimento invalido, n�o pode mover na vertical"<<endl;
					jogadaValida = false;
				}
				
				else{
					board[linhaPeao][colunaPeao] = ' ';
					board[linhaDestino][colunaDestino] = 'P';
					jogadaValida = true;
				}
				
				cout<<endl<<endl<<endl;
			} while (jogadaValida == false);
		}
	}
}

void escolherPeca()
{
	setlocale(LC_ALL, "Portuguese");

	string nomePeca = "";
	int idPeca = 0;
	bool pecaValida = true;

	do{
		cout << endl<< endl<< endl;
		cout << "Qual pe�a deseja jogar?" << endl;
		cin >> nomePeca;
		cout << "Pe�a escolhida: " << nomePeca << endl<< endl;

		for (int i = 0; i < nomePeca.length(); i++){
			nomePeca[i] = toupper(nomePeca[i]);
		}

		if (nomePeca == "PEAO"){
			pecaValida = true;
			peao();
		}
		else if (nomePeca == "CAVALO"){
			pecaValida = true;
			cavalo();
		}
		else if (nomePeca == "BISPO"){
			pecaValida = true;
			bispo();
		}
		else if (nomePeca == "TORRE"){
			pecaValida = true;
			torre();
		}
		else if (nomePeca == "RAINHA"){
			pecaValida = true;
			rainha();
		}
		else if (nomePeca == "REI")	{
			pecaValida = true;
			rei();
		}
		else{
			cout << "Pe�a invalida" << endl;
			pecaValida = false;
		}
	} while (!pecaValida);
}

int main(){
	string tutorial = "";
	vezJogador = "Vez das pe�as brancas";

	setlocale(LC_ALL, "Portuguese");

	cout << "Jogo de Xadrez" << endl << endl<< "Deseja ver um tutorial?" << endl;
	cin >> tutorial;

	for (int i = 0; i < tutorial.length(); i++){
		tutorial[i] = toupper(tutorial[i]);
	}
	
	if (tutorial == "SIM"){
		tutorialJogo();
	}

	// limpar tela
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif

	cout << "As pe�s brancas come�am" << endl;
	while (!gameOver){
		do
		{
			exibeTab();
			escolherPeca();

			// limpar tela
			#ifdef _WIN32
			system("cls");
			#else
			system("clear");
			#endif
		} while (!jogadaValida);
		temRei();

		// limpar tela
		#ifdef _WIN32
		system("cls");
		#else
		system("clear");
		#endif

		if (!temRei()){
			gameOver = true;
			break;
		}
		else if (jogadaValida){
			trocaJogador();
		}
	}

	if (vezJogador == "Vez das pe�as brancas" && gameOver){
		exibeTab();
		cout <<endl<<endl<<"As pe�as brancas venceram";
	}
	else{
		exibeTab();
		cout <<endl<<endl<< "As pe�as pretas venceram";
	}

	return 0;
}
