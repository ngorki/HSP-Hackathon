#include <stdio.h>
#include <string.h>
#include "classes.h"
#include "moves.h"

int basicUsed1, basicUsed2;
int turns = 0;

void fight(struct role *hero, struct role *enemy, struct subclass *heroSub){
    int attackChoice, abilityRemaining;
    
    if(turns % 2 == 0)
        abilityRemaining = hero->charged - basicUsed1;
    else
        abilityRemaining = hero->charged - basicUsed2;
    
    if(abilityRemaining < 0)
        abilityRemaining = 0;
    
    printf("Which attack do you want to use? \n");
    printf("1. Basic Attack\n");
    printf("2. Charged Attack: %d/%d turns until available\n", abilityRemaining, hero->charged); //show availability
    scanf("%d", &attackChoice);
    if(attackChoice == 1){
        basic(hero, enemy, heroSub, turns, &camoChoice);
        if(turns % 2 == 0){
            basicUsed1++;
        }
        else
            basicUsed2++;
    }
    if(attackChoice == 2 && !abilityRemaining){
        if(!(strcmp(hero->name, "Assassin"))){
            assa_charge(hero, enemy);
            if(turns % 2 == 0){
                basicUsed1 = 0;
            }
            else
            {
                basicUsed2 = 0;
            }
        }
        else if(!(strcmp(hero->name, "Tank"))){
            tank_charge(hero, enemy);
            if(turns % 2 == 0){
                basicUsed1 = 0;
            }
            else
                basicUsed2 = 0;
        }
        else if(!(strcmp(hero->name, "Bruiser"))){
        bruiser_charge(hero, enemy, heroSub, turns);
        if(turns % 2 == 0){
            basicUsed1 = 0;
        }
        else
            basicUsed2 = 0;
    }
    }
    else if(attackChoice == 2 && abilityRemaining){
        printf("The charged ability is not available, wait %d turns.", abilityRemaining);
    }
}

int main(void) {
    srand(time(0));
    int playerChoice[4];
    for(int i = 0; i < 4; i += 2){
        int choice, subclass;
        if(!i){
            printf("Player 1\n");
        }
        else
            printf("\nPlayer 2\n");
        
        printf("Choose your character.\n");
        printf("1. Assassin- 10%% chance to decrease enemy defense by 20%%\n");
        printf("2. Bruiser- 10%% chance to increase attack damage by a value from 110%% to 130%%\n");
        printf("3. Tank-  10%% chance to decrease enemy defense by 10%% and increase your own defense by 10%%\n");
        scanf("%d", &choice);
        playerChoice[i] = choice - 1;
        printf("\nChoose a subclass.\n");
        
        if(choice == 1)
        {
            printf("1. Ninja Assassin: Ability to halve opponent's defense.\n");
            printf("2. Vampire Assassin: Ability to Heal by %d percent\n", (int)(subs[0][1].classValue * 100));
        }
        
        if(choice == 2)
        {
            printf("1. Growth: Increase defense by 2 percent each turn\n");
            printf("2. Time Bomb: After a certain amount of turns, 50 percent of damage is given to opponent\n");
        }
        
        if(choice == 3)
        {
            printf("1. Missile: Give 5 percent more damage to your opponent by using more accurate weapons\n");
            printf("2. Camouflage: Ability to dissapear every few turns\n");
            
        }
        scanf("%d", &subclass);
        playerChoice[i+1] = subclass - 1;
    }
    player1 = classes[playerChoice[0]];
    player2 = classes[playerChoice[2]];
    while(player1.hp >= 0 || player2.hp >= 0){
        printf("\nPlayer 1 HP: %.1f | Player 2 HP: %.1f\n", player1.hp, player2.hp);
        struct subclass p1Sub = subs[playerChoice[0]][playerChoice[1]], p2Sub = subs[playerChoice[2]][playerChoice[3]];
        //if
        if(turns % 2 == 0){ //player 1 turn
            printf("Player 1\n");
            fight(&player1, &player2, &p1Sub);
        }
        else{ //player 2 turn
            printf("Player 2\n");
            fight(&player2, &player1, &p2Sub);
        }
        if(player1.hp <= 0){
            printf("Player 2 won!\n");
            break;
        }
        else if(player2.hp <= 0){
            printf("Player 1 won!\n");
            break;
        }
        
        turns++;
    }
    return 0;
 }