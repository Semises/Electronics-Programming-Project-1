#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;
const int W = 8;
//Ilosc pol w wierszu
const int K = 8;
//Ilosc pol w kolumnie
int ktoryruch = 0;
int ktoryruchPC = 0;
bool czyruchwykonany = true;
char punkty[W][K];
char pionki[W][K];
void Przypisanie_wartosci(char[W][K], char[W][K]);
void Game_hub(char[W][K], char[W][K]);
void Game_hubPC(char[W][K], char[W][K]);
int CzyWygralGreGracz(char[W][K]);
int CzyWygralGrePC(char[W][K]);
int Ruch_gracza(char[W][K], char[W][K], int&, bool&);
void Ruch_PC(char[W][K], char[W][K], int&);

main()
{
	Przypisanie_wartosci(punkty, pionki);
	while (true)
	{
		Game_hubPC(punkty, pionki);
		CzyWygralGrePC(pionki);

		if (CzyWygralGrePC(pionki) == 0)
			break;

		Game_hub(punkty, pionki);
		CzyWygralGreGracz(pionki);

		if (CzyWygralGreGracz(pionki) == 0)
			break;
	}

	return 0;
}




int Ruch_gracza(char pun[W][K], char pion[W][K], int &ktoryruch, bool &czyruchwykonany)
{

	ktoryruch++;
	int dodatkowe_punkty = 0;
	char puste_pole = ' ';
	char kolumna;
	int wiersz;
	cout << endl;
	cout << "(Gracz 2 - czarne pionki) (Ruch - " << ktoryruch << ")" << endl;
	cout << "Wpisz numer kolumny i wiersza" << endl;
	cin >> kolumna >> wiersz;


	while (pion[wiersz - 1][kolumna - 65] == 'o')
	{
		cout << "To nie jest Twoj pionek! Sprobuj ponownie" << endl;
		cin >> kolumna >> wiersz;
	}

	while (((kolumna == 'A' || kolumna == 'H') && (wiersz < 3 || wiersz>6)) ||
		((kolumna == 'B' || kolumna == 'G') && (wiersz < 2 || wiersz>7)) ||
		((kolumna == 'C' || kolumna == 'D' || kolumna == 'E' || kolumna == 'F') && (wiersz < 1 || wiersz>8)))

	{
		cout << "To nie jest dozwolone do gry pole! Sprobuj ponownie" << endl;
		cin >> kolumna >> wiersz;
	}

	char obecny_pionek[2][1];
	switch (kolumna)
	{
	case 'A':
		kolumna = 0;
		obecny_pionek[0][0] = pion[wiersz - 1][kolumna];
		obecny_pionek[1][0] = pun[wiersz - 1][kolumna];
		break;

	case 'B':
		kolumna = 1;
		obecny_pionek[0][0] = pion[wiersz - 1][kolumna];
		obecny_pionek[1][0] = pun[wiersz - 1][kolumna];
		break;

	case 'C':
		kolumna = 2;
		obecny_pionek[0][0] = pion[wiersz - 1][kolumna];
		obecny_pionek[1][0] = pun[wiersz - 1][kolumna];
		break;
	case 'D':
		kolumna = 3;
		obecny_pionek[0][0] = pion[wiersz - 1][kolumna];
		obecny_pionek[1][0] = pun[wiersz - 1][kolumna];
		break;
	case 'E':
		kolumna = 4;
		obecny_pionek[0][0] = pion[wiersz - 1][kolumna];
		obecny_pionek[1][0] = pun[wiersz - 1][kolumna];
		break;
	case 'F':
		kolumna = 5;
		obecny_pionek[0][0] = pion[wiersz - 1][kolumna];
		obecny_pionek[1][0] = pun[wiersz - 1][kolumna];
		break;

	case 'G':
		kolumna = 6;
		obecny_pionek[0][0] = pion[wiersz - 1][kolumna];
		obecny_pionek[1][0] = pun[wiersz - 1][kolumna];
		break;

	case 'H':
		kolumna = 7;
		obecny_pionek[0][0] = pion[wiersz - 1][kolumna];
		obecny_pionek[1][0] = pun[wiersz - 1][kolumna];
		break;
	}

	cout << "Jak chcesz ruszyc pionek? Gora (W), Dol (S), Lewo (A), Prawo (D)" << endl;
	char decyzja;
	int oile = 0;
	//Obecna ilosc punktow pionka
	int k = pun[wiersz - 1][kolumna] - 48;
	cin >> decyzja;
	cout << "O ile?" << endl;
	cin >> oile;
	oile = oile + 1;
	while ((decyzja != 'W') && (decyzja != 'S') && (decyzja != 'A') && (decyzja != 'D'))
	{
		cout << "Sprobuj jeszcze raz!" << endl;
		cin >> decyzja;
	}
	while (oile > k + 1)
	{
		oile = 0;
		cout << "Nie mozesz sie o tyle poruszyc! Sprobuj jeszcze raz!" << endl;
		cin >> oile;
		oile = oile + 1;
	}

	if ((decyzja == 'W') && ((wiersz - 1) + oile > 8))
	{
		czyruchwykonany = false;
		return 0;
	}
	if ((decyzja == 'S') && ((wiersz - 1) - oile < 0))
	{
		czyruchwykonany = false;
		return 0;
	}
	if ((decyzja == 'A') && (kolumna - oile < 0))
	{
		czyruchwykonany = false;
		return 0;
	}
	if ((decyzja == 'D') && (kolumna + oile > 8))
	{
		czyruchwykonany = false;
		return 0;
	}
	//Warunek na brak ruchu na niedowolone lub zajete pola przy przemieszczeniu sie w gore
	if ((decyzja == 'W') && ((((wiersz - 1) + oile == 7) && (kolumna == 0)) || (((wiersz - 1) + oile == 6) && (kolumna == 0)) ||
		(((wiersz - 1) + oile == 7) && (kolumna == 1)) || (((wiersz - 1) + oile == 7) && (kolumna == 6)) ||
		(((wiersz - 1) + oile == 7) && (kolumna == 7)) || (((wiersz - 1) + oile == 6) && (kolumna == 7)) || (pion[(wiersz - 1) + oile][kolumna] != puste_pole)))
	{
		czyruchwykonany = false;
		return 0;
	}
	//Warunek na brak ruchu na niedowolone lub zajete pola przy przemieszczeniu sie w dol
	if ((decyzja == 'S') && ((((wiersz - 1) - oile == 1) && (kolumna == 0)) || (((wiersz - 1) - oile == 0) && (kolumna == 0)) ||
		(((wiersz - 1) - oile == 0) && (kolumna == 1)) || (((wiersz - 1) - oile == 1) && (kolumna == 7)) ||
		(((wiersz - 1) - oile == 0) && (kolumna == 6)) || (((wiersz - 1) - oile == 0) && (kolumna == 7)) || (pion[(wiersz - 1) - oile][kolumna] != puste_pole)))
	{
		czyruchwykonany = false;
		return 0;
	}
	//Warunek na brak ruchu na niedowolone lub zajete pola przy przemieszczeniu sie w prawo
	if ((decyzja == 'D') && (((wiersz - 1 == 7) && (kolumna + oile == 6)) || ((wiersz - 1 == 7) && (kolumna + oile == 7)) ||
		((wiersz - 1 == 6) && (kolumna + oile == 7)) || ((wiersz - 1 == 1) && (kolumna + oile == 7)) ||
		((wiersz - 1 == 0) && (kolumna + oile == 7)) || ((wiersz - 1 == 0) && (kolumna + oile == 6)) || (pion[wiersz - 1][kolumna + oile] != puste_pole)))
	{
		czyruchwykonany = false;
		return 0;
	}
	//Warunek na brak ruchu na niedowolone lub zajete pola przy przemieszczeniu sie w lewo
	if ((decyzja == 'A') && (((wiersz - 1 == 7) && (kolumna - oile == 1)) || ((wiersz - 1 == 7) && (kolumna - oile == 0)) ||
		((wiersz - 1 == 6) && (kolumna - oile == 0)) || ((wiersz - 1 == 1) && (kolumna - oile == 0)) ||
		((wiersz - 1 == 0) && (kolumna - oile == 0)) || ((wiersz - 1 == 0) && (kolumna - oile == 1)) || (pion[wiersz - 1][kolumna - oile] != puste_pole)))
	{
		czyruchwykonany = false;
		return 0;
	}

	switch (decyzja)
	{
	case 'W':
		for (int i = 1; i < k + 1; i++)
		{
			if (pion[(wiersz - 1) + i][kolumna] == 'o')
			{
				dodatkowe_punkty++;
				pion[(wiersz - 1) + i][kolumna] = ' ';
				pun[(wiersz - 1) + i][kolumna] = ' ';
			}
		}

		if (pun[wiersz - 1][kolumna] - 48 >= oile)
		{
			pun[(wiersz - 1) + oile][kolumna] = oile + 47;
		}
		else
		{
			pun[(wiersz - 1) + oile][kolumna] = pun[wiersz - 1][kolumna] + dodatkowe_punkty;
		}
		pun[(wiersz - 1)][kolumna] = ' ';
		pion[(wiersz - 1)][kolumna] = ' ';
		pion[(wiersz - 1) + oile][kolumna] = obecny_pionek[0][0];
		break;

	case 'S':
		for (int i = 1; i < k + 1; i++)
		{
			if (pion[(wiersz - 1) - i][kolumna] == 'o')
			{
				dodatkowe_punkty++;
				pion[(wiersz - 1) - i][kolumna] = ' ';
				pun[(wiersz - 1) - i][kolumna] = ' ';
			}
		}

		if (pun[wiersz - 1][kolumna] - 48 >= oile)
		{
			pun[(wiersz - 1) - oile][kolumna] = oile + 47;
		}
		else
		{
			pun[(wiersz - 1) - oile][kolumna] = pun[wiersz - 1][kolumna] + dodatkowe_punkty;
		}
		pun[(wiersz - 1)][kolumna] = ' ';
		pion[(wiersz - 1)][kolumna] = ' ';
		pion[(wiersz - 1) - oile][kolumna] = obecny_pionek[0][0];
		break;

	case 'A':
		for (int i = 1; i < k + 1; i++)
		{
			if (pion[(wiersz - 1)][kolumna - i] == 'o')
			{
				dodatkowe_punkty++;
				pion[(wiersz - 1)][kolumna - i] = ' ';
				pun[(wiersz - 1)][kolumna - i] = ' ';
			}
		}

		if (pun[wiersz - 1][kolumna] - 48 >= oile)
		{
			pun[(wiersz - 1)][kolumna - oile] = oile + 47;
		}
		else
		{
			pun[(wiersz - 1)][kolumna - oile] = pun[wiersz - 1][kolumna] + dodatkowe_punkty;
		}
		pun[(wiersz - 1)][kolumna] = ' ';
		pion[(wiersz - 1)][kolumna] = ' ';
		pion[(wiersz - 1)][kolumna - oile] = obecny_pionek[0][0];
		break;

	case 'D':
		for (int i = 1; i < k + 1; i++)
		{
			if (pion[(wiersz - 1)][kolumna + i] == 'o')
			{
				dodatkowe_punkty++;
				pion[(wiersz - 1)][kolumna + i] = ' ';
				pun[(wiersz - 1)][kolumna + i] = ' ';
			}
		}

		if (pun[wiersz - 1][kolumna] - 48 >= oile)
		{
			pun[(wiersz - 1)][kolumna + oile] = oile + 47;
		}
		else
		{
			pun[(wiersz - 1)][kolumna + oile] = pun[wiersz - 1][kolumna] + dodatkowe_punkty;
		}
		pun[(wiersz - 1)][kolumna] = ' ';
		pion[(wiersz - 1)][kolumna] = ' ';
		pion[(wiersz - 1)][kolumna + oile] = obecny_pionek[0][0];
		break;


	}
}

