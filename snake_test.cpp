#include <iostream>
#include "level.h"
#include "snake.h"
#include <unistd.h>
// #include "memtrace.h"

void Test_1_SetLevelSize(Level **level, Snake **snake)
{
    delete *level;
    delete *snake;
    std::cout << "\n---Palyameret ballitasanak tesztelese---\nA palya elozo meretei: \n\t Szelesseg: " << GameSettings::LEVEL_XDIM << "\n\t Magassag: " << GameSettings::LEVEL_YDIM << "\nAdd meg a palya uj szelesseget (min 3, max 100): ";
    std::cin >> GameSettings::LEVEL_XDIM;
    std::cout << "Add meg a palya uj magassagat (min 3, max 100): ";
    std::cin >> GameSettings::LEVEL_YDIM;
    GameSettings::LEVEL_XDIM = GameSettings::LEVEL_XDIM < 3 ? 3 : GameSettings::LEVEL_XDIM;
    GameSettings::LEVEL_YDIM = GameSettings::LEVEL_YDIM < 3 ? 3 : GameSettings::LEVEL_YDIM;
    GameSettings::LEVEL_XDIM = GameSettings::LEVEL_XDIM > 100 ? 100 : GameSettings::LEVEL_XDIM;
    GameSettings::LEVEL_YDIM = GameSettings::LEVEL_YDIM > 100 ? 100 : GameSettings::LEVEL_YDIM;
    std::cout << "A palya uj meretei: \n Szelesseg: " << GameSettings::LEVEL_XDIM << "\n Magassag: " << GameSettings::LEVEL_YDIM << "\n";
    *level = new Level();
    *snake = new Snake();
}

void Test_2_SnakeSingleStep(Snake *snake)
{
    std::cout << "\n---Kigyo leptetesenek tesztelese---\nKigyo elozo pozicioja: " << snake->GetPosition() << "\nKigyo irany: " << snake->GetDirectionText() << "\n";
    snake->Step();
    std::cout << "Kigyo uj pozicioja: " << snake->GetPosition() << "\n";
}

void Test_3_SetSnakeDirection(Snake *snake)
{
    char c;
    std::cout << "\n---Kigyo iranyvaltoztatasanak tesztelese---\nJelenlegi irany: " << snake->GetDirectionText() << "\nValassz uj iranyt:\n\t[1] - Jobbra \n\t[2] - Balra \n\t[3] - Fel\n\t[4] - Le\n";
    std::cin >> c;
    switch (c)
    {
    case '1':
        snake->SetDirection(RIGHT);
        break;
    case '2':
        snake->SetDirection(LEFT);
        break;
    case '3':
        snake->SetDirection(UP);
        break;
    case '4':
        snake->SetDirection(DOWN);
        break;
    }
    std::cout << "Uj irany: " << snake->GetDirectionText() << "\n";
}

void Test_4_SnakeEating(Level **level, Snake **snake)
{
    (*snake)->SetDirection(LEFT);
    int currentLength = (*snake)->GetLength();
    int rowStep = 0;
    std::cout << "\n---Eves tesztelese---\n";
    while (currentLength == (*snake)->GetLength())
    {
        std::cout << "Kigyo pozicioja: " << (*snake)->GetPosition() << "\tAlma pozicioja: " << (*level)->GetFruit().GetPos() << "\tKigyo hossza: " << (*snake)->GetLength();

        if ((*snake)->GetDirection() == UP)
        {
            std::cout << "\tFelfele lepes";
        }
        (*snake)->Step();
        if ((*snake)->GetIsDead())
        {
            std::cout << "\n A kigyo magaba harapott" << std::endl;
            break;
        }
        if ((*snake)->GetPosition() == (*level)->GetFruit().GetPos())
        {
            (*snake)->Eat((*level)->GetFruit());
            (*level)->SpawnNewFruit(**snake);
        }
        (*snake)->SetDirection(LEFT);
        rowStep++;
        if (rowStep >= GameSettings::LEVEL_XDIM)
        {
            (*snake)->SetDirection(UP);
            rowStep = 0;
        }
        std::cout << std::endl;
    }
    if (!(*snake)->GetIsDead())
    {
        std::cout << "A kigyo evett ebben a pozicioban: " << (*snake)->GetPosition() << " - Kigyo hossza: " << (*snake)->GetLength() << "\n";
    }
    else
    {
        std::cout << "A kigyo meghalt ebben a pozicioban: " << (*snake)->GetPosition() << ", mert magaba harapott";
        delete *snake;
        *snake = new Snake();
    }
}

void AutomaticTestCasesBase(Level **level, Snake **snake)
{
    (*snake)->SetDirection(LEFT);
    int rowStep = 0;
    while (!(*snake)->GetIsDead())
    {
        std::cout << "Kigyo pozicioja: " << (*snake)->GetPosition() << "\tAlma pozicioja: " << (*level)->GetFruit().GetPos() << "\tKigyo hossza: " << (*snake)->GetLength();
        if ((*snake)->GetDirection() == UP)
        {
            std::cout << " Felfele lepes";
        }
        (*snake)->Step();
        // if ((*snake)->GetIsDead())
        // {
        //     std::cout << "\nA kigyo magaba harapott" << std::endl;
        //     break;
        // }
        if ((*snake)->GetPosition() == (*level)->GetFruit().GetPos())
        {
            (*snake)->Eat((*level)->GetFruit());
            if ((*snake)->GetLength() >= GameSettings::LEVEL_XDIM * GameSettings::LEVEL_YDIM)
            {
                std::cout << "\nKigyo pozicioja: " << (*snake)->GetPosition() << "\tAlma pozicioja: " << (*level)->GetFruit().GetPos() << "\tKigyo hossza: " << (*snake)->GetLength();
                std::cout << "\nNincs tobb hely etelt letenni, a kigyo magaba harap";
                break;
            }
            (*level)->SpawnNewFruit(**snake);
        }
        (*snake)->SetDirection(LEFT);
        rowStep++;
        if (rowStep >= GameSettings::LEVEL_XDIM)
        {
            (*snake)->SetDirection(UP);
            rowStep = 0;
        }
        std::cout << std::endl;
    }
    std::cout << "\nA kigyo meghalt ebben a pozicioban: " << (*snake)->GetPosition() << ", mert magaba harapott\n";
    delete *snake;
    *snake = new Snake();
}

