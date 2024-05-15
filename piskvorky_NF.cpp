#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h> //pro barvy

using namespace std;

bool remiza(char pole_znaku[9]);
bool vyhra_horizontal(int hrac, char pole_znaku[9]);
bool vyhra_vertical(int hrac, char pole_znaku[9]);
bool vyhra_diagonal(int hrac, char pole_znaku[9]);
int vyhra(int hrac, char pole_znaku[9]);
bool vyhra_bot(int hrac, char pole_znaku[9]);

int menu();
void hrac(int hrac, char pole_znaku[9]);
void vypis_desky(char pole_znaku[9]);
void robot(int robot, char pole_znaku[9]);
char hraci_znaky(int hrac);

void logo_piskvorky();
void barva(int barvicka);

int main()
{
    char pole_znaku[9];
    int uzivatel_vyber = 0;
    int vyhra_cislo = 1;
    bool reset_hry = true;

    srand(time(0));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    do
    {
        logo_piskvorky();

        // nastavi prazdny pole
        for (int i = 0; i < 9; i++)
        {
            pole_znaku[i] = ' ';
        }

        do
        {
            uzivatel_vyber = menu();
        } while (uzivatel_vyber < 1 || uzivatel_vyber > 4);

        if (uzivatel_vyber == 1)
        {
            // hraje hrac, zkontroluje vyhru, pripadne ukonci hru
            barva(11);
            cout << "--Hrac vs Hrac--\n";
            vypis_desky(pole_znaku);

            while (1)
            {
                hrac(1, pole_znaku);
                vyhra_cislo = vyhra(1, pole_znaku);

                if (vyhra_cislo == 0)
                {
                    break;
                }

                hrac(2, pole_znaku);
                vyhra_cislo = vyhra(2, pole_znaku);

                if (vyhra_cislo == 0)
                {
                    break;
                }
            }
        }

        else if (uzivatel_vyber == 2)
        {
            // hraje hrac nebo robot, zkontroluje vyhru, pripadne ukonci hru
            barva(11);
            cout << "Hrac vs Robot\n";
            vypis_desky(pole_znaku);

            while (1)
            {
                hrac(1, pole_znaku);
                vyhra_cislo = vyhra(1, pole_znaku);

                if (vyhra_cislo == 0)
                {
                    break;
                }

                robot(1, pole_znaku);
                vyhra_cislo = vyhra(3, pole_znaku);

                if (vyhra_cislo == 0)
                {
                    break;
                }
            }
        }

        else if (uzivatel_vyber == 3)
        {
            // hraje robot, zkontroluje vyhru, pripadne ukonci hru
            barva(11);
            cout << "Robot vs Robot\n";
            vypis_desky(pole_znaku);

            while (1)
            {
                robot(2, pole_znaku);
                vyhra_cislo = vyhra(4, pole_znaku);

                if (vyhra_cislo == 0)
                {
                    break;
                }

                robot(1, pole_znaku);
                vyhra_cislo = vyhra(3, pole_znaku);

                if (vyhra_cislo == 0)
                {
                    break;
                }
            }
        }

        else if (uzivatel_vyber == 4)
        {
            reset_hry = false; // ukonci hru
        }

        if (reset_hry) // true
        {
            barva(11);
            cout << "\nChcete resetovat hru a hrat znovu? (Ano[1], Ne[0])\n"; // 1 true;0 false
            cout << "Vyber: ";
            cin >> reset_hry;
            system("cls"); // vymaze minulou hru
        }

    } while (reset_hry);

    return 0;
}

//--  funkce

int menu()
{
    int vyber_uzivatel = 0;
    barva(15);

    cout << "1) Hrac vs Hrac\n";
    cout << "2) Hrac vs Robot\n";
    cout << "3) Robot vs Robot\n";
    cout << "4) Konec hry\n";

    cout << "Vyber: ";
    cin >> vyber_uzivatel;
    cout << '\n';

    return vyber_uzivatel;
}