void Ruch_PC(char pun[W][K], char pion[W][K], int &ktoryruchPC)
{
	ktoryruchPC++;
	char puste_pole = ' ';
	int kolumna = 0;
	int wiersz = 0;
	bool czybylruch = false;
	cout << endl;
	cout << "(Gracz 1 - biale pionki) (Ruch - " << ktoryruchPC << ")" << endl;
	cout << "Wcisnij ENTER, by przejsc do swojego ruchu" << endl;
	getchar();
	getchar();

	do
	{
		srand(time(NULL));
		kolumna = (rand() % 7);
		wiersz = (rand() % 7);

		while ((pion[wiersz][kolumna] == 'x') || ((wiersz == 7) && (kolumna == 0)) || ((wiersz == 7) && (kolumna == 1)) ||
			((wiersz == 7) && (kolumna == 6)) || ((wiersz == 7) && (kolumna == 7)) ||
			((wiersz == 6) && (kolumna == 0)) || ((wiersz == 6) && (kolumna == 7)) || (pion[wiersz][kolumna] == puste_pole) ||
			((wiersz == 1) && (kolumna == 0)) || ((wiersz == 1) && (kolumna == 7)) ||
			((wiersz == 0) && (kolumna == 0)) || ((wiersz == 0) && (kolumna == 1)) ||
			((wiersz == 0) && (kolumna == 6)) || ((wiersz == 0) && (kolumna == 7)))
		{
			kolumna = (rand() % 7);
			wiersz = (rand() % 7);
		}

		char punkty = pun[wiersz][kolumna];
		int skok = punkty - '0';
		skok = skok + 1;
		char bialy_pionek = 'o';
		int dodatkowe_punkty = 0;
		for (int i = 1; i < skok; i++)
		{
			if (wiersz + skok < 8)
			{
				if (pion[wiersz + skok][kolumna] == ' ')
				{
					for (int j = 1; j < skok; j++)
					{
						if (pion[wiersz + j][kolumna] == 'x')
						{
							dodatkowe_punkty++;
							pion[wiersz + j][kolumna] = ' ';
							pun[wiersz + j][kolumna] = ' ';
						}
					}
					if (pun[wiersz][kolumna] - 48 >= skok)
					{
						pun[wiersz + skok][kolumna] = skok + 47;
					}
					else
					{
						pun[wiersz + skok][kolumna] = pun[wiersz][kolumna] + dodatkowe_punkty;
					}
					pun[wiersz][kolumna] = ' ';
					pion[wiersz][kolumna] = ' ';
					pion[wiersz + skok][kolumna] = bialy_pionek;
					czybylruch = true;
				}
			}
			if (czybylruch == true)
				break;
			if (wiersz - skok > 0)
			{
				if (pion[wiersz - skok][kolumna] == ' ')
				{
					for (int j = 1; j < skok; j++)
					{
						if (pion[wiersz - j][kolumna] == 'x')
						{
							dodatkowe_punkty++;
							pion[wiersz - j][kolumna] = ' ';
							pun[wiersz - j][kolumna] = ' ';
						}
					}
					if (pun[wiersz][kolumna] - 48 >= skok)
					{
						pun[wiersz - skok][kolumna] = skok + 47;
					}
					else
					{
						pun[wiersz - skok][kolumna] = pun[wiersz][kolumna] + dodatkowe_punkty;
					}
					pun[wiersz][kolumna] = ' ';
					pion[wiersz][kolumna] = ' ';
					pion[wiersz - skok][kolumna] = bialy_pionek;
					czybylruch = true;

				}
			}
			if (czybylruch == true)
				break;
			if (kolumna + skok < 8)
			{
				if (pion[wiersz][kolumna + skok] == ' ')
				{
					for (int j = 1; j < skok; j++)
					{
						if (pion[wiersz][kolumna + j] == 'x')
						{
							dodatkowe_punkty++;
							pion[wiersz][kolumna + j] = ' ';
							pun[wiersz][kolumna + j] = ' ';
						}
					}
					if (pun[wiersz][kolumna] - 48 >= skok)
					{
						pun[wiersz][kolumna] = skok + 47;
					}
					else
					{
						pun[wiersz][kolumna + skok] = pun[wiersz][kolumna] + dodatkowe_punkty;
					}
					pun[wiersz][kolumna] = ' ';
					pion[wiersz][kolumna] = ' ';
					pion[wiersz][kolumna + skok] = bialy_pionek;
					czybylruch = true;

				}
			}
			if (czybylruch == true)
				break;
			if (kolumna - skok > 0)
			{
				if (pion[wiersz][kolumna - skok] == ' ')
				{
					for (int j = 1; j < skok; j++)
					{
						if (pion[wiersz][kolumna - j] == 'x')
						{
							dodatkowe_punkty++;
							pion[wiersz][kolumna - j] = ' ';
							pun[wiersz][kolumna - j] = ' ';
						}
					}
					if (pun[wiersz][kolumna] - 48 >= skok)
					{
						pun[wiersz][kolumna] = skok + 47;
					}
					else
					{
						pun[wiersz][kolumna - skok] = pun[wiersz][kolumna] + dodatkowe_punkty;
					}
					pun[wiersz][kolumna] = ' ';
					pion[wiersz][kolumna] = ' ';
					pion[wiersz][kolumna - skok] = bialy_pionek;
					czybylruch = true;

				}
			}
		}

	} while (czybylruch == false);
}
void Game_hub(char tab1[W][K], char tab2[W][K])
{
	//Wywolanie planszy z wartosciami
	cout << 8 << "  ---  --- | " << tab2[7][2] << tab1[7][2] << " | " << tab2[7][3] << tab1[7][3] << " | ";
	cout << tab2[7][4] << tab1[7][4] << " | " << tab2[7][5] << tab1[7][5] << " | ---  ---" << endl;
	for (int i = 8; i >= 3; i--)
	{
		if (i == 8 || i == 3)
		{
			cout << i - 1 << "  --- | " << tab2[i - 2][1] << tab1[i - 2][1] << " | " << tab2[i - 2][2] << tab1[i - 2][2] << " | ";
			cout << tab2[i - 2][3] << tab1[i - 2][3] << " | " << tab2[i - 2][4] << tab1[i - 2][4] << " | " << tab2[i - 2][5] << tab1[i - 2][5] << " | ";
			cout << tab2[i - 2][6] << tab1[i - 2][6] << " | ---" << endl;
		}

		if (i >= 4 && i <= 7)
		{
			cout << i - 1 << " | " << tab2[i - 2][0] << tab1[i - 2][0] << " | " << tab2[i - 2][1] << tab1[i - 2][1] << " | ";
			cout << tab2[i - 2][2] << tab1[i - 2][2] << " | " << tab2[i - 2][3] << tab1[i - 2][3] << " | " << tab2[i - 2][4] << tab1[i - 2][4] << " | ";
			cout << tab2[i - 2][5] << tab1[i - 2][5] << " | " << tab2[i - 2][6] << tab1[i - 2][6] << " | " << tab2[i - 2][7] << tab1[i - 2][7] << " |" << endl;
		}
	}
	cout << 1 << "  ---  --- | " << tab2[0][2] << tab1[0][2] << " | " << tab2[0][3] << tab1[0][3] << " | ";
	cout << tab2[0][4] << tab1[0][4] << " | " << tab2[0][5] << tab1[0][5] << " | ---  ---" << endl;
	cout << "   A    B     C    D    E    F    G    H " << endl;
	do
	{
		Ruch_gracza(tab1, tab2, ktoryruch, czyruchwykonany);
	} while (czyruchwykonany != true);
	system("CLS");
}