void Test_5_Automatic_n_n_case(Level **level, Snake **snake)
{
    std::cout << "\n---Automatikus teszteles n*n eset---\nValassz egy palya meretet (min 3, max 100)\nValasztas: ";
    std::cin >> GameSettings::LEVEL_XDIM;
    GameSettings::LEVEL_XDIM = GameSettings::LEVEL_XDIM < 3 ? 3 : GameSettings::LEVEL_XDIM;
    GameSettings::LEVEL_XDIM = GameSettings::LEVEL_XDIM > 100 ? 100 : GameSettings::LEVEL_XDIM;
    GameSettings::LEVEL_YDIM = GameSettings::LEVEL_XDIM;
    delete *level;
    delete *snake;
    *level = new Level();
    *snake = new Snake();
    AutomaticTestCasesBase(level, snake);
}

void Test_6_Automatic_n_k_case(Level **level, Snake **snake)
{
    std::cout << "\n---Automatikus teszteles n*k eset---\nValassz egy palya szelesseget (min 3, max 100)\nValasztas: ";
    std::cin >> GameSettings::LEVEL_XDIM;
    std::cout << "Valassz egy palya magassagot (min 3, max 100)\nValasztas: ";
    std::cin >> GameSettings::LEVEL_YDIM;
    GameSettings::LEVEL_XDIM = GameSettings::LEVEL_XDIM < 3 ? 3 : GameSettings::LEVEL_XDIM;
    GameSettings::LEVEL_YDIM = GameSettings::LEVEL_YDIM < 3 ? 3 : GameSettings::LEVEL_YDIM;
    GameSettings::LEVEL_XDIM = GameSettings::LEVEL_XDIM > 100 ? 100 : GameSettings::LEVEL_XDIM;
    GameSettings::LEVEL_YDIM = GameSettings::LEVEL_YDIM > 100 ? 100 : GameSettings::LEVEL_YDIM;
    delete *level;
    delete *snake;
    *level = new Level();
    *snake = new Snake();
    AutomaticTestCasesBase(level, snake);
}
void Test_7_SelfEatTest(Level **level, Snake **snake)
{
    std::cout << "\n ---Kigyo onmagaba harapas tesztelese---\nKigyo hosszanak novelese kovetkezik, ha nem eleg hosszu\n";
    while ((*snake)->GetLength() < 5)
    {
        Test_4_SnakeEating(level, snake);
    }

    std::cout << "\nHarapas tesztelese, korbe lepkedes";
    (*snake)->SetDirection(UP);
    (*snake)->Step();
    std::cout << "\nKigyo pozicioja: " << (*snake)->GetPosition() << " - Alma pozicioja: " << (*level)->GetFruit().GetPos() << "- Kigyo hossza: " << (*snake)->GetLength();
    (*snake)->SetDirection(RIGHT);
    (*snake)->Step();
    std::cout << "\nKigyo pozicioja: " << (*snake)->GetPosition() << " - Alma pozicioja: " << (*level)->GetFruit().GetPos() << "- Kigyo hossza: " << (*snake)->GetLength();
    (*snake)->SetDirection(DOWN);
    (*snake)->Step();
    std::cout << "\nKigyo pozicioja: " << (*snake)->GetPosition() << " - Alma pozicioja: " << (*level)->GetFruit().GetPos() << "- Kigyo hossza: " << (*snake)->GetLength();
    if ((*snake)->GetIsDead())
    {
        std::cout << "\nA kigyo megette magat ebben a pozicioban: " << (*snake)->GetPosition() << ", a kigyo hossza: " << (*snake)->GetLength() << "\n";
        delete *snake;
        *snake = new Snake();
    }
}
int main()
{
    srand(time(NULL));
    rand();

    Level *level = new Level();
    Snake *snake = new Snake();

    char c;
    while (c != '8')
    {
        std::cout << "\nValassz tesztesetet! \n [1] - Palyameret ballitasanak tesztelese\n [2] - Kigyo leptetesenek tesztelese\n [3] - Kigyo iranyvaltoztatasanak tesztelese\n [4] - Eves tesztelese\n [5] - Automatikus teszteles n*n eset\n [6] - Automatikus teszteles n*k eset\n [7] - Kigyo onmagaba harapas tesztelese\n [8] - Kilepes\n Valasztas: ";
        std::cin >> c;
        switch (c)
        {
        case '1':
            Test_1_SetLevelSize(&level, &snake);
            break;
        case '2':
            Test_2_SnakeSingleStep(snake);
            break;
        case '3':
            Test_3_SetSnakeDirection(snake);
            break;
        case '4':
            Test_4_SnakeEating(&level, &snake);
            break;
        case '5':
            Test_5_Automatic_n_n_case(&level, &snake);
            break;
        case '6':
            Test_6_Automatic_n_k_case(&level, &snake);
            break;
        case '7':
            Test_7_SelfEatTest(&level, &snake);
            break;
        case '8':
            break;
        }
    }
    delete level;
    delete snake;
    return 0;
}