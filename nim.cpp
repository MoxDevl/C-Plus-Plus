#include <iostream>
#include <vector>

std::vector<int> player_turn()
{
    int line, amount;
    
    while (1)
    {
        std::cin >> line >> amount;
        if (std::cin.fail() || line > 3 || line < 1)
        {
            std::cin.clear();
            std::cin.ignore(4444, '\n');
            std::cout << "Wrong input, try again:" << std::endl;
        }
        else
            break;
    }

    return {line, amount};
}

bool repeat()
{
    bool anw;
    while (1)
    {
        std::cin >> anw;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(4444, '\n');
            std::cout << "Try again? ([1]YES [0]NO)" << std::endl;
        }
        else
            break;
    }
    return anw;
}

std::vector<int> destroyer_turn(std::vector<int> rocks) 
{
    std::vector<int> fake_rocks;
    int rsum, X=(rocks[0]^rocks[1]^rocks[2]),
        x1=(X^rocks[0]), x2=(X^rocks[1]), x3=(X^rocks[2]);
        
        if (x1<rocks[0])
            return {1, rocks[0]-x1};
        if (x2<rocks[1])
            return {2, rocks[1]-x2};
        if (x3<rocks[2])
            return {3, rocks[2]-x3};

        for (int i=0; i<3; i++) {
            if (rocks[i]>0) 
                {return {i+1, 1};}
        }
        return {0,0};
}

bool game(std::vector<int> rocks) 
{
    bool end=0, first;
    int pord=0; // 0 for player or 1 for destroyer 
    std::vector <int> turn(2);

    std::cout << "\nWho goes first? ([1]Destroyer [0]Player)" << std::endl;
    
    while(1)
    {
        std::cin>>first;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(4444, '\n');
            std::cout << "Who goes first? ([1]Destroyer [0]Player)" << std::endl;
        }
        else
            break;
    }
    pord=first;
    

    std::cout << "\ngame is on" << std::endl;

    while (!end)
    {
        std::cout << "\nCurrent position: \n"
                  << "Line 1 has "<< rocks[0] << " rocks\n"
                  << "Line 2 has "<< rocks[1] << " rocks\n"
                  << "Line 3 has "<< rocks[2] << " rocks\n" << std::endl;
        
        switch (pord%2)
        {
            case 0: // player's turn
            {
                while(true) {
                    std::cout << "Player's turn:" << std::endl;
                    turn=player_turn();
                    
                    if (rocks[turn[0]-1] < turn[1])
                        std::cout << "Not enough rocks in line to take, input again:" << std::endl;
                    else
                        break;
                }

                rocks[turn[0]-1]-=turn[1];
                break;
            }

            case 1: // destroyer's turn
            {
                turn=destroyer_turn(rocks);
                rocks[turn[0]-1]-=turn[1];

                std::cout << "Destroyer's turn: \n" 
                          << turn[0] << " " << turn[1] << std::endl;                
                break;
            }
        }

        if(rocks[0]==0 && rocks[1]==0 && rocks[2]==0)
        {
            end=1;
            break;
        }

        pord++;
    }

    switch (pord%2)
    {
        case 0: // player won
        {
            std::cout << "\nDestroyer got destroyed!!! Congratulations! \n" 
                      << "... \n" << "... \n" << "... \n" 
                      << "Try again? ([1]YES [0]NO)" << std::endl;
            break;
        }
        case 1: // player lost
        {
            std::cout << "\nDestroyer lives up to his name. \n"
                      << "Maybe the next time will be different... \n" 
                      << "Try again? ([1]YES [0]NO)" << std::endl;
            break;
        }
    }
    
    return repeat();
}

int main()
{
    std::vector<int> rocks(3); 
    rocks[0]=3;
    rocks[1]=4;
    rocks[2]=5;

    std::cout << "\nNIM THE GAME. \n\n"
              << "You can take any amount of rocks from one line you choose. \n"
              << "Player which took the last rock wins. \n\n"
              << "Starting position: \n"
              << "Line 1 has "<< rocks[0] << " rocks\n"
              << "Line 2 has "<< rocks[1] << " rocks\n"
              << "Line 3 has "<< rocks[2] << " rocks\n\n"
              << "Input your turn in form of LINE AMOUNT \n" 
              << "(For example, 3 2 - means take two rocks from line three) \n" 
              << "\nYou are going to play against ~The Destroyer~ so do your best." << std::endl;

    bool start = 1;
    while (start)
        start=game(rocks);
    return 0;
}