void Game_hubPC(char tab1[W][K], char tab2[W][K])
{
	//Wywolanie planszy z wartosciami
	cout << 8 << "  ---  --- | " << tab2[7][2] << tab1[7][2] << " | " << tab2[7][3] << tab1[7][3] << " | ";
	cout << tab2[7][4] << tab1[7][4] << " | " << tab2[7][5] << tab1[7][5] << " | ---  ---" << endl;
	for (int i = 8; i >= 3; i--)
	{
		if (i == 8 || i == 3)
		{
			cout << i - 1 << "  --- | " << tab2[i - 2][1] << tab1[i - 2][1] << " | " << tab2[i - 2][2] << tab1[i - 2][2] << " | ";
			cout << tab2[i - 2][3] << tab1[i - 2][3] << " | " << tab2[i - 2][4] << tab1[i - 2][4] << " | " << tab2[i - 2][5] << tab1[i - 2][5] << " | ";
			cout << tab2[i - 2][6] << tab1[i - 2][6] << " | ---" << endl;
		}

		if (i >= 4 && i <= 7)
		{
			cout << i - 1 << " | " << tab2[i - 2][0] << tab1[i - 2][0] << " | " << tab2[i - 2][1] << tab1[i - 2][1] << " | ";
			cout << tab2[i - 2][2] << tab1[i - 2][2] << " | " << tab2[i - 2][3] << tab1[i - 2][3] << " | " << tab2[i - 2][4] << tab1[i - 2][4] << " | ";
			cout << tab2[i - 2][5] << tab1[i - 2][5] << " | " << tab2[i - 2][6] << tab1[i - 2][6] << " | " << tab2[i - 2][7] << tab1[i - 2][7] << " |" << endl;
		}
	}
	cout << 1 << "  ---  --- | " << tab2[0][2] << tab1[0][2] << " | " << tab2[0][3] << tab1[0][3] << " | ";
	cout << tab2[0][4] << tab1[0][4] << " | " << tab2[0][5] << tab1[0][5] << " | ---  ---" << endl;
	cout << "   A    B     C    D    E    F    G    H " << endl;
	Ruch_PC(tab1, tab2, ktoryruchPC);
	system("CLS");
}