void hrac(int hrac, char pole_znaku[9])
{
    char znak_hrace = hraci_znaky(hrac);
    int pozice_hrace;

    do
    {
        if (hrac == 1)
        {
            barva(11);
        }
        if (hrac == 2)
        {
            barva(13);
        }

        cout << "Hrac" << hrac << "[" << znak_hrace << "]" << " zadej cislo(1-9): ";
        cin >> pozice_hrace;
        pozice_hrace--; // odecte protoze pole se indexuje od 0

        if (pole_znaku[pozice_hrace] != ' ' || pozice_hrace < 0 || pozice_hrace > 9)
        {
            barva(12);
            cout << "Chyba, zkuste znova\n";
        }

        else
        {
            pole_znaku[pozice_hrace] = znak_hrace; // nastavi znak na pozici v poli
            vypis_desky(pole_znaku);
            break;
        }
    } while (pole_znaku[pozice_hrace] != ' ');
}

void vypis_desky(char pole_znaku[9])
{
    barva(15);
    cout << '\n';
    cout << "     |     |     \n";
    cout << "  " << pole_znaku[0] << "  |  " << pole_znaku[1] << "  |  " << pole_znaku[2] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << pole_znaku[3] << "  |  " << pole_znaku[4] << "  |  " << pole_znaku[5] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << pole_znaku[6] << "  |  " << pole_znaku[7] << "  |  " << pole_znaku[8] << "  \n";
    cout << "     |     |     \n";
    cout << '\n';
}

bool remiza(char pole_znaku[9])
{
    for (int i = 0; i < 9; i++)
    {
        if (pole_znaku[i] == ' ') // neni remiza, jsou volny mista
        {
            return false;
        }
    }

    return true; // remiza
}

bool vyhra_horizontal(int hrac, char pole_znaku[9])
{
    char znak_hrace = hraci_znaky(hrac);

    for (int i = 0; i < 3; i++) // 0 1 2; 3 4 5; 6 7 8
    {
        if (pole_znaku[i * 3] == znak_hrace && pole_znaku[(i * 3) + 1] == znak_hrace && pole_znaku[(i * 3) + 2] == znak_hrace)
        {
            return true;
        }
    }

    return false;
}

bool vyhra_vertical(int hrac, char pole_znaku[9])
{
    char znak_hrace = hraci_znaky(hrac);

    for (int i = 0; i < 3; i++) // 0 3 6; 1 4 7; 2 5 8
    {
        if (pole_znaku[i] == znak_hrace && pole_znaku[i + 3] == znak_hrace && pole_znaku[i + 6] == znak_hrace)
        {
            return true;
        }
    }

    return false;
}

bool vyhra_diagonal(int hrac, char pole_znaku[9])
{
    char znak_hrace = hraci_znaky(hrac);

    if (pole_znaku[0] == znak_hrace && pole_znaku[4] == znak_hrace && pole_znaku[8] == znak_hrace)
    {
        return true;
    }

    if (pole_znaku[2] == znak_hrace && pole_znaku[4] == znak_hrace && pole_znaku[6] == znak_hrace)
    {
        return true;
    }

    return false;
}

bool vyhra_bot(int hrac, char pole_znaku[9]) // vlastni zkontrolovani vyhry pro robota(kvuli jeho logice), aby to nedelalo problemy
{
    int hrac_cislo = hrac;

    if (vyhra_horizontal(hrac_cislo, pole_znaku) || vyhra_vertical(hrac_cislo, pole_znaku) || vyhra_diagonal(hrac_cislo, pole_znaku))
    {
        return true;
    }

    return false;
}

int vyhra(int hrac, char pole_znaku[9])
{
    int hrac_cislo = hrac;

    if (remiza(pole_znaku))
    {
        barva(14);
        cout << "Remiza! Nikdo nevyhral :(";
        return 0;
    }

    // ukoncuje hru kdyz jedna z funkci true
    if (vyhra_horizontal(hrac_cislo, pole_znaku) || vyhra_vertical(hrac_cislo, pole_znaku) || vyhra_diagonal(hrac_cislo, pole_znaku))
    {
        barva(10);

        if (hrac_cislo == 3)
        {
            cout << "Vyhral robot1!";
            return 0;
        }

        if (hrac_cislo == 4)
        {
            cout << "Vyhral robot2!";
            return 0;
        }

        cout << "Konec hry!\nVyhral hrac" << hrac_cislo << "! Gratuluji :)";
        return 0;
    }

    return 1;
}

