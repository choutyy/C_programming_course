#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h> //引入字元測試與轉換函數標頭檔
#include <time.h>
#define TIME 200 * 1000
 
/*設定腳色*/
struct player_setting
{
    char *allname;
    int money;
    int current;
    int house[15];
    char name;
    int turns;
    int cards[5];
    int price;
 
} player, computer;
/*函數引數區*/
struct player_setting;
int map(char *[], char *[], int);
int ahead(int, int, char *[], char *[], char, int *);
int back(int, int, char *[], char *[], char);
int estate(int *, int *, int, int[], int[], int, int, int *, int *, char *[], char *[], char);
int carduse(int *, int *, int[], int, int[], int[], int *, int *, char *[], int);
 
/*主程式*/
int main()
{
    printf(" ::::::::::::::::::::::::\n");
    printf("  ::                  ::\n");
    printf("  ::    突如其來的    ::\n");
    printf("  ::  大 富 翁 冒 險  ::\n");
    printf("  ::    (或災難?)     ::\n");
    printf("  ::                  ::\n");
    printf(" ::::::::::::::::::::::::\n\n");
    printf("Press Any Key to start...\n");
    getchar();
    system("cls");
    char e[] = "騷年,你渴望力量嗎";
    for (int i = 0; e[i] != '\0'; i++)
    {
        printf("%c", e[i]);
        usleep(TIME);
    }
    usleep(TIME * 10);
    printf("\b ");
    for (int i = 1; i < sizeof(e); i++)
    {
        printf("\b\b ");
        usleep(TIME);
    }
    char f[] = "來場賭上生命的冒險吧";
    for (int i = 0; f[i] != '\0'; i++)
    {
        printf("%c", f[i]);
        usleep(TIME);
    }
    usleep(TIME * 20);
    system("cls");
 
    printf("是否將生命兌換成5000萬現金 [1]yes ");
    int ans;
    scanf("%d", &ans);
    if (ans != 1)
    {
        printf("就算你按其他鍵也是只有YES的選項喔^_^\n");
        usleep(TIME * 20);
    }
    system("cls");
 
    FILE *fp;
 
    char *located[] = {"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "};
    char *property[] ={"   ","   ","   ","   ","   ","   ","   ","   ","   ","   ","   ","   ","   ","   ","   ",};
    int choice;
    int fang(int turns);
    int  c;
    int goahead = 0;
    int Ppass = 1, Cpass = 1;
    int chance = 0;
    char *dice[] = {"[ · ]", "[· ·]", "[· :]", "[: :]", "[:·:]", "[:::]"};
    // int Q =0 ;
 
    srand((unsigned)time(NULL));
 
    char player_allname[10];
    printf("請輸入你的名字:\n");
    getchar();
    gets(player_allname);
    //printf("%d",strlen(player_allname));
    while (strlen(player_allname) <= 0 ||strlen(player_allname) > 10)
    {
        if (strlen(player_allname) > 10)
        {
            printf("你的名字也太長了吧，誰記得起來啦\n");
            printf("取短一點吧:\n");
            gets(player_allname);
        }
        else if (strlen(player_allname) <= 0)
        {
            printf("你沒有名字嗎，太可憐了吧\n");
            printf("還是取一個啦:\n");
            gets(player_allname);
        }
    }

    if(strcmp(player_allname, "幫我取") == 0){
        printf("真是拿你沒辦法，那就叫你小黑好了\n");
        strcpy(player_allname,"小黑");
        system("pause") ;
    }
start:
    system("cls");
    struct player_setting player = {player_allname, 5000, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 'p', 1, {0, 0, 0, 0, 0}};
    printf("     ^ ^\n   ( ·H· )\n  o.　   .o\n    O___O        %s ", player.allname);
    printf("代號:%c\n", player.name);
    printf("一無是處，就是個社畜\n\n");
    struct player_setting computer = {"Maou", 5000, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 'c', 1, {0, 0, 0, 0, 0}};
 
    printf("   C_\\ \n　  \\ \\(\\   /)\n　   \\ (。V。) \n　　　>  　n \\ \n　　　/ 　 A  \\ \n　　 /　　/ \\  \\ \n　　 L　 /　 \\_L) \n　　/　/ \n　 /　/| \n　(　(\\ \n　|　|、 \n　| /  （  ) \n　| |　　) / \n  / )　　L/       %s ", computer.allname);
    printf("代號:%c\n", computer.name);
    printf("愛玩遊戲的魔王");
    getchar();
turn:
    if (player.money<=0)
    {
        printf("你耗盡了你的資產");
        system("pause");
        goto end;
    }
    if (computer.money<=0)
    {
        printf("Maou耗盡了資產");
        system("pause");
        goto end;
    }
    else if (computer.money>10000)
    {
        printf("Maou賄絡地獄銀行將你的部分財產沒收\n");
        printf("Maou-5000萬 %s -7000萬\n",player.allname);
        computer.money -= 5000;
        player.money -= 7000;
        system("pause");
        goto turn;
    }
    if (player.turns)
    {
        Ppass = 1;
        for (Cpass; Cpass > 0; Cpass--)
        {
            system("cls");
            if (player.current == computer.current)
            {
                char str[4];
                str[0] = player.name;
                str[1] = ' ';
                str[2] = computer.name;
                str[3] = '\0';
                located[player.current] = str;
            }
            else
            {
                char Pstr[4];
                char Cstr[4];
                Pstr[0] = player.name;
                Pstr[1] = ' ';
                Pstr[2] = ' ';
                Pstr[3] = '\0';
                Cstr[0] = computer.name;
                Cstr[1] = ' ';
                Cstr[2] = ' ';
                Cstr[3] = '\0';
                located[player.current] = Pstr;
                located[computer.current] = Cstr;
            }
            chance = 0;
            map(located, property, chance);
            printf("\n%s:%d萬元  %s:%d萬元\n", player_allname, player.money, computer.allname, computer.money);
            printf("----------------------------------------\n");
            printf("請選擇操作:0.存檔 1.骰骰子 2.使用卡片 3.讀檔 4.遊戲說明 5.結束遊戲...\n");
 
            scanf("%d", &choice);
            if (choice == 0)
            {
                fp = fopen(player.allname, "w");
                fwrite(&player, sizeof(struct player_setting), 1, fp);
                fwrite(&computer, sizeof(struct player_setting), 1, fp);
                fclose(fp);
                goto turn;
            }
            else if (choice == 5){
                return 0;
            }
            else if (choice == 4){
                printf("沒什麼遊戲規則，跟著遊戲走就對了，不准質疑遊戲之神\n蛤?你問卡片的作用?\n告訴你就沒意思了，自己去探索吧<3\n");
                system("pause");
                goto turn;
            }
            else if (choice == 3)
            {
                for (int i = 0; i < 15; i++)
                {
                    located[i] = "   ";
                    property[i] = "   ";
                }
                fp = fopen(player.allname, "r");
                if (NULL == fp)
                {
                    printf("Open failure\n");
                    system("pause");
                    goto turn;
                }
                else
                {
                    fread(&player, sizeof(struct player_setting), 1, fp);
                    fread(&computer, sizeof(struct player_setting), 1, fp);
                }
                fclose(fp);
                for (int i = 0; i < 15; i++)
                {
                    if (player.house[i] == 1)
                    {
                        property[i] = "p0 ";
                    }
                    else if (player.house[i] == 2)
                    {
                        property[i] = "p1 ";
                    }
                    else if (player.house[i] == 3)
                    {
                        property[i] = "p2 ";
                    }
                    if (computer.house[i] == 1)
                    {
                        property[i] = "c0 ";
                    }
                    else if (computer.house[i] == 2)
                    {
                        property[i] = "c1 ";
                    }
                    else if (computer.house[i] == 3)
                    {
                        property[i] = "c2 ";
                    }
                }
                goto turn;
            }
            else if (choice == 2)
            {
                carduse(&computer.price, &player.price, player.cards, Cpass, player.house, computer.house, &player.money, &computer.money, property, computer.allname);
                goto turn;
            }
 
            else if (choice == 1)
            {
                for (int i = 0; i < 20; i++)
                {
                    goahead = rand() % 6;
                    printf("%s", dice[goahead]);
                    usleep(10 * 1000);
                    printf("\b\b\b\b\b");
                } /*ptestgo*/
                //goahead = 0;
                printf("%s前進%d格\n", dice[goahead], goahead + 1);
                system("pause");
                goahead = goahead + 1;
                player.current = ahead(goahead, player.current, located, property, player.name, &player.money);
                //system("cls");
                located[player.current] = &player.name;
 
                if (player.current == computer.current)
                {
                    char str[4];
                    str[0] = player.name;
                    str[1] = ' ';
                    str[2] = computer.name;
                    str[3] = '\0';
                    located[player.current] = str;
                }
                else
                {
                    char Pstr[4];
                    char Cstr[4];
                    Pstr[0] = player.name;
                    Pstr[1] = ' ';
                    Pstr[2] = ' ';
                    Pstr[3] = '\0';
                    Cstr[0] = computer.name;
                    Cstr[1] = ' ';
                    Cstr[2] = ' ';
                    Cstr[3] = '\0';
                    located[player.current] = Pstr;
                    located[computer.current] = Cstr;
                }
                map(located, property, chance);
                if (player.current == 8)
                {
                    int odds = rand() % 5;
                    //odds = 2;/*ptestch*/
                    chance = 1;
                    map(located, property, chance);
                    switch (odds)
                    {
                    case 0:
                        printf("得到新竹貢丸，騎著貢丸直達貢丸的故鄉\n");
                        system("pause");
                        c = 2;
                        player.current = ahead(c, player.current, located, property, player.name, &player.money);
                        chance = 0;
                        map(located, property, chance);
                        estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                        break;
                    case 1:
                        printf("獲得臭豆腐，周圍的人對你退避三舍\n");
                        if (computer.current == 7 || computer.current == 8)
                        {
                            c = 3;
                            player.current = back(c, player.current, located, property, player.name);
                            estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                        }
                        else if (computer.current == 9)
                        {
                            c = 3;
                            player.current = ahead(c, player.current, located, property, player.name, &player.money);
                            estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                        }
                        system("pause");
                        break;
                    case 2:
                        printf("天降鯡魚火旁彈，你被臭昏了,休息2回合\n");
                        player.turns = 0;
                        Ppass = 3;
                        system("pause");
                        break;
                    case 3:
                        printf("路邊的麻糬向你跑來，你陷入柔軟的麻糬裡面無法自拔,休息1回合\n");
                        player.turns = 0;
                        Ppass = 2;
                        system("pause");
                        break;
                    case 4:
                        printf("從收容所領養了火雞快速衝刺3格\n");
                        c = 3;
                        player.current = ahead(c, player.current, located, property, player.name, &player.money);
                        estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                        system("pause");
                        break;
                    }
                }
                else if (player.current == 12)
                {
                    int fate = rand() % 5;
                    //fate = 4;/*ptestf*/
                    chance = 2;
                    map(located, property, chance);
                    switch (fate) /*命運選擇*/
                    {
                    case 0:
                        printf("吃到包了金子的水餃+500萬元\n");
                        player.money += 500;
                        system("pause");
                        break;
                    case 1:
                        printf("九方雲集股票大漲+1000萬元\n");
                        player.money += 1000;
                        system("pause");
                        break;
                    case 2:
                        printf("九方雲集股票大跌-1500萬元\n");
                        player.money -= 1500;
                        system("pause");
                        break;
                    case 3:
                        printf("被強迫推銷愛心筆-500萬元\n");
                        player.money -= 500;
                        system("pause");
                        break;
                    case 4:
                        printf("鹽水蜂炮季\n");
                        int i, poker[15], temp, pos;
                        poker[0] = 15;
                        for (i = 0; i < 15; ++i)
                            poker[i] = i;
                        for (i = 0; i < 15; ++i)
                        {
                            pos = 14 * rand() / RAND_MAX;
                            temp = poker[i];
                            poker[i] = poker[pos];
                            poker[pos] = temp;
                        }
                        for (i = 0; i < 15; ++i)
                        {
                            if (player.house[poker[i]] == 1 || player.house[poker[i]] == 2|| player.house[poker[i]] == 3)
                            {
                                player.house[poker[i]] = 0;
                                property[poker[i]] = "\033[41m   \033[m";
                                printf("場上隨機一棟房子被炸了\n");
                                break;
                            }
                            if (computer.house[poker[i]] == 1 || computer.house[poker[i]] == 2|| computer.house[poker[i]] == 3)
                            {
                                computer.house[poker[i]] = 0;
                                property[poker[i]] = "\033[41m   \033[m";
                                printf("場上隨機一棟房子被炸了\n");
                                break;
                            }
                        }
                        usleep(TIME * 10);
                        break;
                    }
                }
                else if (player.current == 4)
                {
                    int buy;
                    int sure;
                    chance = 3;
                    map(located, property, chance);
                card:
                    printf("\n%s:%d萬元  %s:%d萬元\n", player_allname, player.money, computer.allname, computer.money);
                    printf("----------------------------------------\n");
                    printf("歡迎光臨卡片商店，想要買點什麼嗎?(請輸入想購買卡片的編號)\n");
                    scanf("%d", &buy);
                    switch (buy)
                    {
                    case 1:
                        printf("是否要購買火旁龍呢(價格3000萬)? [1]是[0]否\n");
                        scanf("%d", &sure);
                        if (sure == 1)
                        {
                            if (player.money > 3000)
                            {
                                player.money -= 3000;
                                player.cards[0]++;
                                printf("獲得火旁龍，您的金錢剩餘%d\n", player.money);
                            }
                            else
                            {
                                printf("抱歉您的餘額不足喔\n");
                            }
                            goto card;
                        }
                        else
                        {
                            goto card;
                        }
                    case 2:
                        printf("是否要購買南部粽呢(價格1500萬)? [1]是[0]否\n");
                        scanf("%d", &sure);
                        if (sure == 1)
                        {
                            if (player.money > 1500)
                            {
                                player.money -= 1500;
                                player.cards[1]++;
                                printf("獲得南部粽，您的金錢剩餘%d\n", player.money);
                            }
                            else
                            {
                                printf("抱歉您的餘額不足喔\n");
                            }
                            goto card;
                        }
                        else
                        {
                            goto card;
                        }
                    case 3:
                        printf("是否要購買彰化肉粽呢(價格1500萬)? [1]是[0]否\n");
                        scanf("%d", &sure);
                        if (sure == 1)
                        {
                            if (player.money > 1500)
                            {
                                player.money -= 1500;
                                player.cards[2]++;
                                printf("獲得彰化肉粽\n");
                            }
                            else
                            {
                                printf("抱歉您的餘額不足喔\n");
                            }
                            goto card;
                        }
                        else
                        {
                            goto card;
                        }
                    case 4:
                        printf("是否要購買1450呢(價格1450萬)? [1]是[0]否\n");
                        scanf("%d", &sure);
                        if (sure == 1)
                        {
                            if (player.money > 1450)
                            {
                                player.money -= 1450;
                                player.cards[3]++;
                                printf("獲得1450，您的金錢剩餘%d\n", player.money);
                            }
                            else
                            {
                                printf("抱歉您的餘額不足喔\n");
                            }
                            goto card;
                        }
                        else
                        {
                            goto card;
                        }
                    case 5:
                        printf("是否要購買8+9呢(價格3000萬)? [1]是[0]否\n");
                        scanf("%d", &sure);
                        if (sure == 1)
                        {
                            if (player.money > 3000)
                            {
                                player.money -= 3000;
                                player.cards[4]++;
                                printf("獲得8+9，您的金錢剩餘%d\n", player.money);
                            }
                            else
                            {
                                printf("抱歉您的餘額不足喔\n");
                            }
                            goto card;
                        }
                        else
                        {
                            goto card;
                        }
                    default:
                        printf("是否要離開呢? [1]是[0]否\n");
                        scanf("%d", &sure);
                        if (sure == 1)
                        {
                            break;
                        }
                        else
                        {
                            goto card;
                        }
                    }
                }
                else if (player.current == 0)
                {
                    printf("%s向銀行貸款2000萬\n", player_allname);
                    player.money += 2000;
                    system("pause");
                }
                else
                {
                    estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                }
            }
            else
            {
                printf("嘿，請照上面的指示打不要亂輸入..\n");
                system("pause");
                goto turn;
            }
        }
        if (player.current == computer.current)
        {
            char str[4];
            str[0] = player.name;
            str[1] = ' ';
            str[2] = computer.name;
            str[3] = '\0';
            located[player.current] = str;
        }
        else
        {
            char Pstr[4];
            char Cstr[4];
            Pstr[0] = player.name;
            Pstr[1] = ' ';
            Pstr[2] = ' ';
            Pstr[3] = '\0';
            Cstr[0] = computer.name;
            Cstr[1] = ' ';
            Cstr[2] = ' ';
            Cstr[3] = '\0';
            located[player.current] = Pstr;
            located[computer.current] = Cstr;
        }
        chance = 0;
        map(located, property, chance);
        located[player.current] = " ";
        player.turns = 0;
        goto turn;
    }
    else
    { /*魔王*/
        Cpass = 1;
        for (Ppass; Ppass > 0; Ppass--)
        {
            system("cls");
            if (player.current == computer.current)
            {
                char str[4];
                str[0] = player.name;
                str[1] = ' ';
                str[2] = computer.name;
                str[3] = '\0';
                located[player.current] = str;
            }
            else
            {
                char Pstr[4];
                char Cstr[4];
                Pstr[0] = player.name;
                Pstr[1] = ' ';
                Pstr[2] = ' ';
                Pstr[3] = '\0';
                Cstr[0] = computer.name;
                Cstr[1] = ' ';
                Cstr[2] = ' ';
                Cstr[3] = '\0';
                located[player.current] = Pstr;
                located[computer.current] = Cstr;
            }
            map(located, property, chance);
            printf("\n%s:%d萬元  %s:%d萬元\n", player_allname, player.money, computer.allname, computer.money);
            printf("----------------------------------------\n");
            printf("Maou turn%d\n", Ppass);
            chance = 0;
            for (int i = 0; i < 20; i++)
            {
                goahead = rand() % 6;
                printf("%s", dice[goahead]);
                usleep(10 * 1000);
                printf("\b\b\b\b\b");
            }
            //goahead = 3; /*ctestgo*/
            printf("%s前進%d格\n", dice[goahead], goahead + 1);
            usleep(TIME * 10);
            goahead = goahead + 1;
            computer.current = ahead(goahead, computer.current, located, property, computer.name, &computer.money);
            //system("cls");
            located[computer.current] = &computer.name;
            if (computer.current == 8)
            {
                int odds = rand() % 5;
                //odds = 2;
                chance = 1;
                if (player.current == computer.current)
                {
                    char str[4];
                    str[0] = player.name;
                    str[1] = ' ';
                    str[2] = computer.name;
                    str[3] = '\0';
                    located[player.current] = str;
                }
                else
                {
                    char Pstr[4];
                    char Cstr[4];
                    Pstr[0] = player.name;
                    Pstr[1] = ' ';
                    Pstr[2] = ' ';
                    Pstr[3] = '\0';
                    Cstr[0] = computer.name;
                    Cstr[1] = ' ';
                    Cstr[2] = ' ';
                    Cstr[3] = '\0';
                    located[player.current] = Pstr;
                    located[computer.current] = Cstr;
                }
                map(located, property, chance);
                switch (odds)
                {
                case 0:
                    printf("Maou得到新竹貢丸，騎著貢丸直達貢丸的故鄉\n");
                    usleep(TIME * 10);
                    c = 2;
                    computer.current = ahead(c, computer.current, located, property, computer.name, &computer.money);
                    estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                    break;
                case 1:
                    printf("Maou獲得臭豆腐，周圍的人對Maou退避三舍\n");
                    if (player.current == 7 || player.current == 8)
                    {
                        located[player.current] = "   ";
                        c = 3;
                        player.current = back(c, player.current, located, property, player.name);
                        estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                    }
                    else if (player.current == 9)
                    {
                        located[player.current] = "   ";
                        c = 3;
                        player.current = ahead(c, player.current, located, property, player.name, &player.money);
                        estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                    }
                    usleep(TIME * 10);
                    break;
                case 2:
                    printf("天降鯡魚火旁彈，Maou被臭昏了,休息2回合\n");
                    player.turns = 1;
                    Cpass = 3;
                    chance = 0;
                    usleep(TIME * 10);
                    break;
                case 3:
                    printf("路邊的麻糬向Maou跑來，Maou陷入柔軟的麻糬裡面無法自拔,休息1回合\n");
                    player.turns = 1;
                    Cpass = 2;
                    chance = 0;
                    usleep(TIME * 10);
                    break;
                case 4:
                    printf("Maou從收容所領養了火雞快速衝刺3格\n");
                    c = 3;
                    computer.current = ahead(c, computer.current, located, property, computer.name, &computer.money);
                    estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                    usleep(TIME * 10);
                    break;
                }
            }
            else if (computer.current == 12)
            {
                int fate = rand() % 5;
                chance = 2; /*ctestf*/
                switch (fate)
                {
                case 0:
                    printf("Maou吃到包了金子的水餃+500萬元\n");
                    computer.money += 500;
                    usleep(TIME * 10);
                    break;
                case 1:
                    printf("九方雲集股票大漲+1000萬元\n");
                    computer.money += 1000;
                    usleep(TIME * 10);
                    break;
                case 2:
                    printf("九方雲集股票大跌-1500萬元\n");
                    computer.money -= 1500;
                    usleep(TIME * 10);
                    break;
                case 3:
                    printf("Maou被強迫推銷愛心筆-500萬元\n");
                    computer.money -= 500;
                    usleep(TIME * 10);
                    break;
                case 4:
                    printf("鹽水蜂炮季\n");
                    int i, poker[15], temp, pos;
                    poker[0] = 15;
                    for (i = 0; i < 15; ++i)
                        poker[i] = i;
                    for (i = 0; i < 15; ++i)
                    {
                        pos = 14 * rand() / RAND_MAX;
                        temp = poker[i];
                        poker[i] = poker[pos];
                        poker[pos] = temp;
                    }
                    for (i = 0; i < 15; ++i)
                    {
                        if (player.house[i] == 1 || player.house[i] == 2)
                        {
                            player.house[i] = 0;
                            property[i] = "\033[41m   \033[m";
                            printf("場上隨機一棟房子被炸了\n");
                            break;
                        }
                        if (computer.house[i] == 1 || computer.house[i] == 2)
                        {
                            computer.house[i] = 0;
                            property[i] = "\033[41m   \033[m";
                            printf("場上隨機一棟房子被炸了\n");
                            break;
                        }
                    }
                    usleep(TIME * 10);
                    break;
                }
            }
            else if (computer.current == 0)
            {
                //Cround++;
                printf("Maou向銀行貸款2000萬");
                computer.money += 2000;
                usleep(TIME * 10);
            }
            else if (computer.current == 4)
            {
                int buy = rand() % 5;
                //buy = 2; /*ctestc*/
                chance = 3;
                map(located, property, chance);
                if (computer.money > 3000)
                {
                    buy++;
                    switch (buy)
                    {
                    case 1:
                        computer.money -= 3000;
                        printf("Maou獲得火旁龍\n");
                        int out = 0;
                        for (int i = 0; i < 15; i++)
                        {
                            if (player.house[i] == 1 || player.house[i] == 2|| player.house[i] == 3)
                            {
                                player.house[i] = 0;
                                out = 1;
                                property[i] = "\033[41m   \033[m";
                                printf("使用火旁龍，%s的房子被炸了\n", player_allname);
                                usleep(TIME * 10);
                                break;
                            }
                        }
                        if (out == 0)
                        {
                            printf("火旁龍遊行了一圈,街上的人都很開心，Maou獲得香油錢4000元");
                            computer.money += 4000;
                            usleep(TIME * 10);
                            break;
                        }
                        else
                        {
                            break;
                        }
                    case 2:
                        computer.money -= 1500;
                        printf("獲得南部粽\n");
                        printf("Maou將一綑南部粽送給%s，讓%s吃粽子吃到脹氣走不動，休息一回合\n", player_allname, player_allname);
                        Ppass++;
                        usleep(TIME * 10);
                        break;
 
                    case 3:
                        computer.money -= 1500;
                        printf("Maou獲得彰化肉粽\n");
                        printf("送肉粽隊伍經過%s的地，%s下次所收過路費砍半\n", player_allname, player_allname);
                        player.price = 1;
                        usleep(TIME * 10);
                        break;
 
                    case 4:
                        computer.money -= 1450;
                        printf("Maou獲得1450\n");
                        printf("Maou雇用1450，下次收取過路費加倍\n");
                        computer.price = 2;
                        usleep(TIME * 10);
                        break;
 
                    case 5:
                        computer.money -= 3000;
                        printf("Maou獲得8+9\n");
                        printf("8+9向%s收取保護費2000萬元\n", player_allname);
                        player.money -= 2000;
                        computer.money += 2000;
                        usleep(TIME * 10);
                        break;
 
                    default:
                        printf("Maou離開了卡片商店");
                        usleep(TIME * 10);                   
                        break;
                    }
                }
                else{
                    printf("Maou離開了卡片商店");
                    usleep(TIME * 10);
                }
            }
            else
            {
                estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
            }
            if (player.current == computer.current)
            {
                char str[4];
                str[0] = player.name;
                str[1] = ' ';
                str[2] = computer.name;
                str[3] = '\0';
                located[player.current] = str;
            }
            else
            {
                char Pstr[4];
                char Cstr[4];
                Pstr[0] = player.name;
                Pstr[1] = ' ';
                Pstr[2] = ' ';
                Pstr[3] = '\0';
                Cstr[0] = computer.name;
                Cstr[1] = ' ';
                Cstr[2] = ' ';
                Cstr[3] = '\0';
                located[player.current] = Pstr;
                located[computer.current] = Cstr;
            }
            chance = 0;
            map(located, property, chance);
            located[computer.current] = " ";
        }
        player.turns = 1;
        goto turn;
    }
end:
    system("cls");
    if(computer.money<=0){
        printf("    ^  ^\n  ( ·w· ∩ (Ｏ)\n o.　　,/.  ||\n  Ｏ＿./\n     (/\n     i|I    【WIN】\n    -----\n");
        printf("恭喜你打敗Maou獲得神器平底鍋，獲得無上的力量並成為神。\n");
        system("pause");
        system("cls");
        printf("名字：%s\n", player.allname);
        printf("擁有資產：%d萬元\n", player.money);
    }
    else{
        char g[] = "你耗盡了生命，墜落在無盡的深淵...";
        for (int i = 0; g[i] != '\0'; i++)
        {
            printf("%c", g[i]);
            usleep(TIME);
        }
        printf("\n");
    }
    system("pause");
    goto trueend;
trueend:
    printf("請問要重新開始遊戲嗎？ [1]yes [2]no\n");
    int ans1;
    scanf("%d", &ans1);
    if (ans1 == 1){
        system("cls");
        goto start;
    }
    else if(ans1 == 2){
        return 0;
    }
    else{
        printf("好好按照指令是很難逆\n");
        goto trueend;
    }
}
 