void Przypisanie_wartosci(char tab1[W][K], char tab2[W][K])
{
	//Przypisanie wartosci do planszy
	for (int i = 6; i >= 1; i--)
	{
		for (int j = 1; j < 7; j++)
		{
			tab1[i][j] = '1';
			if (i % 2 == 0)
			{
				if (j == 1 || j == 2 || j == 5 || j == 6)
				{
					tab2[i][j] = 'x';
				}
				else
				{
					tab2[i][j] = 'o';
				}
			}
			else
			{
				if (j == 1 || j == 2 || j == 5 || j == 6)
				{
					tab2[i][j] = 'o';
				}
				else
				{
					tab2[i][j] = 'x';
				}

			}
		}
	}
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < 8; j++)
		{

			if ((i == 7) || (i == 0) || (j == 0) || (j == 7))
			{
				tab1[i][j] = ' ';
				tab2[i][j] = ' ';
			}
			if (((i == 7) && (j == 0)) || ((i == 6) && (j == 0)) ||
				((i == 7) && (j == 1)) || ((i == 7) && (j == 6)) ||
				((i == 7) && (j == 7)) || ((i == 6) && (j == 7)) ||
				((i == 1) && (j == 0)) || ((i == 0) && (j == 0)) ||
				((i == 0) && (j == 1)) || ((i == 1) && (j == 7)) ||
				((i == 0) && (j == 6)) || ((i == 0) && (j == 7)))
			{
				tab1[i][j] = 'p';
				tab2[i][j] = 'p';
			}
		}
	}
}

int CzyWygralGreGracz(char tab[W][K])
{
	int czywygral = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (tab[i][j] == 'o')
				czywygral++;
		}
	}
	if (czywygral == 0)
	{
		cout << "Gratulacje! Gre wygral gracz 2" << endl;
		return 0;
	}
}

int CzyWygralGrePC(char tab[W][K])
{
	int czywygral = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (tab[i][j] == 'x')
				czywygral++;
		}
	}
	if (czywygral == 0)
	{
		cout << "Gratulacje! Gre wygral gracz 1" << endl;
		return 0;
	}
}