void robot(int robot, char pole_znaku[9])
{
    int robot_cislo;

    if (robot == 1)
    {
        barva(13);

        for (int i = 0; i < 9; i++)
        {
            if (pole_znaku[i] == ' ')
            {
                pole_znaku[i] = 'O';

                if (vyhra_bot(3, pole_znaku)) // pokud robot vyhraje pristi kolo
                {
                    cout << "\nRobot hraje[O]: " << i + 1 << '\n';
                    vypis_desky(pole_znaku);
                    return;
                }

                pole_znaku[i] = ' ';
            }
        }

        for (int i = 0; i < 9; i++)
        {
            if (pole_znaku[i] == ' ')
            {
                pole_znaku[i] = 'X';

                if (vyhra_bot(1, pole_znaku)) // pokud hrac nebo druhy robot vyhraje pristi kolo, robot zablokuje
                {
                    pole_znaku[i] = 'O';
                    cout << "\nRobot hraje[O]: " << i + 1 << '\n';
                    vypis_desky(pole_znaku);
                    return;
                }

                pole_znaku[i] = ' ';
            }
        }

        if (pole_znaku[4] == ' ') // hraje uprostred, protoze je to nejlepsi misto v piskvorkach ! :)
        {
            pole_znaku[4] = 'O';
            cout << "\nRobot hraje[O]: 5\n";
            vypis_desky(pole_znaku);
            return;
        }

        // pokud mu nic jineho nezbyva, hraje random
        do
        {
            robot_cislo = rand() % 9;
        } while (pole_znaku[robot_cislo] != ' ');

        pole_znaku[robot_cislo] = 'O';

        cout << "\nRobot hraje[O]: " << robot_cislo + 1 << '\n';

        vypis_desky(pole_znaku);
    }

    if (robot == 2)
    {
        barva(11);

        for (int i = 0; i < 9; i++)
        {
            if (pole_znaku[i] == ' ')
            {
                pole_znaku[i] = 'X';

                if (vyhra_bot(4, pole_znaku))
                {
                    cout << "\nRobot hraje[X]: " << i + 1 << '\n';
                    vypis_desky(pole_znaku);
                    return;
                }

                pole_znaku[i] = ' ';
            }
        }

        for (int i = 0; i < 9; i++)
        {
            if (pole_znaku[i] == ' ')
            {
                pole_znaku[i] = 'O';

                if (vyhra_bot(2, pole_znaku))
                {
                    pole_znaku[i] = 'X';
                    cout << "\nRobot hraje[X]: " << i + 1 << '\n';
                    vypis_desky(pole_znaku);
                    return;
                }

                pole_znaku[i] = ' ';
            }
        }

        if (pole_znaku[4] == ' ')
        {
            pole_znaku[4] = 'X';
            cout << "\nRobot hraje[X]: 5\n";
            vypis_desky(pole_znaku);
            return;
        }

        do
        {
            robot_cislo = rand() % 9;
        } while (pole_znaku[robot_cislo] != ' ');

        pole_znaku[robot_cislo] = 'X';

        cout << "\nRobot hraje[X]: " << robot_cislo + 1 << '\n';

        vypis_desky(pole_znaku);
    }
}

void logo_piskvorky()
{

    barva(3);
    cout << "  ___ ___ ___ _  ____   _____  ___ _  ____   __        \n";
    cout << " | _ \\_ _/ __| |/ /\\ \\ / / _ \\| _ \\ |/ /\\ \\ / / \n";
    cout << " |  _/| |\\__ \\ ' <  \\ V / (_) |   / ' <  \\ V /     \n";
    cout << " |_| |___|___/_|\\_\\  \\_/ \\___/|_|_\\_|\\_\\  |_|   \n";
    cout << "\n";
    barva(15);
}

char hraci_znaky(int hrac)
{
    if (hrac == 1 || hrac == 4) // 4 = robot2
    {
        return 'X';
    }

    else if (hrac == 2 || hrac == 3) // 3 = robot1
    {
        return 'O';
    }

    return ' ';
}

// 3 - cyan tmava, 11 - cyan, 13 - fialova, 10 - zelena, 12 - cervena, 14 - zluta, 15 - bila(reset barev)
void barva(int barvicka)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, barvicka);
}