/*定義前進函數*/
int map(char *[], char *[], int);
int ahead(int goahead, int current, char *located[], char *property[], char name, int *money)
{
    int b;
    located[current] = "   ";
    for (b = 0; b < goahead; b++)
    {
        current++;
        if (current >= 16)
        {
            printf("經過地獄銀行，領取銀行發放的2000萬補助\n");
            *money += 2000;
            current = 0;
            usleep(TIME * 10);
        }
    }
    return current;
}
 
/*定義後退函數*/
int map(char *[], char *[], int);
int back(int goback, int current, char *located[], char *property[], char name)
{
    int a, b;
    for (b = 0, a = 0; b < goback; b++)
    {
        if (current <= 0)
        {
            current = 0;
        }
        else
        {
            current = current - 1;
        }
    }
    return current;
}
 
/*房地產*/
struct player_setting;
int map(char *[], char *[], int);
int estate(int *pprice, int *cprice, int p_turns, int p_house[15], int c_house[15], int p_current, int c_current, int *p_money, int *c_money, char *located[], char *property[], char player_allname)
{
    int block = 0;
    int toll_land = 500;
    int toll_house1 = 1000;
    int toll_house2 = 1500;
    int a;
    if (p_turns == 1)
    {
        switch (p_current)
        {
        case 1:
            block = 0;
            break;
        case 2:
            block = 1;
            break;
        case 3:
            block = 2;
            break;
 
        case 5:
            block = 4;
            break;
        case 6:
            block = 5;
            break;
        case 7:
            block = 6;
            break;
 
        case 9:
            block = 8;
            break;
        case 10:
            block = 9;
            break;
        case 11:
            block = 10;
            break;
 
        case 13:
            block = 12;
            break;
        case 14:
            block = 13;
            break;
        case 15:
            block = 14;
            break;
 
        default:
            break;
        }
        if (c_house[block] == 0)
        {
            if (p_house[block] == 0)
            {
                if (*p_money >= 1500)
                {
                    printf("您現在剩下%d萬元，請問要購買地盤嗎？購買地盤需1500萬元。<1>當然要購買！<任意鍵>再想想好了\n", *p_money);
                    scanf("%d", &a);
                    if (a == 1)
                    {
                        p_house[block] = 1;
                        *p_money = *p_money - 1500;
                        property[block] = "p0 ";
                    }
                }
                else
                {
                    printf("錢不夠ㄌ請繼續前進\n");
                    //break;
                }
            }
            else if (p_house[block] == 1)
            {
                if (*p_money >= 1000)
                {
                    printf("您現在剩下%d萬元，請問要建造路邊攤嗎？建造路邊攤需1000萬元。<1>不建白不建！<任意鍵>再想想好了\n", *p_money);
                    scanf("%d", &a);
                    if (a == 1)
                    {
                        p_house[block] = 2;
                        *p_money = *p_money - 1000;
                        property[block] = "p1 ";
                    }
                }
                else
                {
                    printf("錢不夠ㄌ請繼續前進");
                    //break;
                }
            }
            else if (p_house[block] == 2)
            {
                if (*p_money >= 1000)
                {
                    printf("您現在剩下%d萬元，請問要建造店面嗎？建造店面需1000萬元。<1>加吧！<任意鍵>再想想好了\n", *p_money);
                    scanf("%d", &a);
                    if (a == 1)
                    {
                        p_house[block] = 3;
                        *p_money = *p_money - 1000;
                        property[block] = "p2 ";
                    }
                }
                else
                {
                    printf("錢不夠ㄌ請繼續前進");
                    //break;
                }
            }
            else
            {
                printf("房地產已到最高級別！\n");
            }
            //system("pause");
            //break;
        }
        else
        {
            if (*cprice == 0)
            {
                switch (c_house[block])
                {
                case 1:
                    printf("走到Maou的地盤，需支付500萬元過路費。\n");
                    *c_money = *c_money + toll_land;
                    *p_money = *p_money - toll_land;
                    break;
                case 2:
                    printf("走到Maou的一層房，需支付1000萬元過路費。\n");
                    *c_money = *c_money + toll_house1;
                    *p_money = *p_money - toll_house1;
                    break;
                case 3:
                    printf("走到Maou的兩層房，需支付1500萬元過路費。\n");
                    *c_money = *c_money + toll_house2;
                    *p_money = *p_money - toll_house2;
                    break;
                default:
                    break;
                }
            }
            if (*cprice == 1)
            {
                switch (c_house[block])
                {
                case 1:
                    printf("走到Maou的地盤，需支付250萬元過路費。\n");
                    *c_money = *c_money + toll_land / 2;
                    *p_money = *p_money - toll_land / 2;
                    *cprice = 0;
                    break;
                case 2:
                    printf("走到Maou的一層房，需支付500萬元過路費。\n");
                    *c_money = *c_money + toll_house1 / 2;
                    *p_money = *p_money - toll_house1 / 2;
                    *cprice = 0;
                    break;
                case 3:
                    printf("走到Maou的兩層房，需支付750萬元過路費。\n");
                    *c_money = *c_money + toll_house2 / 2;
                    *p_money = *p_money - toll_house2 / 2;
                    *cprice = 0;
                    break;
                default:
                    break;
                }
            }
            if (*cprice == 2)
            {
                switch (c_house[block])
                {
                case 1:
                    printf("走到Maou的地盤，需支付1000萬元過路費。\n");
                    *c_money = *c_money + toll_land * 2;
                    *p_money = *p_money - toll_land * 2;
                    *cprice = 0;
                    break;
                case 2:
                    printf("走到Maou的一層房，需支付2000萬元過路費。\n");
                    *c_money = *c_money + toll_house1 * 2;
                    *p_money = *p_money - toll_house1 * 2;
                    *cprice = 0;
                    break;
                case 3:
                    printf("走到Maou的兩層房，需支付3000萬元過路費。\n");
                    *c_money = *c_money + toll_house2 * 2;
                    *p_money = *p_money - toll_house2 * 2;
                    *cprice = 0;
                    break;
                default:
                    break;
                }
            }
        }
        system("pause");
        // break;
    }
    else
    {
        switch (c_current)
        {
        case 1:
            block = 0;
            break;
        case 2:
            block = 1;
            break;
        case 3:
            block = 2;
            break;
 
        case 5:
            block = 4;
            break;
        case 6:
            block = 5;
            break;
        case 7:
            block = 6;
            break;
 
        case 9:
            block = 8;
            break;
        case 10:
            block = 9;
            break;
        case 11:
            block = 10;
            break;
 
        case 13:
            block = 12;
            break;
        case 14:
            block = 13;
            break;
        case 15:
            block = 14;
            break;
 
        default:
            break;
        }
        if (p_house[block] == 0)
        {
            if (*c_money >= 1500)
            {
                switch (c_house[block])
                {
                case 0:
                    printf("Maou以1500萬元購下該地盤！\n");
                    c_house[block] = 1;
                    *c_money = *c_money - 1500;
                    property[block] = "c0 ";
                    break;
                case 1:
                    printf("Maou以1000萬元建造路邊攤！\n");
                    c_house[block] = 2;
                    *c_money = *c_money - 1000;
                    property[block] = "c1 ";
                    break;
                case 2:
                    printf("Maou以1000萬元建造店面！\n");
                    c_house[block] = 3;
                    *c_money = *c_money - 1000;
                    property[block] = "c2 ";
                    break;
                case 3:
                    printf("Maou的房已達最高等級！\n");
                    break;
                default:
                    break;
                }
            }
            else
            {
                printf("Maou:沒錢買房，再說");
            }
            system("pause");
            // break;
        }
        else
        {
            if (*pprice == 0)
            {
                switch (p_house[block])
                {
                case 1:
                    printf("Maou走到你的地盤，支付500萬元過路費。\n");
                    *c_money = *c_money - toll_land;
                    *p_money = *p_money + toll_land;
                    break;
                case 2:
                    printf("Maou走到你的一層房，支付1000萬元過路費。\n");
                    *c_money = *c_money - toll_house1;
                    *p_money = *p_money + toll_house1;
                    break;
                case 3:
                    printf("Maou走到你的兩層房，支付1500萬元過路費。\n");
                    *c_money = *c_money - toll_house2;
                    *p_money = *p_money + toll_house2;
                    break;
                default:
                    break;
                }
            }
            else if (*pprice == 1)
            {
                switch (p_house[block])
                {
                case 1:
                    printf("Maou走到你的地盤，支付250萬元過路費。\n");
                    *c_money = *c_money - toll_land / 2;
                    *p_money = *p_money + toll_land / 2;
                    *pprice = 0;
                    break;
                case 2:
                    printf("Maou走到你的地盤，支付500萬元過路費。\n");
                    *c_money = *c_money - toll_house1 / 2;
                    *p_money = *p_money + toll_house1 / 2;
                    *pprice = 0;
                    break;
                case 3:
                    printf("Maou走到你的兩層房，支付750萬元過路費。\n");
                    *c_money = *c_money - toll_house2 / 2;
                    *p_money = *p_money + toll_house2 / 2;
                    *pprice = 0;
                    break;
                default:
                    break;
                }
            }
            else if (*pprice == 2)
            {
                switch (p_house[block])
                {
                case 1:
                    printf("Maou走到你的地盤，支付1000萬元過路費。\n");
                    *c_money = *c_money - toll_land * 2;
                    *p_money = *p_money + toll_land * 2;
                    *pprice = 0;
                    break;
                case 2:
                    printf("Maou走到你的一層房，支付2000萬元過路費。\n");
                    *c_money = *c_money - toll_house1 * 2;
                    *p_money = *p_money + toll_house1 * 2;
                    *pprice = 0;
                    break;
                case 3:
                    printf("Maou走到你的兩層房，支付3000萬元過路費。\n");
                    *c_money = *c_money - toll_house2 * 2;
                    *p_money = *p_money + toll_house2 * 2;
                    *pprice = 0;
                    break;
                default:
                    break;
                }
            }
            system("pause");
            // break;
        }
    }
    return 0;
}
 
