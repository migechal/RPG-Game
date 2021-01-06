#include "header/Game.h"
#include "header/character.h"
#include <bits/stdc++.h>


int main(){
    //INIT
    std::map<std::string, std::string> action =
    {
        {"punched", "*you got punched and knocked out*"},
        {"shot", "*You ran and got shot*\n GAME OVER."}
    };

    std::ofstream log("log.msg");

    Base::Color                 color;
    Base::Open                  cache;
    Player::player              player;
    Player::player              narrator;
    Player::player              sergent;
    Player::player              patrol;
    Player::player              fighter1;
    Player::player              fighter2;


    player.color = 'b';
    narrator.color = 'w';
    sergent.color = 'r';
    patrol.color = 'c';
    fighter1.color = 'm';
    fighter2.color = 'g';

    log << "Init phase over\n";

    //Main menu
    using namespace Base;
    clearterm();

    bool loadedFile = false;

    consolePrintMSG("Welcome to your own adventure where you choose what happens", narrator.color);
    if(cache.exist()){
        consolePrintMSG("You have a profile available, use it? [y,n]", narrator.color);
        switch(getStr()[0]){
            case 'y':
                if (cache.getCache(player.playerInfo) == 0){
                    log << "Loaded Save\n";
                    loadedFile = true;
                }
                break;
            default:
                consolePrintMSG("Ok deleting save....", narrator.color);
                remove("saves/save.txt");
                pause(1000);
                clearterm();
                break;
        }
    }
    if(!loadedFile){
        consolePrintMSG("Enter your name:   ", narrator.color);
        std::get<2>(player.playerInfo) = getStr();
        std::get<1>(player.playerInfo) = 1;
    }
    clearterm();

    consolePrintMSG("Welcome to the game "+ std::get<2>(player.playerInfo) + "!", narrator.color);
    cache.doCache(player.playerInfo);
    int depth = std::get<0>(player.playerInfo);
    int choice = std::get<1>(player.playerInfo);
    if (depth >= 0){
        if(depth == 0){
            consolePrintMSG("Welcome to seattle here we live among the few that survived the missle strike, the survivers are in hiding or are serving criminal enterprises for food, shelter and safety.", narrator.color);
            pause(2000);
            clearterm();
            consolePrintMSG("Welcome to seattle A.K.A the lost city, here you will-", narrator.color);
            pause(500);
            consolePrintMSG("HEY, private wake up! No sleeping on guard duty or ill report you to the master.", sergent.color);
            pause(4000);
            consolePrintMSG("Possible responses: \n 1.Yes sir, sorry sir!\n 2.Screw off.\n 3.Don't say anything.\n", narrator.color);
            int select = get();
            switch(select){
                case 1:
                    choice *= select;
                   	consolePrintMSG("Yeah thats what I thought.", sergent.color);
	                break;
                case 2:
                    choice *= select;
                    consolePrintMSG("What did you say private?", sergent.color);
                    pause(1000);
                    consolePrintMSG("I said screw off sir.", player.color);
                    pause(1000);
                    consolePrintMSG(action.find("punched")->second, narrator.color);
                    break;
                case 3:
                    choice *=select;
                    consolePrintMSG("Answer me PRIVATE!", sergent.color);
                    break;
            }            
            player.updateLocation(++depth, choice);
        }
        if(depth == 1)
        {
            switch(choice){
                case 1:
                    choice *= 1;
                    break;
                case 2:
                    choice *= 2;
                        consolePrintMSG("*you wake up 30 minutes later with a bad headache and notice that a patrol is heading you way for a checkin.*", narrator.color);
                        pause(3000);
                        consolePrintMSG("Oh no, what am i gonna say when the patrol asks why i didnt checkin. Let me go and speak with them and try to get out of this.", player.color);
                        pause(5000);
                        consolePrintMSG("*the patrol arrives at your position.*", narrator.color);
                        pause(2000);
                        consolePrintMSG("Hey private, why didnt you checkin with your report.", patrol.color);
                        pause(3000);                            
                        consolePrintMSG("You now have a choice do you snitch on the sergeant or lie for him?\n 1.Snitch\n 2.Lie", narrator.color);
                        pause(2000);
                    break;
                case 3:
                    choice *= 3;
                    consolePrintMSG("Now you have a choice to make will you\n 1.Remain silent\n 2.Apologize\n", narrator.color);
                    switch(get()){
                        case 1:
                            consolePrintMSG("...", player.color);
                            consolePrintMSG(action.find("punched")->second, narrator.color);
                            consolePrintMSG("*you wake up 30 minutes later with a bad headache and notice that a patrol is heading you way for a checkin.*", narrator.color);
                            pause(3000);
                            consolePrintMSG("Oh no, what am i gonna say when the patrol asks why i didnt checkin. Let me go and speak with them and try to get out of this.", player.color);
                            pause(5000);
                            consolePrintMSG("*the patrol arrives at your position.*", narrator.color);
                            pause(2000);
                            consolePrintMSG("Hey private, why didnt you checkin with your report.", patrol.color);
                            pause(3000);                            
                            consolePrintMSG("You now have a choice do you snitch[1] on the sergeant or lie[2] for him?", narrator.color);
                            pause(2000);
                        case 2:
                            choice = 1;
                            consolePrintMSG("That's what I thought.", sergent.color);
                    }
            }
            player.updateLocation(++depth, choice);
        }
        if(depth == 2)
        {
            if(choice == 4 || choice == 9){
                switch(get()){
                    case 1:
                        choice *= 1;
                        consolePrintMSG("Okay, I'll talk to the sergeant about messing with the guards. Thank you private.", patrol.color);
                        pause(3000);
                        break;
                    case 2:
                        choice *= 2;
                        consolePrintMSG("Thats it private your going to detention.", patrol.color);
                        pause(3000);
                        break;
                }
            }
            else if(choice == 1){
                consolePrintMSG("*Your training ends and your now in the cafeteria.*", narrator.color);
                pause(3000);
                consolePrintMSG("Hey lil man give me your food", fighter1.color);
                consolePrintMSG("Do you give them your food?\n 1.Give up food\n 2.Ignore\n 3.Reject", narrator.color);
                pause(1000);
                switch(get()){
                    case 1:
                        consolePrintMSG("Here take it.", player.color);
                        pause(2000);
                        consolePrintMSG("*He takes the food and walks away*", narrator.color);

                    case 2:
                        consolePrintMSG("...", player.color);
                        pause(1000);
                        consolePrintMSG("*He pushes you away and takes your food.*", fighter1.color);
                    case 3: 
                        consolePrintMSG("No your not taking my food.", player.color);
                        pause(2000);
                        consolePrintMSG("Ohhh so we got a tough guy here huh? Aye broski come check this dude out!", fighter1.color);
                        pause(3000);
                        consolePrintMSG("*He and his friend corner you.*", narrator.color);
                        pause(4000);
                        consolePrintMSG("Well, well well what do we have here, a lil weasle looking for his mother eh? I don't think you heard my friend right the first time, give us your food.", fighter2.color);
                }
            }
            player.updateLocation(++depth, choice);
        }
        if(depth == 3){
            if(choice == 4 || choice == 9){
                consolePrintMSG("Okay they are at a meeting now is a perfct time to run, do you?", narrator.color);
                consolePrintMSG(" 1.Run\n 2.Stay at your post.\n", narrator.color);
                switch(get()){
                    case 1:
                        consolePrintMSG(action.find("shot")->second, narrator.color);
                        break;
                    case 2:
                        consolePrintMSG("*They come back to you*", narrator.color);
                        pause(2000);
                        consolePrintMSG("Looks like its your unlucky day private, sergeant has friends in high places.", patrol.color);
                        pause(5000);
                        consolePrintMSG("He raises his gun in between your eyebrows...", narrator.color);
                        pause(2500);
                        consolePrintMSG("Please, we can ta-", player.color);
                        pause(2500);
                        gameOver();
                }
            }
            elseif()
            else{
                gameOver();
            }
            player.updateLocation(++depth, choice);
        }

    }



    return 0;
}