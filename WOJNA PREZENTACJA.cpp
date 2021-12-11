#include <iostream>
#include <time.h>
#include<stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;
const int S = 52;
void pushqueue(int card, char player, int* SizeOfHandA, int* SizeOfHandB, int* tailA, int* tailB, int handA[], int handB[], int* SIZE)
{
	if (player == 'A')
	{
		handA[*tailA] = card; //wkładam karte podspód talii
		*tailA = (*tailA + 1) % *SIZE; //osatnie miejsce w talii zwiększa swój indeks
		*SizeOfHandA = *SizeOfHandA + 1;
	}
	else
	{
		handB[*tailB] = card;
		*tailB = (*tailB + 1) % *SIZE;
		*SizeOfHandB = *SizeOfHandB + 1;
	}
}
int popqueue(char player, int* headA, int* headB, int* SizeOfHandA, int* SizeOfHandB, int* tailA, int* tailB, int handA[], int handB[], int* SIZE)
{
	int card = 0;
	if (player == 'A')
	{
		card = handA[*headA]; //wyjmuje karte z góry talii
		*headA = (*headA + 1) % *SIZE; //pierwsze miejsce w talii zwiększa swój indeks
		*SizeOfHandA = *SizeOfHandA - 1;
	}
	else
	{
		card = handB[*headB];
		*headB = (*headB + 1) % *SIZE;
		*SizeOfHandB = *SizeOfHandB - 1;
	}
	return card;
}
void pushstack(int card, char player, int* SizeOfStackA, int* SizeOfStackB, int stackB[], int stackA[])
{
	if (player == 'A')
	{
		*SizeOfStackA = *SizeOfStackA + 1; //stos wojny zwiększa się
		stackA[*SizeOfStackA] = card; //na stosie wojny ląduje karta
	}
	else
	{
		*SizeOfStackB = *SizeOfStackB + 1;
		stackB[*SizeOfStackB] = card;
	}
}
int popstack(char player, int* SizeOfStackA, int* SizeOfStackB, int stackB[], int stackA[])
{
	int card;
	if (player == 'A')
	{
		card = stackA[*SizeOfStackA]; // wyjmuje karte z szczytu stosu wojny
		stackA[*SizeOfStackA] = 0; //czyszcze stos
		*SizeOfStackA = *SizeOfStackB - 1; //zmniejszam wielkość stosu wojny
	}
	else
	{
		card = stackB[*SizeOfStackB];
		stackB[*SizeOfStackB];
		*SizeOfStackB = *SizeOfStackB - 1;
	}
	return card;
}
void shuffle(int* SizeOfHandA, int* SizeOfHandB, int* tailA, int* tailB, int handA[], int handB[], int deck[], int* SIZE)
{
	int i = 0, j = 0, p = 0;
	while (i < *SIZE) //tasowanie talii
	{
		if (*SIZE == 20)
			deck[i] = rand() % 20 + 32;
		else if (*SIZE == 24)
			deck[i] = rand() % 24 + 28;
		else if (*SIZE == 28)
			deck[i] = rand() % 28 + 24;
		else if (*SIZE == 32)
			deck[i] = rand() % 32 + 20;
		else if (*SIZE == 36)
			deck[i] = rand() % 36 + 16;
		else if (*SIZE == 40)
			deck[i] = rand() % 40 + 12;
		else if (*SIZE == 44)
			deck[i] = rand() % 44 + 8;
		else if (*SIZE == 48)
			deck[i] = rand() % 48 + 4;
		else if (*SIZE == 52)
			deck[i] = rand() % 52;

		for (int j = 0; j < i; j++)
		{
			if (deck[i] == deck[j]) //ponowne losowanie karty w przypadku powtórzenia
			{
				i--;
				break;
			}
		}
		i++;
	}
	for (int k = 0; k < *SIZE; k++) //rozdawanie kart do rąk
	{
		if (k % 2 == 0)
			pushqueue(deck[k], 'A', SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
		else
			pushqueue(deck[k], 'B', SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
	}
}
void war(int* headA, int* headB, int* SizeOfHandA, int* SizeOfHandB, int* tailA, int* tailB, int* SizeOfStackA, int* SizeOfStackB, int* warlength, int stackB[], int stackA[], int handA[], int handB[], bool* mode, int* SIZE,int*turncount)
{
	int C, D;
	bool secondwar = false;
	if (*mode == true)
	{
		if (*SizeOfHandA == 2)
		{
			for (int i = 0; i < 2; i++)
			{
				C = popqueue('A', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE); // gracz A wykłada karte
				D = popqueue('B', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);// gracz B wykłada karte
				pushstack(C, 'A', SizeOfStackA, SizeOfStackB, stackB, stackA);
				pushstack(D, 'B', SizeOfStackA, SizeOfStackB, stackB, stackA);
			}
			D = popqueue('B', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE); // gracz B wykłada karte graczowi A
			pushstack(D, 'A', SizeOfStackA, SizeOfStackB, stackB, stackA); //najpierw stos A
			C = popqueue('B', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE); // gracz B wykłada sobie karte
			pushstack(D, 'B', SizeOfStackA, SizeOfStackB, stackB, stackA); //potem stos B
			secondwar = true;
		}
		else if (*SizeOfHandA == 1)
		{
			C = popqueue('A', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
			D = popqueue('B', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
			pushstack(C, 'A', SizeOfStackA, SizeOfStackB, stackB, stackA);
			pushstack(D, 'B', SizeOfStackA, SizeOfStackB, stackB, stackA);
			for (int i = 0; i < 2; i++)
			{
				D = popqueue('B', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE); // gracz B wykłada karte graczowi A
				pushstack(D, 'A', SizeOfStackA, SizeOfStackB, stackB, stackA);
			}
			for (int i = 0; i < 2; i++)
			{
				D = popqueue('B', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);  // gracz B wykłada sobie karte
				pushstack(D, 'B', SizeOfStackA, SizeOfStackB, stackB, stackA);
			}
			secondwar = true;
		}
		else if (*SizeOfHandB == 2) // ta sama sytuacja co powyżej tylko na odwrót
		{
			for (int i = 0; i < 2; i++)
			{

				C = popqueue('A', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
				D = popqueue('B', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
				pushstack(C, 'A', SizeOfStackA, SizeOfStackB, stackB, stackA);
				pushstack(D, 'B', SizeOfStackA, SizeOfStackB, stackB, stackA);
			}
			D = popqueue('A', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
			pushstack(D, 'B', SizeOfStackA, SizeOfStackB, stackB, stackA); //najpierw stos B
			C = popqueue('A', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
			pushstack(C, 'A', SizeOfStackA, SizeOfStackB, stackB, stackA); //potem stos A
			secondwar = true;
		}
		else if (*SizeOfHandB == 1)
		{
			C = popqueue('A', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
			D = popqueue('B', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
			pushstack(C, 'A', SizeOfStackA, SizeOfStackB, stackB, stackA);
			pushstack(D, 'B', SizeOfStackA, SizeOfStackB, stackB, stackA);
			for (int i = 0; i < 2; i++)
			{
				D = popqueue('A', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
				pushstack(D, 'B', SizeOfStackA, SizeOfStackB, stackB, stackA);
			}
			for (int i = 0; i < 2; i++)
			{
				D = popqueue('A', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
				pushstack(D, 'A', SizeOfStackA, SizeOfStackB, stackB, stackA);
			}
			secondwar = true;
		}
		else //standardowa wojna
		{
			for (int i = 0; i < 3; i++)
			{
				if ((*SizeOfHandA < 0) || (*SizeOfHandB < 0))
				{
					if (*SizeOfHandA > 0)
					{
						cout << endl << "PLAYER A IS THE WINNER !" << endl << "Game lasted " << *turncount + 1 << " rounds" << endl;
						exit(EXIT_FAILURE);
					}
					else
					{
						cout << endl << "PLAYER B IS THE WINNER !" << endl << "Game lasted " << *turncount + 1 << " rounds" << endl;
						exit(EXIT_FAILURE);
					}
				}
				C = popqueue('A', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
				D = popqueue('B', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
				pushstack(C, 'A', SizeOfStackA, SizeOfStackB, stackB, stackA);
				pushstack(D, 'B', SizeOfStackA, SizeOfStackB, stackB, stackA);
			}
		}
	}
	else if (*mode == false)
	{
		for (int i = 0; i < 3; i++)
		{
			C = popqueue('A', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
			D = popqueue('B', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
			pushstack(C, 'A', SizeOfStackA, SizeOfStackB, stackB, stackA);
			pushstack(D, 'B', SizeOfStackA, SizeOfStackB, stackB, stackA);
		}
	}
	if ((stackA[*SizeOfStackA] / 4) > (stackB[*SizeOfStackB] / 4)) //gracz A wygrał wojne
	{
		for (int i = 0; i < *warlength; i++)
		{
			C = popstack('A', SizeOfStackA, SizeOfStackB, stackB, stackA);
			D = popstack('B', SizeOfStackA, SizeOfStackB, stackB, stackA);
			pushqueue(C, 'A', SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
			pushqueue(D, 'A', SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
		}
	}
	else if ((stackB[*SizeOfStackB] / 4) > (stackA[*SizeOfStackA] / 4)) //gracz B wygrał wojne
	{
		for (int i = 0; i < *warlength; i++)
		{
			C = popstack('A', SizeOfStackA, SizeOfStackB, stackB, stackA);
			D = popstack('B', SizeOfStackA, SizeOfStackB, stackB, stackA);
			pushqueue(D, 'B', SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
			pushqueue(C, 'B', SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
		}
	}
	else
	{
		if (secondwar == true) // kiedy wchodzimy do wojny w wojnie w wariancie B, gra się kończy
		{
			if (*SizeOfHandA > 0)
			{
				cout << endl << "PLAYER A IS THE  WINNER !" << endl << "Game lasted " << *turncount + 1 << " rounds" << endl;
				exit(EXIT_FAILURE);
			}
			else
			{
				cout << endl << "PLAYER B IS THE  WINNER !" << endl << "Game lasted " << *turncount + 1 << " rounds" << endl;
				exit(EXIT_FAILURE);
			}
		}
		*warlength += 3; //wojna wydłuża się o kolejne 2 karty
		war(headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, SizeOfStackA, SizeOfStackB, warlength, stackB, stackA, handA, handB, mode, SIZE,turncount);
	}
	*warlength = 3; // ustawianie zmiennej na domyślną wartość
}
void duel(int* headA, int* headB, int* SizeOfHandA, int* SizeOfHandB, int* tailA, int* tailB, int* SizeOfStackA, int* SizeOfStackB, int* warlength, int stackB[], int stackA[], int handA[], int handB[], bool* mode, int* SIZE,int*turncount)
{
	int A, B;
	if (handA[*headA] / 4 > handB[*headB] / 4)
	{
		A = popqueue('A', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
		B = popqueue('B', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
		pushqueue(A, 'A', SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
		pushqueue(B, 'A', SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
	}
	else if (handB[*headB] / 4 > handA[*headA] / 4)
	{
		A = popqueue('A', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
		B = popqueue('B', headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
		pushqueue(B, 'B', SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);
		pushqueue(A, 'B', SizeOfHandA, SizeOfHandB, tailA, tailB, handA, handB, SIZE);

	}
	else
	{
		war(headA, headB, SizeOfHandA, SizeOfHandB, tailA, tailB, SizeOfStackA, SizeOfStackB, warlength, stackB, stackA, handA, handB, mode, SIZE,turncount);
	}

}
void hands_status(int* headA, int* headB, int* SizeOfHandA, int* SizeOfHandB, int handA[], int handB[], int* SIZE)
{
	int indexA=0, indexB=0,cardnumber=0;
	char figure[] = { '2','3','4','5','6','7','8','9','10','J','Q','K','A' };
	char color[] = { 'C','D','H','S' };
	cout << endl << "Players A hand is : ";
	for (int i = 0; i < *SizeOfHandA; i++)
	{
		indexA = *headA + i;
		if (*headA + i >= *SIZE)
			indexA = (*headA + i) - *SIZE; //warunek naprawiający wychodzenie poza zakres tablicy
		cardnumber = handA[indexA];
		if (cardnumber / 4 == 8)
			cout << 10 << color[cardnumber % 4] << " "; //10 jest zapisana na 2 znakach co powoduje problem przy wypisywaniu, dlatego konieczny jest ten warunek
		else
			cout << figure[cardnumber / 4] << color[cardnumber % 4] << " ";
	}
	cout << endl << "Players B hand is : ";
	for (int i = 0; i < *SizeOfHandB; i++)
	{
		indexB = *headB + i;
		if (*headB + i >= *SIZE)
			indexB = (*headB + i) - *SIZE;
		cardnumber = handB[indexB];
		if (cardnumber / 4 == 8)
			cout << 10 << color[cardnumber % 4] << " "; //10 jest zapisana na 2 znakach co powoduje problem przy wypisywaniu, dlatego konieczny jest ten warunek
		else
			cout << figure[cardnumber / 4] << color[cardnumber % 4] << " ";
	}
	cout << endl;
}
int handpower(char player, int* decksize, int handA[], int handB[])
{
	int power = 0;
	for (int i = 0; i < *decksize / 2; i++)
	{
		if (player == 'A')
			power += handA[i] / 4;
		else
			power += handB[i] / 4;
	}
	return power;
}
int main()
{
	srand(time(NULL));
	bool mode;//wariant A = false, B = true
	int headofhandA = 0, headofhandB = 0, decksize = 0, sizeofqueueA = 0, sizeofqueueB = 0, tailofhandA = 0, tailofhandB = 0, sizeofstackA = 0, sizeofstackB = 0, warlength = 3, turncount = 0;
	int stackB[S] = {}, stackA[S] = {}, handA[S] = {}, handB[S] = {}, deck[S] = {};
	char deckchoose, modechoose;
	for (int i = 0; i < 38; i++)
	{
		cout << '-';
	}
	cout << "WAR THE CARD GAME ";
	for (int i = 0; i < 38; i++)
	{
		cout << '-';
	}
	cout << endl<<"CHOOSE GAME MODE :"<<endl<<"A. NORMAL"<<endl<<"B. ALTERNATIVE"<<endl;
	cin >> modechoose;
	if (modechoose == 'A')
		mode = false;
	else if (modechoose == 'B')
		mode = true;
	cout << "CHOOSE A DECK SIZE :" << endl << "A. 52" << endl << "B. 48" <<endl<< "C. 44" << endl << "D. 40" <<endl<< "E. 36" << endl << "F. 32" <<endl<< "G. 28" << endl << "H. 24"<<endl << "I. 20" << endl;
	cin >> deckchoose;
	if (deckchoose == 'A')
		decksize = 52;
	else if (deckchoose == 'B')
		decksize = 48;
	else if (deckchoose == 'C')
		decksize = 44;
	else if (deckchoose == 'D')
		decksize = 40;
	else if (deckchoose == 'E')
		decksize = 36;
	else if (deckchoose == 'F')
		decksize = 32;
	else if (deckchoose == 'G')
		decksize = 28;
	else if (deckchoose == 'H')
		decksize = 24;
	else if (deckchoose == 'I')
		decksize = 20;
	shuffle(&sizeofqueueA, &sizeofqueueB, &tailofhandA, &tailofhandB, handA, handB,deck,&decksize);
	hands_status(&headofhandA,&headofhandB,&sizeofqueueA,&sizeofqueueB, handA, handB,&decksize);
	while (true)
	{
		duel(&headofhandA, &headofhandB, &sizeofqueueA, &sizeofqueueB, &tailofhandA, &tailofhandB, &sizeofstackA, &sizeofstackB, &warlength,stackB, stackA, handA, handB, &mode,&decksize,&turncount);
		if (sizeofqueueA == 0)
		{
			cout << endl << "PLAYER B IS THE WINNER !" << endl << "Game lasted " << turncount + 1 << " rounds" << endl;
			return 0;
		}
		else if(sizeofqueueB == 0)
		{
			cout << endl << "PLAYER A IS THE WINNER !" << endl << "Game lasted " << turncount + 1 << " rounds" << endl;
			return 0;

		}
		hands_status(&headofhandA, &headofhandB, &sizeofqueueA, &sizeofqueueB, handA, handB, &decksize);
		turncount++;
	}
}