/*卡片*/ /*card,turn,house*2,money,property,name*/
int carduse(int *cprice, int *pprice, int card[5], int turns, int my_house[15], int you_house[15], int *my_money, int *you_money, char *property[], int allname)
{
    int use;
    printf("你擁有的卡片:\n");
    if (card[0] >= 1)
    {
        printf("1.火旁龍 ");
    }
    if (card[1] >= 1)
    {
        printf("2.南部粽 ");
    }
    if (card[2] >= 1)
    {
        printf("3.彰化肉粽 ");
    }
    if (card[3] >= 1)
    {
        printf("4.1450 ");
    }
    if (card[4] >= 1)
    {
        printf("5.8+9 ");
    }
    if (card[0] == 0 && card[2] == 0 && card[3] == 0 && card[4] == 0 && card[1] == 0)
    {
        printf("抱歉你沒有卡片呢");
        system("pause");
        return 0;
    }
used:
    printf("\n想使用什麼卡片呢");
    scanf("%d", &use);
    switch (use)
    {
    case 1:
        if (card[0] >= 1)
        {
            card[0] --;
            for (int i = 0; i < 15; i++)
            {
                if (you_house[i] == 1 || you_house[i] == 2 || you_house[i] == 3)
                {
                    you_house[i] = 0;
                    property[i] = "\033[41m   \033[m";
                    printf("使用火旁龍，%s的房子被炸了\n", allname);
                    system("pause");
                    return 0;
                }
                else
                {
                    continue;
                }
            }
            printf("火旁龍遊行了一圈,街上的人都很開心,獲得香油錢4000元");
            system("pause");
            *my_money += 4000;
        }
        else
        {
            printf("抱歉你沒有這張卡");
            system("pause");
            goto used;
        }
        break;
    case 2:
        if (card[1] >= 1)
        {
            card[1]--;
            printf("將一綑南部粽送給%s，使之粽子吃到脹氣走不動，休息一回合\n", allname);
            turns++;
            system("pause");
            return turns;
        }
        else
        {
            printf("抱歉你沒有這張卡");
            system("pause");
            goto used;
        }
        break;
    case 3:
        if (card[2] >= 1)
        {
            card[2]--;
            printf("送肉粽隊伍經過Maou的地，Maou下次收取過路費砍半\n");
            *cprice = 1; /*改房產*/
            system("pause");
            return 0;
        }
        else
        {
            printf("抱歉你沒有這張卡");
            system("pause");
            goto used;
        }
        break;
    case 4:
        if (card[3] >= 1)
        {
            card[3]--;
            printf("雇用1450，下次收取過路費加倍\n");
            *pprice = 2;
            system("pause");
            return 0;
        }
        else
        {
            printf("抱歉你沒有這張卡");
            system("pause");
            goto used;
        }
        break;
    case 5:
        if (card[4] >= 1)
        {
            card[4]--;
            printf("8+9向%s收取保護費2000萬元\n", allname);
            *you_money -= 2000;
            *my_money += 2000;
            return 0;
        }
        else
        {
            printf("抱歉你沒有這張卡");
            system("pause");
            goto used;
        }
        break;
    default:
        break;
    }
    return 0;
}
 
