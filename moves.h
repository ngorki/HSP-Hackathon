#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int tank_is_charged = 0;
int camoChoice = 0;

float damage(struct role *hero, struct role *enemy, float base_damage) {
    float randombase = (rand() % 300 / 100) + base_damage; //should pick random number 0 - 3 out to 2 decimal places, add to base damage
    float damagedone = randombase * (1 + hero->atk / 100) * (1 - enemy->def / 200); //user_attack and opponent_defense stats should be between 0 and 100ish. example: for user_attack == 50 and opponent_defense == 40, damage is randombase * 1.5 * .8
    if (!(strcmp(enemy->name, "Tank")) && tank_is_charged == 1) {
        hero->hp = hero->hp - damagedone;
        tank_is_charged = 0;
    }
    return damagedone;
}

void basic(struct role *hero, struct role *enemy, struct subclass *heroSub, int turns, int *camoChoice) {
    printf("%d\n", *camoChoice);
    float damagedone = damage(hero, enemy, 50);
    if (!(strcmp(hero->name, "Assassin"))) { //assassin
        if (rand() % 10 == 0){
            enemy->def = enemy->def * .8;
            printf("Enemy's defense was decreased by 20%%\n");
        }
        if (!(strcmp(heroSub->subclassName, "Vampire Assassin"))) {
            hero->hp = hero->hp + (damagedone * heroSub->classValue);
            printf("Vampire Perk: Your health increased!\n");
        }
        else if ((!(strcmp(heroSub->subclassName, "Ninja Assassin"))) && (turns % 6 == 4 || turns % 6 == 5)) {
            enemy->def = enemy->def * (1 - heroSub->classValue);
            printf("Ninja Perk: Enemy's defense decreased by %d%%!\n", (int)(heroSub->classValue * 100));
        }
    }
    else if (!(strcmp(hero->name, "Tank"))) {
        *camoChoice = 0;
        int camoReady;
        if (rand() % 10 == 0) {
            enemy->def = enemy->def * .9;
            hero->def = hero->def * 1.1111;
            printf("10%% of enemy's defense stolen\n");
        }
        if (!(strcmp(heroSub->subclassName, "Tank Camo")) && (turns % 4 == 1 || turns % 4 == 2)) {
            camoReady = 1;
        }
        if (!(strcmp(heroSub->subclassName, "Tank Camo")) &&(camoReady = 1)) {
            printf("Your Tank Camo ability is ready. Use it this turn?\n1. Go invisible for a turn\n2. Skip for now\n");
            scanf("%d", camoChoice);
            if (*camoChoice == 1) {
                printf("You are now invisible.\n");
            }
        }
        else if (!(strcmp(heroSub->subclassName, "Tank Missile"))) {
            damagedone = damagedone * (1 + heroSub->classValue);
            printf("Missile Perk: Damage increased by %f.0%%.\n", heroSub->classValue * 100);
        }
    }
    
    else if (!(strcmp(hero->name, "Bruiser"))) {
        if (rand() % 10 == 0){
            float num = (1 + rand() % 3 / 10 + .1);
            damagedone = damagedone * num; //multiply by a random number between 1.1 and 1.3
            printf("Damage increased by %f.0%%\n", num*100);
        }
        if (!(strcmp(heroSub->subclassName, "Bruiser Growth"))) {
            hero->def = hero->def * (1 + heroSub->classValue);
            printf("Growth Perk: Your defense increased!\n");
        }
        else if (!(strcmp(heroSub->subclassName, "Bruiser Time Bomb"))) {
            if (turns % 4 == 1 || turns % 4 == 2) {
                float timebombdamage = hero->hp * (heroSub->classValue);
                hero->hp -= timebombdamage;
                enemy->hp -= timebombdamage;
                printf("Time Bomb Perk: You hurt yourself in order to hurt your enemy!\n");
            }
        }
    }
    if (*camoChoice == 1 && !strcmp(enemy->name, "Tank")) {
        //enemy->hp = enemy->hp + damagedone; //this way, net damage against enemy is 0
        printf("Your opponent was invisible and you did no damage.\n");
        damagedone = 0;
    }
    enemy->hp = enemy->hp - damagedone;
}

void assa_charge(struct role *hero, struct role *enemy) {
    float damagedone = damage(hero, enemy, 90);
    enemy->hp = enemy->hp - damagedone;
    if (enemy->hp > 0)
        enemy->def = enemy->def * .7;
    printf("The enemy's defense was decreased by 30%%, and your attack was stronger than normal!\n");
}

void tank_charge(struct role *hero, struct role *enemy) {
    tank_is_charged = 1;
    printf("Your damage was reflected onto the enemy.\n");
}

void bruiser_charge(struct role *hero, struct role *enemy, struct subclass *heroSub, int turns) {
    hero->atk = hero->atk * 1.3;
    basic(hero, enemy, heroSub, turns, &camoChoice);
    printf("Your attack was 30 percent stronger.\n");
}