/*地圖描繪*/
int map(char *located[], char *property[], int chance)
{
    char *a[] = {"\033[45m+----------------+\033[m", "\033[45m|                |\033[m", "\033[45m| ************** |\033[m", "\033[45m|  # 機    會 #  |\033[m", "\033[45m| ************** |\033[m", "\033[45m|                |\033[m", "\033[45m|        @       |\033[m", "\033[45m|     @     @    |\033[m", "\033[45m|  ~~~~~~~~~~~~  |\033[m", "\033[45m|                |\033[m", "\033[45m+----------------+\033[m"};
    char *b[] = {"\033[45m+----------------+\033[m", "\033[45m|                |\033[m", "\033[45m| ************** |\033[m", "\033[45m|  @ 命    運 @  |\033[m", "\033[45m| ************** |\033[m", "\033[45m|                |\033[m", "\033[45m|        $       |\033[m", "\033[45m|    $   O   $   |\033[m", "\033[45m|        $       |\033[m", "\033[45m|                |\033[m", "\033[45m+----------------+\033[m"};
    char *c[] = {"                  ", "                  ", "                  ", "                  ", "                  ", "                  ", "                  ", "                  ", "                  ", "                  ", "                  "};
    char *d[] = {" +_______________+", "  /             \\ ", " /  卡 片 商 店  \\", "/_               _\\", "  |  1. 火旁龍  | ", "  |  2. 南部粽  | ", "  |  3. 彰化肉粽| ", "  |  4. 1450    | ", "  |  5. 8 + 9   | ", "  |  \033[36m[0] 離開\033[m   | ", " -----------------"};
    if (chance == 1)
    {
        for (int i = 0; i < 12; i++)
        {
            c[i] = a[i];
            system("cls");
            printf("==============================================\n");
            printf("|\033[33m機    會\033[m|苗 栗 國|貢 丸 區|中    壢|\033[33m命    運\033[m|\n");
            printf("|%s     |%s     |%s     |%s     |%s     |\n", property[7], property[8], property[9], property[10], property[11]);
            printf("|%s     |%s     |%s     |%s     |%s     |\n", located[8], located[9], located[10], located[11], located[12]);
            printf("==============================================\n");
            printf("|海    線|    %s    |天 龍 國|\n", c[0]);
            printf("|%s     |    %s    |%s     |\n", property[6], c[1], property[12]);
            printf("|%s     |    %s    |%s     |\n", located[7], c[2], located[13]);
            printf("==========    %s    ==========\n", c[3]);
            printf("|肉 圓 區|    %s    |後 花 園|\n", c[4]);
            printf("|%s     |    %s    |%s     |\n", property[5], c[5], property[13]);
            printf("|%s     |    %s    |%s     |\n", located[6], c[6], located[14]);
            printf("==========    %s    ==========\n", c[7]);
            printf("|火 雞 區|    %s    |東    部|\n", c[8]);
            printf("|%s     |    %s    |%s     |\n", property[4], c[9], property[14]);
            printf("|%s     |    %s    |%s     |\n", located[5], c[10], located[15]);
            printf("==============================================\n");
            printf("|\033[36m卡片商店\033[m|螞蟻王國|猴 子 區|墾    丁|\033[31m地獄銀行\033[m|\n");
            printf("|%s     |%s     |%s     |%s     |        |\n", property[3], property[2], property[1], property[0]);
            printf("|%s     |%s     |%s     |%s     |%s     |\n", located[4], located[3], located[2], located[1], located[0]);
            printf("==============================================\n");
            usleep(TIME);
        }
    }
    else if (chance == 2)
    {
        for (int i = 0; i < 12; i++)
        {
            c[i] = b[i];
            system("cls");
            printf("==============================================\n");
            printf("|\033[33m機    會\033[m|苗 栗 國|貢 丸 區|中    壢|\033[33m命    運\033[m|\n");
            printf("|%s     |%s     |%s     |%s     |%s     |\n", property[7], property[8], property[9], property[10], property[11]);
            printf("|%s     |%s     |%s     |%s     |%s     |\n", located[8], located[9], located[10], located[11], located[12]);
            printf("==============================================\n");
            printf("|海    線|    %s    |天 龍 國|\n", c[0]);
            printf("|%s     |    %s    |%s     |\n", property[6], c[1], property[12]);
            printf("|%s     |    %s    |%s     |\n", located[7], c[2], located[13]);
            printf("==========    %s    ==========\n", c[3]);
            printf("|肉 圓 區|    %s    |後 花 園|\n", c[4]);
            printf("|%s     |    %s    |%s     |\n", property[5], c[5], property[13]);
            printf("|%s     |    %s    |%s     |\n", located[6], c[6], located[14]);
            printf("==========    %s    ==========\n", c[7]);
            printf("|火 雞 區|    %s    |東    部|\n", c[8]);
            printf("|%s     |    %s    |%s     |\n", property[4], c[9], property[14]);
            printf("|%s     |    %s    |%s     |\n", located[5], c[10], located[15]);
            printf("==============================================\n");
            printf("|\033[36m卡片商店\033[m|螞蟻王國|猴 子 區|墾    丁|\033[31m地獄銀行\033[m|\n");
            printf("|%s     |%s     |%s     |%s     |        |\n", property[3], property[2], property[1], property[0]);
            printf("|%s     |%s     |%s     |%s     |%s     |\n", located[4], located[3], located[2], located[1], located[0]);
            printf("==============================================\n");
            usleep(TIME);
        }
    }
    else if (chance == 3)
    {
        for (int i = 12; i >= 0; i--)
        {
            c[i] = d[i];
            system("cls");
            printf("==============================================\n");
            printf("|\033[33m機    會\033[m|苗 栗 國|貢 丸 區|中    壢|\033[33m命    運\033[m|\n");
            printf("|%s     |%s     |%s     |%s     |%s     |\n", property[7], property[8], property[9], property[10], property[11]);
            printf("|%s     |%s     |%s     |%s     |%s     |\n", located[8], located[9], located[10], located[11], located[12]);
            printf("==============================================\n");
            printf("|海    線|    %s    |天 龍 國|\n", c[0]);
            printf("|%s     |    %s    |%s     |\n", property[6], c[1], property[12]);
            printf("|%s     |    %s    |%s     |\n", located[7], c[2], located[13]);
            printf("==========    %s   ==========\n", c[3]);
            printf("|肉 圓 區|    %s    |後 花 園|\n", c[4]);
            printf("|%s     |    %s    |%s     |\n", property[5], c[5], property[13]);
            printf("|%s     |    %s    |%s     |\n", located[6], c[6], located[14]);
            printf("==========    %s    ==========\n", c[7]);
            printf("|火 雞 區|    %s    |東    部|\n", c[8]);
            printf("|%s     |    %s    |%s     |\n", property[4], c[9], property[14]);
            printf("|%s     |    %s    |%s     |\n", located[5], c[10], located[15]);
            printf("==============================================\n");
            printf("|\033[36m卡片商店\033[m|螞蟻王國|猴 子 區|墾    丁|\033[31m地獄銀行\033[m|\n");
            printf("|%s     |%s     |%s     |%s     |        |\n", property[3], property[2], property[1], property[0]);
            printf("|%s     |%s     |%s     |%s     |%s     |\n", located[4], located[3], located[2], located[1], located[0]);
            printf("==============================================\n");
        }
    }
    else
    {
        system("cls");
        printf("==============================================\n");
        printf("|\033[33m機    會\033[m|苗 栗 國|貢 丸 區|中    壢|\033[33m命    運\033[m|\n");
        printf("|%s     |%s     |%s     |%s     |%s     |\n", property[7], property[8], property[9], property[10], property[11]);
        printf("|%s     |%s     |%s     |%s     |%s     |\n", located[8], located[9], located[10], located[11], located[12]);
        printf("==============================================\n");
        printf("|海    線|    %s    |天 龍 國|\n", c[0]);
        printf("|%s     |    %s    |%s     |\n", property[6], c[1], property[12]);
        printf("|%s     |    %s    |%s     |\n", located[7], c[2], located[13]);
        printf("==========    %s    ==========\n", c[3]);
        printf("|肉 圓 區|    %s    |後 花 園|\n", c[4]);
        printf("|%s     |    %s    |%s     |\n", property[5], c[5], property[13]);
        printf("|%s     |    %s    |%s     |\n", located[6], c[6], located[14]);
        printf("==========    %s    ==========\n", c[7]);
        printf("|火 雞 區|    %s    |東    部|\n", c[8]);
        printf("|%s     |    %s    |%s     |\n", property[4], c[9], property[14]);
        printf("|%s     |    %s    |%s     |\n", located[5], c[10], located[15]);
        printf("==============================================\n");
        printf("|\033[36m卡片商店\033[m|螞蟻王國|猴 子 區|墾    丁|\033[31m地獄銀行\033[m|\n");
        printf("|%s     |%s     |%s     |%s     |        |\n", property[3], property[2], property[1], property[0]);
        printf("|%s     |%s     |%s     |%s     |%s     |\n", located[4], located[3], located[2], located[1], located[0]);
        printf("==============================================\n");
    }
    return 0;
}
